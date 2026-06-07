"""Phase 19 — aes_top cocotb tests.

NIST AES-128 ECB and CBC test vectors (FIPS 197 and SP 800-38A).
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK = 10

# APB offsets
CTRL   = 0x00
KEY    = [0x04 + i*4 for i in range(4)]
IV     = [0x14 + i*4 for i in range(4)]
DIN    = [0x24 + i*4 for i in range(4)]
DOUT   = [0x34 + i*4 for i in range(4)]
STATUS = 0x44

AES_START   = 0x1
AES_DECRYPT = 0x2
AES_ECB     = 0x0   # mode bits [3:2]=00
AES_CBC     = 0x4   # mode bits [3:2]=01
AES_CTR     = 0x8   # mode bits [3:2]=10
AES_DONE    = 0x1


async def reset_dut(dut):
    dut.rst_n.value = 0
    dut.psel.value = dut.penable.value = dut.pwrite.value = 0
    dut.paddr.value = dut.pwdata.value = 0
    await Timer(5 * CLK, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK, unit="ns")


async def apb_wr(dut, addr, data):
    dut.paddr.value = addr; dut.pwdata.value = data & 0xFFFFFFFF
    dut.pwrite.value = 1;  dut.psel.value = 1
    await RisingEdge(dut.clk); dut.penable.value = 1
    await RisingEdge(dut.clk); await Timer(1, unit="ns")
    dut.psel.value = dut.penable.value = dut.pwrite.value = 0


async def apb_rd(dut, addr):
    dut.paddr.value = addr; dut.pwrite.value = 0; dut.psel.value = 1
    await RisingEdge(dut.clk); dut.penable.value = 1
    await RisingEdge(dut.clk); await Timer(1, unit="ns")
    v = int(dut.prdata.value)
    dut.psel.value = dut.penable.value = 0
    return v


async def wait_done(dut, timeout=300):
    for _ in range(timeout):
        await RisingEdge(dut.clk); await Timer(1, unit="ns")
        if (await apb_rd(dut, STATUS)) & AES_DONE: return
    assert False, "aes done timeout"


def hex_to_words(h):
    """16-char hex string → list of 4 big-endian uint32_t words."""
    b = bytes.fromhex(h)
    return [int.from_bytes(b[i:i+4], 'big') for i in range(0, 16, 4)]


def words_to_hex(ws):
    return ''.join(f'{w:08x}' for w in ws)


async def aes_ecb(dut, key_words, din_words, decrypt=False):
    for i, w in enumerate(key_words): await apb_wr(dut, KEY[i], w)
    for i, w in enumerate(din_words): await apb_wr(dut, DIN[i], w)
    ctrl = AES_ECB | (AES_DECRYPT if decrypt else 0) | AES_START
    await apb_wr(dut, CTRL, ctrl)
    await wait_done(dut)
    return [await apb_rd(dut, DOUT[i]) for i in range(4)]


async def aes_cbc_enc(dut, key_words, iv_words, pt_words):
    for i, w in enumerate(key_words): await apb_wr(dut, KEY[i], w)
    for i, w in enumerate(iv_words):  await apb_wr(dut, IV[i],  w)
    for i, w in enumerate(pt_words):  await apb_wr(dut, DIN[i], w)
    await apb_wr(dut, CTRL, AES_CBC | AES_START)
    await wait_done(dut)
    return [await apb_rd(dut, DOUT[i]) for i in range(4)]


async def aes_ctr(dut, key_words, ctr_words, pt_words):
    for i, w in enumerate(key_words): await apb_wr(dut, KEY[i], w)
    for i, w in enumerate(ctr_words): await apb_wr(dut, IV[i],  w)
    for i, w in enumerate(pt_words):  await apb_wr(dut, DIN[i], w)
    await apb_wr(dut, CTRL, AES_CTR | AES_START)
    await wait_done(dut)
    return [await apb_rd(dut, DOUT[i]) for i in range(4)]


# ── Test 1: NIST FIPS 197 Appendix B ECB encrypt ─────────────────────────
@cocotb.test()
async def test_nist_ecb_encrypt(dut):
    """FIPS 197 App. B: AES-128 ECB encrypt."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("2b7e151628aed2a6abf7158809cf4f3c")
    pt  = hex_to_words("3243f6a8885a308d313198a2e0370734")
    ct  = await aes_ecb(dut, key, pt)
    expected = "3925841d02dc09fbdc118597196a0b32"
    assert words_to_hex(ct) == expected, f"ECB enc: got {words_to_hex(ct)}"


# ── Test 2: NIST FIPS 197 ECB decrypt ────────────────────────────────────
@cocotb.test()
async def test_nist_ecb_decrypt(dut):
    """FIPS 197 App. B: AES-128 ECB decrypt (round-trip)."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("2b7e151628aed2a6abf7158809cf4f3c")
    ct  = hex_to_words("3925841d02dc09fbdc118597196a0b32")
    pt  = await aes_ecb(dut, key, ct, decrypt=True)
    expected = "3243f6a8885a308d313198a2e0370734"
    assert words_to_hex(pt) == expected, f"ECB dec: got {words_to_hex(pt)}"


# ── Test 3: ECB encrypt→decrypt round-trip (random key) ──────────────────
@cocotb.test()
async def test_ecb_roundtrip(dut):
    """Encrypt then decrypt returns original plaintext."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("deadbeefcafebabe0123456789abcdef")
    pt  = hex_to_words("00112233445566778899aabbccddeeff")
    ct  = await aes_ecb(dut, key, pt)
    pt2 = await aes_ecb(dut, key, ct, decrypt=True)
    assert words_to_hex(pt2) == words_to_hex(pt), \
        f"round-trip: expected {words_to_hex(pt)}, got {words_to_hex(pt2)}"


