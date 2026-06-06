`timescale 1ns/1ps
// Scatter-gather DMA engine — linked-list descriptor chain.
//
// Each descriptor is 5 consecutive words in memory:
//   +0  src_addr       source address
//   +4  dst_addr       destination address
//   +8  byte_count     bytes to copy (must be a multiple of 4)
//   +12 next_desc_addr address of next descriptor; 0 = last in chain
//   +16 flags          [0]=irq_on_complete  [1]=src_inc  [2]=dst_inc
//
// APB register map (8-bit local address):
//   0x00  DESC_ADDR  address of first descriptor (set before start)
//   0x04  CTRL       [0]=start  [1]=abort
//   0x08  STATUS     [0]=busy   [1]=done   [2]=error
//   0x0C  IRQ_MASK   [0]=irq_en (enables irq_o when done)
//
// Memory bus: simple req/ack, 32-bit word granularity.
//   assert mem_req_o; combinational/1-cycle-later mem_ack_i signals completion.
//   reads: mem_rdata_i valid when mem_ack_i=1
//   writes: wdata/waddr sampled when mem_ack_i=1

module sg_dma (
    input  logic        clk,
    input  logic        rst_n,

    // APB slave
    input  logic [7:0]  paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // 32-bit word-level memory bus
    output logic [31:0] mem_addr_o,
    output logic        mem_wr_o,
    output logic [31:0] mem_wdata_o,
    input  logic [31:0] mem_rdata_i,
    output logic        mem_req_o,
    input  logic        mem_ack_i,

    // Interrupt
    output logic        irq_o
);

// ── APB helpers ───────────────────────────────────────────────────────────
logic       apb_wr;
logic [7:0] apb_a;
assign apb_wr = psel & penable & pwrite;
assign pready = 1'b1;
assign apb_a  = paddr;

// ── APB-writable registers ────────────────────────────────────────────────
logic [31:0] desc_addr_r;
logic        ctrl_start_r, ctrl_abort_r;
logic        irq_mask_r;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        desc_addr_r  <= '0;
        ctrl_start_r <= 1'b0;
        ctrl_abort_r <= 1'b0;
        irq_mask_r   <= 1'b1;
    end else if (apb_wr) begin
        case (apb_a)
            8'h00: desc_addr_r  <= pwdata;
            8'h04: begin ctrl_start_r <= pwdata[0]; ctrl_abort_r <= pwdata[1]; end
            8'h0C: irq_mask_r   <= pwdata[0];
            default: ;
        endcase
    end
end

// ── Status registers (FSM-driven) ────────────────────────────────────────
logic status_busy, status_done, status_error;

always_comb begin
    prdata = '0;
    case (apb_a)
        8'h00: prdata = desc_addr_r;
        8'h04: prdata = {30'b0, ctrl_abort_r, ctrl_start_r};
        8'h08: prdata = {29'b0, status_error, status_done, status_busy};
        8'h0C: prdata = {31'b0, irq_mask_r};
        default: prdata = '0;
    endcase
end

assign irq_o = status_done & irq_mask_r;

// ── Descriptor shadow registers ───────────────────────────────────────────
logic [31:0] src_addr_r, dst_addr_r, byte_count_r, next_desc_r;
logic [4:0]  flags_r;

// ── Transfer state ────────────────────────────────────────────────────────
logic [31:0] src_ptr, dst_ptr, xfer_cnt;
logic [31:0] desc_ptr;    // current descriptor address (may advance for chaining)
logic [31:0] xfer_buf;    // read-data buffer between XFER_RD and XFER_WR
logic [2:0]  fetch_cnt;   // 0..4 for 5 descriptor words

// Pre-computed fetch byte offset (outside always_comb — Icarus bit-select rule)
logic [31:0] fetch_off;
assign fetch_off = {29'b0, fetch_cnt} << 2;

logic [31:0] fetch_addr;
assign fetch_addr = desc_ptr + fetch_off;

// ── FSM ──────────────────────────────────────────────────────────────────
typedef enum logic [2:0] {
    S_IDLE,
    S_FETCH,
    S_XFER_RD,
    S_XFER_WR,
    S_CHAIN,
    S_DONE
} sg_state_t;

sg_state_t state;

// Memory bus combinational output
always_comb begin
    mem_req_o   = 1'b0;
    mem_wr_o    = 1'b0;
    mem_addr_o  = '0;
    mem_wdata_o = '0;
    case (state)
        S_FETCH: begin
            mem_req_o  = 1'b1;
            mem_wr_o   = 1'b0;
            mem_addr_o = fetch_addr;
        end
        S_XFER_RD: begin
            mem_req_o  = 1'b1;
            mem_wr_o   = 1'b0;
            mem_addr_o = src_ptr;
        end
        S_XFER_WR: begin
            mem_req_o   = 1'b1;
            mem_wr_o    = 1'b1;
            mem_addr_o  = dst_ptr;
            mem_wdata_o = xfer_buf;
        end
        default: ;
    endcase
end

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state        <= S_IDLE;
        status_busy  <= 1'b0;
        status_done  <= 1'b0;
        status_error <= 1'b0;
        fetch_cnt    <= '0;
        xfer_cnt     <= '0;
        src_ptr      <= '0;
        dst_ptr      <= '0;
        xfer_buf     <= '0;
        desc_ptr     <= '0;
        src_addr_r   <= '0;
        dst_addr_r   <= '0;
        byte_count_r <= '0;
        next_desc_r  <= '0;
        flags_r      <= '0;
    end else begin
        // Abort can fire in any non-IDLE state
        if (ctrl_abort_r && state != S_IDLE && state != S_DONE) begin
            state        <= S_IDLE;
            status_busy  <= 1'b0;
            status_error <= 1'b1;
        end else begin
            case (state)

            S_IDLE: begin
                status_done <= 1'b0;
                if (ctrl_start_r && !status_busy) begin
                    status_busy  <= 1'b1;
                    status_error <= 1'b0;
                    desc_ptr     <= desc_addr_r;
                    fetch_cnt    <= 3'd0;
                    state        <= S_FETCH;
                end
            end

            S_FETCH: begin
                if (mem_ack_i) begin
                    case (fetch_cnt)
                        3'd0: src_addr_r   <= mem_rdata_i;
                        3'd1: dst_addr_r   <= mem_rdata_i;
                        3'd2: byte_count_r <= mem_rdata_i;
                        3'd3: next_desc_r  <= mem_rdata_i;
                        3'd4: flags_r      <= mem_rdata_i[4:0];
                        default: ;
                    endcase
                    if (fetch_cnt == 3'd4) begin
                        fetch_cnt <= 3'd0;
                        xfer_cnt  <= 32'd0;
                        src_ptr   <= src_addr_r;
                        dst_ptr   <= dst_addr_r;
                        // byte_count_r known from fetch_cnt=2 edge (already latched)
                        state     <= S_XFER_RD;
                    end else begin
                        fetch_cnt <= fetch_cnt + 3'd1;
                    end
                end
            end

            S_XFER_RD: begin
                if (mem_ack_i) begin
                    xfer_buf <= mem_rdata_i;
                    if (flags_r[1]) src_ptr <= src_ptr + 32'd4;
                    state <= S_XFER_WR;
                end
            end

            S_XFER_WR: begin
                if (mem_ack_i) begin
                    if (flags_r[2]) dst_ptr <= dst_ptr + 32'd4;
                    xfer_cnt <= xfer_cnt + 32'd4;
                    if (xfer_cnt + 32'd4 >= byte_count_r)
                        state <= S_CHAIN;
                    else
                        state <= S_XFER_RD;
                end
            end

            S_CHAIN: begin
                if (next_desc_r != 32'd0) begin
                    desc_ptr  <= next_desc_r;
                    fetch_cnt <= 3'd0;
                    state     <= S_FETCH;
                end else begin
                    status_done <= 1'b1;
                    status_busy <= 1'b0;
                    state       <= S_DONE;
                end
            end

            S_DONE: begin
                // Remain done until ctrl_start deasserts
                if (!ctrl_start_r) begin
                    status_done <= 1'b0;
                    state       <= S_IDLE;
                end
            end

            default: state <= S_IDLE;
            endcase
        end
    end
end

endmodule
