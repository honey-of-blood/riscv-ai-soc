"""
Phase 16 XMODEM stress tests — hidden edge cases and corner conditions.

Infrastructure added here:
  PacketInterceptor  — sits on the h2d pipe; receives full 132-byte packets,
                       can modify any field before forwarding to the receiver.
  FlakeyReceiver     — replaces XmodemReceiver; NAKs specific block#s a
                       configurable number of times before ACKing (retry tests).
  run_loopback()     — thread helper used by every test below.

Test classes:
  TestProtocolInvariants  — pure math: checksum, complement, packet lengths
  TestEdgeCaseSizes       — 1, 127, 128, 129, 255, 256, 257, 512, 1023, 1024 bytes
  TestBytePatterns        — all-zeros, all-FF, alternating, random 20 KB, max 60 KB
  TestFieldCorruption     — checksum / blk# / inv / data[0] / data[127] corrupted once
  TestRetryBehavior       — NAK 1×, 9× (success), 10× (failure), multi-block retries
  TestBlockSequence       — 255-block, 260-block (wrap), out-of-order block → CAN
  TestSequentialTransfers — 5 independent transfers, varying-size sequence
"""

import sys
import os
import collections
import time
import threading
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
from upload import (  # noqa: E402
    XmodemSender, _checksum8, _make_packet, _pad_block,
    SOH, EOT, ACK, NAK, CAN, BLOCK_SIZE, MAX_RETRIES,
)

# ── BytePipe (copy from test_xmodem.py to keep the stress file self-contained) ─

class BytePipe:
    def __init__(self):
        self._q     = collections.deque()
        self._lock  = threading.Lock()
        self._event = threading.Event()

    def put(self, data: bytes) -> None:
        with self._lock:
            self._q.extend(data)
        self._event.set()

    def get(self, n: int, timeout: float = 3.0) -> bytes:
        deadline = time.monotonic() + timeout
        result   = bytearray()
        while len(result) < n:
            with self._lock:
                while self._q and len(result) < n:
                    result.append(self._q.popleft())
            if len(result) < n:
                remaining = deadline - time.monotonic()
                if remaining <= 0:
                    raise TimeoutError(f"BytePipe: got {len(result)}/{n} bytes")
                self._event.wait(timeout=min(remaining, 0.01))
                self._event.clear()
        return bytes(result)


# ── PacketInterceptor ────────────────────────────────────────────────────────
# Sits between sender's write_fn and the inner BytePipe.
# XmodemSender always writes a complete 132-byte packet or a 1-byte EOT.

class PacketInterceptor:
    """Intercepts XMODEM packets from the sender; modify_fn can corrupt any field.

    modify_fn(pkt_index: int, packet: bytes) -> bytes
      pkt_index: 1-based counter of packets seen (counts retransmits too).
      packet: 132-byte SOH block. Return the (possibly modified) packet.
    """
    def __init__(self, inner: BytePipe, modify_fn=None):
        self._inner     = inner
        self._modify    = modify_fn or (lambda idx, pkt: pkt)
        self._pkt_index = 0

    def put(self, data: bytes) -> None:
        if len(data) == 132 and data[0] == SOH:
            self._pkt_index += 1
            self._inner.put(self._modify(self._pkt_index, data))
        else:
            self._inner.put(data)   # EOT or other control bytes

    def get(self, n: int, timeout: float = 3.0) -> bytes:
        return self._inner.get(n, timeout)


# ── FlakeyReceiver ───────────────────────────────────────────────────────────
# Mirrors xmodem.c logic but NAKs specific block#s a configurable number of
# times before accepting them, to test the sender's retry machinery.

