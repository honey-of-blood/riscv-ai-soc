`timescale 1ns/1ps
// Scratchpad standalone unit testbench.
// Tests all 4 banks, row addressing, 128-bit accel port, byte strobes,
// AXI read path, large row numbers, and write-then-read correctness.

module scratchpad_tb;

    localparam int CLK  = 10;
    localparam int ROWS = 8192;

    logic clk = 0, rst_n = 0;

    // AXI write port
    logic [16:0] s_awaddr;
    logic        s_awvalid, s_awready;
    logic [31:0] s_wdata;
    logic  [3:0] s_wstrb;
    logic        s_wvalid, s_wready;
    logic  [1:0] s_bresp;
    logic        s_bvalid, s_bready;

    // AXI read port
    logic [16:0] s_araddr;
    logic        s_arvalid, s_arready;
    logic [31:0] s_rdata;
    logic  [1:0] s_rresp;
    logic        s_rvalid, s_rready;

    // Accelerator 128-bit read
    logic [12:0]  accel_addr;
    logic [127:0] accel_rdata;

    scratchpad #(.ROWS(ROWS)) dut (.*);

    always #(CLK/2) clk = ~clk;

    int pass_cnt = 0, fail_cnt = 0;

    // ── AXI helpers ──────────────────────────────────────────────────────────
    task automatic sp_write(input [16:0] addr, input [31:0] data, input [3:0] strb);
        @(posedge clk);
        s_awaddr = addr; s_awvalid = 1;
        s_wdata  = data; s_wstrb = strb; s_wvalid = 1;
        @(posedge clk);
        s_awaddr = 0; s_awvalid = 0; s_wdata = 0; s_wvalid = 0;
        s_bready = 1;
        @(posedge clk); s_bready = 0;
    endtask

    task automatic sp_read(input [16:0] addr, output [31:0] data);
        @(posedge clk);
        s_araddr = addr; s_arvalid = 1;
        repeat (10) begin
            @(posedge clk);
            if (s_rvalid) begin
                data = s_rdata; s_rready = 1; break;
            end
        end
        @(posedge clk); s_araddr = 0; s_arvalid = 0; s_rready = 0;
    endtask

    // 128-bit accel read (registered: set addr, wait 1 clk, sample)
    task automatic accel_read(input [12:0] row, output [127:0] data);
        @(posedge clk);
        accel_addr = row;
        @(posedge clk);
        @(posedge clk);  // extra cycle: addr takes 1 clk to register in BRAM
        data = accel_rdata;
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

    task automatic chk128(input string lbl, input [127:0] got, input [127:0] exp);
        if (got === exp) begin
            $display("  PASS  %s : 0x%032x", lbl, got);
            pass_cnt++;
        end else begin
            $display("  FAIL  %s : got 0x%032x", lbl, got);
            $display("         exp 0x%032x", exp);
            fail_cnt++;
        end
    endtask

    logic [31:0]  rd32;
    logic [127:0] rd128;

    // ── Helper: row r byte address (bank 0) = r*8 ────────────────────────────
    // addr[16:0]: bits[15:3]=row, bits[2:1]=bank, bit[0]=byte

    initial begin
        s_awaddr=0; s_awvalid=0; s_wdata=0; s_wstrb=4'hF; s_wvalid=0;
        s_bready=0; s_araddr=0; s_arvalid=0; s_rready=0;
        accel_addr = 0;

        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        // ── T1: Write all 4 banks of row 0, read 128-bit result ───────────
        // Row 0: addr[15:3]=0. Banks at addr[2:1]=0,1,2,3 → addr 0x00,02,04,06
        sp_write(17'h0000, 32'hAABBCCDD, 4'hF);  // bank0
        sp_write(17'h0002, 32'h11223344, 4'hF);  // bank1
        sp_write(17'h0004, 32'h55667788, 4'hF);  // bank2
        sp_write(17'h0006, 32'hDEADBEEF, 4'hF);  // bank3
        accel_read(13'h0, rd128);
        // accel_rdata: [31:0]=bank0, [63:32]=bank1, [95:64]=bank2, [127:96]=bank3
        chk128("T1 all4banks row0",
               rd128, 128'hDEADBEEF_55667788_11223344_AABBCCDD);

        // ── T2: Write row 1, verify row 0 unaffected ──────────────────────
        // Row 1 bank 0: addr[15:3]=1 → addr=0x0008
        sp_write(17'h0008, 32'hCAFEBABE, 4'hF);  // row1 bank0
        accel_read(13'h0, rd128);
        chk128("T2 row0 unchanged", rd128, 128'hDEADBEEF_55667788_11223344_AABBCCDD);
        accel_read(13'h1, rd128);
        // row1: bank0=0xCAFEBABE, banks 1-3 = 0 (never written)
        chk128("T2 row1 bank0", rd128 & 128'hFFFFFFFF, 128'hCAFEBABE);

        // ── T3: Write boundary row 8191 (last valid row) ──────────────────
        // Row 8191 = 0x1FFF. addr[15:3] = 0x1FFF → addr = 0x1FFF*8 = 0xFFF8
        sp_write(17'h1FFF8, 32'h12345678, 4'hF);  // row 8191, bank0
        accel_read(13'h1FFF, rd128);
        chk32("T3 last row", rd128[31:0], 32'h12345678);

        // ── T4: No aliasing: row 0 still unchanged after row 8191 write ───
        accel_read(13'h0, rd128);
        chk128("T4 row0 no-alias", rd128, 128'hDEADBEEF_55667788_11223344_AABBCCDD);

        // ── T5: AXI read back each bank of row 0 ──────────────────────────
        sp_read(17'h0000, rd32); chk32("T5 axi-rd bank0", rd32, 32'hAABBCCDD);
        sp_read(17'h0002, rd32); chk32("T5 axi-rd bank1", rd32, 32'h11223344);
        sp_read(17'h0004, rd32); chk32("T5 axi-rd bank2", rd32, 32'h55667788);
        sp_read(17'h0006, rd32); chk32("T5 axi-rd bank3", rd32, 32'hDEADBEEF);

        // ── T6: Byte-strobe partial write ─────────────────────────────────
        // Write row2 bank0 with full data, then overwrite byte1 only (strb=4'b0010)
        // byte0=0xDD,byte1=0xCC,byte2=0xBB,byte3=0xAA → 0xAABBCCDD
        sp_write(17'h0010, 32'hAABBCCDD, 4'hF);    // row2 bank0 full write
        // overwrite byte1 with 0xEE (bits[15:8])
        sp_write(17'h0010, 32'h0000EE00, 4'b0010);
        sp_read(17'h0010, rd32);
        chk32("T6 byte-strobe b1", rd32, 32'hAABBEEDD);

        // write byte3 only (strb=4'b1000) with 0xFF (bits[31:24])
        sp_write(17'h0010, 32'hFF000000, 4'b1000);
        sp_read(17'h0010, rd32);
        chk32("T6 byte-strobe b3", rd32, 32'hFFBBEEDD);

        // write no bytes (strb=4'b0000) — data should not change
        sp_write(17'h0010, 32'h00000000, 4'b0000);
        sp_read(17'h0010, rd32);
        chk32("T6 byte-strobe none", rd32, 32'hFFBBEEDD);

        // ── T7: Overwrite same location, latest value wins ─────────────────
        sp_write(17'h0018, 32'h11111111, 4'hF);  // row3 bank0
        sp_write(17'h0018, 32'h22222222, 4'hF);  // overwrite
        sp_write(17'h0018, 32'h33333333, 4'hF);  // overwrite again
        sp_read(17'h0018, rd32);
        chk32("T7 overwrite latest", rd32, 32'h33333333);

        // ── T8: Write row 100, bank 3 via addr = 100*8+6 = 806 = 0x326 ────
        sp_write(17'h0326, 32'hBEEFCAFE, 4'hF);
        sp_read(17'h0326, rd32);
        chk32("T8 row100 bank3", rd32, 32'hBEEFCAFE);

        // ── T9: AXI read of large row ─────────────────────────────────────
        sp_read(17'h1FFF8, rd32);  // row 8191, bank0
        chk32("T9 axi-rd last-row", rd32, 32'h12345678);

        // ── T10: Consecutive row writes → distinct rows confirmed ──────────
        sp_write(17'h0008, 32'hAAAAAAAA, 4'hF);  // row1 bank0 (overwrite)
        sp_write(17'h0010, 32'hBBBBBBBB, 4'hF);  // row2 bank0 (overwrite)
        sp_write(17'h0018, 32'hCCCCCCCC, 4'hF);  // row3 bank0 (overwrite)
        // verify row 0 untouched
        accel_read(13'h0, rd128);
        chk32("T10 row0 untouched", rd128[31:0], 32'hAABBCCDD);
        // verify row1,2,3
        accel_read(13'h1, rd128); chk32("T10 row1", rd128[31:0], 32'hAAAAAAAA);
        accel_read(13'h2, rd128); chk32("T10 row2", rd128[31:0], 32'hBBBBBBBB);
        accel_read(13'h3, rd128); chk32("T10 row3", rd128[31:0], 32'hCCCCCCCC);

        // ── T11: BVALID handshake — bvalid stays high until bready ────────
        @(posedge clk);
        s_awaddr = 17'h0020; s_awvalid = 1;
        s_wdata  = 32'hDEAD1234; s_wstrb = 4'hF; s_wvalid = 1;
        @(posedge clk); s_awvalid = 0; s_wvalid = 0;
        @(posedge clk);
        // bvalid should be high; don't assert bready yet
        if (!s_bvalid) begin
            $display("  FAIL  T11 bvalid not raised"); fail_cnt++;
        end else begin
            $display("  PASS  T11 bvalid raised : %0b", s_bvalid); pass_cnt++;
        end
        // deassert after bready
        s_bready = 1;
        @(posedge clk); s_bready = 0;
        @(posedge clk);
        if (s_bvalid) begin
            $display("  FAIL  T11 bvalid should clear"); fail_cnt++;
        end else begin
            $display("  PASS  T11 bvalid cleared"); pass_cnt++;
        end

        $display("\n=== Scratchpad: %0d PASS  %0d FAIL ===\n", pass_cnt, fail_cnt);
        $finish;
    end

    initial begin #2_000_000; $display("WATCHDOG"); $finish; end

endmodule
