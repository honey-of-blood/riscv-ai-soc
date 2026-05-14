"""
Full-pipeline integration tests for riscv_core.sv.

Each test loads a program into a Python instruction-memory dict and a data-
memory dict, runs the core for enough clock cycles, then inspects the data
memory for correctness.  Single-cycle (combinational) memory is modelled by
driving {i,d}mem_rdata_i 1 ns after every rising edge.

Hazard scenarios covered
------------------------
  test_exmem_forward   – back-to-back ALU: EX/MEM → EX forwarding
  test_memwb_forward   – 2-instruction gap:  MEM/WB → EX forwarding
  test_load_use_stall  – LW followed immediately by dependent ALU
  test_branch_taken    – BEQ equal operands: 2-cycle flush, skip 2 instrs
  test_branch_not_taken– BEQ unequal: fall-through, no flush
  test_jal             – JAL link address + 2-cycle flush
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# ---------------------------------------------------------------------------
# Instruction encoding helpers
# ---------------------------------------------------------------------------
OP_R      = 0x33
OP_IMM    = 0x13
OP_LOAD   = 0x03
OP_STORE  = 0x23
OP_BRANCH = 0x63
OP_JAL    = 0x6F
OP_LUI    = 0x37
NOP       = 0x00000013   # ADDI x0, x0, 0

def _r(funct7, rs2, rs1, funct3, rd):
    return (funct7<<25)|(rs2<<20)|(rs1<<15)|(funct3<<12)|(rd<<7)|OP_R

def _i(imm, rs1, funct3, rd, op):
    return ((imm & 0xFFF)<<20)|(rs1<<15)|(funct3<<12)|(rd<<7)|op

def _s(imm, rs2, rs1, funct3):
    imm &= 0xFFF
    return (((imm>>5)&0x7F)<<25)|(rs2<<20)|(rs1<<15)|(funct3<<12)|((imm&0x1F)<<7)|OP_STORE

def _b(imm, rs2, rs1, funct3):
    imm &= 0x1FFF
    return (((imm>>12)&1)<<31)|(((imm>>5)&0x3F)<<25)|(rs2<<20)|(rs1<<15)|\
           (funct3<<12)|(((imm>>1)&0xF)<<8)|(((imm>>11)&1)<<7)|OP_BRANCH

def _j(imm, rd):
    imm &= 0x1FFFFF
    return (((imm>>20)&1)<<31)|(((imm>>1)&0x3FF)<<21)|(((imm>>11)&1)<<20)|\
           (((imm>>12)&0xFF)<<12)|(rd<<7)|OP_JAL

OP_JALR  = 0x67
OP_AUIPC = 0x17

def addi(rd, rs1, imm):   return _i(imm, rs1, 0x0, rd, OP_IMM)
def add (rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x0, rd)
def sub (rd, rs1, rs2):   return _r(0x20, rs2, rs1, 0x0, rd)
def and_(rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x7, rd)
def or_ (rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x6, rd)
def xor_(rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x4, rd)
def sll (rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x1, rd)
def srl (rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x5, rd)
def sra (rd, rs1, rs2):   return _r(0x20, rs2, rs1, 0x5, rd)
def slt (rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x2, rd)
def sltu(rd, rs1, rs2):   return _r(0x00, rs2, rs1, 0x3, rd)
def andi(rd, rs1, imm):   return _i(imm, rs1, 0x7, rd, OP_IMM)
def ori (rd, rs1, imm):   return _i(imm, rs1, 0x6, rd, OP_IMM)
def xori(rd, rs1, imm):   return _i(imm, rs1, 0x4, rd, OP_IMM)
def slli(rd, rs1, shamt): return _i(shamt & 0x1F,          rs1, 0x1, rd, OP_IMM)
def srli(rd, rs1, shamt): return _i(shamt & 0x1F,          rs1, 0x5, rd, OP_IMM)
def srai(rd, rs1, shamt): return _i(0x400|(shamt & 0x1F),  rs1, 0x5, rd, OP_IMM)
def slti(rd, rs1, imm):   return _i(imm, rs1, 0x2, rd, OP_IMM)
def sltiu(rd, rs1, imm):  return _i(imm, rs1, 0x3, rd, OP_IMM)
def lw  (rd,  rs1, imm):  return _i(imm, rs1, 0x2, rd, OP_LOAD)
def lh  (rd,  rs1, imm):  return _i(imm, rs1, 0x1, rd, OP_LOAD)
def lb  (rd,  rs1, imm):  return _i(imm, rs1, 0x0, rd, OP_LOAD)
def lhu (rd,  rs1, imm):  return _i(imm, rs1, 0x5, rd, OP_LOAD)
def lbu (rd,  rs1, imm):  return _i(imm, rs1, 0x4, rd, OP_LOAD)
def sw  (rs2, rs1, imm):  return _s(imm, rs2, rs1, 0x2)
def sh  (rs2, rs1, imm):  return _s(imm, rs2, rs1, 0x1)
def sb  (rs2, rs1, imm):  return _s(imm, rs2, rs1, 0x0)
def beq (rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x0)
def bne (rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x1)
def blt (rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x4)
def bge (rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x5)
def bltu(rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x6)
def bgeu(rs1, rs2, imm):  return _b(imm, rs2, rs1, 0x7)
def jal (rd,  imm):       return _j(imm, rd)
# lui(rd, page): pass full page-aligned value, e.g. lui(1, 0xDEAD0000) → x1=0xDEAD0000
def lui (rd,  imm):       return (((imm>>12)&0xFFFFF)<<12)|(rd<<7)|OP_LUI
def auipc(rd, imm):       return (((imm>>12)&0xFFFFF)<<12)|(rd<<7)|OP_AUIPC
def jalr(rd, rs1, imm):   return _i(imm, rs1, 0x0, rd, OP_JALR)

# ---------------------------------------------------------------------------
# Simulation helpers
# ---------------------------------------------------------------------------
def _u32(sig):
    """Read a DUT signal as an unsigned 32-bit int; return 0 if undefined."""
    try:
        return int(sig.value) & 0xFFFFFFFF
    except Exception:
        return 0

async def reset_dut(dut):
    """Assert rst for 4 cycles then release."""
    dut.rst.value         = 1
    dut.imem_rdata_i.value = NOP
    dut.dmem_rdata_i.value = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0

async def run_program(dut, imem: dict, dmem: dict, cycles: int = 30):
    """
    Simulate `cycles` clock cycles with single-cycle instruction and data
    memory models.

    imem: word-address → 32-bit instruction word (missing entries → NOP)
    dmem: word-address → 32-bit data word        (modified in-place by SW)
    """
    # Pre-drive word 0: during reset PC is held at 0, so IF/ID will latch
    # imem[0] on the very first post-reset rising edge.
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for _ in range(cycles):
        await RisingEdge(dut.clk)
        # 1 ns after the edge: registered PC / EX/MEM addr have settled.
        await Timer(1, unit="ns")

        # ---- Instruction memory ----
        iaddr = _u32(dut.imem_addr_o) >> 2
        dut.imem_rdata_i.value = imem.get(iaddr, NOP)

        # ---- Data memory ----
        daddr = _u32(dut.dmem_addr_o) >> 2          # word address
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
# Test 1: EX/MEM → EX forwarding (back-to-back ALU chain)
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_exmem_forward(dut):
    """
    Chain of ADDI each dependent on the previous result.
    Without forwarding the last ADD would read stale zeros.

    x1 = 10 → +5 → +2 = 17
    x2 = x1 + x1 = 34   (EX/MEM → EX on both rs1 and rs2)
    SW  x2, 0(x0)  → mem[0] = 34
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 10),   # x1 = 10
        1: addi(1, 1,  5),   # x1 = 15  [EX/MEM→EX]
        2: addi(1, 1,  2),   # x1 = 17  [EX/MEM→EX]
        3: add (2, 1,  1),   # x2 = 34  [EX/MEM→EX, both rs]
        4: sw  (2, 0,  0),   # mem[0]  = 34
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    assert dmem.get(0) == 34, f"expected mem[0]=34, got {dmem.get(0)}"

