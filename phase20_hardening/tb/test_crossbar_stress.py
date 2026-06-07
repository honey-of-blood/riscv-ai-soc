"""Phase 20 — axi4_crossbar_param aggressive stress tests.

Covers: true concurrent parallelism on different slaves, round-robin arbitration
under contention (all masters same slave), cross-master data sharing, address
boundary correctness, simultaneous SLVERR from all masters, long sequential
stress, mixed concurrent traffic, and data-pattern extremes.

Concurrent test design note
----------------------------
Icarus VPI writes are NOT immediately visible to reads in the same simulation
time step — last writer wins on concurrent read-modify-write.  All six concurrent
tests therefore:
  1. Write ALL master signals atomically (full-value writes, no RMW) BEFORE any
     ``await``, so the crossbar sees all masters asserted on the same clock.
  2. Use a single polling coroutine (no ``start_soon``) to track every master's
     handshakes, deassert signals with a single atomic write per iteration.
  3. Use ``SlaveState`` to avoid the same RMW race in slave bvalid/rvalid: each
     slave writes only its own Python slot; the flush assembles the full value.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_NS = 10
NM = 3
NS = 4
SLAVE_ADDRS = [0x00000000, 0x10000000, 0x50000000, 0x80000000]


# ── Helpers ────────────────────────────────────────────────────────────────────

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


def get_s_bit(sig, s):      return (int(sig.value) >> s) & 1
def get_s_field(sig, s, w): return (int(sig.value) >> (s * w)) & ((1 << w) - 1)
def get_m_bit(sig, m):      return (int(sig.value) >> m) & 1
def get_m_field(sig, m, w): return (int(sig.value) >> (m * w)) & ((1 << w) - 1)

def set_m_bit(sig, m, val):
    cur = int(sig.value)
    sig.value = (cur | (1 << m)) if val else (cur & ~(1 << m))

def set_m_field(sig, m, w, val):
    cur = int(sig.value)
    mask = ((1 << w) - 1) << (m * w)
    sig.value = (cur & ~mask) | ((val & ((1 << w) - 1)) << (m * w))

def set_s_bit(sig, s, val):
    cur = int(sig.value)
    sig.value = (cur | (1 << s)) if val else (cur & ~(1 << s))

def set_s_field(sig, s, w, val):
    cur = int(sig.value)
    mask = ((1 << w) - 1) << (s * w)
    sig.value = (cur & ~mask) | ((val & ((1 << w) - 1)) << (s * w))


class SlaveState:
    """Avoids VPI RMW races when multiple slaves update shared packed signals."""
    def __init__(self):
        self.bvalid = [0] * NS
        self.rvalid = [0] * NS
        self.rdata  = [0] * NS

    def _flush(self, dut):
        bv = 0; rv = 0; rd = 0
        for s in range(NS):
            bv |= self.bvalid[s] << s
            rv |= self.rvalid[s] << s
            rd |= self.rdata[s] << (s * 32)
        dut.s_bvalid.value = bv
        dut.s_rvalid.value = rv
        dut.s_rdata.value  = rd

    def set_bvalid(self, dut, s, val):
        self.bvalid[s] = val
        self._flush(dut)

    def set_rdata_rvalid(self, dut, s, data, valid):
        self.rdata[s]  = data
        self.rvalid[s] = valid
        self._flush(dut)


def start_slaves(dut, mems):
    state = SlaveState()
    dut.s_awready.value = (1 << NS) - 1
    dut.s_wready.value  = (1 << NS) - 1
    dut.s_arready.value = (1 << NS) - 1
    for s in range(NS):
        cocotb.start_soon(_slave(dut, s, mems[s], state))
    return state


async def _slave(dut, s, mem, state):
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
            await RisingEdge(dut.clk)
            state.set_bvalid(dut, s, 1)
            await RisingEdge(dut.clk)
            state.set_bvalid(dut, s, 0)
        elif ar:
            addr  = get_s_field(dut.s_araddr, s, 32)
            rdata = mem.get(addr & 0xFFFF, 0)
            await RisingEdge(dut.clk)
            state.set_rdata_rvalid(dut, s, rdata, 1)
            await RisingEdge(dut.clk)
            state.set_rdata_rvalid(dut, s, 0, 0)


async def axi_write(dut, master, slave_idx, offset, data, strb=0xF):
    addr = SLAVE_ADDRS[slave_idx] | (offset & 0xFFFF)
    set_m_bit(dut.m_awvalid, master, 1)
    set_m_field(dut.m_awaddr, master, 32, addr)
    set_m_bit(dut.m_wvalid, master, 1)
    set_m_field(dut.m_wdata, master, 32, data)
    set_m_field(dut.m_wstrb, master, 4, strb)
    set_m_bit(dut.m_bready, master, 1)
    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_awready, master):
            set_m_bit(dut.m_awvalid, master, 0)
            break
    else:
        assert False, f"M{master}: AWREADY timeout (slave {slave_idx})"
    for _ in range(50):
        if not ((int(dut.m_wvalid.value) >> master) & 1):
            break
        if get_m_bit(dut.m_wready, master):
            set_m_bit(dut.m_wvalid, master, 0)
            set_m_field(dut.m_wstrb, master, 4, 0)
            break
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
    bresp = 0
    for _ in range(100):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if get_m_bit(dut.m_bvalid, master):
            bresp = get_m_field(dut.m_bresp, master, 2)
            await RisingEdge(dut.clk)
            set_m_bit(dut.m_bready, master, 0)
            break
    else:
        assert False, f"M{master}: BVALID timeout"
    return bresp


async def axi_read(dut, master, slave_idx, offset):
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
            await RisingEdge(dut.clk)
            set_m_bit(dut.m_rready, master, 0)
            break
    else:
        assert False, f"M{master}: RVALID timeout"
    return rdata, rresp


# ── Atomic multi-master helpers ─────────────────────────────────────────────────

def pack_addr(addrs):
    """Pack list of 32-bit addrs into a single integer (master 0 at LSB)."""
    v = 0
    for m, a in enumerate(addrs):
        v |= (a & 0xFFFFFFFF) << (m * 32)
    return v

def pack_data(datas):
    v = 0
    for m, d in enumerate(datas):
        v |= (d & 0xFFFFFFFF) << (m * 32)
    return v

def pack_strb(strbs):
    v = 0
    for m, s in enumerate(strbs):
        v |= (s & 0xF) << (m * 4)
    return v


async def _poll_awready_wready(dut, masters):
    """Poll until all listed masters have received AWREADY; also clears wvalid on wready.
    Returns bitmask of which masters completed AWREADY."""
    aw_done = 0
    mask = sum(1 << m for m in masters)
    for _ in range(150):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        ar   = int(dut.m_awready.value)
        wr   = int(dut.m_wready.value)
        av   = int(dut.m_awvalid.value)
        wv   = int(dut.m_wvalid.value)
        wstrb = int(dut.m_wstrb.value)
        for m in masters:
            if (ar >> m) & 1 and not (aw_done >> m) & 1:
                aw_done |= (1 << m)
                av &= ~(1 << m)
            if (wr >> m) & 1 and (wv >> m) & 1:
                wv &= ~(1 << m)
                wstrb &= ~(0xF << (m * 4))
        dut.m_awvalid.value = av
        dut.m_wvalid.value  = wv
        dut.m_wstrb.value   = wstrb
        if (aw_done & mask) == mask:
            break
    else:
        assert False, f"AWREADY timeout: done={aw_done:#05b} expected={mask:#05b}"


async def _poll_bvalid(dut, masters, timeout=300):
    """Wait for BVALID for each listed master. Returns list of bresps."""
    done = 0
    bresps = [0] * NM
    mask = sum(1 << m for m in masters)
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        bv = int(dut.m_bvalid.value)
        for m in masters:
            if (bv >> m) & 1 and not (done >> m) & 1:
                done |= (1 << m)
                bresps[m] = get_m_field(dut.m_bresp, m, 2)
        if (done & mask) == mask:
            break
    else:
        assert False, f"BVALID timeout: done={done:#05b} expected={mask:#05b}"
    dut.m_bready.value = 0
    await RisingEdge(dut.clk)
    return bresps


async def _poll_arready(dut, masters):
    """Poll until all listed masters have received ARREADY."""
    ar_done = 0
    mask = sum(1 << m for m in masters)
    for _ in range(150):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        arready = int(dut.m_arready.value)
        av      = int(dut.m_arvalid.value)
        for m in masters:
            if (arready >> m) & 1 and not (ar_done >> m) & 1:
                ar_done |= (1 << m)
                av &= ~(1 << m)
        dut.m_arvalid.value = av
        if (ar_done & mask) == mask:
            break
    else:
        assert False, f"ARREADY timeout: done={ar_done:#05b} expected={mask:#05b}"


async def _poll_rvalid(dut, masters, timeout=200):
    """Wait for RVALID for each listed master. Returns (rdatas, rresps) lists."""
    done   = 0
    rdatas = [0] * NM
    rresps = [0] * NM
    mask   = sum(1 << m for m in masters)
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        rv = int(dut.m_rvalid.value)
        for m in masters:
            if (rv >> m) & 1 and not (done >> m) & 1:
                done |= (1 << m)
                rdatas[m] = get_m_field(dut.m_rdata,  m, 32)
                rresps[m] = get_m_field(dut.m_rresp,  m, 2)
        if (done & mask) == mask:
            break
    else:
        assert False, f"RVALID timeout: done={done:#05b} expected={mask:#05b}"
    dut.m_rready.value = 0
    await RisingEdge(dut.clk)
    return rdatas, rresps


# ── Stress Tests ───────────────────────────────────────────────────────────────

@cocotb.test()
async def test_concurrent_writes_diff_slaves(dut):
    """M0→S0, M1→S1, M2→S2 — all signals set atomically before first clock.
    All 3 transactions run concurrently in RTL; data integrity verified by readback."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    d0, d1, d2 = 0xAABBCCDD, 0x11223344, 0x55667788
    addrs = [SLAVE_ADDRS[s] | 0x10 for s in range(3)]

    # Atomic setup — no RMW, single write per signal
    dut.m_awvalid.value = 0x7
    dut.m_awaddr.value  = pack_addr(addrs)
    dut.m_wvalid.value  = 0x7
    dut.m_wdata.value   = pack_data([d0, d1, d2])
    dut.m_wstrb.value   = pack_strb([0xF, 0xF, 0xF])
    dut.m_bready.value  = 0x7

    await _poll_awready_wready(dut, [0, 1, 2])
    bresps = await _poll_bvalid(dut, [0, 1, 2])
    assert all(r == 0 for r in bresps), f"Non-OKAY bresps: {bresps}"

    d0b, _ = await axi_read(dut, 0, 0, 0x10)
    d1b, _ = await axi_read(dut, 1, 1, 0x10)
    d2b, _ = await axi_read(dut, 2, 2, 0x10)
    assert d0b == d0, f"S0: {d0b:#010x}"
    assert d1b == d1, f"S1: {d1b:#010x}"
    assert d2b == d2, f"S2: {d2b:#010x}"


