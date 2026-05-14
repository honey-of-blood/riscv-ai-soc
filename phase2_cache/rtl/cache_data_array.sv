`timescale 1ns/1ps

// 64-set × 4-word (128-bit) data array.
// Write: one word at a time with 4-bit byte enable, synchronous.
// Read:  full 128-bit cache line, asynchronous.
module cache_data_array (
    input  logic        clk,

    // Write port
    input  logic        we_i,
    input  logic [5:0]  idx_i,       // set index
    input  logic [1:0]  word_i,      // which word within the line (0–3)
    input  logic [3:0]  be_i,        // byte enables
    input  logic [31:0] wdata_i,

    // Read port — full cache line, asynchronous
    output logic [31:0] word0_o,     // line word 0
    output logic [31:0] word1_o,     // line word 1
    output logic [31:0] word2_o,     // line word 2
    output logic [31:0] word3_o      // line word 3
);

    logic [31:0] mem [0:63][0:3];    // mem[set][word]

    // Byte-enable write — bit-selects inside always_ff are fine in Icarus
    always_ff @(posedge clk) begin : data_write
        if (we_i) begin
            if (be_i[0]) mem[idx_i][word_i][ 7: 0] <= wdata_i[ 7: 0];
            if (be_i[1]) mem[idx_i][word_i][15: 8] <= wdata_i[15: 8];
            if (be_i[2]) mem[idx_i][word_i][23:16] <= wdata_i[23:16];
            if (be_i[3]) mem[idx_i][word_i][31:24] <= wdata_i[31:24];
        end
    end

    // Asynchronous read of all four words
    assign word0_o = mem[idx_i][0];
    assign word1_o = mem[idx_i][1];
    assign word2_o = mem[idx_i][2];
    assign word3_o = mem[idx_i][3];

endmodule
