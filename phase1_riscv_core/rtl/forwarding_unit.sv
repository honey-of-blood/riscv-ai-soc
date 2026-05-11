`timescale 1ns/1ps

// Forwarding unit: detects RAW hazards that can be resolved by forwarding
// and drives the fwd_a/fwd_b mux selects in execute_stage.
//
// Priority: EX/MEM over MEM/WB (EX/MEM result is more recent).
// x0 is never forwarded — writes to x0 are suppressed by the register file.
//
// fwd_* encoding: 2'b00=use ID/EX data  2'b01=forward EX/MEM  2'b10=forward MEM/WB
module forwarding_unit (
    // Register addresses of the instruction currently in EX (from ID/EX register)
    input  logic [4:0]  rs1_ex_i,
    input  logic [4:0]  rs2_ex_i,

    // Destination register + write-enable of instruction in MEM (EX/MEM register)
    input  logic [4:0]  rd_mem_i,
    input  logic        reg_write_mem_i,

    // Destination register + write-enable of instruction in WB (MEM/WB register)
    input  logic [4:0]  rd_wb_i,
    input  logic        reg_write_wb_i,

    // Forwarding mux selects → execute_stage fwd_a_i / fwd_b_i
    output logic [1:0]  fwd_a_o,
    output logic [1:0]  fwd_b_o
);

    // rs1 forwarding
    always_comb begin
        if (reg_write_mem_i && (rd_mem_i != 5'b0) && (rd_mem_i == rs1_ex_i))
            fwd_a_o = 2'b01;   // EX/MEM → EX (takes priority)
        else if (reg_write_wb_i && (rd_wb_i != 5'b0) && (rd_wb_i == rs1_ex_i))
            fwd_a_o = 2'b10;   // MEM/WB → EX
        else
            fwd_a_o = 2'b00;   // no forwarding
    end

    // rs2 forwarding (identical structure)
    always_comb begin
        if (reg_write_mem_i && (rd_mem_i != 5'b0) && (rd_mem_i == rs2_ex_i))
            fwd_b_o = 2'b01;
        else if (reg_write_wb_i && (rd_wb_i != 5'b0) && (rd_wb_i == rs2_ex_i))
            fwd_b_o = 2'b10;
        else
            fwd_b_o = 2'b00;
    end

endmodule
