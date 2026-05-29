`timescale 1ns/1ps
// Synthesis-specific AXI4-Lite SRAM — 512-word subset (2 KB) of the
// simulation 64 KB SRAM.  The firmware only accesses a small number of
// addresses (< 0x200), so 512 words is representative for synthesis.
// RMW byte-enable pattern avoids multiple-$memwr-cell Yosys issue.

module axi_sram #(
    parameter DEPTH = 512   // synthesis: 512 words × 4 bytes = 2 KB
)(
    input  logic        clk,
    input  logic        rst_n,

    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,

    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,

    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,

    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,

    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready
);

localparam AW = $clog2(DEPTH);

logic [31:0] mem [0:DEPTH-1];

logic [AW-1:0] aw_waddr;
assign aw_waddr = s_awaddr[AW+1:2];

assign s_awready = 1'b1;
assign s_wready  = 1'b1;

logic        wr_pending;
logic [AW-1:0] wr_addr_r;
logic [31:0] wr_data_r;
logic  [3:0] wr_strb_r;

// RMW write: single $memwr cell, one always_ff block
logic [31:0] wr_mask;
assign wr_mask = {{8{wr_strb_r[3]}}, {8{wr_strb_r[2]}}, {8{wr_strb_r[1]}}, {8{wr_strb_r[0]}}};

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_pending <= 1'b0;
        s_bvalid   <= 1'b0;
    end else begin
        if (s_awvalid && s_wvalid) begin
            wr_addr_r  <= aw_waddr;
            wr_data_r  <= s_wdata;
            wr_strb_r  <= s_wstrb;
            wr_pending <= 1'b1;
        end
        if (wr_pending) begin
            mem[wr_addr_r] <= (mem[wr_addr_r] & ~wr_mask) | (wr_data_r & wr_mask);
            wr_pending <= 1'b0;
            s_bvalid   <= 1'b1;
        end
        if (s_bvalid && s_bready)
            s_bvalid <= 1'b0;
    end
end

assign s_bresp = 2'b00;

logic [AW-1:0] ar_waddr;
assign ar_waddr = s_araddr[AW+1:2];

assign s_arready = 1'b1;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        s_rvalid <= 1'b0;
        s_rdata  <= 32'd0;
    end else begin
        if (s_arvalid) begin
            s_rdata  <= mem[ar_waddr];
            s_rvalid <= 1'b1;
        end else if (s_rvalid && s_rready) begin
            s_rvalid <= 1'b0;
        end
    end
end

assign s_rresp = 2'b00;

endmodule