@cocotb.test()
async def test_concurrent_reads_diff_slaves(dut):
    """M0←S0, M1←S1, M2←S3 in parallel — AR/R channel routing verified."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    # Seed via sequential writes (single master at a time — no RMW race)
    await axi_write(dut, 0, 0, 0x20, 0xDEAD0000)
    await axi_write(dut, 0, 1, 0x20, 0xDEAD0001)
    await axi_write(dut, 0, 3, 0x20, 0xDEAD0003)

    read_addrs = [SLAVE_ADDRS[0] | 0x20,
                  SLAVE_ADDRS[1] | 0x20,
                  SLAVE_ADDRS[3] | 0x20]  # M2 reads S3

    dut.m_arvalid.value = 0x7
    dut.m_araddr.value  = pack_addr(read_addrs)
    dut.m_rready.value  = 0x7

    await _poll_arready(dut, [0, 1, 2])
    rdatas, rresps = await _poll_rvalid(dut, [0, 1, 2])

    assert all(r == 0 for r in rresps), f"Non-OKAY rresps: {rresps}"
    assert rdatas[0] == 0xDEAD0000, f"S0: {rdatas[0]:#010x}"
    assert rdatas[1] == 0xDEAD0001, f"S1: {rdatas[1]:#010x}"
    assert rdatas[2] == 0xDEAD0003, f"S3: {rdatas[2]:#010x}"


@cocotb.test()
async def test_all_masters_contend_same_slave(dut):
    """M0, M1, M2 simultaneously target S0 — round-robin must serialize without deadlock.

    AWREADY and BVALID are polled in a single loop because each master's BVALID
    can fire (and expire) while the other two are still awaiting their AWREADY.
    Splitting into two sequential phases would miss early BVALIDs.
    """
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    d0, d1, d2 = 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC
    addrs = [SLAVE_ADDRS[0] | 0x30,
             SLAVE_ADDRS[0] | 0x34,
             SLAVE_ADDRS[0] | 0x38]

    dut.m_awvalid.value = 0x7
    dut.m_awaddr.value  = pack_addr(addrs)
    dut.m_wvalid.value  = 0x7
    dut.m_wdata.value   = pack_data([d0, d1, d2])
    dut.m_wstrb.value   = pack_strb([0xF, 0xF, 0xF])
    dut.m_bready.value  = 0x7

    # Single loop: catch AWREADY and BVALID together.
    # Round-robin serialises: one master gets AWREADY per ~10 cycles, so
    # M0's BVALID arrives ~3 cycles after M0's AWREADY, long before M2's AWREADY.
    aw_done = 0; b_done = 0
    bresps  = [0] * NM
    for _ in range(600):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        ar    = int(dut.m_awready.value)
        wr    = int(dut.m_wready.value)
        bv    = int(dut.m_bvalid.value)
        av    = int(dut.m_awvalid.value)
        wv    = int(dut.m_wvalid.value)
        wstrb = int(dut.m_wstrb.value)
        for m in range(3):
            if (ar >> m) & 1 and not (aw_done >> m) & 1:
                aw_done |= (1 << m); av &= ~(1 << m)
            if (wr >> m) & 1 and (wv >> m) & 1:
                wv &= ~(1 << m); wstrb &= ~(0xF << (m * 4))
            if (bv >> m) & 1 and not (b_done >> m) & 1:
                b_done |= (1 << m); bresps[m] = get_m_field(dut.m_bresp, m, 2)
        dut.m_awvalid.value = av
        dut.m_wvalid.value  = wv
        dut.m_wstrb.value   = wstrb
        if (b_done & 0x7) == 0x7:
            break
    else:
        assert False, \
            f"Contention timeout: aw_done={aw_done:#05b} b_done={b_done:#05b}"

    dut.m_bready.value = 0
    await RisingEdge(dut.clk)

    assert all(r == 0 for r in bresps), f"Non-OKAY bresps: {bresps}"

    d0b, _ = await axi_read(dut, 0, 0, 0x30)
    d1b, _ = await axi_read(dut, 0, 0, 0x34)
    d2b, _ = await axi_read(dut, 0, 0, 0x38)
    assert d0b == d0, f"offset 0x30: {d0b:#010x}"
    assert d1b == d1, f"offset 0x34: {d1b:#010x}"
    assert d2b == d2, f"offset 0x38: {d2b:#010x}"


@cocotb.test()
async def test_cross_master_data_sharing(dut):
    """M0 writes S2; M1 reads back. M2 writes S3; M0 reads back. B/R routing verified."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    assert await axi_write(dut, 0, 2, 0x40, 0xC0FFEE00) == 0
    rdata, rresp = await axi_read(dut, 1, 2, 0x40)
    assert rresp == 0 and rdata == 0xC0FFEE00, \
        f"M0-write/M1-read S2: resp={rresp} data={rdata:#010x}"

    assert await axi_write(dut, 2, 3, 0x44, 0xFEEDFACE) == 0
    rdata2, rresp2 = await axi_read(dut, 0, 3, 0x44)
    assert rresp2 == 0 and rdata2 == 0xFEEDFACE, \
        f"M2-write/M0-read S3: resp={rresp2} data={rdata2:#010x}"

    assert await axi_write(dut, 1, 1, 0x48, 0xBEEFCAFE) == 0
    rdata3, _ = await axi_read(dut, 2, 1, 0x48)
    assert rdata3 == 0xBEEFCAFE, f"M1-write/M2-read S1: {rdata3:#010x}"


