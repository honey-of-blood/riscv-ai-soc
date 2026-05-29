"""
Stress / corner-case tests for the RV32IM M-extension integration.
Complements test_m_ext.py — focuses on pipeline interactions, forwarding
chains, branch interactions, and arithmetic edge-cases not in the basic suite.

17 tests:
  1.  back_to_back_div          — two consecutive DIVs; mext_prev_stall must reset
  2.  div_result_forward        — DIV → ADD using result (EX/MEM→EX forward)
  3.  mul_chain                 — MUL → MUL with result as both operands
  4.  mul_branch_beq            — BEQ taken when condition uses MUL result
  5.  mulh_intmin_neg1          — MULH(INT_MIN, -1) = 0 (not overflow)
  6.  mulh_all_ones             — MULH(-1, -1) = 0  (upper32 of +1)
  7.  mulhu_carry               — MULHU(2, 0x80000000) = 1
  8.  mulhsu_intmin_umax        — MULHSU(INT_MIN, UINT_MAX) = 0x80000000
  9.  mulhsu_positive_rs1       — MULHSU(3, UINT_MAX) = 2 (rs1[31]=0 path)
  10. load_use_then_mul         — LW then MUL on loaded value (load-use hazard)
  11. div_uses_prev_div         — second DIV uses first DIV's quotient as divisor
  12. remu_zero_dividend        — REMU(0, 7) = 0
  13. div_rem_identity          — div(17,5)*5 + rem(17,5) == 17
  14. div_then_branch           — BNE taken using DIV result (MEM/WB→EX forward)
  15. five_consecutive_muls     — 5 MULs back-to-back, no phantom DIV stall
  16. divu_forward              — DIVU result forwarded to ADD
  17. rem_negative_forward      — REM(-13,4)=-1 forwarded to ADD

All tests run real RTL through the full pipeline.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# ---------------------------------------------------------------------------
# Instruction encoders
# ---------------------------------------------------------------------------
OP_R     = 0x33
OP_IMM   = 0x13
OP_STORE = 0x23
OP_LOAD  = 0x03
OP_LUI   = 0x37
OP_BRANCH= 0x63
NOP      = 0x00000013

FUNCT7_M = 0x01

def _r(f7, rs2, rs1, f3, rd):
    return (f7<<25)|(rs2<<20)|(rs1<<15)|(f3<<12)|(rd<<7)|OP_R

def _i(imm, rs1, f3, rd, op):
    return ((imm & 0xFFF)<<20)|(rs1<<15)|(f3<<12)|(rd<<7)|op

def _s(imm, rs2, rs1, f3):
    imm &= 0xFFF
    return (((imm>>5)&0x7F)<<25)|(rs2<<20)|(rs1<<15)|(f3<<12)|((imm&0x1F)<<7)|OP_STORE

def _b(imm, rs2, rs1, f3):
    imm &= 0x1FFF
    b12   = (imm >> 12) & 1
    b11   = (imm >> 11) & 1
    b10_5 = (imm >>  5) & 0x3F
    b4_1  = (imm >>  1) & 0xF
    return (b12<<31)|(b10_5<<25)|(rs2<<20)|(rs1<<15)|(f3<<12)|(b4_1<<8)|(b11<<7)|OP_BRANCH

def addi (rd,rs1,imm):  return _i(imm, rs1, 0x0, rd, OP_IMM)
def lui  (rd,imm):      return (((imm>>12)&0xFFFFF)<<12)|(rd<<7)|OP_LUI
def sw   (rs2,rs1,imm): return _s(imm, rs2, rs1, 0x2)
def lw   (rd,rs1,imm):  return _i(imm, rs1, 0x2, rd, OP_LOAD)
def add  (rd,rs1,rs2):  return _r(0x00, rs2, rs1, 0x0, rd)
def beq  (rs1,rs2,imm): return _b(imm, rs2, rs1, 0b000)
def bne  (rs1,rs2,imm): return _b(imm, rs2, rs1, 0b001)

def mul   (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x0, rd)
def mulh  (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x1, rd)
def mulhsu(rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x2, rd)
def mulhu (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x3, rd)
def div_  (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x4, rd)
def divu  (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x5, rd)
def rem_  (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x6, rd)
def remu  (rd,rs1,rs2): return _r(FUNCT7_M, rs2, rs1, 0x7, rd)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------
def u32(v): return v & 0xFFFF_FFFF

def _u32(sig):
    try:    return int(sig.value) & 0xFFFF_FFFF
    except: return 0

async def reset_dut(dut):
    dut.rst.value          = 1
    dut.imem_rdata_i.value = NOP
    dut.dmem_rdata_i.value = 0
    dut.dmem_stall_i.value = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0

async def run_program(dut, imem: dict, dmem: dict, cycles: int = 50):
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for _ in range(cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        iaddr = _u32(dut.imem_addr_o) >> 2
        dut.imem_rdata_i.value = imem.get(iaddr, NOP)
        daddr = _u32(dut.dmem_addr_o) >> 2
        if _u32(dut.dmem_we_o) & 1:
            be   = _u32(dut.dmem_be_o)
            wdat = _u32(dut.dmem_wdata_o)
            word = dmem.get(daddr, 0)
            for i in range(4):
                if (be >> i) & 1:
                    word = (word & ~(0xFF<<(8*i))) | (((wdat>>(8*i))&0xFF)<<(8*i))
            dmem[daddr] = word
        dut.dmem_rdata_i.value = dmem.get(daddr, 0)


# ===========================================================================
# 1. Back-to-back DIV — tests that mext_prev_stall resets between two divides
# ===========================================================================
@cocotb.test()
async def test_back_to_back_div(dut):
    """Two consecutive DIVs: div(100,7)=14 then div(50,3)=16."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 100),
        1: addi(2, 0, 7),
        2: div_(3, 1, 2),          # x3 = 14, stall 32 cycles
        3: addi(1, 0, 50),
        4: addi(2, 0, 3),
        5: div_(4, 1, 2),          # x4 = 16, stall 32 cycles
        6: sw(3, 0, 0),
        7: sw(4, 0, 4),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=200)
    assert dmem.get(0) == 14, f"first DIV: expected 14, got {dmem.get(0)}"
    assert dmem.get(1) == 16, f"second DIV: expected 16, got {dmem.get(1)}"


