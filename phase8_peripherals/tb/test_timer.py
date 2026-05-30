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

# Update reset_dut to also initialize proxy ports (safe — wr_i=0 is a no-op)
async def reset_dut_full(dut):
    dut.rst_n.value           = 0
    dut.psel.value            = 0
    dut.penable.value         = 0
    dut.pwrite.value          = 0
    dut.paddr.value           = 0
    dut.pwdata.value          = 0
    dut.mtimecmp_lo_i.value   = 0
    dut.mtimecmp_hi_i.value   = 0
    dut.mtimecmp_wr_i.value   = 0
    for _ in range(4): await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


# ===========================================================================
# 6. Reset state
# ===========================================================================
@cocotb.test()
async def test_reset_state(dut):
    """After reset: mtime=0, mtimecmp=0xFFFF_FFFF_FFFF_FFFF, ctrl=0, mtip=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)
    await Timer(CLK_NS * 2, unit="ns")

    lo  = await apb_read(dut, 0x00)
    hi  = await apb_read(dut, 0x04)
    clo = await apb_read(dut, 0x08)
    chi = await apb_read(dut, 0x0C)
    ctrl= await apb_read(dut, 0x10)

    assert lo  == 0,            f"MTIME_LO should be 0 after reset, got {lo:#010x}"
    assert hi  == 0,            f"MTIME_HI should be 0 after reset, got {hi:#010x}"
    assert clo == 0xFFFF_FFFF,  f"MTIMECMP_LO should be 0xFFFFFFFF, got {clo:#010x}"
    assert chi == 0xFFFF_FFFF,  f"MTIMECMP_HI should be 0xFFFFFFFF, got {chi:#010x}"
    assert ctrl == 0,           f"CTRL should be 0 after reset, got {ctrl:#010x}"
    assert _u32(dut.mtip) == 0, "mtip should be 0 after reset"


# ===========================================================================
# 7. IRQ-enable gate — enabled but irq_en off → mtip stays 0
# ===========================================================================
@cocotb.test()
async def test_irq_en_gate(dut):
    """CTRL[0]=1 (enable), CTRL[1]=0 (irq_en off); mtime >= mtimecmp → mtip=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)

    await apb_write(dut, 0x08, 5)     # mtimecmp_lo = 5
    await apb_write(dut, 0x0C, 0)
    await apb_write(dut, 0x10, 0x1)   # CTRL: enable only (no irq_en)

    for _ in range(20): await RisingEdge(dut.clk)
    assert _u32(dut.mtip) == 0, \
        "mtip should NOT assert when irq_en=0 (CTRL[1]=0), even when mtime >= mtimecmp"


# ===========================================================================
# 8. MTIME registers are read-only (write has no effect on counter)
# ===========================================================================
@cocotb.test()
async def test_mtime_readonly(dut):
    """APB write to addr=0x00 (MTIME_LO) should be ignored; counter still advances."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)

    await apb_write(dut, 0x10, 0x1)      # enable timer
    for _ in range(5): await RisingEdge(dut.clk)
    t_before = await apb_read(dut, 0x00)

    # Attempt write to MTIME_LO (should be ignored)
    await apb_write(dut, 0x00, 0xDEAD_BEEF)
    t_after = await apb_read(dut, 0x00)

    # Counter should have advanced, not been set to 0xDEADBEEF
    assert t_after != 0xDEAD_BEEF, \
        "MTIME_LO is read-only; write should not change counter value"
    assert t_after > t_before, \
        "counter should still advance after attempted write"


# ===========================================================================
# 9. CLINT proxy write updates mtimecmp
# ===========================================================================
@cocotb.test()
async def test_clint_proxy_write(dut):
    """Drive mtimecmp_wr_i=1 with new values; verify mtimecmp registers update."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)

    # Pre-set mtimecmp to known value via APB
    await apb_write(dut, 0x08, 0x1111_2222)
    await apb_write(dut, 0x0C, 0x3333_4444)

    lo = await apb_read(dut, 0x08)
    hi = await apb_read(dut, 0x0C)
    assert lo == 0x1111_2222, f"APB write pre-check LO: {lo:#010x}"
    assert hi == 0x3333_4444, f"APB write pre-check HI: {hi:#010x}"

    # Drive proxy write for one clock pulse
    dut.mtimecmp_lo_i.value = 0xAAAA_BBBB
    dut.mtimecmp_hi_i.value = 0xCCCC_DDDD
    dut.mtimecmp_wr_i.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.mtimecmp_wr_i.value = 0

    await RisingEdge(dut.clk)
    lo = await apb_read(dut, 0x08)
    hi = await apb_read(dut, 0x0C)
    assert lo == 0xAAAA_BBBB, f"Proxy write: MTIMECMP_LO should be 0xAAAABBBB, got {lo:#010x}"
    assert hi == 0xCCCC_DDDD, f"Proxy write: MTIMECMP_HI should be 0xCCCCDDDD, got {hi:#010x}"


# ===========================================================================
# 10. 64-bit compare — high half blocks interrupt when mtime_hi < mtimecmp_hi
# ===========================================================================
@cocotb.test()
async def test_64bit_compare(dut):
    """Set mtimecmp_hi=1, mtimecmp_lo=1; enable; mtime[63:32]=0 → mtip must stay 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)

    await apb_write(dut, 0x08, 1)    # mtimecmp_lo = 1 (small)
    await apb_write(dut, 0x0C, 1)    # mtimecmp_hi = 1 (requires mtime[63:32] >= 1)
    await apb_write(dut, 0x10, 0x3)  # enable + irq_en

    # Run for many cycles; mtime will reach 1 in LO but HI stays 0
    for _ in range(30): await RisingEdge(dut.clk)

    # mtime = {0, N} < {1, 1} = mtimecmp → no interrupt
    assert _u32(dut.mtip) == 0, \
        "mtip should NOT fire when mtime[63:32]=0 < mtimecmp[63:32]=1"


# ===========================================================================
# 11. mtip fires immediately when mtimecmp=0 and mtime=0 on enable
# ===========================================================================
@cocotb.test()
async def test_mtip_immediate(dut):
    """Set mtimecmp={0,0}; enable+irq_en; mtip must fire immediately (0>=0)."""
    cocotb.start_soon(Clock(dut.clk, CLK_NS, unit="ns").start())
    await reset_dut_full(dut)

    await apb_write(dut, 0x08, 0)    # mtimecmp_lo = 0
    await apb_write(dut, 0x0C, 0)    # mtimecmp_hi = 0
    await apb_write(dut, 0x10, 0x3)  # enable + irq_en: mtime(0) >= mtimecmp(0)

    await Timer(CLK_NS * 3, unit="ns")
    assert _u32(dut.mtip) == 1, \
        "mtip should fire immediately when mtime=0 >= mtimecmp=0 with irq_en"
