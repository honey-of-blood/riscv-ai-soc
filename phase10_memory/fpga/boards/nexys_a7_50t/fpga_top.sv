`timescale 1ns/1ps
// Nexys A7-50T board wrapper — XC7A50TCSG324-1
//
// Memory backend: mem_bram_backend (512 KB BRAM, no DDR3 MIG needed).
// The 50T device has 1,800 KB of BRAM36 — more than enough for 512 KB.
// DDR3 MIG is licensed under Xilinx IP and requires Vivado; using BRAM
// keeps this board fully open-source and avoids the MIG calibration step.
//
// Clock plan:
//   W5  → 100 MHz sysclk (LVCMOS33)
//   MMCM: 100 MHz → 100 MHz soc_clk (phase-locked, BUFG)
//
// Pinout reference: Digilent Nexys A7-50T Reference Manual (v1.2)

module fpga_top (
    input  logic        sysclk,        // W5 — 100 MHz

    // Reset (CPU_RESETN — active low)
    input  logic        resetn,        // C12

    // UART
    output logic        uart_txd_in,   // D4
    input  logic        uart_rxd_out,  // C4

    // GPIO — 16 LEDs (output only on this board)
    output logic [15:0] led,           // H17 K15 J13 N14 R18 V17 U17 U16
                                       // V16 T15 U14 T16 V15 V14 V12 V11

    // 5 push-buttons as GPIO inputs [4:0]
    input  logic  [4:0] btn,           // BTNC=N17 BTNU=M18 BTNL=P17 BTNR=M17 BTND=P18

    // SPI (routed to PMOD JA)
    output logic        spi_sck,       // JA1 = J1
    output logic        spi_mosi,      // JA2 = L2
    input  logic        spi_miso,      // JA3 = J2
    output logic        spi_cs_n       // JA4 = G2
);

    // ── MMCM: 100 MHz → 100 MHz soc_clk ─────────────────────────────────────
    logic clk_fb, soc_clk, soc_clk_locked;

    MMCME2_BASE #(
        .BANDWIDTH        ("OPTIMIZED"),
        .CLKFBOUT_MULT_F  (10.0),     // VCO = 100 * 10 = 1000 MHz
        .CLKOUT0_DIVIDE_F (10.0),     // soc_clk = 1000/10 = 100 MHz
        .CLKIN1_PERIOD    (10.0),     // 100 MHz input
        .DIVCLK_DIVIDE    (1)
    ) u_mmcm (
        .CLKIN1   (sysclk),
        .CLKOUT0  (soc_clk),
        .CLKFBOUT (clk_fb),
        .CLKFBIN  (clk_fb),
        .LOCKED   (soc_clk_locked),
        .PWRDWN   (1'b0),
        .RST      (~resetn)
    );

    // ── Reset synchroniser: hold SoC in reset until MMCM locks ──────────────
    logic [3:0] rst_pipe;
    logic       soc_rst_n;
    always_ff @(posedge soc_clk or negedge resetn) begin
        if (!resetn) rst_pipe <= 4'b0;
        else         rst_pipe <= {rst_pipe[2:0], soc_clk_locked};
    end
    assign soc_rst_n = rst_pipe[3];

    // ── Memory interface wires ────────────────────────────────────────────────
    logic [31:0] mem_awaddr, mem_wdata, mem_araddr, mem_rdata;
    logic  [3:0] mem_wstrb;
    logic  [1:0] mem_bresp, mem_rresp;
    logic        mem_awvalid, mem_awready, mem_wvalid, mem_wready;
    logic        mem_bvalid, mem_bready, mem_arvalid, mem_arready;
    logic        mem_rvalid, mem_rready;

    // ── SoC ──────────────────────────────────────────────────────────────────
    logic [15:0] gpio_out, gpio_oe, gpio_in;
    assign gpio_in  = {11'b0, btn};
    assign led      = gpio_out & gpio_oe;

    logic [31:0] pc_obs_nc;

    soc_top u_soc (
        .clk           (soc_clk),
        .rst_n         (soc_rst_n),
        .uart_tx_o     (uart_txd_in),
        .uart_rx_i     (uart_rxd_out),
        .gpio_in_i     (gpio_in),
        .gpio_out_o    (gpio_out),
        .gpio_oe_o     (gpio_oe),
        .spi_sck_o     (spi_sck),
        .spi_mosi_o    (spi_mosi),
        .spi_miso_i    (spi_miso),
        .spi_cs_n_o    (spi_cs_n),
        .pc_obs_o      (pc_obs_nc),
        .m_mem_awaddr  (mem_awaddr),  .m_mem_awvalid (mem_awvalid), .m_mem_awready (mem_awready),
        .m_mem_wdata   (mem_wdata),   .m_mem_wstrb   (mem_wstrb),   .m_mem_wvalid  (mem_wvalid),
        .m_mem_wready  (mem_wready),  .m_mem_bresp   (mem_bresp),   .m_mem_bvalid  (mem_bvalid),
        .m_mem_bready  (mem_bready),
        .m_mem_araddr  (mem_araddr),  .m_mem_arvalid (mem_arvalid), .m_mem_arready (mem_arready),
        .m_mem_rdata   (mem_rdata),   .m_mem_rresp   (mem_rresp),   .m_mem_rvalid  (mem_rvalid),
        .m_mem_rready  (mem_rready)
    );

    // ── 512 KB BRAM backend ───────────────────────────────────────────────────
    mem_bram_backend u_mem (
        .clk      (soc_clk),    .rst_n    (soc_rst_n),
        .s_awaddr (mem_awaddr), .s_awvalid(mem_awvalid), .s_awready(mem_awready),
        .s_wdata  (mem_wdata),  .s_wstrb  (mem_wstrb),   .s_wvalid (mem_wvalid),
        .s_wready (mem_wready), .s_bresp  (mem_bresp),   .s_bvalid (mem_bvalid),
        .s_bready (mem_bready),
        .s_araddr (mem_araddr), .s_arvalid(mem_arvalid), .s_arready(mem_arready),
        .s_rdata  (mem_rdata),  .s_rresp  (mem_rresp),   .s_rvalid (mem_rvalid),
        .s_rready (mem_rready)
    );

endmodule
