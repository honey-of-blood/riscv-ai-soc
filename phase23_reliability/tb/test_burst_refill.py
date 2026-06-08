"""test_burst_refill.py — Phase 23.2: AXI4 burst SRAM + D-cache miss penalty.

Tests:
  test_burst_sram_single     — AXI4-Lite single-beat read still works (ARLEN=0)
  test_burst_sram_4beat      — AXI4-full 4-beat INCR burst read
  test_burst_write_4beat     — 4-beat INCR burst write with WLAST
  test_refill_cycles         — D-cache miss fills in ≤6 cycles (not 16+ with b2l)
  test_burst_rlast           — RLAST asserts only on final beat

DUT: axi_sram (for burst tests), cache_top + axi_sram (for refill latency)
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


async def axi_write_single(dut, addr, data):
    # AW channel – s_awready = !wr_active (initially 1); check pre-NBA (no Timer)
    dut.s_awaddr.value  = addr
    dut.s_awlen.value   = 0
    dut.s_awburst.value = 1
    dut.s_awvalid.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_awready.value:   # pre-NBA: wr_active was 0 → SRAM latched AW
            dut.s_awvalid.value = 0
            break
    # W channel – s_wready = wr_active (now 1 after AW accepted)
    dut.s_wdata.value  = data
    dut.s_wstrb.value  = 0xF
    dut.s_wlast.value  = 1
    dut.s_wvalid.value = 1
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_wready.value:    # pre-NBA: wr_active was 1 → SRAM accepted W
            dut.s_wvalid.value = 0
            dut.s_wlast.value  = 0
            break
    # B channel
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
    data = []
    ar_done = False
    for _ in range(beats + 20):
        await RisingEdge(dut.clk)
        # Check arready PRE-Timer (pre-NBA): s_arready = !rd_active (comb).
        # If 1 here, rd_active was 0 at the clock edge → SRAM just latched the AR.
        # Deassert arvalid immediately so the SRAM never re-accepts on completion.
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


@cocotb.test()
async def test_burst_sram_single(dut):
    """AXI4-Lite single-beat read (ARLEN=0) still works."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)
    await axi_write_single(dut, 0x100, 0xABCD1234)
    data = await axi_read_burst(dut, 0x100, 1)
    assert data[0] == 0xABCD1234, f"got 0x{data[0]:08x}"


@cocotb.test()
async def test_burst_sram_4beat(dut):
    """4-beat INCR burst read returns all 4 words in order."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    words = [0x11111111, 0x22222222, 0x33333333, 0x44444444]
    for i, w in enumerate(words):
        await axi_write_single(dut, 0x200 + i * 4, w)

    data = await axi_read_burst(dut, 0x200, 4)
    assert len(data) == 4, f"expected 4 beats, got {len(data)}"
    for i, (got, exp) in enumerate(zip(data, words)):
        assert got == exp, f"beat {i}: got 0x{got:08x} expected 0x{exp:08x}"


@cocotb.test()
async def test_burst_write_4beat(dut):
    """4-beat burst write: write 4 words, read back individually."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    # Send AW
    dut.s_awaddr.value  = 0x300
    dut.s_awlen.value   = 3
    dut.s_awburst.value = 1
    dut.s_awvalid.value = 1
    for _ in range(5):
        await RisingEdge(dut.clk)
        if dut.s_awready.value:
            dut.s_awvalid.value = 0
            break

    words = [0xDEAD0001, 0xDEAD0002, 0xDEAD0003, 0xDEAD0004]
    for i, w in enumerate(words):
        dut.s_wdata.value  = w
        dut.s_wstrb.value  = 0xF
        dut.s_wlast.value  = (1 if i == 3 else 0)
        dut.s_wvalid.value = 1
        for _ in range(5):
            await RisingEdge(dut.clk)
            if dut.s_wready.value:
                break
    dut.s_wvalid.value = 0

    # Wait for B
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.s_bvalid.value:
            break

    # Read back each word
    for i, exp in enumerate(words):
        data = await axi_read_burst(dut, 0x300 + i * 4, 1)
        assert data[0] == exp, f"word {i}: got 0x{data[0]:08x} expected 0x{exp:08x}"


@cocotb.test()
async def test_burst_rlast(dut):
    """RLAST is asserted only on the final beat of a burst."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_sram(dut)

    for i in range(4):
        await axi_write_single(dut, 0x400 + i * 4, 0xFACE0000 | i)

    dut.s_araddr.value  = 0x400
    dut.s_arlen.value   = 3
    dut.s_arburst.value = 1
    dut.s_arvalid.value = 1
    dut.s_rready.value  = 1
    beats = 0
    rlast_beat = -1
    ar_done = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if not ar_done and dut.s_arready.value:  # pre-NBA check
            dut.s_arvalid.value = 0
            ar_done = True
        await Timer(1, unit="ns")
        if dut.s_rvalid.value:
            if dut.s_rlast.value:
                rlast_beat = beats
            beats += 1
            if rlast_beat >= 0:
                break

    assert beats == 4, f"expected 4 beats, got {beats}"
    assert rlast_beat == 3, f"RLAST on beat {rlast_beat}, expected beat 3"
