// Synthesisable tie-off stub for accel_top — core-only run excludes the
// systolic accelerator. Returns AXI OKAY on all transactions, zero read data.
`timescale 1ns/1ps
module accel_top (
    input  logic        clk,
    input  logic        rst_n,

    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,

    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,

    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,

    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,

    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready
);
    assign s_awready = 1'b1;
    assign s_wready  = 1'b1;
    assign s_bresp   = 2'b00;
    assign s_bvalid  = 1'b1;
    assign s_arready = 1'b1;
    assign s_rdata   = 32'b0;
    assign s_rresp   = 2'b00;
    assign s_rvalid  = 1'b1;
endmodule
