"""
AXI4 crossbar stress tests — concurrent access and arbitration corner cases.

Timing rule (matches slave_ack_write pattern from test_axi4_crossbar.py):
  - Slave sets bvalid/rvalid at a clk_edge, then waits 1ns before checking bready/rready
  - Test polls bvalid/rvalid AT the rising edge (no Timer delay)
  This ensures the test reads the asserted value BEFORE the slave's Timer fires.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer

async def gen_clock(dut):
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")

async def clk_edge(dut):
    await RisingEdge(dut.clk)

def idle_all_masters(dut):
    for m in ("m0", "m1", "m2"):
        for sig in ("awvalid", "wvalid", "bready", "arvalid", "rready"):
            getattr(dut, f"{m}_{sig}").value = 0
        for sig in ("awaddr", "wdata", "wstrb", "araddr"):
            try: getattr(dut, f"{m}_{sig}").value = 0
            except: pass

def idle_all_slaves(dut):
    for p in ("s0", "s1", "s2"):
        for sig in ("awready", "wready", "bresp", "bvalid",
                    "arready", "rdata", "rresp", "rvalid"):
            try: getattr(dut, f"{p}_{sig}").value = 0
            except: pass

async def reset_dut(dut, cycles=4):
    dut.rst_n.value = 0
    idle_all_masters(dut)
    idle_all_slaves(dut)
    for _ in range(cycles):
        await clk_edge(dut)
    dut.rst_n.value = 1


async def slave_write_loop(dut, prefix, n=1):
    """Serve n write transactions on slave port `prefix`.
    Asserts awready+wready for 1 cycle after seeing awvalid+wvalid,
    then asserts bvalid until bready is seen."""
    for _ in range(n):
        for _ in range(200):
            await clk_edge(dut)
            await Timer(1, unit="ns")
            awv = int(getattr(dut, f"{prefix}_awvalid").value)
            wv  = int(getattr(dut, f"{prefix}_wvalid").value)
            if awv and wv:
                getattr(dut, f"{prefix}_awready").value = 1
                getattr(dut, f"{prefix}_wready").value  = 1
                await clk_edge(dut)
                await Timer(1, unit="ns")
                getattr(dut, f"{prefix}_awready").value = 0
                getattr(dut, f"{prefix}_wready").value  = 0
                getattr(dut, f"{prefix}_bvalid").value  = 1
                # Hold bvalid until bready seen; check at clk_edge + 1ns
                for _ in range(50):
                    await clk_edge(dut)
                    await Timer(1, unit="ns")
                    if int(getattr(dut, f"{prefix}_bready").value):
                        getattr(dut, f"{prefix}_bvalid").value = 0
                        break
                break


async def slave_read_once(dut, prefix, rdata=0xABCD1234):
    """Serve one read transaction on slave port `prefix`."""
    for _ in range(200):
        await clk_edge(dut)
        await Timer(1, unit="ns")
        if int(getattr(dut, f"{prefix}_arvalid").value):
            getattr(dut, f"{prefix}_arready").value = 1
            await clk_edge(dut)
            await Timer(1, unit="ns")
            getattr(dut, f"{prefix}_arready").value = 0
            getattr(dut, f"{prefix}_rdata").value   = rdata
            getattr(dut, f"{prefix}_rvalid").value  = 1
            getattr(dut, f"{prefix}_rresp").value   = 0
            for _ in range(50):
                await clk_edge(dut)
                await Timer(1, unit="ns")
                if int(getattr(dut, f"{prefix}_rready").value):
                    getattr(dut, f"{prefix}_rvalid").value = 0
                    return True
    return False


def start_write(dut, master, addr, data):
    getattr(dut, f"{master}_awaddr").value  = addr
    getattr(dut, f"{master}_awvalid").value = 1
    getattr(dut, f"{master}_wdata").value   = data
    getattr(dut, f"{master}_wstrb").value   = 0xF
    getattr(dut, f"{master}_wvalid").value  = 1
    getattr(dut, f"{master}_bready").value  = 1

def stop_write(dut, master):
    getattr(dut, f"{master}_awvalid").value = 0
    getattr(dut, f"{master}_wvalid").value  = 0


async def wait_bvalid(dut, master, timeout=100):
    """Poll bvalid AT rising edge (no Timer) so we see it before slave deasserts at +1ns."""
    for _ in range(timeout):
        await clk_edge(dut)
        if int(getattr(dut, f"{master}_bvalid").value):
            stop_write(dut, master)
            getattr(dut, f"{master}_bready").value = 0
            return True
    return False


@cocotb.test()
async def test_m0_m1_simultaneous_write_s0(dut):
    """M0 and M1 both write to S0 simultaneously; arbitration must serve both."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    cocotb.start_soon(slave_write_loop(dut, "s0", n=2))

    start_write(dut, "m0", 0x00000000, 0x11111111)
    start_write(dut, "m1", 0x00000004, 0x22222222)

    m0_done = m1_done = False
    for _ in range(160):
        await clk_edge(dut)
        # Poll at rising edge — before slave's Timer(1ns) fires and deasserts bvalid
        if int(dut.m0_bvalid.value) and not m0_done:
            m0_done = True
            stop_write(dut, "m0")
        if int(dut.m1_bvalid.value) and not m1_done:
            m1_done = True
            stop_write(dut, "m1")
        if m0_done and m1_done:
            break

    assert m0_done, "M0 never got BVALID for write to S0"
    assert m1_done, "M1 never got BVALID for write to S0"


