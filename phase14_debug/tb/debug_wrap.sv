`timescale 1ns/1ps

// Phase 14 Debug Wrapper
// Connects riscv_core + dm_top + trigger_module for cocotb testing.
module debug_wrap (
    input  logic        clk,
    input  logic        rst,

    // IMEM (cocotb drives rdata based on addr)
    output logic [31:0] imem_addr,
    input  logic [31:0] imem_rdata,

    // DMEM (simple passthrough)
    output logic [31:0] dmem_addr,
    output logic [31:0] dmem_wdata,
    output logic        dmem_we,
    output logic        dmem_re,
    output logic [3:0]  dmem_be,
    input  logic [31:0] dmem_rdata,
    input  logic        dmem_stall,

    // DM AXI4-Lite (cocotb writes/reads the DM)
    input  logic [31:0] dm_awaddr,
    input  logic [31:0] dm_araddr,
    input  logic        dm_awvalid,
    input  logic        dm_wvalid,
    input  logic        dm_arvalid,
    input  logic [31:0] dm_wdata,
    input  logic [3:0]  dm_wstrb,
    output logic        dm_awready,
    output logic        dm_wready,
    output logic        dm_arready,
    output logic [1:0]  dm_bresp,
    output logic [1:0]  dm_rresp,
    output logic        dm_bvalid,
    output logic        dm_rvalid,
    input  logic        dm_bready,
    input  logic        dm_rready,
    output logic [31:0] dm_rdata,

    // Observable debug signals
    output logic [31:0] dbg_pc,
    output logic        dbg_halted
);

    // -------------------------------------------------------------------------
    // Wires between riscv_core and dm_top
    // -------------------------------------------------------------------------
    logic        dbg_halt_req;
    logic        dbg_halted_w;
    logic        dbg_resume_req;
    logic [31:0] dbg_pc_w;
    logic [4:0]  dbg_rf_addr;
    logic [31:0] dbg_rf_rdata;
    logic [31:0] dbg_rf_wdata;
    logic        dbg_rf_we;
    logic        dbg_imem_ovr_en;
    logic [31:0] dbg_imem_ovr_data;
    logic        dbg_jump_en;
    logic [31:0] dbg_jump_target;
    logic [31:0] imem_addr_w;

    // Trigger-related wires
    logic        trigger_fire_w;
    logic        tselect_we_w, tdata1_we_w, tdata2_we_w;
    logic [31:0] tselect_wd_w, tdata1_wd_w, tdata2_wd_w;
    logic [31:0] tselect_rd_w, tdata1_rd_w, tdata2_rd_w;
    logic [31:0] dbg_mem_addr_w;
    logic        dbg_mem_we_w;
    logic        dbg_mem_re_w;

    // Expose observable signals
    assign dbg_pc     = dbg_pc_w;
    assign dbg_halted = dbg_halted_w;
    assign imem_addr  = imem_addr_w;

    // -------------------------------------------------------------------------
    // riscv_core instantiation
    // -------------------------------------------------------------------------
    riscv_core u_core (
        .clk                (clk),
        .rst                (rst),
        .imem_addr_o        (imem_addr_w),
        .imem_rdata_i       (imem_rdata),
        .dmem_addr_o        (dmem_addr),
        .dmem_wdata_o       (dmem_wdata),
        .dmem_we_o          (dmem_we),
        .dmem_re_o          (dmem_re),
        .dmem_be_o          (dmem_be),
        .dmem_rdata_i       (dmem_rdata),
        .dmem_stall_i       (dmem_stall),
        .m_ext_irq_i        (1'b0),
        .m_timer_irq_i      (1'b0),
        .m_sw_irq_i         (1'b0),
        // Debug interface
        .dbg_halt_req_i     (dbg_halt_req),
        .dbg_halted_o       (dbg_halted_w),
        .dbg_resume_req_i   (dbg_resume_req),
        .dbg_pc_o           (dbg_pc_w),
        .dbg_rf_addr_i      (dbg_rf_addr),
        .dbg_rf_rdata_o     (dbg_rf_rdata),
        .dbg_rf_wdata_i     (dbg_rf_wdata),
        .dbg_rf_we_i        (dbg_rf_we),
        .dbg_imem_ovr_en_i  (dbg_imem_ovr_en),
        .dbg_imem_ovr_data_i(dbg_imem_ovr_data),
        .dbg_jump_en_i      (dbg_jump_en),
        .dbg_jump_target_i  (dbg_jump_target),
        .trigger_halt_i     (trigger_fire_w),
        // Trigger CSR passthrough
        .tselect_we_o       (tselect_we_w),
        .tselect_wd_o       (tselect_wd_w),
        .tdata1_we_o        (tdata1_we_w),
        .tdata1_wd_o        (tdata1_wd_w),
        .tdata2_we_o        (tdata2_we_w),
        .tdata2_wd_o        (tdata2_wd_w),
        .tselect_rd_i       (tselect_rd_w),
        .tdata1_rd_i        (tdata1_rd_w),
        .tdata2_rd_i        (tdata2_rd_w),
        .dbg_mem_addr_o     (dbg_mem_addr_w),
        .dbg_mem_we_o       (dbg_mem_we_w),
        .dbg_mem_re_o       (dbg_mem_re_w)
    );

    // -------------------------------------------------------------------------
    // dm_top instantiation
    // -------------------------------------------------------------------------
    dm_top u_dm (
        .clk                  (clk),
        .rst_n                (~rst),
        // AXI4-Lite
        .s_awaddr             (dm_awaddr),
        .s_awvalid            (dm_awvalid),
        .s_awready            (dm_awready),
        .s_wdata              (dm_wdata),
        .s_wstrb              (dm_wstrb),
        .s_wvalid             (dm_wvalid),
        .s_wready             (dm_wready),
        .s_bresp              (dm_bresp),
        .s_bvalid             (dm_bvalid),
        .s_bready             (dm_bready),
        .s_araddr             (dm_araddr),
        .s_arvalid            (dm_arvalid),
        .s_arready            (dm_arready),
        .s_rdata              (dm_rdata),
        .s_rresp              (dm_rresp),
        .s_rvalid             (dm_rvalid),
        .s_rready             (dm_rready),
        // Hart debug interface
        .dbg_halt_req_o       (dbg_halt_req),
        .dbg_halted_i         (dbg_halted_w),
        .dbg_resume_req_o     (dbg_resume_req),
        .dbg_rf_addr_o        (dbg_rf_addr),
        .dbg_rf_rdata_i       (dbg_rf_rdata),
        .dbg_rf_wdata_o       (dbg_rf_wdata),
        .dbg_rf_we_o          (dbg_rf_we),
        .dbg_imem_ovr_en_o    (dbg_imem_ovr_en),
        .dbg_imem_ovr_data_o  (dbg_imem_ovr_data),
        .dbg_jump_en_o        (dbg_jump_en),
        .dbg_jump_target_o    (dbg_jump_target),
        .dbg_imem_addr_i      (imem_addr_w)
    );

    // -------------------------------------------------------------------------
    // trigger_module instantiation
    // -------------------------------------------------------------------------
    trigger_module u_trigger (
        .clk            (clk),
        .rst            (rst),
        .tselect_we_i   (tselect_we_w),
        .tselect_wd_i   (tselect_wd_w),
        .tdata1_we_i    (tdata1_we_w),
        .tdata1_wd_i    (tdata1_wd_w),
        .tdata2_we_i    (tdata2_we_w),
        .tdata2_wd_i    (tdata2_wd_w),
        .tselect_rd_o   (tselect_rd_w),
        .tdata1_rd_o    (tdata1_rd_w),
        .tdata2_rd_o    (tdata2_rd_w),
        .pc_ex_i        (dbg_pc_w),
        .mem_addr_i     (dbg_mem_addr_w),
        .store_en_i     (dbg_mem_we_w),
        .load_en_i      (dbg_mem_re_w),
        .trigger_fire_o (trigger_fire_w)
    );

endmodule
