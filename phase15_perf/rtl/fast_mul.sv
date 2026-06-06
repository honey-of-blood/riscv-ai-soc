`timescale 1ns/1ps

// Phase 15: single-cycle registered multiplier.
// USE_DSP=0: behavioral 64-bit multiply, registered.
// USE_DSP=1: DSP48E1 stub (Xilinx synthesis path).
// Icarus rule: signed intermediates extracted as assign outside always_ff.
module fast_mul #(
    parameter USE_DSP = 0
)(
    input  logic        clk,
    input  logic [31:0] a_i,
    input  logic [31:0] b_i,
    input  logic        signed_i,   // 1 = signed×signed (MUL/MULH)
    input  logic        mixed_i,    // 1 = MULHSU (signed a × unsigned b)
    output logic [63:0] result_o    // registered, available 1 cycle after inputs
);

`ifndef XILINX_DSP

    // -------------------------------------------------------------------------
    // Behavioral path (USE_DSP=0)
    // Icarus rule: signed casts must be assign outside always_ff.
    // -------------------------------------------------------------------------
    logic signed [63:0] ss_result;  // signed × signed
    logic signed [63:0] su_result;  // signed × unsigned (MULHSU)
    logic        [63:0] uu_result;  // unsigned × unsigned

    // Sign-extended operands (extracted as assign to satisfy Icarus)
    logic signed [32:0] a_signed_ext;
    logic signed [32:0] b_signed_ext;
    logic        [32:0] a_unsigned_ext;
    logic        [32:0] b_unsigned_ext;
    // MULHSU: both declared signed so Verilog treats multiply as signed×signed.
    // b_su_ext is zero-extended (bit32=0 → always positive), so semantics are correct.
    logic signed [32:0] a_su_ext;
    logic signed [32:0] b_su_ext;

    assign a_signed_ext   = {a_i[31], a_i};
    assign b_signed_ext   = {b_i[31], b_i};
    assign a_unsigned_ext = {1'b0,    a_i};
    assign b_unsigned_ext = {1'b0,    b_i};
    assign a_su_ext       = {a_i[31], a_i};   // signed a
    assign b_su_ext       = {1'b0,    b_i};   // zero-extended b, declared signed → positive

    // Combinational products
    assign ss_result = a_signed_ext * b_signed_ext;
    assign su_result = a_su_ext     * b_su_ext;      // signed×signed: b's sign bit is always 0
    assign uu_result = a_unsigned_ext * b_unsigned_ext;

    always_ff @(posedge clk) begin
        if (signed_i)
            result_o <= ss_result[63:0];
        else if (mixed_i)
            result_o <= su_result[63:0];
        else
            result_o <= uu_result;
    end

`else

    // -------------------------------------------------------------------------
    // DSP48E1 stub (Xilinx synthesis — behavioral replacement for sim)
    // In real synthesis: instantiate DSP48E1 primitives here.
    // -------------------------------------------------------------------------
    logic signed [63:0] ss_result_dsp;
    logic signed [63:0] su_result_dsp;
    logic        [63:0] uu_result_dsp;

    logic signed [32:0] a_se, b_se;
    logic        [32:0] a_ue, b_ue;
    logic signed [32:0] a_su_dsp, b_su_dsp;  // MULHSU: both signed to force signed multiply

    assign a_se      = {a_i[31], a_i};
    assign b_se      = {b_i[31], b_i};
    assign a_ue      = {1'b0,    a_i};
    assign b_ue      = {1'b0,    b_i};
    assign a_su_dsp  = {a_i[31], a_i};
    assign b_su_dsp  = {1'b0,    b_i};

    assign ss_result_dsp = a_se     * b_se;
    assign su_result_dsp = a_su_dsp * b_su_dsp;
    assign uu_result_dsp = a_ue     * b_ue;

    always_ff @(posedge clk) begin
        if (signed_i)
            result_o <= ss_result_dsp[63:0];
        else if (mixed_i)
            result_o <= su_result_dsp[63:0];
        else
            result_o <= uu_result_dsp;
    end

`endif

endmodule
