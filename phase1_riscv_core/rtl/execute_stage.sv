`timescale 1ns/1ps

// EX stage: forwarding muxes, ALU, branch/jump evaluation.
// Purely combinational — no clock. The EX/MEM pipeline register is separate.
// Forwarding unit (hazard_unit.sv) drives fwd_a_i/fwd_b_i selects externally.
module execute_stage (
    // Control signals from ID/EX register
    input  logic        reg_write_i,
    input  logic        mem_read_i,
    input  logic        mem_write_i,
    input  logic        alu_src_b_i,    // 0=rs2_data, 1=imm
    input  logic        alu_src_a_i,    // 0=rs1_data, 1=PC (AUIPC/JAL)
    input  logic        branch_i,
    input  logic        jump_i,
    input  logic [3:0]  alu_ctrl_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [2:0]  funct3_i,

    // Data from ID/EX register
    input  logic [31:0] rs1_data_i,
    input  logic [31:0] rs2_data_i,
    input  logic [31:0] imm_i,
    input  logic [31:0] pc_i,
    input  logic [4:0]  rd_i,

    // Forwarding mux selects (from forwarding unit)
    // 2'b00 = use ID/EX data, 2'b01 = EX/MEM result, 2'b10 = MEM/WB result
    input  logic [1:0]  fwd_a_i,
    input  logic [1:0]  fwd_b_i,
    input  logic [31:0] fwd_ex_mem_i,
    input  logic [31:0] fwd_mem_wb_i,

    // To EX/MEM pipeline register
    output logic [31:0] alu_result_o,
    output logic [31:0] rs2_fwd_o,     // forwarded rs2 — write data for STORE
    output logic [31:0] pc_plus4_o,    // PC+4 for JAL/JALR writeback
    output logic [31:0] imm_o,
    output logic        reg_write_o,
    output logic        mem_read_o,
    output logic        mem_write_o,
    output logic [1:0]  wb_sel_o,
    output logic [2:0]  funct3_o,
    output logic [4:0]  rd_o,

    // Branch/jump resolution — wired back to fetch stage
    output logic        branch_taken_o,
    output logic [31:0] branch_target_o,

    // Forwarded operands exposed for M-extension unit (in riscv_core)
    output logic [31:0] rs1_fwd_o
);

    // -------------------------------------------------------------------------
    // Forwarding muxes for rs1 and rs2
    // -------------------------------------------------------------------------
    logic [31:0] rs1_fwd, rs2_fwd;

    always_comb begin
        case (fwd_a_i)
            2'b01:   rs1_fwd = fwd_ex_mem_i;
            2'b10:   rs1_fwd = fwd_mem_wb_i;
            default: rs1_fwd = rs1_data_i;
        endcase
    end

    always_comb begin
        case (fwd_b_i)
            2'b01:   rs2_fwd = fwd_ex_mem_i;
            2'b10:   rs2_fwd = fwd_mem_wb_i;
            default: rs2_fwd = rs2_data_i;
        endcase
    end

    // -------------------------------------------------------------------------
    // ALU input muxes
    // -------------------------------------------------------------------------
    logic [31:0] alu_a, alu_b;

    assign alu_a = alu_src_a_i ? pc_i    : rs1_fwd;
    assign alu_b = alu_src_b_i ? imm_i   : rs2_fwd;

    // -------------------------------------------------------------------------
    // ALU instantiation
    // -------------------------------------------------------------------------
    logic [31:0] alu_result;
    logic        alu_zero;

    alu u_alu (
        .a        (alu_a),
        .b        (alu_b),
        .alu_ctrl (alu_ctrl_i),
        .result   (alu_result),
        .zero     (alu_zero)
    );

    // -------------------------------------------------------------------------
    // Branch condition — direct comparison on forwarded operands, not via ALU.
    // funct3: BEQ=000 BNE=001 BLT=100 BGE=101 BLTU=110 BGEU=111
    // Icarus compat: signed cast extracted to assign outside always_comb.
    // -------------------------------------------------------------------------
    logic signed [31:0] rs1_sgn, rs2_sgn;
    assign rs1_sgn = rs1_fwd;
    assign rs2_sgn = rs2_fwd;

    logic branch_cond;
    always_comb begin
        case (funct3_i)
            3'b000:  branch_cond = (rs1_fwd == rs2_fwd);   // BEQ
            3'b001:  branch_cond = (rs1_fwd != rs2_fwd);   // BNE
            3'b100:  branch_cond = (rs1_sgn <  rs2_sgn);   // BLT
            3'b101:  branch_cond = (rs1_sgn >= rs2_sgn);   // BGE
            3'b110:  branch_cond = (rs1_fwd <  rs2_fwd);   // BLTU
            3'b111:  branch_cond = (rs1_fwd >= rs2_fwd);   // BGEU
            default: branch_cond = 1'b0;
        endcase
    end

    // -------------------------------------------------------------------------
    // Branch and jump targets
    // Branch: PC + imm (imm_gen already left-shifted by 1 and sign-extended)
    // JAL:    alu_src_a=1  →  alu_result = PC + imm  (correct as-is)
    // JALR:   alu_src_a=0  →  alu_result = rs1 + imm, clear bit 0 per spec
    // -------------------------------------------------------------------------
    logic [31:0] branch_target, jump_target;

    assign branch_target = pc_i + imm_i;
    assign jump_target   = alu_src_a_i ? alu_result : {alu_result[31:1], 1'b0};

    assign branch_taken_o  = (branch_i && branch_cond) || jump_i;
    assign branch_target_o = jump_i ? jump_target : branch_target;

    // -------------------------------------------------------------------------
    // Pass-throughs to EX/MEM pipeline register
    // -------------------------------------------------------------------------
    assign alu_result_o = alu_result;
    assign rs2_fwd_o    = rs2_fwd;
    assign rs1_fwd_o    = rs1_fwd;
    assign pc_plus4_o   = pc_i + 32'd4;
    assign imm_o        = imm_i;
    assign reg_write_o  = reg_write_i;
    assign mem_read_o   = mem_read_i;
    assign mem_write_o  = mem_write_i;
    assign wb_sel_o     = wb_sel_i;
    assign funct3_o     = funct3_i;
    assign rd_o         = rd_i;

endmodule
