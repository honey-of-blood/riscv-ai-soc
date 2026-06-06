#!/usr/bin/env python3
"""
upload.py — host-side XMODEM firmware uploader for the RV32 SoC bootloader.

Usage:
    python upload.py --port /dev/ttyUSB0 --baud 115200 firmware.elf
    python upload.py --port /dev/ttyUSB0 --baud 115200 --raw firmware.bin

The tool opens the serial port, waits for the bootloader NAK, then sends the
binary image using standard XMODEM (128-byte blocks, 8-bit checksum).

Requires: pyserial  (pip install pyserial)
"""

import argparse
import os
import sys
import time

# ── XMODEM constants ────────────────────────────────────────────────────────
SOH = 0x01
EOT = 0x04
ACK = 0x06
NAK = 0x15
CAN = 0x18

BLOCK_SIZE   = 128
MAX_RETRIES  = 10
TIMEOUT_S    = 5.0


# ── Protocol helpers ─────────────────────────────────────────────────────────

def _checksum8(data: bytes) -> int:
    return sum(data) & 0xFF


def _pad_block(data: bytes) -> bytes:
    """Pad a data chunk to exactly BLOCK_SIZE bytes with 0x1A (CTRL-Z)."""
    assert len(data) <= BLOCK_SIZE
    return data + b'\x1a' * (BLOCK_SIZE - len(data))


def _make_packet(block_num: int, data: bytes) -> bytes:
    """Build one XMODEM packet: SOH | blk# | ~blk# | 128B | csum."""
    payload = _pad_block(data)
    bn  = block_num & 0xFF
    ibn = (~bn) & 0xFF
    csum = _checksum8(payload)
    return bytes([SOH, bn, ibn]) + payload + bytes([csum])


# ── Sender class ─────────────────────────────────────────────────────────────

class XmodemSender:
    """XMODEM sender that works with any file-like object exposing
    read(n), write(b), and a flush() method.  Designed so that tests
    can pass an in-memory queue instead of a real serial port.
    """

    def __init__(self, read_fn, write_fn, verbose: bool = True):
        self._read  = read_fn   # read_fn(n) -> bytes
        self._write = write_fn  # write_fn(b: bytes)
        self._verbose = verbose

    def _recv_byte(self, timeout: float = TIMEOUT_S) -> int:
        """Block until one byte arrives; raise TimeoutError on timeout."""
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            b = self._read(1)
            if b:
                return b[0]
            time.sleep(0.001)
        raise TimeoutError("No response from bootloader")

    def _log(self, msg: str) -> None:
        if self._verbose:
            print(msg, flush=True)

    def send(self, image: bytes) -> bool:
        """Send image bytes via XMODEM.  Returns True on success."""
        # Wait for NAK to start
        self._log("Waiting for bootloader NAK...")
        tries = 0
        while True:
            try:
                c = self._recv_byte(timeout=10.0)
            except TimeoutError:
                self._log("ERROR: bootloader did not respond")
                return False
            if c == NAK:
                break
            if c == CAN:
                self._log("ERROR: bootloader cancelled")
                return False
            tries += 1
            if tries > 30:
                self._log("ERROR: too many non-NAK bytes before start")
                return False

        # Slice into 128-byte blocks
        blocks = [image[i:i + BLOCK_SIZE] for i in range(0, len(image), BLOCK_SIZE)]
        if not blocks:
            blocks = [b'']  # send at least one block

        self._log(f"Sending {len(image)} bytes in {len(blocks)} blocks...")
        block_num = 1

        for blk_data in blocks:
            packet  = _make_packet(block_num, blk_data)
            retries = 0
            while retries < MAX_RETRIES:
                self._write(packet)
                try:
                    resp = self._recv_byte()
                except TimeoutError:
                    self._log(f"  Block {block_num}: timeout, retry {retries+1}")
                    retries += 1
                    continue
                if resp == ACK:
                    break
                if resp == NAK:
                    self._log(f"  Block {block_num}: NAK, retry {retries+1}")
                    retries += 1
                    continue
                if resp == CAN:
                    self._log("ERROR: bootloader cancelled mid-transfer")
                    return False
            else:
                self._log(f"ERROR: block {block_num} failed after {MAX_RETRIES} retries")
                return False

            block_num = (block_num + 1) & 0xFF
            if self._verbose and block_num % 16 == 0:
                pct = block_num * BLOCK_SIZE * 100 // len(image)
                print(f"  {pct}% ({block_num * BLOCK_SIZE} / {len(image)} bytes)",
                      flush=True)

        # End of transmission
        for _ in range(MAX_RETRIES):
            self._write(bytes([EOT]))
            try:
                if self._recv_byte() == ACK:
                    self._log("Transfer complete!")
                    return True
            except TimeoutError:
                pass
        self._log("ERROR: no ACK for EOT")
        return False


# ── CLI entry point ──────────────────────────────────────────────────────────

def main() -> None:
    parser = argparse.ArgumentParser(description="XMODEM firmware uploader for RV32 SoC")
    parser.add_argument("image", help="Firmware image (ELF or raw binary)")
    parser.add_argument("--port",  default="/dev/ttyUSB0", help="Serial port")
    parser.add_argument("--baud",  type=int, default=115200, help="Baud rate")
    parser.add_argument("--raw",   action="store_true",
                        help="Send as raw binary (default treats file as binary blob)")
    args = parser.parse_args()

    try:
        import serial  # type: ignore
    except ImportError:
        print("ERROR: pyserial not installed — run: pip install pyserial")
        sys.exit(1)

    with open(args.image, "rb") as f:
        image = f.read()

    print(f"Opening {args.port} @ {args.baud} baud")
    with serial.Serial(args.port, args.baud, timeout=TIMEOUT_S) as port:
        sender = XmodemSender(
            read_fn  = lambda n: port.read(n),
            write_fn = lambda b: port.write(b),
        )
        ok = sender.send(image)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
