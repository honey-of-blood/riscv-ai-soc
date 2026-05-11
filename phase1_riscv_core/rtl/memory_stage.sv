`timescale 1ns/1ps

// MEM stage: drives data memory interface; sign/zero-extends load data.
// Purely combinational — no clock. The MEM/WB pipeline register is separate.
// Assumes single-cycle data memory (SRAM model used in simulation).
module memory_stage (
    // From EX/MEM pipeline register
    input  logic [31:0] alu_result_i,   // memory address (and ALU result for WB_ALU)
    input  logic [31:0] rs2_data_i,     // store write data (already forwarded)
    input  logic [31:0] pc_plus4_i,
    input  logic [31:0] imm_i,
    input  logic        reg_write_i,
    input  logic        mem_read_i,
    input  logic        mem_write_i,
    input  logic [1:0]  wb_sel_i,
    input  logic [2:0]  funct3_i,      // encodes LB/LH/LW/LBU/LHU or SB/SH/SW
    input  logic [4:0]  rd_i,

    // Data memory interface (word-addressed, byte-enable write)
    output logic [31:0] dmem_addr_o,
    output logic [31:0] dmem_wdata_o,  // store data replicated to all byte lanes
    output logic        dmem_we_o,
    output logic        dmem_re_o,
    output logic [3:0]  dmem_be_o,     // byte enables (writes only)
    input  logic [31:0] dmem_rdata_i,

    // To MEM/WB pipeline register
    output logic [31:0] alu_result_o,
    output logic [31:0] mem_rdata_o,   // sign/zero-extended load result
    output logic [31:0] pc_plus4_o,
    output logic [31:0] imm_o,
    output logic        reg_write_o,
    output logic [1:0]  wb_sel_o,
    output logic [4:0]  rd_o
);

    // -------------------------------------------------------------------------
    // Icarus compat: extract part-selects from ports outside always_comb
    // -------------------------------------------------------------------------
    logic [1:0] byte_off;   // byte address within the word: alu_result[1:0]
    logic       half_off;   // halfword offset: alu_result[1]
    logic [7:0]  rs2_byte;
    logic [15:0] rs2_half;
    logic [1:0]  funct3_w;  // width sub-field of funct3: 00=byte 01=half 10=word

    assign byte_off = alu_result_i[1:0];
    assign half_off = alu_result_i[1];
    assign rs2_byte = rs2_data_i[7:0];
    assign rs2_half = rs2_data_i[15:0];
    assign funct3_w = funct3_i[1:0];

    // -------------------------------------------------------------------------
    // Memory control outputs
    // -------------------------------------------------------------------------
    assign dmem_addr_o = alu_result_i;
    assign dmem_we_o   = mem_write_i;
    assign dmem_re_o   = mem_read_i;

    // Store data: byte-replicate so memory only needs to obey byte enables
    always_comb begin
        case (funct3_w)
            2'b00:   dmem_wdata_o = {4{rs2_byte}};   // SB
            2'b01:   dmem_wdata_o = {2{rs2_half}};   // SH
            default: dmem_wdata_o = rs2_data_i;      // SW
        endcase
    end

    // Byte enables: active only during stores; full word for loads (don't-care)
    always_comb begin
        if (mem_write_i) begin
            case (funct3_w)
                2'b00: begin                          // SB — single byte lane
                    case (byte_off)
                        2'b00:   dmem_be_o = 4'b0001;
                        2'b01:   dmem_be_o = 4'b0010;
                        2'b10:   dmem_be_o = 4'b0100;
                        default: dmem_be_o = 4'b1000;
                    endcase
                end
                2'b01:   dmem_be_o = half_off ? 4'b1100 : 4'b0011; // SH
                default: dmem_be_o = 4'b1111;                       // SW
            endcase
        end else begin
            dmem_be_o = 4'b1111;
        end
    end

    // -------------------------------------------------------------------------
    // Load data: extract byte/halfword then sign/zero-extend.
    // funct3: LB=000 LH=001 LW=010 LBU=100 LHU=101
    // Icarus compat: all part-selects on dmem_rdata_i live outside always_comb.
    // -------------------------------------------------------------------------
    logic [7:0]  rdata_b0, rdata_b1, rdata_b2, rdata_b3;
    logic [15:0] rdata_lo, rdata_hi;

    assign rdata_b0 = dmem_rdata_i[7:0];
    assign rdata_b1 = dmem_rdata_i[15:8];
    assign rdata_b2 = dmem_rdata_i[23:16];
    assign rdata_b3 = dmem_rdata_i[31:24];
    assign rdata_lo = dmem_rdata_i[15:0];
    assign rdata_hi = dmem_rdata_i[31:16];

    logic [7:0]  rd_byte;
    logic [15:0] rd_half;
    logic        rd_byte_msb, rd_half_msb;

    always_comb begin
        case (byte_off)
            2'b00:   rd_byte = rdata_b0;
            2'b01:   rd_byte = rdata_b1;
            2'b10:   rd_byte = rdata_b2;
            default: rd_byte = rdata_b3;
        endcase
    end

    always_comb begin
        rd_half = half_off ? rdata_hi : rdata_lo;
    end

    // Sign bits — single-bit selects on local variables are fine in Icarus
    assign rd_byte_msb = rd_byte[7];
    assign rd_half_msb = rd_half[15];

    always_comb begin
        case (funct3_i)
            3'b000:  mem_rdata_o = {{24{rd_byte_msb}}, rd_byte};   // LB
            3'b001:  mem_rdata_o = {{16{rd_half_msb}}, rd_half};   // LH
            3'b010:  mem_rdata_o = dmem_rdata_i;                   // LW
            3'b100:  mem_rdata_o = {24'b0, rd_byte};               // LBU
            3'b101:  mem_rdata_o = {16'b0, rd_half};               // LHU
            default: mem_rdata_o = dmem_rdata_i;
        endcase
    end

    // -------------------------------------------------------------------------
    // Pass-throughs to MEM/WB
    // -------------------------------------------------------------------------
    assign alu_result_o = alu_result_i;
    assign pc_plus4_o   = pc_plus4_i;
    assign imm_o        = imm_i;
    assign reg_write_o  = reg_write_i;
    assign wb_sel_o     = wb_sel_i;
    assign rd_o         = rd_i;

endmodule
