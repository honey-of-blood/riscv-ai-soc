`timescale 1ns/1ps

// Phase 15: Integration wrapper — riscv_core + icache for performance testing.
// The branch predictor is already instantiated inside riscv_core.
// cocotb drives the AXI I-cache slave (ic_*) and the D-memory interface.
module perf_wrap (
    input  logic        clk,
    input  logic        rst_n,

    // I-cache backing memory AXI4-Lite slave (cocotb serves instruction data)
    input  logic [31:0] ic_rdata,
    input  logic        ic_rvalid,
    output logic        ic_rready,
    output logic [31:0] ic_araddr,
    output logic        ic_arvalid,
    input  logic        ic_arready,

    // Data memory (cocotb drives this)
    input  logic [31:0] dmem_rdata,
    input  logic        dmem_stall,
    output logic [31:0] dmem_addr,
    output logic [31:0] dmem_wdata,
    output logic        dmem_we,
    output logic        dmem_re,
    output logic  [3:0] dmem_be,

    // Observability
    output logic [31:0] pc_obs,     // current IF-stage address (imem_addr)
    output logic        halted_obs  // debug_halted_o
);

    // -------------------------------------------------------------------------
    // Internal wires
    // -------------------------------------------------------------------------
    logic [31:0] imem_addr;
    logic [31:0] imem_rdata;
    logic        icache_stall;

    // -------------------------------------------------------------------------
    // I-cache
    // -------------------------------------------------------------------------
    icache u_icache (
        .clk        (clk),
        .rst_n      (rst_n),
        .flush_i    (1'b0),         // no FENCE.I in test programs
        .cpu_addr_i (imem_addr),
        .cpu_rdata_o(imem_rdata),
        .cpu_stall_o(icache_stall),
        .m_araddr   (ic_araddr),
        .m_arvalid  (ic_arvalid),
        .m_arready  (ic_arready),
        .m_rdata    (ic_rdata),
        .m_rvalid   (ic_rvalid),
        .m_rready   (ic_rready)
    );

    // -------------------------------------------------------------------------
    // RISC-V core (with integrated branch predictor from Phase 15)
    // -------------------------------------------------------------------------
    riscv_core u_core (
        .clk                 (clk),
        .rst                 (~rst_n),
        .imem_addr_o         (imem_addr),
        .imem_rdata_i        (imem_rdata),
        .dmem_addr_o         (dmem_addr),
        .dmem_wdata_o        (dmem_wdata),
        .dmem_we_o           (dmem_we),
        .dmem_re_o           (dmem_re),
        .dmem_be_o           (dmem_be),
        .dmem_rdata_i        (dmem_rdata),
        .dmem_stall_i        (dmem_stall),
        .icache_stall_i      (icache_stall),
        .m_ext_irq_i         (1'b0),
        .m_timer_irq_i       (1'b0),
        .m_sw_irq_i          (1'b0),
        // Debug: all tied off
        .dbg_halt_req_i      (1'b0),
        .dbg_halted_o        (halted_obs),
        .dbg_resume_req_i    (1'b0),
        .dbg_pc_o            (),
        .dbg_rf_addr_i       (5'b0),
        .dbg_rf_rdata_o      (),
        .dbg_rf_wdata_i      (32'b0),
        .dbg_rf_we_i         (1'b0),
        .dbg_imem_ovr_en_i   (1'b0),
        .dbg_imem_ovr_data_i (32'b0),
        .dbg_jump_en_i       (1'b0),
        .dbg_jump_target_i   (32'b0),
        .trigger_halt_i      (1'b0),
        .tselect_we_o        (),
        .tselect_wd_o        (),
        .tdata1_we_o         (),
        .tdata1_wd_o         (),
        .tdata2_we_o         (),
        .tdata2_wd_o         (),
        .tselect_rd_i        (32'b0),
        .tdata1_rd_i         (32'b0),
        .tdata2_rd_i         (32'b0),
        .dbg_mem_addr_o      (),
        .dbg_mem_we_o        (),
        .dbg_mem_re_o        ()
    );

    assign pc_obs = imem_addr;

endmodule