@cocotb.test()
async def test_boundary_addresses(dut):
    """First word (offset 0x0000) and last word (offset 0xFFFC) of every slave."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    for s in range(NS):
        first_val = 0xF1F50000 | s
        last_val  = 0xA5A50000 | s

        assert await axi_write(dut, 0, s, 0x0000, first_val) == 0
        assert await axi_write(dut, 0, s, 0xFFFC, last_val)  == 0

        d_first, _ = await axi_read(dut, 0, s, 0x0000)
        d_last,  _ = await axi_read(dut, 0, s, 0xFFFC)
        assert d_first == first_val, f"S{s} first-word: {d_first:#010x}"
        assert d_last  == last_val,  f"S{s} last-word:  {d_last:#010x}"


@cocotb.test()
async def test_slverr_all_masters_concurrent_write(dut):
    """All 3 masters simultaneously issue unmapped writes — each gets SLVERR independently."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    unmapped = [0xDEAD0000, 0xBEEF0000, 0xCAFE0000]
    dut.m_awvalid.value = 0x7
    dut.m_awaddr.value  = pack_addr(unmapped)
    dut.m_wvalid.value  = 0x7
    dut.m_wdata.value   = pack_data([0xBAD00000, 0xBAD00001, 0xBAD00002])
    dut.m_wstrb.value   = pack_strb([0xF, 0xF, 0xF])
    dut.m_bready.value  = 0x7

    # SLVERR AWREADY is combinational — all three must appear immediately
    await Timer(1, unit="ns")
    ardy = int(dut.m_awready.value)
    for m in range(3):
        assert (ardy >> m) & 1, \
            f"M{m}: AWREADY not combinational for unmapped addr {unmapped[m]:#010x}"

    # Advance one clock so the per-master SLVERR FSM captures awvalid
    await RisingEdge(dut.clk)
    dut.m_awvalid.value = 0x0
    dut.m_wvalid.value  = 0x0
    await Timer(1, unit="ns")

    # BVALID with SLVERR(2) should be driven for all 3
    bv = int(dut.m_bvalid.value)
    for m in range(3):
        assert (bv >> m) & 1, f"M{m}: BVALID not driven by SLVERR FSM"
        bresp = get_m_field(dut.m_bresp, m, 2)
        assert bresp == 2, f"M{m}: expected SLVERR(2), got {bresp}"

    await RisingEdge(dut.clk)
    dut.m_bready.value = 0x0


