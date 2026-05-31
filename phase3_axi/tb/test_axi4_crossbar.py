"""
cocotb tests for axi4_crossbar.sv — 3-master × 3-slave AXI4-Lite crossbar.

Address map (decoded on addr[31:16]):
  Slave 0 — 0x0000_xxxx  SRAM
  Slave 1 — 0x1000_xxxx  APB bridge
  Slave 2 — 0x5000_xxxx  AI accelerator MMIO

Tests:
  1. m0_write_s0  — master 0 writes to slave 0 (SRAM region)
  2. m0_write_s1  — master 0 writes to slave 1 (APB region)
  3. m0_write_s2  — master 0 writes to slave 2 (accel region)
  4. m0_read_s0   — master 0 reads from slave 0
  5. m0_read_s1   — master 0 reads from slave 1
  6. m0_read_s2   — master 0 reads from slave 2
  7. m1_write_s0  — master 1 can reach slave 0
  8. m2_write_s0  — master 2 can reach slave 0
  9. addr_decode  — distinct slave AWVALID patterns for all 3 addresses
 10. idle_no_valid — no master drives valid → slave sees no valid
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer

# ── Timing helpers ───────────────────────────────────────────────────────────

async def clk_edge(dut):
    await RisingEdge(dut.clk)

async def wait_ns(n=1):
    await Timer(n, unit="ns")

# ── Slave responder — ACKs a single write or read on a slave port ─────────────

async def slave_ack_write(dut, prefix, rdata=0xDEAD_BEEF):
    """Wait for slave AWVALID+WVALID, assert AWREADY+WREADY, then BVALID."""
    awv = getattr(dut, f"{prefix}_awvalid")
    wv  = getattr(dut, f"{prefix}_wvalid")
    awr = getattr(dut, f"{prefix}_awready")
    wr  = getattr(dut, f"{prefix}_wready")
    bv  = getattr(dut, f"{prefix}_bvalid")
    br  = getattr(dut, f"{prefix}_bready")
    bp  = getattr(dut, f"{prefix}_bresp")
    awr.value = 0;  wr.value = 0;  bv.value = 0;  bp.value = 0

    # Wait for AW + W valid
    for _ in range(50):
        await clk_edge(dut)
        if awv.value and wv.value:
            awr.value = 1;  wr.value = 1
            await clk_edge(dut)
            awr.value = 0;  wr.value = 0
            bp.value = 0;   bv.value = 1
            # Wait for BREADY
            for _ in range(50):
                await clk_edge(dut)
                if br.value:
                    bv.value = 0
                    return
            return

async def slave_ack_read(dut, prefix, rdata=0xABCD1234):
    """Wait for slave ARVALID, respond with RVALID+data."""
    arv = getattr(dut, f"{prefix}_arvalid")
    arr = getattr(dut, f"{prefix}_arready")
    rv  = getattr(dut, f"{prefix}_rvalid")
    rd  = getattr(dut, f"{prefix}_rdata")
    rr  = getattr(dut, f"{prefix}_rready")
    rp  = getattr(dut, f"{prefix}_rresp")
    arr.value = 0;  rv.value = 0;  rd.value = 0;  rp.value = 0

    for _ in range(50):
        await clk_edge(dut)
        if arv.value:
            arr.value = 1
            await clk_edge(dut)
            arr.value = 0
            rd.value = rdata;  rp.value = 0;  rv.value = 1
            for _ in range(50):
                await clk_edge(dut)
                if rr.value:
                    rv.value = 0
                    return
            return

# ── Master drive helpers ─────────────────────────────────────────────────────

def idle_all_masters(dut):
    for m in ("m0", "m1", "m2"):
        for sig in ("awvalid", "wvalid", "bready", "arvalid", "rready"):
            getattr(dut, f"{m}_{sig}").value = 0
        dut.__dict__.get(f"{m}_awaddr", None)
        try: getattr(dut, f"{m}_awaddr").value  = 0
        except: pass
        try: getattr(dut, f"{m}_wdata").value   = 0
        except: pass
        try: getattr(dut, f"{m}_wstrb").value   = 0
        except: pass
        try: getattr(dut, f"{m}_araddr").value  = 0
        except: pass

def idle_all_slaves(dut):
    for s, p in [("s0", "s0"), ("s1", "s1"), ("s2", "s2")]:
        for sig in ("awready", "wready", "bresp", "bvalid",
                    "arready", "rdata", "rresp", "rvalid"):
            try: getattr(dut, f"{p}_{sig}").value = 0
            except: pass

async def drive_write(dut, master, addr, data, strb=0xF):
    """Drive a write on the given master port; returns without waiting for slave."""
    getattr(dut, f"{master}_awaddr").value  = addr
    getattr(dut, f"{master}_awvalid").value = 1
    getattr(dut, f"{master}_wdata").value   = data
    getattr(dut, f"{master}_wstrb").value   = strb
    getattr(dut, f"{master}_wvalid").value  = 1
    getattr(dut, f"{master}_bready").value  = 1

async def drive_read(dut, master, addr):
    getattr(dut, f"{master}_araddr").value  = addr
    getattr(dut, f"{master}_arvalid").value = 1
    getattr(dut, f"{master}_rready").value  = 1

async def release_write(dut, master):
    getattr(dut, f"{master}_awvalid").value = 0
    getattr(dut, f"{master}_wvalid").value  = 0

async def release_read(dut, master):
    getattr(dut, f"{master}_arvalid").value = 0

# ── Clock + Reset ────────────────────────────────────────────────────────────

async def reset_dut(dut, cycles=4):
    dut.rst_n.value = 0
    idle_all_masters(dut)
    idle_all_slaves(dut)
    for _ in range(cycles):
        await clk_edge(dut)
    dut.rst_n.value = 1

async def gen_clock(dut):
    """10 ns period clock."""
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")

# ── Slave port name mapping ───────────────────────────────────────────────────
# Crossbar exposes s0/s1/s2 slave ports.
SLAVE_PORTS = {0x00000000: "s0", 0x10000000: "s1", 0x50000000: "s2"}

# ── Tests ─────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_m0_write_s0(dut):
    """Master 0 write to slave 0 (SRAM region 0x0000_0000)."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    cocotb.start_soon(slave_ack_write(dut, "s0"))
    await drive_write(dut, "m0", 0x00000010, 0xDEADBEEF)
    # Check slave 0 sees AWVALID within 10 cycles
    for _ in range(10):
        await clk_edge(dut)
        if dut.s0_awvalid.value:
            assert int(dut.s0_awaddr.value) == 0x00000010, \
                f"s0_awaddr={hex(int(dut.s0_awaddr.value))}"
            break
    else:
        assert False, "s0 never saw AWVALID"
    # Wait for BVALID back to master
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_bvalid.value:
            assert int(dut.m0_bresp.value) == 0
            break
    else:
        assert False, "m0 never got BVALID"
    await release_write(dut, "m0")


