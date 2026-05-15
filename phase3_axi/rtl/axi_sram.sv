`timescale 1ns/1ps
// AXI4-Lite slave wrapping a 64KB SRAM (word-addressed internally)
// Address range: 0x0000_0000 – 0x0000_FFFF
// - Byte-enable writes, word-aligned reads
// - Single-cycle latency: AWREADY/WREADY=1 combinationally, BVALID next cycle
//   ARREADY=1 combinationally, RVALID next cycle

module axi_sram #(
    parameter DEPTH = 16384  // 16384 words × 4 bytes = 64 KB
)(
    input  logic        clk,
    input  logic        rst_n,

    // AXI4-Lite slave port
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

localparam AW = $clog2(DEPTH);  // word-address width = 14

// SRAM array
logic [31:0] mem [0:DEPTH-1];

// ─── Write path ───────────────────────────────────────────────────────────────
// Accept AW and W simultaneously (common AXI4-Lite practice)
// Both channels must be valid before performing the write.

// Word address extracted outside always_comb (Icarus bit-select rule)
logic [AW-1:0] aw_waddr;
assign aw_waddr = s_awaddr[AW+1:2];  // byte→word: drop 2 LSBs

// Accept both channels when both valid
assign s_awready = 1'b1;
assign s_wready  = 1'b1;

logic wr_pending;
logic [AW-1:0] wr_addr_r;
logic [31:0]   wr_data_r;
logic  [3:0]   wr_strb_r;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_pending <= 1'b0;
        s_bvalid   <= 1'b0;
    end else begin
        // Latch write when AW+W both handshake
        if (s_awvalid && s_wvalid) begin
            wr_addr_r  <= aw_waddr;
            wr_data_r  <= s_wdata;
            wr_strb_r  <= s_wstrb;
            wr_pending <= 1'b1;
        end

        // Perform write to SRAM
        if (wr_pending) begin
            if (wr_strb_r[0]) mem[wr_addr_r][ 7: 0] <= wr_data_r[ 7: 0];
            if (wr_strb_r[1]) mem[wr_addr_r][15: 8] <= wr_data_r[15: 8];
            if (wr_strb_r[2]) mem[wr_addr_r][23:16] <= wr_data_r[23:16];
            if (wr_strb_r[3]) mem[wr_addr_r][31:24] <= wr_data_r[31:24];
            wr_pending <= 1'b0;
            s_bvalid   <= 1'b1;
        end

        // Clear BVALID once master accepts
        if (s_bvalid && s_bready)
            s_bvalid <= 1'b0;
    end
end

assign s_bresp = 2'b00;  // OKAY

// ─── Read path ────────────────────────────────────────────────────────────────
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

assign s_rresp = 2'b00;  // OKAY

endmodule
