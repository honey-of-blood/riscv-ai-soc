`timescale 1ns/1ps
// Top-level UVM testbench for accel_top (4×4 systolic-array accelerator).
// Flat coroutine structure for Verilator 5.020 --timing.

import uvm_mini_pkg::*;
import accel_tb_pkg::*;

module accel_tb_top;

  logic clk, rst_n;
  initial clk = 0;
  always #5 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  accel_if aif (.clk(clk), .rst_n(rst_n));

  accel_top dut (
    .clk      (clk),
    .rst_n    (rst_n),
    .s_awaddr (aif.awaddr),  .s_awvalid(aif.awvalid), .s_awready(aif.awready),
    .s_wdata  (aif.wdata),   .s_wstrb  (aif.wstrb),
    .s_wvalid (aif.wvalid),  .s_wready (aif.wready),
    .s_bresp  (aif.bresp),   .s_bvalid (aif.bvalid),  .s_bready (aif.bready),
    .s_araddr (aif.araddr),  .s_arvalid(aif.arvalid), .s_arready(aif.arready),
    .s_rdata  (aif.rdata),   .s_rresp  (aif.rresp),
    .s_rvalid (aif.rvalid),  .s_rready (aif.rready)
  );

  accel_env env;
  uvm_phase ph;

  // ── Helper: run one matmul and verify all 16 outputs ────────────────────────
  task run_matmul(
    input  logic [31:0] w_rows[4],
    input  logic [31:0] a_rows[4],
    input  string       tag
  );
    logic [31:0] y[4][4];
    env.drv.load_weights(w_rows);
    env.drv.load_activations(a_rows);
    env.drv.start_and_wait();
    env.drv.read_outputs(y);
    env.drain();
    env.cov.mark(tag);
  endtask

  // ── Helper: AXI read with inline result check ─────────────────────────────
  task automatic check_reg(
    input logic [31:0] addr,
    input logic [31:0] expected,
    input string       tag
  );
    logic [31:0] got; logic [1:0] r;
    env.drv.axi_read(got, r, addr);
    if (got === expected)
      $display("[CHK] %s PASS got=0x%08X", tag, got);
    else begin
      uvm_mini_pkg::g_error_count++;
      $display("[CHK] %s FAIL exp=0x%08X got=0x%08X", tag, expected, got);
    end
  endtask

  initial begin
    logic [31:0] w[4], a[4], y[4][4];
    logic [1:0]  resp;

    ph  = new("run");
    env = new("env", null);
    env.m_vif = aif;
    env.build_phase(ph);
    env.drv.init_signals();

    fork
      env.mon.run_monitor();
    join_none

    while (!rst_n) @(posedge clk);
    @(posedge clk);

    // ── TEST 1: Identity weight matrix  Y = A × I = A ─────────────────────────
    $display("\n=== TEST 1: Identity weight matrix (Y = A) ===");
    w[0] = 32'h00_00_00_01;  // W[0] = {0,0,0,1}
    w[1] = 32'h00_00_01_00;  // W[1] = {0,0,1,0}
    w[2] = 32'h00_01_00_00;  // W[2] = {0,1,0,0}
    w[3] = 32'h01_00_00_00;  // W[3] = {1,0,0,0}
    a[0] = 32'h04_03_02_01;  // A[0] = {4,3,2,1}
    a[1] = 32'h08_07_06_05;
    a[2] = 32'h0C_0B_0A_09;
    a[3] = 32'h10_0F_0E_0D;
    run_matmul(w, a, "identity_weights");

    // ── TEST 2: Full 4×4 matmul ────────────────────────────────────────────────
    $display("\n=== TEST 2: Full 4×4 matmul (A=[1..16], W=[1..16]) ===");
    // W same as A (both = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]])
    w[0] = 32'h04_03_02_01;
    w[1] = 32'h08_07_06_05;
    w[2] = 32'h0C_0B_0A_09;
    w[3] = 32'h10_0F_0E_0D;
    a[0] = 32'h04_03_02_01;
    a[1] = 32'h08_07_06_05;
    a[2] = 32'h0C_0B_0A_09;
    a[3] = 32'h10_0F_0E_0D;
    run_matmul(w, a, "full_matmul");

    // ── TEST 3: Signed (negative) weights — W = -I ─────────────────────────────
    $display("\n=== TEST 3: Signed negative weights (W = -I, A = I) ===");
    // W = -identity: W[k][n] = -1 if k==n, else 0  (-1 = 8'hFF)
    w[0] = 32'h00_00_00_FF;
    w[1] = 32'h00_00_FF_00;
    w[2] = 32'h00_FF_00_00;
    w[3] = 32'hFF_00_00_00;
    // A = identity
    a[0] = 32'h00_00_00_01;
    a[1] = 32'h00_00_01_00;
    a[2] = 32'h00_01_00_00;
    a[3] = 32'h01_00_00_00;
    run_matmul(w, a, "signed_weights");

    // ── TEST 4: Zero activations — Y = 0 ──────────────────────────────────────
    $display("\n=== TEST 4: Zero activations (Y = 0) ===");
    w[0] = 32'h04_03_02_01;  // arbitrary weights
    w[1] = 32'h08_07_06_05;
    w[2] = 32'h0C_0B_0A_09;
    w[3] = 32'h10_0F_0E_0D;
    a[0] = 32'h0; a[1] = 32'h0; a[2] = 32'h0; a[3] = 32'h0;
    run_matmul(w, a, "zero_activations");

    // ── TEST 5: Back-to-back — reuse weights from TEST 1, new activations ──────
    $display("\n=== TEST 5: Back-to-back (identity weights, two consecutive runs) ===");
    w[0] = 32'h00_00_00_01; w[1] = 32'h00_00_01_00;
    w[2] = 32'h00_01_00_00; w[3] = 32'h01_00_00_00;
    // First run
    a[0] = 32'h04_03_02_01; a[1] = 32'h08_07_06_05;
    a[2] = 32'h0C_0B_0A_09; a[3] = 32'h10_0F_0E_0D;
    env.drv.load_weights(w);
    env.drv.load_activations(a);
    env.drv.start_and_wait();
    env.drv.read_outputs(y);
    env.drain();
    // Second run immediately (different activations, same weights)
    a[0] = 32'h08_07_06_05; a[1] = 32'h0C_0B_0A_09;
    a[2] = 32'h10_0F_0E_0D; a[3] = 32'h14_13_12_11;
    env.drv.load_activations(a);
    env.drv.start_and_wait();
    env.drv.read_outputs(y);
    env.drain();
    env.cov.mark("back_to_back");

    // ── TEST 6: MMIO register readback ────────────────────────────────────────
    $display("\n=== TEST 6: MMIO register readback (W, A, CTRL) ===");
    // Write distinct W_row0 and A_row0 patterns; read back and verify.
    begin
      logic [1:0] r;
      env.drv.axi_write(r, BASE+W_ROW0,     32'hDE_AD_BE_EF);  @(posedge clk);
      env.drv.axi_write(r, BASE+W_ROW0+'h4, 32'hCA_FE_BA_BE);  @(posedge clk);
      env.drv.axi_write(r, BASE+A_ROW0,     32'h12_34_56_78);  @(posedge clk);
      env.drv.axi_write(r, BASE+A_ROW0+'h4, 32'hAA_BB_CC_DD);  @(posedge clk);
      check_reg(BASE+W_ROW0,       32'hDE_AD_BE_EF, "W_row0 readback");
      check_reg(BASE+W_ROW0+'h4,   32'hCA_FE_BA_BE, "W_row1 readback");
      check_reg(BASE+A_ROW0,       32'h12_34_56_78, "A_row0 readback");
      check_reg(BASE+A_ROW0+'h4,   32'hAA_BB_CC_DD, "A_row1 readback");
      // Drain monitor — W/A reads not verified by scoreboard (non-Y addr)
      env.drain();
    end

    // ── TEST 7: Max positive INT8 × max positive (127 × 127) ─────────────────
    $display("\n=== TEST 7: Max positive INT8 (A=W=127, Y=4*127*127=64516) ===");
    // Each element = 127; Y[m][n] = sum_k 127*127 = 4*16129 = 64516
    w[0] = 32'h7F_7F_7F_7F; w[1] = 32'h7F_7F_7F_7F;
    w[2] = 32'h7F_7F_7F_7F; w[3] = 32'h7F_7F_7F_7F;
    a[0] = 32'h7F_7F_7F_7F; a[1] = 32'h7F_7F_7F_7F;
    a[2] = 32'h7F_7F_7F_7F; a[3] = 32'h7F_7F_7F_7F;
    run_matmul(w, a, "max_positive");

    // ── TEST 8: Max negative INT8 × max negative (-128 × -128) ───────────────
    $display("\n=== TEST 8: Max negative INT8 (A=W=-128, Y=4*(-128)*(-128)=65536) ===");
    // 0x80 = -128 signed; (-128)*(-128)=16384; 4*16384=65536
    w[0] = 32'h80_80_80_80; w[1] = 32'h80_80_80_80;
    w[2] = 32'h80_80_80_80; w[3] = 32'h80_80_80_80;
    a[0] = 32'h80_80_80_80; a[1] = 32'h80_80_80_80;
    a[2] = 32'h80_80_80_80; a[3] = 32'h80_80_80_80;
    run_matmul(w, a, "max_negative");

    // ── TEST 9: Mixed sign (127 × -128) — negative product ───────────────────
    $display("\n=== TEST 9: Mixed sign (A=127, W=-128, Y=4*127*(-128)=-65024) ===");
    // 127 * (-128) = -16256; 4 * -16256 = -65024 = 32'hFFFF0220
    w[0] = 32'h80_80_80_80; w[1] = 32'h80_80_80_80;
    w[2] = 32'h80_80_80_80; w[3] = 32'h80_80_80_80;
    a[0] = 32'h7F_7F_7F_7F; a[1] = 32'h7F_7F_7F_7F;
    a[2] = 32'h7F_7F_7F_7F; a[3] = 32'h7F_7F_7F_7F;
    run_matmul(w, a, "mixed_sign");

    // ── TEST 10: CTRL done-flag lifecycle ─────────────────────────────────────
    $display("\n=== TEST 10: CTRL done-flag lifecycle (verify done=1 after computation) ===");
    // Use identity weights and a known activation; verify CTRL[1]=1 after done.
    w[0] = 32'h00_00_00_01; w[1] = 32'h00_00_01_00;
    w[2] = 32'h00_01_00_00; w[3] = 32'h01_00_00_00;
    a[0] = 32'h05_04_03_02; a[1] = 32'h09_08_07_06;
    a[2] = 32'h0D_0C_0B_0A; a[3] = 32'h11_10_0F_0E;
    env.drv.load_weights(w);
    env.drv.load_activations(a);
    env.drv.start_and_wait();
    // After start_and_wait(): done=1, start=1 → CTRL should be 0x00000003
    check_reg(BASE+CTRL, 32'h00000003, "CTRL done=1 after computation");
    env.drv.read_outputs(y);
    env.drain();
    env.cov.mark("ctrl_lifecycle");

    // ── Report ─────────────────────────────────────────────────────────────────
    repeat (5) @(posedge clk);
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