@cocotb.test()
async def test_m0_write_s1(dut):
    """Master 0 write to slave 1 (APB region 0x1000_0000)."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    cocotb.start_soon(slave_ack_write(dut, "s1"))
    await drive_write(dut, "m0", 0x10000020, 0x12345678)
    for _ in range(10):
        await clk_edge(dut)
        if dut.s1_awvalid.value:
            break
    else:
        assert False, "s1 never saw AWVALID for 0x1000_xxxx address"
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_bvalid.value:
            break
    else:
        assert False, "m0 never got BVALID from s1"
    await release_write(dut, "m0")


@cocotb.test()
async def test_m0_write_s2(dut):
    """Master 0 write to slave 2 (accel region 0x5000_0000)."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    cocotb.start_soon(slave_ack_write(dut, "s2"))
    await drive_write(dut, "m0", 0x50000004, 0xCAFEBABE)
    for _ in range(10):
        await clk_edge(dut)
        if dut.s2_awvalid.value:
            break
    else:
        assert False, "s2 never saw AWVALID for 0x5000_xxxx address"
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_bvalid.value:
            break
    else:
        assert False, "m0 never got BVALID from s2"
    await release_write(dut, "m0")


@cocotb.test()
async def test_m0_read_s0(dut):
    """Master 0 reads from slave 0 — checks returned data."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    expected = 0xA5A5A5A5
    cocotb.start_soon(slave_ack_read(dut, "s0", rdata=expected))
    await drive_read(dut, "m0", 0x00000040)
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_rvalid.value:
            assert int(dut.m0_rdata.value) == expected, \
                f"rdata={hex(int(dut.m0_rdata.value))} expected={hex(expected)}"
            assert int(dut.m0_rresp.value) == 0
            break
    else:
        assert False, "m0 never got RVALID from s0"
    await release_read(dut, "m0")


@cocotb.test()
async def test_m0_read_s1(dut):
    """Master 0 reads from slave 1."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    expected = 0x11223344
    cocotb.start_soon(slave_ack_read(dut, "s1", rdata=expected))
    await drive_read(dut, "m0", 0x10000008)
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_rvalid.value:
            assert int(dut.m0_rdata.value) == expected
            break
    else:
        assert False, "m0 never got RVALID from s1"
    await release_read(dut, "m0")


