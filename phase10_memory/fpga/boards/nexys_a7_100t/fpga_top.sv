`timescale 1ns/1ps
// Nexys A7-100T board wrapper — XC7A100TCSG324-1
//
// Memory backend: mem_ddr3_xilinx (128 MB DDR3L, MT41K128M16JT-125).
// The 100T device has the same DDR3 SODIMM as the 50T but 4× more fabric.
//
// Clock plan:
//   E3  → 100 MHz sysclk (LVCMOS33)
//   MMCM: 100 MHz → 100 MHz soc_clk + 200 MHz ref_clk (for MIG)
//
// Reset interlock:
//   soc_rst_n = resetn_sync AND init_calib_complete
//   DDR3 calibration takes ~10 ms; the SoC is held in reset until done.
//
// Pinout reference: Digilent Nexys A7-100T Reference Manual v1.2

module fpga_top (
    input  logic        sysclk,        // E3 — 100 MHz

    // Reset (CPU_RESETN — active low)
    input  logic        resetn,        // C12

    // UART
    output logic        uart_txd_in,   // D4
    input  logic        uart_rxd_out,  // C4

    // GPIO — 16 LEDs
    output logic [15:0] led,

    // 5 push-buttons
    input  logic  [4:0] btn,

    // SPI (PMOD JA)
    output logic        spi_sck,
    output logic        spi_mosi,
    input  logic        spi_miso,
    output logic        spi_cs_n,

    // DDR3 physical pins
    output logic [14:0] ddr3_addr,
    output logic  [2:0] ddr3_ba,
    output logic        ddr3_cas_n,
    output logic  [0:0] ddr3_ck_n,
    output logic  [0:0] ddr3_ck_p,
    output logic  [0:0] ddr3_cke,
    output logic  [0:0] ddr3_cs_n,
    inout  logic  [1:0] ddr3_dm,
    inout  logic [15:0] ddr3_dq,
    inout  logic  [1:0] ddr3_dqs_n,
    inout  logic  [1:0] ddr3_dqs_p,
    output logic  [0:0] ddr3_odt,
    output logic        ddr3_ras_n,
    output logic        ddr3_reset_n,
    output logic        ddr3_we_n
);

    // ── MMCM: 100 MHz → 100 MHz soc_clk + 200 MHz ref_clk ───────────────────
    logic clk_fb, soc_clk, ref_clk, mmcm_locked;

    MMCME2_BASE #(
        .BANDWIDTH        ("OPTIMIZED"),
        .CLKFBOUT_MULT_F  (10.0),     // VCO = 100 * 10 = 1000 MHz
        .CLKOUT0_DIVIDE_F (10.0),     // soc_clk = 1000/10 = 100 MHz
        .CLKOUT1_DIVIDE   (5),        // ref_clk = 1000/5  = 200 MHz
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
        .ddr3_dm            (ddr3_dm),     .ddr3_dq  (ddr3_dq),
        .ddr3_dqs_n         (ddr3_dqs_n),  .ddr3_dqs_p(ddr3_dqs_p),
        .ddr3_odt           (ddr3_odt),    .ddr3_ras_n(ddr3_ras_n),
        .ddr3_reset_n       (ddr3_reset_n),.ddr3_we_n(ddr3_we_n),
        .init_calib_complete(init_calib_complete)
    );

    // ── Reset: wait for MMCM lock AND DDR3 calibration ───────────────────────
    logic [3:0] rst_pipe;
    logic       soc_rst_n;
    always_ff @(posedge soc_clk or negedge mmcm_locked) begin
        if (!mmcm_locked) rst_pipe <= 4'b0;
        else              rst_pipe <= {rst_pipe[2:0], init_calib_complete & resetn};
    end
    assign soc_rst_n = rst_pipe[3];

    // ── SoC ──────────────────────────────────────────────────────────────────
    logic [15:0] gpio_out, gpio_oe, gpio_in;
    assign gpio_in = {11'b0, btn};
    assign led     = gpio_out & gpio_oe;

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
