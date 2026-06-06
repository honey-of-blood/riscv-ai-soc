`timescale 1ns/1ps

// Testbench wrapper: exposes branch_predictor ports directly for cocotb testing.
module bpred_wrap (
    input  logic        clk,
    input  logic        rst_n,
    input  logic [31:0] pc_if_i,
    output logic        predict_taken_o,
    output logic [31:0] predict_target_o,
    input  logic        branch_resolved_i,
    input  logic        branch_taken_i,
    input  logic [31:0] branch_pc_i,
    input  logic [31:0] branch_target_i
);

    branch_predictor u_bpred (
        .clk               (clk),
        .rst_n             (rst_n),
        .pc_if_i           (pc_if_i),
        .predict_taken_o   (predict_taken_o),
        .predict_target_o  (predict_target_o),
        .branch_resolved_i (branch_resolved_i),
        .branch_taken_i    (branch_taken_i),
        .branch_pc_i       (branch_pc_i),
        .branch_target_i   (branch_target_i)
    );

endmodule