class FlakeyReceiver:
    """NAK rules: {block_num: n} means NAK block_num exactly n times before ACK.
    Block nums here are XMODEM block numbers (1-based, wrap at 255).
    """
    def __init__(self, read_fn, write_fn, nak_rules=None, max_retries=MAX_RETRIES):
        self._read        = read_fn
        self._write       = write_fn
        self._nak_left    = dict(nak_rules or {})
        self._max_retries = max_retries

    def _getb(self): return self._read(1)[0]
    def _putb(self, b): self._write(bytes([b]))

    def receive(self) -> bytes:
        buf      = bytearray()
        expected = 1
        retries  = 0
        self._putb(NAK)

        while True:
            try:
                c = self._getb()
            except TimeoutError:
                retries += 1
                if retries >= self._max_retries:
                    raise RuntimeError("FlakeyReceiver: timeout limit")
                self._putb(NAK)
                continue

            if c == EOT:
                self._putb(ACK)
                return bytes(buf)
            if c == CAN:
                raise RuntimeError("FlakeyReceiver: CAN received")
            if c != SOH:
                continue

            blk = self._getb()
            inv = self._getb()
            if (blk ^ inv) != 0xFF:
                self._putb(NAK)
                retries += 1
                if retries >= self._max_retries:
                    raise RuntimeError("FlakeyReceiver: header error limit")
                continue

            payload  = self._read(BLOCK_SIZE)
            csum_rx  = self._getb()
            if csum_rx != _checksum8(payload):
                self._putb(NAK)
                retries += 1
                if retries >= self._max_retries:
                    raise RuntimeError("FlakeyReceiver: checksum error limit")
                continue

            # Duplicate block (sender retransmitted a block we already ACKed)
            if blk == (expected - 1) & 0xFF:
                self._putb(ACK)
                continue

            if blk != expected & 0xFF:
                self._putb(CAN)
                raise RuntimeError(f"FlakeyReceiver: wrong block {blk}, expected {expected & 0xFF}")

            # Should we NAK this block due to nak_rules?
            key = blk
            if key in self._nak_left and self._nak_left[key] > 0:
                self._nak_left[key] -= 1
                self._putb(NAK)
                retries += 1
                if retries >= self._max_retries:
                    raise RuntimeError("FlakeyReceiver: nak rule exhausted retries")
                continue

            buf.extend(payload)
            expected = (expected + 1) & 0xFF
            retries  = 0   # reset per-block retry counter on success
            self._putb(ACK)


# ── run_loopback / flakey_loopback / intercepted_loopback helpers ────────────

def run_loopback(image: bytes, receiver_cls=None, receiver_kwargs=None,
                 modify_fn=None, timeout=30):
    """Wire sender ↔ receiver; return (ok: bool, received: bytes, recv_error: str|None)."""
    h2d_inner = BytePipe()
    d2h       = BytePipe()

    # Optionally intercept packets before they reach the receiver
    h2d = PacketInterceptor(h2d_inner, modify_fn) if modify_fn else h2d_inner

    rx_cls    = receiver_cls or _DefaultReceiver
    rx_kwargs = receiver_kwargs or {}
    receiver  = rx_cls(
        read_fn  = lambda n: h2d_inner.get(n),
        write_fn = lambda b: d2h.put(b),
        **rx_kwargs,
    )
    sender = XmodemSender(
        read_fn  = lambda n: d2h.get(n, timeout=3.0),
        write_fn = lambda b: h2d.put(b),
        verbose  = False,
    )

    result = {}

    def _recv():
        try:
            result["received"] = receiver.receive()
        except Exception as e:
            result["recv_error"] = str(e)

    def _send():
        result["sent"] = sender.send(image)

    tr = threading.Thread(target=_recv, daemon=True)
    ts = threading.Thread(target=_send, daemon=True)
    tr.start(); ts.start()
    tr.join(timeout=timeout)
    ts.join(timeout=timeout)

    return (
        result.get("sent", False),
        result.get("received", b""),
        result.get("recv_error"),
    )


class _DefaultReceiver:
    """Minimal XMODEM receiver used when no special receiver is needed."""
    def __init__(self, read_fn, write_fn):
        self._read  = read_fn
        self._write = write_fn

    def _getb(self): return self._read(1)[0]
    def _putb(self, b): self._write(bytes([b]))

    def receive(self) -> bytes:
        buf      = bytearray()
        expected = 1
        retries  = 0
        self._putb(NAK)

        while True:
            c = self._getb()
            if c == EOT:
                self._putb(ACK)
                return bytes(buf)
            if c == CAN:
                raise RuntimeError("CAN")
            if c != SOH:
                continue
            blk = self._getb()
            inv = self._getb()
            if (blk ^ inv) != 0xFF:
                self._putb(NAK); retries += 1
                if retries >= MAX_RETRIES: raise RuntimeError("header retries")
                continue
            payload = self._read(BLOCK_SIZE)
            csum_rx = self._getb()
            if csum_rx != _checksum8(payload):
                self._putb(NAK); retries += 1
                if retries >= MAX_RETRIES: raise RuntimeError("csum retries")
                continue
            if blk == (expected - 1) & 0xFF:
                self._putb(ACK); continue
            if blk != expected & 0xFF:
                self._putb(CAN); raise RuntimeError("wrong block")
            buf.extend(payload)
            expected = (expected + 1) & 0xFF
            retries  = 0
            self._putb(ACK)


