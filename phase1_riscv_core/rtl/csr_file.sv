`timescale 1ns/1ps

// Extended machine-mode CSR file for Phase 13.
// Adds: misa, mhartid (RO), mcycle, minstret, mscratch, mtval, mcounteren.
// Keeps existing: mstatus, mie, mtvec, mepc, mcause, mip (read-only mirror).
// Synchronous exception entry/return now handled here along with interrupts.
module csr_file (
    input  logic        clk,
    input  logic        rst,

    // CSR read/write from EX stage
    input  logic        csr_en_i,       // 1 = valid CSR instruction in EX
    input  logic [11:0] csr_addr_i,
    input  logic [1:0]  csr_op_i,       // 01=CSRRW, 10=CSRRS, 11=CSRRC
    input  logic [31:0] csr_wdata_i,    // write data (rs1 or zero-extended uimm)
    output logic [31:0] csr_rdata_o,    // read value (old CSR value)

    // Instruction-retire pulse (for minstret)
    input  logic        instr_commit_i,

    // Trap entry: called by riscv_core on any exception or interrupt
    input  logic        trap_enter_i,
    input  logic [31:0] trap_cause_i,   // mcause value  (MSB=1 → interrupt)
    input  logic [31:0] trap_epc_i,     // PC to save in mepc
    input  logic [31:0] trap_tval_i,    // bad addr/instr for mtval (0 if N/A)

    // MRET: restore MIE from MPIE
    input  logic        mret_i,

    // Interrupt inputs for mip construction
    input  logic        m_ext_irq_i,
    input  logic        m_timer_irq_i,
    input  logic        m_sw_irq_i,

    // CSR outputs read by the pipeline
    output logic [31:0] mstatus_o,
    output logic [31:0] mie_o,
    output logic [31:0] mtvec_o,
    output logic [31:0] mepc_o,
    output logic [31:0] mcause_o,
    output logic [31:0] mtval_o
);
    // -------------------------------------------------------------------------
    // CSR register declarations
    // -------------------------------------------------------------------------
    logic [31:0] mstatus_r;
    logic [31:0] mie_r;
    logic [31:0] mtvec_r;
    logic [31:0] mepc_r;
    logic [31:0] mcause_r;
    logic [31:0] mtval_r;
    logic [31:0] mscratch_r;
    logic [31:0] mcounteren_r;
    logic [63:0] mcycle_r;
    logic [63:0] minstret_r;

    // misa: RV32IMAC — MXL=01(RV32), bits A(0),C(2),I(8),M(12)
    localparam [31:0] MISA_VAL = 32'h4014_1101;
    // mhartid: hart 0
    localparam [31:0] MHARTID_VAL = 32'h0;

    // mip: constructed from live interrupt inputs (read-only)
    logic [31:0] mip_w;
    assign mip_w = {20'b0, m_ext_irq_i, 3'b0, m_timer_irq_i, 3'b0, m_sw_irq_i, 3'b0};

    // Pre-extract 64-bit counter sub-words (Icarus: no bit-selects inside always_comb)
    logic [31:0] mcycle_lo, mcycle_hi, minstret_lo, minstret_hi;
    assign mcycle_lo   = mcycle_r[31:0];
    assign mcycle_hi   = mcycle_r[63:32];
    assign minstret_lo = minstret_r[31:0];
    assign minstret_hi = minstret_r[63:32];

    // -------------------------------------------------------------------------
    // Utility: mstatus field extraction outside always blocks (Icarus compat)
    // -------------------------------------------------------------------------
    logic mstatus_mie, mstatus_mpie;
    assign mstatus_mie  = mstatus_r[3];
    assign mstatus_mpie = mstatus_r[7];

    // Full-word mstatus for trap entry and MRET
    logic [31:0] mstatus_trap_val, mstatus_mret_val;
    assign mstatus_trap_val = (mstatus_r & ~32'h88) | (mstatus_mie ? 32'h80 : 32'h0);
    assign mstatus_mret_val = (mstatus_r & ~32'h88) | 32'h80 | (mstatus_mpie ? 32'h8 : 32'h0);

    // -------------------------------------------------------------------------
    // Combinational CSR read
    // -------------------------------------------------------------------------
    always_comb begin
        case (csr_addr_i)
            12'h300: csr_rdata_o = mstatus_r;
            12'h301: csr_rdata_o = MISA_VAL;
            12'h304: csr_rdata_o = mie_r;
            12'h305: csr_rdata_o = mtvec_r;
            12'h306: csr_rdata_o = mcounteren_r;
            12'h340: csr_rdata_o = mscratch_r;
            12'h341: csr_rdata_o = mepc_r;
            12'h342: csr_rdata_o = mcause_r;
            12'h343: csr_rdata_o = mtval_r;
            12'h344: csr_rdata_o = mip_w;
            12'hB00: csr_rdata_o = mcycle_lo;
            12'hB80: csr_rdata_o = mcycle_hi;
            12'hB02: csr_rdata_o = minstret_lo;
            12'hB82: csr_rdata_o = minstret_hi;
            12'hF14: csr_rdata_o = MHARTID_VAL;
            default:  csr_rdata_o = 32'b0;
        endcase
    end

    // -------------------------------------------------------------------------
    // Compute write data based on CSR operation
    // -------------------------------------------------------------------------
    logic [31:0] csr_new;
    always_comb begin
        case (csr_op_i)
            2'b01: csr_new = csr_wdata_i;                     // CSRRW
            2'b10: csr_new = csr_rdata_o | csr_wdata_i;       // CSRRS
            2'b11: csr_new = csr_rdata_o & ~csr_wdata_i;      // CSRRC
            default: csr_new = csr_wdata_i;
        endcase
    end

    // -------------------------------------------------------------------------
    // Sequential: CSR register updates
    // Priority: trap_enter > mret > csr_en (normal instruction)
    // -------------------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            mstatus_r    <= 32'b0;
            mie_r        <= 32'b0;
            mtvec_r      <= 32'b0;
            mepc_r       <= 32'b0;
            mcause_r     <= 32'b0;
            mtval_r      <= 32'b0;
            mscratch_r   <= 32'b0;
            mcounteren_r <= 32'b0;
            mcycle_r     <= 64'b0;
            minstret_r   <= 64'b0;
        end else begin
            // Free-running counters
            mcycle_r   <= mcycle_r + 64'd1;
            if (instr_commit_i) minstret_r <= minstret_r + 64'd1;

            if (trap_enter_i) begin
                mepc_r    <= trap_epc_i;
                mcause_r  <= trap_cause_i;
                mtval_r   <= trap_tval_i;
                mstatus_r <= mstatus_trap_val;
            end else if (mret_i) begin
                mstatus_r <= mstatus_mret_val;
            end else if (csr_en_i) begin
                case (csr_addr_i)
                    12'h300: mstatus_r    <= csr_new;
                    12'h304: mie_r        <= csr_new;
                    12'h305: mtvec_r      <= csr_new;
                    12'h306: mcounteren_r <= csr_new;
                    12'h340: mscratch_r   <= csr_new;
                    12'h341: mepc_r       <= csr_new;
                    12'h342: mcause_r     <= csr_new;
                    12'h343: mtval_r      <= csr_new;
                    12'hB00: mcycle_r[31:0]   <= csr_new;
                    12'hB80: mcycle_r[63:32]  <= csr_new;
                    12'hB02: minstret_r[31:0]  <= csr_new;
                    12'hB82: minstret_r[63:32] <= csr_new;
                    default: ;
                endcase
            end
        end
    end

    // -------------------------------------------------------------------------
    // Output assignments
    // -------------------------------------------------------------------------
    assign mstatus_o = mstatus_r;
    assign mie_o     = mie_r;
    assign mtvec_o   = mtvec_r;
    assign mepc_o    = mepc_r;
    assign mcause_o  = mcause_r;
    assign mtval_o   = mtval_r;

endmodule
