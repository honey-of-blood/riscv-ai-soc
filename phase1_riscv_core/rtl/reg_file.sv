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
    output logic [31:0] rd2         // read data 2
);
    logic [31:0] regs [1:31];       // x0 is not stored — hardwired to 0

    // Synchronous write with reset — x0 writes are silently ignored
    always_ff @(posedge clk) begin
        if (rst) begin
            for (int i = 1; i < 32; i++)
                regs[i] <= 32'b0;
        end else if (we && rd != 5'b0) begin
            regs[rd] <= wd;
        end
    end

    // Asynchronous read — x0 always returns 0
    assign rd1 = (rs1 == 5'b0) ? 32'b0 : regs[rs1];
    assign rd2 = (rs2 == 5'b0) ? 32'b0 : regs[rs2];

endmodule
