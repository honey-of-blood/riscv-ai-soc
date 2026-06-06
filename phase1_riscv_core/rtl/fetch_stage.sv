`timescale 1ns/1ps

// IF stage: PC register + branch mux + RVC expander + halfword buffer.
// Supports 16-bit compressed instructions (RVC): when two 16-bit instructions
// are packed in a 32-bit word, the upper halfword is buffered for next cycle.
// Instruction memory uses 4-byte aligned word addresses; PC[1] selects the half.
module fetch_stage (
    input  logic        clk,
    input  logic        rst,

    // Hazard unit — freeze PC when a stall is needed
    input  logic        stall_i,

    // EX stage branch/jump redirect
    input  logic        branch_taken_i,
    input  logic [31:0] branch_target_i,

    // Branch predictor interface (Phase 15)
    input  logic        predict_taken_i,   // from branch_predictor
    input  logic [31:0] predict_target_i,
    output logic        pred_taken_o,      // to IF/ID register

    // Instruction memory interface (async/combinational read, word-aligned)
    output logic [31:0] imem_addr_o,
    input  logic [31:0] imem_rdata_i,

    // To IF/ID pipeline register
    output logic [31:0] pc_if_o,
    output logic [31:0] instr_if_o
);
    logic [31:0] pc, pc_next;

    // Halfword buffer: holds the upper 16 bits of a word when the lower 16 were RVC.
    logic [15:0] buf_half;
    logic        buf_valid;

    // Select 16-bit halfword: from buffer (buf_valid=1) or memory (based on PC[1])
    logic [15:0] raw16;
    assign raw16 = buf_valid ? buf_half :
                   (pc[1]   ? imem_rdata_i[31:16] : imem_rdata_i[15:0]);

    // RVC expander instantiation
    logic [31:0] rvc_expanded;
    logic        is_rvc;

    rvc_expander u_rvc (
        .rvc_i   (raw16),
        .rvi_o   (rvc_expanded),
        .valid_o (is_rvc)       // 1 when raw16[1:0] != 11 AND encoding is valid
    );

    // is_compressed: raw16[1:0] != 11 (whether it expands validly or not)
    logic is_compressed;
    assign is_compressed = (raw16[1:0] != 2'b11);

    // Full 32-bit instruction from memory (when not using buffer and PC[1]=0)
    // If PC[1]=1 and not compressed, we have a misaligned 32-bit instruction:
    // the lower half is raw16, upper half from next fetch — not supported here,
    // emit NOP and advance PC to handle gracefully.
    logic [31:0] instr_full;
    assign instr_full = (pc[1] && !is_compressed) ? 32'h0000_0013  // ADDI x0,x0,0 (NOP)
                                                   : imem_rdata_i;

    // Instruction presented to the pipeline
    assign instr_if_o = is_compressed ? rvc_expanded : instr_full;

    // PC increment
    logic [31:0] pc_inc;
    assign pc_inc = is_compressed ? 32'd2 : 32'd4;

    // pred_taken_o: prediction fired this cycle, unless EX is simultaneously
    // redirecting (in which case the prediction is moot).
    // z-safe: treat 'z' on predict_taken_i as 0.
    assign pred_taken_o = (predict_taken_i === 1'b1) && !branch_taken_i;

    // PC mux (priority: EX branch > BP prediction > sequential)
    always_comb begin
        if (branch_taken_i)
            pc_next = branch_target_i;
        else if (predict_taken_i === 1'b1)
            pc_next = predict_target_i;
        else
            pc_next = pc + pc_inc;
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            pc        <= 32'b0;
            buf_valid <= 1'b0;
            buf_half  <= 16'b0;
        end else if (!stall_i) begin
            if (branch_taken_i) begin
                pc        <= branch_target_i;
                buf_valid <= 1'b0;
            end else if (predict_taken_i === 1'b1) begin
                // Branch predictor redirect — clear buffer (same as EX redirect)
                pc        <= predict_target_i;
                buf_valid <= 1'b0;
            end else begin
                pc <= pc_next;
                // Buffer upper half when lower half was a RVC instruction
                // and we fetched a fresh word (not using buffer)
                if (!buf_valid && is_compressed && !pc[1]) begin
                    buf_half  <= imem_rdata_i[31:16];
                    buf_valid <= 1'b1;
                end else begin
                    buf_valid <= 1'b0;
                end
            end
        end
    end

    // Word-aligned address to instruction memory
    assign imem_addr_o = {pc[31:2], 2'b00};
    assign pc_if_o     = pc;

endmodule
