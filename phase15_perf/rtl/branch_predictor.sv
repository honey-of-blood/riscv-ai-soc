`timescale 1ns/1ps

// Phase 15: 32-entry BHT + 16-entry BTB branch predictor.
// BHT: 2-bit saturating counters indexed by pc[6:2].
// BTB: tag-based, indexed by pc[5:2], valid bit per entry.
// Prediction: combinational output; update: registered on branch_resolved_i.
module branch_predictor (
    input  logic        clk,
    input  logic        rst_n,

    // Prediction request (IF stage) — combinational output
    input  logic [31:0] pc_if_i,
    output logic        predict_taken_o,
    output logic [31:0] predict_target_o,

    // Update from EX stage (resolved branch/jump committing)
    input  logic        branch_resolved_i,
    input  logic        branch_taken_i,     // actual outcome
    input  logic [31:0] branch_pc_i,        // PC of branch instruction
    input  logic [31:0] branch_target_i     // actual target
);

    // -------------------------------------------------------------------------
    // BHT: 32 × 2-bit saturating counters
    // -------------------------------------------------------------------------
    logic [1:0] bht [32];

    // BTB: 16-entry tag + target + valid
    logic [31:0] btb_tag    [16];
    logic [31:0] btb_target [16];
    logic        btb_valid  [16];

    // -------------------------------------------------------------------------
    // Index extraction — use wires to avoid bit-selects in always blocks (Icarus)
    // -------------------------------------------------------------------------
    logic [4:0] bht_if_idx;
    logic [3:0] btb_if_idx;
    assign bht_if_idx = pc_if_i[6:2];
    assign btb_if_idx = pc_if_i[5:2];

    logic [4:0] bht_upd_idx;
    logic [3:0] btb_upd_idx;
    assign bht_upd_idx = branch_pc_i[6:2];
    assign btb_upd_idx = branch_pc_i[5:2];

    // -------------------------------------------------------------------------
    // Prediction: combinational
    // Taken if strongly/weakly taken (MSB=1) AND BTB hit for this PC
    // -------------------------------------------------------------------------
    logic btb_hit;
    assign btb_hit        = btb_valid[btb_if_idx] && (btb_tag[btb_if_idx] == pc_if_i);
    assign predict_taken_o  = bht[bht_if_idx][1] && btb_hit;
    assign predict_target_o = btb_target[btb_if_idx];

    // -------------------------------------------------------------------------
    // Reset and update logic
    // -------------------------------------------------------------------------
    integer i;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // Reset: weakly not-taken (2'b01), all BTB invalid
            for (i = 0; i < 32; i = i + 1)
                bht[i] <= 2'b01;
            for (i = 0; i < 16; i = i + 1) begin
                btb_valid[i]  <= 1'b0;
                btb_tag[i]    <= 32'b0;
                btb_target[i] <= 32'b0;
            end
        end else if (branch_resolved_i) begin
            // Update BHT saturating counter
            if (branch_taken_i) begin
                // Increment toward strongly taken (11)
                if (bht[bht_upd_idx] != 2'b11)
                    bht[bht_upd_idx] <= bht[bht_upd_idx] + 2'b01;
            end else begin
                // Decrement toward strongly not-taken (00)
                if (bht[bht_upd_idx] != 2'b00)
                    bht[bht_upd_idx] <= bht[bht_upd_idx] - 2'b01;
            end

            // Update BTB only on taken branches
            if (branch_taken_i) begin
                btb_tag[btb_upd_idx]    <= branch_pc_i;
                btb_target[btb_upd_idx] <= branch_target_i;
                btb_valid[btb_upd_idx]  <= 1'b1;
            end
        end
    end

endmodule
