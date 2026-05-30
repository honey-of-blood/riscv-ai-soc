`timescale 1ns/1ps

// Atomic memory operations for RV32A extension.
// Supports: LR.W, SC.W, AMOSWAP.W, AMOADD.W, AMOAND.W, AMOOR.W, AMOXOR.W.
// AMO operations are carried out as read-modify-write by the memory stage.
// This unit provides:
//   - reservation set/clear logic for LR/SC
//   - AMO result computation (new write value + old read value for rd)
module atomic_unit (
    input  logic        clk,
    input  logic        rst,

    // From memory/execute stage
    input  logic        lr_valid_i,     // LR.W instruction in MEM stage
    input  logic        sc_valid_i,     // SC.W instruction in MEM stage
    input  logic        amo_valid_i,    // AMO instruction in MEM stage
    input  logic [2:0]  amo_funct3_i,  // AMO sub-opcode from funct3/funct5
    input  logic [4:0]  amo_funct5_i,  // funct5 = instr[31:27] for AMOs
    input  logic [31:0] mem_addr_i,    // byte address
    input  logic [31:0] rs2_data_i,    // operand 2 (SC store value or AMO operand)
    input  logic [31:0] mem_rdata_i,   // data read from memory (for AMO RMW)

    // SC result written to rd: 0=success, 1=failure
    output logic [31:0] sc_result_o,

    // AMO outputs
    output logic [31:0] amo_wdata_o,   // value to write back to memory
    output logic [31:0] amo_rd_o,      // value to write back to rd (= old mem value)

    // Memory write-enable override (SC only writes on success)
    output logic        sc_store_en_o  // 1 = SC succeeded, perform the store
);
    // -------------------------------------------------------------------------
    // Reservation register
    // -------------------------------------------------------------------------
    logic        reservation_set;
    logic [31:0] reservation_addr;

    always_ff @(posedge clk) begin
        if (rst) begin
            reservation_set  <= 1'b0;
            reservation_addr <= 32'b0;
        end else begin
            if (lr_valid_i) begin
                reservation_set  <= 1'b1;
                reservation_addr <= mem_addr_i;
            end else if (sc_valid_i) begin
                reservation_set <= 1'b0;   // SC always clears reservation
            end
        end
    end

    // SC succeeds only if reservation matches current address
    logic sc_success;
    assign sc_success    = reservation_set && (reservation_addr == mem_addr_i);
    assign sc_result_o   = sc_success ? 32'd0 : 32'd1;
    assign sc_store_en_o = sc_success;

    // -------------------------------------------------------------------------
    // AMO operation: compute new memory value and capture old value for rd
    // -------------------------------------------------------------------------
    // funct5 encodings (RISC-V A-extension):
    //   00001 = AMOSWAP   00000 = AMOADD
    //   00111 = AMOAND    00110 = AMOOR    00100 = AMOXOR
    //   10000 = AMOMIN    10100 = AMOMAX   11000 = AMOMINU  11100 = AMOMAXU

    logic signed [31:0] mem_signed, rs2_signed;
    assign mem_signed = $signed(mem_rdata_i);
    assign rs2_signed = $signed(rs2_data_i);

    always_comb begin
        amo_rd_o    = mem_rdata_i;   // rd always gets old memory value
        amo_wdata_o = rs2_data_i;    // default: AMOSWAP

        case (amo_funct5_i)
            5'b00001: amo_wdata_o = rs2_data_i;                                    // AMOSWAP
            5'b00000: amo_wdata_o = mem_rdata_i + rs2_data_i;                     // AMOADD
            5'b00111: amo_wdata_o = mem_rdata_i & rs2_data_i;                     // AMOAND
            5'b00110: amo_wdata_o = mem_rdata_i | rs2_data_i;                     // AMOOR
            5'b00100: amo_wdata_o = mem_rdata_i ^ rs2_data_i;                     // AMOXOR
            5'b10000: amo_wdata_o = (mem_signed < rs2_signed) ? mem_rdata_i : rs2_data_i; // AMOMIN
            5'b10100: amo_wdata_o = (mem_signed > rs2_signed) ? mem_rdata_i : rs2_data_i; // AMOMAX
            5'b11000: amo_wdata_o = (mem_rdata_i < rs2_data_i) ? mem_rdata_i : rs2_data_i; // AMOMINU
            5'b11100: amo_wdata_o = (mem_rdata_i > rs2_data_i) ? mem_rdata_i : rs2_data_i; // AMOMAXU
            default:  amo_wdata_o = rs2_data_i;
        endcase
    end

endmodule
