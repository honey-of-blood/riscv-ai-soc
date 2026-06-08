`timescale 1ns/1ps
// Two-flip-flop synchronizer for crossing clock domains.
// ASYNC_REG attribute tells Vivado to place both FFs in the same slice and
// insert a max-delay constraint automatically.
module cdc_sync2 #(parameter W = 1) (
    input  logic         clk_dst,
    input  logic [W-1:0] d,
    output logic [W-1:0] q
);
    (* ASYNC_REG = "TRUE" *) logic [W-1:0] ff1, ff2;
    always_ff @(posedge clk_dst) begin
        ff1 <= d;
        ff2 <= ff1;
    end
    assign q = ff2;
endmodule
