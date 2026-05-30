`timescale 1ns/1ps
// 128 KB scratchpad — 4 × 32 KB BRAM banks operating in parallel.
//
// Write port (32-bit AXI4-Lite slave):
//   CPU or DMA writes 32-bit words.  addr[16:2] selects the word; addr[1:0]
//   selects the bank (interleaved so consecutive bytes stay in adjacent banks).
//
// Read port (128-bit, direct to accelerator):
//   accel_addr[14:0] selects a 16-byte (128-bit) aligned row.
//   All four banks are read simultaneously in one cycle (registered).
//
// Address layout (byte addresses):
//   Bank 0: bytes [3:0]   of each 16-byte row
//   Bank 1: bytes [7:4]
//   Bank 2: bytes [11:8]
//   Bank 3: bytes [15:12]
//   Row address = byte_addr[16:4]  (13 bits → 8192 rows × 16 bytes = 128 KB)

module scratchpad #(
    parameter int ROWS = 8192   // 8192 × 16 bytes = 128 KB
)(
    input  logic        clk,
    input  logic        rst_n,

    // ── AXI4-Lite write port (32-bit) ─────────────────────────────────────
    input  logic [16:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,
    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,
    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,

    // AXI4-Lite read port (32-bit) — for CPU readback / debug
    input  logic [16:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready,

    // ── 128-bit parallel read port (accelerator) ──────────────────────────
    input  logic [12:0] accel_addr,    // row address (16-byte stride)
    output logic [127:0] accel_rdata  // 16 bytes in one cycle (registered)
);

    // ── BRAM storage — 4 banks, each ROWS words deep ──────────────────────
    // Bank b holds word b of each 16-byte row.
    logic [31:0] bank [0:3][0:ROWS-1];

    // Decode helpers
    logic [12:0] wr_row;
    logic  [1:0] wr_bank;
    assign wr_row  = s_awaddr[15:3];   // which 16-byte row
    assign wr_bank = s_awaddr[2:1];    // which 32-bit bank within the row

    // ── Write path ────────────────────────────────────────────────────────
    // Accept write address + data combinationally (AWREADY = WREADY = 1)
    assign s_awready = 1'b1;
    assign s_wready  = 1'b1;

    always_ff @(posedge clk) begin
        if (s_awvalid && s_wvalid) begin
            if (s_wstrb[0]) bank[wr_bank][wr_row][ 7: 0] <= s_wdata[ 7: 0];
            if (s_wstrb[1]) bank[wr_bank][wr_row][15: 8] <= s_wdata[15: 8];
            if (s_wstrb[2]) bank[wr_bank][wr_row][23:16] <= s_wdata[23:16];
            if (s_wstrb[3]) bank[wr_bank][wr_row][31:24] <= s_wdata[31:24];
        end
    end

    // BRESP: one cycle after write
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_bvalid <= 1'b0;
            s_bresp  <= 2'b00;
        end else begin
            s_bvalid <= (s_awvalid && s_wvalid) || (s_bvalid && !s_bready);
            s_bresp  <= 2'b00;
        end
    end

    // ── Read path (32-bit, AXI) ───────────────────────────────────────────
    logic [12:0] rd_row;
    logic  [1:0] rd_bank;
    assign rd_row  = s_araddr[15:3];
    assign rd_bank = s_araddr[2:1];

    assign s_arready = 1'b1;
    assign s_rresp   = 2'b00;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_rvalid <= 1'b0;
            s_rdata  <= 32'h0;
        end else if (s_arvalid) begin
            s_rvalid <= 1'b1;
            s_rdata  <= bank[rd_bank][rd_row];
        end else if (s_rready) begin
            s_rvalid <= 1'b0;
        end
    end

    // ── 128-bit accelerator read (registered for BRAM inference) ─────────
    always_ff @(posedge clk) begin
        accel_rdata[31:0]   <= bank[0][accel_addr];
        accel_rdata[63:32]  <= bank[1][accel_addr];
        accel_rdata[95:64]  <= bank[2][accel_addr];
        accel_rdata[127:96] <= bank[3][accel_addr];
    end

endmodule
