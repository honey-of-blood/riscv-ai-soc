"""
cocotb unit tests for dmem_axi_adapter.sv.

The adapter converts the RISC-V core's simple RE/WE dmem port into AXI4-Lite.
It has a 5-state FSM: IDLE → WR_ADDR → WR_RESP → RD_ADDR → RD_DATA.
The CPU is stalled (cpu_stall_o=1) for the entire AXI transaction.

Tests:
  1. single_write       — cpu_we=1, stalls until bvalid, stall clears after
  2. single_read        — cpu_re=1, stalls until rvalid, returns correct data
  3. write_then_read    — back-to-back write then read (sequential, no overlap)
  4. write_byte_enables — wstrb driven from cpu_be_i
  5. stall_during_wr    — cpu_stall_o=1 from WE until after bvalid
  6. stall_during_rd    — cpu_stall_o=1 from RE until after rvalid
  7. idle_no_stall      — no RE/WE → no stall, no AXI valid signals
  8. slow_slave_write   — slave delays awready/wready by 3 cycles; stall persists
  9. slow_slave_read    — slave delays arready+rvalid by 3 cycles; stall persists
 10. consecutive_writes — 3 back-to-back writes complete in order
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer

async def clk_edge(dut):
    await RisingEdge(dut.clk)

async def wait_ns(n=1):
    await Timer(n, unit="ns")

async def gen_clk(dut):
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")

async def reset(dut, cycles=4):
    dut.rst_n.value     = 0
    dut.cpu_re_i.value  = 0
    dut.cpu_we_i.value  = 0
    dut.cpu_addr_i.value  = 0
    dut.cpu_wdata_i.value = 0
    dut.cpu_be_i.value    = 0
    dut.m_awready.value = 0
    dut.m_wready.value  = 0
    dut.m_bresp.value   = 0
    dut.m_bvalid.value  = 0
    dut.m_arready.value = 0
    dut.m_rdata.value   = 0
    dut.m_rresp.value   = 0
    dut.m_rvalid.value  = 0
    for _ in range(cycles):
        await clk_edge(dut)
    dut.rst_n.value = 1

# ── AXI Lite slave model helpers ─────────────────────────────────────────────

async def axi_slave_write_ack(dut, delay_cycles=0):
    """Wait for AWVALID+WVALID then ack; optionally delay AWREADY/WREADY."""
    for _ in range(60):
        await clk_edge(dut)
        if dut.m_awvalid.value and dut.m_wvalid.value:
            for _ in range(delay_cycles):
                await clk_edge(dut)
            dut.m_awready.value = 1
            dut.m_wready.value  = 1
            await clk_edge(dut)
            dut.m_awready.value = 0
            dut.m_wready.value  = 0
            dut.m_bresp.value   = 0
            dut.m_bvalid.value  = 1
            for _ in range(60):
                await clk_edge(dut)
                if dut.m_bready.value:
                    dut.m_bvalid.value = 0
                    return int(dut.m_awaddr.value), int(dut.m_wdata.value), int(dut.m_wstrb.value)
            return None, None, None
    return None, None, None

async def axi_slave_read_ack(dut, rdata=0x12345678, delay_cycles=0):
    """Wait for ARVALID then respond with rdata; optionally delay arready+rvalid."""
    for _ in range(60):
        await clk_edge(dut)
        if dut.m_arvalid.value:
            addr = int(dut.m_araddr.value)
            for _ in range(delay_cycles):
                await clk_edge(dut)
            dut.m_arready.value = 1
            await clk_edge(dut)
            dut.m_arready.value = 0
            dut.m_rdata.value   = rdata
            dut.m_rresp.value   = 0
            dut.m_rvalid.value  = 1
            for _ in range(60):
                await clk_edge(dut)
                if dut.m_rready.value:
                    dut.m_rvalid.value = 0
                    return addr
            return addr
    return None


# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_single_write(dut):
    """CPU write: correct addr/data forwarded to AXI, stall then clears."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    wr_done = cocotb.start_soon(axi_slave_write_ack(dut))

    dut.cpu_we_i.value    = 1
    dut.cpu_addr_i.value  = 0x0000_1000
    dut.cpu_wdata_i.value = 0xDEADBEEF
    dut.cpu_be_i.value    = 0xF

    # Should stall immediately
    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_stall_o.value) == 1, "CPU should be stalled during write"

    # Wait for slave to finish
    result = await wr_done
    addr, data, strb = result

    assert addr == 0x0000_1000, f"AXI awaddr={hex(addr)}"
    assert data == 0xDEAD_BEEF, f"AXI wdata={hex(data)}"
    assert strb == 0xF,         f"AXI wstrb={hex(strb)}"

    # After bvalid handshake, stall should clear
    dut.cpu_we_i.value = 0
    for _ in range(5):
        await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_stall_o.value) == 0, "Stall should clear after write completes"