# ── Test 4: NIST SP 800-38A CBC encrypt (F.2.1) ──────────────────────────
@cocotb.test()
async def test_nist_cbc_encrypt(dut):
    """SP 800-38A F.2.1: AES-128 CBC encrypt, block 1."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("2b7e151628aed2a6abf7158809cf4f3c")
    iv  = hex_to_words("000102030405060708090a0b0c0d0e0f")
    pt  = hex_to_words("6bc1bee22e409f96e93d7e117393172a")
    ct  = await aes_cbc_enc(dut, key, iv, pt)
    expected = "7649abac8119b246cee98e9b12e9197d"
    assert words_to_hex(ct) == expected, f"CBC enc: got {words_to_hex(ct)}"


# ── Test 5: CBC block 2 (chained IV from block 1 output) ─────────────────
@cocotb.test()
async def test_nist_cbc_encrypt_block2(dut):
    """SP 800-38A F.2.1: block 2 uses ciphertext of block 1 as IV."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("2b7e151628aed2a6abf7158809cf4f3c")
    iv  = hex_to_words("000102030405060708090a0b0c0d0e0f")
    pt1 = hex_to_words("6bc1bee22e409f96e93d7e117393172a")
    pt2 = hex_to_words("ae2d8a571e03ac9c9eb76fac45af8e51")

    ct1 = await aes_cbc_enc(dut, key, iv, pt1)
    # IV for block 2 is already updated in HW register after block 1
    # Just re-load DIN and start
    for i, w in enumerate(pt2): await apb_wr(dut, DIN[i], w)
    await apb_wr(dut, CTRL, AES_CBC | AES_START)
    await wait_done(dut)
    ct2 = [await apb_rd(dut, DOUT[i]) for i in range(4)]

    from Crypto.Cipher import AES as _AES
    key_b = bytes.fromhex("2b7e151628aed2a6abf7158809cf4f3c")
    iv_b  = bytes.fromhex("000102030405060708090a0b0c0d0e0f")
    pt1_b = bytes.fromhex("6bc1bee22e409f96e93d7e117393172a")
    pt2_b = bytes.fromhex("ae2d8a571e03ac9c9eb76fac45af8e51")
    ref   = _AES.new(key_b, _AES.MODE_CBC, iv=iv_b).encrypt(pt1_b + pt2_b)
    exp_ct1 = ref[:16].hex(); exp_ct2 = ref[16:].hex()
    assert words_to_hex(ct1) == exp_ct1, f"block1: expected {exp_ct1}, got {words_to_hex(ct1)}"
    assert words_to_hex(ct2) == exp_ct2, f"block2: expected {exp_ct2}, got {words_to_hex(ct2)}"


# ── Test 6: CTR keystream XOR ─────────────────────────────────────────────
@cocotb.test()
async def test_ctr_encrypt(dut):
    """AES-128 CTR: SP 800-38A F.5.1 block 1."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    key = hex_to_words("2b7e151628aed2a6abf7158809cf4f3c")
    ctr = hex_to_words("f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff")
    pt  = hex_to_words("6bc1bee22e409f96e93d7e117393172a")
    ct  = await aes_ctr(dut, key, ctr, pt)
    expected = "874d6191b620e3261bef6864990db6ce"
    assert words_to_hex(ct) == expected, f"CTR: got {words_to_hex(ct)}"


# ── Test 7: Zero key, zero plaintext ─────────────────────────────────────
@cocotb.test()
async def test_zero_key_zero_pt(dut):
    """AES-128 ECB with all-zero key on all-zero plaintext."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    from Crypto.Cipher import AES as PAES   # pycryptodome
    key_b = bytes(16); pt_b = bytes(16)
    ref = PAES.new(key_b, PAES.MODE_ECB).encrypt(pt_b)
    ref_words = [int.from_bytes(ref[i:i+4],'big') for i in range(0,16,4)]

    key_words = [0]*4; pt_words = [0]*4
    ct = await aes_ecb(dut, key_words, pt_words)
    assert ct == ref_words, f"zero: expected {words_to_hex(ref_words)}, got {words_to_hex(ct)}"


# ── Test 8: ECB identity (encrypt then decrypt) with multiple keys ────────
@cocotb.test()
async def test_ecb_multiple_keys(dut):
    """Three different key/plaintext pairs: encrypt→decrypt roundtrip."""
    cocotb.start_soon(Clock(dut.clk, CLK, units="ns").start())
    await reset_dut(dut)
    import random
    rng = random.Random(0xC0FFEE)
    for _ in range(3):
        key_b = bytes([rng.randint(0,255) for _ in range(16)])
        pt_b  = bytes([rng.randint(0,255) for _ in range(16)])
        from Crypto.Cipher import AES as PAES
        ct_ref = PAES.new(key_b, PAES.MODE_ECB).encrypt(pt_b)
        key_w = [int.from_bytes(key_b[i:i+4],'big') for i in range(0,16,4)]
        pt_w  = [int.from_bytes(pt_b[i:i+4],'big')  for i in range(0,16,4)]
        ct_w  = await aes_ecb(dut, key_w, pt_w)
        ct_ref_w = [int.from_bytes(ct_ref[i:i+4],'big') for i in range(0,16,4)]
        assert ct_w == ct_ref_w, f"key={key_b.hex()}: expected {words_to_hex(ct_ref_w)}, got {words_to_hex(ct_w)}"
        # Decrypt round-trip
        pt2 = await aes_ecb(dut, key_w, ct_w, decrypt=True)
        assert pt2 == pt_w, "decrypt round-trip failed"
