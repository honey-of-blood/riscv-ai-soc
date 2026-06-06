`timescale 1ns/1ps
// True dual-port 64 KB instruction BRAM.
//
// Port A — instruction fetch (read-only from CPU perspective):
//   Async read so riscv_core sees instructions without an extra stall cycle.
//
// Port B — bootloader write port (AXI4-Lite slave at SoC address 0x2000_xxxx):
//   Allows the bootloader to overwrite instruction memory at run-time.
//   After writing a new image the bootloader jumps to the app entry point;
//   all subsequent instruction fetches via Port A see the new code.
//
// On FPGA: Xilinx infers a RAMB36 in SDP or TDP mode from this pattern.

module instr_bram #(
    parameter DEPTH = 16384   // 64 KB / 4 B per word
) (
    input  logic        clk,

    // Port A — instruction fetch
    input  logic [31:0] pa_addr_i,
    output logic [31:0] pa_rdata_o,

    // Port B — AXI4-Lite write (bootloader)
    input  logic        pb_en_i,
    input  logic        pb_we_i,
    input  logic [31:0] pb_addr_i,
    input  logic [31:0] pb_wdata_i,
    output logic [31:0] pb_rdata_o
);
    localparam AW = $clog2(DEPTH);

    logic [31:0] mem [0:DEPTH-1];

    // Port A: async read (no registered address — combinational output)
    assign pa_rdata_o = mem[pa_addr_i[AW+1:2]];

    // Port B: sync read/write
    always_ff @(posedge clk) begin
        if (pb_en_i) begin
            if (pb_we_i)
                mem[pb_addr_i[AW+1:2]] <= pb_wdata_i;
            pb_rdata_o <= mem[pb_addr_i[AW+1:2]];
        end
    end

    initial pb_rdata_o = '0;
endmodule
