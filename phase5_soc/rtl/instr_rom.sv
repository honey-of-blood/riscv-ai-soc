`timescale 1ns/1ps
// Synchronous instruction ROM — initialised from firmware.hex.
// Word-addressed: addr[31:2] selects the word (byte addr >> 2).
module instr_rom #(
    parameter DEPTH = 512  // words; 2 KB — ample for the firmware
)(
    input  logic        clk,
    input  logic [31:0] addr,   // byte address (PC)
    output logic [31:0] rdata
);
    logic [31:0] mem [0:DEPTH-1];

    initial $readmemh("firmware.hex", mem);

    // Combinational read (matches riscv_core's imem model)
    logic [8:0] word_idx;
    assign word_idx = addr[10:2];  // 9-bit word index for 512-word ROM
    assign rdata = mem[word_idx];
endmodule