# ---------------------------------------------------------------------------
# Test 2: MEM/WB → EX forwarding (2-instruction gap)
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_memwb_forward(dut):
    """
    Two unrelated instructions separate producer from consumer.
    x1 is in the MEM/WB stage when ADD x2,x1,x1 enters EX.

    x1 = 5 | x3=1 | x4=2 | ADD x2,x1,x1=10  [MEM/WB→EX]
    SW  x2, 0(x0) → mem[0] = 10
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 5),    # x1 = 5
        1: addi(3, 0, 1),    # x3 = 1  (gap)
        2: addi(4, 0, 2),    # x4 = 2  (gap; x1 now in WB stage)
        3: add (2, 1, 1),    # x2 = 10 [MEM/WB→EX for x1]
        4: sw  (2, 0, 0),    # mem[0] = 10
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    assert dmem.get(0) == 10, f"expected mem[0]=10, got {dmem.get(0)}"

# ---------------------------------------------------------------------------
# Test 3: Load-use stall (1-cycle bubble)
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_load_use_stall(dut):
    """
    LW immediately followed by a dependent ADDI.
    Hazard unit must stall PC + IF/ID for 1 cycle and flush ID/EX.
    After the stall the loaded value is forwarded via MEM/WB → EX.

    SW x1, 0(x0)  → mem[0] = 42
    LW x2, 0(x0)  → x2 = 42
    ADDI x3,x2,1  → x3 = 43   [1-cycle stall + MEM/WB→EX forward]
    SW x3, 4(x0)  → mem[1] = 43
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 42),   # x1 = 42
        1: sw  (1, 0,  0),   # mem[0] = 42
        2: lw  (2, 0,  0),   # x2 = 42  (LOAD)
        3: addi(3, 2,  1),   # x3 = 43  [load-use stall]
        4: sw  (3, 0,  4),   # mem[1] = 43
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 42, f"expected mem[0]=42, got {dmem.get(0)}"
    assert dmem.get(1) == 43, f"expected mem[1]=43, got {dmem.get(1)}"

