`timescale 1ns/1ps
// Phase 9 accel_top_v2 standalone testbench.

module accel_v2_tb;

    localparam int N   = 4;
    localparam int CLK = 10;

    logic        clk = 0, rst_n = 0;
    logic [31:0] s_awaddr, s_wdata;
    logic  [3:0] s_wstrb;
    logic        s_awvalid, s_wvalid, s_awready, s_wready;
    logic  [1:0] s_bresp;
    logic        s_bvalid, s_bready;
    logic [31:0] s_araddr;
    logic        s_arvalid, s_arready;
    logic [31:0] s_rdata;
    logic  [1:0] s_rresp;
    logic        s_rvalid, s_rready;
    logic        irq_done;

    accel_top_v2 #(.N(N)) dut (
        .clk(clk), .rst_n(rst_n),
        .s_awaddr(s_awaddr), .s_awvalid(s_awvalid), .s_awready(s_awready),
        .s_wdata(s_wdata),   .s_wstrb(s_wstrb),     .s_wvalid(s_wvalid),
        .s_wready(s_wready), .s_bresp(s_bresp),      .s_bvalid(s_bvalid),
        .s_bready(s_bready),
        .s_araddr(s_araddr), .s_arvalid(s_arvalid),  .s_arready(s_arready),
        .s_rdata(s_rdata),   .s_rresp(s_rresp),      .s_rvalid(s_rvalid),
        .s_rready(s_rready),
        .irq_done(irq_done)
    );

    always #(CLK/2) clk = ~clk;

    int pass_cnt = 0, fail_cnt = 0;

    task automatic axi_write(input [31:0] addr, input [31:0] data);
        @(posedge clk);
        s_awaddr = addr; s_awvalid = 1;
        s_wdata  = data; s_wstrb = 4'hF; s_wvalid = 1;
        @(posedge clk);
        s_awaddr = 0; s_awvalid = 0;
        s_wdata  = 0;  s_wvalid = 0;
        s_bready = 1;
        @(posedge clk);
        s_bready = 0;
    endtask

    task automatic axi_read(input [31:0] addr, output [31:0] data);
        @(posedge clk);
        s_araddr = addr; s_arvalid = 1;
        repeat (20) begin
            @(posedge clk);
            if (s_rvalid) begin
                data = s_rdata;
                s_rready = 1;
                break;
            end
        end
        @(posedge clk);
        s_araddr = 0; s_arvalid = 0; s_rready = 0;
    endtask

    task automatic poll_done(input int timeout, output logic timed_out);
        timed_out = 1;
        repeat (timeout) begin
            @(posedge clk);
            if (irq_done) begin timed_out = 0; break; end
        end
    endtask

    task automatic chk32(input string lbl, input [31:0] got, input [31:0] exp);
        if (got === exp) begin
            $display("  PASS  %s : 0x%08x", lbl, got);
            pass_cnt++;
        end else begin
            $display("  FAIL  %s : got 0x%08x  exp 0x%08x", lbl, got, exp);
            fail_cnt++;
        end
    endtask

    // Base addresses inside accel_top_v2 address space
    localparam [31:0] CTRL = 32'h0000_0000;  // addr[16]=0 → ctrl regs
    localparam [31:0] SP   = 32'h0001_0000;  // addr[16]=1 → scratchpad

    logic [31:0] rd;
    logic        tout;

    initial begin
        s_awaddr=0; s_awvalid=0; s_wdata=0; s_wstrb=4'hF; s_wvalid=0;
        s_bready=0; s_araddr=0; s_arvalid=0; s_rready=0;

        repeat (4) @(posedge clk);
        rst_n = 1;
        repeat (2) @(posedge clk);

        // ── Test 1: W=+1, a=[1,2,3,4] ─────────────────────────────────────
        // Staggered layout: scratchpad row r has byte r = a[r], others 0.
        // addr = SP_BASE | (r*8)  because addr[15:3]=row → row r starts at byte r*8.
        // a_feed[r] = accel_rdata[r*8+:8] = bank0[row_r][r*8+:8]
        // Row 0 → byte 0 = 1: bank0[row0] = 0x00000001
        // Row 1 → byte 1 = 2: bank0[row1] = 0x00000200
        // Row 2 → byte 2 = 3: bank0[row2] = 0x00030000
        // Row 3 → byte 3 = 4: bank0[row3] = 0x04000000
        axi_write(SP | 32'h0000, 32'h0000_0001);  // row 0, bank 0
        axi_write(SP | 32'h0008, 32'h0000_0200);  // row 1, bank 0
        axi_write(SP | 32'h0010, 32'h0003_0000);  // row 2, bank 0
        axi_write(SP | 32'h0018, 32'h0400_0000);  // row 3, bank 0

        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), 32'h0101_0101);  // w=+1

        axi_write(CTRL | 32'h04, 32'h0);   // ACT_BASE=0
        axi_write(CTRL | 32'h00, 32'h1);   // start, no ReLU

        poll_done(200, tout);
        if (tout) begin $display("  FAIL  T1: timeout"); fail_cnt++; end

        for (int c = 0; c < N; c++) begin
            axi_read(CTRL | (32'h100 + c*4), rd);
            chk32($sformatf("T1 Y[%0d]", c), rd, 32'd10);
        end

        axi_write(CTRL | 32'h00, 32'h0);  // clear start
        repeat (4) @(posedge clk);

        // ── Test 2: W=−1, a=[1,2,3,4], ReLU=on → expect Y=0 ──────────────
        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), 32'hFFFF_FFFF);  // w=-1

        axi_write(CTRL | 32'h04, 32'h0);
        axi_write(CTRL | 32'h00, 32'h5);  // start + relu_en (bits 0,2)

        poll_done(200, tout);
        if (tout) begin $display("  FAIL  T2: timeout"); fail_cnt++; end

        for (int c = 0; c < N; c++) begin
            axi_read(CTRL | (32'h100 + c*4), rd);
            chk32($sformatf("T2 relu Y[%0d]", c), rd, 32'd0);
        end

        axi_write(CTRL | 32'h00, 32'h0);
        repeat (4) @(posedge clk);

        // ── Test 3: W=−1, ReLU=off → Y = −10 = 0xFFFF_FFF6 ──────────────
        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), 32'hFFFF_FFFF);

        axi_write(CTRL | 32'h04, 32'h0);
        axi_write(CTRL | 32'h00, 32'h1);  // start only

        poll_done(200, tout);
        if (tout) begin $display("  FAIL  T3: timeout"); fail_cnt++; end

        for (int c = 0; c < N; c++) begin
            axi_read(CTRL | (32'h100 + c*4), rd);
            chk32($sformatf("T3 Y[%0d]", c), rd, 32'hFFFF_FFF6);
        end

        $display("\n=== Phase 9 accel_top_v2: %0d PASS  %0d FAIL ===\n", pass_cnt, fail_cnt);
        $finish;
    end

    initial begin #1_000_000; $display("WATCHDOG"); $finish; end

endmodule
