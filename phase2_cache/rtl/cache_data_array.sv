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

    // Flat 1-D array: 64 sets × 4 words = 256 entries.
    // Read-modify-write with a 32-bit byte-enable mask gives Yosys a single
    // $proc → single $memwr cell, avoiding the "Multiple edge sensitive events"
    // error that occurs when multiple conditional writes share an address net.
    logic [31:0] mem [0:255];

    logic [31:0] be_mask;
    assign be_mask = {{8{be_i[3]}}, {8{be_i[2]}}, {8{be_i[1]}}, {8{be_i[0]}}};

    always_ff @(posedge clk) begin : data_write
        if (we_i)
            mem[{idx_i,word_i}] <= (mem[{idx_i,word_i}] & ~be_mask)
                                 | (wdata_i & be_mask);
    end

    // Asynchronous read of all four words in the indexed set
    assign word0_o = mem[{idx_i, 2'b00}];
    assign word1_o = mem[{idx_i, 2'b01}];
    assign word2_o = mem[{idx_i, 2'b10}];
    assign word3_o = mem[{idx_i, 2'b11}];

endmodule
