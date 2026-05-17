`timescale 1ns/1ps
// 4×4 weight-stationary systolic array.  Computes Y = A × W (INT8→INT32).
//
// Layout: PE[k][n] receives weight W[k][n] and activation a_feed[k].
// Partial sums flow downward: PE[k][n].p_out feeds PE[k+1][n].p_in next cycle.
// The controller drives a_feed[k] = A[m][k] at time t = m+k so that
// Y[m][n] = Σ_k A[m][k]·W[k][n] emerges at y_out[n] one cycle after t=m+3.
//
// Weight packing (per row register): {W[k][3], W[k][2], W[k][1], W[k][0]}

module systolic_array (
    input  logic        clk,
    input  logic        rst_n,

    // Weights (driven combinationally from MMIO registers in accel_top)
    input  logic [31:0] w_row0,   // {W[0][3],W[0][2],W[0][1],W[0][0]}
    input  logic [31:0] w_row1,
    input  logic [31:0] w_row2,
    input  logic [31:0] w_row3,

    // Staggered activation feeds — one per PE row, driven by controller
    input  logic  [7:0] a_feed0,  // feeds PE row 0
    input  logic  [7:0] a_feed1,  // feeds PE row 1
    input  logic  [7:0] a_feed2,
    input  logic  [7:0] a_feed3,

    // Bottom-row outputs: y_out[c] = Y[current_output_row][c]
    output logic [31:0] y_out0, y_out1, y_out2, y_out3
);
    // Partial-sum wires between rows (psRC = p_out of PE[R][C])
    logic [31:0] ps00, ps01, ps02, ps03;
    logic [31:0] ps10, ps11, ps12, ps13;
    logic [31:0] ps20, ps21, ps22, ps23;
    logic [31:0] ps30, ps31, ps32, ps33;

    // ── Row 0 : p_in = 0 ──────────────────────────────────────────────────────
    pe r0c0(.clk(clk),.rst_n(rst_n),.w_in(w_row0[ 7: 0]),.a_in(a_feed0),.p_in(32'h0),.p_out(ps00));
    pe r0c1(.clk(clk),.rst_n(rst_n),.w_in(w_row0[15: 8]),.a_in(a_feed0),.p_in(32'h0),.p_out(ps01));
    pe r0c2(.clk(clk),.rst_n(rst_n),.w_in(w_row0[23:16]),.a_in(a_feed0),.p_in(32'h0),.p_out(ps02));
    pe r0c3(.clk(clk),.rst_n(rst_n),.w_in(w_row0[31:24]),.a_in(a_feed0),.p_in(32'h0),.p_out(ps03));

    // ── Row 1 ─────────────────────────────────────────────────────────────────
    pe r1c0(.clk(clk),.rst_n(rst_n),.w_in(w_row1[ 7: 0]),.a_in(a_feed1),.p_in(ps00),.p_out(ps10));
    pe r1c1(.clk(clk),.rst_n(rst_n),.w_in(w_row1[15: 8]),.a_in(a_feed1),.p_in(ps01),.p_out(ps11));
    pe r1c2(.clk(clk),.rst_n(rst_n),.w_in(w_row1[23:16]),.a_in(a_feed1),.p_in(ps02),.p_out(ps12));
    pe r1c3(.clk(clk),.rst_n(rst_n),.w_in(w_row1[31:24]),.a_in(a_feed1),.p_in(ps03),.p_out(ps13));

    // ── Row 2 ─────────────────────────────────────────────────────────────────
    pe r2c0(.clk(clk),.rst_n(rst_n),.w_in(w_row2[ 7: 0]),.a_in(a_feed2),.p_in(ps10),.p_out(ps20));
    pe r2c1(.clk(clk),.rst_n(rst_n),.w_in(w_row2[15: 8]),.a_in(a_feed2),.p_in(ps11),.p_out(ps21));
    pe r2c2(.clk(clk),.rst_n(rst_n),.w_in(w_row2[23:16]),.a_in(a_feed2),.p_in(ps12),.p_out(ps22));
    pe r2c3(.clk(clk),.rst_n(rst_n),.w_in(w_row2[31:24]),.a_in(a_feed2),.p_in(ps13),.p_out(ps23));

    // ── Row 3 : outputs ───────────────────────────────────────────────────────
    pe r3c0(.clk(clk),.rst_n(rst_n),.w_in(w_row3[ 7: 0]),.a_in(a_feed3),.p_in(ps20),.p_out(ps30));
    pe r3c1(.clk(clk),.rst_n(rst_n),.w_in(w_row3[15: 8]),.a_in(a_feed3),.p_in(ps21),.p_out(ps31));
    pe r3c2(.clk(clk),.rst_n(rst_n),.w_in(w_row3[23:16]),.a_in(a_feed3),.p_in(ps22),.p_out(ps32));
    pe r3c3(.clk(clk),.rst_n(rst_n),.w_in(w_row3[31:24]),.a_in(a_feed3),.p_in(ps23),.p_out(ps33));

    assign y_out0 = ps30;
    assign y_out1 = ps31;
    assign y_out2 = ps32;
    assign y_out3 = ps33;

endmodule
