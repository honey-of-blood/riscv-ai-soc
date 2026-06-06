`timescale 1ns/1ps

// Testbench wrapper: exposes fast_mul ports directly for cocotb testing.
module mul_wrap (
    input  logic        clk,
    input  logic [31:0] a_i,
    input  logic [31:0] b_i,
    input  logic        signed_i,
    input  logic        mixed_i,
    output logic [63:0] result_o
);

    fast_mul #(.USE_DSP(0)) u_mul (
        .clk      (clk),
        .a_i      (a_i),
        .b_i      (b_i),
        .signed_i (signed_i),
        .mixed_i  (mixed_i),
        .result_o (result_o)
    );

endmodule