# ===========================================================================
# 2. DIV result forwarded to dependent ADD (EX/MEM → EX)
# ===========================================================================
@cocotb.test()
async def test_div_result_forward(dut):
    """DIV(42,6)=7 then ADD(x3,x3)=14 using EX/MEM forward."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 42),
        1: addi(2, 0, 6),
        2: div_(3, 1, 2),          # x3 = 7
        3: add(4, 3, 3),           # x4 = 14, EX/MEM→EX forward
        4: sw(4, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)
    assert dmem.get(0) == 14, f"DIV fwd: expected 14, got {dmem.get(0)}"


# ===========================================================================
# 3. MUL chain — MUL result forwarded as both operands to second MUL
# ===========================================================================
@cocotb.test()
async def test_mul_chain(dut):
    """mul(3,4)=12, then mul(12,12)=144 with EX/MEM→EX forwarding on both operands."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 3),
        1: addi(2, 0, 4),
        2: mul(3, 1, 2),           # x3 = 12
        3: mul(5, 3, 3),           # x5 = 144, both rs1=rs2=x3 from EX/MEM
        4: sw(5, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)
    assert dmem.get(0) == 144, f"MUL chain: expected 144, got {dmem.get(0)}"


# ===========================================================================
# 4. BEQ taken based on MUL result (MEM/WB forward to branch operand)
# ===========================================================================
@cocotb.test()
async def test_mul_branch_beq(dut):
    """mul(5,4)=20; beq(x3,x4) where x4=20 → taken; sentinel=99 at target."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # word 4 = beq; target = word 6 = byte(16)+8 = byte 24
    imem = {
        0: addi(1, 0, 5),
        1: addi(2, 0, 4),
        2: mul(3, 1, 2),           # x3 = 20
        3: addi(4, 0, 20),         # x4 = 20
        4: beq(3, 4, 8),           # branch to word 6 (offset=8)
        5: addi(5, 0, 1),          # should be flushed
        6: addi(5, 0, 99),         # branch target — sentinel
        7: sw(5, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=35)
    assert dmem.get(0) == 99, f"branch after MUL: expected 99, got {dmem.get(0)}"


# ===========================================================================
# 5. MULH(INT_MIN, -1) = 0  — (-2^31) × (-1) = 2^31 → upper32 = 0
# ===========================================================================
@cocotb.test()
async def test_mulh_intmin_neg1(dut):
    """MULH(0x80000000, -1) = 0 (upper32 of +2^31 = 0x0000_0000_8000_0000)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: lui(1, 0x80000000),     # x1 = INT_MIN
        1: addi(2, 0, -1),
        2: mulh(3, 1, 2),
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)
    assert dmem.get(0) == 0, f"MULH(INT_MIN,-1): expected 0, got {dmem.get(0, 0):#010x}"


