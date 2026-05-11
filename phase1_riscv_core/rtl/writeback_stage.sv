`timescale 1ns/1ps

// WB stage: selects the writeback value from four candidates via wb_sel.
// Purely combinational — no clock.
// wb_data_o feeds both the register file write port and the MEM/WB
// forwarding path in the forwarding unit.
module writeback_stage (
    // From MEM/WB pipeline register
    input  logic [31:0] alu_result_i,  // WB_ALU=00: ALU result
    input  logic [31:0] mem_rdata_i,   // WB_MEM=01: sign/zero-extended load data
    input  logic [31:0] pc_plus4_i,    // WB_PC4=10: JAL/JALR return address
    input  logic [31:0] imm_i,         // WB_IMM=11: LUI upper immediate
    input  logic        reg_write_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [4:0]  rd_i,

    // To register file write port + forwarding unit
    output logic [31:0] wb_data_o,
    output logic        reg_write_o,
    output logic [4:0]  rd_o
);

    localparam WB_ALU = 2'b00;
    localparam WB_MEM = 2'b01;
    localparam WB_PC4 = 2'b10;
    localparam WB_IMM = 2'b11;

    always_comb begin
        case (wb_sel_i)
            WB_MEM:  wb_data_o = mem_rdata_i;
            WB_PC4:  wb_data_o = pc_plus4_i;
            WB_IMM:  wb_data_o = imm_i;
            default: wb_data_o = alu_result_i;   // WB_ALU
        endcase
    end

    assign reg_write_o = reg_write_i;
    assign rd_o        = rd_i;

endmodule
