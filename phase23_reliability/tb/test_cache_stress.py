"""test_cache_stress.py — Phase 23 aggressive cache stress tests.

Tests:
  test_all_word_offsets       — hit/miss on all 4 word offsets within a line
  test_write_hit_all_offsets  — write hit at each word offset, read back
  test_byte_enable_partial    — partial byte-enable writes merge correctly
  test_all_64_sets            — fill and read back every one of the 64 sets
  test_dirty_writeback        — write-hit then force eviction, verify MEM updated
  test_lru_stress             — repeated LRU evictions across 5 sets
  test_ecc_all_data_bits      — single-bit at each of 32 data positions → no dbl_err
  test_ecc_all_parity_bits    — single-bit at each of 7 parity positions → no dbl_err
  test_ecc_way1_double        — double-bit injection in way1 → ecc_error_o asserts
  test_ecc_words_1_2_3        — double-bit in each of words 1, 2, 3 → ecc_error_o

Address map: addr[31:10]=tag  addr[9:4]=index(64 sets)  addr[3:2]=word-offset
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

MEM = {}


def _sig(sig):
    try:
        return int(sig.value)
    except ValueError:
        return 0


def apply_be(old, new_data, be):
    """Merge new_data into old using byte-enable mask."""
    result = 0
    for i in range(4):
        if be & (1 << i):
            result |= ((new_data >> (8 * i)) & 0xFF) << (8 * i)
        else:
            result |= ((old >> (8 * i)) & 0xFF) << (8 * i)
    return result


# ── AXI4 slave — burst-write-aware ───────────────────────────────────────────

async def axi_slave_model_wb(dut, max_cycles=6000):
    """AXI4 slave with per-beat burst write address tracking."""
    cycle   = 0
    aw_base = None
    w_beat  = 0
    b_valid = False   # True = need to assert bvalid next cycle

    while cycle < max_cycles:
        await RisingEdge(dut.clk)
        cycle += 1

        # Write address handshake: capture base addr once
        if _sig(dut.m_axi_awvalid_o):
            dut.m_axi_awready_i.value = 1
            if aw_base is None:
                aw_base = _sig(dut.m_axi_awaddr_o)
                w_beat  = 0
        else:
            dut.m_axi_awready_i.value = 0

        # B channel: assert BEFORE W check so b_valid is False on wlast cycle
        if b_valid:
            dut.m_axi_bvalid_i.value = 1
            b_valid = False
        elif _sig(dut.m_axi_bready_o) and _sig(dut.m_axi_bvalid_i):
            dut.m_axi_bvalid_i.value = 0

        # Write data — wready always asserted; track beat address
        if _sig(dut.m_axi_wvalid_o) and aw_base is not None:
            MEM[aw_base + w_beat * 4] = _sig(dut.m_axi_wdata_o)
            w_beat += 1
            if _sig(dut.m_axi_wlast_o):
                b_valid = True   # assert bvalid on NEXT cycle
                aw_base = None

        # Read address handshake and 4-beat burst response
        if _sig(dut.m_axi_arvalid_o) and not _sig(dut.m_axi_arready_i):
            dut.m_axi_arready_i.value = 1
            base = _sig(dut.m_axi_araddr_o)
            for beat in range(4):
                addr = base + beat * 4
                dut.m_axi_rdata_i.value  = MEM.get(addr, 0xDEAD0000 | beat)
                dut.m_axi_rvalid_i.value = 1
                dut.m_axi_rlast_i.value  = (beat == 3)
                await RisingEdge(dut.clk)
                while not _sig(dut.m_axi_rready_o):
                    await RisingEdge(dut.clk)
            dut.m_axi_rvalid_i.value = 0
            dut.m_axi_rlast_i.value  = 0
            dut.m_axi_arready_i.value = 0


# ── Helpers ───────────────────────────────────────────────────────────────────

async def reset(dut):
    dut.rst.value = 1
    dut.cpu_re_i.value = 0
    dut.cpu_we_i.value = 0
    dut.cpu_addr_i.value = 0
    dut.cpu_wdata_i.value = 0
    dut.cpu_be_i.value = 0
    dut.m_axi_awready_i.value = 0
    dut.m_axi_wready_i.value  = 1
    dut.m_axi_bvalid_i.value  = 0
    dut.m_axi_arready_i.value = 0
    dut.m_axi_rvalid_i.value  = 0
    dut.m_axi_rdata_i.value   = 0
    dut.m_axi_rlast_i.value   = 0
    dut.ecc_inject_en_i.value  = 0
    dut.ecc_way_inject_i.value = 0
    dut.ecc_idx_inject_i.value = 0
    dut.ecc_word_inject_i.value = 0
    dut.ecc_bit_inject_i.value  = 0
    await Timer(20, unit="ns")
    dut.rst.value = 0
    await Timer(10, unit="ns")


async def cpu_read(dut, addr, timeout=300):
    dut.cpu_addr_i.value = addr
    dut.cpu_re_i.value = 1
    dut.cpu_we_i.value = 0
    await Timer(1, unit="ns")
    for _ in range(timeout):
        if not dut.cpu_stall_o.value:
            rdata = int(dut.cpu_rdata_o.value)
            await RisingEdge(dut.clk)
            dut.cpu_re_i.value = 0
            return rdata
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
    raise RuntimeError(f"cpu_read timeout addr=0x{addr:08x}")


async def cpu_write(dut, addr, data, be=0xF, timeout=200):
    dut.cpu_addr_i.value  = addr
    dut.cpu_wdata_i.value = data
    dut.cpu_be_i.value    = be
    dut.cpu_we_i.value    = 1
    dut.cpu_re_i.value    = 0
    await Timer(1, unit="ns")
    for _ in range(timeout):
        if not dut.cpu_stall_o.value:
            await RisingEdge(dut.clk)
            dut.cpu_we_i.value = 0
            return
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
    raise RuntimeError(f"cpu_write timeout addr=0x{addr:08x}")


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_all_word_offsets(dut):
    """Fill one cache line, then hit-read all 4 word offsets."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut))
    await reset(dut)

    # Line at index 1, tag 0: addresses 0x0010..0x001C
    for woff in range(4):
        MEM[0x0010 + woff * 4] = 0x1000_0000 | (woff << 4) | woff

    # First read triggers a fill (all 4 words loaded)
    v = await cpu_read(dut, 0x0010)
    assert v == MEM[0x0010], f"woff0 miss: 0x{v:08x}"

    # Subsequent reads should hit
    for woff in range(1, 4):
        addr = 0x0010 + woff * 4
        v = await cpu_read(dut, addr)
        assert v == MEM[addr], f"woff{woff}: got 0x{v:08x} exp 0x{MEM[addr]:08x}"


