`timescale 1ns/1ps
// 2-way set-associative cache controller with LRU replacement.
// External AXI and CPU interfaces are identical to cache_controller.sv so
// cache_top.sv requires only internal sub-module substitution.
//
// Address map (same as 1-way):
//   addr[31:10] = tag  (22 bits)
//   addr[ 9: 4] = index (6 bits → 64 sets)
//   addr[ 3: 2] = word offset (2 bits)
//
// Hit: both ways checked simultaneously; LRU updated to mark hitting way MRU.
// Miss: LRU way evicted (dirty → WRITE_BACK first, then FILL).
// SECDED: errors surfaced via ecc_error_i from data array (sticky in req).
module cache_controller_2way (
    input  logic        clk,
    input  logic        rst,

    // ── CPU interface (same as cache_controller.sv) ───────────────────────
    input  logic        cpu_re_i,
    input  logic        cpu_we_i,
    input  logic [31:0] cpu_addr_i,
    input  logic [31:0] cpu_wdata_i,
    input  logic [3:0]  cpu_be_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,

    // ── Tag array interface (2-way) ───────────────────────────────────────
    output logic        tag_we0_o,
    output logic        tag_we1_o,
    output logic        tag_lru_we_o,
    output logic [5:0]  tag_idx_o,
    output logic [21:0] tag_tag_o,
    output logic        tag_valid_o,
    output logic        tag_dirty_o,
    output logic        tag_lru_o,
    input  logic [21:0] tag_tag0_i,   input logic tag_valid0_i, tag_dirty0_i,
    input  logic [21:0] tag_tag1_i,   input logic tag_valid1_i, tag_dirty1_i,
    input  logic        tag_lru_i,

    // ── Data array interface (2-way) ──────────────────────────────────────
    output logic        data_we_o,
    output logic        data_way_o,
    output logic [5:0]  data_idx_o,
    output logic [1:0]  data_word_o,
    output logic [3:0]  data_be_o,
    output logic [31:0] data_wdata_o,
    input  logic [31:0] data_way0_w0_i, data_way0_w1_i, data_way0_w2_i, data_way0_w3_i,
    input  logic [31:0] data_way1_w0_i, data_way1_w1_i, data_way1_w2_i, data_way1_w3_i,
    input  logic        ecc_error_i,

    // ── AXI4 write channel (WRITE_BACK dirty eviction) ────────────────────
    output logic        m_axi_awvalid_o,
    input  logic        m_axi_awready_i,
    output logic [31:0] m_axi_awaddr_o,
    output logic [7:0]  m_axi_awlen_o,
    output logic [2:0]  m_axi_awsize_o,
    output logic [1:0]  m_axi_awburst_o,

    output logic        m_axi_wvalid_o,
    input  logic        m_axi_wready_i,
    output logic [31:0] m_axi_wdata_o,
    output logic [3:0]  m_axi_wstrb_o,
    output logic        m_axi_wlast_o,

    input  logic        m_axi_bvalid_i,
    output logic        m_axi_bready_o,

    // ── AXI4 read channel (FILL) ──────────────────────────────────────────
    output logic        m_axi_arvalid_o,
    input  logic        m_axi_arready_i,
    output logic [31:0] m_axi_araddr_o,
    output logic [7:0]  m_axi_arlen_o,
    output logic [2:0]  m_axi_arsize_o,
    output logic [1:0]  m_axi_arburst_o,

    input  logic        m_axi_rvalid_i,
    output logic        m_axi_rready_o,
    input  logic [31:0] m_axi_rdata_i,
    input  logic        m_axi_rlast_i
);

    localparam [2:0]
        IDLE       = 3'd0,
        TAG_CHECK  = 3'd1,
        HIT        = 3'd2,
        WRITE_BACK = 3'd3,
        FILL       = 3'd4,
        RESPOND    = 3'd5;

    logic [2:0] state, next_state;

    // Registered CPU request
    logic [31:0] req_addr, req_wdata;
    logic [3:0]  req_be;
    logic        req_we, req_re;

    // Address fields from registered request (outside always_comb — Icarus rule)
    logic [21:0] req_tag;
    logic [5:0]  req_idx;
    logic [1:0]  req_woff;
    logic [31:0] fill_addr, evict_addr;

    assign req_tag   = req_addr[31:10];
    assign req_idx   = req_addr[9:4];
    assign req_woff  = req_addr[3:2];
    assign fill_addr = {req_tag,    req_idx, 4'b0};

    logic [5:0] cpu_addr_idx;
    assign cpu_addr_idx = cpu_addr_i[9:4];

    logic [21:0] evict_tag;
    assign evict_addr = {evict_tag, req_idx, 4'b0};

    // Hit detection
    logic hit0, hit1, cache_hit;
    assign hit0      = tag_valid0_i && (tag_tag0_i == req_tag);
    assign hit1      = tag_valid1_i && (tag_tag1_i == req_tag);
    assign cache_hit = hit0 | hit1;

    // Which way was hit / LRU way to evict
    logic hit_way;   // 0=way0 hit, 1=way1 hit
    logic fill_way;  // way to fill into (LRU at TAG_CHECK time)
    assign hit_way = hit1;  // if both hit (impossible in correct cache) way1 wins

    // AXI burst counter
    logic [1:0] burst_cnt;

    // AW handshake tracker
    logic aw_done;

    // Selected hit data (combinational from data array, based on hit_way)
    logic [31:0] hit_rdata_way0, hit_rdata_way1, hit_rdata;
    always_comb begin
        case (req_woff)
            2'b00:   hit_rdata_way0 = data_way0_w0_i;
            2'b01:   hit_rdata_way0 = data_way0_w1_i;
            2'b10:   hit_rdata_way0 = data_way0_w2_i;
            default: hit_rdata_way0 = data_way0_w3_i;
        endcase
        case (req_woff)
            2'b00:   hit_rdata_way1 = data_way1_w0_i;
            2'b01:   hit_rdata_way1 = data_way1_w1_i;
            2'b10:   hit_rdata_way1 = data_way1_w2_i;
            default: hit_rdata_way1 = data_way1_w3_i;
        endcase
    end
    assign hit_rdata = hit_way ? hit_rdata_way1 : hit_rdata_way0;

    // Write-back data mux — evict way's data
    logic [31:0] wb_wdata_way0, wb_wdata_way1, wb_wdata;
    always_comb begin
        case (burst_cnt)
            2'b00:   wb_wdata_way0 = data_way0_w0_i;
            2'b01:   wb_wdata_way0 = data_way0_w1_i;
            2'b10:   wb_wdata_way0 = data_way0_w2_i;
            default: wb_wdata_way0 = data_way0_w3_i;
        endcase
        case (burst_cnt)
            2'b00:   wb_wdata_way1 = data_way1_w0_i;
            2'b01:   wb_wdata_way1 = data_way1_w1_i;
            2'b10:   wb_wdata_way1 = data_way1_w2_i;
            default: wb_wdata_way1 = data_way1_w3_i;
        endcase
    end
    // evict the LRU way
    assign wb_wdata = fill_way ? wb_wdata_way1 : wb_wdata_way0;

    // ── State register ────────────────────────────────────────────────────
    always_ff @(posedge clk or posedge rst) begin
        if (rst) state <= IDLE;
        else     state <= next_state;
    end

    // ── Datapath registers ────────────────────────────────────────────────
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            req_addr  <= '0; req_wdata <= '0; req_be   <= '0;
            req_we    <= '0; req_re    <= '0;
            evict_tag <= '0; burst_cnt <= '0; aw_done  <= '0;
            fill_way  <= '0;
        end else begin
            if (state == IDLE && (cpu_re_i || cpu_we_i)) begin
                req_addr  <= cpu_addr_i;
                req_wdata <= cpu_wdata_i;
                req_be    <= cpu_be_i;
                req_we    <= cpu_we_i;
                req_re    <= cpu_re_i;
            end

            if (state == TAG_CHECK) begin
                evict_tag <= tag_lru_i ? tag_tag1_i : tag_tag0_i;
                fill_way  <= tag_lru_i;  // evict the LRU way
            end

            if (state == IDLE || next_state == IDLE
                    || (state == WRITE_BACK && next_state == FILL))
                burst_cnt <= 2'b0;
            else if (state == WRITE_BACK && m_axi_wvalid_o && m_axi_wready_i)
                burst_cnt <= burst_cnt + 1'b1;
            else if (state == FILL && m_axi_rvalid_i && m_axi_rready_o)
                burst_cnt <= burst_cnt + 1'b1;

            if (state == IDLE)
                aw_done <= 1'b0;
            else if (m_axi_awvalid_o && m_axi_awready_i)
                aw_done <= 1'b1;
        end
    end

    // ── Next-state logic ──────────────────────────────────────────────────
    // dirty of the LRU (evict) way — outside always_comb
    logic evict_dirty;
    assign evict_dirty = tag_lru_i ? tag_dirty1_i : tag_dirty0_i;

    always_comb begin
        next_state = state;
        case (state)
            IDLE:      if (cpu_re_i || cpu_we_i)          next_state = TAG_CHECK;
            TAG_CHECK: begin
                if (cache_hit)
                    next_state = HIT;
                else if (evict_dirty)
                    next_state = WRITE_BACK;
                else
                    next_state = FILL;
            end
            HIT:       next_state = IDLE;
            WRITE_BACK: if (m_axi_bvalid_i && m_axi_bready_o) next_state = FILL;
            FILL:       if (m_axi_rvalid_i && m_axi_rready_o && m_axi_rlast_i)
                            next_state = RESPOND;
            RESPOND:   next_state = IDLE;
            default:   next_state = IDLE;
        endcase
    end

    // ── CPU output ────────────────────────────────────────────────────────
    always_comb begin
        cpu_stall_o = (state != IDLE) || (cpu_re_i || cpu_we_i);
        cpu_rdata_o = hit_rdata;
        if (state == HIT || state == RESPOND) cpu_stall_o = 1'b0;
        if (state == IDLE && !cpu_re_i && !cpu_we_i) cpu_stall_o = 1'b0;
    end

    // ── Tag array output ──────────────────────────────────────────────────
    always_comb begin
        tag_we0_o   = 1'b0;
        tag_we1_o   = 1'b0;
        tag_lru_we_o= 1'b0;
        tag_idx_o   = req_idx;
        tag_tag_o   = req_tag;
        tag_valid_o = 1'b1;
        tag_dirty_o = 1'b0;
        tag_lru_o   = 1'b0;

        if (state == IDLE) tag_idx_o = cpu_addr_idx;

        // After FILL: write new tag to fill_way, clear dirty, set valid; LRU = fill_way (it's now MRU, so LRU = other)
        if (state == FILL && m_axi_rvalid_i && m_axi_rlast_i) begin
            tag_we0_o    = !fill_way;
            tag_we1_o    =  fill_way;
            tag_dirty_o  = 1'b0;
            tag_valid_o  = 1'b1;
            tag_lru_we_o = 1'b1;
            tag_lru_o    = !fill_way; // fill_way just became MRU → other way is now LRU
        end

        // On write hit: mark dirty; LRU = other way
        if ((state == HIT || state == RESPOND) && req_we) begin
            tag_we0_o    = !hit_way;
            tag_we1_o    =  hit_way;
            tag_dirty_o  = 1'b1;
            tag_valid_o  = 1'b1;
            tag_lru_we_o = 1'b1;
            tag_lru_o    = !hit_way; // hitting way is MRU → other way is LRU
        end

        // On read hit: update LRU only
        if (state == HIT && !req_we) begin
            tag_we0_o    = 1'b0;
            tag_we1_o    = 1'b0;
            tag_lru_we_o = 1'b1;
            tag_lru_o    = !hit_way;
        end
    end

    // ── Data array output ─────────────────────────────────────────────────
    always_comb begin
        data_we_o    = 1'b0;
        data_way_o   = fill_way;
        data_idx_o   = req_idx;
        data_word_o  = req_woff;
        data_be_o    = 4'b1111;
        data_wdata_o = 32'b0;

        if (state == HIT && req_we) begin
            data_we_o    = 1'b1;
            data_way_o   = hit_way;
            data_be_o    = req_be;
            data_wdata_o = req_wdata;
        end

        if (state == FILL && m_axi_rvalid_i) begin
            data_we_o    = 1'b1;
            data_way_o   = fill_way;
            data_word_o  = burst_cnt;
            data_be_o    = 4'b1111;
            data_wdata_o = m_axi_rdata_i;
        end

        if (state == RESPOND && req_we) begin
            data_we_o    = 1'b1;
            data_way_o   = fill_way;
            data_word_o  = req_woff;
            data_be_o    = req_be;
            data_wdata_o = req_wdata;
        end
    end

    // ── AXI write address channel ────────────────────────────────────────
    assign m_axi_awvalid_o = (state == WRITE_BACK) && !aw_done;
    assign m_axi_awaddr_o  = evict_addr;
    assign m_axi_awlen_o   = 8'd3;
    assign m_axi_awsize_o  = 3'b010;
    assign m_axi_awburst_o = 2'b01;

    // ── AXI write data channel ───────────────────────────────────────────
    assign m_axi_wvalid_o = (state == WRITE_BACK) && aw_done;
    assign m_axi_wdata_o  = wb_wdata;
    assign m_axi_wstrb_o  = 4'b1111;
    assign m_axi_wlast_o  = (burst_cnt == 2'd3);
    assign m_axi_bready_o = 1'b1;

    // ── AXI read address channel ─────────────────────────────────────────
    assign m_axi_arvalid_o = (state == FILL) && (burst_cnt == 2'd0) && !m_axi_rvalid_i;
    assign m_axi_araddr_o  = fill_addr;
    assign m_axi_arlen_o   = 8'd3;
    assign m_axi_arsize_o  = 3'b010;
    assign m_axi_arburst_o = 2'b01;
    assign m_axi_rready_o  = (state == FILL);

endmodule
