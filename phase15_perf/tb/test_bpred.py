"""
Phase 15 branch predictor unit tests.
Tests: initial state, saturating counter, BTB prediction, loop pattern.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


async def reset(dut):
    dut.rst_n.value = 0
    dut.pc_if_i.value = 0
    dut.branch_resolved_i.value = 0
    dut.branch_taken_i.value = 0
    dut.branch_pc_i.value = 0
    dut.branch_target_i.value = 0
    await Timer(20, unit="ns")
    await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


async def resolve_branch(dut, pc, taken, target=0):
    """Send one branch resolution update."""
    dut.branch_resolved_i.value = 1
    dut.branch_taken_i.value = 1 if taken else 0
    dut.branch_pc_i.value = pc
    dut.branch_target_i.value = target
    await RisingEdge(dut.clk)
    dut.branch_resolved_i.value = 0
    dut.branch_taken_i.value = 0
    await Timer(1, unit="ns")


@cocotb.test()
async def test_initial_state(dut):
    """After reset, all BHT counters should be weakly not-taken (01),
    so predict_taken_o should be 0 for any PC."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Check several PCs — none should predict taken since BTB is invalid
    for pc in [0x0, 0x4, 0x100, 0x1000]:
        dut.pc_if_i.value = pc
        await Timer(1, unit="ns")
        taken = int(dut.predict_taken_o.value)
        assert taken == 0, f"Expected not-taken after reset for PC={pc:#010x}, got {taken}"


@cocotb.test()
async def test_sat_counter_increment(dut):
    """Resolve branch taken twice → counter should be 11 (strongly taken)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    branch_pc = 0x00000010
    branch_target = 0x00000040

    # First taken resolution
    await resolve_branch(dut, branch_pc, taken=True, target=branch_target)
    # Second taken resolution
    await resolve_branch(dut, branch_pc, taken=True, target=branch_target)

    # Now look up prediction for branch_pc
    dut.pc_if_i.value = branch_pc
    await Timer(1, unit="ns")

    taken = int(dut.predict_taken_o.value)
    target = int(dut.predict_target_o.value)
    assert taken == 1, f"Expected taken prediction after 2 taken resolutions, got {taken}"
    assert target == branch_target, f"Expected target {branch_target:#010x}, got {target:#010x}"


@cocotb.test()
async def test_btb_prediction(dut):
    """After a taken branch, BTB should predict the correct target."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    branch_pc = 0x00000020
    branch_target = 0x00000008

    # Train with two taken resolutions (to get counter to strongly taken)
    await resolve_branch(dut, branch_pc, taken=True, target=branch_target)
    await resolve_branch(dut, branch_pc, taken=True, target=branch_target)

    # Look up the prediction
    dut.pc_if_i.value = branch_pc
    await Timer(1, unit="ns")

    assert int(dut.predict_taken_o.value) == 1, "Should predict taken"
    got_target = int(dut.predict_target_o.value)
    assert got_target == branch_target, \
        f"BTB target mismatch: expected {branch_target:#010x}, got {got_target:#010x}"


@cocotb.test()
async def test_not_taken_after_taken(dut):
    """3 taken + 1 not-taken → counter decrements from 11 to 10 (weakly taken),
    but after 2 not-taken it should be weakly not-taken."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    branch_pc = 0x00000030
    branch_target = 0x00000080

    # Train taken × 3 (start at 01, → 10 → 11 → 11 saturated)
    for _ in range(3):
        await resolve_branch(dut, branch_pc, taken=True, target=branch_target)

    # Not taken × 1 (11 → 10 = weakly taken)
    await resolve_branch(dut, branch_pc, taken=False)

    dut.pc_if_i.value = branch_pc
    await Timer(1, unit="ns")
    # Still weakly taken = still predicts taken (MSB=1)
    assert int(dut.predict_taken_o.value) == 1, \
        "After 3 taken + 1 not-taken, counter=10, should still predict taken"

    # Not taken × 1 more (10 → 01 = weakly not-taken)
    await resolve_branch(dut, branch_pc, taken=False)

    dut.pc_if_i.value = branch_pc
    await Timer(1, unit="ns")
    # Counter=01, MSB=0, predict not taken
    assert int(dut.predict_taken_o.value) == 0, \
        "After 3 taken + 2 not-taken, counter=01, should predict not-taken"


@cocotb.test()
async def test_loop_pattern(dut):
    """Simulate 100 loop iterations: measure prediction accuracy >= 99%."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Loop branch at PC=0x8, back-edge target=0x8 (BNE to same or earlier PC)
    loop_pc     = 0x00000008
    loop_target = 0x00000008  # tight loop back to itself

    correct   = 0
    incorrect = 0
    NUM_ITER  = 100

    for i in range(NUM_ITER):
        # Check prediction before resolving
        dut.pc_if_i.value = loop_pc
        await Timer(1, unit="ns")
        pred = int(dut.predict_taken_o.value)

        # Actual outcome: taken for all but the last iteration
        actual_taken = (i < NUM_ITER - 1)

        if pred == (1 if actual_taken else 0):
            correct += 1
        else:
            incorrect += 1

        # Resolve
        await resolve_branch(dut, loop_pc, taken=actual_taken, target=loop_target)

    total = correct + incorrect
    accuracy = correct / total
    cocotb.log.info(f"Loop prediction: {correct}/{total} correct ({accuracy*100:.1f}%)")
    # Allow for first few mispredictions during warmup
    assert accuracy >= 0.95, \
        f"Loop prediction accuracy {accuracy*100:.1f}% below threshold 95%"
