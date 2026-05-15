"""
cocotb unit tests for axi_apb_bridge.sv
Tests:
  1. single_write       – AXI write → APB SETUP/ENABLE → B response
  2. single_read        – AXI read  → APB SETUP/ENABLE → R response
  3. multi_cycle_ready  – PREADY de-asserted 2 extra cycles
  4. write_then_read    – sequential write + read transactions
  5. slverr_propagate   – PSLVERR=1 maps to BRESP/RRESP=2 (SLVERR)
  6. back_to_back       – 3 writes in a row
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer


# ─── Clock ───────────────────────────────────────────────────────────────────

async def gen_clk(dut):
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")


# ─── APB slave BFM ───────────────────────────────────────────────────────────

class ApbSlave:
    """Minimal APB slave BFM running as a background coroutine."""
    def __init__(self, dut, mem=None, wait_cycles=0, slverr=False):
        self.dut        = dut
        self.mem        = mem if mem is not None else {}
        self.wait_cycles = wait_cycles
        self.slverr     = slverr
        self._task      = None

    def start(self):
        self._task = cocotb.start_soon(self._run())

    async def _run(self):
        dut = self.dut
        while True:
            await RisingEdge(dut.clk)
            if dut.p_psel.value and dut.p_penable.value:
                # Extra wait cycles
                for _ in range(self.wait_cycles):
                    dut.p_pready.value  = 0
                    dut.p_pslverr.value = 0
                    await RisingEdge(dut.clk)
                addr = int(dut.p_paddr.value)
                if dut.p_pwrite.value:
                    self.mem[addr] = int(dut.p_pwdata.value)
                    dut.p_prdata.value = 0
                else:
                    dut.p_prdata.value = self.mem.get(addr, 0)
                dut.p_pready.value  = 1
                dut.p_pslverr.value = 1 if self.slverr else 0
            else:
                dut.p_pready.value  = 0
                dut.p_pslverr.value = 0


# ─── AXI4-Lite master BFMs ───────────────────────────────────────────────────

async def axi_write(dut, addr, data, strb=0xF):
    dut.s_awaddr.value  = addr
    dut.s_awvalid.value = 1
    dut.s_wdata.value   = data
    dut.s_wstrb.value   = strb
    dut.s_wvalid.value  = 1
    dut.s_bready.value  = 1
    await RisingEdge(dut.clk)
    dut.s_awvalid.value = 0
    dut.s_wvalid.value  = 0
    while not dut.s_bvalid.value:
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    resp = int(dut.s_bresp.value)
    await RisingEdge(dut.clk)
    dut.s_bready.value = 0
    return resp


async def axi_read(dut, addr):
    dut.s_araddr.value  = addr
    dut.s_arvalid.value = 1
    dut.s_rready.value  = 1
    await RisingEdge(dut.clk)
    dut.s_arvalid.value = 0
    while not dut.s_rvalid.value:
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    data = int(dut.s_rdata.value)
    resp = int(dut.s_rresp.value)
    await RisingEdge(dut.clk)
    dut.s_rready.value = 0
    return data, resp


async def reset(dut):
    dut.rst_n.value     = 0
    dut.s_awvalid.value = 0
    dut.s_wvalid.value  = 0
    dut.s_bready.value  = 0
    dut.s_arvalid.value = 0
    dut.s_rready.value  = 0
    dut.s_awaddr.value  = 0
    dut.s_wdata.value   = 0
    dut.s_wstrb.value   = 0
    dut.s_araddr.value  = 0
    dut.p_pready.value  = 0
    dut.p_prdata.value  = 0
    dut.p_pslverr.value = 0
    for _ in range(3):
        await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


# ─── Tests ───────────────────────────────────────────────────────────────────

@cocotb.test()
async def single_write(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem).start()
    resp = await axi_write(dut, addr=0x1000_0000, data=0xABCD_1234)
    assert resp == 0, f"Expected OKAY, got {resp}"
    assert mem.get(0x1000_0000) == 0xABCD_1234, "APB write not stored"


@cocotb.test()
async def single_read(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {0x1000_0004: 0xDEAD_BEEF}
    ApbSlave(dut, mem=mem).start()
    data, resp = await axi_read(dut, addr=0x1000_0004)
    assert resp == 0, f"Expected OKAY, got {resp}"
    assert data == 0xDEAD_BEEF, f"Expected 0xDEADBEEF, got 0x{data:08X}"


@cocotb.test()
async def multi_cycle_ready(dut):
    """APB slave holds PREADY low for 2 extra cycles."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem, wait_cycles=2).start()
    resp = await axi_write(dut, addr=0x1000_0008, data=0x5A5A_5A5A)
    assert resp == 0
    assert mem.get(0x1000_0008) == 0x5A5A_5A5A


