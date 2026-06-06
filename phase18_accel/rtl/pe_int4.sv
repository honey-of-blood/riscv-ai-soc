`timescale 1ns/1ps
// Parameterised MAC processing element for INT4 / INT8 systolic arrays.
// c_o <= c_i + sign_extend(a_i * b_i)
// a_o, b_o pass activations and weights to the next PE in the array.
//
// Usage:
//   ACT_W=4  → INT4 (signed −8..7)   PROD_W= 8, sign-extends 8→32
//   ACT_W=8  → INT8 (signed −128..127) PROD_W=16, sign-extends 16→32

module pe_int4 #(
    parameter int ACT_W = 4,    // activation/weight width: 4 or 8
    parameter int ACCW  = 32    // accumulator width
) (
    input  logic                     clk,
    input  logic                     rst_n,

    input  logic signed [ACT_W-1:0]  a_i,   // activation in  (passes through row)
    input  logic signed [ACT_W-1:0]  b_i,   // weight in      (stationary or col)
    input  logic signed [ACCW-1:0]   c_i,   // partial sum in

    output logic signed [ACCW-1:0]   c_o,   // partial sum out (registered)
    output logic signed [ACT_W-1:0]  a_o,   // activation passthrough
    output logic signed [ACT_W-1:0]  b_o    // weight passthrough
);

    // Signed multiply: 2*ACT_W-bit result, then sign-extend to ACCW
    localparam int PROD_W = 2 * ACT_W;
    localparam int EXT_W  = ACCW - PROD_W;

    logic signed [PROD_W-1:0] mult_raw;
    logic signed [ACCW-1:0]   prod_sext;
    assign mult_raw  = a_i * b_i;
    assign prod_sext = {{EXT_W{mult_raw[PROD_W-1]}}, mult_raw};

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            c_o <= '0;
            a_o <= '0;
            b_o <= '0;
        end else begin
            c_o <= c_i + prod_sext;
            a_o <= a_i;
            b_o <= b_i;
        end
    end

endmodule
