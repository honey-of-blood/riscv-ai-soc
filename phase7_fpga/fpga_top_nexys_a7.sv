`timescale 1ns/1ps
// FPGA top-level wrapper — Digilent Nexys A7-50T / A7-100T
// Board clock: 100 MHz on pin E3
// Active-high reset button: CPU_RESETN (active-low on board → invert to rst_n)
// LEDs[15:0]: gpio_o[15:0] — shows accelerator output / firmware status
//
// This wrapper keeps soc_top unchanged; all board-specific glue lives here.
// No MMCM/PLL needed — soc_top synthesises comfortably at 66.7 MHz on Sky130;
// Nexys A7-100T Artix-7 XC7A100T-1CSG324C easily meets timing at 100 MHz.
module fpga_top_nexys_a7 (
    input  logic        CLK100MHZ,   // E3 — 100 MHz board oscillator
    input  logic        CPU_RESETN,  // C12 — active-low push-button (BTNC on 50T)
    output logic [15:0] LED          // output bus driven by gpio_o[15:0]
);

    // -------------------------------------------------------------------------
    // 2-FF reset synchroniser (active-low reset in, active-low rst_n out)
    // Deasserts (goes high) synchronously with CLK100MHZ.
    // -------------------------------------------------------------------------
    logic rst_meta, rst_sync_n;

    always_ff @(posedge CLK100MHZ or negedge CPU_RESETN) begin
        if (!CPU_RESETN) begin
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
        .clk    (CLK100MHZ),
        .rst_n  (rst_sync_n),
        .gpio_o (gpio)
    );

    assign LED = gpio[15:0];

endmodule