@cocotb.test()
async def test_write_hit_all_offsets(dut):
    """Write-hit at each word offset, then read back each written value."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut))
    await reset(dut)

    # Fill line at index 2 (addr 0x0020..0x002C)
    for woff in range(4):
        MEM[0x0020 + woff * 4] = 0xBEEF_0000 | woff
    await cpu_read(dut, 0x0020)  # fill

    writes = [0xDEAD_0000, 0xCAFE_0001, 0xFACE_0002, 0xBABE_0003]
    for woff in range(4):
        await cpu_write(dut, 0x0020 + woff * 4, writes[woff])

    for woff in range(4):
        addr = 0x0020 + woff * 4
        v = await cpu_read(dut, addr)
        assert v == writes[woff], f"woff{woff}: got 0x{v:08x} exp 0x{writes[woff]:08x}"


@cocotb.test()
async def test_byte_enable_partial(dut):
    """Partial byte-enable writes preserve unmasked bytes."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut))
    await reset(dut)

    # Fill line at index 3 (addr 0x0030)
    for woff in range(4):
        MEM[0x0030 + woff * 4] = 0xFF << (woff * 8)
    await cpu_read(dut, 0x0030)  # fill

    # be=0x3: write bytes 0 and 1 of word 0
    old0 = MEM[0x0030]
    await cpu_write(dut, 0x0030, 0x11223344, be=0x3)
    v = await cpu_read(dut, 0x0030)
    assert v == apply_be(old0, 0x11223344, 0x3), \
        f"be=0x3: got 0x{v:08x} exp 0x{apply_be(old0, 0x11223344, 0x3):08x}"

    # be=0xC: write bytes 2 and 3 of word 1
    old1 = MEM[0x0034]
    await cpu_write(dut, 0x0034, 0xAABBCCDD, be=0xC)
    v = await cpu_read(dut, 0x0034)
    assert v == apply_be(old1, 0xAABBCCDD, 0xC), \
        f"be=0xC: got 0x{v:08x} exp 0x{apply_be(old1, 0xAABBCCDD, 0xC):08x}"

    # be=0x5: write bytes 0 and 2 of word 2
    old2 = MEM[0x0038]
    await cpu_write(dut, 0x0038, 0x12345678, be=0x5)
    v = await cpu_read(dut, 0x0038)
    assert v == apply_be(old2, 0x12345678, 0x5), \
        f"be=0x5: got 0x{v:08x} exp 0x{apply_be(old2, 0x12345678, 0x5):08x}"


