"""
PLIC unit tests.

Tests:
  1. priority_readwrite  — write priority for source 2, read back
  2. enable_readwrite    — write enable mask, read back
  3. irq_fires           — set priority/enable, assert irq_src[0], verify m_ext_irq
  4. claim_complete      — claim highest-priority source, verify pending clears
  5. threshold_filter    — set threshold=3; source with priority=2 should NOT fire
  6. priority_arbitration — two sources pending, higher-priority wins claim
  7. pending_readonly    — pending is read-only (write has no effect)
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
    dut.rst_n.value   = 0
    dut.psel.value    = 0
    dut.penable.value = 0
    dut.pwrite.value  = 0
    dut.paddr.value   = 0
    dut.pwdata.value  = 0
    dut.irq_src.value = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


@cocotb.test()
async def test_priority_readwrite(dut):
    """Write priority=5 for source 2 (addr=0x08), read back."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x08, 5)   # source 2: addr = 2*4 = 0x08
    val = await apb_read(dut, 0x08)
    assert val & 0x7 == 5, f"Priority[2]: expected 5, got {val & 0x7}"


@cocotb.test()
async def test_enable_readwrite(dut):
    """Write enable=0xAB, read back."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x24, 0xAB)
    val = await apb_read(dut, 0x24)
    assert val & 0xFF == 0xAB, f"Enable: expected 0xAB, got {val & 0xFF:#04x}"


@cocotb.test()
async def test_irq_fires(dut):
    """Source 0: priority=1, enabled; assert irq_src[0]; verify m_ext_irq=1."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 1)   # priority[0]=1
    await apb_write(dut, 0x24, 0x01) # enable source 0
    await apb_write(dut, 0x28, 0)   # threshold=0

    dut.irq_src.value = 0x01
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00

    await Timer(CLK_NS * 2, unit="ns")
    assert _u32(dut.m_ext_irq) == 1, "m_ext_irq should assert when source 0 fires"


@cocotb.test()
async def test_claim_complete(dut):
    """Claim source 0 (ID=1), write Complete=1, verify pending clears."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 2)   # priority[0]=2
    await apb_write(dut, 0x24, 0x01) # enable source 0
    await apb_write(dut, 0x28, 0)

    dut.irq_src.value = 0x01
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    # Claim: read 0x2C — should return ID=1 (source 0)
    claim = await apb_read(dut, 0x2C)
    assert claim & 0xF == 1, f"Claim: expected ID=1, got {claim & 0xF}"

    # Complete: write ID=1 to 0x2C
    await apb_write(dut, 0x2C, 1)
    for _ in range(3):
        await RisingEdge(dut.clk)

    pending = await apb_read(dut, 0x20)
    assert pending & 1 == 0, f"Pending[0] should clear after complete, got {pending:#010x}"
    assert _u32(dut.m_ext_irq) == 0, "m_ext_irq should deassert after complete"


@cocotb.test()
async def test_threshold_filter(dut):
    """Source 0 priority=2, threshold=3: irq should NOT fire."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 2)   # priority[0]=2
    await apb_write(dut, 0x24, 0x01)
    await apb_write(dut, 0x28, 3)   # threshold=3 (blocks priority<=3)

    dut.irq_src.value = 0x01
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.m_ext_irq) == 0, \
        "m_ext_irq should NOT fire when priority(2) <= threshold(3)"


@cocotb.test()
async def test_priority_arbitration(dut):
    """Sources 0 (pri=1) and 2 (pri=3) both pending; claim should return source 2 (ID=3)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 1)   # priority[0]=1
    await apb_write(dut, 0x08, 3)   # priority[2]=3
    await apb_write(dut, 0x24, 0x05) # enable sources 0 and 2
    await apb_write(dut, 0x28, 0)

    dut.irq_src.value = 0x05  # assert sources 0 and 2
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    claim = await apb_read(dut, 0x2C)
    assert claim & 0xF == 3, \
        f"Claim: expected higher-priority source 2 (ID=3), got {claim & 0xF}"


@cocotb.test()
async def test_pending_readonly(dut):
    """APB write to Pending register (0x20) has no effect — it is read-only."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    # No irq asserted; pending should be 0
    await apb_write(dut, 0x20, 0xFF)   # attempt SW write to pending
    pending = await apb_read(dut, 0x20)
    assert pending & 0xFF == 0, \
        f"Pending should be 0 (RO, no hw irq), got {pending:#010x}"
