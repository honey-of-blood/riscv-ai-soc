`timescale 1ns/1ps
// DMA-capable UART — 16-deep TX/RX FIFOs, DMA request outputs.
//
// Replaces the Phase 8 byte-at-a-time UART with deeper FIFOs and DMA request
// signals so a DMA controller (Phase 18) can move blocks without CPU involvement.
//
// APB register map (within sel=11, 0x1000_Bxxx):
//   0x00 TXDATA  [7:0]=byte to TX  [31]=tx_full   (write pushes FIFO)
//   0x04 RXDATA  [7:0]=RX byte     [31]=rx_valid  (read pops FIFO)
//   0x08 STATUS  [0]=tx_empty [1]=rx_valid [2]=tx_full [3]=rx_full
//                [4]=tx_half_empty [5]=rx_half_full
//   0x0C BAUD    [15:0]=divisor (default 868 = 100 MHz / 115 200)
//   0x10 DMA_CTRL [0]=tx_dma_en  [1]=rx_dma_en
//   0x14 FIFO_LVL [7:0]=tx_count [15:8]=rx_count
//
// DMA request outputs:
//   tx_dma_req_o  — TX FIFO below half-full (request more data from DMA)
//   rx_dma_req_o  — RX FIFO above half-full (request DMA drain)
//
// UART parameters: 8N1, configurable baud rate.

module uart_dma (
    input  logic        clk,
    input  logic        rst_n,

    // APB
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // UART pins
    output logic        uart_tx,
    input  logic        uart_rx,

    // DMA request outputs
    output logic        tx_dma_req_o,
    output logic        rx_dma_req_o,

    // Interrupts
    output logic        tx_irq_o,
    output logic        rx_irq_o
);

localparam FIFO_DEPTH = 16;
localparam FIFO_W     = $clog2(FIFO_DEPTH);   // 4

// ── Registers ──────────────────────────────────────────────────────────────
logic [15:0] baud_div;
logic        tx_dma_en, rx_dma_en;

logic apb_wr;
assign apb_wr = psel & penable & pwrite;
assign pready = 1'b1;

logic [4:0] apb_a;
assign apb_a = paddr[4:0];

// ── 16-deep TX FIFO ────────────────────────────────────────────────────────
logic [7:0]  tx_fifo [0:FIFO_DEPTH-1];
logic [FIFO_W:0] tx_wptr, tx_rptr;
logic [FIFO_W:0] tx_count;
logic        tx_full, tx_empty, tx_half_empty;
assign tx_count      = tx_wptr - tx_rptr;
assign tx_full       = tx_count[FIFO_W];
assign tx_empty      = (tx_count == '0);
assign tx_half_empty = (tx_count < (FIFO_DEPTH / 2));

logic tx_fifo_push, tx_fifo_pop;
logic [7:0] tx_fifo_rdata;
assign tx_fifo_rdata = tx_fifo[tx_rptr[FIFO_W-1:0]];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        tx_wptr <= '0;
    end else if (tx_fifo_push && !tx_full) begin
        tx_fifo[tx_wptr[FIFO_W-1:0]] <= pwdata[7:0];
        tx_wptr <= tx_wptr + 1'b1;
    end
end

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) tx_rptr <= '0;
    else if (tx_fifo_pop && !tx_empty) tx_rptr <= tx_rptr + 1'b1;
end

assign tx_fifo_push = apb_wr && (apb_a == 5'h00) && !tx_full;

// ── 16-deep RX FIFO ────────────────────────────────────────────────────────
logic [7:0]  rx_fifo [0:FIFO_DEPTH-1];
logic [FIFO_W:0] rx_wptr, rx_rptr;
logic [FIFO_W:0] rx_count;
logic        rx_full, rx_empty, rx_valid_flag, rx_half_full;
assign rx_count     = rx_wptr - rx_rptr;
assign rx_full      = rx_count[FIFO_W];
assign rx_empty     = (rx_count == '0);
assign rx_valid_flag = !rx_empty;
assign rx_half_full = (rx_count > (FIFO_DEPTH / 2));

logic rx_fifo_push, rx_fifo_pop;
logic [7:0] rx_fifo_rdata;
assign rx_fifo_rdata = rx_fifo[rx_rptr[FIFO_W-1:0]];
assign rx_fifo_pop   = psel & penable & !pwrite & (apb_a == 5'h04) & !rx_empty;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rx_wptr <= '0;
    end else if (rx_fifo_push && !rx_full) begin
        rx_fifo[rx_wptr[FIFO_W-1:0]] <= rx_byte_captured;
        rx_wptr <= rx_wptr + 1'b1;
    end
end

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) rx_rptr <= '0;
    else if (rx_fifo_pop) rx_rptr <= rx_rptr + 1'b1;
end

// ── APB control registers ──────────────────────────────────────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        baud_div   <= 16'd868;
        tx_dma_en  <= 1'b0;
        rx_dma_en  <= 1'b0;
    end else if (apb_wr) begin
        case (apb_a)
            5'h0C: baud_div  <= pwdata[15:0];
            5'h10: begin tx_dma_en <= pwdata[0]; rx_dma_en <= pwdata[1]; end
            default: ;
        endcase
    end
end

// Registered FIFO head — captures rx_fifo[rx_rptr] one cycle ahead so that
// after a pop (rptr increments via NBA), prdata still holds the popped byte.
logic [7:0] rx_fifo_head_reg;
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) rx_fifo_head_reg <= '0;
    else if (!rx_empty) rx_fifo_head_reg <= rx_fifo[rx_rptr[FIFO_W-1:0]];
end

always_comb begin
    prdata = '0;
    case (apb_a)
        5'h00: prdata = {tx_full, 23'b0, 8'h00};
        5'h04: prdata = {!rx_empty, 23'b0, rx_fifo_head_reg};
        5'h08: prdata = {26'b0, rx_half_full, tx_half_empty,
                         rx_full, tx_full, rx_valid_flag, tx_empty};
        5'h0C: prdata = {16'b0, baud_div};
        5'h10: prdata = {30'b0, rx_dma_en, tx_dma_en};
        5'h14: prdata = {16'b0, rx_count[3:0], 4'b0, tx_count[3:0]};
        default: prdata = '0;
    endcase
end

// ── DMA request outputs ────────────────────────────────────────────────────
assign tx_dma_req_o = tx_dma_en & tx_half_empty;
assign rx_dma_req_o = rx_dma_en & rx_half_full;

// ── TX UART serialiser ─────────────────────────────────────────────────────
logic [15:0] tx_div_cnt;
logic        tx_baud_tick;
assign tx_baud_tick = (tx_div_cnt == baud_div - 16'd1);

logic [3:0]  tx_bit_cnt;
logic [9:0]  tx_shift;   // start + 8 data + stop
logic        tx_busy;

assign tx_fifo_pop = tx_baud_tick & tx_busy & (tx_bit_cnt == 4'd0);

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        uart_tx    <= 1'b1;
        tx_busy    <= 1'b0;
        tx_bit_cnt <= '0;
        tx_shift   <= '1;
        tx_div_cnt <= '0;
    end else begin
        if (tx_baud_tick)
            tx_div_cnt <= '0;
        else
            tx_div_cnt <= tx_div_cnt + 16'd1;

        if (!tx_busy) begin
            uart_tx <= 1'b1;
            if (!tx_empty) begin
                tx_shift   <= {1'b1, tx_fifo_rdata, 1'b0};  // stop+data+start
                tx_busy    <= 1'b1;
                tx_bit_cnt <= 4'd10;
                tx_div_cnt <= '0;
            end
        end else if (tx_baud_tick) begin
            uart_tx  <= tx_shift[0];
            tx_shift <= {1'b1, tx_shift[9:1]};
            if (tx_bit_cnt == 4'd1) begin
                tx_busy    <= 1'b0;
                tx_bit_cnt <= '0;
            end else begin
                tx_bit_cnt <= tx_bit_cnt - 4'd1;
            end
        end
    end
end

// ── RX UART deserialiser ───────────────────────────────────────────────────
logic [15:0] rx_div_cnt;
logic        rx_baud_tick;
logic [15:0] baud_half;
assign baud_half    = {1'b0, baud_div[15:1]};
assign rx_baud_tick = (rx_div_cnt == baud_div - 16'd1);

logic [3:0]  rx_bit_cnt;
logic [7:0]  rx_shift;
logic        rx_busy;
logic [7:0]  rx_byte_captured;
logic        rx_byte_valid;

assign rx_fifo_push = rx_byte_valid;

// rx_uart_q: synchronize rx
logic [1:0] rx_sync;
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) rx_sync <= 2'b11;
    else        rx_sync <= {rx_sync[0], uart_rx};
end
logic rx_uart_q;
assign rx_uart_q = rx_sync[1];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rx_busy         <= 1'b0;
        rx_bit_cnt      <= '0;
        rx_shift        <= '0;
        rx_div_cnt      <= '0;
        rx_byte_captured <= '0;
        rx_byte_valid   <= 1'b0;
    end else begin
        rx_byte_valid <= 1'b0;

        if (!rx_busy) begin
            rx_div_cnt <= '0;
            if (!rx_uart_q) begin   // start bit detected
                rx_busy    <= 1'b1;
                rx_bit_cnt <= 4'd9;   // 9 = skip start, 8 data bits + capture
                rx_div_cnt <= baud_half;  // align first tick to center of start bit
            end
        end else begin
            if (rx_baud_tick) begin
                rx_div_cnt <= '0;
                if (rx_bit_cnt == 4'd9) begin
                    // First tick: center of start bit — sync only, no data shift
                    rx_bit_cnt <= 4'd8;
                end else if (rx_bit_cnt == 4'd0) begin
                    rx_busy         <= 1'b0;
                    rx_byte_captured <= rx_shift;
                    rx_byte_valid   <= 1'b1;
                end else begin
                    rx_shift   <= {rx_uart_q, rx_shift[7:1]};
                    rx_bit_cnt <= rx_bit_cnt - 4'd1;
                end
            end else begin
                rx_div_cnt <= rx_div_cnt + 16'd1;
            end
        end
    end
end

// ── Interrupt outputs ──────────────────────────────────────────────────────
assign tx_irq_o = tx_empty;
assign rx_irq_o = rx_valid_flag;

endmodule