@cocotb.test()
async def test_all_64_sets(dut):
    """Fill and read back all 64 cache sets — cold miss then cache hit."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut, max_cycles=8000))
    await reset(dut)

    for idx in range(64):
        MEM[idx * 0x10] = 0xA000_0000 | idx

    # 64 cold misses
    for idx in range(64):
        v = await cpu_read(dut, idx * 0x10)
        assert v == (0xA000_0000 | idx), f"set{idx} miss: 0x{v:08x}"

    # 64 hits (no AXI traffic)
    for idx in range(64):
        v = await cpu_read(dut, idx * 0x10)
        assert v == (0xA000_0000 | idx), f"set{idx} hit: 0x{v:08x}"


@cocotb.test()
async def test_dirty_writeback(dut):
    """Write-hit to a line, force dirty eviction, verify write-back data in MEM."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut))
    await reset(dut)

    # Four aliasing addresses — same index 0, four different tags
    a0 = 0x0000   # tag 0, index 0
    a1 = 0x0400   # tag 1, index 0
    a2 = 0x0800   # tag 2, index 0
    a3 = 0x0C00   # tag 3, index 0

    for i in range(4):
        MEM[a0 + i * 4] = 0xA0 + i
        MEM[a1 + i * 4] = 0xB0 + i
        MEM[a2 + i * 4] = 0xC0 + i
        MEM[a3 + i * 4] = 0xD0 + i

    WRITTEN = 0xDEAD_BEEF

    # Step 1: fill way0 with a0 → lru=way1
    assert await cpu_read(dut, a0) == 0xA0
    # Step 2: fill way1 with a1 → lru=way0
    assert await cpu_read(dut, a1) == 0xB0
    # Step 3: write-hit to a0 (way0) → way0 dirty, lru=way1
    await cpu_write(dut, a0, WRITTEN)
    # Step 4: fill a2 → evicts lru=way1 (a1, clean, no WB) → lru=way0
    assert await cpu_read(dut, a2) == 0xC0
    # Step 5: fill a3 → evicts lru=way0 (a0, DIRTY) → WRITE_BACK then FILL
    await cpu_read(dut, a3)

    # Write-back must have written WRITTEN to MEM[a0] (word 0 of evicted line)
    assert MEM.get(a0)      == WRITTEN, \
        f"WB word0: got 0x{MEM.get(a0, 0):08x}, exp 0x{WRITTEN:08x}"
    # Words 1–3 are unchanged from original fill
    assert MEM.get(a0 + 4)  == 0xA1, f"WB word1: 0x{MEM.get(a0+4,0):08x}"
    assert MEM.get(a0 + 8)  == 0xA2, f"WB word2: 0x{MEM.get(a0+8,0):08x}"
    assert MEM.get(a0 + 12) == 0xA3, f"WB word3: 0x{MEM.get(a0+12,0):08x}"


@cocotb.test()
async def test_lru_stress(dut):
    """Repeated LRU evictions across 5 sets — verify no incorrect evictions."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut, max_cycles=4000))
    await reset(dut)

    for s in range(5):
        base = s * 0x10
        for t in range(3):
            for woff in range(4):
                MEM[base + t * 0x0400 + woff * 4] = (0x00A0_0000 + t * 0x0010_0000) | (s << 8) | woff

    for s in range(5):
        base = s * 0x10
        a0, a1, a2 = base, base + 0x0400, base + 0x0800

        # a0 miss, a1 miss, a0 hit (makes a1 LRU), a2 miss (evicts a1), a0 still resident
        assert await cpu_read(dut, a0) == MEM[a0], f"set{s} a0 first miss"
        assert await cpu_read(dut, a1) == MEM[a1], f"set{s} a1 miss"
        assert await cpu_read(dut, a0) == MEM[a0], f"set{s} a0 hit"
        assert await cpu_read(dut, a2) == MEM[a2], f"set{s} a2 miss"
        v = await cpu_read(dut, a0)
        assert v == MEM[a0], f"set{s} a0 evicted: 0x{v:08x}"


@cocotb.test()
async def test_ecc_all_data_bits(dut):
    """Single-bit injection at each of bits 0–31 (data positions) — no dbl_err."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut, max_cycles=4000))
    await reset(dut)

    addr = 0x0040  # index = 4
    MEM[addr] = 0xAAAA_AAAA
    await cpu_read(dut, addr)  # fill; req_idx stays at 4 → idx_i = 4

    for bit in range(32):
        # Inject bit B (single flip)
        dut.ecc_inject_en_i.value   = 1
        dut.ecc_way_inject_i.value  = 0
        dut.ecc_idx_inject_i.value  = 4
        dut.ecc_word_inject_i.value = 0
        dut.ecc_bit_inject_i.value  = bit
        await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)   # FF latches decode result
        await Timer(1, unit="ns")
        assert not dut.ecc_error_o.value, \
            f"Spurious dbl_err for data bit {bit} (single flip)"

        # Toggle back (restore to valid codeword)
        dut.ecc_inject_en_i.value  = 1
        dut.ecc_bit_inject_i.value = bit
        await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert not dut.ecc_error_o.value, \
            f"dbl_err persists after restoring data bit {bit}"


