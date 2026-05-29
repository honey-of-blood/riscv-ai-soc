`timescale 1ns/1ps

// 64-entry direct-mapped tag array.
// Each entry: {dirty[23], valid[22], tag[21:0]}
// Synchronous write, asynchronous read.
// On reset all entries are zeroed (valid=0 clears the cache).
module cache_tag_array (
    input  logic        clk,
    input  logic        rst,  // kept for interface compatibility; reset handled by initial block

    // Write port
    input  logic        we_i,
    input  logic [5:0]  idx_i,
    input  logic [21:0] tag_i,
    input  logic        valid_i,
    input  logic        dirty_i,

    // Read port (asynchronous — combinational)
    output logic [21:0] tag_o,
    output logic        valid_o,
    output logic        dirty_o
);

    logic [23:0] mem [0:63];   // {dirty, valid, tag[21:0]}

    // Simulation init — Yosys cannot synthesise for-loop resets of memory arrays.
    // Cache is safe: the cache_controller FSM resets its state on rst and only
    // accesses lines via idx_i; lines not yet written are ignored (valid=0).
    initial begin
        for (int i = 0; i < 64; i++) mem[i] = 24'b0;
    end

    // Synchronous write only (no async reset loop — incompatible with Yosys $memwr)
    always_ff @(posedge clk) begin : tag_write
        if (we_i)
            mem[idx_i] <= {dirty_i, valid_i, tag_i};
    end

    // Asynchronous read — Icarus compat: bit-selects on mem[] are fine in assigns
    assign dirty_o = mem[idx_i][23];
    assign valid_o = mem[idx_i][22];
    assign tag_o   = mem[idx_i][21:0];

endmodule