def simple_loopback(image: bytes):
    ok, rx, _ = run_loopback(image)
    return ok, rx


# ─────────────────────────────────────────────────────────────────────────────
# TEST CLASSES
# ─────────────────────────────────────────────────────────────────────────────

class TestProtocolInvariants(unittest.TestCase):
    """Pure math — verify helpers are correct for all possible inputs."""

    def test_checksum_zero_block(self):
        self.assertEqual(_checksum8(bytes(128)), 0)

    def test_checksum_all_ff_block(self):
        data = bytes([0xFF] * 128)
        # 0xFF * 128 = 0x7F80; low byte = 0x80
        self.assertEqual(_checksum8(data), (0xFF * 128) & 0xFF)

    def test_checksum_sequential_bytes(self):
        data = bytes(range(128))
        expected = sum(range(128)) & 0xFF
        self.assertEqual(_checksum8(data), expected)

    def test_complement_invariant_all_block_numbers(self):
        for blk in range(256):
            pkt = _make_packet(blk, bytes(128))
            self.assertEqual(pkt[1] ^ pkt[2], 0xFF,
                             f"block# {blk}: complement failed")

    def test_packet_is_always_132_bytes(self):
        for blk in range(256):
            pkt = _make_packet(blk, bytes(128))
            self.assertEqual(len(pkt), 132)

    def test_soh_always_first(self):
        for blk in [0, 1, 127, 255]:
            pkt = _make_packet(blk, bytes(128))
            self.assertEqual(pkt[0], SOH)

    def test_checksum_matches_packet_payload(self):
        payload = bytes(range(128))
        pkt     = _make_packet(7, payload)
        self.assertEqual(pkt[131], _checksum8(payload))

    def test_padding_byte_is_ctrl_z(self):
        padded = _pad_block(b'A')
        self.assertEqual(padded[1:], b'\x1a' * 127)


class TestEdgeCaseSizes(unittest.TestCase):

    def _check(self, img):
        ok, rx = simple_loopback(img)
        self.assertTrue(ok, f"Transfer failed for {len(img)}-byte image")
        self.assertEqual(rx[:len(img)], img,
                         f"Data mismatch for {len(img)}-byte image")

    def test_one_byte(self):
        self._check(b'\xAB')

    def test_two_bytes(self):
        self._check(b'\xDE\xAD')

    def test_127_bytes(self):
        self._check(bytes(range(127)))

    def test_128_bytes_exact_block(self):
        self._check(bytes(range(128)))

    def test_129_bytes_crosses_block_boundary(self):
        self._check(bytes(range(129)))

    def test_255_bytes(self):
        self._check(bytes(b'\xAA' * 255))

    def test_256_bytes_two_full_blocks(self):
        self._check(bytes(range(256)))

    def test_257_bytes(self):
        self._check(bytes([i & 0xFF for i in range(257)]))

    def test_512_bytes_four_blocks(self):
        self._check(bytes([i & 0xFF for i in range(512)]))

    def test_1023_bytes(self):
        self._check(bytes([i & 0xFF for i in range(1023)]))

    def test_1024_bytes_eight_full_blocks(self):
        self._check(bytes([i & 0xFF for i in range(1024)]))


class TestBytePatterns(unittest.TestCase):

    def test_all_zeros_4kb(self):
        ok, rx = simple_loopback(bytes(4096))
        self.assertTrue(ok)
        self.assertEqual(rx[:4096], bytes(4096))

    def test_all_ff_4kb(self):
        img = bytes([0xFF] * 4096)
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:4096], img)

    def test_alternating_5a_a5(self):
        img = bytes([0x5A if i % 2 == 0 else 0xA5 for i in range(1024)])
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:1024], img)

    def test_incrementing_byte_values(self):
        img = bytes([i & 0xFF for i in range(256)] * 4)
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_random_20kb(self):
        import os
        img = b'\x7fELF' + os.urandom(20 * 1024 - 4)
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_max_app_size_60kb(self):
        import os
        img = b'\x7fELF' + os.urandom(60 * 1024 - 4)
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)