@cocotb.test()
async def test_ecc_all_parity_bits(dut):
    """Single-bit injection at each of bits 32–38 (parity positions) — no dbl_err."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut, max_cycles=2000))
    await reset(dut)

    addr = 0x0050  # index = 5
    MEM[addr] = 0x5555_5555
    await cpu_read(dut, addr)  # fill; idx_i stays at 5

    for bit in range(32, 39):   # parity bits p[0..6] stored at positions 32..38
        dut.ecc_inject_en_i.value   = 1
        dut.ecc_way_inject_i.value  = 0
        dut.ecc_idx_inject_i.value  = 5
        dut.ecc_word_inject_i.value = 0
        dut.ecc_bit_inject_i.value  = bit
        await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert not dut.ecc_error_o.value, \
            f"Spurious dbl_err for parity bit {bit} (single flip)"

        # Restore
        dut.ecc_inject_en_i.value  = 1
        dut.ecc_bit_inject_i.value = bit
        await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert not dut.ecc_error_o.value, \
            f"dbl_err after restoring parity bit {bit}"


@cocotb.test()
async def test_ecc_way1_double(dut):
    """Double-bit injection into way1 → ecc_error_o must assert."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut))
    await reset(dut)

    # Fill both ways at index 0
    MEM[0x0000] = 0x1234_5678
    MEM[0x0400] = 0x8765_4321
    await cpu_read(dut, 0x0000)   # fills way0; lru=way1
    await cpu_read(dut, 0x0400)   # fills way1; lru=way0; idx_i stays at 0

    for bit in (1, 4):   # flip 2 bits in way1, set 0, word 0
        dut.ecc_inject_en_i.value   = 1
        dut.ecc_way_inject_i.value  = 1   # way1
        dut.ecc_idx_inject_i.value  = 0
        dut.ecc_word_inject_i.value = 0
        dut.ecc_bit_inject_i.value  = bit
        await RisingEdge(dut.clk)
    dut.ecc_inject_en_i.value = 0
    await RisingEdge(dut.clk)   # FF update
    await Timer(1, unit="ns")
    assert dut.ecc_error_o.value, "ecc_error_o not set for way1 double-bit injection"


@cocotb.test()
async def test_ecc_words_1_2_3(dut):
    """Double-bit injection in each of words 1, 2, 3 → ecc_error_o asserts."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model_wb(dut, max_cycles=3000))
    await reset(dut)

    for woff in range(4):
        MEM[0x0060 + woff * 4] = 0xFEED_0000 | woff
    await cpu_read(dut, 0x0060)   # fill; idx_i = 6

    for word in (1, 2, 3):
        # Inject 2 bits into way0, set 6, word N
        for bit in (0, 2):
            dut.ecc_inject_en_i.value   = 1
            dut.ecc_way_inject_i.value  = 0
            dut.ecc_idx_inject_i.value  = 6
            dut.ecc_word_inject_i.value = word
            dut.ecc_bit_inject_i.value  = bit
            await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert dut.ecc_error_o.value, \
            f"ecc_error_o not set for word {word} double-bit injection"

        # Restore by toggling the same 2 bits back
        for bit in (0, 2):
            dut.ecc_inject_en_i.value   = 1
            dut.ecc_way_inject_i.value  = 0
            dut.ecc_idx_inject_i.value  = 6
            dut.ecc_word_inject_i.value = word
            dut.ecc_bit_inject_i.value  = bit
            await RisingEdge(dut.clk)
        dut.ecc_inject_en_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        # After restoration, error should be gone before next word
        assert not dut.ecc_error_o.value, \
            f"dbl_err persists after restoring word {word}"
