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


# ===========================================================================
# 8. Reset state
# ===========================================================================
@cocotb.test()
async def test_reset_state(dut):
    """After reset: m_ext_irq=0, pending=0, enable=0, priorities=0, threshold=0, claim=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.m_ext_irq) == 0, "m_ext_irq should be 0 after reset"
    pending = await apb_read(dut, 0x20)
    assert pending == 0, f"Pending should be 0 after reset, got {pending:#010x}"
    enable  = await apb_read(dut, 0x24)
    assert enable  == 0, f"Enable should be 0 after reset, got {enable:#010x}"
    thresh  = await apb_read(dut, 0x28)
    assert thresh  == 0, f"Threshold should be 0 after reset, got {thresh:#010x}"
    claim   = await apb_read(dut, 0x2C)
    assert claim   == 0, f"Claim should be 0 when nothing pending, got {claim:#010x}"
    pri0    = await apb_read(dut, 0x00)
    assert pri0 & 0x7 == 0, f"Priority[0] should be 0 after reset, got {pri0 & 0x7}"


# ===========================================================================
# 9. Enable bit gates interrupt delivery (pending still latches)
# ===========================================================================
@cocotb.test()
async def test_enable_filter(dut):
    """Source 0 fires with priority=5, enable=0; m_ext_irq must stay 0, pending still set."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 5)    # priority[0]=5
    await apb_write(dut, 0x24, 0x00) # enable = 0 (none enabled)
    await apb_write(dut, 0x28, 0)    # threshold=0

    dut.irq_src.value = 0x01
    for _ in range(4): await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.m_ext_irq) == 0, "m_ext_irq should be 0 when source not enabled"
    pending = await apb_read(dut, 0x20)
    assert pending & 1 == 1, f"Pending[0] should latch even when not enabled, got {pending:#010x}"


# ===========================================================================
# 10. Priority=0 never fires (condition: priority > threshold; 0 > 0 is false)
# ===========================================================================
@cocotb.test()
async def test_priority_zero_no_irq(dut):
    """Source 0: priority=0 (reset default), enable=1, threshold=0; irq fires -> m_ext_irq=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    # Leave priority[0] at reset value of 0
    await apb_write(dut, 0x24, 0x01) # enable source 0
    await apb_write(dut, 0x28, 0)    # threshold=0

    dut.irq_src.value = 0x01
    for _ in range(4): await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.m_ext_irq) == 0, \
        "m_ext_irq should NOT fire when priority=0 (0 > threshold=0 is false)"


# ===========================================================================
# 11. Claim returns 0 when nothing is pending
# ===========================================================================
@cocotb.test()
async def test_claim_returns_zero_when_empty(dut):
    """Read Claim/Complete with nothing pending -> returns 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    claim = await apb_read(dut, 0x2C)
    assert claim == 0, f"Claim should return 0 when no pending IRQ, got {claim:#010x}"


# ===========================================================================
# 12. Pending latches — irq de-asserts but m_ext_irq stays until claimed
# ===========================================================================
@cocotb.test()
async def test_irq_stays_pending(dut):
    """HW irq de-asserts; pending stays set; m_ext_irq remains; claim/complete clears it."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    await apb_write(dut, 0x00, 3)    # priority[0]=3
    await apb_write(dut, 0x24, 0x01) # enable source 0
    await apb_write(dut, 0x28, 0)

    dut.irq_src.value = 0x01
    for _ in range(4): await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00         # de-assert hardware IRQ

    for _ in range(5): await RisingEdge(dut.clk)

    pending = await apb_read(dut, 0x20)
    assert pending & 1 == 1, f"Pending should stay set after irq de-asserts, got {pending:#010x}"
    assert _u32(dut.m_ext_irq) == 1, "m_ext_irq should stay asserted until claimed"

    # Claim then complete to clear
    claim = await apb_read(dut, 0x2C)
    assert claim & 0xF == 1, f"Claim should return ID=1 (source 0), got {claim & 0xF}"
    await apb_write(dut, 0x2C, claim & 0xF)
    for _ in range(3): await RisingEdge(dut.clk)

    pending = await apb_read(dut, 0x20)
    assert pending & 1 == 0, f"Pending should clear after complete, got {pending:#010x}"
    assert _u32(dut.m_ext_irq) == 0, "m_ext_irq should deassert after complete"


# ===========================================================================
# 13. All 8 sources fire simultaneously; highest priority wins claim
# ===========================================================================
@cocotb.test()
async def test_all_eight_sources(dut):
    """All 8 sources fire; source 6 (priority=7, highest) wins claim (ID=7)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    # Set priorities: source 6 gets the max (7); others get 1-6 or 3
    priorities = [1, 2, 3, 4, 5, 6, 7, 3]
    for i, pri in enumerate(priorities):
        await apb_write(dut, i * 4, pri)

    await apb_write(dut, 0x24, 0xFF)  # enable all 8
    await apb_write(dut, 0x28, 0)     # threshold=0

    dut.irq_src.value = 0xFF
    for _ in range(4): await RisingEdge(dut.clk)
    dut.irq_src.value = 0x00
    await Timer(CLK_NS * 2, unit="ns")

    assert _u32(dut.m_ext_irq) == 1, "m_ext_irq should assert when any source fires"
    claim = await apb_read(dut, 0x2C)
    # Source 6 has priority 7 (highest); claim_id = 6+1 = 7
    assert claim & 0xF == 7, \
        f"Claim: expected source 6 (ID=7, priority=7) to win, got ID={claim & 0xF}"
