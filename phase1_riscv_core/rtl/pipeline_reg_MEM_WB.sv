`timescale 1ns/1ps

// MEM/WB pipeline register.
// stall_i: freeze all outputs (cache miss stall — whole pipeline holds).
// No flush port: by the time an instruction reaches MEM/WB it is committed.
// Carries the four writeback candidates so WB stage can select via wb_sel.
module pipeline_reg_MEM_WB (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,

    // Data from MEM stage
    input  logic [31:0] alu_result_i,  // WB_ALU: ALU result
    input  logic [31:0] mem_rdata_i,   // WB_MEM: sign/zero-extended load data
    input  logic [31:0] pc_plus4_i,    // WB_PC4: JAL/JALR return address
    input  logic [31:0] imm_i,         // WB_IMM: LUI upper immediate

    // Control signals from MEM stage
    input  logic        reg_write_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [4:0]  rd_i,

    // Outputs to WB stage and register file
    output logic [31:0] alu_result_o,
    output logic [31:0] mem_rdata_o,
    output logic [31:0] pc_plus4_o,
    output logic [31:0] imm_o,

    output logic        reg_write_o,
    output logic [1:0]  wb_sel_o,
    output logic [4:0]  rd_o
);

    always_ff @(posedge clk) begin
        if (rst) begin
            alu_result_o <= 32'b0;
            mem_rdata_o  <= 32'b0;
            pc_plus4_o   <= 32'b0;
            imm_o        <= 32'b0;
            reg_write_o  <= 1'b0;
            wb_sel_o     <= 2'b0;
            rd_o         <= 5'b0;
        end else if (!stall_i) begin
            alu_result_o <= alu_result_i;
            mem_rdata_o  <= mem_rdata_i;
            pc_plus4_o   <= pc_plus4_i;
            imm_o        <= imm_i;
            reg_write_o  <= reg_write_i;
            wb_sel_o     <= wb_sel_i;
            rd_o         <= rd_i;
        end
    end

endmodule
