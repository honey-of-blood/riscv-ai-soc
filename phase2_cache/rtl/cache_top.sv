`timescale 1ns/1ps

// Top-level L1 data cache.
// Instantiates: cache_controller, cache_tag_array, cache_data_array.
// CPU side: matches Phase 1 riscv_core dmem port (add cpu_stall_o).
// Memory side: AXI4 master (INCR burst, 4-word lines).
module cache_top (
    input  logic        clk,
    input  logic        rst,

    // ── CPU (dmem) interface ───────────────────────────────────────────────
    input  logic        cpu_re_i,
    input  logic        cpu_we_i,
    input  logic [31:0] cpu_addr_i,
    input  logic [31:0] cpu_wdata_i,
    input  logic [3:0]  cpu_be_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,

    // ── AXI4 master (memory side) — write channel ─────────────────────────
    output logic        m_axi_awvalid_o,
    input  logic        m_axi_awready_i,
    output logic [31:0] m_axi_awaddr_o,
    output logic [7:0]  m_axi_awlen_o,
    output logic [2:0]  m_axi_awsize_o,
    output logic [1:0]  m_axi_awburst_o,

    output logic        m_axi_wvalid_o,
    input  logic        m_axi_wready_i,
    output logic [31:0] m_axi_wdata_o,
    output logic [3:0]  m_axi_wstrb_o,
    output logic        m_axi_wlast_o,

    input  logic        m_axi_bvalid_i,
    output logic        m_axi_bready_o,

    // ── AXI4 master (memory side) — read channel ──────────────────────────
    output logic        m_axi_arvalid_o,
    input  logic        m_axi_arready_i,
    output logic [31:0] m_axi_araddr_o,
    output logic [7:0]  m_axi_arlen_o,
    output logic [2:0]  m_axi_arsize_o,
    output logic [1:0]  m_axi_arburst_o,

    input  logic        m_axi_rvalid_i,
    output logic        m_axi_rready_o,
    input  logic [31:0] m_axi_rdata_i,
    input  logic        m_axi_rlast_i
);

    // ── Wires between controller and tag array ────────────────────────────
    logic        tag_we;
    logic [5:0]  tag_idx;
    logic [21:0] tag_tag_w;
    logic        tag_valid_w, tag_dirty_w;
    logic [21:0] tag_tag_r;
    logic        tag_valid_r, tag_dirty_r;

    // ── Wires between controller and data array ───────────────────────────
    logic        data_we;
    logic [5:0]  data_idx;
    logic [1:0]  data_word;
    logic [3:0]  data_be;
    logic [31:0] data_wdata;
    logic [31:0] data_w0, data_w1, data_w2, data_w3;

    // =========================================================================
    // Sub-module instantiations
    // =========================================================================

    cache_controller u_ctrl (
        .clk              (clk),
        .rst              (rst),
        // CPU
        .cpu_re_i         (cpu_re_i),
        .cpu_we_i         (cpu_we_i),
        .cpu_addr_i       (cpu_addr_i),
        .cpu_wdata_i      (cpu_wdata_i),
        .cpu_be_i         (cpu_be_i),
        .cpu_rdata_o      (cpu_rdata_o),
        .cpu_stall_o      (cpu_stall_o),
        // Tag array
        .tag_we_o         (tag_we),
        .tag_idx_o        (tag_idx),
        .tag_tag_o        (tag_tag_w),
        .tag_valid_o      (tag_valid_w),
        .tag_dirty_o      (tag_dirty_w),
        .tag_tag_i        (tag_tag_r),
        .tag_valid_i      (tag_valid_r),
        .tag_dirty_i      (tag_dirty_r),
        // Data array
        .data_we_o        (data_we),
        .data_idx_o       (data_idx),
        .data_word_o      (data_word),
        .data_be_o        (data_be),
        .data_wdata_o     (data_wdata),
        .data_word0_i     (data_w0),
        .data_word1_i     (data_w1),
        .data_word2_i     (data_w2),
        .data_word3_i     (data_w3),
        // AXI write
        .m_axi_awvalid_o  (m_axi_awvalid_o),
        .m_axi_awready_i  (m_axi_awready_i),
        .m_axi_awaddr_o   (m_axi_awaddr_o),
        .m_axi_awlen_o    (m_axi_awlen_o),
        .m_axi_awsize_o   (m_axi_awsize_o),
        .m_axi_awburst_o  (m_axi_awburst_o),
        .m_axi_wvalid_o   (m_axi_wvalid_o),
        .m_axi_wready_i   (m_axi_wready_i),
        .m_axi_wdata_o    (m_axi_wdata_o),
        .m_axi_wstrb_o    (m_axi_wstrb_o),
        .m_axi_wlast_o    (m_axi_wlast_o),
        .m_axi_bvalid_i   (m_axi_bvalid_i),
        .m_axi_bready_o   (m_axi_bready_o),
        // AXI read
        .m_axi_arvalid_o  (m_axi_arvalid_o),
        .m_axi_arready_i  (m_axi_arready_i),
        .m_axi_araddr_o   (m_axi_araddr_o),
        .m_axi_arlen_o    (m_axi_arlen_o),
        .m_axi_arsize_o   (m_axi_arsize_o),
        .m_axi_arburst_o  (m_axi_arburst_o),
        .m_axi_rvalid_i   (m_axi_rvalid_i),
        .m_axi_rready_o   (m_axi_rready_o),
        .m_axi_rdata_i    (m_axi_rdata_i),
        .m_axi_rlast_i    (m_axi_rlast_i)
    );

    cache_tag_array u_tags (
        .clk      (clk),
        .rst      (rst),
        .we_i     (tag_we),
        .idx_i    (tag_idx),
        .tag_i    (tag_tag_w),
        .valid_i  (tag_valid_w),
        .dirty_i  (tag_dirty_w),
        .tag_o    (tag_tag_r),
        .valid_o  (tag_valid_r),
        .dirty_o  (tag_dirty_r)
    );

    cache_data_array u_data (
        .clk     (clk),
        .we_i    (data_we),
        .idx_i   (data_idx),
        .word_i  (data_word),
        .be_i    (data_be),
        .wdata_i (data_wdata),
        .word0_o (data_w0),
        .word1_o (data_w1),
        .word2_o (data_w2),
        .word3_o (data_w3)
    );

endmodule
