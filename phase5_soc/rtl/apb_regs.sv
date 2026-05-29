`timescale 1ns/1ps
// Minimal APB register file — 512 × 32-bit words (2 KB).
// Address decode: paddr[10:2] → word index, covering the full range used
// by cache-line fill/evict operations (needs ≥ bit 10 to separate
// 0x1000_0000 from 0x1000_0400, which share the same cache set).
// Zero-wait (PREADY always 1), no error responses.
module apb_regs (
    input  logic        clk,
    input  logic        rst_n,
    input  logic [31:0] p_paddr,
    input  logic        p_psel,
    input  logic        p_penable,
    input  logic        p_pwrite,
    input  logic [31:0] p_pwdata,
    input  logic  [3:0] p_pstrb,
    output logic [31:0] p_prdata,
    output logic        p_pready,
    output logic        p_pslverr
);

logic [31:0] mem [0:511];
logic [8:0]  widx;
assign widx = p_paddr[10:2];

// Non-blocking array resets in for loops are unsupported by Verilator;
// initial block handles the zero-fill instead.
initial begin
    for (int i = 0; i < 512; i++) mem[i] = 32'h0;
end

logic [31:0] strb_mask;
assign strb_mask = {{8{p_pstrb[3]}}, {8{p_pstrb[2]}}, {8{p_pstrb[1]}}, {8{p_pstrb[0]}}};

always_ff @(posedge clk) begin
    if (p_psel && p_penable && p_pwrite)
        mem[widx] <= (mem[widx] & ~strb_mask) | (p_pwdata & strb_mask);
end

assign p_prdata  = mem[p_paddr[10:2]];
assign p_pready  = 1'b1;
assign p_pslverr = 1'b0;

endmodule
