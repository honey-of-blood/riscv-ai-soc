`timescale 1ns/1ps

module reg_file (
    input  logic        clk,
    input  logic        rst,        // synchronous reset — clears all registers to 0
    input  logic        we,         // write enable
    input  logic [4:0]  rs1,        // read address 1
    input  logic [4:0]  rs2,        // read address 2
    input  logic [4:0]  rd,         // write address
    input  logic [31:0] wd,         // write data
    output logic [31:0] rd1,        // read data 1
    output logic [31:0] rd2,        // read data 2

    // Debug port — used by DM abstract commands when core is halted
    input  logic  [4:0] dbg_addr_i,
    output logic [31:0] dbg_rdata_o,  // async read
    input  logic [31:0] dbg_wdata_i,
    input  logic        dbg_we_i      // sync write on posedge clk
);
    logic [31:0] regs [1:31];       // x0 is not stored — hardwired to 0

    // Debug async read: x0 always returns 0
    assign dbg_rdata_o = (dbg_addr_i == 5'b0) ? 32'b0 : regs[dbg_addr_i];

    // Synchronous write with reset — x0 writes are silently ignored
    // dbg_we_i wins if both write the same register (core is halted during DM access)
    always_ff @(posedge clk) begin
        if (rst) begin
            for (int i = 1; i < 32; i++)
                regs[i] <= 32'b0;
        end else begin
            if (we && rd != 5'b0) begin
                regs[rd] <= wd;
            end
            if (dbg_we_i === 1'b1 && dbg_addr_i != 5'b0) begin
                regs[dbg_addr_i] <= dbg_wdata_i;
            end
        end
    end

    // Asynchronous read with write-before-read: if WB is writing the same
    // register being read in ID this cycle, return the new value directly.
    // This resolves the distance-3 RAW hazard without a forwarding path.
    assign rd1 = (rs1 == 5'b0)          ? 32'b0  :
                 (we && rd == rs1)       ? wd     : regs[rs1];
    assign rd2 = (rs2 == 5'b0)          ? 32'b0  :
                 (we && rd == rs2)       ? wd     : regs[rs2];

endmodule
