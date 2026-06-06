"""Phase 17 — Watchdog timer cocotb tests."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns

CTRL_R   = 0x00
TIMEOUT  = 0x04
KICK_R   = 0x08
STATUS_R = 0x0C

MAGIC_STEP1 = 0x1ACCE551
MAGIC_STEP2 = 0xDEAD5AFE


async def reset(dut):
    dut.rst_n.value = 0
    await Timer(5 * CLK_PERIOD, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_PERIOD, unit="ns")


async def apb_wr(dut, addr, data):
    dut.paddr.value   = addr
    dut.pwdata.value  = data
    dut.pwrite.value  = 1
    dut.psel.value    = 1
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.psel.value    = 0
    dut.penable.value = 0
    dut.pwrite.value  = 0


async def apb_rd(dut, addr):
    dut.paddr.value   = addr
    dut.pwrite.value  = 0
    dut.psel.value    = 1
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    val = int(dut.prdata.value)
    dut.psel.value    = 0
    dut.penable.value = 0
    return val


async def kick(dut):
    await apb_wr(dut, KICK_R, MAGIC_STEP1)
    await apb_wr(dut, KICK_R, MAGIC_STEP2)


@cocotb.test()
async def test_reset_defaults(dut):
    """After reset: WDT disabled, outputs deasserted."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    assert int(dut.wdt_reset_o.value) == 0
    assert int(dut.wdt_nmi_o.value) == 0
    ctrl = await apb_rd(dut, CTRL_R)
    assert (ctrl & 0x1) == 0, "WDT should be disabled at reset"


@cocotb.test()
async def test_timeout_fires_reset(dut):
    """WDT fires wdt_reset_o after counter reaches zero (reset mode)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 10)
    await apb_wr(dut, CTRL_R, 0x1)   # enable, nmi_mode=0
    # Wait for timeout
    fired = False
    for _ in range(30):
        await RisingEdge(dut.clk)
        if int(dut.wdt_reset_o.value):
            fired = True
            break
    assert fired, "wdt_reset_o never asserted"


@cocotb.test()
async def test_timeout_fires_nmi(dut):
    """WDT fires wdt_nmi_o when nmi_mode=1."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 10)
    await apb_wr(dut, CTRL_R, 0x3)   # enable + nmi_mode
    fired = False
    for _ in range(30):
        await RisingEdge(dut.clk)
        if int(dut.wdt_nmi_o.value):
            fired = True
            break
    assert fired, "wdt_nmi_o never asserted"
    # wdt_reset_o must NOT fire in NMI mode
    assert int(dut.wdt_reset_o.value) == 0, "wdt_reset_o should not fire in NMI mode"


@cocotb.test()
async def test_magic_kick_reloads_counter(dut):
    """Correct magic sequence reloads counter before timeout."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 20)
    await apb_wr(dut, CTRL_R, 0x1)
    # Kick at cycle 10 (halfway) — no timeout should fire before we kick
    for _ in range(10):
        await RisingEdge(dut.clk)
    await kick(dut)
    # Now wait 25 more clocks — should NOT fire (counter was reset to 20)
    fired = False
    for _ in range(15):
        await RisingEdge(dut.clk)
        if int(dut.wdt_reset_o.value):
            fired = True
            break
    assert not fired, "wdt_reset_o fired too early after kick"


@cocotb.test()
async def test_wrong_magic_value_locks(dut):
    """Wrong second magic value does NOT reload counter."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 15)
    await apb_wr(dut, CTRL_R, 0x1)
    # Send STEP1 then a wrong value
    await apb_wr(dut, KICK_R, MAGIC_STEP1)
    await apb_wr(dut, KICK_R, 0xDEADBEEF)   # wrong
    # unlock_step should be 0 now
    ks = await apb_rd(dut, KICK_R)
    assert (ks & 0x1) == 0, "unlock_step not cleared by wrong value"


@cocotb.test()
async def test_bad_first_write_no_unlock(dut):
    """Writing wrong first value does NOT set unlock_step."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, KICK_R, 0xCAFEBABE)   # not STEP1
    ks = await apb_rd(dut, KICK_R)
    assert (ks & 0x1) == 0, "unlock_step set on bad first value"


@cocotb.test()
async def test_status_timeout_flag_w1c(dut):
    """STATUS[0]=timeout_flag is set on timeout and cleared by W1C."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 5)
    await apb_wr(dut, CTRL_R, 0x3)   # nmi_mode to avoid consuming reset
    for _ in range(15):
        await RisingEdge(dut.clk)
    st = await apb_rd(dut, STATUS_R)
    assert (st & 0x1), f"timeout_flag not set: {st:#x}"
    # Clear W1C
    await apb_wr(dut, STATUS_R, 0x1)
    st = await apb_rd(dut, STATUS_R)
    assert (st & 0x1) == 0, "timeout_flag not cleared by W1C"


@cocotb.test()
async def test_disabled_wdt_never_fires(dut):
    """Disabled WDT (CTRL[0]=0) never asserts outputs regardless of counter."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await apb_wr(dut, TIMEOUT, 3)
    # Leave CTRL disabled (default)
    fired = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if int(dut.wdt_reset_o.value) or int(dut.wdt_nmi_o.value):
            fired = True
            break
    assert not fired, "WDT fired while disabled"
