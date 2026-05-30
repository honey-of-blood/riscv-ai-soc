"""
GPIO unit tests.

Tests:
  1. output_drive    — set DIR=all-output, write DATA, verify gpio_out
  2. input_read      — set DIR=all-input, drive gpio_in, read DATA
  3. mixed_dir       — lower 8 bits output, upper 8 bits input
  4. edge_irq        — enable IEN, toggle gpio_in, verify ISTAT and irq
  5. istat_w1c       — write 1 to ISTAT to clear, verify irq de-asserts
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
    dut.gpio_in.value = 0
    for _ in range(4): await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)

@cocotb.test()
async def test_output_drive(dut):
    """DIR=0xFFFF (all output), DATA=0xA5A5 → gpio_out=0xA5A5, gpio_oe=0xFFFF."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0xFFFF)   # DIR: all output
    await apb_write(dut, 0x00, 0xA5A5)   # DATA: output value
    await Timer(CLK_NS * 2, unit="ns")
    assert _u32(dut.gpio_out) == 0xA5A5, f"gpio_out: expected 0xA5A5, got {_u32(dut.gpio_out):#06x}"
    assert _u32(dut.gpio_oe)  == 0xFFFF, f"gpio_oe:  expected 0xFFFF, got {_u32(dut.gpio_oe):#06x}"

@cocotb.test()
async def test_input_read(dut):
    """DIR=0 (all input), drive gpio_in=0x1234, read DATA register."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)   # DIR: all input
    dut.gpio_in.value = 0x1234
    # Let synchronizer pipeline (3 cycles) settle
    for _ in range(5): await RisingEdge(dut.clk)
    val = await apb_read(dut, 0x00)
    assert val & 0xFFFF == 0x1234, f"DATA read: expected 0x1234, got {val:#06x}"

@cocotb.test()
async def test_mixed_dir(dut):
    """Lower 8 bits output (DIR=0x00FF), upper 8 input."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x00FF)   # lower 8 = output
    await apb_write(dut, 0x00, 0x00AB)   # drive lower 8
    dut.gpio_in.value = 0xCD00           # upper 8 input
    for _ in range(5): await RisingEdge(dut.clk)
    assert _u32(dut.gpio_oe)  & 0xFFFF == 0x00FF, "gpio_oe mismatch"
    assert _u32(dut.gpio_out) & 0x00FF == 0x00AB, "gpio_out mismatch"
    data = await apb_read(dut, 0x00)
    assert data & 0xFF00 == 0xCD00, f"upper input: expected 0xCD00, got {data:#06x}"

@cocotb.test()
async def test_edge_irq(dut):
    """Enable IEN on bit 0; toggle gpio_in bit 0; verify ISTAT[0]=1 and irq=1."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)   # all input
    await apb_write(dut, 0x08, 0x0001)   # IEN: enable bit 0
    dut.gpio_in.value = 0x0000
    for _ in range(5): await RisingEdge(dut.clk)
    dut.gpio_in.value = 0x0001           # rising edge on bit 0
    for _ in range(5): await RisingEdge(dut.clk)
    istat = await apb_read(dut, 0x0C)
    assert istat & 1 == 1, f"ISTAT[0] should be 1, got {istat:#06x}"
    assert _u32(dut.irq) == 1, "irq should be asserted"

@cocotb.test()
async def test_istat_w1c(dut):
    """Generate interrupt then write 1 to ISTAT to clear it."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)
    await apb_write(dut, 0x08, 0x0001)
    dut.gpio_in.value = 0
    for _ in range(5): await RisingEdge(dut.clk)
    dut.gpio_in.value = 1                # trigger edge
    for _ in range(5): await RisingEdge(dut.clk)
    await apb_write(dut, 0x0C, 0x0001)  # W1C: clear bit 0
    for _ in range(3): await RisingEdge(dut.clk)
    istat = await apb_read(dut, 0x0C)
    assert istat & 1 == 0, f"ISTAT[0] should be cleared, got {istat:#06x}"
    assert _u32(dut.irq) == 0, "irq should be de-asserted after W1C"