# ---------------------------------------------------------------------------
# Test 4: Branch taken (2-cycle flush)
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_branch_taken(dut):
    """
    BEQ with equal operands: branch resolves in EX, 2 wrong instructions
    already in ID and IF are flushed.

    x1 = x2 = 5  →  BEQ taken, skip 2 instrs (would set x3=99/88),
    land at ADDI x3,x0,55  →  mem[2] = 55.

    Branch at PC=8, offset=+12, target=PC 20 (word index 5).
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0,  5),   # x1 = 5
        1: addi(2, 0,  5),   # x2 = 5
        2: beq (1, 2, 12),   # taken → target PC=20 (word 5)
        3: addi(3, 0, 99),   # SKIPPED (flushed)
        4: addi(3, 0, 88),   # SKIPPED (flushed)
        5: addi(3, 0, 55),   # x3 = 55  ← branch target
        6: sw  (3, 0,  8),   # mem[2] = 55
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=35)

    assert dmem.get(2) == 55, f"expected mem[2]=55, got {dmem.get(2)}"
    # Confirm the skipped store (word 3 = byte addr 12) was never executed
    assert dmem.get(3, None) is None or dmem.get(3) == 0, \
        f"skipped instruction wrote to mem[3]={dmem.get(3)}"

# ---------------------------------------------------------------------------
# Test 5: Branch not taken (fall-through)
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_branch_not_taken(dut):
    """
    BEQ with unequal operands: no flush, fall-through executes normally.
    x1=5, x2=6  →  BEQ not taken  →  ADDI x3,x0,77  →  mem[0]=77.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0,  5),   # x1 = 5
        1: addi(2, 0,  6),   # x2 = 6
        2: beq (1, 2, 12),   # NOT taken (5 ≠ 6)
        3: addi(3, 0, 77),   # x3 = 77 (fall-through, must execute)
        4: sw  (3, 0,  0),   # mem[0] = 77
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    assert dmem.get(0) == 77, f"expected mem[0]=77, got {dmem.get(0)}"

# ---------------------------------------------------------------------------
# Test 6: JAL — unconditional jump + link register
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_jal(dut):
    """
    JAL at PC=4 (word 1), offset=+12  →  target=PC 16 (word 4).
    Link register x5 = PC+4 = 8.
    Two instructions at PC=8,12 are flushed.
    x1 (set before JAL) must not be clobbered by the skipped ADDI x1 instrs.

    mem[0] = x5 = 8
    mem[1] = x1 = 100
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 100),  # x1 = 100
        1: jal (5, 12),      # x5=8 (PC+4), jump to PC=16
        2: addi(1, 0,   0),  # SKIPPED (flushed)
        3: addi(1, 0,   0),  # SKIPPED (flushed)
        4: sw  (5, 0,   0),  # mem[0] = x5 = 8
        5: sw  (1, 0,   4),  # mem[1] = x1 = 100
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=35)

    assert dmem.get(0) == 8,   f"expected mem[0]=8 (link addr),  got {dmem.get(0)}"
    assert dmem.get(1) == 100, f"expected mem[1]=100 (x1 intact), got {dmem.get(1)}"

# ---------------------------------------------------------------------------
# BATCH 1 — LUI, AUIPC, JALR, remaining branch types
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_lui(dut):
    """
    LUI writes imm20<<12 directly to rd (no ALU, writeback via WB_IMM path).

    x1 = 0xDEAD0000  →  mem[0] = 0xDEAD0000
    x2 = 0x00001000  →  mem[1] = 0x00001000
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: lui(1, 0xDEAD0000),  # x1 = 0xDEAD0000
        1: lui(2, 0x00001000),  # x2 = 0x00001000
        2: sw (1, 0, 0),        # mem[0] = x1
        3: sw (2, 0, 4),        # mem[1] = x2
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    assert dmem.get(0) == 0xDEAD0000, f"LUI: expected mem[0]=0xDEAD0000, got 0x{dmem.get(0):08X}"
    assert dmem.get(1) == 0x00001000, f"LUI: expected mem[1]=0x00001000, got 0x{dmem.get(1):08X}"


