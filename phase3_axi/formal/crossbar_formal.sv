`timescale 1ns/1ps
// Formal top — feeds unconstrained inputs to axi4_crossbar.
// Formal properties (P1–P4) live in axi4_crossbar.sv under `ifdef FORMAL.
// This file's only job: instantiate the DUT with a free clock/reset and
// unconstrained master+slave signals so the solver can explore all states.
`ifdef FORMAL
module crossbar_formal;

  (* gclk *) reg gclk;
  reg clk;
  initial clk = 0;
  always @(posedge gclk) clk <= ~clk;

  // Free inputs
  reg        rst_n;
  reg [31:0] m0_awaddr,  m1_awaddr,  m2_awaddr;
  reg        m0_awvalid, m1_awvalid, m2_awvalid;
  reg [31:0] m0_wdata,   m1_wdata,   m2_wdata;
  reg  [3:0] m0_wstrb,   m1_wstrb,   m2_wstrb;
  reg        m0_wvalid,  m1_wvalid,  m2_wvalid;
  reg        m0_bready,  m1_bready,  m2_bready;
  reg [31:0] m0_araddr,  m1_araddr,  m2_araddr;
  reg        m0_arvalid, m1_arvalid, m2_arvalid;
  reg        m0_rready,  m1_rready,  m2_rready;
  reg        s0_awready, s1_awready, s2_awready;
  reg        s0_wready,  s1_wready,  s2_wready;
  reg  [1:0] s0_bresp,   s1_bresp,   s2_bresp;
  reg        s0_bvalid,  s1_bvalid,  s2_bvalid;
  reg        s0_arready, s1_arready, s2_arready;
  reg [31:0] s0_rdata,   s1_rdata,   s2_rdata;
  reg  [1:0] s0_rresp,   s1_rresp,   s2_rresp;
  reg        s0_rvalid,  s1_rvalid,  s2_rvalid;

  axi4_crossbar dut (
    .clk(clk), .rst_n(rst_n),
    .m0_awaddr(m0_awaddr),   .m0_awvalid(m0_awvalid), .m0_awready(),
    .m0_wdata(m0_wdata),     .m0_wstrb(m0_wstrb),
    .m0_wvalid(m0_wvalid),   .m0_wready(),
    .m0_bresp(),             .m0_bvalid(),             .m0_bready(m0_bready),
    .m0_araddr(m0_araddr),   .m0_arvalid(m0_arvalid), .m0_arready(),
    .m0_rdata(),             .m0_rresp(),
    .m0_rvalid(),            .m0_rready(m0_rready),
    .m1_awaddr(m1_awaddr),   .m1_awvalid(m1_awvalid), .m1_awready(),
    .m1_wdata(m1_wdata),     .m1_wstrb(m1_wstrb),
    .m1_wvalid(m1_wvalid),   .m1_wready(),
    .m1_bresp(),             .m1_bvalid(),             .m1_bready(m1_bready),
    .m1_araddr(m1_araddr),   .m1_arvalid(m1_arvalid), .m1_arready(),
    .m1_rdata(),             .m1_rresp(),
    .m1_rvalid(),            .m1_rready(m1_rready),
    .m2_awaddr(m2_awaddr),   .m2_awvalid(m2_awvalid), .m2_awready(),
    .m2_wdata(m2_wdata),     .m2_wstrb(m2_wstrb),
    .m2_wvalid(m2_wvalid),   .m2_wready(),
    .m2_bresp(),             .m2_bvalid(),             .m2_bready(m2_bready),
    .m2_araddr(m2_araddr),   .m2_arvalid(m2_arvalid), .m2_arready(),
    .m2_rdata(),             .m2_rresp(),
    .m2_rvalid(),            .m2_rready(m2_rready),
    .s0_awaddr(),            .s0_awvalid(),            .s0_awready(s0_awready),
    .s0_wdata(),             .s0_wstrb(),
    .s0_wvalid(),            .s0_wready(s0_wready),
    .s0_bresp(s0_bresp),     .s0_bvalid(s0_bvalid),   .s0_bready(),
    .s0_araddr(),            .s0_arvalid(),            .s0_arready(s0_arready),
    .s0_rdata(s0_rdata),     .s0_rresp(s0_rresp),
    .s0_rvalid(s0_rvalid),   .s0_rready(),
    .s1_awaddr(),            .s1_awvalid(),            .s1_awready(s1_awready),
    .s1_wdata(),             .s1_wstrb(),
    .s1_wvalid(),            .s1_wready(s1_wready),
    .s1_bresp(s1_bresp),     .s1_bvalid(s1_bvalid),   .s1_bready(),
    .s1_araddr(),            .s1_arvalid(),            .s1_arready(s1_arready),
    .s1_rdata(s1_rdata),     .s1_rresp(s1_rresp),
    .s1_rvalid(s1_rvalid),   .s1_rready(),
    .s2_awaddr(),            .s2_awvalid(),            .s2_awready(s2_awready),
    .s2_wdata(),             .s2_wstrb(),
    .s2_wvalid(),            .s2_wready(s2_wready),
    .s2_bresp(s2_bresp),     .s2_bvalid(s2_bvalid),   .s2_bready(),
    .s2_araddr(),            .s2_arvalid(),            .s2_arready(s2_arready),
    .s2_rdata(s2_rdata),     .s2_rresp(s2_rresp),
    .s2_rvalid(s2_rvalid),   .s2_rready()
  );

endmodule
`endif
