"""Phase 20 — cru.sv aggressive stress tests.

Covers: multiple reset cycles, reset mid-lock-countdown, deterministic lock
timing, all domain resets bounded deassert, async reset immediate propagation,
and rapid successive reset cycling.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

REF_CLK_NS = 10
LOCK_TIMEOUT = 250   # ref cycles; behavioral model locks at cycle 200


async def setup(dut):
    cocotb.start_soon(Clock(dut.clk_ref, REF_CLK_NS, unit="ns").start())
    dut.rst_async_n.value = 0
    await Timer(5 * REF_CLK_NS, unit="ns")
    dut.rst_async_n.value = 1


async def wait_for_lock(dut, timeout=LOCK_TIMEOUT):
    for i in range(timeout):
        await RisingEdge(dut.clk_ref)
        if int(dut.locked.value):
            return i + 1
    assert False, f"MMCM did not lock within {timeout} ref cycles"


async def wait_for_all_resets(dut, timeout=30):
    for _ in range(timeout):
        await RisingEdge(dut.clk_ref)
        if (int(dut.rst_cpu_n.value) and
                int(dut.rst_peri_n.value) and
                int(dut.rst_ddr_n.value)):
            return
    assert False, "One or more domain resets did not deassert"


async def do_reset_cycle(dut):
    """Full reset+lock+all-domain-deassert cycle. Returns lock cycle count."""
    dut.rst_async_n.value = 0
    await Timer(5 * REF_CLK_NS, unit="ns")
    dut.rst_async_n.value = 1
    count = await wait_for_lock(dut)
    await wait_for_all_resets(dut)
    return count


# ── Tests ──────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_five_sequential_reset_cycles(dut):
    """Assert+release reset 5 times; every cycle must lock and all resets must come up."""
    await setup(dut)

    for cycle in range(5):
        count = await do_reset_cycle(dut)
        assert count <= LOCK_TIMEOUT, \
            f"Cycle {cycle+1}: locked after {count} cycles (timeout {LOCK_TIMEOUT})"
        assert int(dut.locked.value),     f"Cycle {cycle+1}: locked not 1 after wait"
        assert int(dut.rst_cpu_n.value),  f"Cycle {cycle+1}: rst_cpu_n still 0"
        assert int(dut.rst_peri_n.value), f"Cycle {cycle+1}: rst_peri_n still 0"
        assert int(dut.rst_ddr_n.value),  f"Cycle {cycle+1}: rst_ddr_n still 0"


@cocotb.test()
async def test_reset_mid_lock_restarts_countdown(dut):
    """Assert reset at cycle 100 (half of 200); verify locked is not asserted early
    and that lock restarts correctly from 0 after reset release."""
    await setup(dut)

    # Run 100 cycles — should NOT be locked yet
    for _ in range(100):
        await RisingEdge(dut.clk_ref)
    assert not int(dut.locked.value), "locked asserted before 200 cycles (at 100)"

    # Re-assert reset — lock countdown resets to 0
    dut.rst_async_n.value = 0
    await Timer(3 * REF_CLK_NS, unit="ns")
    assert not int(dut.locked.value), "locked still 1 while rst_async_n=0"
    dut.rst_async_n.value = 1

    # Must lock within LOCK_TIMEOUT from HERE (full 200-cycle count restarts)
    count = await wait_for_lock(dut)
    assert count <= LOCK_TIMEOUT, f"re-lock after mid-lock reset took {count} cycles"
    await wait_for_all_resets(dut)


@cocotb.test()
async def test_lock_cycle_count_deterministic(dut):
    """Behavioral MMCM is purely synchronous — lock must always fire within the
    same narrow window ([200, 205] ref cycles) from reset release."""
    EXPECTED = 200
    TOLERANCE = 5

    await setup(dut)  # start clock; initial reset already released here

    counts = []
    for _ in range(3):
        dut.rst_async_n.value = 0
        await Timer(5 * REF_CLK_NS, unit="ns")
        dut.rst_async_n.value = 1
        counts.append(await wait_for_lock(dut))
        await wait_for_all_resets(dut)

    for i, c in enumerate(counts):
        assert abs(c - EXPECTED) <= TOLERANCE, \
            f"Run {i+1}: locked at cycle {c}, expected ~{EXPECTED} ±{TOLERANCE}"

    spread = max(counts) - min(counts)
    assert spread <= 2, \
        f"Lock timing not deterministic: counts={counts}, spread={spread}"


@cocotb.test()
async def test_all_domain_resets_deassert_bounded(dut):
    """After lock all three domain resets (cpu/peri/ddr) must deassert within 10 cycles."""
    await setup(dut)
    await wait_for_lock(dut)

    # Count cycles until all three domain resets deassert
    for i in range(10):
        await RisingEdge(dut.clk_ref)
        if (int(dut.rst_cpu_n.value) and
                int(dut.rst_peri_n.value) and
                int(dut.rst_ddr_n.value)):
            return
    assert False, \
        f"Domain resets did not all deassert within 10 cycles of lock: " \
        f"cpu={int(dut.rst_cpu_n.value)} peri={int(dut.rst_peri_n.value)} " \
        f"ddr={int(dut.rst_ddr_n.value)}"


@cocotb.test()
async def test_async_reset_immediate_propagation(dut):
    """Pulling rst_async_n low must IMMEDIATELY assert all domain resets (within 1ns)
    regardless of which domain clock phase we are in."""
    await setup(dut)
    await wait_for_lock(dut)
    await wait_for_all_resets(dut)

    # Confirm everything is deasserted
    assert int(dut.rst_cpu_n.value),  "rst_cpu_n not deasserted before test"
    assert int(dut.rst_peri_n.value), "rst_peri_n not deasserted before test"
    assert int(dut.rst_ddr_n.value),  "rst_ddr_n not deasserted before test"

    # Async reset — domain resets must go low immediately (async path)
    dut.rst_async_n.value = 0
    await Timer(1, unit="ns")
    assert not int(dut.rst_cpu_n.value),  "rst_cpu_n still high 1ns after rst_async_n=0"
    assert not int(dut.rst_peri_n.value), "rst_peri_n still high 1ns after rst_async_n=0"
    assert not int(dut.rst_ddr_n.value),  "rst_ddr_n still high 1ns after rst_async_n=0"

    # Also locked must clear synchronously on rst_async_n (async clear)
    assert not int(dut.locked.value), "locked still high 1ns after rst_async_n=0"

    dut.rst_async_n.value = 1


@cocotb.test()
async def test_rapid_three_resets(dut):
    """Three short reset pulses in rapid succession — all must result in a lock."""
    await setup(dut)

    for cycle in range(3):
        dut.rst_async_n.value = 0
        await Timer(2 * REF_CLK_NS, unit="ns")  # short pulse (2 ref cycles)
        dut.rst_async_n.value = 1
        count = await wait_for_lock(dut)
        assert count <= LOCK_TIMEOUT, \
            f"Rapid cycle {cycle+1}: no lock within {LOCK_TIMEOUT} cycles (got {count})"
        # Verify all resets come up before next pulse
        await wait_for_all_resets(dut)
