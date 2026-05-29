"""
Timer unit tests.

Tests:
  1. counter_increments  — enable timer, read MTIME_LO twice, verify it advances
  2. mtimecmp_readwrite  — write MTIMECMP_LO/HI, read back
  3. mtip_fires          — set MTIMECMP to near-current value, enable IRQ, verify mtip
  4. mtip_rearm          — after interrupt, write new MTIMECMP in future, verify mtip clears
  5. ctrl_disable        — timer stops incrementing when CTRL[0]=0
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_NS = 10

def _u32(sig):
    try:    return int(sig.value) & 0xFFFF_FFFF
    except: return 0

async def apb_write(dut, addr, data):
    await RisingEdge(dut.clk)
    dut.paddr.value = addr; dut.pwdata.value = data
    dut.pwrite.value = 1;   dut.psel.value = 1; dut.penable.value = 0
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    dut.psel.value = 0; dut.penable.value = 0; dut.pwrite.value = 0

async def apb_read(dut, addr):
    await RisingEdge(dut.clk)
    dut.paddr.value = addr; dut.pwrite.value = 0
    dut.psel.value = 1; dut.penable.value = 0
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    val = _u32(dut.prdata)
    dut.psel.value = 0; dut.penable.value = 0
    return val

async def reset_dut(dut):
    dut.rst_n.value = 0; dut.psel.value = 0; dut.penable.value = 0
    dut.pwrite.value = 0; dut.paddr.value = 0; dut.pwdata.value = 0
    for _ in range(4): await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)

@cocotb.test()
async def test_counter_increments(dut):
    """Enable timer (CTRL=0x1), read MTIME_LO twice; second read must be larger."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x10, 0x1)     # CTRL: enable
    t0 = await apb_read(dut, 0x00)
    for _ in range(10): await RisingEdge(dut.clk)
    t1 = await apb_read(dut, 0x00)
    assert t1 > t0, f"MTIME_LO should increase: t0={t0}, t1={t1}"

@cocotb.test()
async def test_mtimecmp_readwrite(dut):
    """Write 0xDEAD_BEEF / 0xCAFE_BABE to MTIMECMP, read back both halves."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x08, 0xDEAD_BEEF)
    await apb_write(dut, 0x0C, 0xCAFE_BABE)
    lo = await apb_read(dut, 0x08)
    hi = await apb_read(dut, 0x0C)
    assert lo == 0xDEAD_BEEF, f"MTIMECMP_LO: expected 0xDEADBEEF, got {lo:#010x}"
    assert hi == 0xCAFE_BABE, f"MTIMECMP_HI: expected 0xCAFEBABE, got {hi:#010x}"

@cocotb.test()
async def test_mtip_fires(dut):
    """Set MTIMECMP just ahead of current MTIME; enable IRQ; verify mtip asserts."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x10, 0x1)          # enable (no IRQ yet)
    # Read current time
    t_now = await apb_read(dut, 0x00)
    # Set compare value 20 ticks ahead
    await apb_write(dut, 0x08, t_now + 20)
    await apb_write(dut, 0x0C, 0)            # high half = 0
    await apb_write(dut, 0x10, 0x3)          # enable + irq_en
    # Wait for compare to fire
    for _ in range(30): await RisingEdge(dut.clk)
    assert _u32(dut.mtip) == 1, "mtip should assert when mtime >= mtimecmp"

@cocotb.test()
async def test_mtip_rearm(dut):
    """After mtip fires, write MTIMECMP far in the future to clear mtip."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x08, 5)     # fire almost immediately
    await apb_write(dut, 0x0C, 0)
    await apb_write(dut, 0x10, 0x3)   # enable + irq_en
    for _ in range(15): await RisingEdge(dut.clk)
    assert _u32(dut.mtip) == 1, "mtip should have fired"
    # Re-arm: move compare far into future
    await apb_write(dut, 0x08, 0xFFFF_FF00)
    await apb_write(dut, 0x0C, 0xFFFF_FFFF)
    await Timer(CLK_NS * 3, unit="ns")
    assert _u32(dut.mtip) == 0, "mtip should clear after re-arm"

@cocotb.test()
async def test_ctrl_disable(dut):
    """Disable timer (CTRL[0]=0); counter must stop advancing."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x10, 0x1)   # enable briefly
    for _ in range(10): await RisingEdge(dut.clk)
    await apb_write(dut, 0x10, 0x0)   # disable
    t0 = await apb_read(dut, 0x00)
    for _ in range(20): await RisingEdge(dut.clk)
    t1 = await apb_read(dut, 0x00)
    assert t0 == t1, f"disabled timer should not advance: t0={t0}, t1={t1}"
