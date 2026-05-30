`timescale 1ns/1ps
// Phase 10 — mem_bram_backend aggressive corner-case testbench (v2).
//
//  T4  All 16 byte-strobe combos (16 checks)
//  T5  Address boundaries: addr=0, 0x7FF00, 0x7FFFC (3 checks)
//  T6  Non-word-aligned address aliasing (2 checks)
//  T7  Read-after-write — zero gap (1 check)
//  T8  Double overwrite — second write wins (1 check)
//  T9  Delayed bready — bvalid must hold 5 cycles (6 checks)
//  T10 Delayed rready — rvalid must hold 5 cycles (6 checks)
//  T11 Zero-strobe write — memory unchanged (1 check)
//  T12 Reset recovery: signals cleared + mem persists + write/read OK (4 checks)
//  T13 Back-to-back reads, 4 addresses (4 checks)
//  T14 Large sequential: 256 words write then verify (256 checks)
//  T15 Static signal checks: awready/wready/arready/bresp/rresp (5 checks)

module mem_bram_tb_v2;

    localparam CLK = 10;
    logic clk = 0, rst_n = 0;
    always #(CLK/2) clk = ~clk;

    logic [31:0] awaddr, wdata, araddr, rdata;
    logic  [3:0] wstrb;
    logic  [1:0] bresp, rresp;
    logic        awvalid, awready, wvalid, wready;
    logic        bvalid, bready, arvalid, arready;
    logic        rvalid, rready;

    mem_bram_backend dut (
        .clk      (clk),     .rst_n    (rst_n),
        .s_awaddr (awaddr),  .s_awvalid(awvalid), .s_awready(awready),
        .s_wdata  (wdata),   .s_wstrb  (wstrb),   .s_wvalid (wvalid),
        .s_wready (wready),  .s_bresp  (bresp),   .s_bvalid (bvalid),
        .s_bready (bready),
        .s_araddr (araddr),  .s_arvalid(arvalid), .s_arready(arready),
        .s_rdata  (rdata),   .s_rresp  (rresp),   .s_rvalid (rvalid),
        .s_rready (rready)
    );

    int pass_cnt = 0, fail_cnt = 0;

    task automatic chk32(input string lbl, input [31:0] got, input [31:0] exp);
        if (got === exp) begin $display("  PASS  %s : 0x%08x", lbl, got); pass_cnt++; end
        else             begin $display("  FAIL  %s : got 0x%08x  exp 0x%08x", lbl, got, exp); fail_cnt++; end
    endtask

    task automatic chk1(input string lbl, input logic got, input logic exp);
        if (got === exp) begin $display("  PASS  %s : %0b", lbl, got); pass_cnt++; end
        else             begin $display("  FAIL  %s : got %0b  exp %0b", lbl, got, exp); fail_cnt++; end
    endtask

    // Pre-posedge drive: set signals before @(posedge clk) so always_ff
    // samples them regardless of coroutine evaluation order.
    task automatic axi_write(input [31:0] addr, input [31:0] data,
                              input [3:0] strb = 4'hF);
        awaddr = addr; awvalid = 1'b1;
        wdata  = data; wstrb   = strb; wvalid = 1'b1;
        @(posedge clk);               // FF: awvalid&&wvalid → wr_pending<=1
        awvalid = 1'b0; wvalid = 1'b0;
        @(posedge clk);               // FF: wr_pending → write, bvalid<=1
        bready = 1'b1;
        @(posedge clk);               // FF: bvalid&&bready → bvalid<=0
        bready = 1'b0;
    endtask

    task automatic axi_read(input [31:0] addr, output [31:0] data);
        araddr = addr; arvalid = 1'b1; rready = 1'b1;
        @(posedge clk);               // FF: arvalid → rdata<=mem[], rvalid<=1
        arvalid = 1'b0;
        @(posedge clk);               // FF: rvalid&&rready → rvalid<=0
        data   = rdata;
        rready = 1'b0;
    endtask

    logic [31:0] rd, rd1, rd2, rd3, rd4;

    initial begin
        awvalid=0; wvalid=0; bready=0; arvalid=0; rready=0;
        awaddr=0; wdata=0; wstrb=0; araddr=0;
        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        // ══ T4: All 16 byte-strobe combos ════════════════════════════════════
        $display("─ T4: all byte-strobe combos ─");
        // Pre-fill 0x304 with 0xFFFF_FFFF; write 0x0000_0000 through each strobe;
        // verify only targeted bytes become 0x00.
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hF); axi_read(32'h304, rd); chk32("T4 strb=F", rd, 32'h0000_0000);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h0); axi_read(32'h304, rd); chk32("T4 strb=0", rd, 32'hFFFF_FFFF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h1); axi_read(32'h304, rd); chk32("T4 strb=1", rd, 32'hFFFF_FF00);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h2); axi_read(32'h304, rd); chk32("T4 strb=2", rd, 32'hFFFF_00FF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h3); axi_read(32'h304, rd); chk32("T4 strb=3", rd, 32'hFFFF_0000);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h4); axi_read(32'h304, rd); chk32("T4 strb=4", rd, 32'hFF00_FFFF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h5); axi_read(32'h304, rd); chk32("T4 strb=5", rd, 32'hFF00_FF00);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h6); axi_read(32'h304, rd); chk32("T4 strb=6", rd, 32'hFF00_00FF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h7); axi_read(32'h304, rd); chk32("T4 strb=7", rd, 32'hFF00_0000);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h8); axi_read(32'h304, rd); chk32("T4 strb=8", rd, 32'h00FF_FFFF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'h9); axi_read(32'h304, rd); chk32("T4 strb=9", rd, 32'h00FF_FF00);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hA); axi_read(32'h304, rd); chk32("T4 strb=A", rd, 32'h00FF_00FF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hB); axi_read(32'h304, rd); chk32("T4 strb=B", rd, 32'h00FF_0000);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hC); axi_read(32'h304, rd); chk32("T4 strb=C", rd, 32'h0000_FFFF);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hD); axi_read(32'h304, rd); chk32("T4 strb=D", rd, 32'h0000_FF00);
        axi_write(32'h304, 32'hFFFF_FFFF, 4'hF); axi_write(32'h304, 32'h0, 4'hE); axi_read(32'h304, rd); chk32("T4 strb=E", rd, 32'h0000_00FF);

        // ══ T5: Address boundaries ════════════════════════════════════════════
        $display("─ T5: address boundaries ─");
        axi_write(32'h0000_0000, 32'hBEEF_0000); axi_read(32'h0000_0000, rd); chk32("T5 addr=0x00000", rd, 32'hBEEF_0000);
        axi_write(32'h0007_FF00, 32'hBEEF_FF00); axi_read(32'h0007_FF00, rd); chk32("T5 addr=0x7FF00", rd, 32'hBEEF_FF00);
        axi_write(32'h0007_FFFC, 32'hBEEF_FFFC); axi_read(32'h0007_FFFC, rd); chk32("T5 addr=0x7FFFC", rd, 32'hBEEF_FFFC);

        // ══ T6: Non-word-aligned address aliasing ═════════════════════════════
        // addr[1:0] are ignored; 0x400 and 0x401/0x403 map to the same word.
        $display("─ T6: non-aligned aliasing ─");
        axi_write(32'h0000_0400, 32'hAAAA_AAAA); axi_read(32'h0000_0403, rd); chk32("T6 wr=0x400 rd=0x403", rd, 32'hAAAA_AAAA);
        axi_write(32'h0000_0401, 32'hBBBB_BBBB); axi_read(32'h0000_0400, rd); chk32("T6 wr=0x401 rd=0x400", rd, 32'hBBBB_BBBB);

        // ══ T7: Read-after-write (zero gap) ══════════════════════════════════
        $display("─ T7: read-after-write ─");
        axi_write(32'h0000_0500, 32'hCAFE_CAFE);
        axi_read (32'h0000_0500, rd);
        chk32("T7 RAW", rd, 32'hCAFE_CAFE);

        // ══ T8: Double overwrite — second write wins ═══════════════════════════
        $display("─ T8: double overwrite ─");
        axi_write(32'h0000_0600, 32'h1111_1111);
        axi_write(32'h0000_0600, 32'h2222_2222);
        axi_read (32'h0000_0600, rd);
        chk32("T8 overwrite", rd, 32'h2222_2222);

        // ══ T9: Delayed bready — bvalid must hold ════════════════════════════
        $display("─ T9: delayed bready ─");
        awaddr = 32'h700; wdata = 32'hDEAD_0009; wstrb = 4'hF;
        awvalid = 1; wvalid = 1;
        @(posedge clk); awvalid = 0; wvalid = 0;
        @(posedge clk);               // write executes, bvalid<=1 (NBA)
        // bvalid is committed by the time we reach the next posedge:
        repeat (5) begin @(posedge clk); chk1("T9 bvalid held", bvalid, 1'b1); end
        bready = 1; @(posedge clk); bready = 0;
        axi_read(32'h700, rd); chk32("T9 data OK", rd, 32'hDEAD_0009);

        // ══ T10: Delayed rready — rvalid must hold ════════════════════════════
        $display("─ T10: delayed rready ─");
        axi_write(32'h800, 32'hDEAD_000A);
        araddr = 32'h800; arvalid = 1; rready = 0;   // rready intentionally low
        @(posedge clk); arvalid = 0;
        @(posedge clk);               // rvalid<=1 committed in NBA of prev edge
        repeat (5) begin @(posedge clk); chk1("T10 rvalid held", rvalid, 1'b1); end
        rready = 1; @(posedge clk);
        rd = rdata;
        rready = 0;
        chk32("T10 data OK", rd, 32'hDEAD_000A);

        // ══ T11: Zero-strobe write — memory unchanged ═════════════════════════
        $display("─ T11: zero-strobe write ─");
        axi_write(32'h900, 32'hABCD_1234, 4'hF);
        axi_write(32'h900, 32'hFFFF_FFFF, 4'h0);     // strb=0 → no bytes written
        axi_read (32'h900, rd);
        chk32("T11 zero-strobe unchanged", rd, 32'hABCD_1234);

        // ══ T12: Reset recovery ═══════════════════════════════════════════════
        $display("─ T12: reset recovery ─");
        axi_write(32'hA00, 32'hDEAD_BEEF);
        rst_n = 0; repeat (3) @(posedge clk);
        chk1("T12 bvalid=0 on rst", bvalid, 1'b0);
        chk1("T12 rvalid=0 on rst", rvalid, 1'b0);
        rst_n = 1; repeat (2) @(posedge clk);
        axi_write(32'hB00, 32'hCAFE_BABE);
        axi_read (32'hB00, rd); chk32("T12 write after rst",  rd, 32'hCAFE_BABE);
        axi_read (32'hA00, rd); chk32("T12 mem persists rst", rd, 32'hDEAD_BEEF);

        // ══ T13: Back-to-back reads ════════════════════════════════════════════
        $display("─ T13: back-to-back reads ─");
        axi_write(32'hC00, 32'hC000_0001); axi_write(32'hC04, 32'hC000_0002);
        axi_write(32'hC08, 32'hC000_0003); axi_write(32'hC0C, 32'hC000_0004);
        axi_read(32'hC00, rd1); axi_read(32'hC04, rd2);
        axi_read(32'hC08, rd3); axi_read(32'hC0C, rd4);
        chk32("T13 bb-read[0]", rd1, 32'hC000_0001);
        chk32("T13 bb-read[1]", rd2, 32'hC000_0002);
        chk32("T13 bb-read[2]", rd3, 32'hC000_0003);
        chk32("T13 bb-read[3]", rd4, 32'hC000_0004);

        // ══ T14: 256-word sequential ═══════════════════════════════════════════
        $display("─ T14: 256-word sequential ─");
        for (int i = 0; i < 256; i++)
            axi_write(i*4, 32'hF000_0000 + i);
        for (int i = 0; i < 256; i++) begin
            axi_read(i*4, rd);
            chk32($sformatf("T14[%0d]", i), rd, 32'hF000_0000 + i);
        end

        // ══ T15: Static signal checks ══════════════════════════════════════════
        $display("─ T15: static signal checks ─");
        chk1("T15 awready=1",  awready,         1'b1);
        chk1("T15 wready=1",   wready,           1'b1);
        chk1("T15 arready=1",  arready,          1'b1);
        chk1("T15 bresp=0",    bresp  == 2'b00,  1'b1);
        chk1("T15 rresp=0",    rresp  == 2'b00,  1'b1);

        $display("");
        $display("╔══════════════════════════════════════════════════════╗");
        $display("║  Phase 10 — BRAM Backend Aggressive Corner Tests    ║");
        $display("╠══════════════════════════════════════════════════════╣");
        if (fail_cnt == 0)
            $display("║  ALL %0d CHECKS PASSED                             ║", pass_cnt);
        else
            $display("║  %0d/%0d CHECKS FAILED — see [FAIL] lines above     ║",
                     fail_cnt, pass_cnt + fail_cnt);
        $display("╚══════════════════════════════════════════════════════╝");
        $finish;
    end

endmodule
