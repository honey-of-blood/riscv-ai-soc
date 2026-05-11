`timescale 1ns/1ps

// Hazard unit: detects load-use stalls and branch misprediction flushes.
// Purely combinational.
//
// --- Load-use stall ---
// When EX holds a LOAD and its rd matches rs1 or rs2 of the instruction
// currently in ID, forwarding cannot help (the value isn't ready yet).
// Fix: stall IF + ID for 1 cycle and insert a NOP bubble into ID/EX.
//
// --- Branch/jump flush (static not-taken prediction) ---
// The branch is resolved in the EX stage.  If taken, the two instructions
// already in the pipeline (one in ID, one in IF) are wrong and must be
// squashed.  fetch_stage redirects the PC autonomously via branch_taken_i;
// hazard_unit flushes IF/ID and ID/EX to drain those bad instructions.
//
// Load-use and branch_taken are mutually exclusive: a LOAD sets mem_read=1
// and branch_taken=0; a BRANCH/JUMP sets branch_taken potentially 1 and
// mem_read=0.  No priority arbitration is needed.
module hazard_unit (
    // Load-use inputs — instruction currently in EX stage
    input  logic        mem_read_ex_i,  // 1 when EX instruction is a LOAD
    input  logic [4:0]  rd_ex_i,        // destination register of EX instruction

    // Register addresses decoded by the instruction currently in ID
    input  logic [4:0]  rs1_id_i,
    input  logic [4:0]  rs2_id_i,

    // Branch/jump resolution from execute_stage
    input  logic        branch_taken_i,

    // --- Stall outputs ---
    output logic        stall_if_o,     // → fetch_stage.stall_i        (hold PC)
    output logic        stall_id_o,     // → pipeline_reg_IF_ID.stall_i (hold IF/ID)

    // --- Flush outputs ---
    output logic        flush_id_o,     // → pipeline_reg_IF_ID.flush_i (branch only)
    output logic        flush_ex_o      // → pipeline_reg_ID_EX.flush_i  (both hazards)
);

    logic load_use;

    // Load-use: rd_ex must be non-zero and match either source of the ID instruction
    assign load_use = mem_read_ex_i
                    && (rd_ex_i != 5'b0)
                    && ((rd_ex_i == rs1_id_i) || (rd_ex_i == rs2_id_i));

    assign stall_if_o = load_use;
    assign stall_id_o = load_use;
    assign flush_id_o = branch_taken_i;
    assign flush_ex_o = load_use | branch_taken_i;

endmodule
