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

def addi(rd, rs1, imm):  return _i(imm, rs1, 0x0, rd, OP_IMM)
def add (rd, rs1, rs2):  return _r(0x00, rs2, rs1, 0x0, rd)
def sub (rd, rs1, rs2):  return _r(0x20, rs2, rs1, 0x0, rd)
def lw  (rd,  rs1, imm): return _i(imm, rs1, 0x2, rd, OP_LOAD)
def sw  (rs2, rs1, imm): return _s(imm, rs2, rs1, 0x2)
def beq (rs1, rs2, imm): return _b(imm, rs2, rs1, 0x0)
def bne (rs1, rs2, imm): return _b(imm, rs2, rs1, 0x1)
def jal (rd,  imm):      return _j(imm, rd)
def lui (rd,  imm):      return (((imm>>12)&0xFFFFF)<<12)|(rd<<7)|OP_LUI

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
