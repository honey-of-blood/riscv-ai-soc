`timescale 1ns/1ps
// Phase 9 accel_top_v2 comprehensive testbench.
// Covers: basic matmul, identity/zero/large weights & activations,
//         non-zero ACT_BASE, back-to-back computes, mixed weights,
//         selective ReLU, register readback, byte-strobe scratchpad writes.

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
        .s_rready(s_rready), .irq_done(irq_done)
    );

    always #(CLK/2) clk = ~clk;

    int pass_cnt = 0, fail_cnt = 0;

    // Base addresses inside accel_top_v2
    localparam [31:0] CTRL = 32'h0000_0000;   // addr[16]=0 → ctrl regs
    localparam [31:0] SP   = 32'h0001_0000;   // addr[16]=1 → scratchpad

    // ── AXI helpers ──────────────────────────────────────────────────────────
    task automatic axi_write(input [31:0] addr, input [31:0] data, input [3:0] strb);
        @(posedge clk);
        s_awaddr = addr; s_awvalid = 1;
        s_wdata  = data; s_wstrb = strb; s_wvalid = 1;
        @(posedge clk);
        s_awaddr = 0; s_awvalid = 0; s_wdata = 0; s_wvalid = 0;
        s_bready = 1; @(posedge clk); s_bready = 0;
    endtask

    task automatic axi_read(input [31:0] addr, output [31:0] data);
        @(posedge clk); s_araddr = addr; s_arvalid = 1;
        repeat (20) begin
            @(posedge clk);
            if (s_rvalid) begin data = s_rdata; s_rready = 1; break; end
        end
        @(posedge clk); s_araddr = 0; s_arvalid = 0; s_rready = 0;
    endtask

    task automatic poll_done(input int tmo, output logic tout);
        tout = 1;
        repeat (tmo) begin @(posedge clk); if (irq_done) begin tout = 0; break; end end
    endtask

    // Load N weights (all same per-row value), set ACT_BASE, start
    task automatic load_and_start(
        input [31:0] w_row_val,  // same value for all N rows
        input [31:0] act_base_val,
        input        relu_en
    );
        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), w_row_val, 4'hF);
        axi_write(CTRL | 32'h04, act_base_val, 4'hF);
        axi_write(CTRL | 32'h00, {29'h0, relu_en, 1'b0, 1'b1}, 4'hF); // relu,0,start
    endtask

    // Write staggered activation vector a=[a0,a1,a2,a3] starting at scratchpad
    // base_row.  Row r is at sp addr = base_row_addr + r*8, contains byte r = a[r].
    task automatic write_staggered(
        input [31:0] base_sp_addr,
        input  [7:0] a0, a1, a2, a3
    );
        axi_write(base_sp_addr + 32'h00, {24'h0, a0},    4'hF);
        axi_write(base_sp_addr + 32'h08, {16'h0, a1, 8'h0}, 4'hF);
        axi_write(base_sp_addr + 32'h10, {8'h0, a2, 16'h0}, 4'hF);
        axi_write(base_sp_addr + 32'h18, {a3, 24'h0},    4'hF);
    endtask

    task automatic clear_start;
        axi_write(CTRL | 32'h00, 32'h0, 4'hF);
        repeat (4) @(posedge clk);
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

    logic [31:0] rd;
    logic        tout;

    // Read all N outputs
    task automatic read_outputs(output logic [31:0] y[0:N-1]);
        for (int c = 0; c < N; c++) axi_read(CTRL | (32'h100 + c*4), y[c]);
    endtask

    logic [31:0] Y[0:N-1];

    initial begin
        s_awaddr=0; s_awvalid=0; s_wdata=0; s_wstrb=4'hF; s_wvalid=0;
        s_bready=0; s_araddr=0; s_arvalid=0; s_rready=0;
        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        // ══ T1: W=+1, a=[1,2,3,4] → Y=10 ════════════════════════════════
        write_staggered(SP | 32'h0000, 8'd1, 8'd2, 8'd3, 8'd4);
        load_and_start(32'h0101_0101, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T1 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T1 Y[%0d]", c), Y[c], 32'd10);
        clear_start();

        // ══ T2: ReLU, W=-1, a=[1,2,3,4] → Y=0 ═══════════════════════════
        load_and_start(32'hFFFF_FFFF, 32'h0, 1'b1);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T2 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T2 relu Y[%0d]", c), Y[c], 32'd0);
        clear_start();

        // ══ T3: No ReLU, W=-1, a=[1,2,3,4] → Y=-10 ══════════════════════
        load_and_start(32'hFFFF_FFFF, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T3 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T3 neg Y[%0d]", c), Y[c], 32'hFFFF_FFF6);
        clear_start();

        // ══ T4: Identity weights W[r][c]=(r==c?1:0) → Y=[1,2,3,4] ═══════
        // w_row[0]={0,0,0,1}=0x01000000? NO:
        // w_row[r][c*8+:8] = weight at (row r, col c)
        // Identity: w[r][c]=1 iff r==c
        // w_row[0]: col0=1,col1=0,col2=0,col3=0 → 0x00_00_00_01
        // w_row[1]: col1=1 → 0x00_00_01_00
        // w_row[2]: col2=1 → 0x00_01_00_00
        // w_row[3]: col3=1 → 0x01_00_00_00
        axi_write(CTRL | 32'h08, 32'h0000_0001, 4'hF);  // w_row[0]
        axi_write(CTRL | 32'h0C, 32'h0000_0100, 4'hF);  // w_row[1]
        axi_write(CTRL | 32'h10, 32'h0001_0000, 4'hF);  // w_row[2]
        axi_write(CTRL | 32'h14, 32'h0100_0000, 4'hF);  // w_row[3]
        axi_write(CTRL | 32'h04, 32'h0, 4'hF);
        axi_write(CTRL | 32'h00, 32'h1, 4'hF);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T4 timeout"); fail_cnt++; end
        read_outputs(Y);
        // Y[c] = a[c]: a=[1,2,3,4] staggered → Y=[1,2,3,4]
        chk32("T4 Y[0]", Y[0], 32'd1);
        chk32("T4 Y[1]", Y[1], 32'd2);
        chk32("T4 Y[2]", Y[2], 32'd3);
        chk32("T4 Y[3]", Y[3], 32'd4);
        clear_start();

        // ══ T5: Zero activations → Y=0 ════════════════════════════════════
        write_staggered(SP | 32'h0000, 8'd0, 8'd0, 8'd0, 8'd0);
        load_and_start(32'h0101_0101, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T5 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T5 zero-a Y[%0d]", c), Y[c], 32'd0);
        clear_start();

        // ══ T6: Zero weights → Y=0 ════════════════════════════════════════
        write_staggered(SP | 32'h0000, 8'd5, 8'd6, 8'd7, 8'd8);  // non-zero activations
        load_and_start(32'h0000_0000, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T6 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T6 zero-w Y[%0d]", c), Y[c], 32'd0);
        clear_start();

        // ══ T7: INT8 max: a=127, w=127 → Y=4×(127×127)=64516 ═════════════
        write_staggered(SP | 32'h0000, 8'd127, 8'd127, 8'd127, 8'd127);
        load_and_start(32'h7F7F_7F7F, 32'h0, 1'b0);  // w=127 (0x7F)
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T7 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T7 max+ Y[%0d]", c), Y[c], 32'd64516);
        clear_start();

        // ══ T8: INT8 min: a=-128 (0x80), w=-128 → Y=4×(-128×-128)=65536 ══
        write_staggered(SP | 32'h0000, 8'h80, 8'h80, 8'h80, 8'h80);
        load_and_start(32'h8080_8080, 32'h0, 1'b0);  // w=-128 (0x80)
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T8 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T8 INT8-min Y[%0d]", c), Y[c], 32'd65536);
        clear_start();

        // ══ T9: Non-zero ACT_BASE — rows 50-53 at byte addr 400=0x190 ══════
        // ACT_BASE[15:3] = 0x190 >> 3 = 50 → act_row_ptr=50
        write_staggered(SP | 32'h0190, 8'd5, 8'd6, 8'd7, 8'd8);  // sum=26
        load_and_start(32'h0101_0101, 32'h0000_0190, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T9 timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T9 ACT_BASE Y[%0d]", c), Y[c], 32'd26);
        clear_start();

        // ══ T10: Back-to-back computes (second run uses W=2) ══════════════
        // T10a: W=1 → Y=10 (scratchpad row 0 still has a=[1,2,3,4] from T1)
        write_staggered(SP | 32'h0000, 8'd1, 8'd2, 8'd3, 8'd4);
        load_and_start(32'h0101_0101, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T10a timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T10a Y[%0d]", c), Y[c], 32'd10);
        clear_start();

        // T10b: W=2 → Y=20 (same activations, doubled weight)
        load_and_start(32'h0202_0202, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T10b timeout"); fail_cnt++; end
        read_outputs(Y);
        for (int c = 0; c < N; c++) chk32($sformatf("T10b W=2 Y[%0d]", c), Y[c], 32'd20);
        clear_start();

        // ══ T11: Mixed weights w[r][c]=(r+1)*(c+1), a=[1,1,1,1] → Y=[10,20,30,40]
        // w_row[0]: {4,3,2,1}=0x04030201  (w[0][c]=c+1)
        // w_row[1]: {8,6,4,2}=0x08060402  (w[1][c]=2*(c+1))
        // w_row[2]: {12,9,6,3}=0x0C090603
        // w_row[3]: {16,12,8,4}=0x100C0804
        write_staggered(SP | 32'h0000, 8'd1, 8'd1, 8'd1, 8'd1);
        axi_write(CTRL | 32'h08, 32'h0403_0201, 4'hF);
        axi_write(CTRL | 32'h0C, 32'h0806_0402, 4'hF);
        axi_write(CTRL | 32'h10, 32'h0C09_0603, 4'hF);
        axi_write(CTRL | 32'h14, 32'h100C_0804, 4'hF);
        axi_write(CTRL | 32'h04, 32'h0, 4'hF);
        axi_write(CTRL | 32'h00, 32'h1, 4'hF);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T11 timeout"); fail_cnt++; end
        read_outputs(Y);
        chk32("T11 Y[0]", Y[0], 32'd10);
        chk32("T11 Y[1]", Y[1], 32'd20);
        chk32("T11 Y[2]", Y[2], 32'd30);
        chk32("T11 Y[3]", Y[3], 32'd40);
        clear_start();

        // ══ T12: Selective ReLU — even cols positive, odd cols negative ════
        // w_row[r] = {0xFF,0x01,0xFF,0x01} → col0=+1,col1=-1,col2=+1,col3=-1
        // a=[1,2,3,4] → Y=[10,-10,10,-10] → relu → [10,0,10,0]
        write_staggered(SP | 32'h0000, 8'd1, 8'd2, 8'd3, 8'd4);
        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), 32'hFF01_FF01, 4'hF);
        axi_write(CTRL | 32'h04, 32'h0, 4'hF);
        axi_write(CTRL | 32'h00, 32'h5, 4'hF);  // start + relu_en
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T12 timeout"); fail_cnt++; end
        read_outputs(Y);
        chk32("T12 Y[0] relu+",  Y[0], 32'd10);
        chk32("T12 Y[1] relu-",  Y[1], 32'd0);
        chk32("T12 Y[2] relu+",  Y[2], 32'd10);
        chk32("T12 Y[3] relu-",  Y[3], 32'd0);
        clear_start();

        // ══ T13: Register readback — verify weight registers read back ═════
        for (int r = 0; r < N; r++)
            axi_write(CTRL | (32'h08 + r*4), 32'hAA55_AA55, 4'hF);
        for (int r = 0; r < N; r++) begin
            axi_read(CTRL | (32'h08 + r*4), rd);
            chk32($sformatf("T13 w_reg[%0d] rdback", r), rd, 32'hAA55_AA55);
        end

        // ══ T14: ACT_BASE register readback ══════════════════════════════
        axi_write(CTRL | 32'h04, 32'h0000_1234, 4'hF);
        axi_read(CTRL | 32'h04, rd);
        chk32("T14 ACT_BASE rdback", rd, 32'h0000_1234);

        // ══ T15: CTRL register read — ctrl bits ═══════════════════════════
        // After T12's clear_start(), ctrl_start=0, ctrl_done=0, ctrl_relu=0
        axi_read(CTRL | 32'h00, rd);
        chk32("T15 CTRL cleared", rd & 32'h7, 32'h0);

        // ══ T16: Scratchpad byte-strobe via accel AXI port ════════════════
        // Write row10 bank0 = 0xA1B2C3D4, then partial overwrite byte2
        axi_write(SP | 32'h0050, 32'hA1B2C3D4, 4'hF);    // row10, addr=10*8=80=0x50
        axi_write(SP | 32'h0050, 32'h00EE0000, 4'b0100);  // byte2 only
        // read back
        // Use accel's AXI read port (s_araddr with addr[16]=1)
        axi_read(SP | 32'h0050, rd);
        chk32("T16 sp byte-strobe", rd, 32'hA1EEC3D4);  // byte2 replaced

        // ══ T17: Negative activations — a=[-1,-2,-3,-4], W=+1 → Y=-10 ═══
        write_staggered(SP | 32'h0000, 8'hFF, 8'hFE, 8'hFD, 8'hFC);
        load_and_start(32'h0101_0101, 32'h0, 1'b0);
        poll_done(300, tout);
        if (tout) begin $display("  FAIL  T17 timeout"); fail_cnt++; end
        read_outputs(Y);
        // -1 + -2 + -3 + -4 = -10 = 0xFFFFFFF6
        for (int c = 0; c < N; c++) chk32($sformatf("T17 neg-a Y[%0d]", c), Y[c], 32'hFFFF_FFF6);
        clear_start();

        // ══ T18: irq_done is low at start, high after done ════════════════
        write_staggered(SP | 32'h0000, 8'd1, 8'd1, 8'd1, 8'd1);
        load_and_start(32'h0101_0101, 32'h0, 1'b0);
        // sample irq_done before done
        repeat (3) @(posedge clk);
        chk32("T18 irq before done", {31'h0, irq_done}, 32'h0);
        poll_done(300, tout);
        if (!tout) chk32("T18 irq after done", {31'h0, irq_done}, 32'h1);
        else begin $display("  FAIL  T18 timeout"); fail_cnt++; end
        clear_start();

        $display("\n=== Phase 9 accel_top_v2: %0d PASS  %0d FAIL ===\n", pass_cnt, fail_cnt);
        $finish;
    end

    initial begin #2_000_000; $display("WATCHDOG"); $finish; end

endmodule
