"""Phase 20 — axi4_crossbar_param cocotb tests.

Instantiated at NM=3, NS=4 (3 masters, 4 slaves).
Address map:
  Slave 0: base=0x0000_0000  mask=0xFFFF_0000   (0x0000_xxxx)
  Slave 1: base=0x1000_0000  mask=0xFFFF_0000   (0x1000_xxxx)
  Slave 2: base=0x5000_0000  mask=0xFFFF_0000   (0x5000_xxxx)
  Slave 3: base=0x8000_0000  mask=0xFFFF_0000   (0x8000_xxxx)
  Unmapped: any other address → SLVERR
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_NS = 10
NM = 3
NS = 4
DATA_W = 32

SLAVE_ADDRS = [0x00000000, 0x10000000, 0x50000000, 0x80000000]


async def reset_dut(dut):
    dut.rst_n.value = 0
    dut.m_awvalid.value = 0; dut.m_awaddr.value = 0
    dut.m_wvalid.value  = 0; dut.m_wdata.value  = 0; dut.m_wstrb.value = 0
    dut.m_bready.value  = 0
    dut.m_arvalid.value = 0; dut.m_araddr.value = 0
    dut.m_rready.value  = 0
    dut.s_awready.value = 0; dut.s_wready.value = 0
    dut.s_bvalid.value  = 0; dut.s_bresp.value  = 0
    dut.s_arready.value = 0
    dut.s_rvalid.value  = 0; dut.s_rdata.value  = 0; dut.s_rresp.value = 0
    await Timer(5 * CLK_NS, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_NS, unit="ns")


def get_s_bit(signal, s):
    return (int(signal.value) >> s) & 1


def get_s_field(signal, s, width):
    return (int(signal.value) >> (s * width)) & ((1 << width) - 1)


def get_m_bit(signal, m):
    return (int(signal.value) >> m) & 1


def get_m_field(signal, m, width):
    return (int(signal.value) >> (m * width)) & ((1 << width) - 1)


def set_m_bit(signal, m, val):
    cur = int(signal.value)
    if val:
        cur |= (1 << m)
    else:
        cur &= ~(1 << m)
    signal.value = cur


def set_m_field(signal, m, width, val):
    cur = int(signal.value)
    mask = ((1 << width) - 1) << (m * width)
    cur = (cur & ~mask) | ((val & ((1 << width) - 1)) << (m * width))
    signal.value = cur


def set_s_bit(signal, s, val):
    cur = int(signal.value)
    if val:
        cur |= (1 << s)
    else:
        cur &= ~(1 << s)
    signal.value = cur


def set_s_field(signal, s, width, val):
    cur = int(signal.value)
    mask = ((1 << width) - 1) << (s * width)
    cur = (cur & ~mask) | ((val & ((1 << width) - 1)) << (s * width))
    signal.value = cur


def start_slaves(dut, mems):
    """Start one background coroutine per slave.

    AWREADY/WREADY/ARREADY are set to 1 for ALL slaves at once (avoids
    read-modify-write race when 4 coroutines start simultaneously).
    Each slave task only manages s_bvalid and s_rvalid.
    """
    # Set all ready bits in a single atomic write — no race
    dut.s_awready.value = (1 << NS) - 1
    dut.s_wready.value  = (1 << NS) - 1
    dut.s_arready.value = (1 << NS) - 1

    handles = []
    for s in range(NS):
        handles.append(cocotb.start_soon(_slave(dut, s, mems[s])))
    return handles


async def _slave(dut, s, mem):
    """Simple AXI4-Lite slave: always-ready, fixed-latency response.

    Timing contract (slave fires before test at every Timer+1ns because the
    slave registers its RisingEdge triggers slightly earlier):
      - Slave sees s_awvalid/s_arvalid at Timer+1ns of the handshake clock.
      - Slave asserts BVALID/RVALID one clock later (RTL arbiter samples it at
        the FOLLOWING clock when m_bready/m_rready is still 1).
      - Slave holds the response signal for 3 clocks total so the RTL arbiter's
        always_ff has one full cycle to register the handshake before clearing.
    """
    while True:
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        aw = get_s_bit(dut.s_awvalid, s)
        w  = get_s_bit(dut.s_wvalid,  s)
        ar = get_s_bit(dut.s_arvalid, s)

        if aw and w:
            addr  = get_s_field(dut.s_awaddr, s, 32)
            wdata = get_s_field(dut.s_wdata,  s, 32)
            mem[addr & 0xFFFF] = wdata
            # Clock +1: assert BVALID (RTL sees it at clock +2 evaluation)
            await RisingEdge(dut.clk)
            set_s_bit(dut.s_bvalid, s, 1)
            # Clock +2: RTL always_ff sees bvalid=1 + bready=1 → wr_busy<=0;
            #           slave clears bvalid and immediately re-enters main loop
            #           so it is available to sample the next AW/AR at +3+Timer.
            await RisingEdge(dut.clk)
            set_s_bit(dut.s_bvalid, s, 0)

        elif ar:
            addr  = get_s_field(dut.s_araddr, s, 32)
            rdata = mem.get(addr & 0xFFFF, 0)
            # Clock +1: assert RVALID + RDATA
            await RisingEdge(dut.clk)
            set_s_field(dut.s_rdata, s, 32, rdata)
            set_s_bit(dut.s_rvalid, s, 1)
            # Clock +2: RTL always_ff sees rvalid=1 + rready=1 → rd_busy<=0
            await RisingEdge(dut.clk)
            set_s_bit(dut.s_rvalid, s, 0)


async def axi_write(dut, master, slave_idx, offset, data, strb=0xF):
    """Issue a single AXI4-Lite write from master m to slave s."""
    addr = SLAVE_ADDRS[slave_idx] | (offset & 0xFFFF)
    set_m_bit(dut.m_awvalid, master, 1)
    set_m_field(dut.m_awaddr, master, 32, addr)
    set_m_bit(dut.m_wvalid, master, 1)
    set_m_field(dut.m_wdata, master, 32, data)
    set_m_field(dut.m_wstrb, master, 4, strb)
    set_m_bit(dut.m_bready, master, 1)

    # Wait for AWREADY
    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_awready, master):
            set_m_bit(dut.m_awvalid, master, 0)
            break
    else:
        assert False, f"M{master}: AWREADY timeout (slave {slave_idx})"

    # Wait for WREADY (with cocotb 2.x safe int conversion)
    for _ in range(50):
        if not ((int(dut.m_wvalid.value) >> master) & 1):
            break
        if get_m_bit(dut.m_wready, master):
            set_m_bit(dut.m_wvalid, master, 0)
            set_m_field(dut.m_wstrb, master, 4, 0)
            break
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

    # Wait for BVALID
    bresp = 0
    for _ in range(100):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_bvalid, master):
            bresp = get_m_field(dut.m_bresp, master, 2)
            # Hold m_bready high for one more clock so the RTL arbiter sees
            # s_bvalid=1 && m_bready=1 at the next rising edge and clears wr_busy
            await RisingEdge(dut.clk)
            set_m_bit(dut.m_bready, master, 0)
            break
    else:
        assert False, f"M{master}: BVALID timeout"
    return bresp


async def axi_read(dut, master, slave_idx, offset):
    """Issue a single AXI4-Lite read from master m."""
    addr = SLAVE_ADDRS[slave_idx] | (offset & 0xFFFF)
    set_m_bit(dut.m_arvalid, master, 1)
    set_m_field(dut.m_araddr, master, 32, addr)
    set_m_bit(dut.m_rready, master, 1)

    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_arready, master):
            set_m_bit(dut.m_arvalid, master, 0)
            break
    else:
        assert False, f"M{master}: ARREADY timeout (slave {slave_idx})"

    rdata = 0; rresp = 0
    for _ in range(100):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_rvalid, master):
            rdata = get_m_field(dut.m_rdata, master, 32)
            rresp = get_m_field(dut.m_rresp, master, 2)
            # Hold m_rready one extra clock so the RTL rd_busy arbiter sees
            # s_rvalid=1 && m_rready=1 at a rising edge and clears rd_busy.
            await RisingEdge(dut.clk)
            set_m_bit(dut.m_rready, master, 0)
            break
    else:
        assert False, f"M{master}: RVALID timeout"
    return rdata, rresp


# ── Test 1: simple write then read, master 0 → slave 0 ───────────────────────
@cocotb.test()
async def test_wr_rd_m0_s0(dut):
    """M0 writes 0xDEADBEEF to S0, reads it back."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    bresp = await axi_write(dut, 0, 0, 0x10, 0xDEADBEEF)
    assert bresp == 0, f"expected OKAY, got {bresp}"
    rdata, rresp = await axi_read(dut, 0, 0, 0x10)
    assert rresp == 0, f"read resp: {rresp}"
    assert rdata == 0xDEADBEEF, f"expected 0xDEADBEEF, got {rdata:#010x}"


