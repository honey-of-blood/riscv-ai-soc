`timescale 1ns/1ps
// Phase 5 SoC top-level — all four phases integrated.
//
// Data path:
//   riscv_core (Ph1) ─┬─ cacheable (0x0000_xxxx / 0x1000_xxxx) ──→ cache_top (Ph2)
//                     │                                                  │ AXI4 burst
//                     │                                        axi4_burst_to_lite
//                     │                                                  │ AXI4-Lite
//                     └─ MMIO (0x5000_xxxx) ──→ dmem_axi_adapter
//                                                          │
//                                             axi4_crossbar (Ph3) M0/M1
//                                              ├── S0: axi_sram        (data)
//                                              ├── S1: axi_apb_bridge → apb_regs
//                                              └── S2: accel_top       (Ph4)
//
// Address map (crossbar decodes addr[31:16]):
//   0x0000_xxxx → SRAM0         (64 KB data memory, cached)
//   0x1000_xxxx → APB bridge    (APB register file, cached path)
//   0x5000_xxxx → accel_top MMIO (non-cached, adapter bypass)

module soc_top (
    input  logic clk,
    input  logic rst_n
);

// ── Instruction memory ────────────────────────────────────────────────────────
logic [31:0] imem_addr, imem_rdata;
instr_rom u_irom (.clk(clk), .addr(imem_addr), .rdata(imem_rdata));

// ── CPU ───────────────────────────────────────────────────────────────────────
logic [31:0] dmem_addr, dmem_wdata, dmem_rdata;
logic        dmem_we, dmem_re, dmem_stall;
logic  [3:0] dmem_be;

riscv_core u_cpu (
    .clk          (clk),
    .rst          (~rst_n),
    .imem_addr_o  (imem_addr),
    .imem_rdata_i (imem_rdata),
    .dmem_addr_o  (dmem_addr),
    .dmem_wdata_o (dmem_wdata),
    .dmem_we_o    (dmem_we),
    .dmem_re_o    (dmem_re),
    .dmem_be_o    (dmem_be),
    .dmem_rdata_i (dmem_rdata),
    .dmem_stall_i (dmem_stall)
);

// ── Address routing: cache vs MMIO bypass ────────────────────────────────────
// MMIO region (0x5000_xxxx) is non-cacheable; all others go through L1 cache.
logic is_mmio;
assign is_mmio = (dmem_addr[31:16] == 16'h5000);

logic        cpu_cache_re, cpu_cache_we;
logic        cpu_mmio_re,  cpu_mmio_we;
assign cpu_cache_re = dmem_re & ~is_mmio;
assign cpu_cache_we = dmem_we & ~is_mmio;
assign cpu_mmio_re  = dmem_re &  is_mmio;
assign cpu_mmio_we  = dmem_we &  is_mmio;

// ── Phase 2: L1 data cache ────────────────────────────────────────────────────
logic [31:0] cache_rdata;
logic        cache_stall;

// Cache AXI4 burst master wires → burst-to-lite bridge slave port
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
    .clk            (clk),
    .rst            (~rst_n),
    // CPU side
    .cpu_re_i       (cpu_cache_re),
    .cpu_we_i       (cpu_cache_we),
    .cpu_addr_i     (dmem_addr),
    .cpu_wdata_i    (dmem_wdata),
    .cpu_be_i       (dmem_be),
    .cpu_rdata_o    (cache_rdata),
    .cpu_stall_o    (cache_stall),
    // AXI4 burst master → bridge
    .m_axi_awvalid_o(c_awvalid),  .m_axi_awready_i(c_awready),
    .m_axi_awaddr_o (c_awaddr),   .m_axi_awlen_o  (c_awlen),
    .m_axi_awsize_o (c_awsize),   .m_axi_awburst_o(c_awburst),
    .m_axi_wvalid_o (c_wvalid),   .m_axi_wready_i (c_wready),
    .m_axi_wdata_o  (c_wdata),    .m_axi_wstrb_o  (c_wstrb),
    .m_axi_wlast_o  (c_wlast),
    .m_axi_bvalid_i (c_bvalid),   .m_axi_bready_o (c_bready),
    .m_axi_arvalid_o(c_arvalid),  .m_axi_arready_i(c_arready),
    .m_axi_araddr_o (c_araddr),   .m_axi_arlen_o  (c_arlen),
    .m_axi_arsize_o (c_arsize),   .m_axi_arburst_o(c_arburst),
    .m_axi_rvalid_i (c_rvalid),   .m_axi_rready_o (c_rready),
    .m_axi_rdata_i  (c_rdata),    .m_axi_rlast_i  (c_rlast)
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
    // from cache
    .s_awaddr  (c_awaddr),  .s_awvalid (c_awvalid),  .s_awready (c_awready),
    .s_wdata   (c_wdata),   .s_wstrb   (c_wstrb),    .s_wlast   (c_wlast),
    .s_wvalid  (c_wvalid),  .s_wready  (c_wready),
    .s_bresp   (c_bresp),   .s_bvalid  (c_bvalid),   .s_bready  (c_bready),
    .s_araddr  (c_araddr),  .s_arvalid (c_arvalid),  .s_arready (c_arready),
    .s_rdata   (c_rdata),   .s_rresp   (c_rresp),    .s_rlast   (c_rlast),
    .s_rvalid  (c_rvalid),  .s_rready  (c_rready),
    // to crossbar m0
    .m_awaddr  (m0_awaddr), .m_awvalid (m0_awvalid), .m_awready (m0_awready),
    .m_wdata   (m0_wdata),  .m_wstrb   (m0_wstrb),   .m_wvalid  (m0_wvalid),
    .m_wready  (m0_wready),
    .m_bresp   (m0_bresp),  .m_bvalid  (m0_bvalid),  .m_bready  (m0_bready),
    .m_araddr  (m0_araddr), .m_arvalid (m0_arvalid), .m_arready (m0_arready),
    .m_rdata   (m0_rdata),  .m_rresp   (m0_rresp),   .m_rvalid  (m0_rvalid),
    .m_rready  (m0_rready)
);

// ── MMIO adapter: CPU → crossbar master 1 (0x5000_xxxx bypass) ───────────────
logic [31:0] mmio_rdata;
logic        mmio_stall;

logic [31:0] m1_awaddr, m1_wdata, m1_araddr, m1_rdata;
logic  [3:0] m1_wstrb;
logic  [1:0] m1_bresp, m1_rresp;
logic        m1_awvalid, m1_awready, m1_wvalid, m1_wready;
logic        m1_bvalid, m1_bready;
logic        m1_arvalid, m1_arready, m1_rvalid, m1_rready;

dmem_axi_adapter u_adapter (
    .clk        (clk), .rst_n      (rst_n),
    .cpu_re_i   (cpu_mmio_re),   .cpu_we_i   (cpu_mmio_we),
    .cpu_addr_i (dmem_addr),     .cpu_wdata_i(dmem_wdata),
    .cpu_be_i   (dmem_be),
    .cpu_rdata_o(mmio_rdata),    .cpu_stall_o(mmio_stall),
    .m_awaddr   (m1_awaddr),  .m_awvalid(m1_awvalid), .m_awready(m1_awready),
    .m_wdata    (m1_wdata),   .m_wstrb  (m1_wstrb),
    .m_wvalid   (m1_wvalid),  .m_wready (m1_wready),
    .m_bresp    (m1_bresp),   .m_bvalid (m1_bvalid),  .m_bready (m1_bready),
    .m_araddr   (m1_araddr),  .m_arvalid(m1_arvalid), .m_arready(m1_arready),
    .m_rdata    (m1_rdata),   .m_rresp  (m1_rresp),
    .m_rvalid   (m1_rvalid),  .m_rready (m1_rready)
);

// ── CPU dmem mux: select cache or MMIO path ───────────────────────────────────
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

// ── Slave 0: SRAM — data memory (0x0000_xxxx) ────────────────────────────────
axi_sram u_sram0 (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s0_awaddr), .s_awvalid(s0_awvalid), .s_awready(s0_awready),
    .s_wdata (s0_wdata),  .s_wstrb  (s0_wstrb),   .s_wvalid (s0_wvalid),  .s_wready(s0_wready),
    .s_bresp (s0_bresp),  .s_bvalid (s0_bvalid),  .s_bready (s0_bready),
    .s_araddr(s0_araddr), .s_arvalid(s0_arvalid), .s_arready(s0_arready),
    .s_rdata (s0_rdata),  .s_rresp  (s0_rresp),   .s_rvalid (s0_rvalid),  .s_rready(s0_rready)
);

// ── APB bus between bridge and register file ──────────────────────────────────
logic [31:0] apb_paddr;
logic        apb_psel, apb_penable, apb_pwrite;
logic [31:0] apb_pwdata;
logic  [3:0] apb_pstrb;
logic [31:0] apb_prdata;
logic        apb_pready, apb_pslverr;

// ── Slave 1: AXI-APB bridge → APB register file (0x1000_xxxx) ────────────────
axi_apb_bridge u_apb_bridge (
    .clk      (clk),          .rst_n    (rst_n),
    .s_awaddr (s1_awaddr),    .s_awvalid(s1_awvalid),   .s_awready(s1_awready),
    .s_wdata  (s1_wdata),     .s_wstrb  (s1_wstrb),     .s_wvalid (s1_wvalid),  .s_wready(s1_wready),
    .s_bresp  (s1_bresp),     .s_bvalid (s1_bvalid),    .s_bready (s1_bready),
    .s_araddr (s1_araddr),    .s_arvalid(s1_arvalid),   .s_arready(s1_arready),
    .s_rdata  (s1_rdata),     .s_rresp  (s1_rresp),     .s_rvalid (s1_rvalid),  .s_rready(s1_rready),
    .p_paddr  (apb_paddr),    .p_psel   (apb_psel),     .p_penable(apb_penable),
    .p_pwrite (apb_pwrite),   .p_pwdata (apb_pwdata),   .p_pstrb  (apb_pstrb),
    .p_prdata (apb_prdata),   .p_pready (apb_pready),   .p_pslverr(apb_pslverr)
);

apb_regs u_apb_regs (
    .clk      (clk),          .rst_n    (rst_n),
    .p_paddr  (apb_paddr),    .p_psel   (apb_psel),     .p_penable(apb_penable),
    .p_pwrite (apb_pwrite),   .p_pwdata (apb_pwdata),   .p_pstrb  (apb_pstrb),
    .p_prdata (apb_prdata),   .p_pready (apb_pready),   .p_pslverr(apb_pslverr)
);

// ── Phase 4: AI accelerator (0x5000_xxxx) ─────────────────────────────────────
accel_top u_accel (
    .clk(clk), .rst_n(rst_n),
    .s_awaddr(s2_awaddr), .s_awvalid(s2_awvalid), .s_awready(s2_awready),
    .s_wdata (s2_wdata),  .s_wstrb  (s2_wstrb),   .s_wvalid (s2_wvalid),  .s_wready(s2_wready),
    .s_bresp (s2_bresp),  .s_bvalid (s2_bvalid),  .s_bready (s2_bready),
    .s_araddr(s2_araddr), .s_arvalid(s2_arvalid), .s_arready(s2_arready),
    .s_rdata (s2_rdata),  .s_rresp  (s2_rresp),   .s_rvalid (s2_rvalid),  .s_rready(s2_rready)
);

endmodule
