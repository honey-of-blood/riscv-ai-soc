`timescale 1ns/1ps
// Integration test: AXI4 crossbar (phase3) + accel_top (phase4) + axi_sram × 2
// Verifies that accel_top routes correctly through the crossbar as slave 2
// and that SRAM (slave 0) still works alongside it.

module crossbar_accel_tb;

  // ── Clock / reset ─────────────────────────────────────────────────────────
  logic clk, rst_n;
  initial clk = 0;
  always #5 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  // ── Error counter ─────────────────────────────────────────────────────────
  int error_count = 0;

  // ── Crossbar master 0 signals (CPU / test driver) ─────────────────────────
  logic [31:0] m0_awaddr;  logic m0_awvalid; logic m0_awready;
  logic [31:0] m0_wdata;   logic [3:0] m0_wstrb; logic m0_wvalid; logic m0_wready;
  logic [1:0]  m0_bresp;   logic m0_bvalid;  logic m0_bready;
  logic [31:0] m0_araddr;  logic m0_arvalid; logic m0_arready;
  logic [31:0] m0_rdata;   logic [1:0] m0_rresp; logic m0_rvalid; logic m0_rready;

  // ── Masters 1 & 2 tied off ────────────────────────────────────────────────
  logic [31:0] m1_awaddr=0, m1_wdata=0, m1_araddr=0;
  logic [3:0]  m1_wstrb=0;
  logic        m1_awvalid=0, m1_wvalid=0, m1_bready=0, m1_arvalid=0, m1_rready=0;
  logic [31:0] m1_rdata; logic [1:0] m1_rresp, m1_bresp;
  logic        m1_awready, m1_wready, m1_bvalid, m1_arready, m1_rvalid;

  logic [31:0] m2_awaddr=0, m2_wdata=0, m2_araddr=0;
  logic [3:0]  m2_wstrb=0;
  logic        m2_awvalid=0, m2_wvalid=0, m2_bready=0, m2_arvalid=0, m2_rready=0;
  logic [31:0] m2_rdata; logic [1:0] m2_rresp, m2_bresp;
  logic        m2_awready, m2_wready, m2_bvalid, m2_arready, m2_rvalid;

  // ── Crossbar slave wires ──────────────────────────────────────────────────
  // Slave 0 → SRAM 0
  logic [31:0] s0_awaddr, s0_wdata, s0_araddr, s0_rdata;
  logic [3:0]  s0_wstrb;
  logic [1:0]  s0_bresp, s0_rresp;
  logic        s0_awvalid, s0_awready, s0_wvalid, s0_wready;
  logic        s0_bvalid, s0_bready, s0_arvalid, s0_arready, s0_rvalid, s0_rready;

  // Slave 1 → SRAM 1 (APB bridge placeholder, use another SRAM)
  logic [31:0] s1_awaddr, s1_wdata, s1_araddr, s1_rdata;
  logic [3:0]  s1_wstrb;
  logic [1:0]  s1_bresp, s1_rresp;
  logic        s1_awvalid, s1_awready, s1_wvalid, s1_wready;
  logic        s1_bvalid, s1_bready, s1_arvalid, s1_arready, s1_rvalid, s1_rready;

  // Slave 2 → accel_top
  logic [31:0] s2_awaddr, s2_wdata, s2_araddr, s2_rdata;
  logic [3:0]  s2_wstrb;
  logic [1:0]  s2_bresp, s2_rresp;
  logic        s2_awvalid, s2_awready, s2_wvalid, s2_wready;
  logic        s2_bvalid, s2_bready, s2_arvalid, s2_arready, s2_rvalid, s2_rready;

  // ── DUT: AXI4 crossbar ────────────────────────────────────────────────────
  axi4_crossbar xbar (
    .clk(clk), .rst_n(rst_n),
    // Master 0
    .m0_awaddr(m0_awaddr), .m0_awvalid(m0_awvalid), .m0_awready(m0_awready),
    .m0_wdata(m0_wdata),   .m0_wstrb(m0_wstrb),     .m0_wvalid(m0_wvalid),  .m0_wready(m0_wready),
    .m0_bresp(m0_bresp),   .m0_bvalid(m0_bvalid),   .m0_bready(m0_bready),
    .m0_araddr(m0_araddr), .m0_arvalid(m0_arvalid), .m0_arready(m0_arready),
    .m0_rdata(m0_rdata),   .m0_rresp(m0_rresp),     .m0_rvalid(m0_rvalid),  .m0_rready(m0_rready),
    // Master 1 (tied off)
    .m1_awaddr(m1_awaddr), .m1_awvalid(m1_awvalid), .m1_awready(m1_awready),
    .m1_wdata(m1_wdata),   .m1_wstrb(m1_wstrb),     .m1_wvalid(m1_wvalid),  .m1_wready(m1_wready),
    .m1_bresp(m1_bresp),   .m1_bvalid(m1_bvalid),   .m1_bready(m1_bready),
    .m1_araddr(m1_araddr), .m1_arvalid(m1_arvalid), .m1_arready(m1_arready),
    .m1_rdata(m1_rdata),   .m1_rresp(m1_rresp),     .m1_rvalid(m1_rvalid),  .m1_rready(m1_rready),
    // Master 2 (tied off)
    .m2_awaddr(m2_awaddr), .m2_awvalid(m2_awvalid), .m2_awready(m2_awready),
    .m2_wdata(m2_wdata),   .m2_wstrb(m2_wstrb),     .m2_wvalid(m2_wvalid),  .m2_wready(m2_wready),
    .m2_bresp(m2_bresp),   .m2_bvalid(m2_bvalid),   .m2_bready(m2_bready),
    .m2_araddr(m2_araddr), .m2_arvalid(m2_arvalid), .m2_arready(m2_arready),
    .m2_rdata(m2_rdata),   .m2_rresp(m2_rresp),     .m2_rvalid(m2_rvalid),  .m2_rready(m2_rready),
    // Slave 0
    .s0_awaddr(s0_awaddr), .s0_awvalid(s0_awvalid), .s0_awready(s0_awready),
    .s0_wdata(s0_wdata),   .s0_wstrb(s0_wstrb),     .s0_wvalid(s0_wvalid),  .s0_wready(s0_wready),
    .s0_bresp(s0_bresp),   .s0_bvalid(s0_bvalid),   .s0_bready(s0_bready),
    .s0_araddr(s0_araddr), .s0_arvalid(s0_arvalid), .s0_arready(s0_arready),
    .s0_rdata(s0_rdata),   .s0_rresp(s0_rresp),     .s0_rvalid(s0_rvalid),  .s0_rready(s0_rready),
    // Slave 1
    .s1_awaddr(s1_awaddr), .s1_awvalid(s1_awvalid), .s1_awready(s1_awready),
    .s1_wdata(s1_wdata),   .s1_wstrb(s1_wstrb),     .s1_wvalid(s1_wvalid),  .s1_wready(s1_wready),
    .s1_bresp(s1_bresp),   .s1_bvalid(s1_bvalid),   .s1_bready(s1_bready),
    .s1_araddr(s1_araddr), .s1_arvalid(s1_arvalid), .s1_arready(s1_arready),
    .s1_rdata(s1_rdata),   .s1_rresp(s1_rresp),     .s1_rvalid(s1_rvalid),  .s1_rready(s1_rready),
    // Slave 2
    .s2_awaddr(s2_awaddr), .s2_awvalid(s2_awvalid), .s2_awready(s2_awready),
    .s2_wdata(s2_wdata),   .s2_wstrb(s2_wstrb),     .s2_wvalid(s2_wvalid),  .s2_wready(s2_wready),
    .s2_bresp(s2_bresp),   .s2_bvalid(s2_bvalid),   .s2_bready(s2_bready),
    .s2_araddr(s2_araddr), .s2_arvalid(s2_arvalid), .s2_arready(s2_arready),
    .s2_rdata(s2_rdata),   .s2_rresp(s2_rresp),     .s2_rvalid(s2_rvalid),  .s2_rready(s2_rready)
  );

  // ── Slave 0: SRAM (0x0000_xxxx) ──────────────────────────────────────────
  axi_sram sram0 (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s0_awaddr), .s_awvalid(s0_awvalid), .s_awready(s0_awready),
    .s_wdata(s0_wdata),   .s_wstrb(s0_wstrb),     .s_wvalid(s0_wvalid),  .s_wready(s0_wready),
    .s_bresp(s0_bresp),   .s_bvalid(s0_bvalid),   .s_bready(s0_bready),
    .s_araddr(s0_araddr), .s_arvalid(s0_arvalid), .s_arready(s0_arready),
    .s_rdata(s0_rdata),   .s_rresp(s0_rresp),     .s_rvalid(s0_rvalid),  .s_rready(s0_rready)
  );

  // ── Slave 1: second SRAM (0x1000_xxxx) ───────────────────────────────────
  axi_sram sram1 (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s1_awaddr), .s_awvalid(s1_awvalid), .s_awready(s1_awready),
    .s_wdata(s1_wdata),   .s_wstrb(s1_wstrb),     .s_wvalid(s1_wvalid),  .s_wready(s1_wready),
    .s_bresp(s1_bresp),   .s_bvalid(s1_bvalid),   .s_bready(s1_bready),
    .s_araddr(s1_araddr), .s_arvalid(s1_arvalid), .s_arready(s1_arready),
    .s_rdata(s1_rdata),   .s_rresp(s1_rresp),     .s_rvalid(s1_rvalid),  .s_rready(s1_rready)
  );

  // ── Slave 2: accel_top (0x5000_xxxx) ─────────────────────────────────────
  accel_top accel (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s2_awaddr), .s_awvalid(s2_awvalid), .s_awready(s2_awready),
    .s_wdata(s2_wdata),   .s_wstrb(s2_wstrb),     .s_wvalid(s2_wvalid),  .s_wready(s2_wready),
    .s_bresp(s2_bresp),   .s_bvalid(s2_bvalid),   .s_bready(s2_bready),
    .s_araddr(s2_araddr), .s_arvalid(s2_arvalid), .s_arready(s2_arready),
    .s_rdata(s2_rdata),   .s_rresp(s2_rresp),     .s_rvalid(s2_rvalid),  .s_rready(s2_rready)
  );

  // ── AXI4-Lite driver tasks (operate on m0_* signals) ─────────────────────

  // The crossbar arbiter is registered: wr_busy/rd_busy goes high ONE cycle after
  // the master presents AWVALID/ARVALID.  The slave only sees routed signals when
  // wr_busy/rd_busy=1, so the master must hold valid signals for one extra clock
  // after the crossbar confirms the grant (awready/arready going high).
  task automatic axi_write(
    input  logic [31:0] addr,
    input  logic [31:0] data,
    input  logic  [3:0] strb = 4'hF
  );
    @(posedge clk);
    m0_awaddr = addr; m0_awvalid = 1;
    m0_wdata  = data; m0_wstrb   = strb; m0_wvalid = 1;
    m0_bready = 1;
    @(posedge clk);
    while (!m0_awready) @(posedge clk);
    // Grant is now visible; hold valid one more cycle so slave latches.
    @(posedge clk);
    m0_awvalid = 0;
    m0_wvalid  = 0;
    while (!m0_bvalid)  @(posedge clk);
    @(posedge clk);
    m0_bready = 0;
  endtask

  task automatic axi_read(
    input  logic [31:0] addr,
    output logic [31:0] data
  );
    @(posedge clk);
    m0_araddr = addr; m0_arvalid = 1; m0_rready = 1;
    @(posedge clk);
    while (!m0_arready) @(posedge clk);
    // Grant is now visible; hold arvalid one more cycle so slave latches.
    @(posedge clk);
    m0_arvalid = 0;
    while (!m0_rvalid)  @(posedge clk);
    data = m0_rdata;
    @(posedge clk);
    m0_rready = 0;
  endtask

  task automatic check(
    input logic [31:0] got,
    input logic [31:0] exp,
    input string       tag
  );
    if (got === exp)
      $display("[PASS] %s  got=0x%08X", tag, got);
    else begin
      $display("[FAIL] %s  exp=0x%08X  got=0x%08X", tag, exp, got);
      error_count++;
    end
  endtask

  // ── Address constants ─────────────────────────────────────────────────────
  localparam logic [31:0] ACCEL_BASE = 32'h5000_0000;
  localparam logic [31:0] SRAM_BASE  = 32'h0000_0000;

  localparam int CTRL   = 'h00;
  localparam int W_ROW0 = 'h04;
  localparam int A_ROW0 = 'h14;
  localparam int Y_BASE = 'h24;

  // ── Test stimulus ─────────────────────────────────────────────────────────
  initial begin
    logic [31:0] rd;
    // initialise master 0 outputs
    m0_awaddr=0; m0_awvalid=0; m0_wdata=0; m0_wstrb=0; m0_wvalid=0;
    m0_bready=0; m0_araddr=0; m0_arvalid=0; m0_rready=0;

    while (!rst_n) @(posedge clk);
    @(posedge clk);

    // ── TEST 1: SRAM sanity (write then read through crossbar → slave 0) ─────
    $display("\n=== TEST 1: SRAM sanity (0x0000_0004 = 0xDEADBEEF) ===");
    axi_write(SRAM_BASE + 32'h4, 32'hDEAD_BEEF);
    axi_read (SRAM_BASE + 32'h4, rd);
    check(rd, 32'hDEAD_BEEF, "SRAM word write/read");

    axi_write(SRAM_BASE + 32'h8, 32'hCAFE_BABE);
    axi_read (SRAM_BASE + 32'h8, rd);
    check(rd, 32'hCAFE_BABE, "SRAM word 2 write/read");

    // ── TEST 2: Identity-weight matmul through crossbar ───────────────────
    $display("\n=== TEST 2: Identity matmul through crossbar (Y = A) ===");
    // W = identity packed per row: {0,0,0,1}, {0,0,1,0}, {0,1,0,0}, {1,0,0,0}
    axi_write(ACCEL_BASE + W_ROW0,       32'h00_00_00_01);
    axi_write(ACCEL_BASE + W_ROW0 + 'h4, 32'h00_00_01_00);
    axi_write(ACCEL_BASE + W_ROW0 + 'h8, 32'h00_01_00_00);
    axi_write(ACCEL_BASE + W_ROW0 + 'hC, 32'h01_00_00_00);
    // A rows: [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
    axi_write(ACCEL_BASE + A_ROW0,       32'h04_03_02_01);
    axi_write(ACCEL_BASE + A_ROW0 + 'h4, 32'h08_07_06_05);
    axi_write(ACCEL_BASE + A_ROW0 + 'h8, 32'h0C_0B_0A_09);
    axi_write(ACCEL_BASE + A_ROW0 + 'hC, 32'h10_0F_0E_0D);
    // Start
    axi_write(ACCEL_BASE + CTRL, 32'h1);
    // Poll done
    do begin
      axi_read(ACCEL_BASE + CTRL, rd);
    end while (!rd[1]);
    $display("[INT] CTRL=0x%08X (done=1)", rd);
    // Read Y[0][0..3] = A row 0 = {1,2,3,4}
    axi_read(ACCEL_BASE + Y_BASE + 0*4,  rd); check(rd, 32'd1, "Y[0][0]=1");
    axi_read(ACCEL_BASE + Y_BASE + 1*4,  rd); check(rd, 32'd2, "Y[0][1]=2");
    axi_read(ACCEL_BASE + Y_BASE + 2*4,  rd); check(rd, 32'd3, "Y[0][2]=3");
    axi_read(ACCEL_BASE + Y_BASE + 3*4,  rd); check(rd, 32'd4, "Y[0][3]=4");
    // Y[1][0..3] = {5,6,7,8}
    axi_read(ACCEL_BASE + Y_BASE + 4*4,  rd); check(rd, 32'd5,  "Y[1][0]=5");
    axi_read(ACCEL_BASE + Y_BASE + 5*4,  rd); check(rd, 32'd6,  "Y[1][1]=6");
    axi_read(ACCEL_BASE + Y_BASE + 6*4,  rd); check(rd, 32'd7,  "Y[1][2]=7");
    axi_read(ACCEL_BASE + Y_BASE + 7*4,  rd); check(rd, 32'd8,  "Y[1][3]=8");
    // Y[2][0..3] = {9,10,11,12}
    axi_read(ACCEL_BASE + Y_BASE + 8*4,  rd); check(rd, 32'd9,  "Y[2][0]=9");
    axi_read(ACCEL_BASE + Y_BASE + 9*4,  rd); check(rd, 32'd10, "Y[2][1]=10");
    axi_read(ACCEL_BASE + Y_BASE + 10*4, rd); check(rd, 32'd11, "Y[2][2]=11");
    axi_read(ACCEL_BASE + Y_BASE + 11*4, rd); check(rd, 32'd12, "Y[2][3]=12");
    // Y[3][0..3] = {13,14,15,16}
    axi_read(ACCEL_BASE + Y_BASE + 12*4, rd); check(rd, 32'd13, "Y[3][0]=13");
    axi_read(ACCEL_BASE + Y_BASE + 13*4, rd); check(rd, 32'd14, "Y[3][1]=14");
    axi_read(ACCEL_BASE + Y_BASE + 14*4, rd); check(rd, 32'd15, "Y[3][2]=15");
    axi_read(ACCEL_BASE + Y_BASE + 15*4, rd); check(rd, 32'd16, "Y[3][3]=16");

    // ── TEST 3: Full matmul through crossbar — A = W = [[1..4],[5..8],..] ───
    $display("\n=== TEST 3: Full matmul through crossbar (A=W=[1..16]) ===");
    axi_write(ACCEL_BASE + W_ROW0,       32'h04_03_02_01);
    axi_write(ACCEL_BASE + W_ROW0 + 'h4, 32'h08_07_06_05);
    axi_write(ACCEL_BASE + W_ROW0 + 'h8, 32'h0C_0B_0A_09);
    axi_write(ACCEL_BASE + W_ROW0 + 'hC, 32'h10_0F_0E_0D);
    axi_write(ACCEL_BASE + A_ROW0,       32'h04_03_02_01);
    axi_write(ACCEL_BASE + A_ROW0 + 'h4, 32'h08_07_06_05);
    axi_write(ACCEL_BASE + A_ROW0 + 'h8, 32'h0C_0B_0A_09);
    axi_write(ACCEL_BASE + A_ROW0 + 'hC, 32'h10_0F_0E_0D);
    axi_write(ACCEL_BASE + CTRL, 32'h1);
    do axi_read(ACCEL_BASE + CTRL, rd); while (!rd[1]);
    // Y[0][0] = 1*1+2*5+3*9+4*13 = 1+10+27+52 = 90
    axi_read(ACCEL_BASE + Y_BASE + 0*4,  rd); check(rd, 32'd90,  "Y[0][0]=90");
    // Y[0][3] = 1*4+2*8+3*12+4*16 = 4+16+36+64 = 120
    axi_read(ACCEL_BASE + Y_BASE + 3*4,  rd); check(rd, 32'd120, "Y[0][3]=120");
    // Y[3][3] = 13*4+14*8+15*12+16*16 = 52+112+180+256 = 600
    axi_read(ACCEL_BASE + Y_BASE + 15*4, rd); check(rd, 32'd600, "Y[3][3]=600");

    // ── TEST 4: Interleaved SRAM + accel access (prove no crossbar pollution) ─
    $display("\n=== TEST 4: Interleaved SRAM + accel access ===");
    // Write a sentinel to SRAM while accel is in DONE_ST
    axi_write(SRAM_BASE + 32'h100, 32'hAB_CD_EF_01);
    // Read it back — must not be corrupted by accel traffic
    axi_read(SRAM_BASE + 32'h100, rd);
    check(rd, 32'hAB_CD_EF_01, "SRAM sentinel after accel ops");

    // New matmul: max-positive (A=W=0x7F, Y = 4*127*127 = 64516)
    axi_write(ACCEL_BASE + W_ROW0,       32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + W_ROW0 + 'h4, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + W_ROW0 + 'h8, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + W_ROW0 + 'hC, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + A_ROW0,       32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + A_ROW0 + 'h4, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + A_ROW0 + 'h8, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + A_ROW0 + 'hC, 32'h7F_7F_7F_7F);
    axi_write(ACCEL_BASE + CTRL, 32'h1);
    do axi_read(ACCEL_BASE + CTRL, rd); while (!rd[1]);
    axi_read(ACCEL_BASE + Y_BASE, rd); check(rd, 32'd64516, "Y[0][0] max+ =64516");
    // SRAM sentinel must be unchanged
    axi_read(SRAM_BASE + 32'h100, rd);
    check(rd, 32'hAB_CD_EF_01, "SRAM sentinel unchanged after max+ matmul");

    // ── Report ────────────────────────────────────────────────────────────────
    repeat (5) @(posedge clk);
    if (error_count == 0)
      $display("\n*** INTEGRATION: ALL TESTS PASSED (0 errors) ***");
    else
      $display("\n*** INTEGRATION: %0d ERRORS ***", error_count);
    $finish;
  end

  initial begin
    #1_000_000;
    $display("[TIMEOUT] Integration test exceeded 1ms");
    $finish;
  end

endmodule
