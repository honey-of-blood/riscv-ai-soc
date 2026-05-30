`timescale 1ns/1ps
// SPI master — single-byte transfers, configurable CPOL/CPHA, active-low CS
module spi (
    input  logic        clk, rst_n,
    input  logic [11:0] paddr,
    input  logic        psel, penable, pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,
    // SPI pins
    output logic        sck,
    output logic        mosi,
    input  logic        miso,
    output logic        cs_n    // active-low chip select
);
    // -----------------------------------------------------------------------
    // APB address decode
    // -----------------------------------------------------------------------
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    // -----------------------------------------------------------------------
    // Registers
    // -----------------------------------------------------------------------
    logic [7:0]  rx_data;          // last received byte
    logic [4:0]  clk_div;          // SCK half-period in sys clocks
    logic        cpol, cpha;
    logic [15:0] cs_reg;           // CS register (active low — SW writes 0 to assert)
    logic        busy;

    // -----------------------------------------------------------------------
    // Shift engine
    // -----------------------------------------------------------------------
    logic [7:0]  tx_shift, rx_shift;
    logic [2:0]  bit_cnt;          // 0-7 (counts falling edges for data)
    logic [4:0]  div_cnt;          // counts to clk_div for half-period
    logic        sck_r;            // registered SCK output
    logic        phase_r;          // 0=first half-period, 1=second half-period
    logic        xfr_active;       // transfer in progress

    // Icarus: extract bit-select
    logic [7:0]  tx_shift_mosi;
    assign tx_shift_mosi = tx_shift;

    // APB write pulse
    logic apb_wr;
    assign apb_wr = psel & penable & pwrite;

    // -----------------------------------------------------------------------
    // Main FSM / shift engine
    // -----------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_shift   <= 8'h00;
            rx_shift   <= 8'h00;
            rx_data    <= 8'h00;
            bit_cnt    <= 3'd0;
            div_cnt    <= 5'd0;
            sck_r      <= 1'b0;
            phase_r    <= 1'b0;
            xfr_active <= 1'b0;
            busy       <= 1'b0;
            clk_div    <= 5'd4;
            cpol       <= 1'b0;
            cpha       <= 1'b0;
            cs_reg     <= 16'hFFFF;
        end else begin
            // APB register writes
            if (apb_wr) begin
                case (apb_addr)
                    8'h00: begin
                        // Write DATA → start transfer if not busy
                        if (!busy) begin
                            tx_shift   <= pwdata[7:0];
                            busy       <= 1'b1;
                            xfr_active <= 1'b1;
                            div_cnt    <= 5'd0;
                            bit_cnt    <= 3'd0;
                            phase_r    <= 1'b0;
                            sck_r      <= cpol;   // idle level
                        end
                    end
                    8'h04: begin
                        clk_div <= pwdata[7:3];
                        cpha    <= pwdata[2];
                        cpol    <= pwdata[1];
                        // bit[0]=busy is RO
                    end
                    8'h08: cs_reg <= pwdata[15:0];
                    default: ;
                endcase
            end

            // Transfer engine
            if (xfr_active) begin
                if (div_cnt < clk_div - 1) begin
                    div_cnt <= div_cnt + 5'd1;
                end else begin
                    div_cnt <= 5'd0;
                    // Toggle SCK
                    sck_r   <= ~sck_r;
                    phase_r <= ~phase_r;

                    if (cpha == 1'b0) begin
                        // CPHA=0: sample on first edge, shift TX on second edge
                        if (phase_r == 1'b0) begin
                            // First edge: sample MISO (all 8 bits land here)
                            rx_shift <= {rx_shift[6:0], miso};
                        end else begin
                            // Second edge: shift TX and advance bit counter
                            tx_shift <= {tx_shift[6:0], 1'b0};
                            if (bit_cnt == 3'd7) begin
                                xfr_active <= 1'b0;
                                busy       <= 1'b0;
                                rx_data    <= rx_shift;  // all 8 bits already in rx_shift
                            end else begin
                                bit_cnt <= bit_cnt + 3'd1;
                            end
                        end
                    end else begin
                        // CPHA=1: shift TX on first edge, sample on second edge
                        if (phase_r == 1'b0) begin
                            // First edge: shift TX
                            tx_shift <= {tx_shift[6:0], 1'b0};
                        end else begin
                            // Second edge: sample MISO
                            rx_shift <= {rx_shift[6:0], miso};
                            if (bit_cnt == 3'd7) begin
                                xfr_active <= 1'b0;
                                busy       <= 1'b0;
                                rx_data    <= {rx_shift[6:0], miso};
                            end else begin
                                bit_cnt <= bit_cnt + 3'd1;
                            end
                        end
                    end
                end
            end
        end
    end

    // -----------------------------------------------------------------------
    // Output assignments
    // -----------------------------------------------------------------------
    // SCK idles at CPOL level; only drive sck_r during active transfer
    assign sck  = xfr_active ? sck_r : cpol;
    assign mosi = tx_shift_mosi[7];  // MSB first
    assign cs_n = cs_reg[0];

    // -----------------------------------------------------------------------
    // APB read
    // -----------------------------------------------------------------------
    always_comb begin
        case (apb_addr)
            8'h00:   prdata = {24'b0, rx_data};
            8'h04:   prdata = {24'b0, clk_div, cpha, cpol, busy};
            8'h08:   prdata = {16'b0, cs_reg};
            default: prdata = 32'b0;
        endcase
    end

    assign pready = 1'b1;
endmodule
