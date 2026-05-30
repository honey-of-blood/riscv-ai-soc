`timescale 1ns/1ps

// ID/EX pipeline register.
// flush_i: insert NOP (zero all control signals) — used for branch taken
//          AND for load-use stall (hazard unit sends flush to ID/EX).
// stall_i: hold current values (reserved for future multi-cycle stalls).
module pipeline_reg_ID_EX (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,
    input  logic        flush_i,

    // Control signals from decode stage
    input  logic        reg_write_i,
    input  logic        mem_read_i,
    input  logic        mem_write_i,
    input  logic        alu_src_b_i,
    input  logic        alu_src_a_i,
    input  logic        branch_i,
    input  logic        jump_i,
    input  logic [3:0]  alu_ctrl_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [2:0]  funct3_i,

    // Data from decode stage
    input  logic [31:0] rs1_data_i,
    input  logic [31:0] rs2_data_i,
    input  logic [31:0] imm_i,
    input  logic [31:0] pc_i,

    // Register addresses — forwarding/hazard unit needs these
    input  logic [4:0]  rs1_i,
    input  logic [4:0]  rs2_i,
    input  logic [4:0]  rd_i,

    // Outputs to EX stage
    output logic        reg_write_o,
    output logic        mem_read_o,
    output logic        mem_write_o,
    output logic        alu_src_b_o,
    output logic        alu_src_a_o,
    output logic        branch_o,
    output logic        jump_o,
    output logic [3:0]  alu_ctrl_o,
    output logic [1:0]  wb_sel_o,
    output logic [2:0]  funct3_o,

    output logic [31:0] rs1_data_o,
    output logic [31:0] rs2_data_o,
    output logic [31:0] imm_o,
    output logic [31:0] pc_o,

    output logic [4:0]  rs1_o,
    output logic [4:0]  rs2_o,
    output logic [4:0]  rd_o,

    // M-extension passthrough
    input  logic        is_mext_i,
    output logic        is_mext_o,

    // CSR / MRET passthrough
    input  logic        is_csr_i,
    input  logic        is_mret_i,
    input  logic [11:0] csr_addr_i,
    output logic        is_csr_o,
    output logic        is_mret_o,
    output logic [11:0] csr_addr_o,

    // Phase 13: exception + atomic passthroughs
    input  logic        is_ecall_i,
    input  logic        is_ebreak_i,
    input  logic        is_illegal_i,
    input  logic        is_lr_i,
    input  logic        is_sc_i,
    input  logic        is_amo_i,
    input  logic [4:0]  amo_funct5_i,
    output logic        is_ecall_o,
    output logic        is_ebreak_o,
    output logic        is_illegal_o,
    output logic        is_lr_o,
    output logic        is_sc_o,
    output logic        is_amo_o,
    output logic [4:0]  amo_funct5_o
);

    always_ff @(posedge clk) begin
        if (rst || flush_i) begin
            // NOP: zero all control signals; data values don't matter
            reg_write_o  <= 1'b0;
            mem_read_o   <= 1'b0;
            mem_write_o  <= 1'b0;
            alu_src_b_o  <= 1'b0;
            alu_src_a_o  <= 1'b0;
            branch_o     <= 1'b0;
            jump_o       <= 1'b0;
            alu_ctrl_o   <= 4'b0;
            wb_sel_o     <= 2'b0;
            funct3_o     <= 3'b0;
            rs1_data_o   <= 32'b0;
            rs2_data_o   <= 32'b0;
            imm_o        <= 32'b0;
            pc_o         <= 32'b0;
            rs1_o        <= 5'b0;
            rs2_o        <= 5'b0;
            rd_o         <= 5'b0;
            is_mext_o    <= 1'b0;
            is_csr_o     <= 1'b0;
            is_mret_o    <= 1'b0;
            csr_addr_o   <= 12'b0;
            is_ecall_o   <= 1'b0;
            is_ebreak_o  <= 1'b0;
            is_illegal_o <= 1'b0;
            is_lr_o      <= 1'b0;
            is_sc_o      <= 1'b0;
            is_amo_o     <= 1'b0;
            amo_funct5_o <= 5'b0;
        end else if (!stall_i) begin
            reg_write_o  <= reg_write_i;
            mem_read_o   <= mem_read_i;
            mem_write_o  <= mem_write_i;
            alu_src_b_o  <= alu_src_b_i;
            alu_src_a_o  <= alu_src_a_i;
            branch_o     <= branch_i;
            jump_o       <= jump_i;
            alu_ctrl_o   <= alu_ctrl_i;
            wb_sel_o     <= wb_sel_i;
            funct3_o     <= funct3_i;
            rs1_data_o   <= rs1_data_i;
            rs2_data_o   <= rs2_data_i;
            imm_o        <= imm_i;
            pc_o         <= pc_i;
            rs1_o        <= rs1_i;
            rs2_o        <= rs2_i;
            rd_o         <= rd_i;
            is_mext_o    <= is_mext_i;
            is_csr_o     <= is_csr_i;
            is_mret_o    <= is_mret_i;
            csr_addr_o   <= csr_addr_i;
            is_ecall_o   <= is_ecall_i;
            is_ebreak_o  <= is_ebreak_i;
            is_illegal_o <= is_illegal_i;
            is_lr_o      <= is_lr_i;
            is_sc_o      <= is_sc_i;
            is_amo_o     <= is_amo_i;
            amo_funct5_o <= amo_funct5_i;
        end
    end

endmodule