@cocotb.test()
async def write_then_read(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem).start()
    await axi_write(dut, addr=0x1000_0010, data=0xCAFE_CAFE)
    data, resp = await axi_read(dut, addr=0x1000_0010)
    assert resp == 0
    assert data == 0xCAFE_CAFE, f"0x{data:08X}"


@cocotb.test()
async def slverr_propagate(dut):
    """PSLVERR=1 should produce BRESP=2 (SLVERR) on writes and RRESP=2 on reads."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    ApbSlave(dut, slverr=True).start()
    resp = await axi_write(dut, addr=0x1000_0020, data=0x1)
    assert resp == 2, f"Expected SLVERR(2), got {resp}"
    _, rresp = await axi_read(dut, addr=0x1000_0020)
    assert rresp == 2, f"Expected SLVERR(2) on read, got {rresp}"


@cocotb.test()
async def back_to_back(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem).start()
    pairs = [(0x1000_0030, 0x1111_0000), (0x1000_0034, 0x2222_0000), (0x1000_0038, 0x3333_0000)]
    for addr, val in pairs:
        resp = await axi_write(dut, addr=addr, data=val)
        assert resp == 0
    for addr, expected in pairs:
        data, resp = await axi_read(dut, addr=addr)
        assert resp == 0
        assert data == expected, f"addr=0x{addr:X}: 0x{data:08X}"


@cocotb.test()
async def long_pready_wait(dut):
    """APB slave holds PREADY low for 7 extra cycles — tests bridge FSM patience."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem, wait_cycles=7).start()
    resp = await axi_write(dut, addr=0x1000_0040, data=0xFEED_FACE)
    assert resp == 0, f"Expected OKAY on write, got {resp}"
    assert mem.get(0x1000_0040) == 0xFEED_FACE, "APB write not stored"
    data, resp = await axi_read(dut, addr=0x1000_0040)
    assert resp == 0, f"Expected OKAY on read, got {resp}"
    assert data == 0xFEED_FACE, f"Expected 0xFEEDFACE, got 0x{data:08X}"


@cocotb.test()
async def multi_cycle_ready_read(dut):
    """Read with 3 extra PREADY wait cycles."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {0x1000_0050: 0x9876_5432}
    ApbSlave(dut, mem=mem, wait_cycles=3).start()
    data, resp = await axi_read(dut, addr=0x1000_0050)
    assert resp == 0, f"Expected OKAY, got {resp}"
    assert data == 0x9876_5432, f"Expected 0x98765432, got 0x{data:08X}"


@cocotb.test()
async def read_slverr(dut):
    """Read SLVERR: PSLVERR=1 on read → RRESP=2 (isolated from write path)."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    ApbSlave(dut, slverr=True).start()
    _, rresp = await axi_read(dut, addr=0x1000_0060)
    assert rresp == 2, f"Expected SLVERR(2) on read, got {rresp}"


@cocotb.test()
async def alternating_rw_stress(dut):
    """Interleaved write+read pairs to 4 different addresses."""
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    mem = {}
    ApbSlave(dut, mem=mem).start()
    pairs = [
        (0x1000_0070, 0xAAAA_0001),
        (0x1000_0074, 0xBBBB_0002),
        (0x1000_0078, 0xCCCC_0003),
        (0x1000_007C, 0xDDDD_0004),
    ]
    for addr, val in pairs:
        resp = await axi_write(dut, addr=addr, data=val)
        assert resp == 0, f"Write resp wrong at 0x{addr:X}: {resp}"
        data, resp = await axi_read(dut, addr=addr)
        assert resp == 0, f"Read resp wrong at 0x{addr:X}: {resp}"
        assert data == val, f"addr=0x{addr:X}: expected 0x{val:08X}, got 0x{data:08X}"
