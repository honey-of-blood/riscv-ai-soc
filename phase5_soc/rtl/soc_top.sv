`timescale 1ns/1ps
// Phase 23 SoC top-level.
//
// Instruction path:
//   riscv_core ──→ icache (Ph15/23) ──→ Crossbar M2 ──→ S0 ──→ m_mem_*
//
// Data path:
//   riscv_core ──┬─ cacheable (0x0000_xxxx) ──→ cache_top (Ph2/23) ──→ m_cache_* (AXI4 burst)
//               └─ MMIO (0x1000_xxxx / 0x5000_xxxx) ──→ Crossbar M0
//
// Crossbar (Ph3) 3-master × 3-slave:
//   M0: MMIO adapter   (CPU MMIO accesses → S1/S2)
//   M1: DMA engine     (Ph9 scatter-gather → S0/S1/S2)
//   M2: I-cache refill (Ph23 → S0)
//
//   S0: m_mem_*        (0x0000_xxxx — external data/instr SRAM or DDR3)
//   S1: axi_apb_bridge (0x1000_xxxx — peripherals)
//   S2: accel_top_v2   (0x5000_xxxx — AI accelerator)
//
// D-cache dedicated AXI4 burst port:
//   m_cache_* — bypasses crossbar; backend connects directly to data SRAM.
//   This eliminates the burst_to_lite adapter (Ph23.2), cutting miss penalty
//   from ~16 cycles to ~6 cycles.
//
// CDC: UART RX and GPIO inputs are synchronised by cdc_sync2 before use.

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
    output logic [31:0] pc_obs_o,

    // ── Shared memory port (I-cache refill + DMA, AXI4-Lite via crossbar S0) ──
    output logic [31:0] m_mem_awaddr,
    output logic        m_mem_awvalid,
    input  logic        m_mem_awready,
    output logic [31:0] m_mem_wdata,
    output logic  [3:0] m_mem_wstrb,
    output logic        m_mem_wvalid,
    input  logic        m_mem_wready,
    input  logic  [1:0] m_mem_bresp,
    input  logic        m_mem_bvalid,
    output logic        m_mem_bready,
    output logic [31:0] m_mem_araddr,
    output logic        m_mem_arvalid,
    input  logic        m_mem_arready,
    input  logic [31:0] m_mem_rdata,
    input  logic  [1:0] m_mem_rresp,
    input  logic        m_mem_rvalid,
    output logic        m_mem_rready,

    // ── D-cache dedicated AXI4 burst port (Phase 23.2) ────────────────────
    // AXI4 write channel (dirty eviction)
    output logic [31:0] m_cache_awaddr,
    output logic  [7:0] m_cache_awlen,
    output logic  [2:0] m_cache_awsize,
    output logic  [1:0] m_cache_awburst,
    output logic        m_cache_awvalid,
    input  logic        m_cache_awready,
    output logic [31:0] m_cache_wdata,
    output logic  [3:0] m_cache_wstrb,
    output logic        m_cache_wvalid,
    output logic        m_cache_wlast,
    input  logic        m_cache_wready,
    input  logic  [1:0] m_cache_bresp,
    input  logic        m_cache_bvalid,
    output logic        m_cache_bready,
    // AXI4 read channel (cache fill)
    output logic [31:0] m_cache_araddr,
    output logic  [7:0] m_cache_arlen,
    output logic  [2:0] m_cache_arsize,
    output logic  [1:0] m_cache_arburst,
    output logic        m_cache_arvalid,
    input  logic        m_cache_arready,
    input  logic [31:0] m_cache_rdata,
    input  logic  [1:0] m_cache_rresp,
    input  logic        m_cache_rvalid,
    input  logic        m_cache_rlast,
    output logic        m_cache_rready
);

// ── CDC: synchronise async external inputs ────────────────────────────────
logic uart_rx_sync;
cdc_sync2 #(.W(1)) u_uart_rx_sync (.clk_dst(clk), .d(uart_rx_i),  .q(uart_rx_sync));

logic [15:0] gpio_in_sync;
cdc_sync2 #(.W(16)) u_gpio_in_sync (.clk_dst(clk), .d(gpio_in_i), .q(gpio_in_sync));

// ── Interrupt wires ───────────────────────────────────────────────────────
logic m_ext_irq, m_timer_irq, m_sw_irq;

// ── I-cache (Phase 23.1) — instruction fetch via AXI4-Lite refill ────────
logic [31:0] imem_addr, imem_rdata;
logic        icache_stall;

// AXI4-Lite master from icache → crossbar M2
logic [31:0] ic_araddr;
logic        ic_arvalid, ic_arready, ic_rvalid, ic_rready;
logic [31:0] ic_rdata;
logic  [1:0] ic_rresp;

icache u_icache (
    .clk         (clk),
    .rst_n       (rst_n),
    .flush_i     (1'b0),           // FENCE.I not implemented in this SoC revision
    .cpu_addr_i  (imem_addr),
    .cpu_rdata_o (imem_rdata),
    .cpu_stall_o (icache_stall),
    .m_araddr    (ic_araddr),
    .m_arvalid   (ic_arvalid),
    .m_arready   (ic_arready),
    .m_rdata     (ic_rdata),
    .m_rvalid    (ic_rvalid),
    .m_rready    (ic_rready)
);

// ── CPU ───────────────────────────────────────────────────────────────────
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
    .icache_stall_i(icache_stall),     // Phase 23.1: live I-cache stall
    .m_ext_irq_i   (m_ext_irq),
    .m_timer_irq_i (m_timer_irq),
    .m_sw_irq_i    (m_sw_irq),
    // Debug ports — not wired in SoC (Phase 14 debug module is standalone)
    .dbg_halt_req_i    (1'b0),
    .dbg_halted_o      (),
    .dbg_resume_req_i  (1'b0),
    .dbg_pc_o          (),
    .dbg_rf_addr_i     (5'b0),
    .dbg_rf_rdata_o    (),
    .dbg_rf_wdata_i    (32'b0),
    .dbg_rf_we_i       (1'b0),
    .dbg_imem_ovr_en_i (1'b0),
    .dbg_imem_ovr_data_i(32'b0),
    .dbg_jump_en_i     (1'b0),
    .dbg_jump_target_i (32'b0),
    .trigger_halt_i    (1'b0),
    .tselect_we_o      (),
    .tselect_wd_o      (),
    .tdata1_we_o       (),
    .tdata1_wd_o       (),
    .tdata2_we_o       (),
    .tdata2_wd_o       (),
    .tselect_rd_i      (32'b0),
    .tdata1_rd_i       (32'b0),
    .tdata2_rd_i       (32'b0),
    .dbg_mem_addr_o    (),
    .dbg_mem_we_o      (),
    .dbg_mem_re_o      ()
);

// ── Address routing: cacheable vs MMIO ───────────────────────────────────
logic is_mmio;
assign is_mmio = (dmem_addr[31:16] == 16'h1000) |
                 (dmem_addr[31:17] == 15'h2800);

logic cpu_cache_re, cpu_cache_we;
logic cpu_mmio_re,  cpu_mmio_we;
assign cpu_cache_re = dmem_re & ~is_mmio;
assign cpu_cache_we = dmem_we & ~is_mmio;
assign cpu_mmio_re  = dmem_re &  is_mmio;
assign cpu_mmio_we  = dmem_we &  is_mmio;

// ── Phase 2/23: L1 data cache — direct AXI4 burst port (bypasses crossbar) ──
logic [31:0] cache_rdata;
logic        cache_stall;

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
    // AXI4 burst master → m_cache_* (Phase 23.2: no burst_to_lite)
    .m_axi_awvalid_o (m_cache_awvalid),  .m_axi_awready_i (m_cache_awready),
    .m_axi_awaddr_o  (m_cache_awaddr),   .m_axi_awlen_o   (m_cache_awlen),
    .m_axi_awsize_o  (m_cache_awsize),   .m_axi_awburst_o (m_cache_awburst),
    .m_axi_wvalid_o  (m_cache_wvalid),   .m_axi_wready_i  (m_cache_wready),
    .m_axi_wdata_o   (m_cache_wdata),    .m_axi_wstrb_o   (m_cache_wstrb),
    .m_axi_wlast_o   (m_cache_wlast),
    .m_axi_bvalid_i  (m_cache_bvalid),   .m_axi_bready_o  (m_cache_bready),
    .m_axi_arvalid_o (m_cache_arvalid),  .m_axi_arready_i (m_cache_arready),
    .m_axi_araddr_o  (m_cache_araddr),   .m_axi_arlen_o   (m_cache_arlen),
    .m_axi_arsize_o  (m_cache_arsize),   .m_axi_arburst_o (m_cache_arburst),
    .m_axi_rvalid_i  (m_cache_rvalid),   .m_axi_rready_o  (m_cache_rready),
    .m_axi_rdata_i   (m_cache_rdata),    .m_axi_rlast_i   (m_cache_rlast)
);

// ── MMIO adapter: CPU → crossbar M0 (MMIO/accel addresses) ───────────────
logic [31:0] mmio_rdata;
logic        mmio_stall;

logic [31:0] m0_awaddr, m0_wdata, m0_araddr, m0_rdata;
logic  [3:0] m0_wstrb;
logic  [1:0] m0_bresp, m0_rresp;
logic        m0_awvalid, m0_awready, m0_wvalid, m0_wready;
logic        m0_bvalid, m0_bready;
logic        m0_arvalid, m0_arready, m0_rvalid, m0_rready;

dmem_axi_adapter u_adapter (
    .clk        (clk),        .rst_n      (rst_n),
    .cpu_re_i   (cpu_mmio_re), .cpu_we_i  (cpu_mmio_we),
    .cpu_addr_i (dmem_addr),   .cpu_wdata_i(dmem_wdata),
    .cpu_be_i   (dmem_be),
    .cpu_rdata_o(mmio_rdata),  .cpu_stall_o(mmio_stall),
    .m_awaddr   (m0_awaddr),   .m_awvalid(m0_awvalid), .m_awready(m0_awready),
    .m_wdata    (m0_wdata),    .m_wstrb  (m0_wstrb),
    .m_wvalid   (m0_wvalid),   .m_wready (m0_wready),
    .m_bresp    (m0_bresp),    .m_bvalid (m0_bvalid),  .m_bready (m0_bready),
    .m_araddr   (m0_araddr),   .m_arvalid(m0_arvalid), .m_arready(m0_arready),
    .m_rdata    (m0_rdata),    .m_rresp  (m0_rresp),
    .m_rvalid   (m0_rvalid),   .m_rready (m0_rready)
);

assign dmem_rdata = is_mmio ? mmio_rdata : cache_rdata;
assign dmem_stall = is_mmio ? mmio_stall : cache_stall;

// ── DMA engine: crossbar M1 (AXI4-Lite scatter-gather) ───────────────────
logic [31:0] m1_awaddr, m1_wdata, m1_araddr;
logic  [3:0] m1_wstrb;
logic        m1_awvalid, m1_wvalid, m1_bready, m1_arvalid, m1_rready;
logic [31:0] m1_rdata;
logic  [1:0] m1_bresp, m1_rresp;
logic        m1_awready, m1_wready, m1_bvalid, m1_arready, m1_rvalid;
logic        dma_irq_ch0, dma_irq_ch1;

// APB DMA config wires (driven by apb_demux below)
logic [11:0] dma_paddr;
logic        dma_psel, dma_pen, dma_pwrite;
logic [31:0] dma_pwdata, dma_prdata;
logic        dma_pready;

dma u_dma (
    .clk       (clk),      .rst_n     (rst_n),
    .paddr     (dma_paddr),.psel      (dma_psel),   .penable  (dma_pen),
    .pwrite    (dma_pwrite),.pwdata   (dma_pwdata), .prdata   (dma_prdata),
    .pready    (dma_pready),
    .m_awaddr  (m1_awaddr), .m_awvalid(m1_awvalid), .m_awready(m1_awready),
    .m_wdata   (m1_wdata),  .m_wstrb  (m1_wstrb),   .m_wvalid (m1_wvalid),
    .m_wready  (m1_wready), .m_bresp  (m1_bresp),   .m_bvalid (m1_bvalid),
    .m_bready  (m1_bready),
    .m_araddr  (m1_araddr), .m_arvalid(m1_arvalid), .m_arready(m1_arready),
    .m_rdata   (m1_rdata),  .m_rresp  (m1_rresp),   .m_rvalid (m1_rvalid),
    .m_rready  (m1_rready),
    .irq_ch0   (dma_irq_ch0), .irq_ch1(dma_irq_ch1)
);

// ── I-cache refill: crossbar M2 (AXI4-Lite, read-only) ───────────────────
// icache only uses the AR/R channels; AW/W/B are tied off.
logic [31:0] m2_awaddr, m2_wdata, m2_araddr;
logic  [3:0] m2_wstrb;
logic        m2_awvalid, m2_wvalid, m2_bready, m2_arvalid, m2_rready;
logic [31:0] m2_rdata;
logic  [1:0] m2_bresp, m2_rresp;
logic        m2_awready, m2_wready, m2_bvalid, m2_arready, m2_rvalid;

// AW/W/B channels unused by icache
assign m2_awaddr  = 32'b0;
assign m2_awvalid = 1'b0;
assign m2_wdata   = 32'b0;
assign m2_wstrb   = 4'b0;
assign m2_wvalid  = 1'b0;
assign m2_bready  = 1'b1;

// AR/R channels: icache refill
assign m2_araddr  = ic_araddr;
assign m2_arvalid = ic_arvalid;
assign ic_arready = m2_arready;
assign ic_rdata   = m2_rdata;
assign ic_rvalid  = m2_rvalid;
assign m2_rready  = ic_rready;
assign ic_rresp   = m2_rresp;

// ── Crossbar slave wires ──────────────────────────────────────────────────
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

// ── AXI4 crossbar: 3M × 3S ───────────────────────────────────────────────
axi4_crossbar u_xbar (
    .clk(clk), .rst_n(rst_n),
    // M0: MMIO adapter
    .m0_awaddr(m0_awaddr), .m0_awvalid(m0_awvalid), .m0_awready(m0_awready),
    .m0_wdata (m0_wdata),  .m0_wstrb  (m0_wstrb),   .m0_wvalid (m0_wvalid),  .m0_wready(m0_wready),
    .m0_bresp (m0_bresp),  .m0_bvalid (m0_bvalid),  .m0_bready (m0_bready),
    .m0_araddr(m0_araddr), .m0_arvalid(m0_arvalid), .m0_arready(m0_arready),
    .m0_rdata (m0_rdata),  .m0_rresp  (m0_rresp),   .m0_rvalid (m0_rvalid),  .m0_rready(m0_rready),
    // M1: DMA engine
    .m1_awaddr(m1_awaddr), .m1_awvalid(m1_awvalid), .m1_awready(m1_awready),
    .m1_wdata (m1_wdata),  .m1_wstrb  (m1_wstrb),   .m1_wvalid (m1_wvalid),  .m1_wready(m1_wready),
    .m1_bresp (m1_bresp),  .m1_bvalid (m1_bvalid),  .m1_bready (m1_bready),
    .m1_araddr(m1_araddr), .m1_arvalid(m1_arvalid), .m1_arready(m1_arready),
    .m1_rdata (m1_rdata),  .m1_rresp  (m1_rresp),   .m1_rvalid (m1_rvalid),  .m1_rready(m1_rready),
    // M2: I-cache refill
    .m2_awaddr(m2_awaddr), .m2_awvalid(m2_awvalid), .m2_awready(m2_awready),
    .m2_wdata (m2_wdata),  .m2_wstrb  (m2_wstrb),   .m2_wvalid (m2_wvalid),  .m2_wready(m2_wready),
    .m2_bresp (m2_bresp),  .m2_bvalid (m2_bvalid),  .m2_bready (m2_bready),
    .m2_araddr(m2_araddr), .m2_arvalid(m2_arvalid), .m2_arready(m2_arready),
    .m2_rdata (m2_rdata),  .m2_rresp  (m2_rresp),   .m2_rvalid (m2_rvalid),  .m2_rready(m2_rready),
    // S0: shared memory (I-cache + DMA)
    .s0_awaddr(s0_awaddr), .s0_awvalid(s0_awvalid), .s0_awready(s0_awready),
    .s0_wdata (s0_wdata),  .s0_wstrb  (s0_wstrb),   .s0_wvalid (s0_wvalid),  .s0_wready(s0_wready),
    .s0_bresp (s0_bresp),  .s0_bvalid (s0_bvalid),  .s0_bready (s0_bready),
    .s0_araddr(s0_araddr), .s0_arvalid(s0_arvalid), .s0_arready(s0_arready),
    .s0_rdata (s0_rdata),  .s0_rresp  (s0_rresp),   .s0_rvalid (s0_rvalid),  .s0_rready(s0_rready),
    // S1: APB bridge
    .s1_awaddr(s1_awaddr), .s1_awvalid(s1_awvalid), .s1_awready(s1_awready),
    .s1_wdata (s1_wdata),  .s1_wstrb  (s1_wstrb),   .s1_wvalid (s1_wvalid),  .s1_wready(s1_wready),
    .s1_bresp (s1_bresp),  .s1_bvalid (s1_bvalid),  .s1_bready (s1_bready),
    .s1_araddr(s1_araddr), .s1_arvalid(s1_arvalid), .s1_arready(s1_arready),
    .s1_rdata (s1_rdata),  .s1_rresp  (s1_rresp),   .s1_rvalid (s1_rvalid),  .s1_rready(s1_rready),
    // S2: accelerator
    .s2_awaddr(s2_awaddr), .s2_awvalid(s2_awvalid), .s2_awready(s2_awready),
    .s2_wdata (s2_wdata),  .s2_wstrb  (s2_wstrb),   .s2_wvalid (s2_wvalid),  .s2_wready(s2_wready),
    .s2_bresp (s2_bresp),  .s2_bvalid (s2_bvalid),  .s2_bready (s2_bready),
    .s2_araddr(s2_araddr), .s2_arvalid(s2_arvalid), .s2_arready(s2_arready),
    .s2_rdata (s2_rdata),  .s2_rresp  (s2_rresp),   .s2_rvalid (s2_rvalid),  .s2_rready(s2_rready)
);

// ── Slave 0: External memory port (0x0000_xxxx) ───────────────────────────
assign m_mem_awaddr  = s0_awaddr;  assign s0_awready = m_mem_awready;
assign m_mem_awvalid = s0_awvalid;
assign m_mem_wdata   = s0_wdata;   assign s0_wready  = m_mem_wready;
assign m_mem_wstrb   = s0_wstrb;
assign m_mem_wvalid  = s0_wvalid;
assign s0_bresp      = m_mem_bresp;  assign s0_bvalid = m_mem_bvalid;
assign m_mem_bready  = s0_bready;
assign m_mem_araddr  = s0_araddr;  assign s0_arready = m_mem_arready;
assign m_mem_arvalid = s0_arvalid;
assign s0_rdata      = m_mem_rdata;  assign s0_rresp = m_mem_rresp;
assign s0_rvalid     = m_mem_rvalid; assign m_mem_rready = s0_rready;

// ── APB bus ───────────────────────────────────────────────────────────────
logic [31:0] apb_paddr;
logic        apb_psel, apb_penable, apb_pwrite;
logic [31:0] apb_pwdata;
logic  [3:0] apb_pstrb;
logic [31:0] apb_prdata;
logic        apb_pready, apb_pslverr;

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

// ── APB peripheral wires ──────────────────────────────────────────────────
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
    .regs_paddr  (regs_paddr),   .regs_psel   (regs_psel),   .regs_penable(regs_pen),
    .regs_pwrite (regs_pwrite),  .regs_pwdata (regs_pwdata), .regs_prdata (regs_prdata),
    .regs_pready (regs_pready),  .regs_pslverr(regs_pslverr),
    .uart_paddr  (uart_paddr),   .uart_psel   (uart_psel),   .uart_penable(uart_pen),
    .uart_pwrite (uart_pwrite),  .uart_pwdata (uart_pwdata), .uart_prdata (uart_prdata),  .uart_pready (uart_pready),
    .gpio_paddr  (gpio_paddr),   .gpio_psel   (gpio_psel),   .gpio_penable(gpio_pen),
    .gpio_pwrite (gpio_pwrite),  .gpio_pwdata (gpio_pwdata), .gpio_prdata (gpio_prdata),  .gpio_pready (gpio_pready),
    .timer_paddr (timer_paddr),  .timer_psel  (timer_psel),  .timer_penable(timer_pen),
    .timer_pwrite(timer_pwrite), .timer_pwdata(timer_pwdata),.timer_prdata(timer_prdata), .timer_pready(timer_pready),
    .spi_paddr   (spi_paddr),    .spi_psel    (spi_psel),    .spi_penable (spi_pen),
    .spi_pwrite  (spi_pwrite),   .spi_pwdata  (spi_pwdata),  .spi_prdata  (spi_prdata),   .spi_pready  (spi_pready),
    .clint_paddr (clint_paddr),  .clint_psel  (clint_psel),  .clint_penable(clint_pen),
    .clint_pwrite(clint_pwrite), .clint_pwdata(clint_pwdata),.clint_prdata(clint_prdata), .clint_pready(clint_pready),
    .plic_paddr  (plic_paddr),   .plic_psel   (plic_psel),   .plic_penable(plic_pen),
    .plic_pwrite (plic_pwrite),  .plic_pwdata (plic_pwdata), .plic_prdata (plic_prdata),  .plic_pready (plic_pready),
    .dma_paddr   (),             .dma_psel    (),             .dma_penable (),
    .dma_pwrite  (),             .dma_pwdata  (),             .dma_prdata  (dma_prdata),   .dma_pready  (dma_pready)
);

// ── APB peripheral instantiations (unchanged from Phase 22) ───────────────
apb_regs u_apb_regs (
    .clk(clk), .rst_n(rst_n),
    .p_paddr({20'b0, regs_paddr}), .p_psel(regs_psel), .p_penable(regs_pen),
    .p_pwrite(regs_pwrite), .p_pwdata(regs_pwdata), .p_pstrb(4'hF),
    .p_prdata(regs_prdata), .p_pready(regs_pready), .p_pslverr(regs_pslverr)
);

logic uart_irq_rx, uart_irq_tx;
uart u_uart (
    .clk(clk), .rst_n(rst_n),
    .paddr(uart_paddr), .psel(uart_psel), .penable(uart_pen),
    .pwrite(uart_pwrite), .pwdata(uart_pwdata), .prdata(uart_prdata),
    .pready(uart_pready),
    .tx(uart_tx_o), .rx(uart_rx_sync),   // Phase 23.5: synchronized RX
    .irq_tx_empty(uart_irq_tx), .irq_rx_valid(uart_irq_rx)
);

logic gpio_irq;
gpio u_gpio (
    .clk(clk), .rst_n(rst_n),
    .paddr(gpio_paddr), .psel(gpio_psel), .penable(gpio_pen),
    .pwrite(gpio_pwrite), .pwdata(gpio_pwdata), .prdata(gpio_prdata),
    .pready(gpio_pready),
    .gpio_in(gpio_in_sync), .gpio_out(gpio_out_o), .gpio_oe(gpio_oe_o),  // Phase 23.5
    .irq(gpio_irq)
);

logic        timer_mtip;
logic [31:0] timer_mtime_lo, timer_mtime_hi, timer_mtcmp_lo, timer_mtcmp_hi;
logic [31:0] clint_mtcmp_lo_wr, clint_mtcmp_hi_wr;
logic        clint_mtcmp_wr;

timer u_timer (
    .clk(clk), .rst_n(rst_n),
    .paddr(timer_paddr), .psel(timer_psel), .penable(timer_pen),
    .pwrite(timer_pwrite), .pwdata(timer_pwdata), .prdata(timer_prdata),
    .pready(timer_pready),
    .mtip(timer_mtip),
    .mtime_lo_o(timer_mtime_lo), .mtime_hi_o(timer_mtime_hi),
    .mtimecmp_lo_o(timer_mtcmp_lo), .mtimecmp_hi_o(timer_mtcmp_hi),
    .mtimecmp_lo_i(clint_mtcmp_lo_wr), .mtimecmp_hi_i(clint_mtcmp_hi_wr),
    .mtimecmp_wr_i(clint_mtcmp_wr)
);

spi u_spi (
    .clk(clk), .rst_n(rst_n),
    .paddr(spi_paddr), .psel(spi_psel), .penable(spi_pen),
    .pwrite(spi_pwrite), .pwdata(spi_pwdata), .prdata(spi_prdata),
    .pready(spi_pready),
    .sck(spi_sck_o), .mosi(spi_mosi_o), .miso(spi_miso_i), .cs_n(spi_cs_n_o)
);

clint u_clint (
    .clk(clk), .rst_n(rst_n),
    .paddr(clint_paddr), .psel(clint_psel), .penable(clint_pen),
    .pwrite(clint_pwrite), .pwdata(clint_pwdata), .prdata(clint_prdata),
    .pready(clint_pready),
    .mtime_lo_i(timer_mtime_lo), .mtime_hi_i(timer_mtime_hi),
    .mtimecmp_lo_i(timer_mtcmp_lo), .mtimecmp_hi_i(timer_mtcmp_hi),
    .mtimecmp_lo_o(clint_mtcmp_lo_wr), .mtimecmp_hi_o(clint_mtcmp_hi_wr),
    .mtimecmp_wr_o(clint_mtcmp_wr),
    .mtip_i(timer_mtip), .mtip_o(m_timer_irq),
    .msip_o(m_sw_irq)
);

logic accel_irq_done;
plic u_plic (
    .clk(clk), .rst_n(rst_n),
    .paddr(plic_paddr), .psel(plic_psel), .penable(plic_pen),
    .pwrite(plic_pwrite), .pwdata(plic_pwdata), .prdata(plic_prdata),
    .pready(plic_pready),
    .irq_src({1'b0, accel_irq_done, dma_irq_ch1, dma_irq_ch0,
              timer_mtip, gpio_irq, uart_irq_tx, uart_irq_rx}),
    .m_ext_irq(m_ext_irq)
);

// ── Slave 2: Accelerator (0x5000_xxxx) ───────────────────────────────────
accel_top_v2 #(.N(4)) u_accel (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s2_awaddr), .s_awvalid(s2_awvalid), .s_awready(s2_awready),
    .s_wdata (s2_wdata),  .s_wstrb  (s2_wstrb),   .s_wvalid (s2_wvalid),  .s_wready(s2_wready),
    .s_bresp (s2_bresp),  .s_bvalid (s2_bvalid),  .s_bready (s2_bready),
    .s_araddr(s2_araddr), .s_arvalid(s2_arvalid), .s_arready(s2_arready),
    .s_rdata (s2_rdata),  .s_rresp  (s2_rresp),   .s_rvalid (s2_rvalid),  .s_rready(s2_rready),
    .irq_done(accel_irq_done)
);

assign pc_obs_o = imem_addr;

endmodule
