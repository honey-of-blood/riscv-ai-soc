`timescale 1ns/1ps

// Cache controller FSM.
//
// CPU interface (matches Phase 1 riscv_core dmem port):
//   cpu_re_i / cpu_we_i  — read / write request (one-hot, held until stall clears)
//   cpu_addr_i           — byte address
//   cpu_wdata_i / cpu_be_i — write data and byte enables
//   cpu_rdata_o          — read data (valid 1 cycle after stall de-asserts)
//   cpu_stall_o          — hold CPU while cache is busy (1 = busy)
//
// Tag / data array interfaces — driven by this module, instantiated in cache_top.
//
// Memory-side AXI4 master (INCR burst, len=3 for 4-word lines):
//   Write channel (WRITE_BACK): evict dirty line to memory.
//   Read  channel (FILL):       fetch new line from memory.
//
// Address map:
//   addr[31:10] = tag  (22 bits)
//   addr[ 9: 4] = index (6 bits → 64 sets)
//   addr[ 3: 2] = word offset (2 bits → 4 words)
//   addr[ 1: 0] = byte offset (ignored by cache; passed to CPU for sub-word loads)
//
// FSM states:
//   IDLE      – wait for CPU request
//   TAG_CHECK – compare stored tag; decide hit / miss path
//   HIT       – service hit in 1 cycle; assert rdata / update dirty
//   WRITE_BACK– burst-write dirty evicted line; AW → W×4 → B
//   FILL      – burst-read new line; AR → R×4; write to data array
//   RESPOND   – return read data / apply write after fill; release stall
module cache_controller (
    input  logic        clk,
    input  logic        rst,

    // ── CPU interface ──────────────────────────────────────────────────────
    input  logic        cpu_re_i,
    input  logic        cpu_we_i,
    input  logic [31:0] cpu_addr_i,
    input  logic [31:0] cpu_wdata_i,
    input  logic [3:0]  cpu_be_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,

    // ── Tag array interface ────────────────────────────────────────────────
    output logic        tag_we_o,
    output logic [5:0]  tag_idx_o,
    output logic [21:0] tag_tag_o,
    output logic        tag_valid_o,
    output logic        tag_dirty_o,
    // read back (async)
    input  logic [21:0] tag_tag_i,
    input  logic        tag_valid_i,
    input  logic        tag_dirty_i,

    // ── Data array interface ───────────────────────────────────────────────
    output logic        data_we_o,
    output logic [5:0]  data_idx_o,
    output logic [1:0]  data_word_o,
    output logic [3:0]  data_be_o,
    output logic [31:0] data_wdata_o,
    // read back (async) — all four words
    input  logic [31:0] data_word0_i,
    input  logic [31:0] data_word1_i,
    input  logic [31:0] data_word2_i,
    input  logic [31:0] data_word3_i,

    // ── AXI4 write channel (WRITE_BACK) ───────────────────────────────────
    output logic        m_axi_awvalid_o,
    input  logic        m_axi_awready_i,
    output logic [31:0] m_axi_awaddr_o,
    output logic [7:0]  m_axi_awlen_o,    // = 8'd3 (4 beats)
    output logic [2:0]  m_axi_awsize_o,   // = 3'b010 (4 bytes)
    output logic [1:0]  m_axi_awburst_o,  // = 2'b01 (INCR)

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
    output logic [7:0]  m_axi_arlen_o,    // = 8'd3
    output logic [2:0]  m_axi_arsize_o,   // = 3'b010
    output logic [1:0]  m_axi_arburst_o,  // = 2'b01 (INCR)

    input  logic        m_axi_rvalid_i,
    output logic        m_axi_rready_o,
    input  logic [31:0] m_axi_rdata_i,
    input  logic        m_axi_rlast_i
);

    // ── FSM state encoding ─────────────────────────────────────────────────
    localparam [2:0]
        IDLE       = 3'd0,
        TAG_CHECK  = 3'd1,
        HIT        = 3'd2,
        WRITE_BACK = 3'd3,
        FILL       = 3'd4,
        RESPOND    = 3'd5;

    logic [2:0] state, next_state;

    // ── Registered CPU request ─────────────────────────────────────────────
    logic [31:0] req_addr;
    logic [31:0] req_wdata;
    logic [3:0]  req_be;
    logic        req_we, req_re;

    // ── Address decode (from registered request) ───────────────────────────
    // Icarus compat: all part-selects outside always_comb
    logic [21:0] req_tag;
    logic [5:0]  req_idx;
    logic [1:0]  req_woff;
    logic [31:0] fill_addr;    // base of new line  = {req_tag, req_idx, 4'b0}
    logic [31:0] evict_addr;   // base of evicted line = {evict_tag, req_idx, 4'b0}

    assign req_tag   = req_addr[31:10];
    assign req_idx   = req_addr[9:4];
    assign req_woff  = req_addr[3:2];
    assign fill_addr = {req_tag,   req_idx, 4'b0};

    // evict_tag is captured in TAG_CHECK from the tag array
    logic [21:0] evict_tag;
    assign evict_addr = {evict_tag, req_idx, 4'b0};

    // ── Hit detection (combinational) ──────────────────────────────────────
    logic cache_hit;
    assign cache_hit = tag_valid_i && (tag_tag_i == req_tag);

    // ── AXI burst counter ─────────────────────────────────────────────────
    logic [1:0] burst_cnt;

    // ── Selected read data from data array ────────────────────────────────
    logic [31:0] hit_rdata;
    always_comb begin
        case (req_woff)
            2'b00:   hit_rdata = data_word0_i;
            2'b01:   hit_rdata = data_word1_i;
            2'b10:   hit_rdata = data_word2_i;
            default: hit_rdata = data_word3_i;
        endcase
    end

    // ── AXI write-back data mux (word indexed by burst_cnt) ───────────────
    logic [31:0] wb_wdata;
    always_comb begin
        case (burst_cnt)
            2'b00:   wb_wdata = data_word0_i;
            2'b01:   wb_wdata = data_word1_i;
            2'b10:   wb_wdata = data_word2_i;
            default: wb_wdata = data_word3_i;
        endcase
    end

    // ── AW handshake tracker ───────────────────────────────────────────────
    logic aw_done;   // AW accepted; pulse clears it

    // =========================================================================
    // State register
    // =========================================================================
    always_ff @(posedge clk or posedge rst) begin
        if (rst) state <= IDLE;
        else     state <= next_state;
    end

    // =========================================================================
    // Datapath registers
    // =========================================================================
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            req_addr  <= 32'b0;
            req_wdata <= 32'b0;
            req_be    <= 4'b0;
            req_we    <= 1'b0;
            req_re    <= 1'b0;
            evict_tag <= 22'b0;
            burst_cnt <= 2'b0;
            aw_done   <= 1'b0;
        end else begin
            // Latch CPU request on transition to TAG_CHECK
            if (state == IDLE && (cpu_re_i || cpu_we_i)) begin
                req_addr  <= cpu_addr_i;
                req_wdata <= cpu_wdata_i;
                req_be    <= cpu_be_i;
                req_we    <= cpu_we_i;
                req_re    <= cpu_re_i;
            end

            // Capture evict tag in TAG_CHECK (before tag array is overwritten)
            if (state == TAG_CHECK)
                evict_tag <= tag_tag_i;

            // Burst counter: increments on AXI data beats
            if (state == IDLE || next_state == IDLE)
                burst_cnt <= 2'b0;
            else if (state == WRITE_BACK && m_axi_wvalid_o && m_axi_wready_i)
                burst_cnt <= burst_cnt + 1'b1;
            else if (state == FILL && m_axi_rvalid_i && m_axi_rready_o)
                burst_cnt <= burst_cnt + 1'b1;

            // AW handshake latch
            if (state == IDLE)
                aw_done <= 1'b0;
            else if (m_axi_awvalid_o && m_axi_awready_i)
                aw_done <= 1'b1;
        end
    end

    // =========================================================================
    // Next-state logic
    // =========================================================================
    always_comb begin
        next_state = state;
        case (state)
            IDLE: begin
                if (cpu_re_i || cpu_we_i)
                    next_state = TAG_CHECK;
            end
            TAG_CHECK: begin
                if (cache_hit)
                    next_state = HIT;
                else if (tag_dirty_i)
                    next_state = WRITE_BACK;
                else
                    next_state = FILL;
            end
            HIT: begin
                next_state = IDLE;
            end
            WRITE_BACK: begin
                // Leave WRITE_BACK once B channel acknowledged
                if (m_axi_bvalid_i && m_axi_bready_o)
                    next_state = FILL;
            end
            FILL: begin
                if (m_axi_rvalid_i && m_axi_rready_o && m_axi_rlast_i)
                    next_state = RESPOND;
            end
            RESPOND: begin
                next_state = IDLE;
            end
            default: next_state = IDLE;
        endcase
    end

    // =========================================================================
    // Output logic
    // =========================================================================

    // ── CPU outputs ───────────────────────────────────────────────────────
    always_comb begin
        cpu_stall_o = (state != IDLE) || (cpu_re_i || cpu_we_i);
        cpu_rdata_o = hit_rdata;

        // Release stall exactly in HIT and RESPOND states
        if (state == HIT || state == RESPOND)
            cpu_stall_o = 1'b0;
        // Also release in IDLE when no new request
        if (state == IDLE && !cpu_re_i && !cpu_we_i)
            cpu_stall_o = 1'b0;
    end

    // ── Tag array outputs ────────────────────────────────────────────────
    always_comb begin
        tag_we_o    = 1'b0;
        tag_idx_o   = req_idx;
        tag_tag_o   = req_tag;
        tag_valid_o = 1'b1;
        tag_dirty_o = 1'b0;

        // IDLE: point tag array at incoming address for TAG_CHECK next cycle
        if (state == IDLE) begin
            tag_idx_o = cpu_addr_i[9:4];
        end

        // After FILL last beat: write new tag (clean)
        if (state == FILL && m_axi_rvalid_i && m_axi_rlast_i) begin
            tag_we_o    = 1'b1;
            tag_dirty_o = 1'b0;
            tag_valid_o = 1'b1;
        end

        // On write hit: mark dirty
        if (state == HIT && req_we) begin
            tag_we_o    = 1'b1;
            tag_dirty_o = 1'b1;
            tag_valid_o = 1'b1;
        end

        // On write after fill (RESPOND with write): mark dirty
        if (state == RESPOND && req_we) begin
            tag_we_o    = 1'b1;
            tag_dirty_o = 1'b1;
            tag_valid_o = 1'b1;
        end
    end

    // ── Data array outputs ───────────────────────────────────────────────
    always_comb begin
        data_we_o    = 1'b0;
        data_idx_o   = req_idx;
        data_word_o  = req_woff;
        data_be_o    = 4'b1111;
        data_wdata_o = 32'b0;

        // Write hit: apply CPU write with byte enables
        if (state == HIT && req_we) begin
            data_we_o    = 1'b1;
            data_be_o    = req_be;
            data_wdata_o = req_wdata;
        end

        // FILL: write each incoming AXI word to the data array
        if (state == FILL && m_axi_rvalid_i) begin
            data_we_o    = 1'b1;
            data_word_o  = burst_cnt;
            data_be_o    = 4'b1111;
            data_wdata_o = m_axi_rdata_i;
        end

        // RESPOND with write: apply CPU write after fill
        if (state == RESPOND && req_we) begin
            data_we_o    = 1'b1;
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
    assign m_axi_arvalid_o = (state == FILL) && (burst_cnt == 2'd0)
                             && !m_axi_rvalid_i;
    assign m_axi_araddr_o  = fill_addr;
    assign m_axi_arlen_o   = 8'd3;
    assign m_axi_arsize_o  = 3'b010;
    assign m_axi_arburst_o = 2'b01;
    assign m_axi_rready_o  = (state == FILL);

endmodule
