"""
Phase 15 fast_mul unit tests.
The multiplier is registered — result is available 1 cycle after inputs are set.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


async def reset_dut(dut):
    dut.a_i.value = 0
    dut.b_i.value = 0
    dut.signed_i.value = 0
    dut.mixed_i.value = 0
    await Timer(20, unit="ns")


async def get_result(dut, a, b, signed_mul=False, mixed=False):
    """Set inputs on posedge, wait one clock cycle, read result."""
    await RisingEdge(dut.clk)
    dut.a_i.value = a & 0xFFFFFFFF
    dut.b_i.value = b & 0xFFFFFFFF
    dut.signed_i.value = 1 if signed_mul else 0
    dut.mixed_i.value = 1 if mixed else 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    return int(dut.result_o.value)


@cocotb.test()
async def test_mul_basic(dut):
    """MUL 5 × 7 = 35."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    result = await get_result(dut, 5, 7, signed_mul=False)
    assert (result & 0xFFFFFFFF) == 35, f"MUL 5×7: expected 35, got {result & 0xFFFFFFFF}"


@cocotb.test()
async def test_mulh_signed(dut):
    """MULH: signed(-2) × signed(3) → full 64-bit = -6 → upper 32 = 0xFFFFFFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # -2 in 32-bit two's complement = 0xFFFFFFFE
    a = 0xFFFFFFFE  # -2
    b = 3
    result = await get_result(dut, a, b, signed_mul=True)
    # -2 × 3 = -6; 64-bit signed -6 = 0xFFFFFFFF_FFFFFFFA
    expected_full = 0xFFFFFFFFFFFFFFFA
    upper32 = (result >> 32) & 0xFFFFFFFF
    assert upper32 == 0xFFFFFFFF, \
        f"MULH(-2,3) upper32: expected 0xFFFFFFFF, got {upper32:#010x}"


@cocotb.test()
async def test_mulhu_unsigned(dut):
    """MULHU: 0xFFFFFFFF × 0xFFFFFFFF upper 32 = 0xFFFFFFFE."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0xFFFFFFFF
    b = 0xFFFFFFFF
    result = await get_result(dut, a, b, signed_mul=False, mixed=False)
    # 0xFFFFFFFF × 0xFFFFFFFF = 0xFFFFFFFE_00000001
    upper32 = (result >> 32) & 0xFFFFFFFF
    assert upper32 == 0xFFFFFFFE, \
        f"MULHU upper32: expected 0xFFFFFFFE, got {upper32:#010x}"


@cocotb.test()
async def test_mul_zero(dut):
    """Any × 0 = 0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    result = await get_result(dut, 0xDEADBEEF, 0, signed_mul=False)
    assert result == 0, f"MUL x×0: expected 0, got {result:#018x}"

    result = await get_result(dut, 0, 0xCAFEBABE, signed_mul=False)
    assert result == 0, f"MUL 0×x: expected 0, got {result:#018x}"


@cocotb.test()
async def test_mul_overflow(dut):
    """0x80000000 × 2: lower 32 = 0x00000000; MULH (signed) = 0xFFFFFFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    a = 0x80000000  # -2147483648 signed
    b = 2

    # Unsigned lower 32: 0x80000000 × 2 = 0x100000000, lower = 0
    result_u = await get_result(dut, a, b, signed_mul=False)
    lower32 = result_u & 0xFFFFFFFF
    assert lower32 == 0x00000000, f"MUL lower32: expected 0x00000000, got {lower32:#010x}"

    # Signed MULH: -2147483648 × 2 = -4294967296 = 0xFFFFFFFF_00000000
    result_s = await get_result(dut, a, b, signed_mul=True)
    upper32 = (result_s >> 32) & 0xFFFFFFFF
    assert upper32 == 0xFFFFFFFF, f"MULH upper32: expected 0xFFFFFFFF, got {upper32:#010x}"
