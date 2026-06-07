"""Phase 19 — sha3_top cocotb tests.

SHA3-256 (Keccak-f[1600]) test vectors from NIST FIPS 202.
SW side pads the input with SHA-3 domain separation (0x06) + 0x80 padding.
"""
import struct
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK = 10

CTRL   = 0x000
STATUS = 0x08C

SHA3_START = 1
SHA3_RESET = 2
SHA3_DONE  = 1

# SHA3-256 rate = 1088 bits = 136 bytes = 17 × 64-bit lanes


def sha3_256_pad(msg: bytes) -> bytes:
    """
    SHA-3 padding (FIPS 202 §B.2): append 0x06, zero-pad, set last bit 0x80.
    Returns padded block of exactly 136 bytes.
    """
    assert len(msg) < 136, "multi-block SHA-3 not exercised in hw test"
    padded = bytearray(136)
    padded[:len(msg)] = msg
    padded[len(msg)] ^= 0x06       # domain separation
    padded[135]      ^= 0x80       # final padding bit
    return bytes(padded)


def block_to_lanes(padded: bytes):
    """136 bytes → 17 × uint64_t little-endian lanes."""
    return list(struct.unpack_from('<17Q', padded))


async def reset_dut(dut):
    dut.rst_n.value = 0
    dut.psel.value = dut.penable.value = dut.pwrite.value = 0
    dut.paddr.value = dut.pwdata.value = 0
    await Timer(5 * CLK, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK, unit="ns")


async def apb_wr(dut, addr, data):
    dut.paddr.value = addr & 0x3FF; dut.pwdata.value = data & 0xFFFFFFFF
    dut.pwrite.value = 1; dut.psel.value = 1
    await RisingEdge(dut.clk); dut.penable.value = 1
    await RisingEdge(dut.clk); await Timer(1, unit="ns")
    dut.psel.value = dut.penable.value = dut.pwrite.value = 0


async def apb_rd(dut, addr):
    dut.paddr.value = addr & 0x3FF; dut.pwrite.value = 0; dut.psel.value = 1
    await RisingEdge(dut.clk); dut.penable.value = 1
    await RisingEdge(dut.clk); await Timer(1, unit="ns")
    v = int(dut.prdata.value)
    dut.psel.value = dut.penable.value = 0
    return v


async def wait_done(dut, timeout=300):
    for _ in range(timeout):
        await RisingEdge(dut.clk); await Timer(1, unit="ns")
        if (await apb_rd(dut, STATUS)) & SHA3_DONE: return
    assert False, "sha3 done timeout"


async def hw_sha3_256(dut, msg: bytes):
    """Pad msg, load into HW, run permutation, return 32-byte digest."""
    padded = sha3_256_pad(msg)
    lanes  = block_to_lanes(padded)

    await apb_wr(dut, CTRL, SHA3_RESET)   # clear state
    for i, lane in enumerate(lanes):
        base = 0x004 + i * 8
        await apb_wr(dut, base,       lane & 0xFFFFFFFF)   # LO
        await apb_wr(dut, base + 4,   (lane >> 32) & 0xFFFFFFFF)  # HI

    await apb_wr(dut, CTRL, SHA3_START)
    await wait_done(dut)

    # Read 256-bit output: 4 × 64-bit lanes at 0x090–0x0AC
    digest_bytes = bytearray(32)
    for j in range(4):
        base = 0x090 + j * 8
        lo = await apb_rd(dut, base)
        hi = await apb_rd(dut, base + 4)
        lane = lo | (hi << 32)
        struct.pack_into('<Q', digest_bytes, j * 8, lane)
    return bytes(digest_bytes)


def ref_sha3_256(msg: bytes) -> bytes:
    import hashlib
    return hashlib.sha3_256(msg).digest()


# ── Test 1: SHA3-256("") ──────────────────────────────────────────────────
@cocotb.test()
async def test_empty_message(dut):
    """SHA3-256 of empty message matches hashlib reference."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    got = await hw_sha3_256(dut, b"")
    ref = ref_sha3_256(b"")
    assert got == ref, f"empty: expected {ref.hex()}, got {got.hex()}"


# ── Test 2: SHA3-256("abc") ───────────────────────────────────────────────
@cocotb.test()
async def test_abc(dut):
    """SHA3-256("abc") NIST KAT vector."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    got = await hw_sha3_256(dut, b"abc")
    ref = ref_sha3_256(b"abc")
    assert got == ref, f"abc: expected {ref.hex()}, got {got.hex()}"


# ── Test 3: SHA3-256("abcdbcdecdef…") ────────────────────────────────────
@cocotb.test()
async def test_nist_448bit_msg(dut):
    """SHA3-256 of 28-byte message matches hashlib."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    msg = b"abcdbcdecdefdefgefghfghighi"
    got = await hw_sha3_256(dut, msg)
    ref = ref_sha3_256(msg)
    assert got == ref, f"28-byte: expected {ref.hex()}, got {got.hex()}"


# ── Test 4: random 64-byte message ───────────────────────────────────────
@cocotb.test()
async def test_random_64bytes(dut):
    """SHA3-256 of 64 random bytes matches hashlib."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    import random
    rng = random.Random(0xDEADC0DE)
    msg = bytes([rng.randint(0, 255) for _ in range(64)])
    got = await hw_sha3_256(dut, msg)
    ref = ref_sha3_256(msg)
    assert got == ref, f"64-byte: expected {ref.hex()}, got {got.hex()}"


# ── Test 5: reset between two runs ───────────────────────────────────────
@cocotb.test()
async def test_reset_between_runs(dut):
    """Two consecutive hashes with reset_state between them."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    for msg in [b"hello", b"world"]:
        got = await hw_sha3_256(dut, msg)
        ref = ref_sha3_256(msg)
        assert got == ref, f"msg={msg}: expected {ref.hex()}, got {got.hex()}"


# ── Test 6: 100-byte message ──────────────────────────────────────────────
@cocotb.test()
async def test_100bytes(dut):
    """SHA3-256 of 100-byte message (still fits in rate=136 bytes)."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    msg = bytes(range(100))
    got = await hw_sha3_256(dut, msg)
    ref = ref_sha3_256(msg)
    assert got == ref, f"100-byte: expected {ref.hex()}, got {got.hex()}"
