"""
Phase 15 fast_mul stress tests — boundary values, MULHSU, back-to-back.

Coverage beyond test_fast_mul.py:
  - 0xFFFFFFFF × 0xFFFFFFFF full 64-bit result
  - INT_MIN × INT_MIN signed (0x80000000 × 0x80000000)
  - MULHSU(-1, 0xFFFFFFFF): signed × unsigned boundary
  - MULHSU asymmetry: MULHSU(a,b) ≠ MULHSU(b,a) for mixed types
  - 20 back-to-back multiplies with incrementing operands
  - Identity (MUL(x, 1) = x)
  - MULH vs MULHU differ for operands with MSB=1
  - Consecutive sign changes: verify pipeline holds no residue
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


def s32(x):
    """Interpret 32-bit unsigned as signed Python int."""
    x &= 0xFFFFFFFF
    return x if x < 0x80000000 else x - 0x100000000


def expected_mul(a, b):
    """Lower 32 bits of unsigned multiply."""
    return (a * b) & 0xFFFFFFFF


def expected_mulh(a, b):
    """Upper 32 bits of signed × signed."""
    return ((s32(a) * s32(b)) >> 32) & 0xFFFFFFFF


def expected_mulhu(a, b):
    """Upper 32 bits of unsigned × unsigned."""
    return ((a & 0xFFFFFFFF) * (b & 0xFFFFFFFF) >> 32) & 0xFFFFFFFF


def expected_mulhsu(a, b):
    """Upper 32 bits of signed × unsigned."""
    return ((s32(a) * (b & 0xFFFFFFFF)) >> 32) & 0xFFFFFFFF


async def reset_dut(dut):
    dut.a_i.value = 0
    dut.b_i.value = 0
    dut.signed_i.value = 0
    dut.mixed_i.value = 0
    await Timer(20, unit="ns")


async def get_result(dut, a, b, signed_mul=False, mixed=False):
    await RisingEdge(dut.clk)
    dut.a_i.value = a & 0xFFFFFFFF
    dut.b_i.value = b & 0xFFFFFFFF
    dut.signed_i.value = 1 if signed_mul else 0
    dut.mixed_i.value = 1 if mixed else 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    return int(dut.result_o.value)


@cocotb.test()
async def test_maxval_unsigned_full(dut):
    """0xFFFFFFFF × 0xFFFFFFFF = 0xFFFFFFFE_00000001 (full 64-bit)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0xFFFFFFFF
    b = 0xFFFFFFFF
    result = await get_result(dut, a, b, signed_mul=False)

    lower = result & 0xFFFFFFFF
    upper = (result >> 32) & 0xFFFFFFFF

    assert lower == 0x00000001, f"MUL lower: expected 0x00000001, got {lower:#010x}"
    assert upper == 0xFFFFFFFE, f"MULHU upper: expected 0xFFFFFFFE, got {upper:#010x}"


@cocotb.test()
async def test_intmin_squared_signed(dut):
    """INT_MIN × INT_MIN: MUL lower = 0x00000000, MULH upper = 0x40000000.
    -2^31 × -2^31 = 2^62 = 0x4000_0000_0000_0000.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0x80000000
    b = 0x80000000

    result = await get_result(dut, a, b, signed_mul=True)
    lower = result & 0xFFFFFFFF
    upper = (result >> 32) & 0xFFFFFFFF

    assert lower == 0x00000000, f"MULH lower: expected 0, got {lower:#010x}"
    assert upper == 0x40000000, f"MULH upper: expected 0x40000000, got {upper:#010x}"


@cocotb.test()
async def test_mulhsu_neg1_max(dut):
    """MULHSU(-1, 0xFFFFFFFF): signed(-1) × unsigned(0xFFFFFFFF).
    = -1 × 4294967295 = -4294967295 = 0xFFFFFFFF_00000001 (full 64-bit)
    upper = 0xFFFFFFFF.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0xFFFFFFFF  # -1 signed
    b = 0xFFFFFFFF  # max unsigned
    result = await get_result(dut, a, b, signed_mul=False, mixed=True)

    upper = (result >> 32) & 0xFFFFFFFF
    expected_upper = expected_mulhsu(a, b)
    assert upper == expected_upper, \
        f"MULHSU(-1, max): upper={upper:#010x}, expected={expected_upper:#010x}"