# ── Test 2: master 1 → slave 2 ────────────────────────────────────────────────
@cocotb.test()
async def test_wr_rd_m1_s2(dut):
    """M1 writes to S2 (addr 0x5000_xxxx)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    bresp = await axi_write(dut, 1, 2, 0x00, 0xCAFEBABE)
    assert bresp == 0
    rdata, _ = await axi_read(dut, 1, 2, 0x00)
    assert rdata == 0xCAFEBABE, f"got {rdata:#010x}"


# ── Test 3: master 2 → slave 3 ────────────────────────────────────────────────
@cocotb.test()
async def test_wr_rd_m2_s3(dut):
    """M2 accesses S3 (addr 0x8000_xxxx)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    bresp = await axi_write(dut, 2, 3, 0x04, 0x12345678)
    assert bresp == 0
    rdata, _ = await axi_read(dut, 2, 3, 0x04)
    assert rdata == 0x12345678


# ── Test 4: address decode — all four slaves from master 0 ────────────────────
@cocotb.test()
async def test_all_slaves_m0(dut):
    """M0 writes a different value to each slave, reads back."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    for s in range(NS):
        val = 0xA0000000 | s
        await axi_write(dut, 0, s, 0x00, val)
    for s in range(NS):
        val = 0xA0000000 | s
        rdata, _ = await axi_read(dut, 0, s, 0x00)
        assert rdata == val, f"S{s}: expected {val:#x}, got {rdata:#x}"


# ── Test 5: sequential writes from different masters to same slave ─────────────
@cocotb.test()
async def test_sequential_masters_same_slave(dut):
    """M0, M1, M2 each write to S1 in sequence; read back via respective master."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    for m in range(NM):
        bresp = await axi_write(dut, m, 1, m * 4, 0xBEEF0000 | m)
        assert bresp == 0, f"M{m} write to S1 failed"
    for m in range(NM):
        rdata, _ = await axi_read(dut, m, 1, m * 4)
        assert rdata == (0xBEEF0000 | m), f"M{m} readback failed: {rdata:#x}"


