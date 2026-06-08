`timescale 1ns/1ps
// fpga_top_de1_soc.sv — Intel DE1-SoC (Cyclone V 5CSEMA5F31C6N) board top
//
// Board resources used:
//   CLOCK_50    : 50 MHz oscillator → PLL → 100 MHz CPU
//   KEY[1:0]    : active-low push-buttons; KEY[0]=reset, KEY[1]=user
//   SW[9:0]     : slide switches mapped to gpio_in_i[9:0]
//   LEDR[9:0]   : red LEDs driven by gpio_out_o[9:0]
//   UART_RXD/TXD: on-board USB UART (FTDI)
//   GPIO_0[1:0] : SPI SCK/MOSI, GPIO_0[2]=MISO, GPIO_0[3]=CS_N
//   GPIO_0[7:4] : SPI/JTAG debug signals (optional)
//
// Compile: quartus_sh --flow compile my_soc -c de1_soc
//          or: quartus_sh -t scripts/quartus_build.tcl
`define INTEL_FPGA

module fpga_top_de1_soc (
    // ── Clocks & resets ───────────────────────────────────────────────────
    input  wire        CLOCK_50,     // 50 MHz board oscillator (PIN_AF14)
    input  wire  [1:0] KEY,          // Active-low push-buttons: 0=reset, 1=user

    // ── LEDs & switches ───────────────────────────────────────────────────
    input  wire  [9:0] SW,           // Slide switches
    output wire  [9:0] LEDR,         // Red LEDs

    // ── UART (via USB-to-serial FTDI chip) ────────────────────────────────
    input  wire        UART_RXD,     // USB UART RX
    output wire        UART_TXD,     // USB UART TX

    // ── SPI / GPIO header (GPIO_0) ────────────────────────────────────────
    inout  wire [35:0] GPIO_0        // 40-pin expansion header
);

    // ── PLL: 50 → 100 / 25 MHz ───────────────────────────────────────────
    wire clk_cpu, clk_peri, pll_locked;

    pll_50_to_100 u_pll (
        .inclk0 (CLOCK_50),
        .c0     (clk_cpu),
        .c1     (clk_peri),
        .locked (pll_locked)
    );

    // ── Reset: release only after PLL locked + KEY[0] deasserted ────────
    logic [2:0] rst_pipe;
    wire        rst_n_sync;

    always_ff @(posedge clk_cpu or negedge KEY[0]) begin
        if (!KEY[0]) rst_pipe <= 3'b000;
        else         rst_pipe <= {rst_pipe[1:0], pll_locked};
    end
    assign rst_n_sync = rst_pipe[2];

    // ── GPIO routing ─────────────────────────────────────────────────────
    logic [15:0] gpio_out, gpio_oe;
    wire  [15:0] gpio_in;

    assign gpio_in       = {6'b0, SW};          // SW[9:0] → gpio_in[9:0]
    assign LEDR          = gpio_out[9:0];

    // ── SPI ───────────────────────────────────────────────────────────────
    wire spi_sck, spi_mosi, spi_miso, spi_cs_n;
    assign GPIO_0[0]  = spi_sck;
    assign GPIO_0[1]  = spi_mosi;
    assign spi_miso   = GPIO_0[2];
    assign GPIO_0[3]  = spi_cs_n;
    assign GPIO_0[35:4] = 32'bz;  // tristate unused header pins

    // ── BRAM backend (inferred BRAM — Cyclone V M10K blocks) ─────────────
    // AXI4-Lite SRAM slave: 64 KB instruction + data memory at 0x0000_xxxx
    //
    // AXI signals between soc_top m_mem_* and the inferred BRAM:
    logic [31:0] mem_awaddr, mem_wdata, mem_araddr, mem_rdata;
    logic  [3:0] mem_wstrb;
    logic        mem_awvalid, mem_awready, mem_wvalid, mem_wready;
    logic  [1:0] mem_bresp;
    logic        mem_bvalid, mem_bready;
    logic        mem_arvalid, mem_arready;
    logic  [1:0] mem_rresp;
    logic        mem_rvalid, mem_rready;

    // ── SoC ───────────────────────────────────────────────────────────────
    soc_top u_soc (
        .clk             (clk_cpu),
        .rst_n           (rst_n_sync),

        .uart_tx_o       (UART_TXD),
        .uart_rx_i       (UART_RXD),

        .gpio_in_i       (gpio_in),
        .gpio_out_o      (gpio_out),
        .gpio_oe_o       (gpio_oe),

        .spi_sck_o       (spi_sck),
        .spi_mosi_o      (spi_mosi),
        .spi_miso_i      (spi_miso),
        .spi_cs_n_o      (spi_cs_n),

        .pc_obs_o        (),

        .m_mem_awaddr    (mem_awaddr),
        .m_mem_awvalid   (mem_awvalid),
        .m_mem_awready   (mem_awready),
        .m_mem_wdata     (mem_wdata),
        .m_mem_wstrb     (mem_wstrb),
        .m_mem_wvalid    (mem_wvalid),
        .m_mem_wready    (mem_wready),
        .m_mem_bresp     (mem_bresp),
        .m_mem_bvalid    (mem_bvalid),
        .m_mem_bready    (mem_bready),
        .m_mem_araddr    (mem_araddr),
        .m_mem_arvalid   (mem_arvalid),
        .m_mem_arready   (mem_arready),
        .m_mem_rdata     (mem_rdata),
        .m_mem_rresp     (mem_rresp),
        .m_mem_rvalid    (mem_rvalid),
        .m_mem_rready    (mem_rready)
    );

    // ── Inferred BRAM (64 KB = 16 384 words) ─────────────────────────────
    // Quartus infers Cyclone V M10K blocks from this pattern.
    localparam DEPTH = 16384;
    logic [31:0] bram [0:DEPTH-1];
    logic [31:0] bram_rdata_r;
    logic        bram_rd_valid;

    // Write port
    always_ff @(posedge clk_cpu) begin
        if (mem_awvalid && mem_awready && mem_wvalid && mem_wready) begin
            if (mem_wstrb[0]) bram[mem_awaddr[15:2]][7:0]   <= mem_wdata[7:0];
            if (mem_wstrb[1]) bram[mem_awaddr[15:2]][15:8]  <= mem_wdata[15:8];
            if (mem_wstrb[2]) bram[mem_awaddr[15:2]][23:16] <= mem_wdata[23:16];
            if (mem_wstrb[3]) bram[mem_awaddr[15:2]][31:24] <= mem_wdata[31:24];
        end
    end

    // Read port
    always_ff @(posedge clk_cpu) begin
        if (mem_arvalid) bram_rdata_r <= bram[mem_araddr[15:2]];
        bram_rd_valid <= mem_arvalid;
    end

    // AXI4-Lite handshake (single-cycle, always-ready)
    assign mem_awready = 1'b1;
    assign mem_wready  = 1'b1;
    assign mem_bresp   = 2'b00;
    assign mem_bvalid  = 1'b1;
    assign mem_arready = 1'b1;
    assign mem_rdata   = bram_rdata_r;
    assign mem_rresp   = 2'b00;
    assign mem_rvalid  = bram_rd_valid;

endmodule
