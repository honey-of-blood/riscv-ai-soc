`timescale 1ns/1ps
// Phase 9 SoC end-to-end integration testbench.
//
// Runs the Phase 9 firmware which exercises the full pipeline:
//   CPU → SRAM write → cache flush → DMA (4 single-word transfers) →
//   Scratchpad rows 0-3 → Accel_top_v2 matmul → Y[0]=10 → GPIO
//
// Checks (firmware signals via GPIO after pipeline completes):
//   [PASS] GPIO[0]    = 1     — firmware reached the done sentinel
//   [PASS] GPIO[15:8] = 0x0A  — Y[0] = 10 (= 1+2+3+4 with W=all-ones)
//
// Timeout: 200 000 cycles (DMA × 4 + cache misses + accel pipeline).

module soc_ph9_tb;

logic clk   = 0;
logic rst_n = 0;
always #5 clk = ~clk;   // 10 ns → 100 MHz

initial begin
    repeat (8) @(posedge clk);
    rst_n = 1;
end

// ── DUT ───────────────────────────────────────────────────────────────────────
logic [15:0] gpio_out, gpio_oe;
logic [31:0] pc_obs;

soc_top dut (
    .clk        (clk),
    .rst_n      (rst_n),
    .uart_tx_o  (),
    .uart_rx_i  (1'b1),
    .gpio_in_i  (16'h0),
    .gpio_out_o (gpio_out),
    .gpio_oe_o  (gpio_oe),
    .spi_sck_o  (),
    .spi_mosi_o (),
    .spi_miso_i (1'b0),
    .spi_cs_n_o (),
    .pc_obs_o   (pc_obs)
);

// ── Monitors ─────────────────────────────────────────────────────────────────
integer cycle_ctr = 0;
logic   done_flag = 0;

always @(posedge clk) begin
    cycle_ctr <= cycle_ctr + 1;
    if (rst_n && gpio_out[0])
        done_flag <= 1;
end

// ── Result helpers ────────────────────────────────────────────────────────────
integer chk_pass = 0, chk_fail = 0;

task automatic result(input string s, input logic ok);
    if (ok) begin $display("[PASS] %s", s); chk_pass++; end
    else    begin $display("[FAIL] %s", s); chk_fail++; end
endtask

// ── Main check ────────────────────────────────────────────────────────────────
initial begin
    repeat (200_000) begin
        @(posedge clk);
        if (done_flag) break;
    end

    if (!done_flag) begin
        $display("[TIMEOUT] Phase 9 E2E: 200 000 cycles without GPIO[0]=1");
        $display("  pc=0x%08x gpio=0x%04x", pc_obs, gpio_out);
        $finish;
    end

    $display("");
    $display("╔════════════════════════════════════════════════════════════╗");
    $display("║  Phase 9 — DMA + Accelerator End-to-End SoC Test          ║");
    $display("╠════════════════════════════════════════════════════════════╣");
    result("GPIO[0]=1  — firmware reached done sentinel",   gpio_out[0] == 1'b1);
    result("GPIO[15:8]=0x0A — Y[0]=10 (DMA+matmul correct)", gpio_out[15:8] == 8'h0A);
    $display("     Completion at cycle %0d", cycle_ctr);
    $display("     gpio_out = 0x%04x", gpio_out);
    $display("╠════════════════════════════════════════════════════════════╣");
    if (chk_fail == 0)
        $display("║  ALL %0d CHECKS PASSED — Phase 9 integration complete      ║", chk_pass);
    else
        $display("║  %0d/%0d CHECKS FAILED — see [FAIL] lines above             ║",
                 chk_fail, chk_pass + chk_fail);
    $display("╚════════════════════════════════════════════════════════════╝");
    $finish;
end

endmodule
