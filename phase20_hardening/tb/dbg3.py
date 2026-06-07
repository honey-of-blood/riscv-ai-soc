import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

NS = 4

def get_s_bit(signal, s):
    return (int(signal.value) >> s) & 1

def set_s_bit(signal, s, val):
    cur = int(signal.value)
    signal.value = (cur | (1<<s)) if val else (cur & ~(1<<s))

def set_s_field(signal, s, width, val):
    cur = int(signal.value)
    mask = ((1<<width)-1) << (s*width)
    signal.value = (cur & ~mask) | ((val & ((1<<width)-1)) << (s*width))

def get_s_field(signal, s, width):
    return (int(signal.value) >> (s*width)) & ((1<<width)-1)

async def _slave(dut, s, mem):
    set_s_bit(dut.s_awready, s, 1)
    set_s_bit(dut.s_wready,  s, 1)
    set_s_bit(dut.s_arready, s, 1)
    while True:
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        aw = get_s_bit(dut.s_awvalid, s)
        w  = get_s_bit(dut.s_wvalid,  s)
        if aw and w:
            addr  = get_s_field(dut.s_awaddr, s, 32)
            wdata = get_s_field(dut.s_wdata,  s, 32)
            mem[addr & 0xFFFF] = wdata
            await RisingEdge(dut.clk)
            cocotb.log.info(f"Slave {s}: sending BVALID")
            set_s_bit(dut.s_bvalid, s, 1)
            for _ in range(50):
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                if get_s_bit(dut.s_bready, s):
                    break
            set_s_bit(dut.s_bvalid, s, 0)

@cocotb.test()
async def test_debug3(dut):
    """Check slave task + crossbar interaction."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.rst_n.value = 0
    for sig in [dut.m_awvalid, dut.m_awaddr, dut.m_wvalid, dut.m_wdata, dut.m_wstrb,
                dut.m_bready, dut.m_arvalid, dut.m_araddr, dut.m_rready]:
        sig.value = 0
    dut.s_awready.value = 0; dut.s_wready.value = 0; dut.s_bvalid.value = 0
    dut.s_bresp.value = 0; dut.s_arready.value = 0; dut.s_rvalid.value = 0
    dut.s_rdata.value = 0; dut.s_rresp.value = 0
    await Timer(50, unit="ns")
    dut.rst_n.value = 1
    await Timer(10, unit="ns")

    mems = [{} for _ in range(NS)]
    for s in range(NS): cocotb.start_soon(_slave(dut, s, mems[s]))
    await Timer(20, unit="ns")  # 2 clock cycles

    cocotb.log.info(f"After init: s_awready={int(dut.s_awready.value):#x}")

    # Drive write from M0 to S0
    dut.m_awaddr.value = 0x00000010
    dut.m_awvalid.value = 1
    dut.m_wdata.value = 0xDEADBEEF
    dut.m_wstrb.value = 0xF
    dut.m_wvalid.value = 1
    dut.m_bready.value = 1

    for i in range(20):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        aw_rdy = int(dut.m_awready.value)
        w_rdy  = int(dut.m_wready.value)
        bval   = int(dut.m_bvalid.value)
        saw    = int(dut.s_awvalid.value)
        saw_r  = int(dut.s_awready.value)
        sbval  = int(dut.s_bvalid.value)
        cocotb.log.info(f"C{i}: awrdy={aw_rdy} wrdy={w_rdy} bval={bval} saw={saw} saw_r={saw_r:#x} sbval={sbval}")
        if aw_rdy: dut.m_awvalid.value = 0
        if w_rdy:  dut.m_wvalid.value = 0
        if bval:
            cocotb.log.info(f"BVALID received! bresp={int(dut.m_bresp.value)}")
            dut.m_bready.value = 0
            break
    else:
        assert False, "BVALID timeout"
