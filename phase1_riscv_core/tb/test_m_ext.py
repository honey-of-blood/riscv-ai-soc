"""
RV32IM M-extension tests for riscv_core.sv.

Tests run programs through the full pipeline and inspect data memory.
All eight M-extension instructions are covered:
  MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU

Edge cases tested:
  - Division by zero  (quotient = -1, remainder = dividend per RV32IM spec)
  - INT_MIN / -1      (quotient = INT_MIN, remainder = 0 per RV32IM spec)
  - Negative operands (signed vs unsigned differences)
  - Forwarding after MUL result

Memory convention: same as test_riscv_core.py — word-addressed (keys are addr >> 2).
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# ---------------------------------------------------------------------------
# Instruction encoding helpers (same conventions as test_riscv_core.py)
# ---------------------------------------------------------------------------
OP_R     = 0x33
OP_IMM   = 0x13
OP_STORE = 0x23
OP_LOAD  = 0x03
OP_LUI   = 0x37
NOP      = 0x00000013

FUNCT7_MEXT = 0x01   # RV32IM M-extension funct7 = 7'b0000001

def _r(funct7, rs2, rs1, funct3, rd):
    return (funct7<<25)|(rs2<<20)|(rs1<<15)|(funct3<<12)|(rd<<7)|OP_R

def _i(imm, rs1, funct3, rd, op):
    return ((imm & 0xFFF)<<20)|(rs1<<15)|(funct3<<12)|(rd<<7)|op

def _s(imm, rs2, rs1, funct3):
    imm &= 0xFFF
    return (((imm>>5)&0x7F)<<25)|(rs2<<20)|(rs1<<15)|(funct3<<12)|((imm&0x1F)<<7)|OP_STORE

def addi(rd, rs1, imm):   return _i(imm, rs1, 0x0, rd, OP_IMM)
def lui (rd, imm):        return (((imm>>12)&0xFFFFF)<<12)|(rd<<7)|OP_LUI
def sw  (rs2, rs1, imm):  return _s(imm, rs2, rs1, 0x2)

# M-extension instruction encoders (funct7 = 0x01)
def mul   (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x0, rd)
def mulh  (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x1, rd)
def mulhsu(rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x2, rd)
def mulhu (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x3, rd)
def div_  (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x4, rd)
def divu  (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x5, rd)
def rem_  (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x6, rd)
def remu  (rd, rs1, rs2): return _r(FUNCT7_MEXT, rs2, rs1, 0x7, rd)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------
def u32(v):
    return v & 0xFFFF_FFFF

def _u32(sig):
    try:
        return int(sig.value) & 0xFFFF_FFFF
    except Exception:
        return 0

async def reset_dut(dut):
    dut.rst.value          = 1
    dut.imem_rdata_i.value = NOP
    dut.dmem_rdata_i.value = 0
    dut.dmem_stall_i.value = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0

async def run_program(dut, imem: dict, dmem: dict, cycles: int = 30):
    """
    Simulate `cycles` clock cycles.
    imem / dmem are word-addressed dicts (keys = byte_addr >> 2).
    Missing imem entries → NOP. dmem modified in-place by SW.
    """
    dut.imem_rdata_i.value = imem.get(0, NOP)   # pre-drive word 0 for first fetch
    for _ in range(cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        iaddr = _u32(dut.imem_addr_o) >> 2
        dut.imem_rdata_i.value = imem.get(iaddr, NOP)

        daddr = _u32(dut.dmem_addr_o) >> 2
        if _u32(dut.dmem_we_o) & 1:
            be    = _u32(dut.dmem_be_o)
            wdata = _u32(dut.dmem_wdata_o)
            word  = dmem.get(daddr, 0)
            for i in range(4):
                if (be >> i) & 1:
                    word = (word & ~(0xFF << (8*i))) | (((wdata >> (8*i)) & 0xFF) << (8*i))
            dmem[daddr] = word
        dut.dmem_rdata_i.value = dmem.get(daddr, 0)


# ---------------------------------------------------------------------------
# test_mul — MUL: lower 32 bits of signed × signed
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_mul(dut):
    """MUL: 7 × 6 = 42; (-3) × 5 = -15."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # x1=7, x2=6 → MUL x3,x1,x2 = 42
    # x4=-3, x5=5 → MUL x6,x4,x5 = -15
    imem = {
        0: addi(1, 0, 7),
        1: addi(2, 0, 6),
        2: mul(3, 1, 2),
        3: addi(4, 0, -3),
        4: addi(5, 0, 5),
        5: mul(6, 4, 5),
        6: sw(3, 0, 0),   # mem[0] = 42
        7: sw(6, 0, 4),   # mem[1] = -15
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=50)

    assert dmem.get(0, None) == 42, f"MUL 7×6: expected 42, got {dmem.get(0)}"
    assert u32(dmem.get(1, None)) == u32(-15), \
        f"MUL (-3)×5: expected {u32(-15):#010x}, got {dmem.get(1, 0):#010x}"


