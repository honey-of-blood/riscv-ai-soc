import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

@cocotb.test()
async def test_debug2(dut):
    """Check: does wr_busy[0] become 1, and what is m_awready?"""
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

    # Set awready=1 for all slaves
    dut.s_awready.value = 0xF
    dut.s_wready.value  = 0xF
    dut.s_arready.value = 0xF

    # Set M0 write to slave 0
    dut.m_awaddr.value = 0x00000010
    dut.m_awvalid.value = 0x1
    dut.m_wdata.value = 0xDEADBEEF
    dut.m_wstrb.value = 0xF
    dut.m_wvalid.value = 0x1
    dut.m_bready.value = 0x1

    for i in range(5):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        cocotb.log.info(f"C{i}: awvalid={int(dut.m_awvalid.value)} awready={int(dut.m_awready.value)} "
                        f"sawvalid={int(dut.s_awvalid.value)} sawready={int(dut.s_awready.value)} "
                        f"swvalid={int(dut.s_wvalid.value)} swready={int(dut.s_wready.value)} "
                        f"bvalid={int(dut.m_bvalid.value)} sbvalid={int(dut.s_bvalid.value)}")
        if int(dut.m_awready.value):
            dut.m_awvalid.value = 0
            cocotb.log.info("M0 AWREADY seen!")
        if int(dut.m_wready.value):
            dut.m_wvalid.value = 0
            cocotb.log.info("M0 WREADY seen!")

    # Now set s_bvalid to see if B gets routed
    dut.s_bvalid.value = 0x1  # slave 0 asserts bvalid
    await Timer(1, unit="ns")
    cocotb.log.info(f"After s_bvalid=1: m_bvalid={int(dut.m_bvalid.value)} m_bresp={int(dut.m_bresp.value)}")
