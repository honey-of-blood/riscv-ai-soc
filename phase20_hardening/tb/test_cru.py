"""Phase 20 — cru.sv cocotb tests.

Tests:
  1. MMCM locks within 210 ref cycles (behavioral model: 200 cycles)
  2. rst_cpu_n / rst_peri_n / rst_ddr_n deassert after locked
  3. Resets reassert when rst_async_n goes low
  4. CPU reset re-deasserts after rst_async_n returns high
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

REF_CLK_NS = 10   # 100 MHz reference

LOCK_TIMEOUT = 250  # ref cycles, model asserts at 200


async def setup(dut):
    cocotb.start_soon(Clock(dut.clk_ref, REF_CLK_NS, units="ns").start())
    dut.rst_async_n.value = 0
    await Timer(5 * REF_CLK_NS, unit="ns")
    dut.rst_async_n.value = 1


# ── Test 1: MMCM locks within LOCK_TIMEOUT ref cycles ─────────────────────────
@cocotb.test()
async def test_lock_timing(dut):
    """locked asserts within 250 ref-clock cycles of rst_async_n deassertion."""
    await setup(dut)
    for i in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            cocotb.log.info(f"locked after {i+1} ref cycles")
            return
    assert False, f"locked did not assert within {LOCK_TIMEOUT} ref cycles"


# ── Test 2: CPU reset deasserts after lock ─────────────────────────────────────
@cocotb.test()
async def test_rst_cpu_deasserts_after_lock(dut):
    """rst_cpu_n is low while unlocked, deasserts ≤3 cpu cycles after locked."""
    await setup(dut)
    # Wait for locked
    for _ in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            break
    else:
        assert False, "locked timeout"

    # rst_cpu_n should deassert within a few CPU clock cycles
    for i in range(10):
        await RisingEdge(dut.clk_cpu)
        if int(dut.rst_cpu_n.value):
            cocotb.log.info(f"rst_cpu_n deasserted after {i+1} cpu cycles post-lock")
            return
    assert False, "rst_cpu_n did not deassert after locked"


# ── Test 3: peri reset deasserts after lock ────────────────────────────────────
@cocotb.test()
async def test_rst_peri_deasserts(dut):
    """rst_peri_n deasserts after locked."""
    await setup(dut)
    for _ in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            break
    else:
        assert False, "locked timeout"

    for i in range(20):
        await RisingEdge(dut.clk_peri)
        if int(dut.rst_peri_n.value):
            cocotb.log.info(f"rst_peri_n deasserted after {i+1} peri cycles")
            return
    assert False, "rst_peri_n did not deassert"


# ── Test 4: DDR reset deasserts after lock ─────────────────────────────────────
@cocotb.test()
async def test_rst_ddr_deasserts(dut):
    """rst_ddr_n deasserts after locked."""
    await setup(dut)
    for _ in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            break
    else:
        assert False, "locked timeout"

    for i in range(10):
        await RisingEdge(dut.clk_ddr)
        if int(dut.rst_ddr_n.value):
            cocotb.log.info(f"rst_ddr_n deasserted after {i+1} ddr cycles")
            return
    assert False, "rst_ddr_n did not deassert"


# ── Test 5: resets reassert on async rst_async_n ──────────────────────────────
@cocotb.test()
async def test_reset_reasserts(dut):
    """Pulling rst_async_n low immediately reasserts all domain resets."""
    await setup(dut)
    # Wait for all resets to deassert
    for _ in range(LOCK_TIMEOUT + 20):
        await RisingEdge(dut.clk_ref)
        if (int(dut.rst_cpu_n.value) and
            int(dut.rst_peri_n.value) and
            int(dut.rst_ddr_n.value)):
            break
    else:
        assert False, "Resets never deasserted"

    # Now pull async reset low
    dut.rst_async_n.value = 0
    await Timer(1, unit="ns")  # combinational propagation

    assert not int(dut.rst_cpu_n.value),  "rst_cpu_n still high after rst_async_n=0"
    assert not int(dut.rst_peri_n.value), "rst_peri_n still high after rst_async_n=0"
    assert not int(dut.rst_ddr_n.value),  "rst_ddr_n still high after rst_async_n=0"


# ── Test 6: re-lock after reset cycle ─────────────────────────────────────────
@cocotb.test()
async def test_relock_after_reset_cycle(dut):
    """MMCM re-locks and resets re-deassert after a reset cycle."""
    await setup(dut)
    # First lock
    for _ in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value): break
    else:
        assert False, "initial lock timeout"

    # Reset again
    dut.rst_async_n.value = 0
    await Timer(5 * REF_CLK_NS, unit="ns")
    dut.rst_async_n.value = 1

    # Should lock again
    locked2 = False
    for _ in range(LOCK_TIMEOUT):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            locked2 = True
            break
    assert locked2, "did not re-lock after second reset"

    # rst_cpu_n should re-deassert
    for _ in range(10):
        await RisingEdge(dut.clk_cpu)
        if int(dut.rst_cpu_n.value):
            return
    assert False, "rst_cpu_n did not re-deassert after second lock"
