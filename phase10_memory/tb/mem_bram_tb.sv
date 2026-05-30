`timescale 1ns/1ps
// Phase 10 — mem_bram_backend unit testbench.
//
// Drive convention: signals are set BEFORE @(posedge clk) so the always_ff
// block reliably samples them regardless of coroutine evaluation order.
//
// Tests:
//  T1 Sequential R/W : write/read 16 words
//  T2 Byte enables   : only target bytes modified
//  T3 Simultaneous AW+W pattern (same as DMA)
//  T4 Back-to-back writes, 8 words

module mem_bram_tb;

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

    // Drive AW+W before posedge so always_ff reliably samples them.
    // 3-cycle latency: posedge[0]=latch AW+W, posedge[1]=write+bvalid, posedge[2]=bready deassert
    task automatic axi_write(input [31:0] addr, input [31:0] data, input [3:0] strb = 4'hF);
        // Drive signals (stable before next posedge)
        awaddr = addr; awvalid = 1'b1;
        wdata  = data; wstrb   = strb; wvalid = 1'b1;
        @(posedge clk);           // FF: awvalid&&wvalid → wr_pending<=1, latch addr/data
        awvalid = 1'b0; wvalid = 1'b0;
        @(posedge clk);           // FF: wr_pending=1 → write, bvalid<=1
        bready = 1'b1;            // arm bready before next edge
        @(posedge clk);           // FF: bvalid=1 && bready=1 → bvalid<=0
        bready = 1'b0;
    endtask

    // 2-cycle latency: posedge[0]=sample AR + latch rdata + rvalid, posedge[1]=rvalid deassert
    task automatic axi_read(input [31:0] addr, output [31:0] data);
        araddr = addr; arvalid = 1'b1; rready = 1'b1;
        @(posedge clk);           // FF: arvalid=1 → rdata<=mem[addr], rvalid<=1
        arvalid = 1'b0;
        @(posedge clk);           // FF: rvalid=1 && rready=1 → rvalid<=0; capture rdata
        data   = rdata;
        rready = 1'b0;
    endtask

    logic [31:0] rd;

    initial begin
        awvalid=0; wvalid=0; bready=0; arvalid=0; rready=0;
        awaddr=0; wdata=0; wstrb=0; araddr=0;
        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        // ══ T1: 16 sequential writes then reads ════════════════════════════════
        $display("─ T1: sequential write/read 16 words ─");
        for (int i = 0; i < 16; i++)
            axi_write(i*4, 32'hA000_0000 + i);
        for (int i = 0; i < 16; i++) begin
            axi_read(i*4, rd);
            chk32($sformatf("T1[%0d]", i), rd, 32'hA000_0000 + i);
        end

        // ══ T2: Byte enables ══════════════════════════════════════════════════
        $display("─ T2: byte-enable writes ─");
        axi_write(32'h100, 32'hDEAD_BEEF, 4'hF);   // pre-fill
        axi_write(32'h100, 32'h0000_00AB, 4'h1);   // byte0 only → [7:0]=0xAB
        axi_read (32'h100, rd);
        chk32("T2 byte0", rd, 32'hDEAD_BEAB);      // [7:0] changed
        axi_write(32'h100, 32'hDEAD_BEEF, 4'hF);   // reset
        axi_write(32'h100, 32'h00CD_0000, 4'h4);   // byte2 only → [23:16]=0xCD
        axi_read (32'h100, rd);
        chk32("T2 byte2", rd, 32'hDECD_BEEF);      // [23:16] changed

        // ══ T3: Back-to-back 8 writes then verify ═════════════════════════════
        $display("─ T3: back-to-back 8 writes ─");
        for (int i = 0; i < 8; i++)
            axi_write(32'h200 + i*4, 32'hC000_0000 + i);
        for (int i = 0; i < 8; i++) begin
            axi_read(32'h200 + i*4, rd);
            chk32($sformatf("T3[%0d]", i), rd, 32'hC000_0000 + i);
        end

        $display("");
        $display("╔════════════════════════════════════════╗");
        $display("║  Phase 10 — BRAM Backend Unit Tests   ║");
        $display("╠════════════════════════════════════════╣");
        if (fail_cnt == 0)
            $display("║  ALL %0d CHECKS PASSED                ║", pass_cnt);
        else
            $display("║  %0d/%0d CHECKS FAILED                ║", fail_cnt, pass_cnt+fail_cnt);
        $display("╚════════════════════════════════════════╝");
        $finish;
    end

endmodule