@cocotb.test()
async def test_mulhsu_asymmetry(dut):
    """MULHSU(a, b) ≠ MULHSU(b, a) for a negative, b unsigned.
    The instruction treats the FIRST operand as signed, SECOND as unsigned.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0x80000000   # -2147483648 signed
    b = 0x00000003   # 3 unsigned

    result_ab = await get_result(dut, a, b, signed_mul=False, mixed=True)
    result_ba = await get_result(dut, b, a, signed_mul=False, mixed=True)

    upper_ab = (result_ab >> 32) & 0xFFFFFFFF
    upper_ba = (result_ba >> 32) & 0xFFFFFFFF

    exp_ab = expected_mulhsu(a, b)
    exp_ba = expected_mulhsu(b, a)

    assert upper_ab == exp_ab, f"MULHSU(a,b) upper={upper_ab:#010x}, expected={exp_ab:#010x}"
    assert upper_ba == exp_ba, f"MULHSU(b,a) upper={upper_ba:#010x}, expected={exp_ba:#010x}"
    assert upper_ab != upper_ba or exp_ab == exp_ba, \
        "MULHSU(a,b) and MULHSU(b,a) should differ when a is negative and b is unsigned"


@cocotb.test()
async def test_20_back_to_back(dut):
    """20 consecutive multiplications with incrementing operands — no pipeline residue."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    errors = []
    for i in range(20):
        a = (i * 7 + 3) & 0xFFFFFFFF
        b = (i * 13 + 5) & 0xFFFFFFFF
        result = await get_result(dut, a, b, signed_mul=False)
        lower = result & 0xFFFFFFFF
        expected = expected_mul(a, b)
        if lower != expected:
            errors.append(f"i={i}: a={a:#010x} b={b:#010x} got={lower:#010x} expected={expected:#010x}")

    assert not errors, "Back-to-back multiply errors:\n" + "\n".join(errors)


@cocotb.test()
async def test_identity(dut):
    """MUL(x, 1) = x for a range of values."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    test_vals = [0, 1, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF, 0xDEADBEEF, 42, 0x12345678]
    for x in test_vals:
        result = await get_result(dut, x, 1, signed_mul=False)
        lower = result & 0xFFFFFFFF
        assert lower == x & 0xFFFFFFFF, \
            f"MUL({x:#010x}, 1): expected {x & 0xFFFFFFFF:#010x}, got {lower:#010x}"


@cocotb.test()
async def test_mulh_vs_mulhu_differ(dut):
    """MULH and MULHU give different upper halves for the same bit pattern when
    the sign interpretation matters: a=0xFFFFFFFF (-1 signed, max unsigned), b=2."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # a=0xFFFFFFFF, b=2:
    #   MULH  (signed):   (-1) × 2   = -2         → upper = 0xFFFFFFFF
    #   MULHU (unsigned): (2^32-1)×2 = 2^33-2     → upper = 0x00000001
    a = 0xFFFFFFFF
    b = 0x00000002

    result_signed = await get_result(dut, a, b, signed_mul=True)
    result_unsigned = await get_result(dut, a, b, signed_mul=False)

    upper_s = (result_signed >> 32) & 0xFFFFFFFF
    upper_u = (result_unsigned >> 32) & 0xFFFFFFFF

    exp_s = expected_mulh(a, b)    # 0xFFFFFFFF
    exp_u = expected_mulhu(a, b)   # 0x00000001

    assert upper_s == exp_s, f"MULH upper={upper_s:#010x}, expected={exp_s:#010x}"
    assert upper_u == exp_u, f"MULHU upper={upper_u:#010x}, expected={exp_u:#010x}"
    assert upper_s != upper_u, \
        f"MULH and MULHU should differ: MULH={upper_s:#010x}, MULHU={upper_u:#010x}"


@cocotb.test()
async def test_consecutive_sign_changes(dut):
    """Alternate between signed and unsigned multiplications; verify no state leaks."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    pairs = [
        (0xFFFFFFFE, 0x00000003, True),   # -2 × 3 signed
        (0xFFFFFFFE, 0x00000003, False),  # same bits, unsigned
        (0x7FFFFFFF, 0x00000002, True),   # INT_MAX × 2 signed
        (0x7FFFFFFF, 0x00000002, False),  # same bits, unsigned
        (0x80000001, 0x80000001, True),   # both negative signed
        (0x80000001, 0x80000001, False),  # both MSB=1 unsigned
    ]

    for a, b, is_signed in pairs:
        result = await get_result(dut, a, b, signed_mul=is_signed)
        upper = (result >> 32) & 0xFFFFFFFF
        lower = result & 0xFFFFFFFF

        if is_signed:
            expected_u = expected_mulh(a, b)
        else:
            expected_u = expected_mulhu(a, b)
        expected_l = expected_mul(a, b)

        assert lower == expected_l, \
            f"a={a:#010x} b={b:#010x} signed={is_signed}: lower={lower:#010x}, expected={expected_l:#010x}"
        assert upper == expected_u, \
            f"a={a:#010x} b={b:#010x} signed={is_signed}: upper={upper:#010x}, expected={expected_u:#010x}"
