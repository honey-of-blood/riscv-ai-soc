"""
Decode stage testbench.
Tests:
  1. Control signals for every RV32I instruction type
  2. ALU control for all R-type and I-type arithmetic variants
  3. Register address pass-through
  4. ID/EX pipeline register: flush and stall behaviour
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# ---------------------------------------------------------------------------
# RV32I instruction encoders (same helpers as test_imm_gen.py)
# ---------------------------------------------------------------------------
def mk_r(funct7, rs2, rs1, funct3, rd, opcode):
    return (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode

def mk_i(imm12, rs1, funct3, rd, opcode):
    return ((imm12 & 0xFFF) << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode

def mk_s(imm12, rs2, rs1, funct3, opcode):
    hi = (imm12 >> 5) & 0x7F
    lo = imm12 & 0x1F
    return (hi << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (lo << 7) | opcode

def mk_b(imm13, rs2, rs1, funct3, opcode):
    i = imm13 & 0x1FFF
    return (((i >> 12) & 1) << 31) | (((i >> 5) & 0x3F) << 25) | (rs2 << 20) | \
           (rs1 << 15) | (funct3 << 12) | (((i >> 1) & 0xF) << 8) | \
           (((i >> 11) & 1) << 7) | opcode

def mk_u(imm20, rd, opcode):
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | opcode

def mk_j(imm21, rd, opcode):
    i = imm21 & 0x1FFFFF
    return (((i >> 20) & 1) << 31) | (((i >> 12) & 0xFF) << 12) | \
           (((i >> 11) & 1) << 20) | (((i >> 1) & 0x3FF) << 21) | (rd << 7) | opcode

# Opcodes
OP_R      = 0b011_0011
OP_IMM    = 0b001_0011
OP_LOAD   = 0b000_0011
OP_STORE  = 0b010_0011
OP_BRANCH = 0b110_0011
OP_JAL    = 0b110_1111
OP_JALR   = 0b110_0111
OP_LUI    = 0b011_0111
OP_AUIPC  = 0b001_0111

# ALU control encodings (must match alu.sv / decode_stage.sv)
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

# wb_sel
WB_ALU = 0b00
WB_MEM = 0b01
WB_PC4 = 0b10
WB_IMM = 0b11

NOP = 0x00000013  # ADDI x0, x0, 0


async def drive(dut, instr, rs1_data=0, rs2_data=0, pc=0):
    dut.instr_i.value    = instr
    dut.rs1_data_i.value = rs1_data
    dut.rs2_data_i.value = rs2_data
    dut.pc_i.value       = pc
    await Timer(1, unit="ns")


def ctrl(dut):
    """Read all control signals as a dict."""
    return {
        "reg_write":  int(dut.reg_write_o.value),
        "mem_read":   int(dut.mem_read_o.value),
        "mem_write":  int(dut.mem_write_o.value),
        "alu_src_b":  int(dut.alu_src_b_o.value),
        "alu_src_a":  int(dut.alu_src_a_o.value),
        "branch":     int(dut.branch_o.value),
        "jump":       int(dut.jump_o.value),
        "alu_ctrl":   int(dut.alu_ctrl_o.value),
        "wb_sel":     int(dut.wb_sel_o.value),
    }


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_r_type_control(dut):
    """R-type instructions: reg_write=1, alu_src_b=0, wb_sel=ALU."""
    # ADD x1, x2, x3
    await drive(dut, mk_r(0, 3, 2, 0b000, 1, OP_R))
    c = ctrl(dut)
    assert c["reg_write"] == 1,  "ADD: reg_write must be 1"
    assert c["mem_read"]  == 0,  "ADD: mem_read must be 0"
    assert c["mem_write"] == 0,  "ADD: mem_write must be 0"
    assert c["alu_src_b"] == 0,  "ADD: alu_src_b must be 0 (use rs2)"
    assert c["alu_src_a"] == 0,  "ADD: alu_src_a must be 0"
    assert c["branch"]    == 0,  "ADD: branch must be 0"
    assert c["jump"]      == 0,  "ADD: jump must be 0"
    assert c["alu_ctrl"]  == ALU_ADD, f"ADD: alu_ctrl expected {ALU_ADD}, got {c['alu_ctrl']}"
    assert c["wb_sel"]    == WB_ALU, "ADD: wb_sel must be ALU"

    # SUB x1, x2, x3 (funct7[5]=1)
    await drive(dut, mk_r(0b010_0000, 3, 2, 0b000, 1, OP_R))
    assert int(dut.alu_ctrl_o.value) == ALU_SUB, "SUB: alu_ctrl mismatch"

    dut._log.info("PASS: R-type control signals correct")


@cocotb.test()
async def test_i_type_control(dut):
    """I-type arithmetic: reg_write=1, alu_src_b=1."""
    # ADDI x1, x2, 42
    await drive(dut, mk_i(42, 2, 0b000, 1, OP_IMM))
    c = ctrl(dut)
    assert c["reg_write"] == 1, "ADDI: reg_write"
    assert c["alu_src_b"] == 1, "ADDI: alu_src_b must be 1 (use imm)"
    assert c["alu_src_a"] == 0, "ADDI: alu_src_a must be 0"
    assert c["mem_read"]  == 0, "ADDI: mem_read"
    assert c["mem_write"] == 0, "ADDI: mem_write"
    assert c["branch"]    == 0, "ADDI: branch"
    assert c["jump"]      == 0, "ADDI: jump"
    assert c["alu_ctrl"]  == ALU_ADD, f"ADDI alu_ctrl expected ADD"
    assert c["wb_sel"]    == WB_ALU,  "ADDI wb_sel"

    dut._log.info("PASS: I-type arithmetic control signals correct")


@cocotb.test()
async def test_load_control(dut):
    """LOAD: reg_write=1, mem_read=1, alu_src_b=1, wb_sel=MEM."""
    # LW x1, 4(x2)
    await drive(dut, mk_i(4, 2, 0b010, 1, OP_LOAD))
    c = ctrl(dut)
    assert c["reg_write"] == 1,   "LW: reg_write"
    assert c["mem_read"]  == 1,   "LW: mem_read"
    assert c["mem_write"] == 0,   "LW: mem_write"
    assert c["alu_src_b"] == 1,   "LW: alu_src_b"
    assert c["wb_sel"]    == WB_MEM, "LW: wb_sel must be MEM"
    assert c["alu_ctrl"]  == ALU_ADD, "LW: alu_ctrl must be ADD (addr=base+offset)"

    dut._log.info("PASS: LOAD control signals correct")


@cocotb.test()
async def test_store_control(dut):
    """STORE: mem_write=1, alu_src_b=1, reg_write=0."""
    # SW x3, 8(x2)
    await drive(dut, mk_s(8, 3, 2, 0b010, OP_STORE))
    c = ctrl(dut)
    assert c["reg_write"] == 0,   "SW: reg_write must be 0"
    assert c["mem_write"] == 1,   "SW: mem_write"
    assert c["mem_read"]  == 0,   "SW: mem_read"
    assert c["alu_src_b"] == 1,   "SW: alu_src_b"
    assert c["alu_ctrl"]  == ALU_ADD, "SW: alu_ctrl must be ADD"

    dut._log.info("PASS: STORE control signals correct")


@cocotb.test()
async def test_branch_control(dut):
    """BRANCH: branch=1, reg_write=0, mem=0."""
    # BEQ x1, x2, +8
    await drive(dut, mk_b(8, 2, 1, 0b000, OP_BRANCH))
    c = ctrl(dut)
    assert c["branch"]    == 1, "BEQ: branch"
    assert c["reg_write"] == 0, "BEQ: reg_write must be 0"
    assert c["mem_read"]  == 0, "BEQ: mem_read"
    assert c["mem_write"] == 0, "BEQ: mem_write"
    assert c["jump"]      == 0, "BEQ: jump"

    dut._log.info("PASS: BRANCH control signals correct")


@cocotb.test()
async def test_jal_control(dut):
    """JAL: jump=1, reg_write=1, alu_src_a=1 (PC), wb_sel=PC4."""
    # JAL x1, +16
    await drive(dut, mk_j(16, 1, OP_JAL), pc=0x100)
    c = ctrl(dut)
    assert c["reg_write"] == 1,   "JAL: reg_write"
    assert c["jump"]      == 1,   "JAL: jump"
    assert c["alu_src_a"] == 1,   "JAL: alu_src_a must be 1 (PC)"
    assert c["alu_src_b"] == 1,   "JAL: alu_src_b must be 1 (imm)"
    assert c["wb_sel"]    == WB_PC4, "JAL: wb_sel must be PC+4"
    assert c["branch"]    == 0,   "JAL: branch must be 0"
    assert c["mem_read"]  == 0,   "JAL: mem_read"

    dut._log.info("PASS: JAL control signals correct")


@cocotb.test()
async def test_jalr_control(dut):
    """JALR: jump=1, reg_write=1, alu_src_a=0 (rs1), wb_sel=PC4."""
    # JALR x1, x2, 0
    await drive(dut, mk_i(0, 2, 0b000, 1, OP_JALR))
    c = ctrl(dut)
    assert c["reg_write"] == 1,   "JALR: reg_write"
    assert c["jump"]      == 1,   "JALR: jump"
    assert c["alu_src_a"] == 0,   "JALR: alu_src_a must be 0 (rs1, not PC)"
    assert c["alu_src_b"] == 1,   "JALR: alu_src_b"
    assert c["wb_sel"]    == WB_PC4, "JALR: wb_sel"
    assert c["branch"]    == 0,   "JALR: branch must be 0"

    dut._log.info("PASS: JALR control signals correct")


@cocotb.test()
async def test_lui_control(dut):
    """LUI: reg_write=1, wb_sel=IMM, alu_src_a=0 (no PC)."""
    # LUI x1, 0x12345
    await drive(dut, mk_u(0x12345, 1, OP_LUI))
    c = ctrl(dut)
    assert c["reg_write"] == 1,   "LUI: reg_write"
    assert c["wb_sel"]    == WB_IMM, "LUI: wb_sel must be IMM"
    assert c["alu_src_a"] == 0,   "LUI: alu_src_a must be 0"
    assert c["mem_read"]  == 0,   "LUI: mem_read"
    assert c["branch"]    == 0,   "LUI: branch"
    assert c["jump"]      == 0,   "LUI: jump"

    dut._log.info("PASS: LUI control signals correct")


@cocotb.test()
async def test_auipc_control(dut):
    """AUIPC: reg_write=1, alu_src_a=1 (PC), alu_src_b=1 (imm), wb_sel=ALU."""
    # AUIPC x1, 0x10
    await drive(dut, mk_u(0x10, 1, OP_AUIPC), pc=0x200)
    c = ctrl(dut)
    assert c["reg_write"] == 1,   "AUIPC: reg_write"
    assert c["alu_src_a"] == 1,   "AUIPC: alu_src_a must be 1 (PC)"
    assert c["alu_src_b"] == 1,   "AUIPC: alu_src_b"
    assert c["wb_sel"]    == WB_ALU, "AUIPC: wb_sel must be ALU (PC+imm)"
    assert c["alu_ctrl"]  == ALU_ADD, "AUIPC: alu_ctrl must be ADD"
    assert c["branch"]    == 0,   "AUIPC: branch"
    assert c["jump"]      == 0,   "AUIPC: jump"

    dut._log.info("PASS: AUIPC control signals correct")


@cocotb.test()
async def test_alu_ctrl_all_ops(dut):
    """ALU control: all 10 R-type ops and all 9 I-type ALU ops decoded correctly."""
    # (funct7, funct3, opcode, expected_alu_ctrl, description)
    r_cases = [
        (0b000_0000, 0b000, OP_R,   ALU_ADD,  "ADD"),
        (0b010_0000, 0b000, OP_R,   ALU_SUB,  "SUB"),
        (0b000_0000, 0b001, OP_R,   ALU_SLL,  "SLL"),
        (0b000_0000, 0b010, OP_R,   ALU_SLT,  "SLT"),
        (0b000_0000, 0b011, OP_R,   ALU_SLTU, "SLTU"),
        (0b000_0000, 0b100, OP_R,   ALU_XOR,  "XOR"),
        (0b000_0000, 0b101, OP_R,   ALU_SRL,  "SRL"),
        (0b010_0000, 0b101, OP_R,   ALU_SRA,  "SRA"),
        (0b000_0000, 0b110, OP_R,   ALU_OR,   "OR"),
        (0b000_0000, 0b111, OP_R,   ALU_AND,  "AND"),
        # I-type (funct7 field is shamt/ignored except for SRAI)
        (0b000_0000, 0b000, OP_IMM, ALU_ADD,  "ADDI"),
        (0b000_0000, 0b001, OP_IMM, ALU_SLL,  "SLLI"),
        (0b000_0000, 0b010, OP_IMM, ALU_SLT,  "SLTI"),
        (0b000_0000, 0b011, OP_IMM, ALU_SLTU, "SLTIU"),
        (0b000_0000, 0b100, OP_IMM, ALU_XOR,  "XORI"),
        (0b000_0000, 0b101, OP_IMM, ALU_SRL,  "SRLI"),
        (0b010_0000, 0b101, OP_IMM, ALU_SRA,  "SRAI"),
        (0b000_0000, 0b110, OP_IMM, ALU_OR,   "ORI"),
        (0b000_0000, 0b111, OP_IMM, ALU_AND,  "ANDI"),
    ]
    errors = 0
    for funct7, funct3, opcode, expected, name in r_cases:
        instr = mk_r(funct7, 2, 1, funct3, 1, opcode)
        await drive(dut, instr)
        got = int(dut.alu_ctrl_o.value)
        if got != expected:
            dut._log.error(f"{name}: expected alu_ctrl={expected}, got {got}")
            errors += 1
    assert errors == 0
    dut._log.info(f"PASS: ALU control correct for all 19 R/I-type variants")


@cocotb.test()
async def test_reg_address_passthrough(dut):
    """rs1, rs2, rd fields must be correctly extracted from instruction."""
    # ADD x7, x13, x21
    instr = mk_r(0, 21, 13, 0b000, 7, OP_R)
    await drive(dut, instr, rs1_data=0xAAAA, rs2_data=0xBBBB)
    assert int(dut.rs1_o.value)      == 13,    f"rs1: expected 13, got {int(dut.rs1_o.value)}"
    assert int(dut.rs2_o.value)      == 21,    f"rs2: expected 21, got {int(dut.rs2_o.value)}"
    assert int(dut.rd_o.value)       == 7,     f"rd: expected 7, got {int(dut.rd_o.value)}"
    assert int(dut.rs1_data_o.value) == 0xAAAA, "rs1_data passthrough"
    assert int(dut.rs2_data_o.value) == 0xBBBB, "rs2_data passthrough"

    dut._log.info("PASS: register address and data pass-through correct")


@cocotb.test()
async def test_nop_decode(dut):
    """NOP (ADDI x0, x0, 0) must decode without side effects."""
    await drive(dut, NOP)
    c = ctrl(dut)
    # reg_write=1 is fine for NOP (rd=x0, reg_file will ignore it)
    assert c["mem_read"]  == 0, "NOP: mem_read"
    assert c["mem_write"] == 0, "NOP: mem_write"
    assert c["branch"]    == 0, "NOP: branch"
    assert c["jump"]      == 0, "NOP: jump"

    dut._log.info("PASS: NOP decodes without dangerous side effects")


@cocotb.test()
async def test_id_ex_pipeline_reg_flush(dut):
    """ID/EX pipeline register: flush zeroes all control signals."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.rst.value   = 1
    dut.flush_i.value = 0
    dut.stall_i.value = 0
    await RisingEdge(dut.clk)
    dut.rst.value = 0

    # Drive ADDI into decode stage, let it propagate to ID/EX
    instr = mk_i(42, 1, 0, 2, OP_IMM)
    dut.instr_i.value    = instr
    dut.rs1_data_i.value = 0x1234
    dut.rs2_data_i.value = 0
    dut.pc_i.value       = 0x10

    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    # Verify that reg_write propagated
    assert int(dut.reg_write_ex_o.value) == 1, \
        f"Expected reg_write=1 after ADDI, got {int(dut.reg_write_ex_o.value)}"

    # Now flush
    dut.flush_i.value = 1
    await RisingEdge(dut.clk)
    dut.flush_i.value = 0
    await Timer(1, unit="ns")

    # All control signals must be 0
    for sig_name, sig in [
        ("reg_write", dut.reg_write_ex_o),
        ("mem_read",  dut.mem_read_ex_o),
        ("mem_write", dut.mem_write_ex_o),
        ("branch",    dut.branch_ex_o),
        ("jump",      dut.jump_ex_o),
    ]:
        val = int(sig.value)
        assert val == 0, f"After flush: {sig_name} expected 0, got {val}"

    dut._log.info("PASS: ID/EX flush zeroes all control signals (NOP bubble)")


