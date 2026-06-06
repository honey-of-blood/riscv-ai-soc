`timescale 1ns/1ps

// Test wrapper: fetch_stage + pipeline_reg_IF_ID wired together.
// Only used for simulation — not part of the final SoC.
module fetch_if_id_wrap (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,
    input  logic        flush_i,
    input  logic        branch_taken_i,
    input  logic [31:0] branch_target_i,
    input  logic [31:0] imem_rdata_i,
    output logic [31:0] imem_addr_o,
    output logic [31:0] pc_id_o,
    output logic [31:0] instr_id_o
);
    logic [31:0] pc_if, instr_if;

    logic pred_taken_if_w;

    fetch_stage u_fetch (
        .clk              (clk),
        .rst              (rst),
        .stall_i          (stall_i),
        .branch_taken_i   (branch_taken_i),
        .branch_target_i  (branch_target_i),
        .predict_taken_i  (1'b0),
        .predict_target_i (32'b0),
        .pred_taken_o     (pred_taken_if_w),
        .imem_addr_o      (imem_addr_o),
        .imem_rdata_i     (imem_rdata_i),
        .pc_if_o          (pc_if),
        .instr_if_o       (instr_if)
    );

    pipeline_reg_IF_ID u_if_id (
        .clk          (clk),
        .rst          (rst),
        .stall_i      (stall_i),
        .flush_i      (flush_i),
        .pc_if_i      (pc_if),
        .instr_if_i   (instr_if),
        .pred_taken_i (pred_taken_if_w),
        .pred_taken_o (),
        .pc_id_o      (pc_id_o),
        .instr_id_o   (instr_id_o)
    );

endmodule
