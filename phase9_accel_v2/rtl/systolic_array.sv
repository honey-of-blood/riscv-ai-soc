`timescale 1ns/1ps
// Parametric N×N weight-stationary systolic array.
// pe.sv is unchanged — only the instantiation topology is parametric.
// Set N=4 for simulation speed, N=8 for Basys3/50T, N=16 for 100T-class.
//
// Dataflow:
//   - Weights loaded once per tile via w_row[r] packed bytes.
//   - Activations staggered: row r receives its input at cycle m+r.
//   - Partial sums flow down each column; y_out[c] is the bottom accumulator.

module systolic_array #(
    parameter int N = 4
)(
    input  logic              clk,
    input  logic              rst_n,
    input  logic [N*8-1:0]   w_row  [0:N-1],   // N packed INT8 weights per row
    input  logic [7:0]        a_feed [0:N-1],   // N staggered activation feeds
    output logic [31:0]       y_out  [0:N-1]    // N accumulated INT32 outputs
);
    // ps[r][c] = partial sum entering row r, column c
    logic [31:0] ps [0:N][0:N-1];

    // Zero feed into row 0
    genvar r, c;
    generate
        for (r = 0; r < N; r++) begin : g_row
            assign ps[0][r] = 32'd0;
            for (c = 0; c < N; c++) begin : g_col
                pe u_pe (
                    .clk   (clk),
                    .rst_n (rst_n),
                    .w_in  (w_row[r][c*8 +: 8]),
                    .a_in  (a_feed[r]),
                    .p_in  (ps[r][c]),
                    .p_out (ps[r+1][c])
                );
            end
        end
        for (c = 0; c < N; c++) begin : g_out
            assign y_out[c] = ps[N][c];
        end
    endgenerate

endmodule