# ===========================================================================
# 6. MULH(-1, -1) = 0  — (-1) × (-1) = 1 → upper32 = 0
# ===========================================================================
@cocotb.test()
async def test_mulh_all_ones(dut):
    """MULH(-1,-1) = 0 (upper32 of +1)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, -1),
        1: mulh(3, 1, 1),
        2: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=20)
    assert dmem.get(0) == 0, f"MULH(-1,-1): expected 0, got {dmem.get(0, 0):#010x}"


# ===========================================================================
# 7. MULHU(2, 0x80000000) = 1  — 2 × 2^31 = 2^32 → upper32 = 1
# ===========================================================================
@cocotb.test()
async def test_mulhu_carry(dut):
    """MULHU(2, 0x80000000) = 1 (tests carry into upper 32 bits)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 2),
        1: lui(2, 0x80000000),     # x2 = 0x8000_0000
        2: mulhu(3, 1, 2),
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)
    assert dmem.get(0) == 1, f"MULHU carry: expected 1, got {dmem.get(0, 0):#010x}"


# ===========================================================================
# 8. MULHSU(INT_MIN, UINT_MAX) = 0x80000000
# ===========================================================================
@cocotb.test()
async def test_mulhsu_intmin_umax(dut):
    """MULHSU(0x80000000, 0xFFFFFFFF) = 0x80000000."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: lui(1, 0x80000000),     # x1 = INT_MIN (rs1[31]=1)
        1: addi(2, 0, -1),         # x2 = 0xFFFF_FFFF
        2: mulhsu(3, 1, 2),
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)
    expected = 0x80000000
    assert u32(dmem.get(0, 0)) == expected, \
        f"MULHSU(INT_MIN,UINT_MAX): expected {expected:#010x}, got {dmem.get(0,0):#010x}"


# ===========================================================================
# 9. MULHSU(3, UINT_MAX) = 2  — positive rs1 (rs1[31]=0), no correction applied
# ===========================================================================
@cocotb.test()
async def test_mulhsu_positive_rs1(dut):
    """MULHSU(3, 0xFFFFFFFF) = 2: rs1[31]=0 so correction is zero, same as MULHU."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # 3 × 0xFFFF_FFFF = 0x2_FFFF_FFFD → upper32 = 2
    imem = {
        0: addi(1, 0, 3),
        1: addi(2, 0, -1),         # x2 = 0xFFFF_FFFF
        2: mulhsu(3, 1, 2),
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)
    assert dmem.get(0) == 2, f"MULHSU(3,UINT_MAX): expected 2, got {dmem.get(0, 0):#010x}"


# ===========================================================================
# 10. LW (load-use stall) immediately followed by MUL on the loaded value
# ===========================================================================
@cocotb.test()
async def test_load_use_then_mul(dut):
    """LW x2 then MUL(x2,3)=126; hazard unit inserts 1-cycle bubble, MEM/WB forwards."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # Pre-store 42 to mem[0] via the program itself before the LW.
    imem = {
        0: addi(1, 0, 42),
        1: sw(1, 0, 0),            # mem[0] = 42
        2: addi(3, 0, 3),          # x3 = 3
        3: lw(2, 0, 0),            # x2 = 42  (load-use: dependent MUL is next)
        4: mul(4, 2, 3),           # x4 = 42×3 = 126  (hazard stall + MEM/WB fwd)
        5: sw(4, 0, 4),            # mem[1] = 126
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=40)
    assert dmem.get(1) == 126, f"load-use+MUL: expected 126, got {dmem.get(1)}"


# ===========================================================================
# 11. Second DIV uses first DIV's quotient as its divisor
# ===========================================================================
@cocotb.test()
async def test_div_uses_prev_div(dut):
    """div(100,4)=25, then div(100,25)=4 using forwarded quotient as divisor."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 100),
        1: addi(2, 0, 4),
        2: div_(3, 1, 2),          # x3 = 25, stall 32 cycles
        3: div_(4, 1, 3),          # x4 = 100/25 = 4; x3 forwarded from EX/MEM as rs2
        4: sw(3, 0, 0),            # mem[0] = 25
        5: sw(4, 0, 4),            # mem[1] = 4
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=150)
    assert dmem.get(0) == 25, f"first DIV: expected 25, got {dmem.get(0)}"
    assert dmem.get(1) == 4,  f"second DIV: expected 4, got {dmem.get(1)}"


