`timescale 1ns/1ps
// Synchronous instruction ROM — initialised from firmware.hex.
// Word-addressed: addr[31:2] selects the word (byte addr >> 2).
// 4096 words = 16 KB, sufficient for GCC-compiled programs (Phase 7+).
module instr_rom #(
    parameter DEPTH = 4096  // words; 16 KB
)(
    input  logic        clk,
    input  logic [31:0] addr,   // byte address (PC)
    output logic [31:0] rdata
);
    logic [31:0] mem [0:DEPTH-1];

    initial $readmemh("firmware.hex", mem);

    // Combinational read (matches riscv_core's imem model)
    logic [11:0] word_idx;
    assign word_idx = addr[13:2];  // 12-bit word index for 4096-word ROM
    assign rdata = mem[word_idx];
endmodule
