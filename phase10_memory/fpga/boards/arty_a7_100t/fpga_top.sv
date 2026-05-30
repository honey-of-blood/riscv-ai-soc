`timescale 1ns/1ps
// Arty A7-100T board wrapper — XC7A100TCSG324-1
//
// Memory backend: mem_ddr3_xilinx (256 MB DDR3, MT41K128M16JT-125 × 2 chips).
// Arty A7-100T has two 16-bit DDR3 chips on a single 32-bit bus.  The MIG
// should be configured for a 32-bit data width (instead of 16-bit on Nexys A7).
//
// Clock plan:
//   E3  → 100 MHz sysclk (LVCMOS33)
//   MMCM: 100 MHz → 100 MHz soc_clk + 200 MHz ref_clk
//
// Reset interlock same as Nexys A7-100T.
// Pinout reference: Digilent Arty A7-100T Reference Manual v1.1

module fpga_top (
    input  logic        sysclk,        // E3 — 100 MHz

    input  logic        resetn,        // C2 (BTN0, active low in this design)

    // UART (USB-UART via FTDI)
    output logic        uart_txd_in,   // D10
    input  logic        uart_rxd_out,  // A9

    // GPIO — 4 LEDs
    output logic  [3:0] led,           // H5 J5 T9 T10

    // 4 RGB LEDs (used as extended GPIO output)
    output logic  [2:0] led0_rgb,      // G6 F6 E1
    output logic  [2:0] led1_rgb,      // G3 J4 G4
    output logic  [2:0] led2_rgb,      // J3 J2 H4
    output logic  [2:0] led3_rgb,      // K1 H6 K2

    // 4 push-buttons
    input  logic  [3:0] btn,           // D9 C9 B9 B8

    // 4 slide switches
    input  logic  [3:0] sw,            // A8 C11 C10 A10

    // SPI (PMOD JA)
    output logic        spi_sck,       // G13
    output logic        spi_mosi,      // B11
    input  logic        spi_miso,      // A11
    output logic        spi_cs_n,      // D12

    // DDR3 physical pins (32-bit bus, 2 chips)
    output logic [13:0] ddr3_addr,
    output logic  [2:0] ddr3_ba,
    output logic        ddr3_cas_n,
    output logic  [0:0] ddr3_ck_n,
    output logic  [0:0] ddr3_ck_p,
    output logic  [0:0] ddr3_cke,
    output logic  [0:0] ddr3_cs_n,
    inout  logic  [3:0] ddr3_dm,
    inout  logic [31:0] ddr3_dq,
    inout  logic  [3:0] ddr3_dqs_n,
    inout  logic  [3:0] ddr3_dqs_p,
    output logic  [0:0] ddr3_odt,
    output logic        ddr3_ras_n,
    output logic        ddr3_reset_n,
    output logic        ddr3_we_n
);

    // ── MMCM ──────────────────────────────────────────────────────────────────
    logic clk_fb, soc_clk, ref_clk, mmcm_locked;

    MMCME2_BASE #(
        .BANDWIDTH        ("OPTIMIZED"),
        .CLKFBOUT_MULT_F  (10.0),
        .CLKOUT0_DIVIDE_F (10.0),
        .CLKOUT1_DIVIDE   (5),
        .CLKIN1_PERIOD    (10.0),
        .DIVCLK_DIVIDE    (1)
    ) u_mmcm (
        .CLKIN1   (sysclk),
        .CLKOUT0  (soc_clk),
        .CLKOUT1  (ref_clk),
        .CLKFBOUT (clk_fb),
        .CLKFBIN  (clk_fb),
        .LOCKED   (mmcm_locked),
        .PWRDWN   (1'b0),
        .RST      (~resetn)
    );

    // ── DDR3 backend ──────────────────────────────────────────────────────────
    // NOTE: mem_ddr3_xilinx uses a 16-bit DDR3 port by default (Nexys A7).
    // For Arty A7 (32-bit DDR3), regenerate MIG with 32-bit data width and
    // update the instantiation here accordingly.  The axi_width_32to128 still
    // works: 32-bit AXI → 128-bit MIG with appropriate byte enables.
    logic [31:0] mem_awaddr, mem_wdata, mem_araddr, mem_rdata;
    logic  [3:0] mem_wstrb;
    logic  [1:0] mem_bresp, mem_rresp;
    logic        mem_awvalid, mem_awready, mem_wvalid, mem_wready;
    logic        mem_bvalid, mem_bready, mem_arvalid, mem_arready;
    logic        mem_rvalid, mem_rready;
    logic        init_calib_complete;

    mem_ddr3_xilinx u_ddr3 (
        .sys_clk_i          (ref_clk),
        .sys_rst_n          (mmcm_locked),
        .clk                (soc_clk),
        .s_awaddr           (mem_awaddr),  .s_awvalid(mem_awvalid), .s_awready(mem_awready),
        .s_wdata            (mem_wdata),   .s_wstrb  (mem_wstrb),   .s_wvalid (mem_wvalid),
        .s_wready           (mem_wready),  .s_bresp  (mem_bresp),   .s_bvalid (mem_bvalid),
        .s_bready           (mem_bready),
        .s_araddr           (mem_araddr),  .s_arvalid(mem_arvalid), .s_arready(mem_arready),
        .s_rdata            (mem_rdata),   .s_rresp  (mem_rresp),   .s_rvalid (mem_rvalid),
        .s_rready           (mem_rready),
        .ddr3_addr          (ddr3_addr),   .ddr3_ba  (ddr3_ba),
        .ddr3_cas_n         (ddr3_cas_n),  .ddr3_ck_n(ddr3_ck_n),  .ddr3_ck_p(ddr3_ck_p),
        .ddr3_cke           (ddr3_cke),    .ddr3_cs_n(ddr3_cs_n),
        .ddr3_dm            (ddr3_dm[1:0]),.ddr3_dq  (ddr3_dq[15:0]),
        .ddr3_dqs_n         (ddr3_dqs_n[1:0]),.ddr3_dqs_p(ddr3_dqs_p[1:0]),
        .ddr3_odt           (ddr3_odt),    .ddr3_ras_n(ddr3_ras_n),
        .ddr3_reset_n       (ddr3_reset_n),.ddr3_we_n(ddr3_we_n),
        .init_calib_complete(init_calib_complete)
    );

    // ── Reset interlock ───────────────────────────────────────────────────────
    logic [3:0] rst_pipe;
    logic       soc_rst_n;
    always_ff @(posedge soc_clk or negedge mmcm_locked) begin
        if (!mmcm_locked) rst_pipe <= 4'b0;
        else              rst_pipe <= {rst_pipe[2:0], init_calib_complete & resetn};
    end
    assign soc_rst_n = rst_pipe[3];

    // ── SoC ──────────────────────────────────────────────────────────────────
    logic [15:0] gpio_out, gpio_oe, gpio_in;
    assign gpio_in = {8'b0, sw, btn};
    assign led     = gpio_out[3:0] & gpio_oe[3:0];
    // Route GPIO[15:4] to RGB LEDs for visual feedback
    assign led0_rgb = gpio_out[6:4]  & gpio_oe[6:4];
    assign led1_rgb = gpio_out[9:7]  & gpio_oe[9:7];
    assign led2_rgb = gpio_out[12:10] & gpio_oe[12:10];
    assign led3_rgb = gpio_out[15:13] & gpio_oe[15:13];

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

endmodule
