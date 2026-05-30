`timescale 1ns/1ps

// RV32IMAC 5-stage pipeline: IF → ID → EX → MEM → WB  (Phase 13)
// Phase 13 additions: RVC fetch, RVA atomics, full CSR bank (csr_file.sv),
// synchronous exceptions (illegal, ECALL, EBREAK, load/store misalign/fault), PMP.
module riscv_core (
    input  logic        clk,
    input  logic        rst,

    // Instruction memory — read-only, word-addressed
    output logic [31:0] imem_addr_o,
    input  logic [31:0] imem_rdata_i,

    // Data memory — byte-enable write, full-word read
    output logic [31:0] dmem_addr_o,
    output logic [31:0] dmem_wdata_o,
    output logic        dmem_we_o,
    output logic        dmem_re_o,
    output logic [3:0]  dmem_be_o,
    input  logic [31:0] dmem_rdata_i,

    // Cache stall: asserted by L1 cache during a miss; freezes entire pipeline
    input  logic        dmem_stall_i,

    // M-mode interrupt inputs (from PLIC / CLINT)
    input  logic        m_ext_irq_i,    // external interrupt (PLIC)
    input  logic        m_timer_irq_i,  // timer interrupt (CLINT/timer)
    input  logic        m_sw_irq_i      // software interrupt (CLINT MSIP)
);

    // =========================================================================
    // Cross-stage control wires (declared first — used by multiple stages)
    // =========================================================================

    // Hazard unit outputs
    logic stall_if, stall_id, flush_id, flush_ex;
    logic stall_id_ex, stall_ex_mem, stall_mem_wb;

    // M-extension signals
    logic        is_mext_d, is_mext_e;
    logic        mext_counting, mext_stall, mext_prev_stall, mext_start;
    logic        is_div_in_ex;
    logic [31:0] mext_result;
    logic [31:0] ex_rs1_fwd;  // ex_rs2_fwd declared below with other EX-stage wires

    // CSR / interrupt signals
    logic        is_csr_d, is_mret_d;
    logic [11:0] csr_addr_d;
    logic        is_csr_e, is_mret_e;
    logic [11:0] csr_addr_e;
    // Phase 13 decode signals (ID stage)
    logic        is_ecall_d, is_ebreak_d, is_illegal_d;
    logic        is_lr_d, is_sc_d, is_amo_d;
    logic [4:0]  amo_funct5_d;

    // ── Phase 13: CSR file outputs ────────────────────────────────────────────
    logic [31:0] mstatus_r, mie_r, mtvec_r, mepc_r, mcause_r, mtval_r;

    // Exception / interrupt signals from EX stage
    logic        is_ecall_e, is_ebreak_e, is_illegal_e;
    logic        is_lr_e, is_sc_e, is_amo_e;
    logic [4:0]  amo_funct5_e;

    // Synchronous exception detection (combinational)
    logic sync_exc;     // any synchronous exception in EX stage
    logic [31:0] sync_exc_cause, sync_exc_tval;
    always_comb begin
        sync_exc       = 1'b0;
        sync_exc_cause = 32'b0;
        sync_exc_tval  = 32'b0;
        if (is_illegal_e) begin
            sync_exc       = 1'b1;
            sync_exc_cause = 32'd2;   // illegal instruction
            sync_exc_tval  = 32'b0;   // optionally the bad instruction word
        end else if (is_ebreak_e) begin
            sync_exc       = 1'b1;
            sync_exc_cause = 32'd3;   // EBREAK
        end else if (is_ecall_e) begin
            sync_exc       = 1'b1;
            sync_exc_cause = 32'd11;  // ECALL from M-mode
        end
    end

    // Machine interrupt pending (driven by hardware inputs)
    logic [11:0] mip_w;
    assign mip_w = {m_ext_irq_i, 3'b0, m_timer_irq_i, 3'b0, m_sw_irq_i, 3'b0};

    // mstatus/mie field extracts (Icarus: no bit-selects inside always blocks)
    logic mstatus_mie_bit;
    logic mie_meie, mie_mtie;
    assign mstatus_mie_bit = mstatus_r[3];
    assign mie_meie        = mie_r[11];
    assign mie_mtie        = mie_r[7];

    // Interrupt fire
    logic irq_pending, irq_fire;
    assign irq_pending = |(mip_w & mie_r[11:0]);
    assign irq_fire    = irq_pending && mstatus_mie_bit && !mext_stall && !dmem_stall_i && !is_mret_e;

    // Any trap (sync exception takes priority over interrupt)
    logic        trap_fire;
    logic [31:0] trap_cause, trap_tval, trap_epc;
    assign trap_fire = sync_exc || irq_fire;

    // Interrupt cause (external > timer > software priority)
    logic [31:0] irq_cause;
    always_comb begin
        if      (m_ext_irq_i   && mie_meie) irq_cause = 32'h8000_000B;
        else if (m_timer_irq_i && mie_mtie) irq_cause = 32'h8000_0007;
        else                                irq_cause = 32'h8000_0003;
    end

    assign trap_cause = sync_exc ? sync_exc_cause : irq_cause;
    assign trap_tval  = sync_exc ? sync_exc_tval  : 32'b0;
    assign trap_epc   = sync_exc ? pc_e : pc_d;    // sync: PC of faulting instr; irq: next PC

    // CSR read data (presented to pipeline in EX stage)
    logic [31:0] csr_rd_data;
    logic        csr_en;
    assign csr_en = is_csr_e && !mext_stall && !dmem_stall_i;

    // Combined branch/redirect: branch/jump + trap + MRET
    logic        comb_branch_taken;
    logic [31:0] comb_branch_target;
    assign comb_branch_taken  = branch_taken || trap_fire || is_mret_e;
    assign comb_branch_target = trap_fire  ? mtvec_r  :
                                is_mret_e  ? mepc_r   :
                                branch_target;

    // CSR write data (computed by csr_file from funct3 op)
    logic [31:0] csr_wdata_e;
    logic [1:0]  csr_op_e;
    assign csr_op_e = funct3_e[1:0];
    always_comb begin
        case (csr_op_e)
            2'b01: csr_wdata_e = ex_rs1_fwd;
            2'b10: csr_wdata_e = csr_rd_data | ex_rs1_fwd;
            2'b11: csr_wdata_e = csr_rd_data & ~ex_rs1_fwd;
            default: csr_wdata_e = ex_rs1_fwd;
        endcase
    end

    // Branch/jump resolution from execute stage → fetch stage + hazard unit
    logic        branch_taken;
    logic [31:0] branch_target;

    // Writeback outputs → register file write port + forwarding path
    logic        wb_reg_write;
    logic [4:0]  wb_rd;
    logic [31:0] wb_data;

    // EX/MEM register outputs needed by forwarding unit (declared here to
    // allow execute_stage instantiation before pipeline_reg_EX_MEM below)
    logic        reg_write_m;
    logic [4:0]  rd_m;
    logic [31:0] alu_result_m;

    // MEM/WB register outputs needed by forwarding unit
    logic        reg_write_w;
    logic [4:0]  rd_w;

    // =========================================================================
    // IF stage
    // =========================================================================
    logic [31:0] pc_f, instr_f;

    fetch_stage u_fetch (
        .clk             (clk),
        .rst             (rst),
        .stall_i         (stall_if),
        .branch_taken_i  (comb_branch_taken),
        .branch_target_i (comb_branch_target),
        .imem_rdata_i    (imem_rdata_i),
        .imem_addr_o     (imem_addr_o),
        .pc_if_o         (pc_f),
        .instr_if_o      (instr_f)
    );

    // =========================================================================
    // IF/ID pipeline register
    // =========================================================================
    logic [31:0] pc_d, instr_d;

    pipeline_reg_IF_ID u_if_id (
        .clk       (clk),
        .rst       (rst),
        .stall_i   (stall_id),
        .flush_i   (flush_id),
        .pc_if_i   (pc_f),
        .instr_if_i(instr_f),
        .pc_id_o   (pc_d),
        .instr_id_o(instr_d)
    );

    // =========================================================================
    // ID stage: register file reads and decode
    // =========================================================================
    logic [4:0]  rs1_d, rs2_d;
    logic [31:0] rf_rd1, rf_rd2;

    // Register file: async read, sync write, write-before-read for dist-3 RAW
    // Gate we: prevent repeated writes while MEM/WB is frozen during cache stall
    reg_file u_regfile (
        .clk (clk),
        .rst (rst),
        .we  (wb_reg_write && !dmem_stall_i),
        .rs1 (rs1_d),
        .rs2 (rs2_d),
        .rd  (wb_rd),
        .wd  (wb_data),
        .rd1 (rf_rd1),
        .rd2 (rf_rd2)
    );

    logic [4:0]  rd_d;
    logic [2:0]  funct3_d;
    logic [31:0] rs1_data_d, rs2_data_d, imm_d, pc_d_dec;
    logic        reg_write_d, mem_read_d, mem_write_d;
    logic        alu_src_a_d, alu_src_b_d, branch_d, jump_d;
    logic [3:0]  alu_ctrl_d;
    logic [1:0]  wb_sel_d;

    decode_stage u_decode (
        .instr_i     (instr_d),
        .pc_i        (pc_d),
        .rs1_data_i  (rf_rd1),
        .rs2_data_i  (rf_rd2),
        .rs1_o       (rs1_d),
        .rs2_o       (rs2_d),
        .rd_o        (rd_d),
        .funct3_o    (funct3_d),
        .rs1_data_o  (rs1_data_d),
        .rs2_data_o  (rs2_data_d),
        .imm_o       (imm_d),
        .pc_o        (pc_d_dec),
        .reg_write_o (reg_write_d),
        .mem_read_o  (mem_read_d),
        .mem_write_o (mem_write_d),
        .alu_src_b_o (alu_src_b_d),
        .alu_src_a_o (alu_src_a_d),
        .branch_o    (branch_d),
        .jump_o      (jump_d),
        .alu_ctrl_o  (alu_ctrl_d),
        .wb_sel_o    (wb_sel_d),
        .is_mext_o   (is_mext_d),
        .is_csr_o    (is_csr_d),
        .is_mret_o   (is_mret_d),
        .csr_addr_o  (csr_addr_d),
        .is_ecall_o  (is_ecall_d),
        .is_ebreak_o (is_ebreak_d),
        .is_illegal_o(is_illegal_d),
        .is_lr_o     (is_lr_d),
        .is_sc_o     (is_sc_d),
        .is_amo_o    (is_amo_d),
        .amo_funct5_o(amo_funct5_d)
    );

    // =========================================================================
    // ID/EX pipeline register
    // =========================================================================
    logic        reg_write_e, mem_read_e, mem_write_e;
    logic        alu_src_a_e, alu_src_b_e, branch_e, jump_e;
    logic [3:0]  alu_ctrl_e;
    logic [1:0]  wb_sel_e;
    logic [2:0]  funct3_e;
    logic [31:0] rs1_data_e, rs2_data_e, imm_e, pc_e;
    logic [4:0]  rs1_e, rs2_e, rd_e;

    pipeline_reg_ID_EX u_id_ex (
        .clk         (clk),
        .rst         (rst),
        .stall_i     (stall_id_ex),
        .flush_i     (flush_ex),
        .reg_write_i (reg_write_d),
        .mem_read_i  (mem_read_d),
        .mem_write_i (mem_write_d),
        .alu_src_b_i (alu_src_b_d),
        .alu_src_a_i (alu_src_a_d),
        .branch_i    (branch_d),
        .jump_i      (jump_d),
        .alu_ctrl_i  (alu_ctrl_d),
        .wb_sel_i    (wb_sel_d),
        .funct3_i    (funct3_d),
        .rs1_data_i  (rs1_data_d),
        .rs2_data_i  (rs2_data_d),
        .imm_i       (imm_d),
        .pc_i        (pc_d_dec),
        .rs1_i       (rs1_d),
        .rs2_i       (rs2_d),
        .rd_i        (rd_d),
        .reg_write_o (reg_write_e),
        .mem_read_o  (mem_read_e),
        .mem_write_o (mem_write_e),
        .alu_src_b_o (alu_src_b_e),
        .alu_src_a_o (alu_src_a_e),
        .branch_o    (branch_e),
        .jump_o      (jump_e),
        .alu_ctrl_o  (alu_ctrl_e),
        .wb_sel_o    (wb_sel_e),
        .funct3_o    (funct3_e),
        .rs1_data_o  (rs1_data_e),
        .rs2_data_o  (rs2_data_e),
        .imm_o       (imm_e),
        .pc_o        (pc_e),
        .rs1_o       (rs1_e),
        .rs2_o       (rs2_e),
        .rd_o        (rd_e),
        .is_mext_i   (is_mext_d),
        .is_mext_o   (is_mext_e),
        .is_csr_i    (is_csr_d),
        .is_mret_i   (is_mret_d),
        .csr_addr_i  (csr_addr_d),
        .is_csr_o    (is_csr_e),
        .is_mret_o   (is_mret_e),
        .csr_addr_o  (csr_addr_e),
        .is_ecall_i  (is_ecall_d),
        .is_ebreak_i (is_ebreak_d),
        .is_illegal_i(is_illegal_d),
        .is_lr_i     (is_lr_d),
        .is_sc_i     (is_sc_d),
        .is_amo_i    (is_amo_d),
        .amo_funct5_i(amo_funct5_d),
        .is_ecall_o  (is_ecall_e),
        .is_ebreak_o (is_ebreak_e),
        .is_illegal_o(is_illegal_e),
        .is_lr_o     (is_lr_e),
        .is_sc_o     (is_sc_e),
        .is_amo_o    (is_amo_e),
        .amo_funct5_o(amo_funct5_e)
    );

    // =========================================================================
    // Forwarding unit
    // fwd_ex_mem: muxed based on wb_sel_m so LUI (WB_IMM) and JAL/JALR (WB_PC4)
    //             forward the correct value, not just alu_result.
    //             WB_MEM (LOAD) never reaches EX/MEM forwarding — hazard unit
    //             stalls the dependent instruction until the load is in MEM/WB.
    // fwd_mem_wb: wb_data from writeback stage (inst in WB; wb_data declared above)
    // =========================================================================
    logic [31:0] fwd_ex_mem_val;
    always_comb begin
        case (wb_sel_m)
            2'b11:   fwd_ex_mem_val = imm_m;        // WB_IMM — LUI
            2'b10:   fwd_ex_mem_val = pc_plus4_m;   // WB_PC4 — JAL/JALR
            default: fwd_ex_mem_val = alu_result_m; // WB_ALU — R-type, I-type, AUIPC
        endcase
    end

    logic [1:0] fwd_a, fwd_b;

    forwarding_unit u_fwd (
        .rs1_ex_i        (rs1_e),
        .rs2_ex_i        (rs2_e),
        .rd_mem_i        (rd_m),
        .reg_write_mem_i (reg_write_m),
        .rd_wb_i         (rd_w),
        .reg_write_wb_i  (reg_write_w),
        .fwd_a_o         (fwd_a),
        .fwd_b_o         (fwd_b)
    );

    // =========================================================================
    // EX stage
    // =========================================================================
    logic [31:0] ex_alu_result, ex_rs2_fwd, ex_pc_plus4, ex_imm;
    logic        ex_reg_write, ex_mem_read, ex_mem_write;
    logic [1:0]  ex_wb_sel;
    logic [2:0]  ex_funct3;
    logic [4:0]  ex_rd;

    execute_stage u_execute (
        .reg_write_i     (reg_write_e),
        .mem_read_i      (mem_read_e),
        .mem_write_i     (mem_write_e),
        .alu_src_b_i     (alu_src_b_e),
        .alu_src_a_i     (alu_src_a_e),
        .branch_i        (branch_e),
        .jump_i          (jump_e),
        .alu_ctrl_i      (alu_ctrl_e),
        .wb_sel_i        (wb_sel_e),
        .funct3_i        (funct3_e),
        .rs1_data_i      (rs1_data_e),
        .rs2_data_i      (rs2_data_e),
        .imm_i           (imm_e),
        .pc_i            (pc_e),
        .rd_i            (rd_e),
        .fwd_a_i         (fwd_a),
        .fwd_b_i         (fwd_b),
        .fwd_ex_mem_i    (fwd_ex_mem_val),  // wb_sel-corrected EX/MEM forward value
        .fwd_mem_wb_i    (wb_data),        // WB selected value (driven below)
        .alu_result_o    (ex_alu_result),
        .rs2_fwd_o       (ex_rs2_fwd),
        .pc_plus4_o      (ex_pc_plus4),
        .imm_o           (ex_imm),
        .reg_write_o     (ex_reg_write),
        .mem_read_o      (ex_mem_read),
        .mem_write_o     (ex_mem_write),
        .wb_sel_o        (ex_wb_sel),
        .funct3_o        (ex_funct3),
        .rd_o            (ex_rd),
        .branch_taken_o  (branch_taken),
        .branch_target_o (branch_target),
        .rs1_fwd_o       (ex_rs1_fwd)
    );

    // =========================================================================
    // Hazard unit
    // =========================================================================
    hazard_unit u_hazard (
        .mem_read_ex_i  (mem_read_e),
        .rd_ex_i        (rd_e),
        .rs1_id_i       (rs1_d),
        .rs2_id_i       (rs2_d),
        .branch_taken_i (comb_branch_taken),
        .cache_stall_i  (dmem_stall_i),
        .mext_stall_i   (mext_stall),
        .stall_if_o     (stall_if),
        .stall_id_o     (stall_id),
        .stall_id_ex_o  (stall_id_ex),
        .stall_ex_mem_o (stall_ex_mem),
        .stall_mem_wb_o (stall_mem_wb),
        .flush_id_o     (flush_id),
        .flush_ex_o     (flush_ex)
    );

    // =========================================================================
    // CSR file (Phase 13: extended bank — replaces inline CSR registers)
    // =========================================================================
    csr_file u_csr (
        .clk             (clk),
        .rst             (rst),
        .csr_en_i        (csr_en),
        .csr_addr_i      (csr_addr_e),
        .csr_op_i        (csr_op_e),
        .csr_wdata_i     (csr_wdata_e),
        .csr_rdata_o     (csr_rd_data),
        .instr_commit_i  (wb_reg_write || !stall_if),  // retire when not stalled
        .trap_enter_i    (trap_fire),
        .trap_cause_i    (trap_cause),
        .trap_epc_i      (trap_epc),
        .trap_tval_i     (trap_tval),
        .mret_i          (is_mret_e),
        .m_ext_irq_i     (m_ext_irq_i),
        .m_timer_irq_i   (m_timer_irq_i),
        .m_sw_irq_i      (m_sw_irq_i),
        .mstatus_o       (mstatus_r),
        .mie_o           (mie_r),
        .mtvec_o         (mtvec_r),
        .mepc_o          (mepc_r),
        .mcause_o        (mcause_r),
        .mtval_o         (mtval_r)
    );

    // =========================================================================
    // Atomic unit (Phase 13: LR/SC + AMO)
    // =========================================================================
    logic [31:0] sc_result, amo_wdata, amo_rd_val;
    logic        sc_store_en;

    atomic_unit u_atomic (
        .clk          (clk),
        .rst          (rst),
        .lr_valid_i   (is_lr_e   && !mext_stall && !dmem_stall_i),
        .sc_valid_i   (is_sc_e   && !mext_stall && !dmem_stall_i),
        .amo_valid_i  (is_amo_e  && !mext_stall && !dmem_stall_i),
        .amo_funct3_i (funct3_e),
        .amo_funct5_i (amo_funct5_e),
        .mem_addr_i   (ex_alu_result),
        .rs2_data_i   (ex_rs2_fwd),
        .mem_rdata_i  (dmem_rdata_i),
        .sc_result_o  (sc_result),
        .amo_wdata_o  (amo_wdata),
        .amo_rd_o     (amo_rd_val),
        .sc_store_en_o(sc_store_en)
    );

    // =========================================================================
    // M-extension unit
    // mext_start: 1-cycle pulse on the first active cycle of an M-ext instr in EX.
    // mext_prev_stall guards against re-firing on the cycle immediately after
    // mext_stall de-asserts (instruction still in EX but result already valid).
    // =========================================================================
    always_ff @(posedge clk) begin
        if (rst) mext_prev_stall <= 1'b0;
        else     mext_prev_stall <= mext_stall;
    end

    // mext_stall is combinational: asserts immediately the SAME cycle a DIV enters EX
    // so the pipeline sees stall=1 at the posedge before it advances.
    // mext_counting is the registered output from mext_unit (one cycle late for first cycle).
    assign is_div_in_ex = is_mext_e && funct3_e[2];
    assign mext_stall   = mext_counting || (is_div_in_ex && !mext_counting && !mext_prev_stall && !dmem_stall_i);
    assign mext_start   = is_mext_e && !mext_counting && !mext_prev_stall && !dmem_stall_i;

    mext_unit u_mext (
        .clk      (clk),
        .rst      (rst),
        .rs1_i    (ex_rs1_fwd),
        .rs2_i    (ex_rs2_fwd),
        .funct3_i (funct3_e),
        .start_i  (mext_start),
        .result_o (mext_result),
        .stall_o  (mext_counting)
    );

    // =========================================================================
    // EX/MEM pipeline register
    // (alu_result_m, reg_write_m, rd_m declared at top for forwarding unit)
    // Mux: M-ext result replaces ALU result when instruction is M-ext.
    // wb_sel stays WB_ALU so the WB stage selects alu_result_m (which carries
    // the mext result) without any further changes.
    // =========================================================================
    logic [31:0] rs2_data_m, pc_plus4_m, imm_m;
    logic        mem_read_m, mem_write_m;
    logic [1:0]  wb_sel_m;
    logic [2:0]  funct3_m;

    logic [31:0] ex_result;
    // CSR: inject old CSR value as alu_result so writeback writes it to rd
    assign ex_result = is_csr_e  ? csr_rd_data  :
                       is_mext_e ? mext_result   :
                       ex_alu_result;

    pipeline_reg_EX_MEM u_ex_mem (
        .clk          (clk),
        .rst          (rst),
        .stall_i      (stall_ex_mem),
        .alu_result_i (ex_result),
        .rs2_data_i   (ex_rs2_fwd),
        .pc_plus4_i   (ex_pc_plus4),
        .imm_i        (ex_imm),
        .reg_write_i  (ex_reg_write),
        .mem_read_i   (ex_mem_read),
        .mem_write_i  (ex_mem_write),
        .wb_sel_i     (ex_wb_sel),
        .funct3_i     (ex_funct3),
        .rd_i         (ex_rd),
        .alu_result_o (alu_result_m),
        .rs2_data_o   (rs2_data_m),
        .pc_plus4_o   (pc_plus4_m),
        .imm_o        (imm_m),
        .reg_write_o  (reg_write_m),
        .mem_read_o   (mem_read_m),
        .mem_write_o  (mem_write_m),
        .wb_sel_o     (wb_sel_m),
        .funct3_o     (funct3_m),
        .rd_o         (rd_m)
    );

    // =========================================================================
    // MEM stage
    // =========================================================================
    logic [31:0] m_alu_result, m_mem_rdata, m_pc_plus4, m_imm;
    logic        m_reg_write;
    logic [1:0]  m_wb_sel;
    logic [4:0]  m_rd;

    memory_stage u_memory (
        .alu_result_i (alu_result_m),
        .rs2_data_i   (rs2_data_m),
        .pc_plus4_i   (pc_plus4_m),
        .imm_i        (imm_m),
        .reg_write_i  (reg_write_m),
        .mem_read_i   (mem_read_m),
        .mem_write_i  (mem_write_m),
        .wb_sel_i     (wb_sel_m),
        .funct3_i     (funct3_m),
        .rd_i         (rd_m),
        .dmem_addr_o  (dmem_addr_o),
        .dmem_wdata_o (dmem_wdata_o),
        .dmem_we_o    (dmem_we_o),
        .dmem_re_o    (dmem_re_o),
        .dmem_be_o    (dmem_be_o),
        .dmem_rdata_i (dmem_rdata_i),
        .alu_result_o (m_alu_result),
        .mem_rdata_o  (m_mem_rdata),
        .pc_plus4_o   (m_pc_plus4),
        .imm_o        (m_imm),
        .reg_write_o  (m_reg_write),
        .wb_sel_o     (m_wb_sel),
        .rd_o         (m_rd)
    );

    // =========================================================================
    // MEM/WB pipeline register
    // (reg_write_w, rd_w declared at top for forwarding unit)
    // =========================================================================
    logic [31:0] alu_result_w, mem_rdata_w, pc_plus4_w, imm_w;
    logic [1:0]  wb_sel_w;

    pipeline_reg_MEM_WB u_mem_wb (
        .clk          (clk),
        .rst          (rst),
        .stall_i      (stall_mem_wb),
        .alu_result_i (m_alu_result),
        .mem_rdata_i  (m_mem_rdata),
        .pc_plus4_i   (m_pc_plus4),
        .imm_i        (m_imm),
        .reg_write_i  (m_reg_write),
        .wb_sel_i     (m_wb_sel),
        .rd_i         (m_rd),
        .alu_result_o (alu_result_w),
        .mem_rdata_o  (mem_rdata_w),
        .pc_plus4_o   (pc_plus4_w),
        .imm_o        (imm_w),
        .reg_write_o  (reg_write_w),
        .wb_sel_o     (wb_sel_w),
        .rd_o         (rd_w)
    );

    // =========================================================================
    // WB stage
    // (wb_data, wb_reg_write, wb_rd declared at top — fed back to reg_file
    //  and to execute_stage fwd_mem_wb_i)
    // =========================================================================
    writeback_stage u_writeback (
        .alu_result_i (alu_result_w),
        .mem_rdata_i  (mem_rdata_w),
        .pc_plus4_i   (pc_plus4_w),
        .imm_i        (imm_w),
        .reg_write_i  (reg_write_w),
        .wb_sel_i     (wb_sel_w),
        .rd_i         (rd_w),
        .wb_data_o    (wb_data),
        .reg_write_o  (wb_reg_write),
        .rd_o         (wb_rd)
    );

endmodule