@cocotb.test()
async def test_slverr_all_masters_concurrent_read(dut):
    """All 3 masters simultaneously issue unmapped reads — each gets SLVERR independently."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    unmapped = [0xF0000000, 0xF1000000, 0xF2000000]
    dut.m_arvalid.value = 0x7
    dut.m_araddr.value  = pack_addr(unmapped)
    dut.m_rready.value  = 0x7

    # SLVERR ARREADY is combinational
    await Timer(1, unit="ns")
    ardy = int(dut.m_arready.value)
    for m in range(3):
        assert (ardy >> m) & 1, \
            f"M{m}: ARREADY not combinational for unmapped addr {unmapped[m]:#010x}"

    await RisingEdge(dut.clk)
    dut.m_arvalid.value = 0x0
    await Timer(1, unit="ns")

    rv = int(dut.m_rvalid.value)
    for m in range(3):
        assert (rv >> m) & 1, f"M{m}: RVALID not driven by SLVERR FSM"
        rresp = get_m_field(dut.m_rresp, m, 2)
        assert rresp == 2, f"M{m}: expected SLVERR(2), got {rresp}"

    await RisingEdge(dut.clk)
    dut.m_rready.value = 0x0


@cocotb.test()
async def test_20_sequential_writes_and_reads(dut):
    """M0 issues 20 consecutive writes to S0 then reads all 20 back — no data corruption."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    N = 20
    for i in range(N):
        resp = await axi_write(dut, 0, 0, i * 4, 0xA0000000 | i)
        assert resp == 0, f"write {i} returned {resp}"

    for i in range(N):
        rdata, rresp = await axi_read(dut, 0, 0, i * 4)
        assert rresp == 0, f"read {i} rresp={rresp}"
        assert rdata == (0xA0000000 | i), f"offset {i*4:#05x}: {rdata:#010x}"


