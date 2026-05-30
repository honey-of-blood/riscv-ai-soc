`timescale 1ns/1ps
// AXI4-Lite 32-bit → AXI4 128-bit data-width converter.
//
// Bridges the SoC's 32-bit AXI4-Lite memory port to a 128-bit AXI4 memory
// controller (Xilinx MIG 7-series default data width).
//
// Each 32-bit transaction maps to one 128-bit transaction with byte enables
// placed in the correct lane (addr[3:2] selects lane 0-3 within the 128-bit
// word).  AWLEN=0 (single beat), AWSIZE=4 (16 bytes), AWBURST=INCR.
//
// This is a 1:1 beat converter — it does not pack multiple 32-bit accesses
// into a single 128-bit beat.  Bandwidth is 1/4 of peak DDR3 throughput but
// the logic is simple and correct.

module axi_width_32to128 (
    input  logic         clk,
    input  logic         rst_n,

    // ── Slave: AXI4-Lite 32-bit (from soc_top m_mem_*) ──────────────────────
    input  logic [31:0]  s_awaddr,
    input  logic         s_awvalid,
    output logic         s_awready,
    input  logic [31:0]  s_wdata,
    input  logic  [3:0]  s_wstrb,
    input  logic         s_wvalid,
    output logic         s_wready,
    output logic  [1:0]  s_bresp,
    output logic         s_bvalid,
    input  logic         s_bready,

    input  logic [31:0]  s_araddr,
    input  logic         s_arvalid,
    output logic         s_arready,
    output logic [31:0]  s_rdata,
    output logic  [1:0]  s_rresp,
    output logic         s_rvalid,
    input  logic         s_rready,

    // ── Master: AXI4 128-bit (to MIG) ────────────────────────────────────────
    output logic [29:0]  m_awaddr,   // 128-bit word address = s_awaddr[31:4] >> 2
    output logic  [7:0]  m_awlen,    // 0 = single beat
    output logic  [2:0]  m_awsize,   // 4 = 16 bytes
    output logic  [1:0]  m_awburst,  // INCR
    output logic         m_awvalid,
    input  logic         m_awready,
    output logic [127:0] m_wdata,
    output logic  [15:0] m_wstrb,
    output logic         m_wlast,
    output logic         m_wvalid,
    input  logic         m_wready,
    input  logic  [1:0]  m_bresp,
    input  logic         m_bvalid,
    output logic         m_bready,

    output logic [29:0]  m_araddr,
    output logic  [7:0]  m_arlen,
    output logic  [2:0]  m_arsize,
    output logic  [1:0]  m_arburst,
    output logic         m_arvalid,
    input  logic         m_arready,
    input  logic [127:0] m_rdata,
    input  logic  [1:0]  m_rresp,
    input  logic         m_rlast,
    input  logic         m_rvalid,
    output logic         m_rready
);

    // Fixed AXI4 burst parameters
    assign m_awlen   = 8'd0;
    assign m_awsize  = 3'd4;
    assign m_awburst = 2'b01;
    assign m_wlast   = 1'b1;
    assign m_arlen   = 8'd0;
    assign m_arsize  = 3'd4;
    assign m_arburst = 2'b01;

    // ── Write channel ─────────────────────────────────────────────────────────
    typedef enum logic [1:0] { WR_IDLE, WR_AW, WR_W, WR_RESP } wr_st_t;
    wr_st_t wst;

    logic [31:0] aw_r;
    logic [31:0] wd_r;
    logic  [3:0] ws_r;
    logic  [1:0] aw_lane;
    assign aw_lane  = aw_r[3:2];
    assign m_awaddr = aw_r[31:2];   // byte addr → 32-bit word addr → top 30 bits

    always_comb begin
        m_wdata = 128'h0;
        m_wstrb = 16'h0;
        m_wdata[aw_lane*32 +: 32] = wd_r;
        m_wstrb[aw_lane*4  +:  4] = ws_r;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wst <= WR_IDLE;
            s_awready <= 1'b0; s_wready <= 1'b0;
            s_bvalid  <= 1'b0; s_bresp  <= 2'b0;
            m_awvalid <= 1'b0; m_wvalid <= 1'b0; m_bready <= 1'b0;
            aw_r <= '0; wd_r <= '0; ws_r <= '0;
        end else begin
            case (wst)
            WR_IDLE: begin
                s_awready <= 1'b1; s_wready <= 1'b1;
                if (s_awvalid && s_wvalid) begin
                    aw_r <= s_awaddr; wd_r <= s_wdata; ws_r <= s_wstrb;
                    s_awready <= 1'b0; s_wready <= 1'b0;
                    m_awvalid <= 1'b1; m_wvalid <= 1'b1;
                    wst <= WR_RESP;
                end else if (s_awvalid) begin
                    aw_r <= s_awaddr; s_awready <= 1'b0; wst <= WR_W;
                end else if (s_wvalid) begin
                    wd_r <= s_wdata; ws_r <= s_wstrb; s_wready <= 1'b0; wst <= WR_AW;
                end
            end
            WR_AW: begin    // waiting for AW
                s_awready <= 1'b1;
                if (s_awvalid) begin
                    aw_r <= s_awaddr; s_awready <= 1'b0;
                    m_awvalid <= 1'b1; m_wvalid <= 1'b1; wst <= WR_RESP;
                end
            end
            WR_W: begin     // waiting for W
                s_wready <= 1'b1;
                if (s_wvalid) begin
                    wd_r <= s_wdata; ws_r <= s_wstrb; s_wready <= 1'b0;
                    m_awvalid <= 1'b1; m_wvalid <= 1'b1; wst <= WR_RESP;
                end
            end
            WR_RESP: begin
                if (m_awready) m_awvalid <= 1'b0;
                if (m_wready)  m_wvalid  <= 1'b0;
                if (!m_awvalid && !m_wvalid && !m_bready)
                    m_bready <= 1'b1;
                if (m_bvalid && m_bready) begin
                    m_bready <= 1'b0;
                    s_bvalid <= 1'b1;
                    s_bresp  <= m_bresp;
                end
                if (s_bvalid && s_bready) begin
                    s_bvalid <= 1'b0; wst <= WR_IDLE;
                end
            end
            endcase
        end
    end

    // ── Read channel ──────────────────────────────────────────────────────────
    typedef enum logic [1:0] { RD_IDLE, RD_WAIT } rd_st_t;
    rd_st_t rdst;

    logic [31:0] ar_r;
    logic  [1:0] rd_lane;
    assign rd_lane  = ar_r[3:2];
    assign m_araddr = ar_r[31:2];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rdst <= RD_IDLE;
            s_arready <= 1'b0; s_rvalid <= 1'b0; s_rresp <= 2'b0;
            m_arvalid <= 1'b0; m_rready <= 1'b0;
            ar_r <= '0;
        end else begin
            case (rdst)
            RD_IDLE: begin
                s_arready <= 1'b1;
                if (s_arvalid) begin
                    ar_r <= s_araddr; s_arready <= 1'b0;
                    m_arvalid <= 1'b1; rdst <= RD_WAIT;
                end
            end
            RD_WAIT: begin
                if (m_arready) m_arvalid <= 1'b0;
                if (m_rvalid && !s_rvalid) begin
                    m_rready <= 1'b1;
                    s_rvalid <= 1'b1;
                    s_rdata  <= m_rdata[rd_lane*32 +: 32];
                    s_rresp  <= m_rresp;
                end else m_rready <= 1'b0;
                if (s_rvalid && s_rready) begin
                    s_rvalid <= 1'b0; rdst <= RD_IDLE;
                end
            end
            endcase
        end
    end

endmodule
