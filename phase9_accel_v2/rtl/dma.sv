`timescale 1ns/1ps
// 2-channel DMA engine.
//
// Config (APB slave) — accessible at 0x1000_7xxx via APB demux port 7:
//   0x00  CH0_SRC_LO   channel 0 source address
//   0x04  CH0_DST_LO   channel 0 destination address
//   0x08  CH0_LEN      transfer length in bytes (must be word-aligned)
//   0x0C  CH0_CTRL     [0]=start  [1]=done(RO)  [2]=irq_enable
//   0x10  CH1_SRC_LO
//   0x14  CH1_DST_LO
//   0x18  CH1_LEN
//   0x1C  CH1_CTRL
//
// AXI4-Lite master — issues reads from SRC, writes to DST, word (32-bit) at a
// time.  Both channels share one AXI master with simple priority arbitration:
// channel 0 has priority over channel 1.
//
// IRQ fires per channel when done && irq_enable.
// Software clears done by writing CH_CTRL[0]=0.

module dma (
    input  logic clk,
    input  logic rst_n,

    // ── APB slave (config, connected to APB demux port 7) ─────────────────
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // ── AXI4-Lite master (data transfers) ─────────────────────────────────
    output logic [31:0] m_awaddr,
    output logic        m_awvalid,
    input  logic        m_awready,
    output logic [31:0] m_wdata,
    output logic  [3:0] m_wstrb,
    output logic        m_wvalid,
    input  logic        m_wready,
    input  logic  [1:0] m_bresp,
    input  logic        m_bvalid,
    output logic        m_bready,

    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [31:0] m_rdata,
    input  logic  [1:0] m_rresp,
    input  logic        m_rvalid,
    output logic        m_rready,

    // ── Interrupt outputs (one per channel) ───────────────────────────────
    output logic irq_ch0,
    output logic irq_ch1
);

    // ── Config registers ──────────────────────────────────────────────────
    logic [31:0] src  [0:1];
    logic [31:0] dst  [0:1];
    logic [31:0] len  [0:1];   // remaining bytes
    logic        start[0:1];
    logic        done [0:1];
    logic        irq_en[0:1];

    // APB interface — single-cycle pready
    assign pready = 1'b1;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (int ch = 0; ch < 2; ch++) begin
                src[ch] <= '0; dst[ch] <= '0; len[ch] <= '0;
                start[ch] <= 1'b0; irq_en[ch] <= 1'b0;
            end
        end else if (psel && penable && pwrite) begin
            case (paddr[4:0])
                5'h00: src[0]    <= pwdata;
                5'h04: dst[0]    <= pwdata;
                5'h08: len[0]    <= pwdata;
                5'h0C: begin
                    start[0]  <= pwdata[0];
                    irq_en[0] <= pwdata[2];
                    if (!pwdata[0]) done[0] <= 1'b0;  // SW clears done
                end
                5'h10: src[1]    <= pwdata;
                5'h14: dst[1]    <= pwdata;
                5'h18: len[1]    <= pwdata;
                5'h1C: begin
                    start[1]  <= pwdata[0];
                    irq_en[1] <= pwdata[2];
                    if (!pwdata[0]) done[1] <= 1'b0;
                end
                default: ;
            endcase
        end
    end

    always_comb begin
        case (paddr[4:0])
            5'h0C: prdata = {29'h0, irq_en[0], done[0], start[0]};
            5'h1C: prdata = {29'h0, irq_en[1], done[1], start[1]};
            5'h00: prdata = src[0];
            5'h04: prdata = dst[0];
            5'h08: prdata = len[0];
            5'h10: prdata = src[1];
            5'h14: prdata = dst[1];
            5'h18: prdata = len[1];
            default: prdata = 32'h0;
        endcase
    end

    assign irq_ch0 = done[0] & irq_en[0];
    assign irq_ch1 = done[1] & irq_en[1];

    // ── DMA transfer FSM ──────────────────────────────────────────────────
    // AW and W are issued simultaneously so the slave sees both valid in the
    // same cycle — required by slaves that check (awvalid && wvalid) together
    // (AXI4-Lite allows this and our scratchpad requires it).
    typedef enum logic [2:0] {
        IDLE, ARB, READ_ADDR, READ_DATA, WRITE, WRITE_RESP
    } dma_state_t;
    dma_state_t dstate;

    logic        active_ch;      // which channel is currently transferring
    logic [31:0] cur_src, cur_dst;
    logic [31:0] cur_len;
    logic [31:0] read_buf;
    logic [31:0] ch_src_r [0:1];  // running src/dst pointers during transfer
    logic [31:0] ch_dst_r [0:1];
    logic [31:0] ch_len_r [0:1];  // remaining bytes during transfer

    // AXI master outputs — AW and W driven simultaneously in WRITE state
    always_comb begin
        m_awaddr  = cur_dst;
        m_awvalid = (dstate == WRITE);
        m_wdata   = read_buf;
        m_wstrb   = 4'hF;
        m_wvalid  = (dstate == WRITE);
        m_bready  = (dstate == WRITE_RESP);
        m_araddr  = cur_src;
        m_arvalid = (dstate == READ_ADDR);
        m_rready  = (dstate == READ_DATA);
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dstate    <= IDLE;
            active_ch <= 1'b0;
            cur_src   <= '0;
            cur_dst   <= '0;
            cur_len   <= '0;
            read_buf  <= '0;
            for (int ch = 0; ch < 2; ch++) begin
                ch_src_r[ch] <= '0;
                ch_dst_r[ch] <= '0;
                ch_len_r[ch] <= '0;
                done[ch]     <= 1'b0;
            end
        end else begin
            case (dstate)

            IDLE: dstate <= ARB;

            ARB: begin
                // Priority: ch0 over ch1
                if (start[0] && !done[0] && ch_len_r[0] == 0) begin
                    active_ch    <= 1'b0;
                    ch_src_r[0]  <= src[0];
                    ch_dst_r[0]  <= dst[0];
                    ch_len_r[0]  <= len[0];
                    cur_src      <= src[0];
                    cur_dst      <= dst[0];
                    cur_len      <= len[0];
                    dstate       <= READ_ADDR;
                end else if (start[0] && !done[0] && ch_len_r[0] > 0) begin
                    active_ch <= 1'b0;
                    cur_src   <= ch_src_r[0];
                    cur_dst   <= ch_dst_r[0];
                    cur_len   <= ch_len_r[0];
                    dstate    <= READ_ADDR;
                end else if (start[1] && !done[1] && ch_len_r[1] == 0) begin
                    active_ch    <= 1'b1;
                    ch_src_r[1]  <= src[1];
                    ch_dst_r[1]  <= dst[1];
                    ch_len_r[1]  <= len[1];
                    cur_src      <= src[1];
                    cur_dst      <= dst[1];
                    cur_len      <= len[1];
                    dstate       <= READ_ADDR;
                end else if (start[1] && !done[1] && ch_len_r[1] > 0) begin
                    active_ch <= 1'b1;
                    cur_src   <= ch_src_r[1];
                    cur_dst   <= ch_dst_r[1];
                    cur_len   <= ch_len_r[1];
                    dstate    <= READ_ADDR;
                end else begin
                    dstate <= IDLE;
                end
            end

            READ_ADDR: if (m_arready) dstate <= READ_DATA;

            READ_DATA: begin
                if (m_rvalid) begin
                    read_buf <= m_rdata;
                    dstate   <= WRITE;
                end
            end

            WRITE: if (m_awready && m_wready) dstate <= WRITE_RESP;

            WRITE_RESP: begin
                if (m_bvalid) begin
                    // Advance pointers
                    ch_src_r[active_ch] <= cur_src + 4;
                    ch_dst_r[active_ch] <= cur_dst + 4;
                    if (cur_len <= 4) begin
                        ch_len_r[active_ch] <= 32'h0;
                        done[active_ch]     <= 1'b1;
                        dstate              <= IDLE;
                    end else begin
                        ch_len_r[active_ch] <= cur_len - 4;
                        dstate              <= ARB;
                    end
                end
            end

            default: dstate <= IDLE;
            endcase
        end
    end

endmodule
