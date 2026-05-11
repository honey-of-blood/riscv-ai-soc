`timescale 1ns/1ps

module alu (
    input  logic [31:0] a,
    input  logic [31:0] b,
    input  logic [ 3:0] alu_ctrl,
    output logic [31:0] result,
    output logic        zero
);
    // ALU control encodings
    localparam ALU_ADD  = 4'b0000;
    localparam ALU_SUB  = 4'b0001;
    localparam ALU_AND  = 4'b0010;
    localparam ALU_OR   = 4'b0011;
    localparam ALU_XOR  = 4'b0100;
    localparam ALU_SLL  = 4'b0101;
    localparam ALU_SRL  = 4'b0110;
    localparam ALU_SRA  = 4'b0111;
    localparam ALU_SLT  = 4'b1000;
    localparam ALU_SLTU = 4'b1001;

    logic [4:0] shamt;
    assign shamt = b[4:0];

    always_comb begin
        case (alu_ctrl)
            ALU_ADD  : result = a + b;
            ALU_SUB  : result = a - b;
            ALU_AND  : result = a & b;
            ALU_OR   : result = a | b;
            ALU_XOR  : result = a ^ b;
            ALU_SLL  : result = a << shamt;
            ALU_SRL  : result = a >> shamt;
            ALU_SRA  : result = $signed(a) >>> shamt;
            ALU_SLT  : result = {31'b0, $signed(a) < $signed(b)};
            ALU_SLTU : result = {31'b0, a < b};
            default  : result = 32'b0;
        endcase
    end

    assign zero = (result == 32'b0);

endmodule
