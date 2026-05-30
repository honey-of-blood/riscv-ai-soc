"""
CLINT unit tests (standalone — timer inputs driven by testbench).

Tests:
  1. msip_readwrite   — write 1 to MSIP, read back; write 0, read back
  2. msip_output      — verify msip_o port reflects MSIP register
  3. mtime_passthru   — drive mtime_lo_i/mtime_hi_i, read via MTIME_LO/HI registers
  4. mtimecmp_proxy   — write MTIMECMP_LO/HI, verify mtimecmp_lo_o/mtimecmp_hi_o
  5. mtimecmp_wr_pulse — write MTIMECMP_LO, verify mtimecmp_wr_o pulses for one cycle
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
    dut.paddr.value   = addr
    dut.pwdata.value  = data
    dut.pwrite.value  = 1
    dut.psel.value    = 1
    dut.penable.value = 0
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    dut.psel.value    = 0
    dut.penable.value = 0
    dut.pwrite.value  = 0

async def apb_read(dut, addr):
    await RisingEdge(dut.clk)
    dut.paddr.value   = addr
    dut.pwrite.value  = 0
    dut.psel.value    = 1
    dut.penable.value = 0
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    val = _u32(dut.prdata)
    dut.psel.value    = 0
    dut.penable.value = 0
    return val

async def reset_dut(dut):
    dut.rst_n.value        = 0
    dut.psel.value         = 0
    dut.penable.value      = 0
    dut.pwrite.value       = 0
    dut.paddr.value        = 0
    dut.pwdata.value       = 0
    dut.mtime_lo_i.value   = 0
    dut.mtime_hi_i.value   = 0
    dut.mtimecmp_lo_i.value = 0
    dut.mtimecmp_hi_i.value = 0
    dut.mtip_i.value       = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


@cocotb.test()
async def test_msip_readwrite(dut):
    """Write 1 to MSIP[0], read back; then write 0 and verify clear."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 0x1)
    val = await apb_read(dut, 0x00)
    assert val & 1 == 1, f"MSIP: expected 1, got {val:#010x}"

    await apb_write(dut, 0x00, 0x0)
    val = await apb_read(dut, 0x00)
    assert val & 1 == 0, f"MSIP: expected 0 after clear, got {val:#010x}"


@cocotb.test()
async def test_msip_output(dut):
    """msip_o output port tracks MSIP register."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    assert _u32(dut.msip_o) == 0, "msip_o should be 0 after reset"

    await apb_write(dut, 0x00, 0x1)
    await Timer(CLK_NS * 2, unit="ns")
    assert _u32(dut.msip_o) == 1, "msip_o should follow MSIP register"

    await apb_write(dut, 0x00, 0x0)
    await Timer(CLK_NS * 2, unit="ns")
    assert _u32(dut.msip_o) == 0, "msip_o should clear with MSIP register"


@cocotb.test()
async def test_mtime_passthru(dut):
    """Drive mtime_lo_i=0xDEAD_BEEF, mtime_hi_i=0x1234_5678; verify reads at 0x04/0x08."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    dut.mtime_lo_i.value = 0xDEAD_BEEF
    dut.mtime_hi_i.value = 0x1234_5678
    await Timer(CLK_NS * 2, unit="ns")

    lo = await apb_read(dut, 0x04)
    hi = await apb_read(dut, 0x08)
    assert lo == 0xDEAD_BEEF, f"MTIME_LO: expected 0xDEADBEEF, got {lo:#010x}"
    assert hi == 0x1234_5678, f"MTIME_HI: expected 0x12345678, got {hi:#010x}"


@cocotb.test()
async def test_mtimecmp_proxy(dut):
    """Write MTIMECMP_LO/HI via APB; verify they appear on mtimecmp_lo_o/hi_o."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x0C, 0xCAFE_BABE)
    await apb_write(dut, 0x10, 0x0000_00FF)
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.mtimecmp_lo_o) == 0xCAFE_BABE, \
        f"mtimecmp_lo_o: expected 0xCAFEBABE, got {_u32(dut.mtimecmp_lo_o):#010x}"
    assert _u32(dut.mtimecmp_hi_o) == 0x0000_00FF, \
        f"mtimecmp_hi_o: expected 0x000000FF, got {_u32(dut.mtimecmp_hi_o):#010x}"


@cocotb.test()
async def test_mtimecmp_wr_pulse(dut):
    """Write MTIMECMP_LO; verify mtimecmp_wr_o pulses high for exactly one cycle."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    # Should be 0 before write
    assert _u32(dut.mtimecmp_wr_o) == 0, "mtimecmp_wr_o should be 0 before write"

    # Perform the APB write using the helper
    await apb_write(dut, 0x0C, 0x1234)
    # After the write posedge, wr_r=1 for exactly one cycle (mid-cycle sample to catch it)
    await Timer(CLK_NS // 2, unit="ns")
    wr_during = _u32(dut.mtimecmp_wr_o)

    # Next posedge clears wr_r back to 0 — sample after it settles
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    wr_after = _u32(dut.mtimecmp_wr_o)

    assert wr_during == 1, f"mtimecmp_wr_o should be 1 during write cycle, got {wr_during}"
    assert wr_after  == 0, f"mtimecmp_wr_o should clear next cycle, got {wr_after}"
