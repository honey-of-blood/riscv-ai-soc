`timescale 1ns/1ps
// Phase 8 SoC top-level — all phases + peripheral suite integrated.
//
// Data path:
//   riscv_core (Ph1) ─┬─ cacheable (0x0000_xxxx) ──→ cache_top (Ph2)
//                     │                                    │ AXI4 burst → axi4_burst_to_lite
//                     │                                    │ AXI4-Lite
//                     └─ MMIO (0x5000_xxxx) → dmem_axi_adapter
//
// Crossbar (Ph3) slaves:
//   S0: axi_sram      (0x0000_xxxx — 64 KB data)
//   S1: axi_apb_bridge→ apb_demux  (0x1000_xxxx — peripherals)
//   S2: accel_top     (0x5000_xxxx — AI accelerator Ph4)
//
// APB peripheral map (0x1000_xxxx, decoded by paddr[15:12]):
//   0x1000_0xxx  apb_regs  — generic register file (Phase 5 backward compat)
//   0x1000_1xxx  UART      — 8N1 with TX/RX FIFO + IRQ
//   0x1000_2xxx  GPIO      — 16-bit direction + edge IRQ
//   0x1000_3xxx  Timer     — 64-bit RISC-V mtime counter
//   0x1000_4xxx  SPI       — 8-bit master, CPHA/CPOL
//   0x1000_5xxx  CLINT     — MSIP + mtime pass-through
//   0x1000_6xxx  PLIC      — 8-source priority arbiter
//
// Interrupt routing:
//   timer.mtip → clint.mtip_i → clint.mtip_o → cpu.m_timer_irq_i  (MTIP)
//   uart/gpio/timer irqs → plic.irq_src → plic.m_ext_irq → cpu.m_ext_irq_i (MEIP)
//   clint.msip_o → cpu.m_sw_irq_i  (MSIP)

module soc_top (
    input  logic        clk,
    input  logic        rst_n,

    // UART
    output logic        uart_tx_o,
    input  logic        uart_rx_i,

    // GPIO
    input  logic [15:0] gpio_in_i,
    output logic [15:0] gpio_out_o,
    output logic [15:0] gpio_oe_o,

    // SPI
    output logic        spi_sck_o,
    output logic        spi_mosi_o,
    input  logic        spi_miso_i,
    output logic        spi_cs_n_o,

    // Debug / synthesis keep-alive
    output logic [31:0] pc_obs_o
);

// ── Instruction memory ────────────────────────────────────────────────────────
logic [31:0] imem_addr, imem_rdata;
instr_rom u_irom (.clk(clk), .addr(imem_addr), .rdata(imem_rdata));

// ── Interrupt wires ───────────────────────────────────────────────────────────
logic m_ext_irq, m_timer_irq, m_sw_irq;

// ── CPU ───────────────────────────────────────────────────────────────────────
logic [31:0] dmem_addr, dmem_wdata, dmem_rdata;
logic        dmem_we, dmem_re, dmem_stall;
logic  [3:0] dmem_be;

riscv_core u_cpu (
    .clk           (clk),
    .rst           (~rst_n),
    .imem_addr_o   (imem_addr),
    .imem_rdata_i  (imem_rdata),
    .dmem_addr_o   (dmem_addr),
    .dmem_wdata_o  (dmem_wdata),
    .dmem_we_o     (dmem_we),
    .dmem_re_o     (dmem_re),
    .dmem_be_o     (dmem_be),
    .dmem_rdata_i  (dmem_rdata),
    .dmem_stall_i  (dmem_stall),
    .m_ext_irq_i   (m_ext_irq),
    .m_timer_irq_i (m_timer_irq),
    .m_sw_irq_i    (m_sw_irq)
);

// ── Address routing: cache vs MMIO bypass ────────────────────────────────────
logic is_mmio;
assign is_mmio = (dmem_addr[31:16] == 16'h1000) | (dmem_addr[31:16] == 16'h5000);

logic cpu_cache_re, cpu_cache_we;
logic cpu_mmio_re,  cpu_mmio_we;
assign cpu_cache_re = dmem_re & ~is_mmio;
assign cpu_cache_we = dmem_we & ~is_mmio;
assign cpu_mmio_re  = dmem_re &  is_mmio;
assign cpu_mmio_we  = dmem_we &  is_mmio;

// ── Phase 2: L1 data cache ────────────────────────────────────────────────────
logic [31:0] cache_rdata;
logic        cache_stall;

logic [31:0] c_awaddr, c_wdata, c_araddr, c_rdata;
logic  [3:0] c_wstrb;
logic  [7:0] c_awlen, c_arlen;
logic  [2:0] c_awsize, c_arsize;
logic  [1:0] c_awburst, c_arburst;
logic        c_awvalid, c_awready;
logic        c_wvalid, c_wready, c_wlast;
logic  [1:0] c_bresp;
logic        c_bvalid, c_bready;
logic        c_arvalid, c_arready;
logic  [1:0] c_rresp;
logic        c_rvalid, c_rready, c_rlast;

cache_top u_cache (
    .clk             (clk),
    .rst             (~rst_n),
    .cpu_re_i        (cpu_cache_re),
    .cpu_we_i        (cpu_cache_we),
    .cpu_addr_i      (dmem_addr),
    .cpu_wdata_i     (dmem_wdata),
    .cpu_be_i        (dmem_be),
    .cpu_rdata_o     (cache_rdata),
    .cpu_stall_o     (cache_stall),
    .m_axi_awvalid_o (c_awvalid),  .m_axi_awready_i (c_awready),
    .m_axi_awaddr_o  (c_awaddr),   .m_axi_awlen_o   (c_awlen),
    .m_axi_awsize_o  (c_awsize),   .m_axi_awburst_o (c_awburst),
    .m_axi_wvalid_o  (c_wvalid),   .m_axi_wready_i  (c_wready),
    .m_axi_wdata_o   (c_wdata),    .m_axi_wstrb_o   (c_wstrb),
    .m_axi_wlast_o   (c_wlast),
    .m_axi_bvalid_i  (c_bvalid),   .m_axi_bready_o  (c_bready),
    .m_axi_arvalid_o (c_arvalid),  .m_axi_arready_i (c_arready),
    .m_axi_araddr_o  (c_araddr),   .m_axi_arlen_o   (c_arlen),
    .m_axi_arsize_o  (c_arsize),   .m_axi_arburst_o (c_arburst),
    .m_axi_rvalid_i  (c_rvalid),   .m_axi_rready_o  (c_rready),
    .m_axi_rdata_i   (c_rdata),    .m_axi_rlast_i   (c_rlast)
);

// ── Burst-to-Lite bridge: cache → crossbar master 0 ──────────────────────────
logic [31:0] m0_awaddr, m0_wdata, m0_araddr, m0_rdata;
logic  [3:0] m0_wstrb;
logic  [1:0] m0_bresp, m0_rresp;
logic        m0_awvalid, m0_awready, m0_wvalid, m0_wready;
logic        m0_bvalid, m0_bready;
logic        m0_arvalid, m0_arready, m0_rvalid, m0_rready;

axi4_burst_to_lite u_b2l (
    .clk       (clk), .rst_n     (rst_n),
    .s_awaddr  (c_awaddr),   .s_awvalid (c_awvalid),  .s_awready (c_awready),
    .s_wdata   (c_wdata),    .s_wstrb   (c_wstrb),    .s_wlast   (c_wlast),
    .s_wvalid  (c_wvalid),   .s_wready  (c_wready),
    .s_bresp   (c_bresp),    .s_bvalid  (c_bvalid),   .s_bready  (c_bready),
    .s_araddr  (c_araddr),   .s_arvalid (c_arvalid),  .s_arready (c_arready),
    .s_rdata   (c_rdata),    .s_rresp   (c_rresp),    .s_rlast   (c_rlast),
    .s_rvalid  (c_rvalid),   .s_rready  (c_rready),
    .m_awaddr  (m0_awaddr),  .m_awvalid (m0_awvalid), .m_awready (m0_awready),
    .m_wdata   (m0_wdata),   .m_wstrb   (m0_wstrb),   .m_wvalid  (m0_wvalid),
    .m_wready  (m0_wready),
    .m_bresp   (m0_bresp),   .m_bvalid  (m0_bvalid),  .m_bready  (m0_bready),
    .m_araddr  (m0_araddr),  .m_arvalid (m0_arvalid), .m_arready (m0_arready),
    .m_rdata   (m0_rdata),   .m_rresp   (m0_rresp),   .m_rvalid  (m0_rvalid),
    .m_rready  (m0_rready)
);

// ── MMIO adapter: CPU → crossbar master 1 (0x5000_xxxx) ──────────────────────
logic [31:0] mmio_rdata;
logic        mmio_stall;

logic [31:0] m1_awaddr, m1_wdata, m1_araddr, m1_rdata;
logic  [3:0] m1_wstrb;
logic  [1:0] m1_bresp, m1_rresp;
logic        m1_awvalid, m1_awready, m1_wvalid, m1_wready;
logic        m1_bvalid, m1_bready;
logic        m1_arvalid, m1_arready, m1_rvalid, m1_rready;

dmem_axi_adapter u_adapter (
    .clk        (clk),        .rst_n      (rst_n),
    .cpu_re_i   (cpu_mmio_re), .cpu_we_i  (cpu_mmio_we),
    .cpu_addr_i (dmem_addr),   .cpu_wdata_i(dmem_wdata),
    .cpu_be_i   (dmem_be),
    .cpu_rdata_o(mmio_rdata),  .cpu_stall_o(mmio_stall),
    .m_awaddr   (m1_awaddr),   .m_awvalid(m1_awvalid), .m_awready(m1_awready),
    .m_wdata    (m1_wdata),    .m_wstrb  (m1_wstrb),
    .m_wvalid   (m1_wvalid),   .m_wready (m1_wready),
    .m_bresp    (m1_bresp),    .m_bvalid (m1_bvalid),  .m_bready (m1_bready),
    .m_araddr   (m1_araddr),   .m_arvalid(m1_arvalid), .m_arready(m1_arready),
    .m_rdata    (m1_rdata),    .m_rresp  (m1_rresp),
    .m_rvalid   (m1_rvalid),   .m_rready (m1_rready)
);

assign dmem_rdata = is_mmio ? mmio_rdata : cache_rdata;
assign dmem_stall = is_mmio ? mmio_stall : cache_stall;

// ── Master 2: tied off ────────────────────────────────────────────────────────
logic [31:0] m2_awaddr=0, m2_wdata=0, m2_araddr=0;
logic  [3:0] m2_wstrb=0;
logic        m2_awvalid=0, m2_wvalid=0, m2_bready=0, m2_arvalid=0, m2_rready=0;
logic [31:0] m2_rdata;
logic  [1:0] m2_bresp, m2_rresp;
logic        m2_awready, m2_wready, m2_bvalid, m2_arready, m2_rvalid;

// ── Crossbar slave wires ──────────────────────────────────────────────────────
logic [31:0] s0_awaddr, s0_wdata, s0_araddr, s0_rdata;
logic  [3:0] s0_wstrb;
logic  [1:0] s0_bresp, s0_rresp;
logic        s0_awvalid, s0_awready, s0_wvalid, s0_wready;
logic        s0_bvalid, s0_bready, s0_arvalid, s0_arready, s0_rvalid, s0_rready;

logic [31:0] s1_awaddr, s1_wdata, s1_araddr, s1_rdata;
logic  [3:0] s1_wstrb;
logic  [1:0] s1_bresp, s1_rresp;
logic        s1_awvalid, s1_awready, s1_wvalid, s1_wready;
logic        s1_bvalid, s1_bready, s1_arvalid, s1_arready, s1_rvalid, s1_rready;

logic [31:0] s2_awaddr, s2_wdata, s2_araddr, s2_rdata;
logic  [3:0] s2_wstrb;
logic  [1:0] s2_bresp, s2_rresp;
logic        s2_awvalid, s2_awready, s2_wvalid, s2_wready;
logic        s2_bvalid, s2_bready, s2_arvalid, s2_arready, s2_rvalid, s2_rready;

// ── Phase 3: AXI4 crossbar ────────────────────────────────────────────────────
axi4_crossbar u_xbar (
    .clk(clk), .rst_n(rst_n),
    .m0_awaddr(m0_awaddr), .m0_awvalid(m0_awvalid), .m0_awready(m0_awready),
    .m0_wdata (m0_wdata),  .m0_wstrb  (m0_wstrb),   .m0_wvalid (m0_wvalid),  .m0_wready(m0_wready),
    .m0_bresp (m0_bresp),  .m0_bvalid (m0_bvalid),  .m0_bready (m0_bready),
    .m0_araddr(m0_araddr), .m0_arvalid(m0_arvalid), .m0_arready(m0_arready),
    .m0_rdata (m0_rdata),  .m0_rresp  (m0_rresp),   .m0_rvalid (m0_rvalid),  .m0_rready(m0_rready),
    .m1_awaddr(m1_awaddr), .m1_awvalid(m1_awvalid), .m1_awready(m1_awready),
    .m1_wdata (m1_wdata),  .m1_wstrb  (m1_wstrb),   .m1_wvalid (m1_wvalid),  .m1_wready(m1_wready),
    .m1_bresp (m1_bresp),  .m1_bvalid (m1_bvalid),  .m1_bready (m1_bready),
    .m1_araddr(m1_araddr), .m1_arvalid(m1_arvalid), .m1_arready(m1_arready),
    .m1_rdata (m1_rdata),  .m1_rresp  (m1_rresp),   .m1_rvalid (m1_rvalid),  .m1_rready(m1_rready),
    .m2_awaddr(m2_awaddr), .m2_awvalid(m2_awvalid), .m2_awready(m2_awready),
    .m2_wdata (m2_wdata),  .m2_wstrb  (m2_wstrb),   .m2_wvalid (m2_wvalid),  .m2_wready(m2_wready),
    .m2_bresp (m2_bresp),  .m2_bvalid (m2_bvalid),  .m2_bready (m2_bready),
    .m2_araddr(m2_araddr), .m2_arvalid(m2_arvalid), .m2_arready(m2_arready),
    .m2_rdata (m2_rdata),  .m2_rresp  (m2_rresp),   .m2_rvalid (m2_rvalid),  .m2_rready(m2_rready),
    .s0_awaddr(s0_awaddr), .s0_awvalid(s0_awvalid), .s0_awready(s0_awready),
    .s0_wdata (s0_wdata),  .s0_wstrb  (s0_wstrb),   .s0_wvalid (s0_wvalid),  .s0_wready(s0_wready),
    .s0_bresp (s0_bresp),  .s0_bvalid (s0_bvalid),  .s0_bready (s0_bready),
    .s0_araddr(s0_araddr), .s0_arvalid(s0_arvalid), .s0_arready(s0_arready),
    .s0_rdata (s0_rdata),  .s0_rresp  (s0_rresp),   .s0_rvalid (s0_rvalid),  .s0_rready(s0_rready),
    .s1_awaddr(s1_awaddr), .s1_awvalid(s1_awvalid), .s1_awready(s1_awready),
    .s1_wdata (s1_wdata),  .s1_wstrb  (s1_wstrb),   .s1_wvalid (s1_wvalid),  .s1_wready(s1_wready),
    .s1_bresp (s1_bresp),  .s1_bvalid (s1_bvalid),  .s1_bready (s1_bready),
    .s1_araddr(s1_araddr), .s1_arvalid(s1_arvalid), .s1_arready(s1_arready),
    .s1_rdata (s1_rdata),  .s1_rresp  (s1_rresp),   .s1_rvalid (s1_rvalid),  .s1_rready(s1_rready),
    .s2_awaddr(s2_awaddr), .s2_awvalid(s2_awvalid), .s2_awready(s2_awready),
    .s2_wdata (s2_wdata),  .s2_wstrb  (s2_wstrb),   .s2_wvalid (s2_wvalid),  .s2_wready(s2_wready),
    .s2_bresp (s2_bresp),  .s2_bvalid (s2_bvalid),  .s2_bready (s2_bready),
    .s2_araddr(s2_araddr), .s2_arvalid(s2_arvalid), .s2_arready(s2_arready),
    .s2_rdata (s2_rdata),  .s2_rresp  (s2_rresp),   .s2_rvalid (s2_rvalid),  .s2_rready(s2_rready)
);

// ── Slave 0: SRAM (0x0000_xxxx) ──────────────────────────────────────────────
axi_sram u_sram0 (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s0_awaddr), .s_awvalid(s0_awvalid), .s_awready(s0_awready),
    .s_wdata (s0_wdata),  .s_wstrb  (s0_wstrb),   .s_wvalid (s0_wvalid),  .s_wready(s0_wready),
    .s_bresp (s0_bresp),  .s_bvalid (s0_bvalid),  .s_bready (s0_bready),
    .s_araddr(s0_araddr), .s_arvalid(s0_arvalid), .s_arready(s0_arready),
    .s_rdata (s0_rdata),  .s_rresp  (s0_rresp),   .s_rvalid (s0_rvalid),  .s_rready(s0_rready)
);

// ── APB bus (AXI-APB bridge → APB demux) ─────────────────────────────────────
logic [31:0] apb_paddr;
logic        apb_psel, apb_penable, apb_pwrite;
logic [31:0] apb_pwdata;
logic  [3:0] apb_pstrb;
logic [31:0] apb_prdata;
logic        apb_pready, apb_pslverr;

// ── Slave 1: AXI-APB bridge (0x1000_xxxx) ────────────────────────────────────
axi_apb_bridge u_apb_bridge (
    .clk      (clk),          .rst_n    (rst_n),
    .s_awaddr (s1_awaddr),    .s_awvalid(s1_awvalid),  .s_awready(s1_awready),
    .s_wdata  (s1_wdata),     .s_wstrb  (s1_wstrb),    .s_wvalid (s1_wvalid),  .s_wready(s1_wready),
    .s_bresp  (s1_bresp),     .s_bvalid (s1_bvalid),   .s_bready (s1_bready),
    .s_araddr (s1_araddr),    .s_arvalid(s1_arvalid),  .s_arready(s1_arready),
    .s_rdata  (s1_rdata),     .s_rresp  (s1_rresp),    .s_rvalid (s1_rvalid),  .s_rready(s1_rready),
    .p_paddr  (apb_paddr),    .p_psel   (apb_psel),    .p_penable(apb_penable),
    .p_pwrite (apb_pwrite),   .p_pwdata (apb_pwdata),  .p_pstrb  (apb_pstrb),
    .p_prdata (apb_prdata),   .p_pready (apb_pready),  .p_pslverr(apb_pslverr)
);

// ── APB peripheral wires ──────────────────────────────────────────────────────
logic [11:0] regs_paddr, uart_paddr,  gpio_paddr, timer_paddr;
logic [11:0] spi_paddr,  clint_paddr, plic_paddr;
logic        regs_psel,  uart_psel,   gpio_psel,  timer_psel;
logic        spi_psel,   clint_psel,  plic_psel;
logic        regs_pen,   uart_pen,    gpio_pen,   timer_pen;
logic        spi_pen,    clint_pen,   plic_pen;
logic        regs_pwrite,uart_pwrite, gpio_pwrite,timer_pwrite;
logic        spi_pwrite, clint_pwrite,plic_pwrite;
logic [31:0] regs_pwdata,uart_pwdata, gpio_pwdata,timer_pwdata;
logic [31:0] spi_pwdata, clint_pwdata,plic_pwdata;
logic [31:0] regs_prdata,uart_prdata, gpio_prdata,timer_prdata;
logic [31:0] spi_prdata, clint_prdata,plic_prdata;
logic        regs_pready,uart_pready, gpio_pready,timer_pready;
logic        spi_pready, clint_pready,plic_pready;
logic        regs_pslverr;

apb_demux u_apb_demux (
    .paddr       (apb_paddr),    .psel        (apb_psel),    .penable     (apb_penable),
    .pwrite      (apb_pwrite),   .pwdata      (apb_pwdata),  .pstrb       (apb_pstrb),
    .prdata      (apb_prdata),   .pready      (apb_pready),  .pslverr     (apb_pslverr),
    // Slave 0: generic regs
    .regs_paddr  (regs_paddr),   .regs_psel   (regs_psel),   .regs_penable(regs_pen),
    .regs_pwrite (regs_pwrite),  .regs_pwdata (regs_pwdata), .regs_prdata (regs_prdata),
    .regs_pready (regs_pready),  .regs_pslverr(regs_pslverr),
    // Slave 1: UART
    .uart_paddr  (uart_paddr),   .uart_psel   (uart_psel),   .uart_penable(uart_pen),
    .uart_pwrite (uart_pwrite),  .uart_pwdata (uart_pwdata), .uart_prdata (uart_prdata),  .uart_pready (uart_pready),
    // Slave 2: GPIO
    .gpio_paddr  (gpio_paddr),   .gpio_psel   (gpio_psel),   .gpio_penable(gpio_pen),
    .gpio_pwrite (gpio_pwrite),  .gpio_pwdata (gpio_pwdata), .gpio_prdata (gpio_prdata),  .gpio_pready (gpio_pready),
    // Slave 3: Timer
    .timer_paddr (timer_paddr),  .timer_psel  (timer_psel),  .timer_penable(timer_pen),
    .timer_pwrite(timer_pwrite), .timer_pwdata(timer_pwdata),.timer_prdata(timer_prdata), .timer_pready(timer_pready),
    // Slave 4: SPI
    .spi_paddr   (spi_paddr),    .spi_psel    (spi_psel),    .spi_penable (spi_pen),
    .spi_pwrite  (spi_pwrite),   .spi_pwdata  (spi_pwdata),  .spi_prdata  (spi_prdata),   .spi_pready  (spi_pready),
    // Slave 5: CLINT
    .clint_paddr (clint_paddr),  .clint_psel  (clint_psel),  .clint_penable(clint_pen),
    .clint_pwrite(clint_pwrite), .clint_pwdata(clint_pwdata),.clint_prdata(clint_prdata), .clint_pready(clint_pready),
    // Slave 6: PLIC
    .plic_paddr  (plic_paddr),   .plic_psel   (plic_psel),   .plic_penable(plic_pen),
    .plic_pwrite (plic_pwrite),  .plic_pwdata (plic_pwdata), .plic_prdata (plic_prdata),  .plic_pready (plic_pready)
);

// ── Slave 0: APB register file (Phase 5 backward compat, 0x1000_0xxx) ────────
apb_regs u_apb_regs (
    .clk      (clk),          .rst_n    (rst_n),
    .p_paddr  ({20'b0, regs_paddr}), .p_psel (regs_psel), .p_penable(regs_pen),
    .p_pwrite (regs_pwrite),  .p_pwdata (regs_pwdata), .p_pstrb  (4'hF),
    .p_prdata (regs_prdata),  .p_pready (regs_pready), .p_pslverr(regs_pslverr)
);

// ── UART (0x1000_1xxx) ────────────────────────────────────────────────────────
logic uart_irq_rx, uart_irq_tx;

uart u_uart (
    .clk         (clk),        .rst_n     (rst_n),
    .paddr       (uart_paddr), .psel      (uart_psel),   .penable    (uart_pen),
    .pwrite      (uart_pwrite),.pwdata    (uart_pwdata), .prdata     (uart_prdata),
    .pready      (uart_pready),
    .tx          (uart_tx_o),  .rx        (uart_rx_i),
    .irq_tx_empty(uart_irq_tx), .irq_rx_valid(uart_irq_rx)
);

// ── GPIO (0x1000_2xxx) ────────────────────────────────────────────────────────
logic gpio_irq;

gpio u_gpio (
    .clk      (clk),        .rst_n    (rst_n),
    .paddr    (gpio_paddr), .psel     (gpio_psel),   .penable  (gpio_pen),
    .pwrite   (gpio_pwrite),.pwdata   (gpio_pwdata), .prdata   (gpio_prdata),
    .pready   (gpio_pready),
    .gpio_in  (gpio_in_i),  .gpio_out (gpio_out_o),  .gpio_oe  (gpio_oe_o),
    .irq      (gpio_irq)
);

// ── Timer (0x1000_3xxx) ───────────────────────────────────────────────────────
logic        timer_mtip;
logic [31:0] timer_mtime_lo, timer_mtime_hi, timer_mtcmp_lo, timer_mtcmp_hi;
logic [31:0] clint_mtcmp_lo_wr, clint_mtcmp_hi_wr;
logic        clint_mtcmp_wr;

timer u_timer (
    .clk           (clk),           .rst_n         (rst_n),
    .paddr         (timer_paddr),   .psel          (timer_psel),   .penable       (timer_pen),
    .pwrite        (timer_pwrite),  .pwdata        (timer_pwdata), .prdata        (timer_prdata),
    .pready        (timer_pready),
    .mtip          (timer_mtip),
    .mtime_lo_o    (timer_mtime_lo), .mtime_hi_o   (timer_mtime_hi),
    .mtimecmp_lo_o (timer_mtcmp_lo), .mtimecmp_hi_o(timer_mtcmp_hi),
    .mtimecmp_lo_i (clint_mtcmp_lo_wr), .mtimecmp_hi_i(clint_mtcmp_hi_wr),
    .mtimecmp_wr_i (clint_mtcmp_wr)
);

// ── SPI (0x1000_4xxx) ─────────────────────────────────────────────────────────
spi u_spi (
    .clk    (clk),       .rst_n  (rst_n),
    .paddr  (spi_paddr), .psel   (spi_psel),   .penable(spi_pen),
    .pwrite (spi_pwrite),.pwdata (spi_pwdata), .prdata (spi_prdata),
    .pready (spi_pready),
    .sck    (spi_sck_o), .mosi   (spi_mosi_o), .miso   (spi_miso_i),
    .cs_n   (spi_cs_n_o)
);

// ── CLINT (0x1000_5xxx) ───────────────────────────────────────────────────────
clint u_clint (
    .clk           (clk),            .rst_n         (rst_n),
    .paddr         (clint_paddr),    .psel          (clint_psel),  .penable       (clint_pen),
    .pwrite        (clint_pwrite),   .pwdata        (clint_pwdata),.prdata        (clint_prdata),
    .pready        (clint_pready),
    .mtime_lo_i    (timer_mtime_lo), .mtime_hi_i    (timer_mtime_hi),
    .mtimecmp_lo_i (timer_mtcmp_lo), .mtimecmp_hi_i (timer_mtcmp_hi),
    .mtimecmp_lo_o (clint_mtcmp_lo_wr), .mtimecmp_hi_o(clint_mtcmp_hi_wr),
    .mtimecmp_wr_o (clint_mtcmp_wr),
    .mtip_i        (timer_mtip),     .mtip_o        (m_timer_irq),
    .msip_o        (m_sw_irq)
);

// ── PLIC (0x1000_6xxx) ────────────────────────────────────────────────────────
plic u_plic (
    .clk      (clk),       .rst_n  (rst_n),
    .paddr    (plic_paddr),.psel   (plic_psel),   .penable(plic_pen),
    .pwrite   (plic_pwrite),.pwdata(plic_pwdata), .prdata (plic_prdata),
    .pready   (plic_pready),
    .irq_src  ({4'b0, timer_mtip, gpio_irq, uart_irq_tx, uart_irq_rx}),
    .m_ext_irq(m_ext_irq)
);

// ── Phase 4: AI accelerator (0x5000_xxxx) ────────────────────────────────────
accel_top u_accel (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s2_awaddr), .s_awvalid(s2_awvalid), .s_awready(s2_awready),
    .s_wdata (s2_wdata),  .s_wstrb  (s2_wstrb),   .s_wvalid (s2_wvalid),  .s_wready(s2_wready),
    .s_bresp (s2_bresp),  .s_bvalid (s2_bvalid),  .s_bready (s2_bready),
    .s_araddr(s2_araddr), .s_arvalid(s2_arvalid), .s_arready(s2_arready),
    .s_rdata (s2_rdata),  .s_rresp  (s2_rresp),   .s_rvalid (s2_rvalid),  .s_rready(s2_rready)
);

assign pc_obs_o = imem_addr;

endmodule
