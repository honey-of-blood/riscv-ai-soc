`timescale 1ns/1ps

// 8N1 UART with 16-deep TX/RX FIFOs, APB slave interface.
// TX: baud-rate divider drives 1 bit per period.
// RX: start-bit detected on falling edge; first sample at half-period centre;
//     subsequent samples at full-period intervals (16x-oversample equivalent).
//
// Register map (byte offsets from base address):
//   0x00  TXDATA   [7:0]=byte to send  [31]=tx_full (read status)
//   0x04  RXDATA   [7:0]=byte received  [31]=valid flag; read pops the FIFO
//   0x08  STATUS   [0]=tx_empty [1]=rx_valid [2]=tx_full [3]=rx_full
//   0x0C  BAUD     divisor (default 868 = 100 MHz / 115200)

module uart (
    input  logic        clk,
    input  logic        rst_n,

    // APB slave
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // UART I/O
    output logic        tx,
    input  logic        rx,

    // Interrupt outputs
    output logic        irq_tx_empty,
    output logic        irq_rx_valid
);

    // -------------------------------------------------------------------------
    // APB address extract (Icarus: no bit-selects inside always_comb)
    // -------------------------------------------------------------------------
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    // -------------------------------------------------------------------------
    // Baud rate divisor
    // -------------------------------------------------------------------------
    logic [15:0] baud_div;

    // -------------------------------------------------------------------------
    // TX FIFO (16 × 8-bit, circular)
    // -------------------------------------------------------------------------
    logic [7:0] tx_fifo [0:15];
    logic [3:0] tx_wptr, tx_rptr;
    logic [4:0] tx_cnt;
    logic tx_full, tx_empty;
    assign tx_full  = tx_cnt[4];
    assign tx_empty = (tx_cnt == 5'd0);

    // -------------------------------------------------------------------------
    // RX FIFO (16 × 8-bit, circular)
    // -------------------------------------------------------------------------
    logic [7:0] rx_fifo [0:15];
    logic [3:0] rx_wptr, rx_rptr;
    logic [4:0] rx_cnt;
    logic rx_full, rx_empty;
    assign rx_full  = rx_cnt[4];
    assign rx_empty = (rx_cnt == 5'd0);

    // -------------------------------------------------------------------------
    // TX state machine
    //   0=IDLE  1=START  2-9=DATA(bit 0..7)  10=STOP
    // -------------------------------------------------------------------------
    logic [3:0]  tx_state;
    logic [7:0]  tx_shift;
    logic [2:0]  tx_bit_idx;
    logic [15:0] tx_div_cnt;

    // Icarus-safe: bit-select of variable extracted to assign
    logic tx_data_bit;
    assign tx_data_bit = tx_shift[tx_bit_idx];

    logic tx_baud_tick;
    assign tx_baud_tick = (tx_div_cnt == baud_div - 16'd1);

    // TX combinational output
    logic tx_out;
    always_comb begin
        case (tx_state)
            4'd1:                          tx_out = 1'b0;       // START
            4'd2, 4'd3, 4'd4, 4'd5,
            4'd6, 4'd7, 4'd8, 4'd9:       tx_out = tx_data_bit; // DATA
            default:                       tx_out = 1'b1;       // IDLE / STOP
        endcase
    end
    assign tx = tx_out;

    // Push/pop enable (combinational) for tx_cnt arithmetic
    logic tx_push, tx_pop;
    assign tx_push = psel && penable && pwrite && (apb_addr == 8'h00) && !tx_full;
    assign tx_pop  = (tx_state == 4'd0) && !tx_empty;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            baud_div    <= 16'd868;
            tx_wptr     <= 4'd0;
            tx_rptr     <= 4'd0;
            tx_cnt      <= 5'd0;
            tx_state    <= 4'd0;
            tx_shift    <= 8'h00;
            tx_bit_idx  <= 3'd0;
            tx_div_cnt  <= 16'd0;
        end else begin
            // FIFO push (APB write to TXDATA)
            if (tx_push) begin
                tx_fifo[tx_wptr] <= pwdata[7:0];
                tx_wptr          <= tx_wptr + 4'd1;
            end

            // BAUD register update
            if (psel && penable && pwrite && apb_addr == 8'h0C)
                baud_div <= pwdata[15:0];

            // tx_cnt: net push minus pop in this cycle
            tx_cnt <= tx_cnt + {4'b0, tx_push} - {4'b0, tx_pop};

            // TX state machine
            case (tx_state)
                4'd0: begin  // IDLE
                    tx_div_cnt <= 16'd0;
                    if (tx_pop) begin
                        tx_shift   <= tx_fifo[tx_rptr];
                        tx_rptr    <= tx_rptr + 4'd1;
                        tx_state   <= 4'd1;
                        tx_bit_idx <= 3'd0;
                    end
                end
                default: begin  // START / DATA / STOP
                    if (tx_baud_tick) begin
                        tx_div_cnt <= 16'd0;
                        if (tx_state == 4'd9) begin
                            tx_state <= 4'd10;  // last data bit → STOP
                        end else if (tx_state == 4'd10) begin
                            tx_state <= 4'd0;   // STOP → IDLE
                        end else begin
                            if (tx_state >= 4'd2)
                                tx_bit_idx <= tx_bit_idx + 3'd1;
                            tx_state <= tx_state + 4'd1;
                        end
                    end else begin
                        tx_div_cnt <= tx_div_cnt + 16'd1;
                    end
                end
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // RX: 2-FF sync + state machine
    //   0=IDLE  1=HALF (align to bit centre)  2=DATA  3=STOP
    // -------------------------------------------------------------------------
    logic rx_s0, rx_s1, rx_prev;
    logic [1:0]  rx_state;
    logic [7:0]  rx_shift;
    logic [2:0]  rx_bit_idx;
    logic [15:0] rx_div_cnt;

    // half-period for start-bit alignment (baud_div >> 1)
    logic [15:0] half_baud;
    assign half_baud = {1'b0, baud_div[15:1]};

    logic [15:0] rx_period;
    assign rx_period = (rx_state == 2'd1) ? half_baud : baud_div;

    logic rx_baud_tick;
    assign rx_baud_tick = (rx_div_cnt == rx_period - 16'd1);

    // Push/pop for rx_cnt arithmetic
    logic rx_push, rx_pop;
    assign rx_push = (rx_state == 2'd3) && rx_baud_tick && rx_s1 && !rx_full;
    assign rx_pop  = psel && penable && !pwrite && (apb_addr == 8'h04) && !rx_empty;

    // Bit-select extracted for Icarus
    logic rx_bit_val;
    assign rx_bit_val = rx_shift[rx_bit_idx];  // used below for prdata (not used in always)

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx_s0      <= 1'b1; rx_s1 <= 1'b1; rx_prev <= 1'b1;
            rx_state   <= 2'd0;
            rx_shift   <= 8'h00;
            rx_bit_idx <= 3'd0;
            rx_div_cnt <= 16'd0;
            rx_wptr    <= 4'd0;
            rx_rptr    <= 4'd0;
            rx_cnt     <= 5'd0;
        end else begin
            rx_s0   <= rx;
            rx_s1   <= rx_s0;
            rx_prev <= rx_s1;

            // rx_cnt: net push minus pop
            rx_cnt <= rx_cnt + {4'b0, rx_push} - {4'b0, rx_pop};
            if (rx_pop)
                rx_rptr <= rx_rptr + 4'd1;

            case (rx_state)
                2'd0: begin  // IDLE: detect falling edge on synchronised rx
                    rx_div_cnt <= 16'd0;
                    if (rx_prev && !rx_s1)
                        rx_state <= 2'd1;  // start bit detected
                end
                2'd1: begin  // HALF: wait half baud, verify start bit
                    if (rx_baud_tick) begin
                        rx_div_cnt <= 16'd0;
                        rx_bit_idx <= 3'd0;
                        if (!rx_s1) rx_state <= 2'd2;  // valid start
                        else        rx_state <= 2'd0;  // glitch, abort
                    end else
                        rx_div_cnt <= rx_div_cnt + 16'd1;
                end
                2'd2: begin  // DATA: 8 bits LSB-first
                    if (rx_baud_tick) begin
                        rx_div_cnt             <= 16'd0;
                        rx_shift[rx_bit_idx]   <= rx_s1;
                        if (rx_bit_idx == 3'd7) begin
                            rx_state   <= 2'd3;
                            rx_bit_idx <= 3'd0;
                        end else
                            rx_bit_idx <= rx_bit_idx + 3'd1;
                    end else
                        rx_div_cnt <= rx_div_cnt + 16'd1;
                end
                2'd3: begin  // STOP: verify stop bit, push to FIFO
                    if (rx_baud_tick) begin
                        rx_div_cnt <= 16'd0;
                        rx_state   <= 2'd0;
                        if (rx_push) begin
                            rx_fifo[rx_wptr] <= rx_shift;
                            rx_wptr          <= rx_wptr + 4'd1;
                        end
                    end else
                        rx_div_cnt <= rx_div_cnt + 16'd1;
                end
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // APB read mux
    // -------------------------------------------------------------------------
    logic [7:0] rx_rdata_byte;
    assign rx_rdata_byte = rx_fifo[rx_rptr];

    always_comb begin
        case (apb_addr)
            8'h00:   prdata = {tx_full, 23'b0, 8'h00};
            8'h04:   prdata = {!rx_empty, 23'b0, rx_rdata_byte};
            8'h08:   prdata = {28'b0, rx_full, tx_full, !rx_empty, tx_empty};
            8'h0C:   prdata = {16'b0, baud_div};
            default: prdata = 32'b0;
        endcase
    end

    assign pready       = 1'b1;
    assign irq_tx_empty = tx_empty;
    assign irq_rx_valid = !rx_empty;

endmodule