class TestFieldCorruption(unittest.TestCase):
    """Corrupt a specific field once → sender retransmits → success."""

    def _corrupt_once(self, byte_offset_in_packet):
        """Return a modify_fn that flips byte at `byte_offset_in_packet` in packet#1 only."""
        corrupted = [False]
        def modify(pkt_idx, pkt):
            if pkt_idx == 1 and not corrupted[0]:
                corrupted[0] = True
                pkt = bytearray(pkt)
                pkt[byte_offset_in_packet] ^= 0xFF
                return bytes(pkt)
            return pkt
        return modify

    def test_corrupt_checksum_field_retries_once(self):
        # Byte 131 = checksum in the first packet
        img = bytes(256)
        ok, rx, _ = run_loopback(img, modify_fn=self._corrupt_once(131))
        self.assertTrue(ok, "Transfer should succeed after 1 checksum error")
        self.assertEqual(rx[:256], img)

    def test_corrupt_block_number_retries_once(self):
        # Byte 1 = block# in the first packet
        img = bytes(128)
        ok, rx, _ = run_loopback(img, modify_fn=self._corrupt_once(1))
        self.assertTrue(ok, "Transfer should succeed after 1 block# error")

    def test_corrupt_inv_field_retries_once(self):
        # Byte 2 = ~block# in the first packet
        img = bytes(128)
        ok, rx, _ = run_loopback(img, modify_fn=self._corrupt_once(2))
        self.assertTrue(ok, "Transfer should succeed after 1 inv error")

    def test_corrupt_data_byte_pos0_retries_once(self):
        # Byte 3 = first data byte (offset 0 in payload)
        img = bytes(range(128))
        ok, rx, _ = run_loopback(img, modify_fn=self._corrupt_once(3))
        self.assertTrue(ok)
        self.assertEqual(rx[:128], img)

    def test_corrupt_data_byte_pos127_retries_once(self):
        # Byte 130 = last data byte (offset 127 in payload)
        img = bytes(range(128))
        ok, rx, _ = run_loopback(img, modify_fn=self._corrupt_once(130))
        self.assertTrue(ok)
        self.assertEqual(rx[:128], img)

    def test_corrupt_second_block_checksum_retries(self):
        """Corruption in block 2 (packet index 2): retry and succeed."""
        corrupted = [False]
        def modify(pkt_idx, pkt):
            if pkt_idx == 2 and not corrupted[0]:
                corrupted[0] = True
                pkt = bytearray(pkt)
                pkt[131] ^= 0x01
                return bytes(pkt)
            return pkt
        img = bytes(256)   # 2 blocks
        ok, rx, _ = run_loopback(img, modify_fn=modify)
        self.assertTrue(ok)
        self.assertEqual(rx[:256], img)

    def test_persistent_corruption_fails(self):
        """Every packet has a bad checksum → exhausts MAX_RETRIES → sender fails."""
        def always_corrupt(pkt_idx, pkt):
            pkt = bytearray(pkt)
            pkt[131] ^= 0xFF
            return bytes(pkt)
        img = bytes(128)
        ok, _, _ = run_loopback(img, modify_fn=always_corrupt, timeout=20)
        self.assertFalse(ok, "Should fail when checksum is always bad")


