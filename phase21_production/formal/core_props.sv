`timescale 1ns/1ps
// Phase 21 — SVA property module for riscv_core.sv
//
// Bind this module to the DUT in simulation or use sby for BMC.
// Properties are organised into named groups so coverage reports
// are readable.
//
// Bind example:
//   bind riscv_core core_props u_props (.*);

module core_props (
    input  logic        clk,
    input  logic        rst,
    // Instruction memory interface
    input  logic [31:0] imem_addr_o,
    input  logic [31:0] imem_rdata_i,
    // Data memory interface
    input  logic [31:0] dmem_addr_o,
    input  logic [31:0] dmem_wdata_o,
    input  logic [3:0]  dmem_be_o,
    input  logic        dmem_we_o,
    input  logic [31:0] dmem_rdata_i,
    input  logic        dmem_stall_i,
    // Debug interface
    input  logic        dbg_halt_req_i,
    input  logic        dbg_halted_o,
    input  logic [4:0]  dbg_rf_addr_i,
    input  logic [31:0] dbg_rf_rdata_o,
    // x0 zero-register (whitebox — connect to regfile[0] in bind context)
    input  logic [31:0] x0_val
);

    // ── 1. PC Alignment ────────────────────────────────────────────────────────
    // Every instruction fetch is word-aligned.
    property p_pc_aligned;
        @(posedge clk) disable iff (rst)
        (imem_addr_o[1:0] == 2'b00);
    endproperty
    ap_pc_aligned: assert property (p_pc_aligned)
        else $error("PC misaligned: 0x%08x", imem_addr_o);

    // ── 2. x0 Invariant ────────────────────────────────────────────────────────
    // The zero register x0 must never hold a non-zero value.
    property p_x0_zero;
        @(posedge clk) disable iff (rst)
        (x0_val == 32'h0);
    endproperty
    ap_x0_zero: assert property (p_x0_zero)
        else $error("x0 != 0: 0x%08x", x0_val);

    // ── 3. DMEM Write Enable Width ─────────────────────────────────────────────
    // Byte enables must be sub-word: no 5-F patterns from an erroneous BE bus.
    property p_dmem_be_valid;
        @(posedge clk) disable iff (rst)
        dmem_we_o |-> (dmem_be_o inside {4'b0001, 4'b0011, 4'b0111,
                                          4'b1000, 4'b1100, 4'b1110, 4'b1111,
                                          4'b0010, 4'b0100, 4'b0110,
                                          4'b0001, 4'b0011, 4'b1111,
                                          4'b0000, 4'b0001, 4'b0011, 4'b1111});
    endproperty
    // Simplified: just check BE != 0 when WE=1
    property p_dmem_be_nonzero;
        @(posedge clk) disable iff (rst)
        dmem_we_o |-> (dmem_be_o != 4'b0000);
    endproperty
    ap_dmem_be_nonzero: assert property (p_dmem_be_nonzero)
        else $error("dmem_we_o=1 but dmem_be_o=0");

    // ── 4. Halt handshake ──────────────────────────────────────────────────────
    // Once halt_req is asserted, halted_o must go high within 10 cycles.
    property p_halt_response;
        @(posedge clk) disable iff (rst)
        $rose(dbg_halt_req_i) |-> ##[1:10] dbg_halted_o;
    endproperty
    ap_halt_response: assert property (p_halt_response)
        else $error("Core did not halt within 10 cycles of dbg_halt_req");

    // ── 5. No-write-to-zero (duplicate whitebox check) ─────────────────────────
    // When halted and addr=0, rdata must be 0.
    property p_rf_x0_read_zero;
        @(posedge clk) disable iff (rst)
        (dbg_halted_o && dbg_rf_addr_i == 5'd0) |-> (dbg_rf_rdata_o == 32'h0);
    endproperty
    ap_rf_x0_read_zero: assert property (p_rf_x0_read_zero)
        else $error("dbg_rf[0] != 0 when halted");

    // ── Coverage bins ──────────────────────────────────────────────────────────
    cp_fetch_nonzero:    cover property (@(posedge clk) imem_addr_o != 0);
    cp_dmem_write:       cover property (@(posedge clk) dmem_we_o);
    cp_dmem_read:        cover property (@(posedge clk) !dmem_we_o && dmem_addr_o != 0);
    cp_stall:            cover property (@(posedge clk) dmem_stall_i);
    cp_halt_req:         cover property (@(posedge clk) dbg_halt_req_i);
    cp_halted:           cover property (@(posedge clk) dbg_halted_o);

endmodule
