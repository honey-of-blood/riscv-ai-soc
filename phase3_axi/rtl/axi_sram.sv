`timescale 1ns/1ps
// AXI4 slave wrapping a 64KB SRAM.
// Supports both AXI4-Lite (ARLEN=0) and AXI4 INCR bursts (ARLEN=1..255).
// Address range: 0x0000_0000 – 0x0000_FFFF
//
// Read bursts: accepts ARLEN, increments address by 4 bytes per beat,
//   asserts RLAST on the final beat.
// Write bursts: accepts AWLEN, WLAST; commits each W beat individually.
// AXI4-Lite compatibility: tie ARLEN=0, AWLEN=0, ARBURST=0, AWBURST=0 for
//   single-beat behaviour — identical to original AXI4-Lite interface.

module axi_sram #(
    parameter DEPTH = 16384  // 16384 words × 4 bytes = 64 KB
)(
    input  logic        clk,
    input  logic        rst_n,

    // ── AXI4 write address channel ────────────────────────────────────────
    input  logic [31:0] s_awaddr,
    input  logic  [7:0] s_awlen,     // 0 = 1 beat (AXI4-Lite compat)
    input  logic  [1:0] s_awburst,   // 01 = INCR
    input  logic        s_awvalid,
    output logic        s_awready,

    // ── AXI4 write data channel ───────────────────────────────────────────
    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wlast,
    input  logic        s_wvalid,
    output logic        s_wready,

    // ── AXI4 write response channel ───────────────────────────────────────
    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,

    // ── AXI4 read address channel ─────────────────────────────────────────
    input  logic [31:0] s_araddr,
    input  logic  [7:0] s_arlen,     // 0 = 1 beat
    input  logic  [1:0] s_arburst,   // 01 = INCR
    input  logic        s_arvalid,
    output logic        s_arready,

    // ── AXI4 read data channel ────────────────────────────────────────────
    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    output logic        s_rlast,
    input  logic        s_rready
);

localparam AW = $clog2(DEPTH);

logic [31:0] mem [0:DEPTH-1];

// ── Write path ────────────────────────────────────────────────────────────
// Accept AW immediately; buffer address + burst params.
// Accept W beats one by one, incrementing address per beat (INCR burst).

logic        wr_active;
logic [31:0] wr_cur_addr;
logic  [7:0] wr_remaining;
logic [AW-1:0] wr_waddr;
assign wr_waddr = wr_cur_addr[AW+1:2];

assign s_awready = !wr_active;
assign s_wready  =  wr_active;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_active    <= 1'b0;
        wr_cur_addr  <= 32'b0;
        wr_remaining <= 8'b0;
        s_bvalid     <= 1'b0;
    end else begin
        if (s_bvalid && s_bready) s_bvalid <= 1'b0;

        if (!wr_active) begin
            if (s_awvalid) begin
                wr_cur_addr  <= s_awaddr;
                wr_remaining <= s_awlen;
                wr_active    <= 1'b1;
            end
        end else begin
            if (s_wvalid) begin
                // Byte-enable write
                if (s_wstrb[0]) mem[wr_waddr][ 7: 0] <= s_wdata[ 7: 0];
                if (s_wstrb[1]) mem[wr_waddr][15: 8] <= s_wdata[15: 8];
                if (s_wstrb[2]) mem[wr_waddr][23:16] <= s_wdata[23:16];
                if (s_wstrb[3]) mem[wr_waddr][31:24] <= s_wdata[31:24];

                if (wr_remaining == 8'b0 || s_wlast) begin
                    wr_active <= 1'b0;
                    s_bvalid  <= 1'b1;
                end else begin
                    wr_cur_addr  <= wr_cur_addr + 4;
                    wr_remaining <= wr_remaining - 1'b1;
                end
            end
        end
    end
end

assign s_bresp = 2'b00;

// ── Read path ─────────────────────────────────────────────────────────────
// Burst read FSM: one beat per cycle after address handshake.
// 1-cycle SRAM latency: data arrives the cycle after the address is captured.

logic        rd_active;
logic [31:0] rd_cur_addr;
logic  [7:0] rd_remaining;
logic [AW-1:0] rd_raddr;
assign rd_raddr    = rd_cur_addr[AW+1:2];

assign s_arready = !rd_active;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rd_active    <= 1'b0;
        rd_cur_addr  <= 32'b0;
        rd_remaining <= 8'b0;
        s_rvalid     <= 1'b0;
        s_rdata      <= 32'b0;
        s_rlast      <= 1'b0;
    end else begin
        if (!rd_active) begin
            if (s_arvalid) begin
                rd_cur_addr  <= s_araddr;
                rd_remaining <= s_arlen;
                rd_active    <= 1'b1;
                // Serve first word immediately next cycle
                s_rdata  <= mem[s_araddr[AW+1:2]];
                s_rvalid <= 1'b1;
                s_rlast  <= (s_arlen == 8'b0);
            end
        end else begin
            if (s_rvalid && s_rready) begin
                if (rd_remaining == 8'b0) begin
                    // Last beat consumed
                    rd_active <= 1'b0;
                    s_rvalid  <= 1'b0;
                    s_rlast   <= 1'b0;
                end else begin
                    rd_cur_addr  <= rd_cur_addr + 4;
                    rd_remaining <= rd_remaining - 1'b1;
                    s_rdata  <= mem[(rd_cur_addr[AW+1:2]) + 1];
                    s_rvalid <= 1'b1;
                    s_rlast  <= (rd_remaining == 8'd1);
                end
            end
        end
    end
end

assign s_rresp = 2'b00;

endmodule
