"""Phase 21 stress — structural coverage edge cases.

Tests things the base test_coverage.py explicitly avoids (boundary values,
div-by-zero semantics, shift extremes, SB/SH stores, AUIPC, JALR, long
forwarding chains, consecutive load-use stalls, ADD/SUB overflow).
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.dirname(__file__))

import cocotb
from cocotb.triggers import RisingEdge, Timer
from core_helpers import (start_core, reset_dut, run_program, read_registers,
                          DONE_ADDR, NOP, CLK_NS, _u32)
from prog_gen import (addi, add, sub, and_, or_, xor_, sll, srl, sra, slt, sltu,
                      andi, ori, xori, slti, sltiu, slli, srli, srai,
                      lw, lh, lb, lhu, lbu, sw, sh, sb,
                      mul, mulh, mulhsu, mulhu,
                      div_, divu, rem_, remu,
                      lui, auipc, jal, jalr, _b, _i, _j,
                      OP_IMM, OP_LOAD, OP_STORE, DONE_ADDR as GEN_DONE_ADDR)
from iss.rv32imac_iss import RV32IMISS

# Generous timeout for tests with multi-cycle DIV operations
DIV_TIMEOUT_MULT = 50


async def _run_and_read(dut, instrs, timeout=None):
    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = {}
    cyc  = timeout or (len(instrs) * 12 + 100)
    done = await run_program(dut, imem, dmem, cycles=cyc, stop_on_done=True)
    assert done, f"Done sentinel not seen within {cyc} cycles"
    return await read_registers(dut)


async def _run_with_dmem(dut, instrs, init_dmem, timeout=None):
    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = dict(init_dmem)
    cyc  = timeout or (len(instrs) * 12 + 100)
    done = await run_program(dut, imem, dmem, cycles=cyc, stop_on_done=True)
    assert done, f"Done sentinel not seen within {cyc} cycles"
    regs = await read_registers(dut)
    return regs, dmem


def _epilogue():
    return [sw(1, 16, 0), jal(0, 0)]


# ═══════════════════════════════════════════════════════════════════════════════
# 1. DIV/REM by zero — spec-defined semantics
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_div_by_zero_semantics(dut):
    """DIV(x,0)=−1, DIVU(x,0)=0xFFFFFFFF, REM(x,0)=x, REMU(x,0)=x per RISC-V spec."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 7),     # x1=7  (dividend)
        addi(2, 0, 0),     # x2=0  (zero divisor)
        lui(16, 0x1000),
    ] + [
        div_ (3, 1, 2),    # x3 = -1 = 0xFFFFFFFF
        divu (4, 1, 2),    # x4 = 0xFFFFFFFF
        rem_ (5, 1, 2),    # x5 = 7
        remu (6, 1, 2),    # x6 = 7
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs, timeout=len(instrs)*DIV_TIMEOUT_MULT+200)

    assert (regs[3] & 0xFFFFFFFF) == 0xFFFFFFFF, f"DIV/0: x3=0x{regs[3]&0xFFFFFFFF:08x}"
    assert (regs[4] & 0xFFFFFFFF) == 0xFFFFFFFF, f"DIVU/0: x4=0x{regs[4]&0xFFFFFFFF:08x}"
    assert (regs[5] & 0xFFFFFFFF) == 7,           f"REM/0: x5={regs[5]}"
    assert (regs[6] & 0xFFFFFFFF) == 7,           f"REMU/0: x6={regs[6]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 2. DIV/REM overflow: INT_MIN / −1
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_divrem_overflow(dut):
    """DIV(INT_MIN,−1)=INT_MIN, REM(INT_MIN,−1)=0 — spec-mandated overflow case."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        lui(1, 0x80000000),   # x1 = 0x80000000 = INT_MIN
        addi(2, 0, -1),       # x2 = 0xFFFFFFFF = −1
        lui(16, 0x1000),
    ] + [
        div_ (3, 1, 2),   # x3 = INT_MIN (overflow → saturate)
        rem_ (4, 1, 2),   # x4 = 0
        divu (5, 1, 2),   # x5 = 0x80000000 / 0xFFFFFFFF = 0 (unsigned small/large)
        remu (6, 1, 2),   # x6 = 0x80000000 % 0xFFFFFFFF = 0x80000000
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs, timeout=len(instrs)*DIV_TIMEOUT_MULT+200)

    assert (regs[3] & 0xFFFFFFFF) == 0x80000000, f"DIV overflow: x3=0x{regs[3]&0xFFFFFFFF:08x}"
    assert (regs[4] & 0xFFFFFFFF) == 0,           f"REM overflow: x4={regs[4]}"
    # DIVU: 0x80000000 / 0xFFFFFFFF = 0 (since 0x80000000 < 0xFFFFFFFF unsigned)
    assert (regs[5] & 0xFFFFFFFF) == 0,            f"DIVU INT_MIN/-1: x5={regs[5]}"
    assert (regs[6] & 0xFFFFFFFF) == 0x80000000,  f"REMU INT_MIN/-1: x6=0x{regs[6]&0xFFFFFFFF:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 3. Shift by 0 (all six shift instructions)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_shift_by_zero(dut):
    """Shift by 0 must leave the value unchanged for SLL/SRL/SRA/SLLI/SRLI/SRAI."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, -1),    # x1 = 0xFFFFFFFF
        addi(2, 0, 0),     # x2 = 0 (shift amount register)
        lui(16, 0x1000),
    ] + [
        sll (3, 1, 2),   # x3 = 0xFFFFFFFF << 0 = 0xFFFFFFFF
        srl (4, 1, 2),   # x4 = 0xFFFFFFFF >> 0 = 0xFFFFFFFF
        sra (5, 1, 2),   # x5 = arithmetic >> 0 = 0xFFFFFFFF
        slli(6, 1, 0),   # x6 = 0xFFFFFFFF
        srli(7, 1, 0),   # x7 = 0xFFFFFFFF
        srai(8, 1, 0),   # x8 = 0xFFFFFFFF
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    for r in range(3, 9):
        got = regs[r] & 0xFFFFFFFF
        assert got == 0xFFFFFFFF, f"shift-by-0: x{r}=0x{got:08x} expected 0xFFFFFFFF"


# ═══════════════════════════════════════════════════════════════════════════════
# 4. Shift by 31 (all six shift instructions)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_shift_by_31(dut):
    """Shift by 31 — MSB/LSB extraction, sign fill for SRA."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, -1),    # x1 = 0xFFFFFFFF (all ones)
        addi(2, 0, 1),     # x2 = 1 (positive test value)
        addi(3, 0, 31),    # x3 = 31 (shift amount register)
        lui(16, 0x1000),
    ] + [
        sll (4, 2, 3),   # x4 = 1 << 31 = 0x80000000
        srl (5, 1, 3),   # x5 = 0xFFFFFFFF >> 31 = 1
        sra (6, 1, 3),   # x6 = arithmetic -1 >> 31 = 0xFFFFFFFF (all sign bits)
        slli(7, 2, 31),  # x7 = 1 << 31 = 0x80000000
        srli(8, 1, 31),  # x8 = 0xFFFFFFFF >> 31 = 1
        srai(9, 1, 31),  # x9 = 0xFFFFFFFF (arithmetic -1 >> 31)
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    expected = {
        4: 0x80000000, 5: 1, 6: 0xFFFFFFFF,
        7: 0x80000000, 8: 1, 9: 0xFFFFFFFF,
    }
    for r, e in expected.items():
        got = regs[r] & 0xFFFFFFFF
        assert got == e, f"shift-by-31: x{r}=0x{got:08x} expected 0x{e:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 5. ADD overflow / SUB underflow (unsigned wrap-around)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_add_sub_overflow(dut):
    """ADD wraps at 2^32, SUB wraps below 0 — unsigned modular arithmetic."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, -1),    # x1 = 0xFFFFFFFF (max unsigned)
        addi(2, 0, 1),     # x2 = 1
        addi(3, 0, 0),     # x3 = 0 (min unsigned)
        lui(16, 0x1000),
    ] + [
        add(4, 1, 2),    # x4 = 0xFFFFFFFF + 1 = 0 (overflow wrap)
        add(5, 1, 1),    # x5 = 0xFFFFFFFF + 0xFFFFFFFF = 0xFFFFFFFE (wrap)
        sub(6, 3, 2),    # x6 = 0 - 1 = 0xFFFFFFFF (underflow wrap)
        sub(7, 2, 1),    # x7 = 1 - 0xFFFFFFFF = 2 (1 - (-1) = 2)
        add(8, 4, 2),    # x8 = 0 + 1 = 1 (verify wrap then add)
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    expected = {
        4: 0x00000000, 5: 0xFFFFFFFE,
        6: 0xFFFFFFFF, 7: 0x00000002,
        8: 0x00000001,
    }
    for r, e in expected.items():
        got = regs[r] & 0xFFFFFFFF
        assert got == e, f"overflow: x{r}=0x{got:08x} expected 0x{e:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 6. SLTU/SLTIU unsigned boundary comparisons
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_sltu_unsigned_boundary(dut):
    """SLTU/SLTIU with max-unsigned, 0, and sign-extension traps."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, -1),   # x1 = 0xFFFFFFFF (max unsigned)
        addi(2, 0, 0),    # x2 = 0
        addi(3, 0, 1),    # x3 = 1
        lui(16, 0x1000),
    ] + [
        sltu(4, 2, 1),    # x4 = 1  (0 < 0xFFFF unsigned)
        sltu(5, 1, 2),    # x5 = 0  (0xFFFF NOT < 0)
        sltu(6, 3, 3),    # x6 = 0  (1 NOT < 1, same register)
        sltiu(7, 1, 1),   # x7 = 0  (0xFFFF NOT < 1 unsigned: 0xFFFF > 1)
        sltiu(8, 2, 1),   # x8 = 1  (0 < 1 unsigned)
        # SLT: signed −1 < 0 is TRUE
        slt(9, 1, 2),     # x9 = 1  (signed −1 < 0)
        slt(10, 2, 1),    # x10= 0  (signed 0 NOT < −1)
        # SLTI: signed comparison with immediate
        slti(11, 1, 0),   # x11= 1  (signed x1=−1 < imm=0)
        slti(12, 2, 0),   # x12= 0  (signed x2=0 NOT < imm=0)
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    expected = {4: 1, 5: 0, 6: 0, 7: 0, 8: 1, 9: 1, 10: 0, 11: 1, 12: 0}
    for r, e in expected.items():
        got = regs[r] & 0xFFFFFFFF
        assert got == e, f"sltu_boundary: x{r}={got} expected {e}"


# ═══════════════════════════════════════════════════════════════════════════════
# 7. Three consecutive load-use stalls
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_three_consecutive_load_use_stalls(dut):
    """Chain of 3 load-use hazards: each loaded value immediately consumed."""
    start_core(dut)
    await reset_dut(dut)

    # mem[0x2000]=10  mem[0x2004]=20  mem[0x2008]=30
    instrs = [
        lui(17, 0x2000),    # x17 = 0x2000 (data base)
        lui(16, 0x1000),    # x16 = done addr
    ] + [
        lw(1, 17, 0),       # x1 = 10  (load-use stall 1)
        add(2, 1, 1),       # x2 = 20  (uses x1 immediately)
        lw(3, 17, 4),       # x3 = 20  (load-use stall 2)
        add(4, 3, 2),       # x4 = 40  (uses x3 immediately)
        lw(5, 17, 8),       # x5 = 30  (load-use stall 3)
        add(6, 5, 4),       # x6 = 70  (uses x5 immediately)
        add(7, 2, 4),       # x7 = 60  (MEM→EX forward from x2,x4)
    ] + _epilogue()

    regs, _ = await _run_with_dmem(
        dut, instrs,
        {0x2000 >> 2: 10, 0x2004 >> 2: 20, 0x2008 >> 2: 30})

    expected = {1: 10, 2: 20, 3: 20, 4: 40, 5: 30, 6: 70, 7: 60}
    for r, e in expected.items():
        got = regs[r] & 0xFFFFFFFF
        assert got == e, f"3-load-use: x{r}={got} expected {e}"


# ═══════════════════════════════════════════════════════════════════════════════
# 8. SH and SB stores — byte-lane routing verified
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_sh_sb_stores(dut):
    """SH (half-word) and SB (byte) stores followed by matching loads."""
    start_core(dut)
    await reset_dut(dut)

    # Store then reload using narrow stores
    instrs = [
        addi(1, 0, 0x5A),    # x1 = 0x5A (byte value)
        addi(2, 0, 0x234),   # x2 = 0x234 (halfword value; 0x1234 exceeds 12-bit signed)
        addi(3, 0, -1),      # x3 = 0xFFFFFFFF (verify only low bits stored)
        lui(17, 0x2000),     # x17 = data base
        lui(16, 0x1000),
    ] + [
        sw(0, 17, 0),         # clear mem[0x2000]
        sb(1, 17, 0),         # mem[0x2000] byte0 = 0x5A
        lbu(4, 17, 0),        # x4 = 0x5A (zero-extended)
        lb (5, 17, 0),        # x5 = 0x5A (positive, no sign-ext needed)
        sw(0, 17, 4),         # clear mem[0x2004]
        sh(2, 17, 4),         # mem[0x2004] half0 = 0x234
        lhu(6, 17, 4),        # x6 = 0x234
        lh (7, 17, 4),        # x7 = 0x234 (positive)
        # Negative byte: 0xFF → lb=-1
        addi(8, 0, -1),       # x8 = 0xFF in low byte (0xFFFFFFFF, sb takes low byte)
        sb(8, 17, 8),         # mem[0x2008] byte0 = 0xFF
        lbu(9, 17, 8),        # x9 = 0xFF (zero-extended)
        lb (10, 17, 8),       # x10 = -1 (sign-extended)
        # SB only stores the low byte — upper bits not touched
        sw(3, 17, 12),        # mem[0x200C] = 0xFFFFFFFF
        sb(1, 17, 12),        # byte0 of mem[0x200C] = 0x5A
        lw(11, 17, 12),       # x11 = 0xFFFFFF5A (upper bytes unchanged)
    ] + _epilogue()

    regs, _ = await _run_with_dmem(dut, instrs, {})

    expected = {
        4: 0x5A, 5: 0x5A,
        6: 0x234, 7: 0x234,
        9: 0xFF, 10: 0xFFFFFFFF,
        11: 0xFFFFFF5A,
    }
    for r, e in expected.items():
        got = regs[r] & 0xFFFFFFFF
        assert got == e, f"sh_sb: x{r}=0x{got:08x} expected 0x{e:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 9. AUIPC — PC-relative address formation
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_auipc_correctness(dut):
    """AUIPC rd = PC + upper_imm; verify at known instruction positions."""
    start_core(dut)
    await reset_dut(dut)

    # Fixed layout — position of each AUIPC is known at write time:
    #  word 0: lui x16,0x1000
    #  word 1: auipc x1,0x1000  → x1 = 4 + 0x1000 = 0x1004
    #  word 2: auipc x2,0x2000  → x2 = 8 + 0x2000 = 0x2008
    #  word 3: auipc x3,0       → x3 = 12          = 0x000C
    #  word 4: sw x1,0(x16)     — done sentinel
    #  word 5: jal x0,0

    instrs = [
        lui(16, 0x1000),
        auipc(1, 0x1000),    # PC=4  → x1 = 4 + 0x1000 = 0x1004
        auipc(2, 0x2000),    # PC=8  → x2 = 8 + 0x2000 = 0x2008
        auipc(3, 0),         # PC=12 → x3 = 12  = 0x000C
        sw(1, 16, 0),
        jal(0, 0),
    ]

    regs = await _run_and_read(dut, instrs)

    assert (regs[1] & 0xFFFFFFFF) == 0x1004, f"AUIPC@4: x1=0x{regs[1]&0xFFFFFFFF:08x}"
    assert (regs[2] & 0xFFFFFFFF) == 0x2008, f"AUIPC@8: x2=0x{regs[2]&0xFFFFFFFF:08x}"
    assert (regs[3] & 0xFFFFFFFF) == 0x000C, f"AUIPC@12 zero-offset: x3=0x{regs[3]&0xFFFFFFFF:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 10. JALR — link register + bit-0 clearing of target
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_jalr_correctness(dut):
    """JALR: rd = PC+4; target = (rs1+imm)&~1 (bit-0 always cleared)."""
    start_core(dut)
    await reset_dut(dut)

    # Layout:
    #  word 0: lui  x16, 0x1000
    #  word 1: addi x17, x0, 20   ; x17 = 20 (byte addr of word 5)
    #  word 2: jalr x5, x17, 0    ; x5 = PC+4 = 12; jump to 20 (word 5)
    #  word 3: addi x6, x0, 99    ; SKIPPED (not on taken path)
    #  word 4: addi x7, x0, 99    ; SKIPPED
    #  word 5: (JALR target)  addi x8, x0, 42
    #  word 6: sw x8, 0(x16)      ; done sentinel
    #  word 7: jal x0, 0
    # Also test bit-0 clearing: set x17=21 (odd), JALR target still 20

    instrs = [
        lui(16, 0x1000),
        addi(17, 0, 20),       # x17 = 20 = 5*4
        jalr(5, 17, 0),        # x5 = 12 (PC=8+4); jump to 20
        addi(6, 0, 99),        # skipped
        addi(7, 0, 99),        # skipped
        addi(8, 0, 42),        # JALR target: x8 = 42
        sw(8, 16, 0),
        jal(0, 0),
    ]

    regs = await _run_and_read(dut, instrs)

    assert (regs[5] & 0xFFFFFFFF) == 12, f"JALR link: x5={regs[5]} expected 12"
    assert (regs[6] & 0xFFFFFFFF) == 0,  f"JALR skipped: x6={regs[6]} expected 0"
    assert (regs[7] & 0xFFFFFFFF) == 0,  f"JALR skipped: x7={regs[7]} expected 0"
    assert (regs[8] & 0xFFFFFFFF) == 42, f"JALR target: x8={regs[8]} expected 42"

    # Bit-0 clearing test
    start_core(dut)
    await reset_dut(dut)

    instrs2 = [
        lui(16, 0x1000),
        addi(17, 0, 21),       # x17 = 21 (ODD) → bit-0 cleared → target = 20
        jalr(5, 17, 0),        # x5 = 12; jump to 21&~1 = 20 (word 5)
        addi(6, 0, 99),        # skipped
        addi(7, 0, 99),        # skipped
        addi(8, 0, 42),        # still word 5 (byte 20) — target
        sw(8, 16, 0),
        jal(0, 0),
    ]

    regs2 = await _run_and_read(dut, instrs2)

    assert (regs2[8] & 0xFFFFFFFF) == 42, f"JALR bit0 clear: x8={regs2[8]} expected 42"
    assert (regs2[6] & 0xFFFFFFFF) == 0,  f"JALR bit0 skip: x6={regs2[6]} should be 0"


# ═══════════════════════════════════════════════════════════════════════════════
# 11. XOR self-clear and SUB self-zero
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_xor_self_and_sub_self(dut):
    """XOR x,x,x = 0  and  SUB x,x,x = 0 for multiple registers."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 0x5A),
        addi(2, 0, -1),
        addi(3, 0, 0x12345678 & 0xFFF),  # lower 12-bit of large const
        lui(16, 0x1000),
    ] + [
        xor_(4, 1, 1),   # x4 = 0
        xor_(5, 2, 2),   # x5 = 0
        sub (6, 1, 1),   # x6 = 0
        sub (7, 2, 2),   # x7 = 0
        sub (8, 3, 3),   # x8 = 0
        # AND x,x = x (identity)
        and_(9, 2, 2),   # x9 = 0xFFFFFFFF (−1 AND −1 = −1)
        # OR x,x = x (identity)
        or_ (10, 1, 1),  # x10 = 0x5A
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    for r in [4, 5, 6, 7, 8]:
        assert (regs[r] & 0xFFFFFFFF) == 0, f"self-zero: x{r}={regs[r]}"
    assert (regs[9]  & 0xFFFFFFFF) == 0xFFFFFFFF, f"AND identity: x9=0x{regs[9]&0xFFFFFFFF:08x}"
    assert (regs[10] & 0xFFFFFFFF) == 0x5A,       f"OR identity: x10=0x{regs[10]&0xFFFFFFFF:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 12. Consecutive taken branches (4 in a row)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_four_consecutive_taken_branches(dut):
    """Four taken branches in rapid succession — tests multiple consecutive pipeline flushes."""
    start_core(dut)
    await reset_dut(dut)

    # Each taken branch increments a counter; NOPs after each branch are skipped.
    # Final x10 = 4 means all four branches were taken correctly.
    # Pattern: beq x0,x0 (always taken), skip 1 NOP, set sentinel.
    instrs = [
        addi(10, 0, 0),    # x10 = 0 (branch counter)
        lui(16, 0x1000),
    ]
    # 4 taken branches with increment
    for _ in range(4):
        instrs += [
            _b(8, 0, 0, 0),      # beq x0,x0, +8 (always taken; skip addi x10,-1)
            addi(10, 0, -1),     # SKIPPED if taken
            addi(10, 10, 1),     # x10++ (branch target)
        ]
    instrs += _epilogue()

    regs = await _run_and_read(dut, instrs)
    assert (regs[10] & 0xFFFFFFFF) == 4, f"4 consecutive branches: x10={regs[10]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 13. Long ALU forwarding chain (12-deep dependency)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_deep_forwarding_chain(dut):
    """12-deep chain of dependent ADDs: x=x+1 twelve times from x=0 → x=12."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 0),     # x1 = 0
        lui(16, 0x1000),
    ]
    for _ in range(12):
        instrs.append(addi(1, 1, 1))   # x1++ (each uses EX→EX forwarded result)

    instrs += _epilogue()

    regs = await _run_and_read(dut, instrs)
    assert (regs[1] & 0xFFFFFFFF) == 12, f"12-deep chain: x1={regs[1]} expected 12"


# ═══════════════════════════════════════════════════════════════════════════════
# 14. LUI with large upper immediate + ADDI lower 12 bits (PC-agnostic 32-bit const)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_lui_addi_large_constant(dut):
    """LUI+ADDI constructs 32-bit constants; negative lower offset handled correctly."""
    start_core(dut)
    await reset_dut(dut)

    # 0xDEADBEEF = 0xDEADB000 + 0xEEF
    # But ADDI sign-extends 12-bit imm: 0xEEF = 3823. As signed 12-bit: -(4096-3823) = -273.
    # So we need upper part adjusted: 0xDEADB000 + 0xEEF.
    # Correct split: LUI(0xDEADC) + ADDI(-0x111) ?
    # Easier test: use 0x12345678
    # 0x12345678 = 0x12345000 + 0x678
    # 0x678 as signed 12-bit = 1656 (positive) → upper = 0x12345, lower = 0x678
    instrs = [
        lui(1, 0x12345000),    # x1 = 0x12345000
        addi(1, 1, 0x678),     # x1 = 0x12345678
        # Negative lower half: 0xABCDE000 + 0x??? where lower is negative
        # 0x80001234: upper = 0x80001, lower = 0x234 (positive, no correction needed)
        lui(2, 0x80001000),    # x2 = 0x80001000
        addi(2, 2, 0x234),     # x2 = 0x80001234
        lui(16, 0x1000),
    ] + _epilogue()

    regs = await _run_and_read(dut, instrs)

    assert (regs[1] & 0xFFFFFFFF) == 0x12345678, f"LUI+ADDI: x1=0x{regs[1]&0xFFFFFFFF:08x}"
    assert (regs[2] & 0xFFFFFFFF) == 0x80001234, f"LUI+ADDI neg: x2=0x{regs[2]&0xFFFFFFFF:08x}"


# ═══════════════════════════════════════════════════════════════════════════════
# 15. ISS-comparison for the boundary-value programs above (golden sanity)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_iss_boundary_seed100(dut):
    """Random seed=100 with all boundary-triggering fractions enabled."""
    from core_helpers import start_core, reset_dut, run_program, read_registers, DONE_ADDR
    from prog_gen import gen_program
    from iss.rv32imac_iss import RV32IMISS

    start_core(dut)
    await reset_dut(dut)

    instrs, iss_steps, _ = gen_program(
        n_body=30, seed=100,
        m_ext_frac=0.10, branch_frac=0.10, div_frac=0.10)

    iss = RV32IMISS()
    iss.load(instrs)
    iss_regs = iss.run_n(iss_steps)

    imem = {i: instrs[i] for i in range(len(instrs))}
    timeout = len(instrs) * 50 + 300

    done = await run_program(dut, imem, {}, cycles=timeout, stop_on_done=True)
    assert done, f"Done sentinel not seen"

    dut_regs = await read_registers(dut)
    mismatches = []
    for r in range(1, 17):
        iv = iss_regs[r] & 0xFFFFFFFF
        dv = dut_regs[r] & 0xFFFFFFFF
        if iv != dv:
            mismatches.append(f"x{r:02d}: ISS=0x{iv:08x} DUT=0x{dv:08x}")
    assert not mismatches, "\n".join(mismatches)
