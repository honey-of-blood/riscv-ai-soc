`timescale 1ns/1ps

// EX/MEM pipeline register.
// stall_i: freeze all outputs (cache miss stall — whole pipeline holds).
// No flush port: branch redirect flushes IF/ID and ID/EX upstream;
// by the time an instruction reaches EX/MEM it is committed to execute.
module pipeline_reg_EX_MEM (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,

    // Data from EX stage
    input  logic [31:0] alu_result_i,
    input  logic [31:0] rs2_data_i,    // forwarded rs2 — write data for STORE
    input  logic [31:0] pc_plus4_i,    // PC+4 for JAL/JALR writeback
    input  logic [31:0] imm_i,         // immediate for LUI writeback

    // Control signals from EX stage
    input  logic        reg_write_i,
    input  logic        mem_read_i,
    input  logic        mem_write_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [2:0]  funct3_i,      // byte/halfword select for loads/stores
    input  logic [4:0]  rd_i,

    // Phase 13: atomic passthrough
    input  logic        is_sc_i,
    input  logic        sc_store_en_i, // SC.W succeeded in EX stage
    input  logic        is_amo_i,
    input  logic [4:0]  amo_funct5_i,

    // Outputs to MEM stage
    output logic [31:0] alu_result_o,
    output logic [31:0] rs2_data_o,
    output logic [31:0] pc_plus4_o,
    output logic [31:0] imm_o,

    output logic        reg_write_o,
    output logic        mem_read_o,
    output logic        mem_write_o,
    output logic [1:0]  wb_sel_o,
    output logic [2:0]  funct3_o,
    output logic [4:0]  rd_o,

    output logic        is_sc_o,
    output logic        sc_store_en_o,
    output logic        is_amo_o,
    output logic [4:0]  amo_funct5_o
);

    always_ff @(posedge clk) begin
        if (rst) begin
            alu_result_o  <= 32'b0;
            rs2_data_o    <= 32'b0;
            pc_plus4_o    <= 32'b0;
            imm_o         <= 32'b0;
            reg_write_o   <= 1'b0;
            mem_read_o    <= 1'b0;
            mem_write_o   <= 1'b0;
            wb_sel_o      <= 2'b0;
            funct3_o      <= 3'b0;
            rd_o          <= 5'b0;
            is_sc_o       <= 1'b0;
            sc_store_en_o <= 1'b0;
            is_amo_o      <= 1'b0;
            amo_funct5_o  <= 5'b0;
        end else if (!stall_i) begin
            alu_result_o  <= alu_result_i;
            rs2_data_o    <= rs2_data_i;
            pc_plus4_o    <= pc_plus4_i;
            imm_o         <= imm_i;
            reg_write_o   <= reg_write_i;
            mem_read_o    <= mem_read_i;
            mem_write_o   <= mem_write_i;
            wb_sel_o      <= wb_sel_i;
            funct3_o      <= funct3_i;
            rd_o          <= rd_i;
            is_sc_o       <= is_sc_i;
            sc_store_en_o <= sc_store_en_i;
            is_amo_o      <= is_amo_i;
            amo_funct5_o  <= amo_funct5_i;
        end
    end

endmodule
