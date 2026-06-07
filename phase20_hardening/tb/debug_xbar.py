import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

@cocotb.test()
async def test_debug(dut):
    """Debug: check address decode and arbiter signals."""
    cocotb.start_soon(Clock(dut.clk, 10, units="ns").start())
    dut.rst_n.value = 0
    dut.m_awvalid.value = 0; dut.m_awaddr.value = 0
    dut.m_wvalid.value = 0; dut.m_wdata.value = 0; dut.m_wstrb.value = 0
    dut.m_bready.value = 0
    dut.m_arvalid.value = 0; dut.m_araddr.value = 0; dut.m_rready.value = 0
    dut.s_awready.value = 0xF  # all slaves ready
    dut.s_wready.value = 0xF
    dut.s_bvalid.value = 0; dut.s_bresp.value = 0
    dut.s_arready.value = 0xF
    dut.s_rvalid.value = 0; dut.s_rdata.value = 0; dut.s_rresp.value = 0
    await Timer(50, unit="ns")
    dut.rst_n.value = 1
    await Timer(10, unit="ns")

    # Set M0 AW to slave 0 (addr 0x0000_0010)
    dut.m_awaddr.value = 0x00000010   # M0 addr
    dut.m_awvalid.value = 0x1          # M0 valid
    dut.m_wdata.value = 0xDEADBEEF
    dut.m_wstrb.value = 0xF
    dut.m_wvalid.value = 0x1
    dut.m_bready.value = 0x1

    for i in range(10):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        cocotb.log.info(f"Cycle {i}: m_awvalid={int(dut.m_awvalid.value):#x} "
                        f"m_awready={int(dut.m_awready.value):#x} "
                        f"s_awvalid={int(dut.s_awvalid.value):#x} "
                        f"s_awready={int(dut.s_awready.value):#x} "
                        f"m_bvalid={int(dut.m_bvalid.value):#x} "
                        f"s_bvalid={int(dut.s_bvalid.value):#x}")
