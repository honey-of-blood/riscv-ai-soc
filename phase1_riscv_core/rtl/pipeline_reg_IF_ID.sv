`timescale 1ns/1ps

// IF/ID pipeline register.
// stall: hold current values (hazard unit freezes this stage).
// flush: insert NOP — used when a branch is taken and the fetched
//        instruction behind the branch must be killed.
// NOP = ADDI x0, x0, 0 = 32'h0000_0013
module pipeline_reg_IF_ID (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,
    input  logic        flush_i,

    // From fetch stage
    input  logic [31:0] pc_if_i,
    input  logic [31:0] instr_if_i,

    // To decode stage
    output logic [31:0] pc_id_o,
    output logic [31:0] instr_id_o
);
    localparam NOP = 32'h0000_0013; // ADDI x0, x0, 0

    always_ff @(posedge clk or posedge rst) begin
        if (rst || flush_i) begin
            pc_id_o    <= 32'b0;
            instr_id_o <= NOP;
        end else if (!stall_i) begin
            pc_id_o    <= pc_if_i;
            instr_id_o <= instr_if_i;
        end
        // stall: implicit — outputs hold their values
    end

endmodule