@cocotb.test()
async def test_m0_read_s2(dut):
    """Master 0 reads from slave 2."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    expected = 0xFEEDFACE
    cocotb.start_soon(slave_ack_read(dut, "s2", rdata=expected))
    await drive_read(dut, "m0", 0x50000000)
    for _ in range(30):
        await clk_edge(dut)
        if dut.m0_rvalid.value:
            assert int(dut.m0_rdata.value) == expected
            break
    else:
        assert False, "m0 never got RVALID from s2"
    await release_read(dut, "m0")


@cocotb.test()
async def test_m1_write_s0(dut):
    """Master 1 can reach slave 0."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    cocotb.start_soon(slave_ack_write(dut, "s0"))
    await drive_write(dut, "m1", 0x00000100, 0x11111111)
    for _ in range(10):
        await clk_edge(dut)
        if dut.s0_awvalid.value:
            break
    else:
        assert False, "s0 never saw AWVALID from m1"
    for _ in range(30):
        await clk_edge(dut)
        if dut.m1_bvalid.value:
            break
    else:
        assert False, "m1 never got BVALID"
    await release_write(dut, "m1")


@cocotb.test()
async def test_m2_write_s0(dut):
    """Master 2 can reach slave 0."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    cocotb.start_soon(slave_ack_write(dut, "s0"))
    await drive_write(dut, "m2", 0x00000200, 0x22222222)
    for _ in range(10):
        await clk_edge(dut)
        if dut.s0_awvalid.value:
            break
    else:
        assert False, "s0 never saw AWVALID from m2"
    for _ in range(30):
        await clk_edge(dut)
        if dut.m2_bvalid.value:
            break
    else:
        assert False, "m2 never got BVALID"
    await release_write(dut, "m2")


@cocotb.test()
async def test_addr_decode(dut):
    """Address decode: three writes to three regions hit three different slaves."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)

    test_cases = [
        (0x00000000, "s0", "s1", "s2"),
        (0x10000000, "s1", "s0", "s2"),
        (0x50000000, "s2", "s0", "s1"),
    ]

    for addr, hit_slave, miss1, miss2 in test_cases:
        idle_all_masters(dut)
        idle_all_slaves(dut)
        await clk_edge(dut)

        cocotb.start_soon(slave_ack_write(dut, hit_slave))
        await drive_write(dut, "m0", addr, 0xDEAD)

        hit_seen = False
        for _ in range(15):
            await clk_edge(dut)
            if getattr(dut, f"{hit_slave}_awvalid").value:
                hit_seen = True
                # Verify the other slaves are NOT being accessed
                assert not getattr(dut, f"{miss1}_awvalid").value, \
                    f"addr {hex(addr)}: unexpected AWVALID on {miss1}"
                assert not getattr(dut, f"{miss2}_awvalid").value, \
                    f"addr {hex(addr)}: unexpected AWVALID on {miss2}"
                break
        assert hit_seen, f"addr {hex(addr)}: {hit_slave} never got AWVALID"
        await release_write(dut, "m0")
        for _ in range(30):
            await clk_edge(dut)
            if dut.m0_bvalid.value:
                break


@cocotb.test()
async def test_idle_no_valid(dut):
    """With all masters idle, all slave AWVALID and ARVALID are 0 after reset."""
    cocotb.start_soon(gen_clock(dut))
    await reset_dut(dut)
    idle_all_masters(dut)
    idle_all_slaves(dut)

    # Observe for 5 cycles — no spurious valids
    for _ in range(5):
        await clk_edge(dut)
        await wait_ns(1)
        for s in ("s0", "s1", "s2"):
            assert not getattr(dut, f"{s}_awvalid").value, \
                f"{s}_awvalid asserted without master request"
            assert not getattr(dut, f"{s}_arvalid").value, \
                f"{s}_arvalid asserted without master request"