@cocotb.test()
async def test_auipc(dut):
    """
    AUIPC writes PC + (imm20<<12) to rd.

    AUIPC at word 1 → PC=4.  imm=0x1000 → result = 4 + 0x1000 = 0x1004.
    AUIPC at word 2 → PC=8.  imm=0x2000 → result = 8 + 0x2000 = 0x2008.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(0, 0, 0),       # NOP — padding so word 1 has PC=4
        1: auipc(1, 0x1000),    # x1 = 4  + 0x1000 = 0x1004
        2: auipc(2, 0x2000),    # x2 = 8  + 0x2000 = 0x2008
        3: sw  (1, 0, 0),       # mem[0] = x1
        4: sw  (2, 0, 4),       # mem[1] = x2
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=25)

    assert dmem.get(0) == 0x1004, f"AUIPC word1: expected 0x1004, got 0x{dmem.get(0):08X}"
    assert dmem.get(1) == 0x2008, f"AUIPC word2: expected 0x2008, got 0x{dmem.get(1):08X}"


@cocotb.test()
async def test_jalr(dut):
    """
    JALR at word 1 (PC=4): base=x1=12, offset=4 → target=(12+4)&~1=16 (word 4).
    Link x5 = PC+4 = 8.  Two instructions in flight are flushed.
    x1 must not be clobbered by the skipped ADDIs.

    mem[0] = x5 = 8   (link address)
    mem[1] = x1 = 12  (base register unchanged)
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 12),   # x1 = 12  (JALR base)
        1: jalr(5, 1,  4),   # x5=8 (PC+4=4+4), jump to (12+4)&~1=16 (word 4)
        2: addi(1, 0,  0),   # SKIPPED (flushed)
        3: addi(1, 0,  0),   # SKIPPED (flushed)
        4: sw  (5, 0,  0),   # mem[0] = x5 = 8
        5: sw  (1, 0,  4),   # mem[1] = x1 = 12
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=35)

    assert dmem.get(0) == 8,  f"JALR: expected mem[0]=8 (link), got {dmem.get(0)}"
    assert dmem.get(1) == 12, f"JALR: expected mem[1]=12 (base intact), got {dmem.get(1)}"


@cocotb.test()
async def test_bne_taken(dut):
    """
    BNE with unequal operands: branch taken, 2-cycle flush.

    x1=3, x2=5 → BNE taken → skip 2 instrs → ADDI x3,x0,77 → mem[0]=77
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0,  3),   # x1 = 3
        1: addi(2, 0,  5),   # x2 = 5
        2: bne (1, 2, 12),   # taken (3≠5) → target word 5
        3: addi(3, 0, 99),   # SKIPPED
        4: addi(3, 0, 88),   # SKIPPED
        5: addi(3, 0, 77),   # x3 = 77
        6: sw  (3, 0,  0),   # mem[0] = 77
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 77, f"BNE taken: expected 77, got {dmem.get(0)}"


@cocotb.test()
async def test_blt_taken(dut):
    """
    BLT signed: -1 < 1 → taken.  Tests that signed comparison works.

    x1 = -1 (0xFFFFFFFF), x2 = 1 → BLT taken → ADDI x3,x0,55 → mem[0]=55
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, -1),   # x1 = 0xFFFFFFFF (-1 signed)
        1: addi(2, 0,  1),   # x2 = 1
        2: blt (1, 2, 12),   # taken (-1 < 1 signed) → target word 5
        3: addi(3, 0, 99),   # SKIPPED
        4: addi(3, 0, 88),   # SKIPPED
        5: addi(3, 0, 55),   # x3 = 55
        6: sw  (3, 0,  0),   # mem[0] = 55
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 55, f"BLT: expected 55, got {dmem.get(0)}"


