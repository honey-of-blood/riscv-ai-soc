import cocotb
from cocotb.triggers import Timer

# ---------------------------------------------------------------------------
# RV32I instruction encoders — build 32-bit words from field values
# ---------------------------------------------------------------------------

def sign_ext(val, bits):
    """Sign-extend an n-bit value to a Python int."""
    if val & (1 << (bits - 1)):
        val -= (1 << bits)
    return val & 0xFFFFFFFF

def mk_i(imm12, rs1, funct3, rd, opcode):
    """Encode an I-type instruction."""
    return ((imm12 & 0xFFF) << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode

def mk_s(imm12, rs2, rs1, funct3, opcode):
    """Encode an S-type instruction."""
    hi = (imm12 >> 5) & 0x7F
    lo = imm12 & 0x1F
    return (hi << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (lo << 7) | opcode

def mk_b(imm13, rs2, rs1, funct3, opcode):
    """Encode a B-type instruction (imm13 is the signed offset, LSB always 0)."""
    i = imm13 & 0x1FFF         # 13-bit value
    b12  = (i >> 12) & 1
    b11  = (i >> 11) & 1
    b10_5 = (i >> 5) & 0x3F
    b4_1  = (i >> 1) & 0xF
    return (b12 << 31) | (b10_5 << 25) | (rs2 << 20) | (rs1 << 15) | \
           (funct3 << 12) | (b4_1 << 8) | (b11 << 7) | opcode

def mk_u(imm20, rd, opcode):
    """Encode a U-type instruction (imm20 are the upper 20 bits)."""
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | opcode

def mk_j(imm21, rd, opcode):
    """Encode a J-type instruction (imm21 is signed offset, LSB always 0)."""
    i = imm21 & 0x1FFFFF
    b20    = (i >> 20) & 1
    b10_1  = (i >> 1)  & 0x3FF
    b11    = (i >> 11) & 1
    b19_12 = (i >> 12) & 0xFF
    return (b20 << 31) | (b19_12 << 12) | (b11 << 20) | (b10_1 << 21) | \
           (rd << 7) | opcode

# Opcodes
OP_LOAD   = 0b000_0011
OP_IMM    = 0b001_0011
OP_JALR   = 0b110_0111
OP_STORE  = 0b010_0011
OP_BRANCH = 0b110_0011
OP_LUI    = 0b011_0111
OP_AUIPC  = 0b001_0111
OP_JAL    = 0b110_1111


async def drive(dut, instr):
    dut.instr.value = instr & 0xFFFFFFFF
    await Timer(1, unit="ns")
    return int(dut.imm.value)


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_i_type(dut):
    """I-type: ADDI, LW, JALR — positive and negative immediates."""
    cases = [
        # (imm12_raw, expected_signed_result, description)
        (0x7FF,  sign_ext(0x7FF, 12), "max positive +2047"),
        (0x800,  sign_ext(0x800, 12), "min negative -2048"),
        (0xFFF,  sign_ext(0xFFF, 12), "-1"),
        (0x001,  sign_ext(0x001, 12), "+1"),
        (0x000,  0,                   "zero"),
        (0x555,  sign_ext(0x555, 12), "0x555"),
        (0xABC,  sign_ext(0xABC, 12), "0xABC negative"),
    ]
    errors = 0
    for imm12, expected, desc in cases:
        for opcode in [OP_LOAD, OP_IMM, OP_JALR]:
            instr = mk_i(imm12, 1, 0, 1, opcode)
            got = await drive(dut, instr)
            if got != expected & 0xFFFFFFFF:
                dut._log.error(f"I-type {desc} op=0b{opcode:07b}: "
                               f"expected 0x{expected & 0xFFFFFFFF:08X}, got 0x{got:08X}")
                errors += 1
    assert errors == 0
    dut._log.info("PASS: I-type immediates correct")


@cocotb.test()
async def test_s_type(dut):
    """S-type: SW, SH, SB — split immediate reconstructed correctly."""
    cases = [
        (0x7FF, sign_ext(0x7FF, 12), "+2047"),
        (0x800, sign_ext(0x800, 12), "-2048"),
        (0xFFF, sign_ext(0xFFF, 12), "-1"),
        (0x01F, sign_ext(0x01F, 12), "low-bits only (imm[4:0])"),
        (0xFE0, sign_ext(0xFE0, 12), "high-bits only (imm[11:5])"),
        (0x555, sign_ext(0x555, 12), "alternating bits"),
    ]
    errors = 0
    for imm12, expected, desc in cases:
        instr = mk_s(imm12, 2, 1, 0b010, OP_STORE)
        got = await drive(dut, instr)
        if got != expected & 0xFFFFFFFF:
            dut._log.error(f"S-type {desc}: expected 0x{expected & 0xFFFFFFFF:08X}, got 0x{got:08X}")
            errors += 1
    assert errors == 0
    dut._log.info("PASS: S-type immediates correct (split field reconstruction verified)")


@cocotb.test()
async def test_b_type(dut):
    """B-type: BEQ, BNE — scrambled bit positions reconstructed correctly."""
    cases = [
        (0x0002,  sign_ext(0x0002,  13), "+2 (min positive)"),
        (0x0FFE,  sign_ext(0x0FFE,  13), "+4094"),
        (0x1FFE,  sign_ext(0x1FFE,  13), "-2 (min negative)"),
        (0x1000,  sign_ext(0x1000,  13), "-4096 (most negative)"),
        (0x0100,  sign_ext(0x0100,  13), "bit[8] only"),
        (0x0800,  sign_ext(0x0800,  13), "bit[11] only"),
        (0x1000,  sign_ext(0x1000,  13), "bit[12] only (sign bit)"),
    ]
    errors = 0
    for imm13, expected, desc in cases:
        instr = mk_b(imm13, 2, 1, 0b000, OP_BRANCH)
        got = await drive(dut, instr)
        if got != expected & 0xFFFFFFFF:
            dut._log.error(f"B-type {desc}: expected 0x{expected & 0xFFFFFFFF:08X}, got 0x{got:08X}")
            errors += 1
    assert errors == 0
    dut._log.info("PASS: B-type immediates correct (bit[7] and bit[31] scramble verified)")


@cocotb.test()
async def test_u_type(dut):
    """U-type: LUI, AUIPC — upper 20 bits placed, lower 12 zeroed."""
    cases = [
        (0x12345, 0x12345000, "typical value"),
        (0xFFFFF, 0xFFFFF000, "all ones upper"),
        (0x00001, 0x00001000, "bit[12] only"),
        (0x80000, 0x80000000, "sign bit of result"),
        (0x00000, 0x00000000, "zero"),
    ]
    errors = 0
    for imm20, expected, desc in cases:
        for opcode in [OP_LUI, OP_AUIPC]:
            instr = mk_u(imm20, 1, opcode)
            got = await drive(dut, instr)
            if got != expected:
                dut._log.error(f"U-type {desc} op=0b{opcode:07b}: "
                               f"expected 0x{expected:08X}, got 0x{got:08X}")
                errors += 1
    assert errors == 0
    dut._log.info("PASS: U-type immediates correct (lower 12 bits zeroed)")


@cocotb.test()
async def test_j_type(dut):
    """J-type: JAL — four scattered fields reassembled correctly."""
    cases = [
        (0x000002,  sign_ext(0x000002,  21), "+2"),
        (0x000100,  sign_ext(0x000100,  21), "bit[8]"),
        (0x000800,  sign_ext(0x000800,  21), "bit[11]"),
        (0x001000,  sign_ext(0x001000,  21), "bit[12]"),
        (0x080000,  sign_ext(0x080000,  21), "bit[19]"),
        (0x100000,  sign_ext(0x100000,  21), "bit[20] (sign)"),
        (0x0FFFFE,  sign_ext(0x0FFFFE,  21), "max positive +1048574"),
        (0x100000,  sign_ext(0x100000,  21), "most negative"),
    ]
    errors = 0
    for imm21, expected, desc in cases:
        instr = mk_j(imm21, 1, OP_JAL)
        got = await drive(dut, instr)
        if got != expected & 0xFFFFFFFF:
            dut._log.error(f"J-type {desc}: expected 0x{expected & 0xFFFFFFFF:08X}, got 0x{got:08X}")
            errors += 1
    assert errors == 0
    dut._log.info("PASS: J-type immediates correct (all 4 scattered fields verified)")


@cocotb.test()
async def test_lsb_always_zero(dut):
    """B-type and J-type immediates must always have LSB=0 (word-aligned offsets)."""
    # B-type
    instr = mk_b(0x1FFE, 0, 0, 0, OP_BRANCH)
    got = await drive(dut, instr)
    assert (got & 1) == 0, f"B-type imm LSB not zero: 0x{got:08X}"

    # J-type
    instr = mk_j(0x1FFFFE, 0, OP_JAL)
    got = await drive(dut, instr)
    assert (got & 1) == 0, f"J-type imm LSB not zero: 0x{got:08X}"

    dut._log.info("PASS: B-type and J-type immediates have LSB=0")


@cocotb.test()
async def test_r_type_zero(dut):
    """R-type instruction (opcode=0110011) should produce imm=0."""
    r_type = 0x00000033  # ADD x0, x0, x0
    got = await drive(dut, r_type)
    assert got == 0, f"R-type: expected imm=0, got 0x{got:08X}"
    dut._log.info("PASS: R-type produces zero immediate")
