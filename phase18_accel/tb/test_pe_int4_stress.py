"""Phase 18 stress tests — pe_int4 (ACT_W=4, ACCW=32).

Exercises every INT4 input pair, accumulation depth, reset recovery,
nonzero c_i, pipelined back-to-back values, zero-factor, and sign extension.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns


def to_signed4(x):
    v = int(x) & 0xF
    return v - 16 if v >= 8 else v


def to_signed32(x):
    v = int(x) & 0xFFFFFFFF
    return v - 0x100000000 if v >= 0x80000000 else v


async def reset(dut):
    dut.rst_n.value = 0
    dut.a_i.value   = 0
    dut.b_i.value   = 0
    dut.c_i.value   = 0
    await Timer(5 * CLK_PERIOD, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_PERIOD, unit="ns")


@cocotb.test()
async def test_full_int4_sweep(dut):
    """All 256 signed INT4 × INT4 products with c_i=0 → c_o = a*b."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    errors = []
    for a in range(-8, 8):
        for b in range(-8, 8):
            dut.a_i.value = a & 0xF
            dut.b_i.value = b & 0xF
            dut.c_i.value = 0
            await RisingEdge(dut.clk)
            await Timer(1, unit="ns")
            c_o = to_signed32(dut.c_o.value)
            if c_o != a * b:
                errors.append(f"a={a}, b={b}: expected {a*b}, got {c_o}")
    assert not errors, f"{len(errors)} failures:\n" + "\n".join(errors[:10])


@cocotb.test()
async def test_large_accumulation(dut):
    """Accumulate c_o back as c_i for 30 cycles; result = 30 * (a*b)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    a, b = 3, 3  # product = 9
    acc = 0
    for _ in range(30):
        dut.a_i.value = a & 0xF
        dut.b_i.value = b & 0xF
        dut.c_i.value = acc & 0xFFFFFFFF
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        acc = to_signed32(dut.c_o.value)
    assert acc == 30 * 9, f"expected 270, got {acc}"


@cocotb.test()
async def test_reset_mid_compute(dut):
    """Accumulate 5 cycles, then assert reset; c_o must return to 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    acc = 0
    for _ in range(5):
        dut.a_i.value = 5
        dut.b_i.value = 5
        dut.c_i.value = acc & 0xFFFFFFFF
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        acc = to_signed32(dut.c_o.value)
    assert acc == 5 * 25, f"pre-reset expected 125, got {acc}"

    # Assert reset mid-compute
    dut.rst_n.value = 0
    await Timer(3 * CLK_PERIOD, unit="ns")
    dut.rst_n.value = 1
    dut.a_i.value = 0
    dut.b_i.value = 0
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(dut.c_o.value)
    assert c_o == 0, f"post-reset c_o should be 0, got {c_o}"


@cocotb.test()
async def test_nonzero_c_i(dut):
    """c_i=100, a=3, b=4 → c_o=112; c_i=−50, a=2, b=3 → c_o=−44."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    dut.a_i.value = 3
    dut.b_i.value = 4
    dut.c_i.value = 100
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert to_signed32(dut.c_o.value) == 112, f"got {to_signed32(dut.c_o.value)}"

    dut.a_i.value = 2
    dut.b_i.value = 3
    dut.c_i.value = (-50) & 0xFFFFFFFF
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert to_signed32(dut.c_o.value) == -44, f"got {to_signed32(dut.c_o.value)}"


@cocotb.test()
async def test_pipelined_back_to_back(dut):
    """Different (a,b,c_i) every cycle — verify 30-cycle pipeline correctness."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    # Build test sequence: (a, b, c_i) and expected c_o
    cases = []
    import random
    rng = random.Random(0xDEAD)
    for _ in range(30):
        a   = rng.randint(-7, 7)
        b   = rng.randint(-7, 7)
        ci  = rng.randint(-50, 50)
        cases.append((a, b, ci, a * b + ci))

    # Prime first cycle
    a0, b0, ci0, exp0 = cases[0]
    dut.a_i.value = a0 & 0xF
    dut.b_i.value = b0 & 0xF
    dut.c_i.value = ci0 & 0xFFFFFFFF

    errors = []
    for a, b, ci, exp in cases[1:]:
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        c_o = to_signed32(dut.c_o.value)
        if c_o != exp0:
            errors.append(f"a={a0},b={b0},c_i={ci0}: expected {exp0}, got {c_o}")
        dut.a_i.value = a & 0xF
        dut.b_i.value = b & 0xF
        dut.c_i.value = ci & 0xFFFFFFFF
        a0, b0, ci0, exp0 = a, b, ci, exp

    # Final cycle
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(dut.c_o.value)
    if c_o != exp0:
        errors.append(f"last: expected {exp0}, got {c_o}")

    assert not errors, f"{len(errors)} failures:\n" + "\n".join(errors[:5])


@cocotb.test()
async def test_zero_factor(dut):
    """a=0 → c_o=c_i regardless of b; b=0 → c_o=c_i regardless of a."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    for b in range(-8, 8):
        dut.a_i.value = 0
        dut.b_i.value = b & 0xF
        dut.c_i.value = 42
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        c_o = to_signed32(dut.c_o.value)
        assert c_o == 42, f"a=0, b={b}: expected 42, got {c_o}"

    for a in range(-8, 8):
        dut.a_i.value = a & 0xF
        dut.b_i.value = 0
        dut.c_i.value = 42
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        c_o = to_signed32(dut.c_o.value)
        assert c_o == 42, f"a={a}, b=0: expected 42, got {c_o}"


@cocotb.test()
async def test_boundary_products(dut):
    """Verify corner INT4 products: max*max, min*min, max*min."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    cases = [
        (7,  7,  49),
        (-8, -8, 64),
        (7,  -8, -56),
        (-8,  7, -56),
        (-1, -1,  1),
        (-1,  1, -1),
    ]
    for a, b, expected in cases:
        dut.a_i.value = a & 0xF
        dut.b_i.value = b & 0xF
        dut.c_i.value = 0
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        c_o = to_signed32(dut.c_o.value)
        assert c_o == expected, f"a={a}, b={b}: expected {expected}, got {c_o}"


@cocotb.test()
async def test_sign_extension_across_accw(dut):
    """Negative products must be sign-extended to all 32 accumulator bits."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    # Accumulate -1 * -1 = 1 into a large negative c_i
    dut.a_i.value = 0xF   # -1 in INT4
    dut.b_i.value = 0xF   # -1 in INT4
    dut.c_i.value = 0xFFFFFF00  # -256 as INT32
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(dut.c_o.value)
    assert c_o == -255, f"expected -255 (-256+1), got {c_o}"

    # -8 * 7 = -56 added to +100
    dut.a_i.value = 0x8   # -8 in INT4
    dut.b_i.value = 7
    dut.c_i.value = 100
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(dut.c_o.value)
    assert c_o == 44, f"expected 44 (100-56), got {c_o}"

    # Verify upper bits are all-1 for negative result
    dut.a_i.value = 0x8   # -8
    dut.b_i.value = 1
    dut.c_i.value = 0      # c_o = -8
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    raw = int(dut.c_o.value) & 0xFFFFFFFF
    assert raw == 0xFFFFFFF8, f"expected 0xFFFFFFF8, got {raw:#010x}"
