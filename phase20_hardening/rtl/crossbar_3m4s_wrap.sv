`timescale 1ns/1ps
// Testbench wrapper: axi4_crossbar_param instantiated at NM=3, NS=4
// Address map:
//   S0: 0x0000_0000 / mask 0xFFFF_0000
//   S1: 0x1000_0000 / mask 0xFFFF_0000
//   S2: 0x5000_0000 / mask 0xFFFF_0000
//   S3: 0x8000_0000 / mask 0xFFFF_0000

module crossbar_3m4s_wrap (
    input  logic clk,
    input  logic rst_n,
    // Masters (NM=3)
    input  logic [2:0]   m_awvalid,
    input  logic [95:0]  m_awaddr,
    output logic [2:0]   m_awready,
    input  logic [2:0]   m_wvalid,
    input  logic [95:0]  m_wdata,
    input  logic [11:0]  m_wstrb,
    output logic [2:0]   m_wready,
    output logic [2:0]   m_bvalid,
    output logic [5:0]   m_bresp,
    input  logic [2:0]   m_bready,
    input  logic [2:0]   m_arvalid,
    input  logic [95:0]  m_araddr,
    output logic [2:0]   m_arready,
    output logic [2:0]   m_rvalid,
    output logic [95:0]  m_rdata,
    output logic [5:0]   m_rresp,
    input  logic [2:0]   m_rready,
    // Slaves (NS=4)
    output logic [3:0]   s_awvalid,
    output logic [127:0] s_awaddr,
    input  logic [3:0]   s_awready,
    output logic [3:0]   s_wvalid,
    output logic [127:0] s_wdata,
    output logic [15:0]  s_wstrb,
    input  logic [3:0]   s_wready,
    input  logic [3:0]   s_bvalid,
    input  logic [7:0]   s_bresp,
    output logic [3:0]   s_bready,
    output logic [3:0]   s_arvalid,
    output logic [127:0] s_araddr,
    input  logic [3:0]   s_arready,
    input  logic [3:0]   s_rvalid,
    input  logic [127:0] s_rdata,
    input  logic [7:0]   s_rresp,
    output logic [3:0]   s_rready
);

// Slave s at bits [s*32+:32]: slave 0 at [31:0], slave 1 at [63:32], etc.
localparam [8*32-1:0] SBASE =
    {32'h0, 32'h0, 32'h0, 32'h0, 32'h8000_0000, 32'h5000_0000, 32'h1000_0000, 32'h0000_0000};
localparam [8*32-1:0] SMASK =
    {32'h0, 32'h0, 32'h0, 32'h0, 32'hFFFF_0000, 32'hFFFF_0000, 32'hFFFF_0000, 32'hFFFF_0000};

axi4_crossbar_param #(
    .NM         (3),
    .NS         (4),
    .DATA_W     (32),
    .ADDR_W     (32),
    .SLAVE_BASE (SBASE),
    .SLAVE_MASK (SMASK)
) u_xbar (
    .clk        (clk),
    .rst_n      (rst_n),
    .m_awvalid  (m_awvalid),
    .m_awaddr   (m_awaddr),
    .m_awready  (m_awready),
    .m_wvalid   (m_wvalid),
    .m_wdata    (m_wdata),
    .m_wstrb    (m_wstrb),
    .m_wready   (m_wready),
    .m_bvalid   (m_bvalid),
    .m_bresp    (m_bresp),
    .m_bready   (m_bready),
    .m_arvalid  (m_arvalid),
    .m_araddr   (m_araddr),
    .m_arready  (m_arready),
    .m_rvalid   (m_rvalid),
    .m_rdata    (m_rdata),
    .m_rresp    (m_rresp),
    .m_rready   (m_rready),
    .s_awvalid  (s_awvalid),
    .s_awaddr   (s_awaddr),
    .s_awready  (s_awready),
    .s_wvalid   (s_wvalid),
    .s_wdata    (s_wdata),
    .s_wstrb    (s_wstrb),
    .s_wready   (s_wready),
    .s_bvalid   (s_bvalid),
    .s_bresp    (s_bresp),
    .s_bready   (s_bready),
    .s_arvalid  (s_arvalid),
    .s_araddr   (s_araddr),
    .s_arready  (s_arready),
    .s_rvalid   (s_rvalid),
    .s_rdata    (s_rdata),
    .s_rresp    (s_rresp),
    .s_rready   (s_rready)
);

endmodule