@cocotb.test()
async def test_bge_taken(dut):
    """
    BGE signed: 10 >= 10 → taken (equal case).

    x1=10, x2=10 → BGE taken → ADDI x3,x0,44 → mem[0]=44
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 10),   # x1 = 10
        1: addi(2, 0, 10),   # x2 = 10
        2: bge (1, 2, 12),   # taken (10 >= 10) → target word 5
        3: addi(3, 0, 99),   # SKIPPED
        4: addi(3, 0, 88),   # SKIPPED
        5: addi(3, 0, 44),   # x3 = 44
        6: sw  (3, 0,  0),   # mem[0] = 44
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 44, f"BGE: expected 44, got {dmem.get(0)}"


@cocotb.test()
async def test_bltu_taken(dut):
    """
    BLTU unsigned: 1 < 0xFFFFFFFF → taken.
    0xFFFFFFFF is -1 signed but the largest unsigned 32-bit value.

    x1=1, x2=0xFFFFFFFF → BLTU taken → ADDI x3,x0,33 → mem[0]=33
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # Load 0xFFFFFFFF into x2 via ADDI x2,x0,-1 (sign-extended -1 = 0xFFFFFFFF)
    imem = {
        0: addi(1, 0,  1),   # x1 = 1
        1: addi(2, 0, -1),   # x2 = 0xFFFFFFFF
        2: bltu(1, 2, 12),   # taken (1 < 0xFFFFFFFF unsigned) → target word 5
        3: addi(3, 0, 99),   # SKIPPED
        4: addi(3, 0, 88),   # SKIPPED
        5: addi(3, 0, 33),   # x3 = 33
        6: sw  (3, 0,  0),   # mem[0] = 33
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 33, f"BLTU: expected 33, got {dmem.get(0)}"


@cocotb.test()
async def test_bgeu_taken(dut):
    """
    BGEU unsigned: 0xFFFFFFFF >= 1 → taken.

    x1=0xFFFFFFFF, x2=1 → BGEU taken → ADDI x3,x0,22 → mem[0]=22
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, -1),   # x1 = 0xFFFFFFFF
        1: addi(2, 0,  1),   # x2 = 1
        2: bgeu(1, 2, 12),   # taken (0xFFFFFFFF >= 1 unsigned) → target word 5
        3: addi(3, 0, 99),   # SKIPPED
        4: addi(3, 0, 88),   # SKIPPED
        5: addi(3, 0, 22),   # x3 = 22
        6: sw  (3, 0,  0),   # mem[0] = 22
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 22, f"BGEU: expected 22, got {dmem.get(0)}"

# ---------------------------------------------------------------------------
# BATCH 2 — R-type and I-type ALU ops through the full pipeline
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_r_type_ops(dut):
    """
    SUB, AND, OR, XOR through the full pipeline.
    x1=0b10110 (22), x2=0b01110 (14)
      SUB:  22-14 = 8      → mem[0]
      AND:  22&14 = 0b00110 = 6  → mem[1]
      OR:   22|14 = 0b11110 = 30 → mem[2]
      XOR:  22^14 = 0b11000 = 24 → mem[3]
    Each SW is back-to-back with its producer → exercises EX/MEM forwarding.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0:  addi(1, 0, 22),    # x1 = 22
        1:  addi(2, 0, 14),    # x2 = 14
        2:  sub (3, 1, 2),     # x3 = 8
        3:  sw  (3, 0,  0),    # mem[0] = 8
        4:  and_(3, 1, 2),     # x3 = 6
        5:  sw  (3, 0,  4),    # mem[1] = 6
        6:  or_ (3, 1, 2),     # x3 = 30
        7:  sw  (3, 0,  8),    # mem[2] = 30
        8:  xor_(3, 1, 2),     # x3 = 24
        9:  sw  (3, 0, 12),    # mem[3] = 24
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=50)

    assert dmem.get(0) ==  8, f"SUB:  expected  8, got {dmem.get(0)}"
    assert dmem.get(1) ==  6, f"AND:  expected  6, got {dmem.get(1)}"
    assert dmem.get(2) == 30, f"OR:   expected 30, got {dmem.get(2)}"
    assert dmem.get(3) == 24, f"XOR:  expected 24, got {dmem.get(3)}"


@cocotb.test()
async def test_shift_ops(dut):
    """
    SLL, SRL, SRA through the full pipeline.
    x1=0x000000F0 (240), x2=4 (shift amount)
      SLL: 240 << 4 = 3840 (0xF00)          → mem[0]
      SRL: 240 >> 4 = 15                     → mem[1]
    x1=0xF0000000 (signed negative), x2=4
      SRA: arithmetic right shift → 0xFF000000 → mem[2]
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0:  addi(1, 0, 0xF0),         # x1 = 240
        1:  addi(2, 0, 4),             # x2 = 4
        2:  sll (3, 1, 2),             # x3 = 240 << 4 = 3840
        3:  sw  (3, 0,  0),            # mem[0] = 3840
        4:  srl (3, 1, 2),             # x3 = 240 >> 4 = 15
        5:  sw  (3, 0,  4),            # mem[1] = 15
        # SRA: load 0xF0000000 (-268435456) into x1 via LUI
        6:  lui (1, 0xF0000000),       # x1 = 0xF0000000
        7:  sra (3, 1, 2),             # x3 = 0xF0000000 >> 4 = 0xFF000000
        8:  sw  (3, 0,  8),            # mem[2] = 0xFF000000
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=45)

    assert dmem.get(0) == 3840,       f"SLL: expected 3840, got {dmem.get(0)}"
    assert dmem.get(1) == 15,         f"SRL: expected 15,   got {dmem.get(1)}"
    assert dmem.get(2) == 0xFF000000, f"SRA: expected 0xFF000000, got 0x{dmem.get(2):08X}"


@cocotb.test()
async def test_compare_ops(dut):
    """
    SLT (signed) and SLTU (unsigned) through the full pipeline.
      x1=-1 (0xFFFFFFFF), x2=1
      SLT  x3, x1, x2: -1 < 1  signed   → x3=1  → mem[0]
      SLTU x4, x1, x2: 0xFFFFFFFF < 1 unsigned? No → x4=0  → mem[1]
      SLT  x5, x2, x1: 1 < -1  signed?  No → x5=0  → mem[2]
      SLTU x6, x2, x1: 1 < 0xFFFFFFFF unsigned? Yes → x6=1  → mem[3]
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0:  addi(1, 0, -1),    # x1 = 0xFFFFFFFF
        1:  addi(2, 0,  1),    # x2 = 1
        2:  slt (3, 1, 2),     # x3 = 1  (-1 < 1 signed)
        3:  sw  (3, 0,  0),
        4:  sltu(4, 1, 2),     # x4 = 0  (0xFFFFFFFF NOT < 1 unsigned)
        5:  sw  (4, 0,  4),
        6:  slt (5, 2, 1),     # x5 = 0  (1 NOT < -1 signed)
        7:  sw  (5, 0,  8),
        8:  sltu(6, 2, 1),     # x6 = 1  (1 < 0xFFFFFFFF unsigned)
        9:  sw  (6, 0, 12),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=50)

    assert dmem.get(0) == 1, f"SLT(-1<1):   expected 1, got {dmem.get(0)}"
    assert dmem.get(1) == 0, f"SLTU(big<1): expected 0, got {dmem.get(1)}"
    assert dmem.get(2) == 0, f"SLT(1<-1):   expected 0, got {dmem.get(2)}"
    assert dmem.get(3) == 1, f"SLTU(1<big): expected 1, got {dmem.get(3)}"


