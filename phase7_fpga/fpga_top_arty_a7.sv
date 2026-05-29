`timescale 1ns/1ps
// FPGA top-level wrapper — Digilent Arty A7-100T
// Board clock: 100 MHz on pin E3
// Active-low reset: BTNC (C2)
// RGB LEDs + green LEDs: gpio_o mapped to LD[3:0] (green) and LD[5:4] (RGB control)
//
// Arty A7 uses the same Artix-7 XC7A100T device as the Nexys A7-100T;
// only pin assignments differ.
module fpga_top_arty_a7 (
    input  logic       clk,     // E3 — 100 MHz board oscillator
    input  logic       resetn,  // C2 — active-low push-button (BTNC)
    output logic [3:0] led,     // H5/J5/T9/T10 — green LEDs
    output logic [2:0] led0_rgb // J3/J2/G2 — RGB LED 0 (B/G/R)
);

    // -------------------------------------------------------------------------
    // 2-FF reset synchroniser
    // -------------------------------------------------------------------------
    logic rst_meta, rst_sync_n;

    always_ff @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            rst_meta   <= 1'b0;
            rst_sync_n <= 1'b0;
        end else begin
            rst_meta   <= 1'b1;
            rst_sync_n <= rst_meta;
        end
    end

    // -------------------------------------------------------------------------
    // SoC
    // -------------------------------------------------------------------------
    logic [31:0] gpio;

    soc_top u_soc (
        .clk    (clk),
        .rst_n  (rst_sync_n),
        .gpio_o (gpio)
    );

    assign led      = gpio[3:0];
    assign led0_rgb = gpio[6:4];

endmodule