@cocotb.test()
async def test_m0_write_m1_write_different_slaves(dut):
    """M0→S0 and M1→S1 simultaneously; different slaves allow parallel completion."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    cocotb.start_soon(slave_write_loop(dut, "s0", n=1))
    cocotb.start_soon(slave_write_loop(dut, "s1", n=1))

    start_write(dut, "m0", 0x00000010, 0xAAAAAAAA)
    start_write(dut, "m1", 0x10000010, 0xBBBBBBBB)

    m0_done = m1_done = False
    for _ in range(80):
        await clk_edge(dut)
        if int(dut.m0_bvalid.value) and not m0_done:
            m0_done = True
            stop_write(dut, "m0")
        if int(dut.m1_bvalid.value) and not m1_done:
            m1_done = True
            stop_write(dut, "m1")
        if m0_done and m1_done:
            break

    assert m0_done, "M0 write to S0 never completed"
    assert m1_done, "M1 write to S1 never completed"


@cocotb.test()
async def test_m0_read_while_m1_writes_same_slave(dut):
    """M1 writes to S0 while M0 reads from S0; both must complete."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    cocotb.start_soon(slave_write_loop(dut, "s0", n=1))
    cocotb.start_soon(slave_read_once(dut, "s0", rdata=0x42424242))

    start_write(dut, "m1", 0x00000020, 0xDEADBEEF)
    dut.m0_araddr.value  = 0x00000020
    dut.m0_arvalid.value = 1
    dut.m0_rready.value  = 1

    m0_read_done = m1_write_done = False
    for _ in range(120):
        await clk_edge(dut)
        if int(dut.m0_rvalid.value) and not m0_read_done:
            m0_read_done = True
            dut.m0_arvalid.value = 0
        if int(dut.m1_bvalid.value) and not m1_write_done:
            m1_write_done = True
            stop_write(dut, "m1")
        if m0_read_done and m1_write_done:
            break

    assert m0_read_done,  "M0 read from S0 never completed"
    assert m1_write_done, "M1 write to S0 never completed"


@cocotb.test()
async def test_m0_back_to_back_all_slaves(dut):
    """M0 writes S0 → S1 → S2 sequentially (no idle between transactions)."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)

    for slave, addr, data in [
        ("s0", 0x00000030, 0x11111111),
        ("s1", 0x10000030, 0x22222222),
        ("s2", 0x50000030, 0x33333333),
    ]:
        cocotb.start_soon(slave_write_loop(dut, slave, n=1))
        start_write(dut, "m0", addr, data)
        ok = await wait_bvalid(dut, "m0")
        assert ok, f"M0 back-to-back write to {slave} timed out"
        await clk_edge(dut)


@cocotb.test()
async def test_all_three_masters_to_same_slave(dut):
    """M0, M1, M2 all contend for S0; round-robin must serve all three."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    cocotb.start_soon(slave_write_loop(dut, "s0", n=3))

    start_write(dut, "m0", 0x00000040, 0xAAAAAAAA)
    start_write(dut, "m1", 0x00000044, 0xBBBBBBBB)
    start_write(dut, "m2", 0x00000048, 0xCCCCCCCC)

    done = {"m0": False, "m1": False, "m2": False}
    for _ in range(200):
        await clk_edge(dut)
        for m in ("m0", "m1", "m2"):
            if int(getattr(dut, f"{m}_bvalid").value) and not done[m]:
                done[m] = True
                stop_write(dut, m)
        if all(done.values()):
            break

    for m, ok in done.items():
        assert ok, f"{m} never got BVALID when all three masters contend for S0"


@cocotb.test()
async def test_m0_m1_reads_different_slaves(dut):
    """M0 reads S0 and M1 reads S1 simultaneously; both complete independently."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    cocotb.start_soon(slave_read_once(dut, "s0", rdata=0x01010101))
    cocotb.start_soon(slave_read_once(dut, "s1", rdata=0x02020202))

    dut.m0_araddr.value  = 0x00000050
    dut.m0_arvalid.value = 1
    dut.m0_rready.value  = 1
    dut.m1_araddr.value  = 0x10000050
    dut.m1_arvalid.value = 1
    dut.m1_rready.value  = 1

    m0_data = m1_data = None
    for _ in range(80):
        await clk_edge(dut)
        if int(dut.m0_rvalid.value) and m0_data is None:
            m0_data = int(dut.m0_rdata.value)
            dut.m0_arvalid.value = 0
        if int(dut.m1_rvalid.value) and m1_data is None:
            m1_data = int(dut.m1_rdata.value)
            dut.m1_arvalid.value = 0
        if m0_data is not None and m1_data is not None:
            break

    assert m0_data == 0x01010101, f"M0 read S0: expected 0x01010101, got {m0_data:#010x}"
    assert m1_data == 0x02020202, f"M1 read S1: expected 0x02020202, got {m1_data:#010x}"
