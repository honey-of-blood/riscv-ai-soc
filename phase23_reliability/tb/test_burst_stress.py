"""test_burst_stress.py — Phase 23 aggressive AXI4 burst SRAM stress tests.

Tests:
  test_byte_strobes         — all 15 non-zero strobe patterns, only written bytes change
  test_back_to_back_bursts  — two burst writes then two burst reads, data intact
  test_write_read_hazard    — write then immediately read same address
  test_data_patterns        — corner values: all-0, all-1, alternating 0xAA, 0x55
  test_overwrite_same_addr  — three sequential writes to same addr, last one wins

DUT: axi_sram
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


async def reset_sram(dut):
    dut.rst_n.value = 0
    dut.s_awvalid.value = 0
    dut.s_wvalid.value  = 0
    dut.s_bready.value  = 1
    dut.s_arvalid.value = 0
    dut.s_rready.value  = 1
    dut.s_awlen.value   = 0
    dut.s_awburst.value = 1
    dut.s_arlen.value   = 0
    dut.s_arburst.value = 1
    dut.s_wstrb.value   = 0xF
    dut.s_wlast.value   = 1
    await Timer(20, unit="ns")
    dut.rst_n.value = 1
    await Timer(10, unit="ns")


async def axi_write_strobe(dut, addr, data, strobe=0xF):
    """Single-beat AXI write with explicit byte strobe."""
    dut.s_awaddr.value  = addr
    dut.s_awlen.value   = 0
    dut.s_awburst.value = 1
    dut.s_awvalid.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_awready.value:
            dut.s_awvalid.value = 0
            break
    dut.s_wdata.value  = data
    dut.s_wstrb.value  = strobe
    dut.s_wlast.value  = 1
    dut.s_wvalid.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_wready.value:
            dut.s_wvalid.value = 0
            dut.s_wlast.value  = 0
            break
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_bvalid.value:
            break


async def axi_read_burst(dut, addr, beats):
    dut.s_araddr.value  = addr
    dut.s_arlen.value   = beats - 1
    dut.s_arburst.value = 1
    dut.s_arvalid.value = 1
    dut.s_rready.value  = 1
    data   = []
    ar_done = False
    for _ in range(beats + 30):
        await RisingEdge(dut.clk)
        if not ar_done and dut.s_arready.value:
            dut.s_arvalid.value = 0
            ar_done = True
        await Timer(1, unit="ns")
        if dut.s_rvalid.value:
            data.append(int(dut.s_rdata.value))
            if dut.s_rlast.value:
                break
    assert data, "RLAST never asserted"
    return data


async def burst_write_4(dut, base_addr, words):
    """4-beat INCR burst write; words must have exactly 4 elements."""
    dut.s_awaddr.value  = base_addr
    dut.s_awlen.value   = 3
    dut.s_awburst.value = 1
    dut.s_awvalid.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_awready.value:
            dut.s_awvalid.value = 0
            break
    for i, w in enumerate(words):
        dut.s_wdata.value  = w
        dut.s_wstrb.value  = 0xF
        dut.s_wlast.value  = 1 if i == 3 else 0
        dut.s_wvalid.value = 1
        for _ in range(10):
            await RisingEdge(dut.clk)
            if dut.s_wready.value:
                break
    dut.s_wvalid.value = 0
    dut.s_wlast.value  = 0
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_bvalid.value:
            break


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_byte_strobes(dut):
    """All 15 non-zero strobe patterns: written bytes hold new value, rest stay zero."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    base = 0x1000
    for strobe in range(1, 16):
        addr = base + strobe * 0x10  # distinct address per strobe pattern

        # Ensure location is 0x00000000 (write with full strobe first)
        await axi_write_strobe(dut, addr, 0x00000000, 0xF)
        # Now write 0xFFFFFFFF with the partial strobe
        await axi_write_strobe(dut, addr, 0xFFFFFFFF, strobe)

        data = await axi_read_burst(dut, addr, 1)
        expected = sum((0xFF << (b * 8)) for b in range(4) if strobe & (1 << b))
        assert data[0] == expected, \
            f"strobe=0x{strobe:X}: got 0x{data[0]:08x} exp 0x{expected:08x}"


@cocotb.test()
async def test_back_to_back_bursts(dut):
    """Two consecutive 4-beat burst writes followed by two 4-beat burst reads."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    words1 = [0xA100_0000 | i for i in range(4)]
    words2 = [0xA200_0000 | i for i in range(4)]

    await burst_write_4(dut, 0x2000, words1)
    await burst_write_4(dut, 0x2010, words2)

    data1 = await axi_read_burst(dut, 0x2000, 4)
    data2 = await axi_read_burst(dut, 0x2010, 4)

    for i, (got, exp) in enumerate(zip(data1, words1)):
        assert got == exp, f"burst1 beat{i}: got 0x{got:08x} exp 0x{exp:08x}"
    for i, (got, exp) in enumerate(zip(data2, words2)):
        assert got == exp, f"burst2 beat{i}: got 0x{got:08x} exp 0x{exp:08x}"


@cocotb.test()
async def test_write_read_hazard(dut):
    """Write then immediately read the same address — must return the written value."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    await axi_write_strobe(dut, 0x3000, 0x1234_5678)
    data = await axi_read_burst(dut, 0x3000, 1)
    assert data[0] == 0x1234_5678, f"hazard: got 0x{data[0]:08x}"

    # Repeat at a second address to confirm it's not a coincidence
    await axi_write_strobe(dut, 0x3004, 0xDEAD_BEEF)
    data = await axi_read_burst(dut, 0x3004, 1)
    assert data[0] == 0xDEAD_BEEF, f"hazard2: got 0x{data[0]:08x}"


@cocotb.test()
async def test_data_patterns(dut):
    """Corner data patterns: all-0, all-1, 0xAAAAAAAA, 0x55555555."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    patterns = [0x0000_0000, 0xFFFF_FFFF, 0xAAAA_AAAA, 0x5555_5555]
    for i, pat in enumerate(patterns):
        await axi_write_strobe(dut, 0x4000 + i * 4, pat)

    for i, pat in enumerate(patterns):
        data = await axi_read_burst(dut, 0x4000 + i * 4, 1)
        assert data[0] == pat, f"pattern 0x{pat:08x}: got 0x{data[0]:08x}"

    # Also verify as a 4-beat burst read
    data = await axi_read_burst(dut, 0x4000, 4)
    for i, (got, exp) in enumerate(zip(data, patterns)):
        assert got == exp, f"burst pattern beat{i}: got 0x{got:08x} exp 0x{exp:08x}"


@cocotb.test()
async def test_overwrite_same_addr(dut):
    """Three sequential writes to the same address — latest write wins."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    await axi_write_strobe(dut, 0x5000, 0x1111_1111)
    await axi_write_strobe(dut, 0x5000, 0x2222_2222)
    await axi_write_strobe(dut, 0x5000, 0x3333_3333)

    data = await axi_read_burst(dut, 0x5000, 1)
    assert data[0] == 0x3333_3333, f"overwrite: got 0x{data[0]:08x}"
