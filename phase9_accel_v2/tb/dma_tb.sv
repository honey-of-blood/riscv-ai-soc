`timescale 1ns/1ps
// Phase 9 DMA unit testbench.

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

    dma dut (
        .clk(clk), .rst_n(rst_n),
        .paddr(paddr), .psel(psel), .penable(penable),
        .pwrite(pwrite), .pwdata(pwdata),
        .prdata(prdata), .pready(pready),
        .m_awaddr(m_awaddr), .m_awvalid(m_awvalid), .m_awready(m_awready),
        .m_wdata(m_wdata),   .m_wstrb(m_wstrb),
        .m_wvalid(m_wvalid), .m_wready(m_wready),
        .m_bresp(m_bresp),   .m_bvalid(m_bvalid),   .m_bready(m_bready),
        .m_araddr(m_araddr), .m_arvalid(m_arvalid),  .m_arready(m_arready),
        .m_rdata(m_rdata),   .m_rresp(m_rresp),
        .m_rvalid(m_rvalid), .m_rready(m_rready),
        .irq_ch0(irq_ch0),   .irq_ch1(irq_ch1)
    );

    always #(CLK/2) clk = ~clk;

    int pass_cnt = 0, fail_cnt = 0;

    task automatic apb_write(input [11:0] addr, input [31:0] data);
        @(posedge clk);
        paddr = addr; pwdata = data; pwrite = 1; psel = 1; penable = 0;
        @(posedge clk);
        penable = 1;
        @(posedge clk);
        psel = 0; penable = 0; pwrite = 0;
    endtask

    task automatic apb_read(input [11:0] addr, output [31:0] data);
        @(posedge clk);
        paddr = addr; pwrite = 0; psel = 1; penable = 0;
        @(posedge clk);
        penable = 1;
        @(posedge clk);
        data = prdata;
        psel = 0; penable = 0;
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

    // Source and destination memory models
    logic [31:0] src_mem [0:3];
    logic [31:0] dst_mem [0:3];

    initial begin
        src_mem[0] = 32'hCAFE_BABE;
        src_mem[1] = 32'hDEAD_BEEF;
        src_mem[2] = 32'h1234_5678;
        src_mem[3] = 32'hAABB_CCDD;
        dst_mem[0] = 32'h0;
        dst_mem[1] = 32'h0;
        dst_mem[2] = 32'h0;
        dst_mem[3] = 32'h0;
    end

    // AXI read responder (src memory at base 0x1000)
    logic ar_pending = 0;
    logic [31:0] ar_addr_lat = 0;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_arready <= 0; m_rvalid <= 0; m_rdata <= 0;
        end else begin
            if (m_arvalid && !m_arready) begin
                m_arready   <= 1;
                ar_addr_lat <= m_araddr;
            end else begin
                m_arready <= 0;
            end
            if (m_arready && m_arvalid) begin
                m_rvalid <= 1;
                m_rdata  <= src_mem[(ar_addr_lat - 32'h1000) >> 2];
            end else if (m_rvalid && m_rready) begin
                m_rvalid <= 0;
            end
        end
    end

    // AXI write responder (dst memory at base 0x2000)
    logic aw_pending = 0;
    logic [31:0] aw_addr_lat = 0;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            m_awready <= 0; m_wready <= 0; m_bvalid <= 0;
        end else begin
            if (m_awvalid && !m_awready) begin
                m_awready   <= 1;
                aw_addr_lat <= m_awaddr;
            end else begin
                m_awready <= 0;
            end
            if (m_wvalid && !m_wready) begin
                m_wready <= 1;
                dst_mem[(aw_addr_lat - 32'h2000) >> 2] <= m_wdata;
            end else begin
                m_wready <= 0;
            end
            if (m_wready && m_wvalid) begin
                m_bvalid <= 1;
            end else if (m_bvalid && m_bready) begin
                m_bvalid <= 0;
            end
        end
    end

    assign m_rresp = 2'b00;
    assign m_bresp = 2'b00;

    initial begin
        paddr=0; psel=0; penable=0; pwrite=0; pwdata=0;

        repeat (4) @(posedge clk);
        rst_n = 1;
        repeat (2) @(posedge clk);

        // ── Test 1: CH0 transfers 4 words from 0x1000 to 0x2000 ──────────
        apb_write(12'h00, 32'h0000_1000);  // CH0_SRC
        apb_write(12'h04, 32'h0000_2000);  // CH0_DST
        apb_write(12'h08, 32'h0000_0010);  // CH0_LEN = 16 bytes
        apb_write(12'h0C, 32'h0000_0005);  // CH0_CTRL: start=1, irq_en=1

        // Wait for irq_ch0
        begin
            logic done;
            done = 0;
            repeat (1000) begin
                @(posedge clk);
                if (irq_ch0) begin done = 1; break; end
            end
            if (!done) begin
                $display("  FAIL  DMA ch0: timeout waiting for irq");
                fail_cnt++;
            end
        end

        @(posedge clk);
        chk32("ch0 dst[0]", dst_mem[0], src_mem[0]);
        chk32("ch0 dst[1]", dst_mem[1], src_mem[1]);
        chk32("ch0 dst[2]", dst_mem[2], src_mem[2]);
        chk32("ch0 dst[3]", dst_mem[3], src_mem[3]);

        begin
            logic [31:0] cv;
            apb_read(12'h0C, cv);
            chk32("ch0 done-bit", {30'h0, cv[1], 1'b0}, 32'h2);
        end

        // Clear start/done
        apb_write(12'h0C, 32'h0);

        $display("\n=== Phase 9 DMA: %0d PASS  %0d FAIL ===\n", pass_cnt, fail_cnt);
        $finish;
    end

    initial begin #500_000; $display("WATCHDOG"); $finish; end

endmodule
