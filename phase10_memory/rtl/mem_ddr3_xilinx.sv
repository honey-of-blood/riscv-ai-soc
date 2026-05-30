`timescale 1ns/1ps
// DDR3 memory backend — Xilinx 7-series wrapper.
//
// This module wraps Vivado's Memory Interface Generator (MIG) 7-series IP
// and exposes the same AXI4-Lite 32-bit slave interface as mem_bram_backend,
// so it can be dropped into any board wrapper that supports DDR3.
//
// ─────────────────────────────────────────────────────────────────────────────
// IMPORTANT — Before synthesis:
//   1. In Vivado: Tools → Create IP → MIG 7-Series
//      - Component name:  mig_7series_0
//      - AXI4 interface:  Yes (128-bit data, 30-bit address)
//      - Clock period:    5000 ps (200 MHz)
//      - Memory type:     DDR3L (1.35 V)
//      - Memory part:     Nexys A7-50T: MT41K128M16JT-125
//                         Nexys A7-100T/Arty A7-100T: MT41K128M16JT-125
//      - Data width:      16-bit (Nexys A7), 16-bit (Arty A7)
//   2. Generate the IP. The mig_7series_0.v file will appear in the IP
//      output directory — add it to your Vivado project source set.
//   3. sys_clk_i must be the 200 MHz reference clock from an MMCM.
// ─────────────────────────────────────────────────────────────────────────────
//
// Reset interlock: hold soc_rst_n low (keep SoC in reset) until
// init_calib_complete goes high — DDR3 calibration takes ~10 ms.
// Releasing reset before calibration produces garbage reads.
//
// Connections:
//   sys_clk_i        ← 200 MHz from MMCM (clk_ref input of fpga_top)
//   sys_rst_n        ← board-level power-on reset (active low)
//   s_axi_*          ← soc_top m_mem_* (via axi_width_32to128)
//   ddr3_*           ← DDR3 SDRAM physical pins on FPGA I/O bank
//   init_calib_complete → AND with sys_rst_n to gate soc_rst_n

module mem_ddr3_xilinx (
    input  logic         sys_clk_i,       // 200 MHz reference clock
    input  logic         sys_rst_n,       // board reset (active low)

    // AXI4-Lite 32-bit slave (from soc_top m_mem_*)
    input  logic         clk,
    input  logic [31:0]  s_awaddr,
    input  logic         s_awvalid,
    output logic         s_awready,
    input  logic [31:0]  s_wdata,
    input  logic  [3:0]  s_wstrb,
    input  logic         s_wvalid,
    output logic         s_wready,
    output logic  [1:0]  s_bresp,
    output logic         s_bvalid,
    input  logic         s_bready,
    input  logic [31:0]  s_araddr,
    input  logic         s_arvalid,
    output logic         s_arready,
    output logic [31:0]  s_rdata,
    output logic  [1:0]  s_rresp,
    output logic         s_rvalid,
    input  logic         s_rready,

    // DDR3 physical pins (connect to XDC constraints)
    output logic [14:0]  ddr3_addr,
    output logic  [2:0]  ddr3_ba,
    output logic         ddr3_cas_n,
    output logic  [0:0]  ddr3_ck_n,
    output logic  [0:0]  ddr3_ck_p,
    output logic  [0:0]  ddr3_cke,
    output logic  [0:0]  ddr3_cs_n,
    inout  logic  [1:0]  ddr3_dm,
    inout  logic [15:0]  ddr3_dq,
    inout  logic  [1:0]  ddr3_dqs_n,
    inout  logic  [1:0]  ddr3_dqs_p,
    output logic  [0:0]  ddr3_odt,
    output logic         ddr3_ras_n,
    output logic         ddr3_reset_n,
    output logic         ddr3_we_n,

    output logic         init_calib_complete   // high when DDR3 is ready
);

    // 32-bit → 128-bit AXI width converter
    logic [29:0]  m_awaddr_128;
    logic  [7:0]  m_awlen;
    logic  [2:0]  m_awsize;
    logic  [1:0]  m_awburst;
    logic         m_awvalid_128, m_awready_128;
    logic [127:0] m_wdata_128;
    logic  [15:0] m_wstrb_128;
    logic         m_wlast, m_wvalid_128, m_wready_128;
    logic  [1:0]  m_bresp_128;
    logic         m_bvalid_128, m_bready_128;
    logic [29:0]  m_araddr_128;
    logic  [7:0]  m_arlen;
    logic  [2:0]  m_arsize;
    logic  [1:0]  m_arburst;
    logic         m_arvalid_128, m_arready_128;
    logic [127:0] m_rdata_128;
    logic  [1:0]  m_rresp_128;
    logic         m_rlast, m_rvalid_128, m_rready_128;

    axi_width_32to128 u_w32to128 (
        .clk        (clk),          .rst_n      (sys_rst_n),
        .s_awaddr   (s_awaddr),     .s_awvalid  (s_awvalid),   .s_awready  (s_awready),
        .s_wdata    (s_wdata),      .s_wstrb    (s_wstrb),     .s_wvalid   (s_wvalid),
        .s_wready   (s_wready),     .s_bresp    (s_bresp),     .s_bvalid   (s_bvalid),
        .s_bready   (s_bready),
        .s_araddr   (s_araddr),     .s_arvalid  (s_arvalid),   .s_arready  (s_arready),
        .s_rdata    (s_rdata),      .s_rresp    (s_rresp),     .s_rvalid   (s_rvalid),
        .s_rready   (s_rready),
        .m_awaddr   (m_awaddr_128), .m_awlen    (m_awlen),     .m_awsize   (m_awsize),
        .m_awburst  (m_awburst),    .m_awvalid  (m_awvalid_128),.m_awready (m_awready_128),
        .m_wdata    (m_wdata_128),  .m_wstrb    (m_wstrb_128), .m_wlast    (m_wlast),
        .m_wvalid   (m_wvalid_128), .m_wready   (m_wready_128),
        .m_bresp    (m_bresp_128),  .m_bvalid   (m_bvalid_128),.m_bready   (m_bready_128),
        .m_araddr   (m_araddr_128), .m_arlen    (m_arlen),     .m_arsize   (m_arsize),
        .m_arburst  (m_arburst),    .m_arvalid  (m_arvalid_128),.m_arready (m_arready_128),
        .m_rdata    (m_rdata_128),  .m_rresp    (m_rresp_128), .m_rlast    (m_rlast),
        .m_rvalid   (m_rvalid_128), .m_rready   (m_rready_128)
    );

    // ─────────────────────────────────────────────────────────────────────────
    // mig_7series_0 instantiation — GENERATED BY VIVADO, not hand-written.
    //
    // After running MIG IP generation in Vivado, replace the placeholder below
    // with the actual instantiation from the generated example_top.v.
    //
    // Key AXI slave port connections from MIG (128-bit, LEN/SIZE/BURST capable):
    //   s_axi_awid     = 4'b0
    //   s_axi_awaddr   = {2'b0, m_awaddr_128}
    //   s_axi_awlen    = m_awlen
    //   s_axi_awsize   = m_awsize
    //   s_axi_awburst  = m_awburst
    //   s_axi_awlock   = 1'b0
    //   s_axi_awcache  = 4'b0011
    //   s_axi_awprot   = 3'b000
    //   s_axi_awqos    = 4'b0000
    //   s_axi_awvalid  = m_awvalid_128
    //   s_axi_awready  → m_awready_128
    //   s_axi_wdata    = m_wdata_128
    //   s_axi_wstrb    = m_wstrb_128
    //   s_axi_wlast    = m_wlast
    //   s_axi_wvalid   = m_wvalid_128
    //   s_axi_wready   → m_wready_128
    //   s_axi_bid      → (ignored)
    //   s_axi_bresp    → m_bresp_128
    //   s_axi_bvalid   → m_bvalid_128
    //   s_axi_bready   = m_bready_128
    //   s_axi_arid     = 4'b0
    //   s_axi_araddr   = {2'b0, m_araddr_128}
    //   (... similar for read address / data channels)
    //   init_calib_complete → init_calib_complete
    //   ddr3_*         → ddr3_* ports above
    //   sys_clk_i      = sys_clk_i
    //   clk_ref_i      = sys_clk_i   (same 200 MHz reference)
    //   sys_rst        = ~sys_rst_n
    // ─────────────────────────────────────────────────────────────────────────

    // Simulation stub: tie-off outputs so the module compiles without MIG IP
`ifndef SYNTHESIS
    assign m_awready_128   = 1'b1;
    assign m_wready_128    = 1'b1;
    assign m_bresp_128     = 2'b00;
    assign m_bvalid_128    = 1'b0;
    assign m_arready_128   = 1'b1;
    assign m_rdata_128     = 128'h0;
    assign m_rresp_128     = 2'b00;
    assign m_rlast         = 1'b1;
    assign m_rvalid_128    = 1'b0;
    assign init_calib_complete = 1'b1;
    assign ddr3_addr       = '0;
    assign ddr3_ba         = '0;
    assign ddr3_cas_n      = 1'b1;
    assign ddr3_ck_n       = 1'b1;
    assign ddr3_ck_p       = 1'b0;
    assign ddr3_cke        = '0;
    assign ddr3_cs_n       = '1;
    assign ddr3_odt        = '0;
    assign ddr3_ras_n      = 1'b1;
    assign ddr3_reset_n    = 1'b0;
    assign ddr3_we_n       = 1'b1;
`endif

endmodule
