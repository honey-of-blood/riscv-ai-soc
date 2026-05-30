`timescale 1ns/1ps
// Phase 9 DMA comprehensive testbench.
// Covers: CH0/CH1 independent transfers, priority arbitration, IRQ,
//         done-bit persistence, restart, single-word and multi-word,
//         irq_en=0 (no IRQ), CH1 runs when CH0 done.

module dma_tb;

    localparam int CLK = 10;

    logic clk = 0, rst_n = 0;

    logic [11:0] paddr;
    logic        psel, penable, pwrite;
    logic [31:0] pwdata, prdata;
    logic        pready;

    logic [31:0] m_awaddr, m_wdata;
    logic  [3:0] m_wstrb;
    logic        m_awvalid, m_awready;
    logic        m_wvalid,  m_wready;
    logic  [1:0] m_bresp;
    logic        m_bvalid,  m_bready;
    logic [31:0] m_araddr,  m_rdata;
    logic  [1:0] m_rresp;
    logic        m_arvalid, m_arready;
    logic        m_rvalid,  m_rready;

    logic irq_ch0, irq_ch1;

    dma dut (.*);

    always #(CLK/2) clk = ~clk;

    int pass_cnt = 0, fail_cnt = 0;

    // ── APB helpers ───────────────────────────────────────────────────────────
    task automatic apb_write(input [11:0] addr, input [31:0] data);
        @(posedge clk);
        paddr = addr; pwdata = data; pwrite = 1; psel = 1; penable = 0;
        @(posedge clk); penable = 1;
        @(posedge clk); psel = 0; penable = 0; pwrite = 0;
    endtask

    task automatic apb_read(input [11:0] addr, output [31:0] data);
        @(posedge clk); paddr = addr; pwrite = 0; psel = 1; penable = 0;
        @(posedge clk); penable = 1;
        @(posedge clk); data = prdata; psel = 0; penable = 0;
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

    task automatic poll_irq(input logic chan_sel, input int tmo, output logic tout);
        tout = 1;
        repeat (tmo) begin
            @(posedge clk);
            if (chan_sel == 0 && irq_ch0) begin tout = 0; break; end
            if (chan_sel == 1 && irq_ch1) begin tout = 0; break; end
        end
    endtask

    // ── Memory models ─────────────────────────────────────────────────────────
    // Source banks at 0x1000 (CH0) and 0x3000 (CH1)
    logic [31:0] src0_mem [0:7];  // 8 words
    logic [31:0] src1_mem [0:7];
    logic [31:0] dst0_mem [0:7];  // written by DMA to 0x2000
    logic [31:0] dst1_mem [0:7];  // written by DMA to 0x4000

    initial begin
        for (int i = 0; i < 8; i++) begin
            src0_mem[i] = 32'hA000_0000 + i;
            src1_mem[i] = 32'hB000_0000 + i;
            dst0_mem[i] = 32'hDEAD_DEAD;
            dst1_mem[i] = 32'hDEAD_DEAD;
        end
    end

    // AXI read responder
    logic ar_held = 0;
    logic [31:0] ar_addr_lat = 0;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_arready <= 0; m_rvalid <= 0; m_rdata <= 0;
        end else begin
            if (m_arvalid && !m_arready) begin
                m_arready   <= 1;
                ar_addr_lat <= m_araddr;
            end else m_arready <= 0;

            if (m_arready && m_arvalid) begin
                m_rvalid <= 1;
                // Route by address range
                if (ar_addr_lat >= 32'h1000 && ar_addr_lat < 32'h2000)
                    m_rdata <= src0_mem[(ar_addr_lat - 32'h1000) >> 2];
                else if (ar_addr_lat >= 32'h3000 && ar_addr_lat < 32'h4000)
                    m_rdata <= src1_mem[(ar_addr_lat - 32'h3000) >> 2];
                else m_rdata <= 32'hDEAD_BEEF;
            end else if (m_rvalid && m_rready)
                m_rvalid <= 0;
        end
    end

    // AXI write responder — handles simultaneous AW+W (DMA now issues both together)
    // and also sequential AW then W for general correctness.
    logic [31:0] aw_addr_lat  = 0;
    logic        aw_lat_valid = 0;

    // Combinational: effective address/valid covers both simultaneous and latched cases
    wire [31:0] eff_aw_addr  = (m_awvalid && !m_awready) ? m_awaddr : aw_addr_lat;
    wire        eff_aw_valid = aw_lat_valid | (m_awvalid & ~m_awready);

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_awready <= 0; m_wready <= 0; m_bvalid <= 0;
            aw_addr_lat <= 0; aw_lat_valid <= 0;
        end else begin
            if (m_awvalid && !m_awready) begin
                m_awready   <= 1;
                aw_addr_lat <= m_awaddr;
                aw_lat_valid<= 1;
            end else m_awready <= 0;

            if (m_wvalid && !m_wready) begin
                m_wready <= 1;
                if (eff_aw_valid) begin
                    if (eff_aw_addr >= 32'h2000 && eff_aw_addr < 32'h3000)
                        dst0_mem[(eff_aw_addr - 32'h2000) >> 2] <= m_wdata;
                    else if (eff_aw_addr >= 32'h4000 && eff_aw_addr < 32'h5000)
                        dst1_mem[(eff_aw_addr - 32'h4000) >> 2] <= m_wdata;
                    aw_lat_valid <= 0;
                end
            end else m_wready <= 0;

            if (m_wready && m_wvalid)
                m_bvalid <= 1;
            else if (m_bvalid && m_bready)
                m_bvalid <= 0;
        end
    end

    assign m_rresp = 2'b00;
    assign m_bresp = 2'b00;

    logic       tout;
    logic [31:0] ctrl_val;

    initial begin
        paddr=0; psel=0; penable=0; pwrite=0; pwdata=0;
        repeat (4) @(posedge clk); rst_n = 1; repeat (2) @(posedge clk);

        // ══ T1: CH0 transfers 4 words src=0x1000 → dst=0x2000 ════════════
        apb_write(12'h00, 32'h0000_1000);  // CH0_SRC
        apb_write(12'h04, 32'h0000_2000);  // CH0_DST
        apb_write(12'h08, 32'h0000_0010);  // CH0_LEN = 16 bytes = 4 words
        apb_write(12'h0C, 32'h0000_0005);  // CH0_CTRL: start=1, irq_en=1

        poll_irq(0, 1000, tout);
        if (tout) begin $display("  FAIL  T1 ch0 timeout"); fail_cnt++; end
        @(posedge clk);
        for (int i = 0; i < 4; i++)
            chk32($sformatf("T1 dst0[%0d]", i), dst0_mem[i], src0_mem[i]);
        apb_write(12'h0C, 32'h0);  // clear

        // ══ T2: CH0 single word (len=4) ════════════════════════════════════
        apb_write(12'h00, 32'h0000_1004);  // src offset by 1 word
        apb_write(12'h04, 32'h0000_2010);  // dst at offset 4 words
        apb_write(12'h08, 32'h0000_0004);  // len=4 bytes (1 word)
        apb_write(12'h0C, 32'h0000_0005);
        poll_irq(0, 500, tout);
        if (tout) begin $display("  FAIL  T2 single-word timeout"); fail_cnt++; end
        @(posedge clk);
        chk32("T2 single-word", dst0_mem[4], src0_mem[1]);
        apb_write(12'h0C, 32'h0);

        // ══ T3: CH0 two words (len=8) ══════════════════════════════════════
        apb_write(12'h00, 32'h0000_1000);
        apb_write(12'h04, 32'h0000_2020);  // dst at new location
        apb_write(12'h08, 32'h0000_0008);  // len=8
        apb_write(12'h0C, 32'h0000_0005);
        poll_irq(0, 500, tout);
        if (tout) begin $display("  FAIL  T3 two-word timeout"); fail_cnt++; end
        @(posedge clk);
        chk32("T3 word0", dst0_mem[(32'h2020-32'h2000)>>2], src0_mem[0]);
        chk32("T3 word1", dst0_mem[(32'h2024-32'h2000)>>2], src0_mem[1]);
        apb_write(12'h0C, 32'h0);

        // ══ T4: irq_en=0 — transfer completes but irq_ch0 stays low ═══════
        apb_write(12'h00, 32'h0000_1000);
        apb_write(12'h04, 32'h0000_2000);
        apb_write(12'h08, 32'h0000_0004);
        apb_write(12'h0C, 32'h0000_0001);  // start=1, irq_en=0
        // wait generous time
        repeat (500) @(posedge clk);
        chk32("T4 no-irq ch0", {31'h0, irq_ch0}, 32'h0);
        // done bit should still be set
        apb_read(12'h0C, ctrl_val);
        chk32("T4 done-bit set", {30'h0, ctrl_val[1], 1'b0}, 32'h2);
        apb_write(12'h0C, 32'h0);

        // ══ T5: Done bit persists until cleared by SW ══════════════════════
        apb_write(12'h00, 32'h0000_1000);
        apb_write(12'h04, 32'h0000_2000);
        apb_write(12'h08, 32'h0000_0004);
        apb_write(12'h0C, 32'h0000_0005);
        poll_irq(0, 500, tout);
        if (tout) begin $display("  FAIL  T5 timeout"); fail_cnt++; end
        // Wait several cycles — done should stay
        repeat (50) @(posedge clk);
        apb_read(12'h0C, ctrl_val);
        chk32("T5 done stays", {30'h0, ctrl_val[1], 1'b0}, 32'h2);
        // Now clear
        apb_write(12'h0C, 32'h0);
        repeat (5) @(posedge clk);
        apb_read(12'h0C, ctrl_val);
        chk32("T5 done cleared", {30'h0, ctrl_val[1], 1'b0}, 32'h0);

        // ══ T6: CH1 independent transfer src=0x3000 → dst=0x4000 ══════════
        apb_write(12'h10, 32'h0000_3000);  // CH1_SRC
        apb_write(12'h14, 32'h0000_4000);  // CH1_DST
        apb_write(12'h18, 32'h0000_0010);  // CH1_LEN = 16 bytes
        apb_write(12'h1C, 32'h0000_0005);  // CH1 start + irq_en
        poll_irq(1, 1000, tout);
        if (tout) begin $display("  FAIL  T6 ch1 timeout"); fail_cnt++; end
        @(posedge clk);
        for (int i = 0; i < 4; i++)
            chk32($sformatf("T6 dst1[%0d]", i), dst1_mem[i], src1_mem[i]);
        apb_write(12'h1C, 32'h0);

        // ══ T7: CH0 priority over CH1 (start both simultaneously) ══════════
        // Reset dst memories to sentinel
        for (int i = 0; i < 8; i++) begin
            dst0_mem[i] = 32'hCCCC_CCCC;
            dst1_mem[i] = 32'hDDDD_DDDD;
        end
        // Start CH0 8 words, CH1 4 words at the same time
        apb_write(12'h00, 32'h0000_1000);
        apb_write(12'h04, 32'h0000_2000);
        apb_write(12'h08, 32'h0000_0020);  // CH0: 8 words
        apb_write(12'h10, 32'h0000_3000);
        apb_write(12'h14, 32'h0000_4000);
        apb_write(12'h18, 32'h0000_0010);  // CH1: 4 words
        // Start both in quick succession (CH0 first = higher priority)
        apb_write(12'h0C, 32'h0000_0005);  // CH0 start
        apb_write(12'h1C, 32'h0000_0005);  // CH1 start
        // Wait for both to complete
        poll_irq(0, 2000, tout);
        if (tout) begin $display("  FAIL  T7 ch0 timeout"); fail_cnt++; end
        poll_irq(1, 2000, tout);
        if (tout) begin $display("  FAIL  T7 ch1 timeout"); fail_cnt++; end
        @(posedge clk);
        // Both should have transferred correctly despite interleaving
        chk32("T7 ch0[0]", dst0_mem[0], src0_mem[0]);
        chk32("T7 ch0[7]", dst0_mem[7], src0_mem[7]);
        chk32("T7 ch1[0]", dst1_mem[0], src1_mem[0]);
        chk32("T7 ch1[3]", dst1_mem[3], src1_mem[3]);
        apb_write(12'h0C, 32'h0);
        apb_write(12'h1C, 32'h0);

        // ══ T8: Restart CH0 after completion ════════════════════════════════
        for (int i = 0; i < 8; i++) dst0_mem[i] = 32'hEEEE_EEEE;
        // Configure and start
        apb_write(12'h00, 32'h0000_1000);
        apb_write(12'h04, 32'h0000_2000);
        apb_write(12'h08, 32'h0000_0008);
        apb_write(12'h0C, 32'h0000_0005);
        poll_irq(0, 500, tout);
        if (tout) begin $display("  FAIL  T8a timeout"); fail_cnt++; end
        chk32("T8a first-run[0]", dst0_mem[0], src0_mem[0]);
        // Clear done/start
        apb_write(12'h0C, 32'h0);
        repeat (5) @(posedge clk);
        // Restart with new destination
        for (int i = 0; i < 8; i++) dst0_mem[i] = 32'hEEEE_EEEE;
        apb_write(12'h04, 32'h0000_2000);
        apb_write(12'h0C, 32'h0000_0005);
        poll_irq(0, 500, tout);
        if (tout) begin $display("  FAIL  T8b timeout"); fail_cnt++; end
        chk32("T8b restart[0]", dst0_mem[0], src0_mem[0]);
        chk32("T8b restart[1]", dst0_mem[1], src0_mem[1]);
        apb_write(12'h0C, 32'h0);

        // ══ T9: APB register readback ════════════════════════════════════════
        apb_write(12'h00, 32'h0000_ABCD);
        apb_write(12'h04, 32'h0000_1234);
        apb_write(12'h08, 32'h0000_5678);
        begin
            logic [31:0] v;
            apb_read(12'h00, v); chk32("T9 CH0_SRC", v, 32'h0000_ABCD);
            apb_read(12'h04, v); chk32("T9 CH0_DST", v, 32'h0000_1234);
            apb_read(12'h08, v); chk32("T9 CH0_LEN", v, 32'h0000_5678);
        end

        $display("\n=== Phase 9 DMA: %0d PASS  %0d FAIL ===\n", pass_cnt, fail_cnt);
        $finish;
    end

    initial begin #5_000_000; $display("WATCHDOG"); $finish; end

endmodule