# ---------------------------------------------------------------------------
# test_mulh — MULH: upper 32 bits of signed × signed
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_mulh(dut):
    """MULH: 0x7FFF_FFFF × 0x7FFF_FFFF upper 32 = 0x3FFF_FFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # lui(1, 0x7FFF_F000) → x1 = 0x7FFF_F000, then addi(1,1,-1) = 0x7FFF_EFFF
    # Actually: lui encodes upper 20 bits. lui(1, 0x7FFFF000) → x1 = 0x7FFFF000
    # addi(1, 1, -1) → x1 = 0x7FFFEFFF — wrong
    # Use two steps: lui + addi for 0x7FFF_FFFF:
    #   lui(1, 0x80000000): x1 = 0x80000000 (upper 20 bits = 0x80000)
    #   addi(1, 1, -1): x1 = 0x7FFFFFFF ✓
    imem = {
        0: lui(1, 0x80000000),        # x1 = 0x80000000
        1: addi(1, 1, -1),             # x1 = 0x7FFF_FFFF
        2: mulh(3, 1, 1),              # upper32(0x7FFF_FFFF ^ 2) = 0x3FFF_FFFF
        3: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    expected = 0x3FFF_FFFF
    assert dmem.get(0, None) == expected, \
        f"MULH: expected {expected:#010x}, got {dmem.get(0, 0):#010x}"


# ---------------------------------------------------------------------------
# test_mulhu — MULHU: upper 32 bits of unsigned × unsigned
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_mulhu(dut):
    """MULHU: 0xFFFF_FFFF × 0xFFFF_FFFF upper 32 = 0xFFFF_FFFE."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, -1),            # x1 = 0xFFFF_FFFF
        1: mulhu(3, 1, 1),
        2: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    expected = 0xFFFF_FFFE
    assert dmem.get(0, None) == expected, \
        f"MULHU: expected {expected:#010x}, got {dmem.get(0, 0):#010x}"


# ---------------------------------------------------------------------------
# test_mulhsu — MULHSU: upper 32 bits of signed × unsigned
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_mulhsu(dut):
    """MULHSU: (-1) × 0xFFFF_FFFF = upper32(-0xFFFF_FFFF) = 0xFFFF_FFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # signed(-1) × unsigned(0xFFFF_FFFF) → upper32 = 0xFFFF_FFFF
    imem = {
        0: addi(1, 0, -1),            # x1 = -1 signed = 0xFFFF_FFFF unsigned
        1: mulhsu(3, 1, 1),
        2: sw(3, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    expected = 0xFFFF_FFFF
    assert dmem.get(0, None) == expected, \
        f"MULHSU: expected {expected:#010x}, got {dmem.get(0, 0):#010x}"


# ---------------------------------------------------------------------------
# test_div — DIV: signed quotient
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_div(dut):
    """DIV: 20/3=6; -20/3=-6; div-by-zero=0xFFFF_FFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0:  addi(1, 0, 20),
        1:  addi(2, 0, 3),
        2:  div_(3, 1, 2),            # 20/3 = 6
        3:  addi(4, 0, -20),
        4:  div_(5, 4, 2),            # -20/3 = -6
        5:  addi(6, 0, 0),
        6:  div_(7, 1, 6),            # 20/0 = 0xFFFF_FFFF
        7:  sw(3, 0, 0),
        8:  sw(5, 0, 4),
        9:  sw(7, 0, 8),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=220)

    assert dmem.get(0, None) == 6, \
        f"DIV 20/3: expected 6, got {dmem.get(0)}"
    assert u32(dmem.get(1, None)) == u32(-6), \
        f"DIV -20/3: expected {u32(-6):#010x}, got {dmem.get(1, 0):#010x}"
    assert u32(dmem.get(2, None)) == 0xFFFF_FFFF, \
        f"DIV by zero: expected 0xFFFFFFFF, got {dmem.get(2, 0):#010x}"


