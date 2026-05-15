`timescale 1ns/1ps
// Top-level UVM testbench for axi4_crossbar
// Execution model: flat coroutine structure for Verilator 5.020 --timing
//   - Monitors forked directly from initial block (not nested in class tasks)
//   - Driver tasks called directly by the test sequence (no sequencer coroutines)

import uvm_mini_pkg::*;
import crossbar_tb_pkg::*;

module crossbar_tb_top;

  logic clk, rst_n;
  initial clk = 0;
  always #5 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  // ─── Master interfaces ─────────────────────────────────────────────────────
  axi4_if mif0 (.clk(clk), .rst_n(rst_n));
  axi4_if mif1 (.clk(clk), .rst_n(rst_n));
  axi4_if mif2 (.clk(clk), .rst_n(rst_n));

  // ─── Slave wires ───────────────────────────────────────────────────────────
  logic [31:0] s0_awaddr, s1_awaddr, s2_awaddr;
  logic        s0_awvalid, s1_awvalid, s2_awvalid;
  logic        s0_awready, s1_awready, s2_awready;
  logic [31:0] s0_wdata,  s1_wdata,  s2_wdata;
  logic  [3:0] s0_wstrb,  s1_wstrb,  s2_wstrb;
  logic        s0_wvalid, s1_wvalid, s2_wvalid;
  logic        s0_wready, s1_wready, s2_wready;
  logic  [1:0] s0_bresp,  s1_bresp,  s2_bresp;
  logic        s0_bvalid, s1_bvalid, s2_bvalid;
  logic        s0_bready, s1_bready, s2_bready;
  logic [31:0] s0_araddr, s1_araddr, s2_araddr;
  logic        s0_arvalid, s1_arvalid, s2_arvalid;
  logic        s0_arready, s1_arready, s2_arready;
  logic [31:0] s0_rdata,  s1_rdata,  s2_rdata;
  logic  [1:0] s0_rresp,  s1_rresp,  s2_rresp;
  logic        s0_rvalid, s1_rvalid, s2_rvalid;
  logic        s0_rready, s1_rready, s2_rready;

  // ─── DUT ───────────────────────────────────────────────────────────────────
  axi4_crossbar dut (
    .clk(clk), .rst_n(rst_n),
    .m0_awaddr(mif0.awaddr), .m0_awvalid(mif0.awvalid), .m0_awready(mif0.awready),
    .m0_wdata(mif0.wdata),   .m0_wstrb(mif0.wstrb),
    .m0_wvalid(mif0.wvalid), .m0_wready(mif0.wready),
    .m0_bresp(mif0.bresp),   .m0_bvalid(mif0.bvalid),   .m0_bready(mif0.bready),
    .m0_araddr(mif0.araddr), .m0_arvalid(mif0.arvalid), .m0_arready(mif0.arready),
    .m0_rdata(mif0.rdata),   .m0_rresp(mif0.rresp),
    .m0_rvalid(mif0.rvalid), .m0_rready(mif0.rready),
    .m1_awaddr(mif1.awaddr), .m1_awvalid(mif1.awvalid), .m1_awready(mif1.awready),
    .m1_wdata(mif1.wdata),   .m1_wstrb(mif1.wstrb),
    .m1_wvalid(mif1.wvalid), .m1_wready(mif1.wready),
    .m1_bresp(mif1.bresp),   .m1_bvalid(mif1.bvalid),   .m1_bready(mif1.bready),
    .m1_araddr(mif1.araddr), .m1_arvalid(mif1.arvalid), .m1_arready(mif1.arready),
    .m1_rdata(mif1.rdata),   .m1_rresp(mif1.rresp),
    .m1_rvalid(mif1.rvalid), .m1_rready(mif1.rready),
    .m2_awaddr(mif2.awaddr), .m2_awvalid(mif2.awvalid), .m2_awready(mif2.awready),
    .m2_wdata(mif2.wdata),   .m2_wstrb(mif2.wstrb),
    .m2_wvalid(mif2.wvalid), .m2_wready(mif2.wready),
    .m2_bresp(mif2.bresp),   .m2_bvalid(mif2.bvalid),   .m2_bready(mif2.bready),
    .m2_araddr(mif2.araddr), .m2_arvalid(mif2.arvalid), .m2_arready(mif2.arready),
    .m2_rdata(mif2.rdata),   .m2_rresp(mif2.rresp),
    .m2_rvalid(mif2.rvalid), .m2_rready(mif2.rready),
    .s0_awaddr(s0_awaddr), .s0_awvalid(s0_awvalid), .s0_awready(s0_awready),
    .s0_wdata(s0_wdata),   .s0_wstrb(s0_wstrb),
    .s0_wvalid(s0_wvalid), .s0_wready(s0_wready),
    .s0_bresp(s0_bresp),   .s0_bvalid(s0_bvalid),   .s0_bready(s0_bready),
    .s0_araddr(s0_araddr), .s0_arvalid(s0_arvalid), .s0_arready(s0_arready),
    .s0_rdata(s0_rdata),   .s0_rresp(s0_rresp),
    .s0_rvalid(s0_rvalid), .s0_rready(s0_rready),
    .s1_awaddr(s1_awaddr), .s1_awvalid(s1_awvalid), .s1_awready(s1_awready),
    .s1_wdata(s1_wdata),   .s1_wstrb(s1_wstrb),
    .s1_wvalid(s1_wvalid), .s1_wready(s1_wready),
    .s1_bresp(s1_bresp),   .s1_bvalid(s1_bvalid),   .s1_bready(s1_bready),
    .s1_araddr(s1_araddr), .s1_arvalid(s1_arvalid), .s1_arready(s1_arready),
    .s1_rdata(s1_rdata),   .s1_rresp(s1_rresp),
    .s1_rvalid(s1_rvalid), .s1_rready(s1_rready),
    .s2_awaddr(s2_awaddr), .s2_awvalid(s2_awvalid), .s2_awready(s2_awready),
    .s2_wdata(s2_wdata),   .s2_wstrb(s2_wstrb),
    .s2_wvalid(s2_wvalid), .s2_wready(s2_wready),
    .s2_bresp(s2_bresp),   .s2_bvalid(s2_bvalid),   .s2_bready(s2_bready),
    .s2_araddr(s2_araddr), .s2_arvalid(s2_arvalid), .s2_arready(s2_arready),
    .s2_rdata(s2_rdata),   .s2_rresp(s2_rresp),
    .s2_rvalid(s2_rvalid), .s2_rready(s2_rready)
  );

  // ─── Slaves ────────────────────────────────────────────────────────────────
  axi_sram #(.DEPTH(16384)) s0 (.clk(clk), .rst_n(rst_n),
    .s_awaddr(s0_awaddr), .s_awvalid(s0_awvalid), .s_awready(s0_awready),
    .s_wdata(s0_wdata), .s_wstrb(s0_wstrb), .s_wvalid(s0_wvalid), .s_wready(s0_wready),
    .s_bresp(s0_bresp), .s_bvalid(s0_bvalid), .s_bready(s0_bready),
    .s_araddr(s0_araddr), .s_arvalid(s0_arvalid), .s_arready(s0_arready),
    .s_rdata(s0_rdata), .s_rresp(s0_rresp), .s_rvalid(s0_rvalid), .s_rready(s0_rready));

  axi_sram #(.DEPTH(16384)) s1 (.clk(clk), .rst_n(rst_n),
    .s_awaddr(s1_awaddr), .s_awvalid(s1_awvalid), .s_awready(s1_awready),
    .s_wdata(s1_wdata), .s_wstrb(s1_wstrb), .s_wvalid(s1_wvalid), .s_wready(s1_wready),
    .s_bresp(s1_bresp), .s_bvalid(s1_bvalid), .s_bready(s1_bready),
    .s_araddr(s1_araddr), .s_arvalid(s1_arvalid), .s_arready(s1_arready),
    .s_rdata(s1_rdata), .s_rresp(s1_rresp), .s_rvalid(s1_rvalid), .s_rready(s1_rready));

  axi_sram #(.DEPTH(64)) s2 (.clk(clk), .rst_n(rst_n),
    .s_awaddr(s2_awaddr), .s_awvalid(s2_awvalid), .s_awready(s2_awready),
    .s_wdata(s2_wdata), .s_wstrb(s2_wstrb), .s_wvalid(s2_wvalid), .s_wready(s2_wready),
    .s_bresp(s2_bresp), .s_bvalid(s2_bvalid), .s_bready(s2_bready),
    .s_araddr(s2_araddr), .s_arvalid(s2_arvalid), .s_arready(s2_arready),
    .s_rdata(s2_rdata), .s_rresp(s2_rresp), .s_rvalid(s2_rvalid), .s_rready(s2_rready));

  // ─── UVM environment ───────────────────────────────────────────────────────
  crossbar_env env;
  uvm_phase    ph;

  // ─── Main test sequence ────────────────────────────────────────────────────
  initial begin
    logic [31:0] rdata;
    logic  [1:0] resp;

    ph  = new("run");
    env = new("env", null);
    env.m_vif0 = mif0; env.m_vif1 = mif1; env.m_vif2 = mif2;
    env.build_phase(ph);

    // Init all driver signals low
    env.agent[0].drv.init_signals();
    env.agent[1].drv.init_signals();
    env.agent[2].drv.init_signals();

    // Spawn monitors as top-level coroutines (flat, not nested inside class tasks)
    fork
      env.agent[0].mon.run_monitor();
      env.agent[1].mon.run_monitor();
      env.agent[2].mon.run_monitor();
    join_none

    // Wait for reset
    while (!rst_n) @(posedge clk);
    @(posedge clk);

    // ── TEST 1: Routing — all 9 master→slave pairs ────────────────────────────
    $display("\n=== TEST 1: Routing (9 master->slave pairs) ===");

    env.agent[0].drv.axi_write(resp, 32'h0000_0010, 32'hDEAD_0001); @(posedge clk);
    env.agent[0].drv.axi_read (rdata, resp, 32'h0000_0010);         @(posedge clk);
    env.agent[0].drv.axi_write(resp, 32'h1000_0008, 32'hDEAD_0002); @(posedge clk);
    env.agent[0].drv.axi_read (rdata, resp, 32'h1000_0008);         @(posedge clk);
    env.agent[0].drv.axi_write(resp, 32'h5000_0004, 32'hDEAD_0003); @(posedge clk);
    env.agent[0].drv.axi_read (rdata, resp, 32'h5000_0004);         @(posedge clk);

    env.agent[1].drv.axi_write(resp, 32'h0000_0020, 32'hBEEF_0004); @(posedge clk);
    env.agent[1].drv.axi_read (rdata, resp, 32'h0000_0020);         @(posedge clk);
    env.agent[1].drv.axi_write(resp, 32'h1000_0010, 32'hBEEF_0005); @(posedge clk);
    env.agent[1].drv.axi_read (rdata, resp, 32'h1000_0010);         @(posedge clk);
    env.agent[1].drv.axi_write(resp, 32'h5000_0008, 32'hBEEF_0006); @(posedge clk);
    env.agent[1].drv.axi_read (rdata, resp, 32'h5000_0008);         @(posedge clk);

    env.agent[2].drv.axi_write(resp, 32'h0000_0030, 32'hCAFE_0007); @(posedge clk);
    env.agent[2].drv.axi_read (rdata, resp, 32'h0000_0030);         @(posedge clk);
    env.agent[2].drv.axi_write(resp, 32'h1000_0018, 32'hCAFE_0008); @(posedge clk);
    env.agent[2].drv.axi_read (rdata, resp, 32'h1000_0018);         @(posedge clk);
    env.agent[2].drv.axi_write(resp, 32'h5000_000C, 32'hCAFE_0009); @(posedge clk);
    env.agent[2].drv.axi_read (rdata, resp, 32'h5000_000C);         @(posedge clk);

    // Allow monitors to drain
    repeat (20) @(posedge clk);
    env.drain();

    // ── TEST 2: Arbitration — 3 masters targeting Slave 0 simultaneously ──────
    $display("\n=== TEST 2: Arbitration (3 masters -> Slave 0) ===");
    // Fork all three writes simultaneously
    fork
      env.agent[0].drv.axi_write(resp, 32'h0000_0100, 32'hAABB_CC00);
      env.agent[1].drv.axi_write(resp, 32'h0000_0104, 32'hAABB_CC01);
      env.agent[2].drv.axi_write(resp, 32'h0000_0108, 32'hAABB_CC02);
    join
    repeat (10) @(posedge clk);
    // Read each back sequentially (crossbar arbitrates)
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_0100); @(posedge clk);
    env.agent[1].drv.axi_read(rdata, resp, 32'h0000_0104); @(posedge clk);
    env.agent[2].drv.axi_read(rdata, resp, 32'h0000_0108); @(posedge clk);

    repeat (20) @(posedge clk);
    env.drain();

    // ── TEST 3: No-contention — M0→S0, M1→S1, M2→S2 simultaneously ───────────
    $display("\n=== TEST 3: No-contention (M0->S0, M1->S1, M2->S2) ===");
    fork
      env.agent[0].drv.axi_write(resp, 32'h0000_0200, 32'hFACE_0001);
      env.agent[1].drv.axi_write(resp, 32'h1000_0200, 32'hFACE_0002);
      env.agent[2].drv.axi_write(resp, 32'h5000_0200, 32'hFACE_0003);
    join
    repeat (10) @(posedge clk);
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_0200); @(posedge clk);
    env.agent[1].drv.axi_read(rdata, resp, 32'h1000_0200); @(posedge clk);
    env.agent[2].drv.axi_read(rdata, resp, 32'h5000_0200); @(posedge clk);

    repeat (20) @(posedge clk);
    env.drain();

    // ── TEST 4: Back-to-back from single master (M0 → S0, 4 writes then 4 reads)
    $display("\n=== TEST 4: Back-to-back single master (M0->S0, 4 W + 4 R) ===");
    env.agent[0].drv.axi_write(resp, 32'h0000_0300, 32'h0001_0001); @(posedge clk);
    env.agent[0].drv.axi_write(resp, 32'h0000_0304, 32'h0002_0002); @(posedge clk);
    env.agent[0].drv.axi_write(resp, 32'h0000_0308, 32'h0003_0003); @(posedge clk);
    env.agent[0].drv.axi_write(resp, 32'h0000_030C, 32'h0004_0004); @(posedge clk);
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_0300); @(posedge clk);
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_0304); @(posedge clk);
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_0308); @(posedge clk);
    env.agent[0].drv.axi_read(rdata, resp, 32'h0000_030C); @(posedge clk);

    repeat (20) @(posedge clk);
    env.drain();

    // ── Report ────────────────────────────────────────────────────────────────
    env.report_phase(ph);

    if (uvm_mini_pkg::g_error_count == 0)
      $display("\n*** ALL TESTS PASSED (0 errors) ***");
    else
      $display("\n*** %0d ERRORS DETECTED ***", uvm_mini_pkg::g_error_count);

    $finish;
  end

  initial begin
    #500_000;
    $display("[TIMEOUT] Exceeded 500us");
    $finish;
  end

endmodule