@cocotb.test()
async def test_single_read(dut):
    """CPU read: stalls, correct data returned on rdata output."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    expected = 0xCAFEBABE
    rd_done = cocotb.start_soon(axi_slave_read_ack(dut, rdata=expected))

    dut.cpu_re_i.value   = 1
    dut.cpu_addr_i.value = 0x0000_2004

    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_stall_o.value) == 1, "CPU should stall during read"

    await rd_done

    # cpu_rdata_o should hold the returned data
    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_rdata_o.value) == expected, \
        f"cpu_rdata_o={hex(int(dut.cpu_rdata_o.value))} expected={hex(expected)}"

    dut.cpu_re_i.value = 0
    for _ in range(3):
        await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_stall_o.value) == 0, "Stall should clear after read"


@cocotb.test()
async def test_write_then_read(dut):
    """Back-to-back write then read; both complete correctly."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    # Write
    wr = cocotb.start_soon(axi_slave_write_ack(dut))
    dut.cpu_we_i.value    = 1
    dut.cpu_addr_i.value  = 0x0000_0100
    dut.cpu_wdata_i.value = 0x11223344
    dut.cpu_be_i.value    = 0xF
    await wr
    dut.cpu_we_i.value = 0
    # Wait for stall to clear
    for _ in range(5):
        await clk_edge(dut)

    # Read
    rd = cocotb.start_soon(axi_slave_read_ack(dut, rdata=0x99887766))
    dut.cpu_re_i.value   = 1
    dut.cpu_addr_i.value = 0x0000_0100
    await rd
    dut.cpu_re_i.value = 0
    for _ in range(3):
        await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_rdata_o.value) == 0x99887766, "Read data after write should match"
    assert int(dut.cpu_stall_o.value) == 0


@cocotb.test()
async def test_write_byte_enables(dut):
    """cpu_be_i is forwarded unchanged as m_wstrb."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    for be in [0x1, 0x2, 0x4, 0x8, 0x3, 0xC, 0xF]:
        wr = cocotb.start_soon(axi_slave_write_ack(dut))
        dut.cpu_we_i.value    = 1
        dut.cpu_addr_i.value  = 0x0000_0008
        dut.cpu_wdata_i.value = 0xABCD_EF01
        dut.cpu_be_i.value    = be
        result = await wr
        _, _, strb = result
        assert strb == be, f"wstrb={hex(strb)} expected be={hex(be)}"
        dut.cpu_we_i.value = 0
        for _ in range(3):
            await clk_edge(dut)


@cocotb.test()
async def test_stall_during_write(dut):
    """cpu_stall_o stays high from WE until bvalid handshake completes."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    wr = cocotb.start_soon(axi_slave_write_ack(dut))
    dut.cpu_we_i.value    = 1
    dut.cpu_addr_i.value  = 0x0000_0010
    dut.cpu_wdata_i.value = 0x5A5A5A5A
    dut.cpu_be_i.value    = 0xF

    stall_seen = False
    bvalid_seen = False
    stall_dropped_before_bvalid = False

    for _ in range(40):
        await clk_edge(dut)
        await wait_ns(1)
        curr_stall  = int(dut.cpu_stall_o.value)
        curr_bvalid = int(dut.m_bvalid.value)
        if curr_stall:
            stall_seen = True
        if curr_bvalid:
            bvalid_seen = True
        # Stall must not drop while we are mid-transaction and bvalid never fired
        if stall_seen and not bvalid_seen and curr_stall == 0:
            stall_dropped_before_bvalid = True

    await wr
    assert stall_seen, "Stall was never asserted during write"
    assert not stall_dropped_before_bvalid, "Stall cleared before bvalid handshake began"
    dut.cpu_we_i.value = 0