# ---------------------------------------------------------------------------
# test_divu — DIVU: unsigned quotient
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_divu(dut):
    """DIVU: 0xFFFF_FFFF / 2 = 0x7FFF_FFFF; divu-by-zero = 0xFFFF_FFFF."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, -1),            # x1 = 0xFFFF_FFFF
        1: addi(2, 0, 2),
        2: divu(3, 1, 2),             # 0xFFFF_FFFF / 2 = 0x7FFF_FFFF
        3: addi(4, 0, 0),
        4: divu(5, 1, 4),             # div-by-zero = 0xFFFF_FFFF
        5: sw(3, 0, 0),
        6: sw(5, 0, 4),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=150)

    assert dmem.get(0, None) == 0x7FFF_FFFF, \
        f"DIVU: expected 0x7FFFFFFF, got {dmem.get(0, 0):#010x}"
    assert u32(dmem.get(1, None)) == 0xFFFF_FFFF, \
        f"DIVU by zero: expected 0xFFFFFFFF, got {dmem.get(1, 0):#010x}"


# ---------------------------------------------------------------------------
# test_rem — REM: signed remainder
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_rem(dut):
    """REM: 20%3=2; -20%3=-2; rem-by-zero=dividend."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0:  addi(1, 0, 20),
        1:  addi(2, 0, 3),
        2:  rem_(3, 1, 2),            # 20%3 = 2
        3:  addi(4, 0, -20),
        4:  rem_(5, 4, 2),            # -20%3 = -2
        5:  addi(6, 0, 0),
        6:  rem_(7, 1, 6),            # 20%0 = 20
        7:  sw(3, 0, 0),
        8:  sw(5, 0, 4),
        9:  sw(7, 0, 8),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=220)

    assert dmem.get(0, None) == 2, \
        f"REM 20%3: expected 2, got {dmem.get(0)}"
    assert u32(dmem.get(1, None)) == u32(-2), \
        f"REM -20%3: expected {u32(-2):#010x}, got {dmem.get(1, 0):#010x}"
    assert dmem.get(2, None) == 20, \
        f"REM by zero: expected 20, got {dmem.get(2)}"


# ---------------------------------------------------------------------------
# test_remu — REMU: unsigned remainder
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_remu(dut):
    """REMU: 0xFFFF_FFFF % 5 = 0; remu-by-zero = dividend."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    # 0xFFFF_FFFF = 4294967295 = 5 × 858993459 + 0
    imem = {
        0: addi(1, 0, -1),            # x1 = 0xFFFF_FFFF
        1: addi(2, 0, 5),
        2: remu(3, 1, 2),             # 4294967295 % 5 = 0
        3: addi(4, 0, 0),
        4: remu(5, 1, 4),             # remu-by-zero = dividend (0xFFFF_FFFF)
        5: sw(3, 0, 0),
        6: sw(5, 0, 4),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=150)

    assert dmem.get(0, None) == 0, \
        f"REMU 0xFFFFFFFF % 5: expected 0, got {dmem.get(0)}"
    assert u32(dmem.get(1, None)) == 0xFFFF_FFFF, \
        f"REMU by zero: expected 0xFFFFFFFF, got {dmem.get(1, 0):#010x}"


# ---------------------------------------------------------------------------
# test_div_overflow — INT_MIN / -1 overflow case
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_div_overflow(dut):
    """DIV overflow: INT_MIN / -1 = INT_MIN; REM = 0 per RV32IM spec."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    INT_MIN = 0x8000_0000
    # lui(1, INT_MIN) → x1 = 0x8000_0000; addi does NOT change it since lui loads exact
    imem = {
        0: lui(1, INT_MIN),            # x1 = 0x8000_0000 (INT_MIN)
        1: addi(2, 0, -1),             # x2 = -1 = 0xFFFF_FFFF
        2: div_(3, 1, 2),              # INT_MIN / -1 = INT_MIN (overflow)
        3: rem_(4, 1, 2),              # INT_MIN % -1 = 0
        4: sw(3, 0, 0),
        5: sw(4, 0, 4),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=150)

    assert u32(dmem.get(0, None)) == INT_MIN, \
        f"DIV overflow quot: expected 0x80000000, got {dmem.get(0, 0):#010x}"
    assert dmem.get(1, None) == 0, \
        f"DIV overflow rem: expected 0, got {dmem.get(1)}"


# ---------------------------------------------------------------------------
# test_forwarding_with_mul — MUL result forwarded to next instruction
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_forwarding_with_mul(dut):
    """MUL result forwarded: (3 × 4) + 5 = 17."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)
    imem = {
        0: addi(1, 0, 3),
        1: addi(2, 0, 4),
        2: mul(3, 1, 2),              # x3 = 12
        3: addi(5, 3, 5),             # x5 = x3 + 5 = 17 (EX/MEM→EX forwarding)
        4: sw(5, 0, 0),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0, None) == 17, \
        f"Forwarding after MUL: expected 17, got {dmem.get(0)}"