# ===========================================================================
# 6. Reset state
# ===========================================================================
@cocotb.test()
async def test_reset_state(dut):
    """After reset: DIR=0, OUT=0, IEN=0, ISTAT=0, irq=0, gpio_oe=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.gpio_oe)  == 0, f"gpio_oe should be 0 after reset, got {_u32(dut.gpio_oe):#06x}"
    assert _u32(dut.gpio_out) == 0, f"gpio_out should be 0 after reset, got {_u32(dut.gpio_out):#06x}"
    assert _u32(dut.irq)      == 0, f"irq should be 0 after reset, got {_u32(dut.irq)}"
    istat = await apb_read(dut, 0x0C)
    assert istat == 0, f"ISTAT should be 0 after reset, got {istat:#06x}"


# ===========================================================================
# 7. Falling-edge interrupt detection
# ===========================================================================
@cocotb.test()
async def test_falling_edge_irq(dut):
    """Enable IEN bit 0, gpio_in goes 1→0 (falling edge); ISTAT[0] must set."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)   # all input
    await apb_write(dut, 0x08, 0x0001)   # IEN bit 0

    # Set bit 0 high first, let synchronizer settle
    dut.gpio_in.value = 0x0001
    for _ in range(5): await RisingEdge(dut.clk)

    # Falling edge: 1 → 0
    dut.gpio_in.value = 0x0000
    for _ in range(5): await RisingEdge(dut.clk)

    istat = await apb_read(dut, 0x0C)
    assert istat & 1 == 1, f"ISTAT[0] should be set on falling edge, got {istat:#06x}"
    assert _u32(dut.irq) == 1, "irq should assert on falling edge"


# ===========================================================================
# 8. Multiple bits generate independent ISTAT entries
# ===========================================================================
@cocotb.test()
async def test_multiple_irq_bits(dut):
    """Enable IEN bits 0 and 7; toggle both; ISTAT should have both bits set."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)
    await apb_write(dut, 0x08, 0x0081)   # IEN bits 0 and 7

    dut.gpio_in.value = 0x0000
    for _ in range(5): await RisingEdge(dut.clk)

    # Rising edge on bits 0 and 7 simultaneously
    dut.gpio_in.value = 0x0081
    for _ in range(5): await RisingEdge(dut.clk)

    istat = await apb_read(dut, 0x0C)
    assert istat & 0x0001 == 1,    f"ISTAT[0] should be set, got {istat:#06x}"
    assert istat & 0x0080 == 0x80, f"ISTAT[7] should be set, got {istat:#06x}"


# ===========================================================================
# 9. W1C clears only specified bits — others remain
# ===========================================================================
@cocotb.test()
async def test_partial_w1c(dut):
    """Set bits 0 and 3 in ISTAT; W1C only bit 0; bit 3 must remain set."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)
    await apb_write(dut, 0x08, 0x0009)   # IEN bits 0 and 3

    dut.gpio_in.value = 0x0000
    for _ in range(5): await RisingEdge(dut.clk)
    dut.gpio_in.value = 0x0009           # rising edge on both
    for _ in range(5): await RisingEdge(dut.clk)

    istat = await apb_read(dut, 0x0C)
    assert istat & 0x9 == 0x9, f"Both bits should be set before W1C, got {istat:#06x}"

    # Clear only bit 0
    await apb_write(dut, 0x0C, 0x0001)
    for _ in range(3): await RisingEdge(dut.clk)

    istat = await apb_read(dut, 0x0C)
    assert istat & 0x1 == 0, f"Bit 0 should be cleared by W1C, got {istat:#06x}"
    assert istat & 0x8 == 0x8, f"Bit 3 should still be set, got {istat:#06x}"


# ===========================================================================
# 10. No interrupt when IEN is disabled
# ===========================================================================
@cocotb.test()
async def test_no_irq_without_ien(dut):
    """Toggle gpio_in without enabling IEN; irq must stay 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x0000)
    await apb_write(dut, 0x08, 0x0000)   # IEN disabled

    dut.gpio_in.value = 0x0000
    for _ in range(5): await RisingEdge(dut.clk)
    dut.gpio_in.value = 0xFFFF           # toggle all bits
    for _ in range(5): await RisingEdge(dut.clk)

    istat = await apb_read(dut, 0x0C)
    assert istat == 0,         f"ISTAT should be 0 when IEN=0, got {istat:#06x}"
    assert _u32(dut.irq) == 0, "irq should be 0 when IEN=0"


# ===========================================================================
# 11. Output enable mask — only DIR=1 bits appear in gpio_oe
# ===========================================================================
@cocotb.test()
async def test_oe_masking(dut):
    """DIR=0x0F (lower 4 output); verify gpio_oe=0x000F, upper bits 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await apb_write(dut, 0x04, 0x000F)   # lower 4 bits = output
    await Timer(CLK_NS * 2, unit="ns")

    oe = _u32(dut.gpio_oe) & 0xFFFF
    assert oe == 0x000F, f"gpio_oe should be 0x000F, got {oe:#06x}"