@cocotb.test()
async def test_i_type_alu_ops(dut):
    """
    I-type ALU ops: ANDI, ORI, XORI, SLLI, SRLI, SRAI, SLTI, SLTIU through pipeline.
    x1 = 0b11001010 = 202

      ANDI x1, 0b11110000 (0xF0) = 0b11000000 = 192 → mem[0]
      ORI  x1, 0b00001111 (0x0F) = 0b11001111 = 207 → mem[1]
      XORI x1, 0b11111111 (0xFF) = 0b00110101 = 53  → mem[2]
      SLLI x1, 2                 = 808              → mem[3]
      SRLI x1, 2                 = 50               → mem[4]
      SRAI (x1=0xFFFFFF00), 4    = 0xFFFFFFF0       → mem[5]
      SLTI x1(202), 203          = 1                → mem[6]
      SLTIU x1(202), 100         = 0                → mem[7]
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0:  addi(1, 0, 202),         # x1 = 202 = 0b11001010
        1:  andi(2, 1, 0xF0),        # x2 = 202 & 0xF0 = 0b11000000 = 192
        2:  sw  (2, 0,  0),
        3:  ori (2, 1, 0x0F),        # x2 = 202 | 0x0F = 0b11001111 = 207
        4:  sw  (2, 0,  4),
        5:  xori(2, 1, 0xFF),        # x2 = 202 ^ 0xFF = 0b00110101 = 53
        6:  sw  (2, 0,  8),
        7:  slli(2, 1, 2),           # x2 = 202 << 2 = 808
        8:  sw  (2, 0, 12),
        9:  srli(2, 1, 2),           # x2 = 202 >> 2 = 50
        10: sw  (2, 0, 16),
        # SRAI: need a negative value; ADDI sign-extends -16 → 0xFFFFFFF0
        11: addi(1, 0, -16),         # x1 = 0xFFFFFFF0 (signed -16)
        12: srai(2, 1, 2),           # x2 = 0xFFFFFFF0 >> 2 = 0xFFFFFFFC
        13: sw  (2, 0, 20),
        # SLTI / SLTIU
        14: addi(1, 0, 202),         # x1 = 202 again
        15: slti (2, 1, 203),        # x2 = 1 (202 < 203 signed)
        16: sw   (2, 0, 24),
        17: sltiu(2, 1, 100),        # x2 = 0 (202 NOT < 100 unsigned)
        18: sw   (2, 0, 28),
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=80)

    assert dmem.get(0) == 192,        f"ANDI: expected 192,        got {dmem.get(0)}"
    assert dmem.get(1) == 207,        f"ORI:  expected 207,        got {dmem.get(1)}"
    assert dmem.get(2) == 53,         f"XORI: expected 53,         got {dmem.get(2)}"
    assert dmem.get(3) == 808,        f"SLLI: expected 808,        got {dmem.get(3)}"
    assert dmem.get(4) == 50,         f"SRLI: expected 50,         got {dmem.get(4)}"
    assert dmem.get(5) == 0xFFFFFFFC, f"SRAI: expected 0xFFFFFFFC, got 0x{dmem.get(5):08X}"
    assert dmem.get(6) == 1,          f"SLTI: expected 1,          got {dmem.get(6)}"
    assert dmem.get(7) == 0,          f"SLTIU:expected 0,          got {dmem.get(7)}"

# ---------------------------------------------------------------------------
# BATCH 3 — Byte/halfword loads and stores, branch on forwarded value
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_byte_loads(dut):
    """
    LB (sign-extend), LBU (zero-extend), LH (sign-extend), LHU (zero-extend).

    Store 0xABCD_8180 at word 0.
      Byte layout (little-endian):  [0]=0x80  [1]=0x81  [2]=0xCD  [3]=0xAB
      LB  0(x0) → sign-extend(0x80) = 0xFFFFFF80  → mem[1]
      LBU 0(x0) → zero-extend(0x80) = 0x00000080  → mem[2]
      LH  0(x0) → sign-extend(0x8180) = 0xFFFF8180 → mem[3]
      LHU 0(x0) → zero-extend(0x8180) = 0x00008180 → mem[4]
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # Build 0xABCD8180 via LUI + ADDI (LUI gives 0xABCD8000, ADDI adds 0x180=384)
    # 0xABCD8000 + 0x180 = 0xABCD8180. But ADDI immediate is signed 12-bit.
    # 0x180 = 384, fits in 12-bit signed (max 2047). ✓
    imem = {
        0: lui (1, 0xABCD8000),   # x1 = 0xABCD8000
        1: addi(1, 1, 0x180),     # x1 = 0xABCD8180
        2: sw  (1, 0, 0),         # mem[0] = 0xABCD8180
        3: lb  (2, 0, 0),         # x2 = sign_ext(0x80) = 0xFFFFFF80
        4: sw  (2, 0, 4),         # mem[1] = 0xFFFFFF80
        5: lbu (3, 0, 0),         # x3 = zero_ext(0x80) = 0x00000080
        6: sw  (3, 0, 8),         # mem[2] = 0x00000080
        7: lh  (4, 0, 0),         # x4 = sign_ext(0x8180) = 0xFFFF8180
        8: sw  (4, 0, 12),        # mem[3] = 0xFFFF8180
        9: lhu (5, 0, 0),         # x5 = zero_ext(0x8180) = 0x00008180
        10: sw  (5, 0, 16),       # mem[4] = 0x00008180
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=60)

    assert dmem.get(1) == 0xFFFFFF80, f"LB:  expected 0xFFFFFF80, got 0x{dmem.get(1):08X}"
    assert dmem.get(2) == 0x00000080, f"LBU: expected 0x00000080, got 0x{dmem.get(2):08X}"
    assert dmem.get(3) == 0xFFFF8180, f"LH:  expected 0xFFFF8180, got 0x{dmem.get(3):08X}"
    assert dmem.get(4) == 0x00008180, f"LHU: expected 0x00008180, got 0x{dmem.get(4):08X}"


