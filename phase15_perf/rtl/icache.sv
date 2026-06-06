`timescale 1ns/1ps

// Phase 15: 4KB direct-mapped instruction cache with AXI4-Lite refill master.
// Parameters: 256 sets, 4 words per line (16 bytes/line), 20-bit tag.
// Address decode: tag = addr[31:12], index = addr[11:4], word_off = addr[3:2]
// One-cycle hit; on miss asserts cpu_stall_o and issues 4 sequential AXI reads.
module icache #(
    parameter SETS      = 256,
    parameter LINE_WORDS= 4,
    parameter TAG_BITS  = 20,
    parameter IDX_BITS  = 8,
    parameter OFF_BITS  = 2
)(
    input  logic        clk,
    input  logic        rst_n,

    // FENCE.I — clears all valid bits in one cycle
    input  logic        flush_i,

    // CPU interface (word-granular, always valid)
    input  logic [31:0] cpu_addr_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,

    // AXI4-Lite read master (no write channel — I-cache is read-only)
    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [31:0] m_rdata,
    input  logic        m_rvalid,
    output logic        m_rready
);

    // -------------------------------------------------------------------------
    // Cache storage
    // -------------------------------------------------------------------------
    logic [TAG_BITS-1:0] tag_arr  [0:SETS-1];
    logic [31:0]         data_arr [0:SETS-1][0:LINE_WORDS-1];
    logic                valid    [0:SETS-1];

    // -------------------------------------------------------------------------
    // Address field extracts (Icarus: assign outside always blocks)
    // -------------------------------------------------------------------------
    logic [TAG_BITS-1:0] req_tag;
    logic [IDX_BITS-1:0] req_idx;
    logic [OFF_BITS-1:0] req_off;

    assign req_tag = cpu_addr_i[31:12];
    assign req_idx = cpu_addr_i[11:4];
    assign req_off = cpu_addr_i[3:2];

    // -------------------------------------------------------------------------
    // Hit detection (combinational)
    // -------------------------------------------------------------------------
    logic hit;
    assign hit = valid[req_idx] && (tag_arr[req_idx] == req_tag);

    // -------------------------------------------------------------------------
    // FSM
    // -------------------------------------------------------------------------
    typedef enum logic [1:0] {
        LOOKUP = 2'd0,
        FILL   = 2'd1
    } state_t;

    state_t state;

    logic [1:0] fill_word;  // which word in line being filled (0..3)

    // Registered fill address (base of cache line, word-aligned to line boundary)
    logic [31:0] fill_base;

    // -------------------------------------------------------------------------
    // AXI read channel — registered outputs
    // -------------------------------------------------------------------------
    logic        arvalid_r;
    logic [31:0] araddr_r;

    assign m_arvalid = arvalid_r;
    assign m_araddr  = araddr_r;
    assign m_rready  = 1'b1;  // always ready to accept read data

    // -------------------------------------------------------------------------
    // CPU read data and stall
    // -------------------------------------------------------------------------
    // In LOOKUP and hit: serve directly from cache.
    // Otherwise stall.
    assign cpu_rdata_o = data_arr[req_idx][req_off];
    assign cpu_stall_o = (state != LOOKUP) || !hit;

    // -------------------------------------------------------------------------
    // Main FSM
    // -------------------------------------------------------------------------
    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state      <= LOOKUP;
            fill_word  <= 2'd0;
            arvalid_r  <= 1'b0;
            araddr_r   <= 32'b0;
            fill_base  <= 32'b0;
            for (i = 0; i < SETS; i = i + 1) begin
                valid[i]   <= 1'b0;
                tag_arr[i] <= {TAG_BITS{1'b0}};
            end
        end else if (flush_i) begin
            // FENCE.I: invalidate all lines in one cycle
            for (i = 0; i < SETS; i = i + 1)
                valid[i] <= 1'b0;
            // Also abort any in-progress fill
            state     <= LOOKUP;
            arvalid_r <= 1'b0;
            fill_word <= 2'd0;
        end else begin
            case (state)
                // -----------------------------------------------------------------
                LOOKUP: begin
                    if (!hit) begin
                        // Cache miss — start refill
                        // Line base: addr with lower 4 bits zeroed
                        fill_base <= {cpu_addr_i[31:4], 4'b0000};
                        // Invalidate the line being replaced immediately
                        valid[req_idx] <= 1'b0;
                        fill_word      <= 2'd0;
                        // Issue first AXI read
                        arvalid_r      <= 1'b1;
                        araddr_r       <= {cpu_addr_i[31:4], 4'b0000};
                        state          <= FILL;
                    end
                end
                // -----------------------------------------------------------------
                FILL: begin
                    if (arvalid_r && m_arready) begin
                        // Address handshake complete — deassert arvalid
                        arvalid_r <= 1'b0;
                    end

                    if (m_rvalid) begin
                        // Capture one word
                        data_arr[req_idx][fill_word] <= m_rdata;
                        if (fill_word == 2'd3) begin
                            // Line complete — update tag, set valid, return to LOOKUP
                            tag_arr[req_idx] <= req_tag;
                            valid[req_idx]   <= 1'b1;
                            fill_word        <= 2'd0;
                            arvalid_r        <= 1'b0;
                            state            <= LOOKUP;
                        end else begin
                            // Issue next AXI read
                            fill_word <= fill_word + 2'd1;
                            arvalid_r <= 1'b1;
                            araddr_r  <= fill_base + {fill_word + 2'd1, 2'b00};
                        end
                    end
                end
                // -----------------------------------------------------------------
                default: state <= LOOKUP;
            endcase
        end
    end

endmodule
