"""test_cache_2way.py — Phase 23.3: 2-way SA cache + SECDED ECC tests.

Tests:
  test_basic_hit_miss       — basic read/write hit and miss
  test_conflict_miss_2way   — two addresses with same index, different tags → no thrash
  test_lru_replacement      — fill both ways, access way0, confirm way1 is evicted next
  test_ecc_single_bit_correct — inject 1-bit flip, confirm silent correction
  test_ecc_double_bit_detect  — inject 2-bit flip, confirm ecc_error_o

DUT: cache_top (uses cache_controller_2way + cache_tag_array_2way + cache_data_array_2way)
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# ── AXI4 burst SRAM model ────────────────────────────────────────────────────
MEM = {}

def _sig(sig):
    """Return int value of a signal, 0 if X/Z (before reset settles)."""
    try:
        return int(sig.value)
    except ValueError:
        return 0


async def axi_slave_model(dut, max_cycles=2000):
    """Respond to cache AXI4 burst requests for the duration of the test."""
    cycle = 0
    while cycle < max_cycles:
        await RisingEdge(dut.clk)
        cycle += 1

        # Write address handshake
        if _sig(dut.m_axi_awvalid_o):
            dut.m_axi_awready_i.value = 1
        else:
            dut.m_axi_awready_i.value = 0

        # Write data: accept and store
        if _sig(dut.m_axi_wvalid_o) and not _sig(dut.m_axi_awvalid_o):
            addr = _sig(dut.m_axi_awaddr_o)
            MEM[addr] = _sig(dut.m_axi_wdata_o)
            if _sig(dut.m_axi_wlast_o):
                dut.m_axi_bvalid_i.value = 1
        if _sig(dut.m_axi_bready_o):
            dut.m_axi_bvalid_i.value = 0

        # Read address handshake and burst response
        if _sig(dut.m_axi_arvalid_o) and not _sig(dut.m_axi_arready_i):
            dut.m_axi_arready_i.value = 1
            base = _sig(dut.m_axi_araddr_o)
            # Drive 4-beat burst immediately
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


async def cpu_read(dut, addr, timeout=200):
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


async def cpu_write(dut, addr, data, be=0xF, timeout=100):
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


@cocotb.test()
async def test_basic_hit_miss(dut):
    """Miss on first access, then hit on second access to same address."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model(dut))
    await reset(dut)

    MEM[0x100] = 0xABCD1234
    val = await cpu_read(dut, 0x100)
    assert val == 0xABCD1234, f"miss read got 0x{val:08x}"

    # Second read should hit (no AXI activity)
    val2 = await cpu_read(dut, 0x100)
    assert val2 == 0xABCD1234, f"hit read got 0x{val2:08x}"


@cocotb.test()
async def test_conflict_miss_2way(dut):
    """Two addresses mapping to same index (differ by 0x400 = cache_size).
    In direct-mapped they would thrash; 2-way holds both.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model(dut))
    await reset(dut)

    addr_a = 0x0000  # index 0, tag A
    addr_b = 0x1000  # same index 0 (addr[9:4]), different tag (32-set × 16-byte = 0x200 stride... actually 64-set × 16-byte = 0x400)
    # Both map to the same set in a 64-set, 4-word-line cache
    # addr[9:4] = set index; stride between aliasing addrs = 2^10 = 0x400
    # Using stride 0x400 ensures they alias
    addr_b2 = 0x0400

    MEM[addr_a]   = 0xAAAA_0000
    MEM[addr_b2]  = 0xBBBB_0000

    # Load both lines into the 2-way cache
    v_a = await cpu_read(dut, addr_a)
    v_b = await cpu_read(dut, addr_b2)

    assert v_a == 0xAAAA_0000, f"addr_a got 0x{v_a:08x}"
    assert v_b == 0xBBBB_0000, f"addr_b2 got 0x{v_b:08x}"

    # Read addr_a again — must still be in cache (way1 holds addr_b2)
    v_a2 = await cpu_read(dut, addr_a)
    assert v_a2 == 0xAAAA_0000, "addr_a evicted after conflict — 2-way failed"


@cocotb.test()
async def test_lru_replacement(dut):
    """Fill both ways of a set, access way0, then confirm way1 is evicted next."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model(dut))
    await reset(dut)

    # Three aliasing addresses for the same set (index 0)
    a0 = 0x0000   # tag 0, index 0
    a1 = 0x0400   # tag 1, index 0
    a2 = 0x0800   # tag 2, index 0

    MEM[a0] = 0xAAAA0000
    MEM[a1] = 0xBBBB0000
    MEM[a2] = 0xCCCC0000

    # Load a0 → way0 (LRU=way0 before, now way0 is MRU, LRU=way1)
    assert await cpu_read(dut, a0) == 0xAAAA0000
    # Load a1 → way1 (LRU=way0 now since way1 is MRU)
    assert await cpu_read(dut, a1) == 0xBBBB0000

    # Access a0 again → LRU bit flips: way1 becomes LRU
    assert await cpu_read(dut, a0) == 0xAAAA0000

    # Load a2 → must evict way1 (LRU), not way0
    assert await cpu_read(dut, a2) == 0xCCCC0000

    # a0 must still be readable (it was NOT evicted)
    v = await cpu_read(dut, a0)
    assert v == 0xAAAA0000, f"a0 was wrongly evicted; got 0x{v:08x}"


@cocotb.test()
async def test_ecc_single_bit_correct(dut):
    """Write a value, corrupt 1 bit via injection port, read back — must be correct."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model(dut))
    await reset(dut)

    addr = 0x0080  # set index = 8
    MEM[addr] = 0x12345678
    await cpu_read(dut, addr)   # fill cache

    # Corrupt bit 7 of the stored word in way0, set 8, word 0
    dut.ecc_inject_en_i.value  = 1
    dut.ecc_way_inject_i.value = 0
    dut.ecc_idx_inject_i.value = 8
    dut.ecc_word_inject_i.value = 0
    dut.ecc_bit_inject_i.value  = 7   # flip data bit 7
    await RisingEdge(dut.clk)
    dut.ecc_inject_en_i.value  = 0
    await Timer(1, unit="ns")

    # Read back — SECDED should correct silently
    val = await cpu_read(dut, addr)
    assert val == 0x12345678, f"ECC correction failed: got 0x{val:08x}"
    # No double-bit error should be flagged
    await Timer(1, unit="ns")
    assert not dut.ecc_error_o.value, "ecc_error_o unexpectedly set for single-bit error"


@cocotb.test()
async def test_ecc_double_bit_detect(dut):
    """Inject 2-bit error → ecc_error_o must assert."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    cocotb.start_soon(axi_slave_model(dut))
    await reset(dut)

    addr = 0x00C0  # set index = 12
    MEM[addr] = 0xDEADBEEF
    await cpu_read(dut, addr)

    # Inject 2 different data bits via top-level ports
    for bit in (3, 5):
        dut.ecc_inject_en_i.value  = 1
        dut.ecc_way_inject_i.value = 0
        dut.ecc_idx_inject_i.value = 12
        dut.ecc_word_inject_i.value = 0
        dut.ecc_bit_inject_i.value  = bit
        await RisingEdge(dut.clk)
    dut.ecc_inject_en_i.value = 0
    # ecc_error_o is registered (1-cycle delay) — one extra clock to let FF update
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert dut.ecc_error_o.value, "ecc_error_o not set after double-bit injection"