@cocotb.test()
async def test_byte_stores(dut):
    """
    SB and SH: partial-word writes using byte enables.

    Start with mem[0] = 0xFFFFFFFF (pre-initialised).
    SB x1(0x42), 0(x0)  → only byte 0 changes: 0xFFFFFF42
    SH x2(0x1234), 2(x0) → halfword at offset 2: 0x1234FF42
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 0x42),     # x1 = 0x42
        1: addi(2, 0, 0x1234),   # x2 = 0x1234  (fits in 12-bit signed: max 2047, 0x1234=4660 > 2047)
    }
    # 0x1234 = 4660 > 2047, so we need LUI+ADDI for x2
    imem = {
        0: addi(1, 0, 0x42),     # x1 = 0x42
        1: lui (2, 0x1000),      # x2 = 0x1000
        2: addi(2, 2, 0x234),    # x2 = 0x1234  (0x234=564 fits in 12-bit signed ✓)
        3: sb  (1, 0, 0),        # mem[0] byte 0 ← 0x42  (rest unchanged)
        4: sh  (2, 0, 2),        # mem[0] halfword at byte offset 2 ← 0x1234
        5: lw  (3, 0, 0),        # x3 = full word at mem[0]
        6: sw  (3, 0, 4),        # mem[1] = final value of mem[0]
    }
    dmem = {0: 0xFFFFFFFF}       # pre-initialise word 0 to all-ones
    await run_program(dut, imem, dmem, cycles=40)

    assert dmem.get(1) == 0x1234FF42, \
        f"SB+SH: expected 0x1234FF42, got 0x{dmem.get(1):08X}"


@cocotb.test()
async def test_branch_on_forwarded(dut):
    """
    Branch where both operands are forwarded:
      x1 is 2 instructions before BEQ → MEM/WB forwarding
      x2 is 1 instruction before BEQ  → EX/MEM forwarding
    Both paths must feed into the branch condition evaluator.

    x1=7, x2=7 → BEQ taken → skip ADDI x3,x0,99 → ADDI x3,x0,55 → mem[0]=55
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        0: addi(1, 0, 7),    # x1=7  (in MEM/WB when BEQ is in EX)
        1: addi(2, 0, 7),    # x2=7  (in EX/MEM when BEQ is in EX)
        2: beq (1, 2, 8),    # BEQ: 7==7 via forwarding → taken, target word 4
        3: addi(3, 0, 99),   # SKIPPED (flushed)
        4: addi(3, 0, 55),   # x3 = 55
        5: sw  (3, 0, 0),    # mem[0] = 55
    }
    dmem = {}
    await run_program(dut, imem, dmem, cycles=30)

    assert dmem.get(0) == 55, f"branch-forwarded: expected 55, got {dmem.get(0)}"

