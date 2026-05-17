`timescale 1ns/1ps
// Single processing element: p_out = p_in + signed(a_in) * signed(w_in), registered.
// Weight is combinational (driven directly from MMIO registers in accel_top).

module pe (
    input  logic        clk,
    input  logic        rst_n,
    input  logic  [7:0] w_in,    // signed INT8 weight (combinational from MMIO)
    input  logic  [7:0] a_in,    // signed INT8 activation
    input  logic [31:0] p_in,    // partial sum from row above
    output logic [31:0] p_out    // accumulated partial sum (registered)
);
    // Icarus rule: signed casts must be assign outside always
    logic signed  [7:0] a_s;
    logic signed  [7:0] w_s;
    logic signed [15:0] product;
    assign a_s    = a_in;
    assign w_s    = w_in;
    assign product = a_s * w_s;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) p_out <= 32'h0;
        else        p_out <= p_in + {{16{product[15]}}, product};
    end
endmodule