@cocotb.test()
async def test_mixed_concurrent_traffic(dut):
    """M0 reads S0, M1 writes S1, M2 reads S3 simultaneously — signals set atomically."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    # Pre-seed S0 and S3 so reads have known data
    await axi_write(dut, 0, 0, 0x50, 0x12345678)
    await axi_write(dut, 0, 3, 0x50, 0x87654321)

    # Atomic setup: M0=AR(S0), M1=AW+W(S1), M2=AR(S3)
    ar0 = SLAVE_ADDRS[0] | 0x50
    aw1 = SLAVE_ADDRS[1] | 0x50
    ar2 = SLAVE_ADDRS[3] | 0x50

    dut.m_arvalid.value = (1 << 0) | (1 << 2)
    dut.m_araddr.value  = pack_addr([ar0, 0, ar2])   # M1 slot unused
    dut.m_rready.value  = (1 << 0) | (1 << 2)

    dut.m_awvalid.value = (1 << 1)
    dut.m_awaddr.value  = pack_addr([0, aw1, 0])
    dut.m_wvalid.value  = (1 << 1)
    dut.m_wdata.value   = pack_data([0, 0xABCDEF01, 0])
    dut.m_wstrb.value   = pack_strb([0, 0xF, 0])
    dut.m_bready.value  = (1 << 1)

    # Poll AR-ready for M0 and M2; AW-ready for M1 — all in single loop
    ar_done = 0; aw_done = 0
    for _ in range(100):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        arready = int(dut.m_arready.value)
        awready = int(dut.m_awready.value)
        wready  = int(dut.m_wready.value)
        av      = int(dut.m_arvalid.value)
        awv     = int(dut.m_awvalid.value)
        wv      = int(dut.m_wvalid.value)
        wstrb   = int(dut.m_wstrb.value)

        if (arready >> 0) & 1 and not (ar_done >> 0) & 1:
            ar_done |= (1 << 0); av &= ~(1 << 0)
        if (arready >> 2) & 1 and not (ar_done >> 2) & 1:
            ar_done |= (1 << 2); av &= ~(1 << 2)
        if (awready >> 1) & 1 and not (aw_done >> 1) & 1:
            aw_done |= (1 << 1); awv &= ~(1 << 1)
        if (wready >> 1) & 1 and (wv >> 1) & 1:
            wv &= ~(1 << 1); wstrb &= ~(0xF << 4)

        dut.m_arvalid.value = av
        dut.m_awvalid.value = awv
        dut.m_wvalid.value  = wv
        dut.m_wstrb.value   = wstrb

        if (ar_done & 0x5) == 0x5 and (aw_done & 0x2) == 0x2:
            break
    else:
        assert False, f"AR/AW-READY timeout: ar_done={ar_done:#05b} aw_done={aw_done:#05b}"

    # Poll RVALID for M0 and M2; BVALID for M1
    r_done = 0; b_done = 0
    rdatas = [0] * NM; bresp1 = 0
    for _ in range(200):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        rv = int(dut.m_rvalid.value)
        bv = int(dut.m_bvalid.value)
        if (rv >> 0) & 1 and not (r_done >> 0) & 1:
            r_done |= 1; rdatas[0] = get_m_field(dut.m_rdata, 0, 32)
        if (rv >> 2) & 1 and not (r_done >> 2) & 1:
            r_done |= 4; rdatas[2] = get_m_field(dut.m_rdata, 2, 32)
        if (bv >> 1) & 1 and not (b_done >> 1) & 1:
            b_done |= 2; bresp1 = get_m_field(dut.m_bresp, 1, 2)
        if (r_done & 0x5) == 0x5 and (b_done & 0x2) == 0x2:
            break
    else:
        assert False, f"RVALID/BVALID timeout: r_done={r_done:#05b} b_done={b_done:#05b}"

    dut.m_rready.value = 0x0
    dut.m_bready.value = 0x0
    await RisingEdge(dut.clk)

    assert rdatas[0] == 0x12345678, f"M0 read S0: {rdatas[0]:#010x}"
    assert rdatas[2] == 0x87654321, f"M2 read S3: {rdatas[2]:#010x}"
    assert bresp1 == 0,             f"M1 write S1: resp={bresp1}"

    d1b, _ = await axi_read(dut, 1, 1, 0x50)
    assert d1b == 0xABCDEF01, f"M1 write S1 readback: {d1b:#010x}"


@cocotb.test()
async def test_data_patterns(dut):
    """Stress data bus with 0x00000000, 0xFFFFFFFF, 0xAAAAAAAA, 0x55555555 across all slaves."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    patterns = [0x00000000, 0xFFFFFFFF, 0xAAAAAAAA, 0x55555555]
    for s in range(NS):
        for i, pat in enumerate(patterns):
            off = i * 4
            assert await axi_write(dut, 0, s, off, pat) == 0, \
                f"S{s} off={off:#05x} write failed"
            rdata, rresp = await axi_read(dut, 0, s, off)
            assert rresp == 0, f"S{s} off={off:#05x} rresp={rresp}"
            assert rdata == pat, \
                f"S{s} off={off:#05x}: wrote {pat:#010x}, read {rdata:#010x}"


@cocotb.test()
async def test_write_then_overwrite_and_verify(dut):
    """Write a value, overwrite it, verify only the last value persists."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    mems = [{} for _ in range(NS)]
    start_slaves(dut, mems)
    await Timer(2 * CLK_NS, unit="ns")

    for s in range(NS):
        await axi_write(dut, 0, s, 0x60, 0xDEAD1111)
        await axi_write(dut, 0, s, 0x60, 0x12345678)
        rdata, _ = await axi_read(dut, 0, s, 0x60)
        assert rdata == 0x12345678, f"S{s}: overwrite failed, got {rdata:#010x}"
