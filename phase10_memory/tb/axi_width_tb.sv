`timescale 1ns/1ps
// axi_width_32to128 comprehensive testbench.
//
// Drive convention: signals driven BEFORE @(posedge clk) so always_ff
// reliably samples them.  Tasks account for the registered state machine:
//
//   w32          7 clocks (simultaneous AW+W)
//   w32_wfirst   9 clocks (W arrives before AW → WR_AW state)
//   w32_awfirst  9 clocks (AW arrives before W → WR_W state)
//   r32          5 clocks
//
// Tests:
//  T1  All 4 write lanes — m_awaddr / m_wdata / m_wstrb placement
//  T2  All 4 read lanes  — s_rdata extraction from 128-bit m_rdata
//  T3  Partial byte enables per lane
//  T4  W-before-AW path (WR_AW state)
//  T5  AW-before-W path (WR_W state)
//  T6  Delayed m_awready (3-cycle hold, m_wready immediate)
//  T7  Delayed m_wready  (3-cycle hold, m_awready immediate)
//  T8  Delayed m_rvalid  (3-cycle hold after AR handshake)
//  T9  Back-to-back writes (3 transactions)
//  T10 Back-to-back reads  (4 transactions)
//  T11 Fixed AXI4 parameter checks

module axi_width_tb;

    localparam CLK = 10;
    logic clk = 0, rst_n = 0;
    always #(CLK/2) clk = ~clk;

    // ── 32-bit slave side ───────────────────────────────────────────────────────
    logic [31:0] s_awaddr, s_wdata, s_araddr, s_rdata;
    logic  [3:0] s_wstrb;
    logic  [1:0] s_bresp, s_rresp;
    logic        s_awvalid, s_awready, s_wvalid, s_wready;
    logic        s_bvalid, s_bready, s_arvalid, s_arready, s_rvalid, s_rready;

    // ── 128-bit master side ─────────────────────────────────────────────────────
    logic [29:0]  m_awaddr;
    logic  [7:0]  m_awlen;
    logic  [2:0]  m_awsize;
    logic  [1:0]  m_awburst;
    logic         m_awvalid, m_awready;
    logic [127:0] m_wdata;
    logic  [15:0] m_wstrb;
    logic         m_wlast, m_wvalid, m_wready;
    logic  [1:0]  m_bresp;
    logic         m_bvalid, m_bready;
    logic [29:0]  m_araddr;
    logic  [7:0]  m_arlen;
    logic  [2:0]  m_arsize;
    logic  [1:0]  m_arburst;
    logic         m_arvalid, m_arready;
    logic [127:0] m_rdata;
    logic  [1:0]  m_rresp;
    logic         m_rlast, m_rvalid, m_rready;

    axi_width_32to128 dut (
        .clk       (clk),       .rst_n     (rst_n),
        .s_awaddr  (s_awaddr),  .s_awvalid (s_awvalid), .s_awready (s_awready),
        .s_wdata   (s_wdata),   .s_wstrb   (s_wstrb),   .s_wvalid  (s_wvalid),
        .s_wready  (s_wready),  .s_bresp   (s_bresp),   .s_bvalid  (s_bvalid),
        .s_bready  (s_bready),
        .s_araddr  (s_araddr),  .s_arvalid (s_arvalid), .s_arready (s_arready),
        .s_rdata   (s_rdata),   .s_rresp   (s_rresp),   .s_rvalid  (s_rvalid),
        .s_rready  (s_rready),
        .m_awaddr  (m_awaddr),  .m_awlen   (m_awlen),   .m_awsize  (m_awsize),
        .m_awburst (m_awburst), .m_awvalid (m_awvalid), .m_awready (m_awready),
        .m_wdata   (m_wdata),   .m_wstrb   (m_wstrb),   .m_wlast   (m_wlast),
        .m_wvalid  (m_wvalid),  .m_wready  (m_wready),
        .m_bresp   (m_bresp),   .m_bvalid  (m_bvalid),  .m_bready  (m_bready),
        .m_araddr  (m_araddr),  .m_arlen   (m_arlen),   .m_arsize  (m_arsize),
        .m_arburst (m_arburst), .m_arvalid (m_arvalid), .m_arready (m_arready),
        .m_rdata   (m_rdata),   .m_rresp   (m_rresp),   .m_rlast   (m_rlast),
        .m_rvalid  (m_rvalid),  .m_rready  (m_rready)
    );

    int pass_cnt = 0, fail_cnt = 0;

    task automatic chk32(input string lbl, input [31:0] got, input [31:0] exp);
        if (got === exp) begin $display("  PASS  %s : 0x%08x", lbl, got); pass_cnt++; end
        else             begin $display("  FAIL  %s : got 0x%08x  exp 0x%08x", lbl, got, exp); fail_cnt++; end
    endtask

    task automatic chk128(input string lbl, input [127:0] got, input [127:0] exp);
        if (got === exp) begin $display("  PASS  %s", lbl); pass_cnt++; end
        else begin $display("  FAIL  %s\n        got 0x%032x\n        exp 0x%032x", lbl, got, exp); fail_cnt++; end
    endtask

    task automatic chk_any(input string lbl, input [31:0] got, input [31:0] exp);
        if (got === exp) begin $display("  PASS  %s : 0x%x", lbl, got); pass_cnt++; end
        else             begin $display("  FAIL  %s : got 0x%x  exp 0x%x", lbl, got, exp); fail_cnt++; end
    endtask

    // ── Helper functions for expected lane values ───────────────────────────────
    function automatic [127:0] lane_data(input [31:0] d, input [1:0] ln);
        lane_data = 128'h0; lane_data[ln*32 +: 32] = d;
    endfunction

    function automatic [31:0] lane_strb(input [3:0] s, input [1:0] ln);
        logic [15:0] tmp; tmp = 16'h0; tmp[ln*4 +: 4] = s;
        lane_strb = {16'b0, tmp};
    endfunction

    // ── Write task: simultaneous AW+W, immediate master-side response ───────────
    // 7 clocks total.
    task automatic w32(
        input  [31:0]  sa, sd, input [3:0] ss,
        output [29:0]  out_ma,
        output [127:0] out_md,
        output  [15:0] out_ms
    );
        // Cycle 1 – drive both channels
        s_awaddr=sa; s_awvalid=1; s_wdata=sd; s_wstrb=ss; s_wvalid=1;
        @(posedge clk);             // DUT WR_IDLE→WR_RESP, m_awvalid<=1, m_wvalid<=1
        s_awvalid=0; s_wvalid=0;
        // Cycle 2 – m_awvalid=1, m_wvalid=1; combinational m_wdata/m_wstrb valid
        @(posedge clk);
        out_ma=m_awaddr; out_md=m_wdata; out_ms=m_wstrb;
        // Accept both master channels
        m_awready=1; m_wready=1;
        // Cycle 3 – DUT clears m_awvalid, m_wvalid
        @(posedge clk); m_awready=0; m_wready=0;
        // Cycle 4 – DUT: !m_awvalid&&!m_wvalid → m_bready<=1
        @(posedge clk);
        m_bvalid=1; m_bresp=2'b00;
        // Cycle 5 – DUT: m_bvalid&&m_bready → s_bvalid<=1, m_bready<=0
        @(posedge clk); m_bvalid=0;
        s_bready=1;
        // Cycle 6 – DUT: s_bvalid&&s_bready → WR_IDLE, s_bvalid<=0
        @(posedge clk); s_bready=0;
        // Cycle 7 – DUT WR_IDLE: s_awready<=1, s_wready<=1
        @(posedge clk);
    endtask

    // ── Write task: W arrives before AW (exercises WR_AW state) ────────────────
    task automatic w32_wfirst(
        input  [31:0]  sa, sd, input [3:0] ss,
        output [29:0]  out_ma,
        output [127:0] out_md,
        output  [15:0] out_ms
    );
        // Drive W only
        s_wdata=sd; s_wstrb=ss; s_wvalid=1; s_awvalid=0;
        @(posedge clk);             // DUT WR_IDLE→WR_AW (W latched, waiting for AW)
        s_wvalid=0;
        @(posedge clk);             // in WR_AW; s_awready=1
        // Now drive AW
        s_awaddr=sa; s_awvalid=1;
        @(posedge clk);             // DUT WR_AW→WR_RESP; m_awvalid<=1, m_wvalid<=1
        s_awvalid=0;
        @(posedge clk);
        out_ma=m_awaddr; out_md=m_wdata; out_ms=m_wstrb;
        m_awready=1; m_wready=1;
        @(posedge clk); m_awready=0; m_wready=0;
        @(posedge clk);
        m_bvalid=1; m_bresp=2'b00;
        @(posedge clk); m_bvalid=0; s_bready=1;
        @(posedge clk); s_bready=0;
        @(posedge clk);
    endtask

    // ── Write task: AW arrives before W (exercises WR_W state) ─────────────────
    task automatic w32_awfirst(
        input  [31:0]  sa, sd, input [3:0] ss,
        output [29:0]  out_ma,
        output [127:0] out_md,
        output  [15:0] out_ms
    );
        // Drive AW only
        s_awaddr=sa; s_awvalid=1; s_wvalid=0;
        @(posedge clk);             // DUT WR_IDLE→WR_W (AW latched, waiting for W)
        s_awvalid=0;
        @(posedge clk);             // in WR_W; s_wready=1
        // Now drive W
        s_wdata=sd; s_wstrb=ss; s_wvalid=1;
        @(posedge clk);             // DUT WR_W→WR_RESP; m_awvalid<=1, m_wvalid<=1
        s_wvalid=0;
        @(posedge clk);
        out_ma=m_awaddr; out_md=m_wdata; out_ms=m_wstrb;
        m_awready=1; m_wready=1;
        @(posedge clk); m_awready=0; m_wready=0;
        @(posedge clk);
        m_bvalid=1; m_bresp=2'b00;
        @(posedge clk); m_bvalid=0; s_bready=1;
        @(posedge clk); s_bready=0;
        @(posedge clk);
    endtask

    // ── Read task ───────────────────────────────────────────────────────────────
    // 5 clocks total.
    task automatic r32(
        input  [31:0]  sa,
        input  [127:0] mig_rdata,
        output [31:0]  out_sd
    );
        s_araddr=sa; s_arvalid=1; s_rready=1;
        @(posedge clk);             // DUT RD_IDLE→RD_WAIT, m_arvalid<=1
        s_arvalid=0; m_arready=1;
        @(posedge clk);             // DUT: m_arvalid<=0
        m_arready=0;
        m_rdata=mig_rdata; m_rvalid=1; m_rlast=1; m_rresp=2'b00;
        @(posedge clk);             // DUT: s_rdata<=lane, s_rvalid<=1
        m_rvalid=0;
        @(posedge clk);             // DUT: s_rvalid&&s_rready → RD_IDLE, s_rvalid<=0
        out_sd=s_rdata;
        s_rready=0;
        @(posedge clk);             // DUT RD_IDLE: s_arready<=1
    endtask

    // ── Locals ──────────────────────────────────────────────────────────────────
    logic [29:0]  ma;
    logic [127:0] md, rdat128;
    logic  [15:0] ms;
    logic [31:0]  rd;

    initial begin
        s_awaddr=0; s_awvalid=0; s_wdata=0; s_wstrb=0; s_wvalid=0;
        s_bready=0; s_araddr=0; s_arvalid=0; s_rready=0;
        m_awready=0; m_wready=0; m_bvalid=0; m_bresp=0;
        m_arready=0; m_rdata=0; m_rvalid=0; m_rlast=0; m_rresp=0;
        repeat(4) @(posedge clk); rst_n=1; repeat(2) @(posedge clk);

        // ══ T1: All 4 write lanes ═══════════════════════════════════════════
        $display("─ T1: write lane placement ─");
        // Lane 0 (addr=0x00, addr[3:2]=0)
        w32(32'h0000_0000, 32'hA000_0000, 4'hF, ma, md, ms);
        chk_any("T1 L0 m_awaddr", {2'b0, ma}, 32'd0);
        chk128("T1 L0 m_wdata",   md, lane_data(32'hA000_0000, 0));
        chk_any("T1 L0 m_wstrb",  {16'b0, ms}, lane_strb(4'hF, 0));
        // Lane 1 (addr=0x04, addr[3:2]=1)
        w32(32'h0000_0004, 32'hA000_0001, 4'hF, ma, md, ms);
        chk_any("T1 L1 m_awaddr", {2'b0, ma}, 32'd1);
        chk128("T1 L1 m_wdata",   md, lane_data(32'hA000_0001, 1));
        chk_any("T1 L1 m_wstrb",  {16'b0, ms}, lane_strb(4'hF, 1));
        // Lane 2 (addr=0x08, addr[3:2]=2)
        w32(32'h0000_0008, 32'hA000_0002, 4'hF, ma, md, ms);
        chk_any("T1 L2 m_awaddr", {2'b0, ma}, 32'd2);
        chk128("T1 L2 m_wdata",   md, lane_data(32'hA000_0002, 2));
        chk_any("T1 L2 m_wstrb",  {16'b0, ms}, lane_strb(4'hF, 2));
        // Lane 3 (addr=0x0C, addr[3:2]=3)
        w32(32'h0000_000C, 32'hA000_0003, 4'hF, ma, md, ms);
        chk_any("T1 L3 m_awaddr", {2'b0, ma}, 32'd3);
        chk128("T1 L3 m_wdata",   md, lane_data(32'hA000_0003, 3));
        chk_any("T1 L3 m_wstrb",  {16'b0, ms}, lane_strb(4'hF, 3));
        // Lane 0 of next 128-bit block (addr=0x10, addr[3:2]=0 again)
        w32(32'h0000_0010, 32'hA000_0010, 4'hF, ma, md, ms);
        chk_any("T1 L0' m_awaddr", {2'b0, ma}, 32'd4);
        chk128("T1 L0' m_wdata",   md, lane_data(32'hA000_0010, 0));

        // ══ T2: All 4 read lanes ══════════════════════════════════════════════
        $display("─ T2: read lane extraction ─");
        // Pack known values into each 32-bit lane of m_rdata
        rdat128 = {32'hDEAD_0003, 32'hDEAD_0002, 32'hDEAD_0001, 32'hDEAD_0000};
        r32(32'h0000_0000, rdat128, rd); chk32("T2 L0 s_rdata", rd, 32'hDEAD_0000);
        r32(32'h0000_0004, rdat128, rd); chk32("T2 L1 s_rdata", rd, 32'hDEAD_0001);
        r32(32'h0000_0008, rdat128, rd); chk32("T2 L2 s_rdata", rd, 32'hDEAD_0002);
        r32(32'h0000_000C, rdat128, rd); chk32("T2 L3 s_rdata", rd, 32'hDEAD_0003);

        // ══ T3: Partial byte enables per lane ════════════════════════════════
        $display("─ T3: partial byte enables ─");
        w32(32'h0000_0000, 32'hABCD_EF01, 4'h5, ma, md, ms);
        chk_any("T3 L0 strb=5", {16'b0, ms}, lane_strb(4'h5, 0));
        w32(32'h0000_0004, 32'hABCD_EF01, 4'h9, ma, md, ms);
        chk_any("T3 L1 strb=9", {16'b0, ms}, lane_strb(4'h9, 1));
        w32(32'h0000_0008, 32'hABCD_EF01, 4'h3, ma, md, ms);
        chk_any("T3 L2 strb=3", {16'b0, ms}, lane_strb(4'h3, 2));
        w32(32'h0000_000C, 32'hABCD_EF01, 4'hA, ma, md, ms);
        chk_any("T3 L3 strb=A", {16'b0, ms}, lane_strb(4'hA, 3));

        // ══ T4: W-before-AW path (WR_AW state) ═══════════════════════════════
        $display("─ T4: W-before-AW path ─");
        w32_wfirst(32'h0000_0004, 32'hB0B0_0001, 4'h6, ma, md, ms);
        chk_any("T4 m_awaddr", {2'b0, ma}, 32'd1);
        chk128("T4 m_wdata",   md, lane_data(32'hB0B0_0001, 1));
        chk_any("T4 m_wstrb",  {16'b0, ms}, lane_strb(4'h6, 1));

        // ══ T5: AW-before-W path (WR_W state) ════════════════════════════════
        $display("─ T5: AW-before-W path ─");
        w32_awfirst(32'h0000_0008, 32'hC0C0_0002, 4'hC, ma, md, ms);
        chk_any("T5 m_awaddr", {2'b0, ma}, 32'd2);
        chk128("T5 m_wdata",   md, lane_data(32'hC0C0_0002, 2));
        chk_any("T5 m_wstrb",  {16'b0, ms}, lane_strb(4'hC, 2));

        // ══ T6: Delayed m_awready (3 cycles, m_wready immediate) ═════════════
        // Cycle count: 1=drive, 2=WR_RESP entry, 3=accept W, 4..6=delay, 7=accept AW,
        //              8=bready set, 9=bvalid in, 10=bready consumed, 11=WR_IDLE.
        $display("─ T6: delayed m_awready ─");
        s_awaddr=32'h0; s_awvalid=1; s_wdata=32'hD0D0_0000; s_wstrb=4'hF; s_wvalid=1;
        @(posedge clk); s_awvalid=0; s_wvalid=0;   // cycle 1
        @(posedge clk);                              // cycle 2: m_awvalid=1, m_wvalid=1
        m_wready=1;
        @(posedge clk); m_wready=0;                 // cycle 3: m_wvalid<=0
        repeat(3) @(posedge clk);                   // cycles 4-6: m_awvalid still 1
        m_awready=1;
        @(posedge clk); m_awready=0;                // cycle 7: m_awvalid<=0
        @(posedge clk);                              // cycle 8: m_bready<=1
        m_bvalid=1; m_bresp=2'b00;
        @(posedge clk); m_bvalid=0; s_bready=1;     // cycle 9: s_bvalid<=1
        @(posedge clk); s_bready=0;                 // cycle 10: WR_IDLE
        @(posedge clk);                              // cycle 11: s_awready<=1
        // Verify DUT returned to WR_IDLE (s_awready re-armed)
        chk_any("T6 s_awready after delayed-awready", {31'b0, s_awready}, 32'd1);

        // ══ T7: Delayed m_wready (3 cycles, m_awready immediate) ═════════════
        $display("─ T7: delayed m_wready ─");
        s_awaddr=32'h4; s_awvalid=1; s_wdata=32'hD0D0_0001; s_wstrb=4'hF; s_wvalid=1;
        @(posedge clk); s_awvalid=0; s_wvalid=0;
        @(posedge clk);
        m_awready=1;
        @(posedge clk); m_awready=0;
        repeat(3) @(posedge clk);
        m_wready=1;
        @(posedge clk); m_wready=0;
        @(posedge clk);
        m_bvalid=1; m_bresp=2'b00;
        @(posedge clk); m_bvalid=0; s_bready=1;
        @(posedge clk); s_bready=0;
        @(posedge clk);
        chk_any("T7 s_awready after delayed-wready", {31'b0, s_awready}, 32'd1);

        // ══ T8: Delayed m_rvalid (3-cycle hold after AR handshake) ═══════════
        $display("─ T8: delayed m_rvalid ─");
        rdat128 = {32'hBEEF_0003, 32'hBEEF_0002, 32'hBEEF_0001, 32'hBEEF_0000};
        s_araddr=32'h8; s_arvalid=1; s_rready=1;
        @(posedge clk); s_arvalid=0; m_arready=1;   // RD_WAIT entry
        @(posedge clk); m_arready=0;                // m_arvalid<=0
        repeat(3) @(posedge clk);                   // hold 3 cycles before rvalid
        m_rdata=rdat128; m_rvalid=1; m_rlast=1;
        @(posedge clk); m_rvalid=0;                 // s_rdata<=lane2, s_rvalid<=1
        @(posedge clk); rd=s_rdata; s_rready=0;     // capture after rvalid&&rready
        @(posedge clk);
        chk32("T8 delayed rvalid lane2", rd, 32'hBEEF_0002);

        // ══ T9: Back-to-back writes (3 transactions) ═════════════════════════
        $display("─ T9: back-to-back writes ─");
        w32(32'h0000_0000, 32'hE000_0000, 4'hF, ma, md, ms);
        chk128("T9 bb-wr[0] m_wdata", md, lane_data(32'hE000_0000, 0));
        w32(32'h0000_0004, 32'hE000_0001, 4'hF, ma, md, ms);
        chk128("T9 bb-wr[1] m_wdata", md, lane_data(32'hE000_0001, 1));
        w32(32'h0000_000C, 32'hE000_0003, 4'hF, ma, md, ms);
        chk128("T9 bb-wr[2] m_wdata", md, lane_data(32'hE000_0003, 3));

        // ══ T10: Back-to-back reads (4 transactions) ═════════════════════════
        $display("─ T10: back-to-back reads ─");
        rdat128 = {32'hF0F0_000C, 32'hF0F0_0008, 32'hF0F0_0004, 32'hF0F0_0000};
        r32(32'h0, rdat128, rd); chk32("T10 bb-rd[0]", rd, 32'hF0F0_0000);
        r32(32'h4, rdat128, rd); chk32("T10 bb-rd[1]", rd, 32'hF0F0_0004);
        r32(32'h8, rdat128, rd); chk32("T10 bb-rd[2]", rd, 32'hF0F0_0008);
        r32(32'hC, rdat128, rd); chk32("T10 bb-rd[3]", rd, 32'hF0F0_000C);

        // ══ T11: Fixed AXI4 parameter checks ═════════════════════════════════
        $display("─ T11: fixed AXI4 parameters ─");
        chk_any("T11 m_awlen=0",    {24'b0, m_awlen},   32'd0);
        chk_any("T11 m_awsize=4",   {29'b0, m_awsize},  32'd4);
        chk_any("T11 m_awburst=1",  {30'b0, m_awburst}, 32'd1);
        chk_any("T11 m_wlast=1",    {31'b0, m_wlast},   32'd1);
        chk_any("T11 m_arlen=0",    {24'b0, m_arlen},   32'd0);
        chk_any("T11 m_arsize=4",   {29'b0, m_arsize},  32'd4);
        chk_any("T11 m_arburst=1",  {30'b0, m_arburst}, 32'd1);

        $display("");
        $display("╔════════════════════════════════════════════════════════╗");
        $display("║  Phase 10 — axi_width_32to128 Comprehensive Tests     ║");
        $display("╠════════════════════════════════════════════════════════╣");
        if (fail_cnt == 0)
            $display("║  ALL %0d CHECKS PASSED                               ║", pass_cnt);
        else
            $display("║  %0d/%0d CHECKS FAILED — see [FAIL] lines above        ║",
                     fail_cnt, pass_cnt + fail_cnt);
        $display("╚════════════════════════════════════════════════════════╝");
        $finish;
    end

endmodule
