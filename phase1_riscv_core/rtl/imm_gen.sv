`timescale 1ns/1ps

// Generates sign-extended 32-bit immediate from a 32-bit instruction word.
// Encoding reference: RISC-V ISA Spec Vol I, Table 2.1
module imm_gen (
    input  logic [31:0] instr,
    output logic [31:0] imm
);
    // RV32I opcode definitions
    localparam OP_LOAD   = 7'b000_0011; // I-type
    localparam OP_IMM    = 7'b001_0011; // I-type
    localparam OP_JALR   = 7'b110_0111; // I-type
    localparam OP_SYSTEM = 7'b111_0011; // I-type
    localparam OP_STORE  = 7'b010_0011; // S-type
    localparam OP_BRANCH = 7'b110_0011; // B-type
    localparam OP_LUI    = 7'b011_0111; // U-type
    localparam OP_AUIPC  = 7'b001_0111; // U-type
    localparam OP_JAL    = 7'b110_1111; // J-type

    logic [6:0]  opcode;
    logic [31:0] imm_i, imm_s, imm_b, imm_u, imm_j;

    assign opcode = instr[6:0];

    // Precompute each immediate type with continuous assigns (Icarus compat)
    assign imm_i = {{20{instr[31]}}, instr[31:20]};
    assign imm_s = {{20{instr[31]}}, instr[31:25], instr[11:7]};
    assign imm_b = {{19{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
    assign imm_u = {instr[31:12], 12'b0};
    assign imm_j = {{11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0};

    // Select the correct immediate based on opcode — no bit ops inside case
    always_comb begin
        case (opcode)
            OP_LOAD,
            OP_IMM,
            OP_JALR,
            OP_SYSTEM : imm = imm_i;
            OP_STORE  : imm = imm_s;
            OP_BRANCH : imm = imm_b;
            OP_LUI,
            OP_AUIPC  : imm = imm_u;
            OP_JAL    : imm = imm_j;
            default   : imm = 32'b0;
        endcase
    end

endmodule
