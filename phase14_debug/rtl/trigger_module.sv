`timescale 1ns/1ps

// Phase 14: Hardware trigger module.
// Supports 4 type-2 (address-match) triggers.
// Connected to csr_file trigger passthrough and riscv_core pipeline signals.
module trigger_module (
    input  logic        clk,
    input  logic        rst,

    // CSR interface (from csr_file passthrough)
    input  logic        tselect_we_i,
    input  logic [31:0] tselect_wd_i,
    input  logic        tdata1_we_i,
    input  logic [31:0] tdata1_wd_i,
    input  logic        tdata2_we_i,
    input  logic [31:0] tdata2_wd_i,
    output logic [31:0] tselect_rd_o,
    output logic [31:0] tdata1_rd_o,
    output logic [31:0] tdata2_rd_o,

    // Pipeline compare signals
    input  logic [31:0] pc_ex_i,      // EX-stage PC
    input  logic [31:0] mem_addr_i,   // data memory address
    input  logic        store_en_i,   // store operation active
    input  logic        load_en_i,    // load operation active

    // Output
    output logic        trigger_fire_o
);
    localparam int NUM_TRIGGERS = 4;
    // tdata1 reset value: type=2 (bits[31:28]=0010), m=1 (bit[6])
    // = 32'h2000_0040
    localparam [31:0] TDATA1_RESET = 32'h2000_0040;

    // -------------------------------------------------------------------------
    // Registers
    // -------------------------------------------------------------------------
    logic [31:0] tselect_r;
    logic [31:0] tdata1_r [NUM_TRIGGERS];
    logic [31:0] tdata2_r [NUM_TRIGGERS];

    // tselect index (safe clamp to NUM_TRIGGERS-1)
    logic [1:0] sel;
    assign sel = (tselect_r < 32'd4) ? tselect_r[1:0] : 2'd3;

    // CSR read outputs (based on current tselect)
    assign tselect_rd_o = tselect_r;
    assign tdata1_rd_o  = tdata1_r[sel];
    assign tdata2_rd_o  = tdata2_r[sel];

    // -------------------------------------------------------------------------
    // Sequential: CSR writes
    // -------------------------------------------------------------------------
    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            tselect_r <= 32'b0;
            for (i = 0; i < NUM_TRIGGERS; i = i + 1) begin
                tdata1_r[i] <= TDATA1_RESET;
                tdata2_r[i] <= 32'b0;
            end
        end else begin
            if (tselect_we_i)
                tselect_r <= tselect_wd_i;
            if (tdata1_we_i)
                tdata1_r[sel] <= tdata1_wd_i;
            if (tdata2_we_i)
                tdata2_r[sel] <= tdata2_wd_i;
        end
    end

    // -------------------------------------------------------------------------
    // Combinational: trigger firing
    // tdata1 bit[19]=execute, bit[18]=store, bit[17]=load
    // type-2 address match: fire when address matches tdata2 and action enabled
    // Icarus compat: extract all fields via continuous assigns outside always_comb
    // -------------------------------------------------------------------------

    // Extract type and action bits for each trigger (Icarus: assign outside always)
    logic [3:0]  t0_type,  t1_type,  t2_type,  t3_type;
    logic        t0_exec,  t1_exec,  t2_exec,  t3_exec;
    logic        t0_store, t1_store, t2_store, t3_store;
    logic        t0_load,  t1_load,  t2_load,  t3_load;

    assign t0_type  = tdata1_r[0][31:28]; assign t1_type  = tdata1_r[1][31:28];
    assign t2_type  = tdata1_r[2][31:28]; assign t3_type  = tdata1_r[3][31:28];
    assign t0_exec  = tdata1_r[0][19];    assign t1_exec  = tdata1_r[1][19];
    assign t2_exec  = tdata1_r[2][19];    assign t3_exec  = tdata1_r[3][19];
    assign t0_store = tdata1_r[0][18];    assign t1_store = tdata1_r[1][18];
    assign t2_store = tdata1_r[2][18];    assign t3_store = tdata1_r[3][18];
    assign t0_load  = tdata1_r[0][17];    assign t1_load  = tdata1_r[1][17];
    assign t2_load  = tdata1_r[2][17];    assign t3_load  = tdata1_r[3][17];

    // Per-trigger hit signals
    logic h0_exec, h1_exec, h2_exec, h3_exec;
    logic h0_store, h1_store, h2_store, h3_store;
    logic h0_load, h1_load, h2_load, h3_load;

    assign h0_exec  = (t0_type == 4'd2) && t0_exec  && (pc_ex_i  == tdata2_r[0]);
    assign h1_exec  = (t1_type == 4'd2) && t1_exec  && (pc_ex_i  == tdata2_r[1]);
    assign h2_exec  = (t2_type == 4'd2) && t2_exec  && (pc_ex_i  == tdata2_r[2]);
    assign h3_exec  = (t3_type == 4'd2) && t3_exec  && (pc_ex_i  == tdata2_r[3]);

    assign h0_store = (t0_type == 4'd2) && t0_store && store_en_i && (mem_addr_i == tdata2_r[0]);
    assign h1_store = (t1_type == 4'd2) && t1_store && store_en_i && (mem_addr_i == tdata2_r[1]);
    assign h2_store = (t2_type == 4'd2) && t2_store && store_en_i && (mem_addr_i == tdata2_r[2]);
    assign h3_store = (t3_type == 4'd2) && t3_store && store_en_i && (mem_addr_i == tdata2_r[3]);

    assign h0_load  = (t0_type == 4'd2) && t0_load  && load_en_i && (mem_addr_i == tdata2_r[0]);
    assign h1_load  = (t1_type == 4'd2) && t1_load  && load_en_i && (mem_addr_i == tdata2_r[1]);
    assign h2_load  = (t2_type == 4'd2) && t2_load  && load_en_i && (mem_addr_i == tdata2_r[2]);
    assign h3_load  = (t3_type == 4'd2) && t3_load  && load_en_i && (mem_addr_i == tdata2_r[3]);

    assign trigger_fire_o = h0_exec | h1_exec | h2_exec | h3_exec |
                            h0_store| h1_store| h2_store| h3_store|
                            h0_load | h1_load | h2_load | h3_load;

endmodule