# ===========================================================================
# 12. REMU(0, 7) = 0  — zero dividend edge case
# ===========================================================================
@cocotb.test()
async def test_remu_zero_dividend(dut):
    """REMU(0, 7) = 0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 0),
        1: addi(2, 0, 7),
        2: remu(3, 1, 2),
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)
    assert dmem.get(0) == 0, f"REMU(0,7): expected 0, got {dmem.get(0)}"


# ===========================================================================
# 13. DIV / REM identity: div(17,5)*5 + rem(17,5) == 17
# ===========================================================================
@cocotb.test()
async def test_div_rem_identity(dut):
    """Verify q*d + r == n for n=17, d=5."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 17),         # n
        1: addi(2, 0, 5),          # d
        2: div_(3, 1, 2),          # x3 = 3  (q)
        3: rem_(4, 1, 2),          # x4 = 2  (r)
        4: mul(5, 3, 2),           # x5 = 3×5 = 15
        5: add(6, 5, 4),           # x6 = 15+2 = 17
        6: sw(6, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=180)
    assert dmem.get(0) == 17, f"DIV/REM identity: expected 17, got {dmem.get(0)}"


# ===========================================================================
# 14. BNE taken using DIV result forwarded to branch condition
# ===========================================================================
@cocotb.test()
async def test_div_then_branch(dut):
    """div(9,3)=3; bne(x3,x4=4) taken; sentinel=77 at target."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # word 4 = bne; offset=8 → target = byte(16)+8 = byte 24 = word 6
    imem = {
        0: addi(1, 0, 9),
        1: addi(2, 0, 3),
        2: div_(3, 1, 2),          # x3 = 3, stall 32 cycles
        3: addi(4, 0, 4),          # x4 = 4
        4: bne(3, 4, 8),           # branch to word 6 (3 ≠ 4)
        5: addi(5, 0, 1),          # flushed
        6: addi(5, 0, 77),         # branch target
        7: sw(5, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)
    assert dmem.get(0) == 77, f"branch after DIV: expected 77, got {dmem.get(0)}"


# ===========================================================================
# 15. Five consecutive MULs — no phantom 32-cycle stall from is_div_in_ex
# ===========================================================================
@cocotb.test()
async def test_five_consecutive_muls(dut):
    """5 back-to-back MULs; 2→4→16→256→65536. No divide stall, finishes in ~30 cy."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 2),
        1: mul(2, 1, 1),           # x2 = 4
        2: mul(3, 2, 2),           # x3 = 16
        3: mul(4, 3, 3),           # x4 = 256
        4: mul(5, 4, 4),           # x5 = 65536
        5: sw(4, 0, 0),            # mem[0] = 256
        6: sw(5, 0, 4),            # mem[1] = 65536
    }
    dmem = {}
    # Deliberately tight budget — passes only if there is no 32-cycle stall
    await run_program(dut, imem, dmem, cycles=30)
    assert dmem.get(0) == 256,   f"5 MULs x4: expected 256, got {dmem.get(0)}"
    assert dmem.get(1) == 65536, f"5 MULs x5: expected 65536, got {dmem.get(1)}"


# ===========================================================================
# 16. DIVU result forwarded to ADD
# ===========================================================================
@cocotb.test()
async def test_divu_forward(dut):
    """divu(0xFFFFFFFF, 2)=0x7FFFFFFF then add(x3,x3)=0xFFFFFFFE via EX/MEM fwd."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, -1),         # x1 = 0xFFFF_FFFF
        1: addi(2, 0, 2),
        2: divu(3, 1, 2),          # x3 = 0x7FFF_FFFF
        3: add(4, 3, 3),           # x4 = 0xFFFF_FFFE (EX/MEM fwd)
        4: sw(4, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)
    expected = 0xFFFF_FFFE
    assert u32(dmem.get(0, 0)) == expected, \
        f"DIVU fwd: expected {expected:#010x}, got {dmem.get(0, 0):#010x}"


# ===========================================================================
# 17. REM negative operand forwarded to ADD
# ===========================================================================
@cocotb.test()
async def test_rem_negative_forward(dut):
    """rem(-13,4)=-1; add(x3,x3)=-2 = 0xFFFFFFFE via EX/MEM forward."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, -13),        # x1 = -13
        1: addi(2, 0, 4),
        2: rem_(3, 1, 2),          # x3 = REM(-13,4) = -1
        3: add(4, 3, 3),           # x4 = -2 (EX/MEM fwd)
        4: sw(4, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)
    expected = u32(-2)
    assert u32(dmem.get(0, 0)) == expected, \
        f"REM neg fwd: expected {expected:#010x}, got {dmem.get(0, 0):#010x}"
