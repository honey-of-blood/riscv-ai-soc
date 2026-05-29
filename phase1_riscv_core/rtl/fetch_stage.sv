`timescale 1ns/1ps

// IF stage: PC register + branch mux + instruction memory address drive.
// Combinational read model: imem_addr = PC, imem_rdata available same cycle.
// The IF/ID pipeline register captures outputs on the next clock edge.
module fetch_stage (
    input  logic        clk,
    input  logic        rst,

    // Hazard unit — freeze PC when a stall is needed
    input  logic        stall_i,

    // EX stage branch/jump redirect
    input  logic        branch_taken_i,
    input  logic [31:0] branch_target_i,

    // Instruction memory interface (async/combinational read)
    output logic [31:0] imem_addr_o,
    input  logic [31:0] imem_rdata_i,

    // To IF/ID pipeline register
    output logic [31:0] pc_if_o,
    output logic [31:0] instr_if_o
);
    logic [31:0] pc, pc_next;

    // PC mux: redirect on branch/jump, else PC+4
    always_comb begin
        if (branch_taken_i)
            pc_next = branch_target_i;
        else
            pc_next = pc + 32'd4;
    end

    // PC register — stall holds, reset to 0.
    // Synchronous reset avoids Yosys proc_arst failures with self-referential else branch.
    always_ff @(posedge clk) begin
        if (rst) pc <= 32'b0;
        else     pc <= stall_i ? pc : pc_next;
    end

    // Drive instruction memory with current PC
    assign imem_addr_o  = pc;
    assign pc_if_o      = pc;
    assign instr_if_o   = imem_rdata_i;

endmodule
