`timescale 1ns/1ps
// Converts 4-beat AXI4 INCR bursts (from cache_top) into sequential
// AXI4-Lite single-beat transactions (to the crossbar).
//
// Assumptions:
//   - AWLEN = ARLEN = 3 (4-beat bursts only)
//   - INCR burst; each beat addresses base + beat*4
//   - Write and read channels are never active simultaneously (cache guarantee)
module axi4_burst_to_lite (
    input  logic clk,
    input  logic rst_n,

    // ── AXI4 burst slave (from cache_top) ────────────────────────────────────
    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,
    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wlast,
    input  logic        s_wvalid,
    output logic        s_wready,
    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,

    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rlast,
    output logic        s_rvalid,
    input  logic        s_rready,

    // ── AXI4-Lite master (to crossbar) ───────────────────────────────────────
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
    output logic        m_rready
);

// ── Write state machine ───────────────────────────────────────────────────────
// Per-beat: accept W from cache → issue AW+W to Lite → wait B → next beat.
// After 4 beats: return aggregated B to cache.

typedef enum logic [2:0] {
    WR_IDLE,
    WR_W_WAIT,    // waiting for W beat from cache
    WR_AXI_ADDR, // issuing AW+W to Lite slave, waiting both handshakes
    WR_AXI_RESP, // waiting for B from Lite slave
    WR_RESP      // returning aggregated B to cache
} wr_state_t;

wr_state_t wr_state;
logic [31:0] wr_base;
logic  [1:0] wr_beat;
logic  [1:0] wr_bresp_agg;
logic [31:0] wr_wdata_r;
logic  [3:0] wr_wstrb_r;
logic        aw_done, w_done;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_state     <= WR_IDLE;
        wr_base      <= '0;
        wr_beat      <= '0;
        wr_bresp_agg <= '0;
        wr_wdata_r   <= '0;
        wr_wstrb_r   <= '0;
        aw_done      <= '0;
        w_done       <= '0;
    end else begin
        case (wr_state)
            WR_IDLE: begin
                if (s_awvalid) begin
                    wr_base      <= s_awaddr;
                    wr_beat      <= '0;
                    wr_bresp_agg <= '0;
                    wr_state     <= WR_W_WAIT;
                end
            end

            WR_W_WAIT: begin
                if (s_wvalid) begin
                    wr_wdata_r <= s_wdata;
                    wr_wstrb_r <= s_wstrb;
                    aw_done    <= '0;
                    w_done     <= '0;
                    wr_state   <= WR_AXI_ADDR;
                end
            end

            WR_AXI_ADDR: begin
                if (m_awready && !aw_done) aw_done <= 1'b1;
                if (m_wready  && !w_done)  w_done  <= 1'b1;
                // Transition when both channels are accepted (use current-cycle signals)
                if ((aw_done || m_awready) && (w_done || m_wready))
                    wr_state <= WR_AXI_RESP;
            end

            WR_AXI_RESP: begin
                if (m_bvalid) begin
                    wr_bresp_agg <= wr_bresp_agg | m_bresp;
                    if (wr_beat == 2'd3) begin
                        wr_state <= WR_RESP;
                    end else begin
                        wr_beat  <= wr_beat + 1'b1;
                        wr_state <= WR_W_WAIT;
                    end
                end
            end

            WR_RESP: begin
                if (s_bready) wr_state <= WR_IDLE;
            end

            default: wr_state <= WR_IDLE;
        endcase
    end
end

// beat offset: wr_beat * 4 (Icarus-safe — no bit-select in always_comb)
logic [31:0] wr_beat_off;
assign wr_beat_off = {28'b0, wr_beat, 2'b0};

always_comb begin
    s_awready = (wr_state == WR_IDLE) && s_awvalid;
    s_wready  = (wr_state == WR_W_WAIT);
    s_bvalid  = (wr_state == WR_RESP);
    s_bresp   = wr_bresp_agg;

    m_awvalid = (wr_state == WR_AXI_ADDR) && !aw_done;
    m_awaddr  = wr_base + wr_beat_off;
    m_wvalid  = (wr_state == WR_AXI_ADDR) && !w_done;
    m_wdata   = wr_wdata_r;
    m_wstrb   = wr_wstrb_r;
    m_bready  = (wr_state == WR_AXI_RESP);
end

// ── Read state machine ────────────────────────────────────────────────────────
// Per-beat: issue AR to Lite → wait R → return to cache → next beat.
// Assert RLAST on final beat.

typedef enum logic [1:0] {
    RD_IDLE,
    RD_AR,    // issuing AR to Lite slave
    RD_DATA   // waiting for R from Lite, forwarding to cache
} rd_state_t;

rd_state_t rd_state;
logic [31:0] rd_base;
logic  [1:0] rd_beat;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rd_state <= RD_IDLE;
        rd_base  <= '0;
        rd_beat  <= '0;
    end else begin
        case (rd_state)
            RD_IDLE: begin
                if (s_arvalid) begin
                    rd_base  <= s_araddr;
                    rd_beat  <= '0;
                    rd_state <= RD_AR;
                end
            end

            RD_AR: begin
                if (m_arready) rd_state <= RD_DATA;
            end

            RD_DATA: begin
                if (m_rvalid && s_rready) begin
                    if (rd_beat == 2'd3)
                        rd_state <= RD_IDLE;
                    else begin
                        rd_beat  <= rd_beat + 1'b1;
                        rd_state <= RD_AR;
                    end
                end
            end

            default: rd_state <= RD_IDLE;
        endcase
    end
end

logic [31:0] rd_beat_off;
assign rd_beat_off = {28'b0, rd_beat, 2'b0};

always_comb begin
    s_arready = (rd_state == RD_IDLE) && s_arvalid;

    m_arvalid = (rd_state == RD_AR);
    m_araddr  = rd_base + rd_beat_off;

    s_rvalid  = (rd_state == RD_DATA) && m_rvalid;
    s_rdata   = m_rdata;
    s_rresp   = m_rresp;
    s_rlast   = (rd_state == RD_DATA) && (rd_beat == 2'd3) && m_rvalid;

    m_rready  = (rd_state == RD_DATA) && s_rready;
end

endmodule