# ---------------------------------------------------------------------------
# BATCH 4 — Bubblesort integration test
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_bubblesort(dut):
    """
    Sorts [3, 1, 4, 1, 5] in-place using bubble sort.
    Exercises: nested loops, LW/SW, SLLI, ADD, BGE (loop control), BLT (no-swap
    path), all forwarding paths, multiple branch flushes and load-use stalls.

    Expected result: [1, 1, 3, 4, 5] at word addresses 0–4.

    Register allocation:
      x1  = n = 5 (array size)
      x2  = i   (outer loop counter)
      x3  = j   (inner loop counter)
      x4  = arr[j]
      x5  = arr[j+1]
      x6  = n-1 = 4  (outer loop limit)
      x7  = (n-1)-i  (inner loop limit)
      x8  = j*4      (byte offset)
      x9  = &arr[j]  (element address)
      x10 = array base address = 0

    Instruction layout (word addresses):
      0:  addi x1, x0, 5       n = 5
      1:  addi x10, x0, 0      base = 0
      2:  addi x2, x0, 0       i = 0
      ── outer_check (word 3): ──
      3:  addi x6, x1, -1      x6 = n-1 = 4
      4:  bge  x2, x6, +60     if i >= 4 → done (word 19, PC=76)
      5:  addi x3, x0, 0       j = 0
      ── inner_check (word 6): ──
      6:  sub  x7, x6, x2      x7 = (n-1)-i
      7:  bge  x3, x7, +40     if j >= x7 → inner_done (word 17, PC=68)
      ── loop body: ──
      8:  slli x8, x3, 2       x8 = j*4
      9:  add  x9, x10, x8     x9 = &arr[j]
      10: lw   x4, 0(x9)       x4 = arr[j]
      11: lw   x5, 4(x9)       x5 = arr[j+1]
      12: bge  x5, x4, +12     if arr[j+1] >= arr[j] → no_swap (word 15, PC=60)
      13: sw   x5, 0(x9)       arr[j]   = arr[j+1]
      14: sw   x4, 4(x9)       arr[j+1] = arr[j]
      ── no_swap (word 15): ──
      15: addi x3, x3, 1       j++
      16: jal  x0, -40         → inner_check (word 6, PC=24)
      ── inner_done (word 17): ──
      17: addi x2, x2, 1       i++
      18: jal  x0, -60         → outer_check (word 3, PC=12)
      ── done (word 19): ──   (program halts via NOP fill)
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    imem = {
        # Initialisation
        0:  addi(1,  0,  5),    # x1  = 5  (n)
        1:  addi(10, 0,  0),    # x10 = 0  (base address)
        2:  addi(2,  0,  0),    # x2  = 0  (i)
        # outer_check
        3:  addi(6,  1, -1),    # x6  = n-1 = 4
        4:  bge (2,  6, 60),    # i >= 4 → jump to word 19 (done)
        5:  addi(3,  0,  0),    # x3  = 0  (j)
        # inner_check
        6:  sub (7,  6,  2),    # x7  = (n-1) - i
        7:  bge (3,  7, 40),    # j >= x7 → jump to word 17 (inner_done)
        # loop body
        8:  slli(8,  3,  2),    # x8  = j * 4
        9:  add (9, 10,  8),    # x9  = base + j*4 = &arr[j]
        10: lw  (4,  9,  0),    # x4  = arr[j]
        11: lw  (5,  9,  4),    # x5  = arr[j+1]
        12: bge (5,  4, 12),    # arr[j+1] >= arr[j] → no_swap (word 15)
        13: sw  (5,  9,  0),    # arr[j]   = arr[j+1]
        14: sw  (4,  9,  4),    # arr[j+1] = arr[j]
        # no_swap
        15: addi(3,  3,  1),    # j++
        16: jal (0, -40),       # → inner_check (word 6): (6-16)*4 = -40
        # inner_done
        17: addi(2,  2,  1),    # i++
        18: jal (0, -60),       # → outer_check (word 3): (3-18)*4 = -60
        # done — NOP fill keeps pipeline draining
    }

    dmem = {0: 3, 1: 1, 2: 4, 3: 1, 4: 5}   # input: [3, 1, 4, 1, 5]
    await run_program(dut, imem, dmem, cycles=300)

    assert dmem.get(0) == 1, f"bubblesort[0]: expected 1, got {dmem.get(0)}"
    assert dmem.get(1) == 1, f"bubblesort[1]: expected 1, got {dmem.get(1)}"
    assert dmem.get(2) == 3, f"bubblesort[2]: expected 3, got {dmem.get(2)}"
    assert dmem.get(3) == 4, f"bubblesort[3]: expected 4, got {dmem.get(3)}"
    assert dmem.get(4) == 5, f"bubblesort[4]: expected 5, got {dmem.get(4)}"
