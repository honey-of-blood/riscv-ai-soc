`timescale 1ns/1ps
// Phase 8 end-to-end SoC integration testbench.
// Loads fw_hello firmware: timer ISR toggles GPIO, main loop prints "Hello, World!\r\n".
//
// Checks:
//  1. GPIO[0] toggles to 1  → timer interrupt fired, ISR executed
//  2. UART TX start bit     → UART peripheral is transmitting
//  3. First UART byte = 'H' → correct APB address decode + UART shift register
//
// BAUD=868 cycles/bit (UART reset default, 100 MHz clock).
// Timer TICK=1000 cycles → GPIO toggles ~1100 cycles after firmware start.
// UART 'H' frame decode completes ~8000 cycles after start. Timeout = 30 000.

module soc_ph8_tb;

// ── Clock + reset ─────────────────────────────────────────────────────────────
logic clk   = 0;
logic rst_n = 0;
always #5 clk = ~clk;          // 10 ns = 100 MHz
initial begin
    repeat (8) @(posedge clk);
    rst_n = 1;
end

// ── DUT ──────────────────────────────────────────────────────────────────────
logic        uart_tx;
logic [15:0] gpio_out, gpio_oe;
logic [31:0] pc_obs;

logic [31:0] mem_awaddr, mem_wdata, mem_araddr, mem_rdata;
logic  [3:0] mem_wstrb;
logic  [1:0] mem_bresp, mem_rresp;
logic        mem_awvalid, mem_awready, mem_wvalid, mem_wready;
logic        mem_bvalid, mem_bready, mem_arvalid, mem_arready;
logic        mem_rvalid, mem_rready;

soc_top dut (
    .clk           (clk),
    .rst_n         (rst_n),
    .uart_tx_o     (uart_tx),
    .uart_rx_i     (1'b1),
    .gpio_in_i     (16'h0),
    .gpio_out_o    (gpio_out),
    .gpio_oe_o     (gpio_oe),
    .spi_sck_o     (),
    .spi_mosi_o    (),
    .spi_miso_i    (1'b0),
    .spi_cs_n_o    (),
    .pc_obs_o      (pc_obs),
    .m_mem_awaddr  (mem_awaddr),  .m_mem_awvalid (mem_awvalid), .m_mem_awready (mem_awready),
    .m_mem_wdata   (mem_wdata),   .m_mem_wstrb   (mem_wstrb),   .m_mem_wvalid  (mem_wvalid),
    .m_mem_wready  (mem_wready),  .m_mem_bresp   (mem_bresp),   .m_mem_bvalid  (mem_bvalid),
    .m_mem_bready  (mem_bready),
    .m_mem_araddr  (mem_araddr),  .m_mem_arvalid (mem_arvalid), .m_mem_arready (mem_arready),
    .m_mem_rdata   (mem_rdata),   .m_mem_rresp   (mem_rresp),   .m_mem_rvalid  (mem_rvalid),
    .m_mem_rready  (mem_rready)
);

axi_sram u_mem (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(mem_awaddr),  .s_awvalid(mem_awvalid), .s_awready(mem_awready),
    .s_wdata (mem_wdata),   .s_wstrb  (mem_wstrb),   .s_wvalid (mem_wvalid),
    .s_wready(mem_wready),  .s_bresp  (mem_bresp),   .s_bvalid (mem_bvalid),
    .s_bready(mem_bready),
    .s_araddr(mem_araddr),  .s_arvalid(mem_arvalid), .s_arready(mem_arready),
    .s_rdata (mem_rdata),   .s_rresp  (mem_rresp),   .s_rvalid (mem_rvalid),
    .s_rready(mem_rready)
);

// ── Observation state ─────────────────────────────────────────────────────────
// UART baud = 868 clk cycles at reset default; sample centre of each data bit.
localparam integer BAUD = 868;
localparam integer HALF = 434;  // BAUD/2

integer  cycle_ctr    = 0;

// GPIO check
logic    gpio0_prev   = 0;
logic    gpio_toggled = 0;
integer  gpio_cycle   = 0;

// UART byte decode
logic        uart_prev  = 1;
logic        uart_armed = 0;   // start bit falling edge seen
integer      uart_wcnt  = 0;   // cycles since arm
logic [7:0]  uart_rx    = 8'h00;
integer      uart_bits  = 0;
logic        uart_done  = 0;

// Unified completion flag (set by always block, polled in initial)
logic done_flag = 0;

always @(posedge clk) begin
    cycle_ctr <= cycle_ctr + 1;

    // ── GPIO[0] rising edge (timer ISR toggled LED) ───────────────────────
    if (rst_n && !gpio_toggled && gpio_out[0] && !gpio0_prev) begin
        gpio_toggled <= 1;
        gpio_cycle   <= cycle_ctr;
    end
    gpio0_prev <= gpio_out[0];

    // ── UART start-bit detection + 8-data-bit sampling ───────────────────
    if (rst_n) begin
        if (!uart_armed) begin
            if (uart_prev && !uart_tx) begin   // falling edge = start bit
                uart_armed <= 1;
                uart_wcnt  <= 0;
                uart_bits  <= 0;
                uart_rx    <= 8'h00;
            end
        end else if (!uart_done) begin
            uart_wcnt <= uart_wcnt + 1;
            if (uart_bits < 8) begin
                // Centre of data bit n: offset = (n+1)*BAUD + HALF - 1
                // (-1 because uart_wcnt starts incrementing the cycle AFTER arming)
                if (uart_wcnt == (uart_bits + 1) * BAUD + HALF - 1) begin
                    uart_rx[uart_bits] <= uart_tx;          // LSB first
                    if (uart_bits == 7) uart_done <= 1;
                    uart_bits          <= uart_bits + 1;
                end
            end
        end
        uart_prev <= uart_tx;
    end

    // ── Completion flag: both GPIO and UART done ──────────────────────────
    if (gpio_toggled && uart_done)
        done_flag <= 1;
end

// ── Result helpers ────────────────────────────────────────────────────────────
integer chk_pass = 0, chk_fail = 0;
task automatic result(input string s, input logic ok);
    if (ok) begin $display("[PASS] %s", s); chk_pass++; end
    else    begin $display("[FAIL] %s", s); chk_fail++; end
endtask

// ── Main check block — mirrors Phase 5 repeat/break pattern ──────────────────
initial begin
    // Poll until done or timeout (Phase 5 style: repeat + break)
    repeat (30_000) begin
        @(posedge clk);
        if (done_flag) break;
    end

    if (!done_flag) begin
        $display("[TIMEOUT] Phase 8 E2E test: 30 000 cycles elapsed without completion");
        $display("  uart_armed=%0d uart_done=%0d gpio_toggled=%0d uart_rx=0x%02x",
                  uart_armed, uart_done, gpio_toggled, uart_rx);
        $finish;
    end

    $display("");
    $display("╔════════════════════════════════════════════════════════════╗");
    $display("║  Phase 8 — End-to-End SoC Integration Test                ║");
    $display("╠════════════════════════════════════════════════════════════╣");
    result("Timer ISR ran — GPIO[0] toggled to 1",  gpio_toggled);
    result("UART TX asserted (start bit observed)", uart_armed);
    result("First UART byte decoded = 'H' (0x48)", uart_done && (uart_rx == 8'h48));
    $display("     GPIO[0] toggled at cycle %0d",   gpio_cycle);
    $display("     UART byte received  : 0x%02x",   uart_rx);
    $display("╠════════════════════════════════════════════════════════════╣");
    if (chk_fail == 0)
        $display("║  ALL %0d CHECKS PASSED — Phase 8 integration complete      ║", chk_pass);
    else
        $display("║  %0d/%0d CHECKS FAILED — see [FAIL] lines above             ║", chk_fail, chk_pass + chk_fail);
    $display("╚════════════════════════════════════════════════════════════╝");
    $finish;
end

endmodule
