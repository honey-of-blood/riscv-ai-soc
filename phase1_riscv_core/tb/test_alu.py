import cocotb
from cocotb.triggers import Timer
import random

# Must match alu.sv localparam encodings
ALU_ADD  = 0b0000
ALU_SUB  = 0b0001
ALU_AND  = 0b0010
ALU_OR   = 0b0011
ALU_XOR  = 0b0100
ALU_SLL  = 0b0101
ALU_SRL  = 0b0110
ALU_SRA  = 0b0111
ALU_SLT  = 0b1000
ALU_SLTU = 0b1001

MASK32 = 0xFFFFFFFF

def to_signed32(v):
    v &= MASK32
    return v - (1 << 32) if v >= (1 << 31) else v

def alu_model(a, b, ctrl):
    a &= MASK32
    b &= MASK32
    shamt = b & 0x1F
    if ctrl == ALU_ADD:  return (a + b) & MASK32
    if ctrl == ALU_SUB:  return (a - b) & MASK32
    if ctrl == ALU_AND:  return a & b
    if ctrl == ALU_OR:   return a | b
    if ctrl == ALU_XOR:  return a ^ b
    if ctrl == ALU_SLL:  return (a << shamt) & MASK32
    if ctrl == ALU_SRL:  return a >> shamt
    if ctrl == ALU_SRA:  return to_signed32(a) >> shamt & MASK32
    if ctrl == ALU_SLT:  return 1 if to_signed32(a) < to_signed32(b) else 0
    if ctrl == ALU_SLTU: return 1 if a < b else 0
    return 0

async def drive(dut, a, b, ctrl):
    dut.a.value = a & MASK32
    dut.b.value = b & MASK32
    dut.alu_ctrl.value = ctrl
    await Timer(1, unit="ns")           # let combinational logic settle
    result = int(dut.result.value)
    zero   = int(dut.zero.value)
    return result, zero

@cocotb.test()
async def test_all_operations(dut):
    """Exhaustive check: all 10 ops across fixed + random inputs."""
    errors = 0

    test_cases = [
        # (a, b, description)
        (0x00000005, 0x00000003, "small positive"),
        (0xFFFFFFFF, 0x00000001, "overflow/wrap"),
        (0x80000000, 0x80000000, "min signed"),
        (0x7FFFFFFF, 0x00000001, "max signed +1"),
        (0x00000000, 0x00000000, "zero"),
        (0xDEADBEEF, 0xCAFEBABE, "arbitrary"),
    ]
    # add 14 random cases
    random.seed(42)
    for _ in range(14):
        test_cases.append((random.randint(0, MASK32), random.randint(0, MASK32), "random"))

    ops = [ALU_ADD, ALU_SUB, ALU_AND, ALU_OR, ALU_XOR,
           ALU_SLL, ALU_SRL, ALU_SRA, ALU_SLT, ALU_SLTU]
    op_names = ["ADD","SUB","AND","OR","XOR","SLL","SRL","SRA","SLT","SLTU"]

    for a, b, desc in test_cases:
        for ctrl, name in zip(ops, op_names):
            expected = alu_model(a, b, ctrl)
            got, zero_got = await drive(dut, a, b, ctrl)
            zero_exp = 1 if expected == 0 else 0

            if got != expected or zero_got != zero_exp:
                dut._log.error(
                    f"FAIL {name} a=0x{a:08X} b=0x{b:08X} [{desc}]"
                    f" expected=0x{expected:08X} got=0x{got:08X}"
                    f" zero_exp={zero_exp} zero_got={zero_got}"
                )
                errors += 1

    total = len(test_cases) * len(ops)
    assert errors == 0, f"{errors}/{total} operations FAILED"
    dut._log.info(f"PASS: {total} operations correct (all 10 ops × {len(test_cases)} input pairs)")


@cocotb.test()
async def test_zero_flag(dut):
    """Zero flag must be 1 only when result == 0."""
    # SUB same value → result 0, zero=1
    result, zero = await drive(dut, 0xABCD1234, 0xABCD1234, ALU_SUB)
    assert result == 0 and zero == 1, f"Expected zero=1, got result={result} zero={zero}"

    # AND with 0 → result 0, zero=1
    result, zero = await drive(dut, 0xFFFFFFFF, 0x00000000, ALU_AND)
    assert result == 0 and zero == 1

    # ADD non-zero → zero=0
    result, zero = await drive(dut, 0x00000001, 0x00000001, ALU_ADD)
    assert zero == 0, f"Expected zero=0, got zero={zero}"

    dut._log.info("PASS: zero flag correct in all cases")


@cocotb.test()
async def test_slt_sign(dut):
    """SLT must treat operands as signed; SLTU as unsigned."""
    # Signed: 0x80000000 = -2147483648, less than 1
    result, _ = await drive(dut, 0x80000000, 0x00000001, ALU_SLT)
    assert result == 1, f"SLT: -2^31 < 1 should be 1, got {result}"

    # Unsigned: 0x80000000 > 1
    result, _ = await drive(dut, 0x80000000, 0x00000001, ALU_SLTU)
    assert result == 0, f"SLTU: 0x80000000 > 1 should be 0, got {result}"

    dut._log.info("PASS: SLT/SLTU sign handling correct")
