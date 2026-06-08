`timescale 1ns/1ps
// 2-way set-associative tag array with LRU bits.
// Each entry stores {dirty, valid, tag[TAG_W-1:0]}.
// LRU bit per set: 0 = way0 is LRU (evict way0 next), 1 = way1 is LRU.
module cache_tag_array_2way #(
    parameter N_SETS = 64,
    parameter TAG_W  = 22
)(
    input  logic                     clk,
    input  logic                     rst,
    input  logic [$clog2(N_SETS)-1:0] index,

    // Way 0 write
    input  logic           we0,
    input  logic           valid_in0,
    input  logic           dirty_in0,
    input  logic [TAG_W-1:0] tag_in0,
    // Way 0 read
    output logic           valid_out0,
    output logic           dirty_out0,
    output logic [TAG_W-1:0] tag_out0,

    // Way 1 write
    input  logic           we1,
    input  logic           valid_in1,
    input  logic           dirty_in1,
    input  logic [TAG_W-1:0] tag_in1,
    // Way 1 read
    output logic           valid_out1,
    output logic           dirty_out1,
    output logic [TAG_W-1:0] tag_out1,

    // LRU (1 bit per set)
    input  logic           lru_we,
    input  logic           lru_in,
    output logic           lru_out
);
    // {dirty, valid, tag}
    logic [TAG_W+1:0] tags0 [0:N_SETS-1];
    logic [TAG_W+1:0] tags1 [0:N_SETS-1];
    logic             lru   [0:N_SETS-1];

    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < N_SETS; i = i + 1) begin
                tags0[i] <= '0;
                tags1[i] <= '0;
                lru[i]   <= 1'b0;
            end
        end else begin
            if (we0)   tags0[index] <= {dirty_in0, valid_in0, tag_in0};
            if (we1)   tags1[index] <= {dirty_in1, valid_in1, tag_in1};
            if (lru_we) lru[index]  <= lru_in;
        end
    end

    assign {dirty_out0, valid_out0, tag_out0} = tags0[index];
    assign {dirty_out1, valid_out1, tag_out1} = tags1[index];
    assign lru_out = lru[index];
endmodule