@cocotb.test()
async def test_id_ex_pipeline_reg_stall(dut):
    """ID/EX pipeline register: stall holds all values."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.rst.value   = 1
    dut.flush_i.value = 0
    dut.stall_i.value = 0
    await RisingEdge(dut.clk)
    dut.rst.value = 0

    # Load a LW instruction
    instr = mk_i(4, 2, 0b010, 5, OP_LOAD)
    dut.instr_i.value    = instr
    dut.rs1_data_i.value = 0xDEAD
    dut.pc_i.value       = 0x20
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    saved_rw  = int(dut.reg_write_ex_o.value)
    saved_mr  = int(dut.mem_read_ex_o.value)
    saved_rd  = int(dut.rd_ex_o.value)

    # Stall for 2 cycles — change decode inputs, ID/EX must hold
    dut.stall_i.value    = 1
    dut.instr_i.value    = NOP
    dut.rs1_data_i.value = 0x0
    for _ in range(2):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.reg_write_ex_o.value) == saved_rw, "reg_write changed during stall"
        assert int(dut.mem_read_ex_o.value)  == saved_mr, "mem_read changed during stall"
        assert int(dut.rd_ex_o.value)        == saved_rd, "rd changed during stall"

    dut.stall_i.value = 0
    dut._log.info("PASS: ID/EX stall holds all values for 2 cycles")