class TestRetryBehavior(unittest.TestCase):
    """Test the sender's retry state machine using FlakeyReceiver."""

    def _flakey_loopback(self, image, nak_rules, max_retries=MAX_RETRIES, timeout=30):
        ok, rx, err = run_loopback(
            image,
            receiver_cls=FlakeyReceiver,
            receiver_kwargs={"nak_rules": nak_rules, "max_retries": max_retries},
            timeout=timeout,
        )
        return ok, rx, err

    def test_nak_block1_once_succeeds(self):
        img = bytes(128)
        ok, rx, _ = self._flakey_loopback(img, nak_rules={1: 1})
        self.assertTrue(ok)
        self.assertEqual(rx[:128], img)

    def test_nak_block1_five_times_succeeds(self):
        img = bytes(128)
        ok, rx, _ = self._flakey_loopback(img, nak_rules={1: 5})
        self.assertTrue(ok)
        self.assertEqual(rx[:128], img)

    def test_nak_block1_nine_times_succeeds(self):
        # 9 NAKs < MAX_RETRIES=10 → sender succeeds on 10th attempt
        img = bytes(128)
        ok, rx, _ = self._flakey_loopback(img, nak_rules={1: 9})
        self.assertTrue(ok, "9 NAKs should still succeed (MAX_RETRIES=10)")
        self.assertEqual(rx[:128], img)

    def test_nak_block1_ten_times_fails(self):
        # 10 NAKs == MAX_RETRIES → sender gives up
        img = bytes(128)
        ok, _, _ = self._flakey_loopback(img, nak_rules={1: MAX_RETRIES}, timeout=20)
        self.assertFalse(ok, "10 NAKs should exhaust MAX_RETRIES and fail")

    def test_nak_every_block_once_multi_block(self):
        # 5 blocks, each NAKed once — all should recover
        img = bytes(5 * BLOCK_SIZE)
        nak_rules = {blk: 1 for blk in range(1, 6)}
        ok, rx, _ = self._flakey_loopback(img, nak_rules=nak_rules)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_nak_every_block_three_times_multi_block(self):
        # 3 blocks, each NAKed 3 times — all recover (3 < MAX_RETRIES)
        img = bytes(3 * BLOCK_SIZE)
        nak_rules = {1: 3, 2: 3, 3: 3}
        ok, rx, _ = self._flakey_loopback(img, nak_rules=nak_rules)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_nak_block2_not_block1(self):
        # Only block 2 has retries — block 1 passes immediately
        img = bytes(2 * BLOCK_SIZE)
        ok, rx, _ = self._flakey_loopback(img, nak_rules={2: 4})
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)


class TestBlockSequence(unittest.TestCase):

    def test_255_block_transfer(self):
        img = bytes([i & 0xFF for i in range(255 * BLOCK_SIZE)])
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_260_block_wrap(self):
        # Block numbers wrap: 1..255, 0, 1..4 for 260 blocks total
        img = bytes([i & 0xFF for i in range(260 * BLOCK_SIZE)])
        ok, rx = simple_loopback(img)
        self.assertTrue(ok)
        self.assertEqual(rx[:len(img)], img)

    def test_out_of_order_block_triggers_can(self):
        """Receiver gets block 2 before ACKing block 1 → sends CAN."""
        # Forge a stream: send block 2 first instead of block 1.
        h2d = BytePipe()
        d2h = BytePipe()

        receiver = _DefaultReceiver(
            read_fn  = lambda n: h2d.get(n),
            write_fn = lambda b: d2h.put(b),
        )
        result = {}

        def _recv():
            try:
                receiver.receive()
            except RuntimeError as e:
                result["error"] = str(e)

        t = threading.Thread(target=_recv, daemon=True)
        t.start()

        # Wait for NAK
        nak = d2h.get(1, timeout=3)
        self.assertEqual(nak, bytes([NAK]))

        # Send block 2 instead of block 1
        h2d.put(_make_packet(2, bytes(BLOCK_SIZE)))
        response = d2h.get(1, timeout=3)
        t.join(timeout=5)

        # Receiver should have sent CAN (0x18) and raised RuntimeError
        self.assertEqual(response, bytes([CAN]))
        self.assertIn("error", result)


class TestSequentialTransfers(unittest.TestCase):

    def test_five_sequential_independent_transfers(self):
        images = [
            b'\x7fELF' + bytes(i * 17 % 256 for i in range(252)),
            bytes(256),
            bytes([0xFF] * 512),
            bytes(range(256)) * 2,
            b'hello world\r\n',
        ]
        for i, img in enumerate(images):
            ok, rx = simple_loopback(img)
            self.assertTrue(ok, f"Transfer {i+1} failed")
            self.assertEqual(rx[:len(img)], img, f"Transfer {i+1} data mismatch")

    def test_varying_sizes_sequential(self):
        sizes = [1, 128, 129, 256, 1000, 4096]
        for sz in sizes:
            img = bytes([sz & 0xFF] * sz)
            ok, rx = simple_loopback(img)
            self.assertTrue(ok, f"Transfer of {sz} bytes failed")
            self.assertEqual(rx[:sz], img, f"Data mismatch at size {sz}")

    def test_alternating_small_and_large(self):
        pairs = [(b'X' * 1, bytes(4096)), (bytes(4096), b'Y' * 128)]
        for small, large in pairs:
            for img in (small, large):
                ok, rx = simple_loopback(img)
                self.assertTrue(ok)
                self.assertEqual(rx[:len(img)], img)


if __name__ == "__main__":
    unittest.main(verbosity=2)
