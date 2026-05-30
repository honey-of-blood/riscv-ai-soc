`timescale 1ns/1ps
// Phase 10 SoC integration testbench.
//
// Instantiates soc_top with the abstract memory port wired to
// mem_bram_backend (512 KB BRAM).  Runs the Phase 9 firmware which
// exercises the full pipeline:
//   CPU → BRAM write → cache flush → DMA → Scratchpad → Accel → GPIO
//
// Checks (same as soc_ph9_tb):
//   GPIO[0]=1      — firmware reached done sentinel
//   GPIO[15:8]=0x0A — Y[0]=10 (matmul result via BRAM-backed memory)
//
// This test verifies that the abstract memory port abstraction works
// correctly: the SoC does not care whether S0 is backed by axi_sram,
// mem_bram_backend, or mem_ddr3_xilinx — behaviour is identical.

module soc_ph10_tb;

logic clk   = 0;
logic rst_n = 0;
always #5 clk = ~clk;

initial begin
    repeat (8) @(posedge clk);
    rst_n = 1;
end

// ── External memory wires ─────────────────────────────────────────────────────
logic [31:0] mem_awaddr, mem_wdata, mem_araddr, mem_rdata;
logic  [3:0] mem_wstrb;
logic  [1:0] mem_bresp, mem_rresp;
logic        mem_awvalid, mem_awready, mem_wvalid, mem_wready;
logic        mem_bvalid, mem_bready, mem_arvalid, mem_arready;
logic        mem_rvalid, mem_rready;

// ── DUT: SoC with abstract memory port ───────────────────────────────────────
logic [15:0] gpio_out, gpio_oe;
logic [31:0] pc_obs;

soc_top dut (
    .clk           (clk),
    .rst_n         (rst_n),
    .uart_tx_o     (),
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

// ── Phase 10 memory backend: 512 KB BRAM ─────────────────────────────────────
mem_bram_backend u_bram (
    .clk      (clk),        .rst_n    (rst_n),
    .s_awaddr (mem_awaddr), .s_awvalid(mem_awvalid), .s_awready(mem_awready),
    .s_wdata  (mem_wdata),  .s_wstrb  (mem_wstrb),   .s_wvalid (mem_wvalid),
    .s_wready (mem_wready), .s_bresp  (mem_bresp),   .s_bvalid (mem_bvalid),
    .s_bready (mem_bready),
    .s_araddr (mem_araddr), .s_arvalid(mem_arvalid), .s_arready(mem_arready),
    .s_rdata  (mem_rdata),  .s_rresp  (mem_rresp),   .s_rvalid (mem_rvalid),
    .s_rready (mem_rready)
);

// ── Monitor ───────────────────────────────────────────────────────────────────
integer cycle_ctr = 0;
logic   done_flag = 0;
always @(posedge clk) begin
    cycle_ctr <= cycle_ctr + 1;
    if (rst_n && gpio_out[0]) done_flag <= 1;
end

// ── Checks ────────────────────────────────────────────────────────────────────
integer chk_pass = 0, chk_fail = 0;
task automatic result(input string s, input logic ok);
    if (ok) begin $display("[PASS] %s", s); chk_pass++; end
    else    begin $display("[FAIL] %s", s); chk_fail++; end
endtask

initial begin
    repeat (200_000) begin
        @(posedge clk);
        if (done_flag) break;
    end

    if (!done_flag) begin
        $display("[TIMEOUT] Phase 10 E2E: 200 000 cycles without GPIO[0]=1");
        $display("  pc=0x%08x gpio=0x%04x", pc_obs, gpio_out);
        $finish;
    end

    $display("");
    $display("╔════════════════════════════════════════════════════════════╗");
    $display("║  Phase 10 — BRAM Backend SoC Integration Test             ║");
    $display("╠════════════════════════════════════════════════════════════╣");
    result("GPIO[0]=1  — firmware reached done sentinel",     gpio_out[0] == 1'b1);
    result("GPIO[15:8]=0x0A — Y[0]=10 (BRAM-backed matmul)", gpio_out[15:8] == 8'h0A);
    $display("     Completion at cycle %0d", cycle_ctr);
    $display("     gpio_out = 0x%04x", gpio_out);
    $display("╠════════════════════════════════════════════════════════════╣");
    if (chk_fail == 0)
        $display("║  ALL %0d CHECKS PASSED — Phase 10 BRAM integration OK     ║", chk_pass);
    else
        $display("║  %0d/%0d CHECKS FAILED — see [FAIL] lines above             ║",
                 chk_fail, chk_pass + chk_fail);
    $display("╚════════════════════════════════════════════════════════════╝");
    $finish;
end

endmodule
