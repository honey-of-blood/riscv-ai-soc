`timescale 1ns/1ps

// Testbench wrapper: exposes icache ports directly for cocotb testing.
module icache_wrap (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        flush_i,
    input  logic [31:0] cpu_addr_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,
    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [31:0] m_rdata,
    input  logic        m_rvalid,
    output logic        m_rready
);

    icache u_icache (
        .clk        (clk),
        .rst_n      (rst_n),
        .flush_i    (flush_i),
        .cpu_addr_i (cpu_addr_i),
        .cpu_rdata_o(cpu_rdata_o),
        .cpu_stall_o(cpu_stall_o),
        .m_araddr   (m_araddr),
        .m_arvalid  (m_arvalid),
        .m_arready  (m_arready),
        .m_rdata    (m_rdata),
        .m_rvalid   (m_rvalid),
        .m_rready   (m_rready)
    );

endmodule
