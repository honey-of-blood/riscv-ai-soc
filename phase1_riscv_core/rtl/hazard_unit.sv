`timescale 1ns/1ps

// Hazard unit: detects load-use stalls, branch flushes, and cache-miss stalls.
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
// --- Cache-miss stall ---
// When the L1 cache asserts stall (miss in progress), ALL five pipeline
// stages must freeze simultaneously.  Flushes are suppressed during stall
// so a branch in EX does not corrupt the frozen IF/ID and ID/EX registers;
// the flush fires normally on the cycle stall de-asserts.
module hazard_unit (
    // Load-use inputs — instruction currently in EX stage
    input  logic        mem_read_ex_i,  // 1 when EX instruction is a LOAD
    input  logic [4:0]  rd_ex_i,        // destination register of EX instruction

    // Register addresses decoded by the instruction currently in ID
    input  logic [4:0]  rs1_id_i,
    input  logic [4:0]  rs2_id_i,

    // Branch/jump resolution from execute_stage
    input  logic        branch_taken_i,

    // Cache-miss stall from L1 cache (cpu_stall_o)
    input  logic        cache_stall_i,

    // M-extension divide stall (32-cycle operation in EX stage)
    input  logic        mext_stall_i,

    // I-cache miss stall (Phase 15)
    input  logic        icache_stall_i,

    // Debug stall: core halted by debug module
    input  logic        debug_stall_i,

    // --- Stall outputs ---
    output logic        stall_if_o,      // → fetch_stage.stall_i         (hold PC)
    output logic        stall_id_o,      // → pipeline_reg_IF_ID.stall_i  (hold IF/ID)
    output logic        stall_id_ex_o,   // → pipeline_reg_ID_EX.stall_i  (hold ID/EX)
    output logic        stall_ex_mem_o,  // → pipeline_reg_EX_MEM.stall_i (hold EX/MEM)
    output logic        stall_mem_wb_o,  // → pipeline_reg_MEM_WB.stall_i (hold MEM/WB)

    // --- Flush outputs ---
    output logic        flush_id_o,     // → pipeline_reg_IF_ID.flush_i (branch only)
    output logic        flush_ex_o      // → pipeline_reg_ID_EX.flush_i  (both hazards)
);

    logic load_use;
    logic pipe_stall;   // any whole-pipeline stall (cache miss or M-ext divide)
    logic debug_stall;  // debug halt stall

    // Load-use: rd_ex must be non-zero and match either source of the ID instruction
    assign load_use = mem_read_ex_i
                    && (rd_ex_i != 5'b0)
                    && ((rd_ex_i == rs1_id_i) || (rd_ex_i == rs2_id_i));

    // Whole-pipeline stall: cache miss OR M-ext divide OR I-cache miss (all freeze all stages)
    assign pipe_stall  = cache_stall_i || mext_stall_i || (icache_stall_i === 1'b1);
    // Debug stall: z-safe case equality check
    assign debug_stall = (debug_stall_i === 1'b1);

    // Suppress flushes during any whole-pipeline stall so a branch sitting in EX
    // does not corrupt frozen IF/ID / ID/EX — the flush fires on resume.
    // Debug stall also suppresses flushes (core frozen in place).
    assign stall_if_o     = load_use || pipe_stall || debug_stall;
    assign stall_id_o     = load_use || pipe_stall || debug_stall;
    assign stall_id_ex_o  = pipe_stall || debug_stall;
    assign stall_ex_mem_o = pipe_stall || debug_stall;
    assign stall_mem_wb_o = pipe_stall || debug_stall;
    assign flush_id_o     = branch_taken_i && !pipe_stall && !debug_stall;
    assign flush_ex_o     = (load_use || branch_taken_i) && !pipe_stall && !debug_stall;

endmodule
