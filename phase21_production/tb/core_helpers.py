"""Shared cocotb helpers for Phase 21 riscv_core tests.

Provides:
  reset_dut(dut)                     — full reset with all inputs driven
  run_program(dut, imem, dmem, ...)  — drive memory interfaces for N cycles
  read_registers(dut)                — halt core, read all 32 GPRs via debug port
"""
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import cocotb

CLK_NS = 10
NOP    = 0x00000013  # ADDI x0, x0, 0
DONE_ADDR = 0x1000   # byte address of done sentinel


def _u32(sig):
    try:
        return int(sig.value) & 0xFFFFFFFF
    except Exception:
        return 0


async def reset_dut(dut):
    """Assert rst for 5 cycles, then release. Drive all optional inputs to 0."""
    dut.rst.value               = 1
    dut.imem_rdata_i.value      = NOP
    dut.dmem_rdata_i.value      = 0
    dut.dmem_stall_i.value      = 0
    dut.icache_stall_i.value    = 0
    dut.m_ext_irq_i.value       = 0
    dut.m_timer_irq_i.value     = 0
    dut.m_sw_irq_i.value        = 0
    dut.dbg_halt_req_i.value    = 0
    dut.dbg_resume_req_i.value  = 0
    dut.dbg_rf_addr_i.value     = 0
    dut.dbg_rf_wdata_i.value    = 0
    dut.dbg_rf_we_i.value       = 0
    dut.dbg_imem_ovr_en_i.value = 0
    dut.dbg_imem_ovr_data_i.value = 0
    dut.dbg_jump_en_i.value     = 0
    dut.dbg_jump_target_i.value = 0
    dut.trigger_halt_i.value    = 0
    dut.tselect_rd_i.value      = 0
    dut.tdata1_rd_i.value       = 0
    dut.tdata2_rd_i.value       = 0
    for _ in range(5):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")


async def run_program(dut, imem: dict, dmem: dict, cycles: int = 100,
                      stop_on_done: bool = True):
    """Drive single-cycle imem + dmem for up to `cycles` clocks.

    Returns True if the done sentinel (SW to DONE_ADDR) was detected.
    """
    done = False
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for _ in range(cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        iaddr = _u32(dut.imem_addr_o) >> 2
        dut.imem_rdata_i.value = imem.get(iaddr, NOP)

        daddr = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1:
            be    = _u32(dut.dmem_be_o)
            wdata = _u32(dut.dmem_wdata_o)
            waddr = daddr >> 2
            word  = dmem.get(waddr, 0)
            for i in range(4):
                if (be >> i) & 1:
                    word = (word & ~(0xFF << (8*i))) | (((wdata >> (8*i)) & 0xFF) << (8*i))
            dmem[waddr] = word
            if daddr == DONE_ADDR:
                done = True
                if stop_on_done:
                    # Drain pipeline: 5 more cycles before halting
                    for _ in range(5):
                        await RisingEdge(dut.clk)
                        await Timer(1, unit="ns")
                        ia = _u32(dut.imem_addr_o) >> 2
                        dut.imem_rdata_i.value = imem.get(ia, NOP)
                    return done

        dut.dmem_rdata_i.value = dmem.get(daddr >> 2, 0)

    return done


async def read_registers(dut):
    """Halt the core via debug interface and read all 32 GPRs.

    Returns list of 32 u32 values [x0, x1, ..., x31].
    """
    dut.dbg_halt_req_i.value = 1
    for _ in range(30):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if _u32(dut.dbg_halted_o):
            break

    regs = []
    for r in range(32):
        dut.dbg_rf_addr_i.value = r
        await Timer(1, unit="ns")
        regs.append(_u32(dut.dbg_rf_rdata_o))

    dut.dbg_halt_req_i.value = 0
    return regs


def start_core(dut):
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