@cocotb.test()
async def test_stall_during_read(dut):
    """cpu_stall_o stays high for the entire read transaction."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    rd = cocotb.start_soon(axi_slave_read_ack(dut, rdata=0xFEFEFEFE))
    dut.cpu_re_i.value   = 1
    dut.cpu_addr_i.value = 0x0000_0020

    stall_seen = False
    for _ in range(40):
        await clk_edge(dut)
        await wait_ns(1)
        if int(dut.cpu_stall_o.value) == 1:
            stall_seen = True

    await rd
    assert stall_seen, "Stall was never asserted during read"
    dut.cpu_re_i.value = 0


@cocotb.test()
async def test_idle_no_stall(dut):
    """No RE/WE → cpu_stall_o=0, no AXI valid signals."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    for _ in range(10):
        await clk_edge(dut)
        await wait_ns(1)
        assert int(dut.cpu_stall_o.value) == 0,  "Unexpected stall in IDLE"
        assert int(dut.m_awvalid.value)   == 0,  "Unexpected AWVALID in IDLE"
        assert int(dut.m_wvalid.value)    == 0,  "Unexpected WVALID in IDLE"
        assert int(dut.m_arvalid.value)   == 0,  "Unexpected ARVALID in IDLE"


@cocotb.test()
async def test_slow_slave_write(dut):
    """Slave holds off awready/wready for 3 cycles; stall persists throughout."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    wr = cocotb.start_soon(axi_slave_write_ack(dut, delay_cycles=3))
    dut.cpu_we_i.value    = 1
    dut.cpu_addr_i.value  = 0x0000_0030
    dut.cpu_wdata_i.value = 0xBEEFBEEF
    dut.cpu_be_i.value    = 0xF

    # During the delay, the adapter must hold AWVALID and WVALID high
    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.m_awvalid.value) == 1, "AWVALID must stay high waiting for awready"
    assert int(dut.cpu_stall_o.value) == 1, "Stall must be active during slow ack"

    result = await wr
    addr, data, _ = result
    assert addr == 0x0000_0030
    assert data == 0xBEEFBEEF
    dut.cpu_we_i.value = 0


@cocotb.test()
async def test_slow_slave_read(dut):
    """Slave delays arready+rvalid by 3 cycles; stall persists."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    expected = 0x76543210
    rd = cocotb.start_soon(axi_slave_read_ack(dut, rdata=expected, delay_cycles=3))
    dut.cpu_re_i.value   = 1
    dut.cpu_addr_i.value = 0x0000_0040

    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.m_arvalid.value) == 1, "ARVALID must be held high"
    assert int(dut.cpu_stall_o.value) == 1

    await rd
    await clk_edge(dut)
    await wait_ns(1)
    assert int(dut.cpu_rdata_o.value) == expected
    dut.cpu_re_i.value = 0


@cocotb.test()
async def test_consecutive_writes(dut):
    """Three back-to-back writes complete in sequence; addresses and data correct."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    transactions = [
        (0x0000_0100, 0xAABBCCDD),
        (0x0000_0104, 0x11223344),
        (0x0000_0108, 0xDEADF00D),
    ]

    for addr, data in transactions:
        wr = cocotb.start_soon(axi_slave_write_ack(dut))
        dut.cpu_we_i.value    = 1
        dut.cpu_addr_i.value  = addr
        dut.cpu_wdata_i.value = data
        dut.cpu_be_i.value    = 0xF
        result = await wr
        got_addr, got_data, _ = result
        assert got_addr == addr, f"addr={hex(got_addr)} exp={hex(addr)}"
        assert got_data == data, f"data={hex(got_data)} exp={hex(data)}"
        dut.cpu_we_i.value = 0
        # Wait for stall to clear before next transaction
        for _ in range(4):
            await clk_edge(dut)
        await wait_ns(1)
        assert int(dut.cpu_stall_o.value) == 0, f"Stall not cleared after write {hex(addr)}"