# ── Test 6: SLVERR on unmapped write address ──────────────────────────────────
@cocotb.test()
async def test_slverr_unmapped_write(dut):
    """Write to unmapped address (0xDEAD_0000) returns BRESP=SLVERR (2'b10)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    UNMAPPED = 0xDEAD0000
    set_m_field(dut.m_awaddr, 0, 32, UNMAPPED)
    set_m_bit(dut.m_awvalid, 0, 1)
    set_m_field(dut.m_wdata, 0, 32, 0xBAD0)
    set_m_field(dut.m_wstrb, 0, 4, 0xF)
    set_m_bit(dut.m_wvalid, 0, 1)
    set_m_bit(dut.m_bready, 0, 1)

    # SLVERR path: m_awready is COMBINATIONAL (asserted as soon as m_awvalid=1
    # and addr is unmapped, before any clock edge).  After the next rising edge
    # the SLVERR FSM captures AW+W and sets slverr_wr_busy (NBA), which deasserts
    # AWREADY and asserts BVALID.  We must sample AWREADY before that NBA.
    await Timer(1, unit="ns")
    assert get_m_bit(dut.m_awready, 0), "AWREADY not combinational for unmapped addr"

    # Advance one clock so the SLVERR FSM captures the transaction
    await RisingEdge(dut.clk)
    set_m_bit(dut.m_awvalid, 0, 0)
    set_m_bit(dut.m_wvalid, 0, 0)

    # slverr_wr_busy is now 1 (NBA committed); m_bvalid=1 combinationally
    await Timer(1, unit="ns")
    assert get_m_bit(dut.m_bvalid, 0), "BVALID not driven by SLVERR FSM"
    bresp = get_m_field(dut.m_bresp, 0, 2)
    assert bresp == 2, f"expected SLVERR (2), got {bresp}"
    # Hold m_bready through one more clock so the FSM clears slverr_wr_busy
    await RisingEdge(dut.clk)
    set_m_bit(dut.m_bready, 0, 0)


# ── Test 7: SLVERR on unmapped read address ───────────────────────────────────
@cocotb.test()
async def test_slverr_unmapped_read(dut):
    """Read from unmapped address returns RRESP=SLVERR (2'b10)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    UNMAPPED = 0xF0000000
    set_m_field(dut.m_araddr, 1, 32, UNMAPPED)
    set_m_bit(dut.m_arvalid, 1, 1)
    set_m_bit(dut.m_rready, 1, 1)

    # SLVERR path: m_arready is COMBINATIONAL (same logic as write AWREADY).
    # Sample it before the first clock edge; then advance one clock for the
    # SLVERR FSM to set slverr_rd_busy (NBA), which deasserts ARREADY and
    # asserts RVALID.
    await Timer(1, unit="ns")
    assert get_m_bit(dut.m_arready, 1), "ARREADY not combinational for unmapped addr"

    await RisingEdge(dut.clk)
    set_m_bit(dut.m_arvalid, 1, 0)

    # slverr_rd_busy is now 1 (NBA committed); m_rvalid=1 combinationally
    await Timer(1, unit="ns")
    assert get_m_bit(dut.m_rvalid, 1), "RVALID not driven by SLVERR FSM"
    rresp = get_m_field(dut.m_rresp, 1, 2)
    assert rresp == 2, f"expected SLVERR (2), got {rresp}"
    # Hold m_rready through one more clock so the FSM clears slverr_rd_busy
    await RisingEdge(dut.clk)
    set_m_bit(dut.m_rready, 1, 0)


# ── Test 8: back-to-back writes from master 0 to slave 0 ─────────────────────
@cocotb.test()
async def test_back_to_back_writes(dut):
    """Four consecutive writes from M0 to S0 at different offsets."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    for i in range(4):
        bresp = await axi_write(dut, 0, 0, i * 4, 0x1000 + i)
        assert bresp == 0
    for i in range(4):
        rdata, _ = await axi_read(dut, 0, 0, i * 4)
        assert rdata == (0x1000 + i), f"offset {i*4}: got {rdata}"
