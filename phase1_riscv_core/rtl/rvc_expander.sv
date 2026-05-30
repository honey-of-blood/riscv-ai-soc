`timescale 1ns/1ps

// RVC (compressed instruction) expander — purely combinational.
// All bit-slices of intermediate signals are extracted to assigns outside
// always_comb (Icarus compat rule: no bit-selects inside always_comb).
module rvc_expander (
    input  logic [15:0] rvc_i,
    output logic [31:0] rvi_o,
    output logic        valid_o
);
    // ── Field extraction ──────────────────────────���─────────────────────────
    logic [1:0]  q;
    logic [2:0]  funct3;
    logic [4:0]  rs1p, rs2p;   // "prime" regs x8-x15
    logic [4:0]  rd5;
    logic        bit12;

    assign q      = rvc_i[1:0];
    assign funct3 = rvc_i[15:13];
    assign rs1p   = {2'b01, rvc_i[9:7]};
    assign rs2p   = {2'b01, rvc_i[4:2]};
    assign rd5    = rvc_i[11:7];
    assign bit12  = rvc_i[12];

    // ── Immediate pre-computation (all as assigns) ───────────────────────────
    // CI imm: sign-ext {instr[12], instr[6:2]}
    logic [11:0] ci_imm12;
    assign ci_imm12 = {{6{rvc_i[12]}}, rvc_i[12], rvc_i[6:2]};

    // CL/CS offset for LW/SW: {0[4:0],instr[5],instr[12:10],instr[6],00}
    logic [11:0] cls_off;
    assign cls_off = {5'b0, rvc_i[5], rvc_i[12:10], rvc_i[6], 2'b00};

    // CIW nzuimm for ADDI4SPN
    logic [11:0] ciw_imm;
    assign ciw_imm = {2'b0, rvc_i[10:7], rvc_i[12:11], rvc_i[5], rvc_i[6], 2'b00};

    // CB branch offset (13-bit signed)
    logic [12:0] cb_off;
    assign cb_off = {{4{rvc_i[12]}}, rvc_i[12], rvc_i[6:5], rvc_i[2],
                     rvc_i[11:10], rvc_i[4:3], 1'b0};

    // CJ jump offset (21-bit signed)
    logic [20:0] cj_off;
    assign cj_off = {{9{rvc_i[12]}}, rvc_i[12], rvc_i[8], rvc_i[10:9],
                     rvc_i[6], rvc_i[7], rvc_i[2], rvc_i[11], rvc_i[5:3], 1'b0};

    // ADDI16SP nzimm (12-bit)
    logic [11:0] addi16sp_imm12;
    assign addi16sp_imm12 = {{3{rvc_i[12]}}, rvc_i[12], rvc_i[4:3],
                              rvc_i[5], rvc_i[2], rvc_i[6], 4'b0};

    // LWSP offset
    logic [11:0] lwsp_off;
    assign lwsp_off = {4'b0, rvc_i[3:2], rvc_i[12], rvc_i[6:4], 2'b00};

    // SWSP offset
    logic [11:0] swsp_off;
    assign swsp_off = {4'b0, rvc_i[8:7], rvc_i[12:9], 2'b00};

    // LUI nzuimm as upper-20 bits
    logic [19:0] lui_imm20;
    assign lui_imm20 = {{14{rvc_i[12]}}, rvc_i[12], rvc_i[6:2]};

    // SW imm split (for C.SW and C.SWSP)
    logic [6:0] sw_hi;    logic [4:0] sw_lo;
    logic [6:0] swsp_hi;  logic [4:0] swsp_lo;
    assign sw_hi   = cls_off[11:5];  assign sw_lo   = cls_off[4:0];
    assign swsp_hi = swsp_off[11:5]; assign swsp_lo = swsp_off[4:0];

    // shamt for shift instructions
    logic [4:0] shamt5;
    assign shamt5 = rvc_i[6:2];

    // CJ immediate field splits (pre-extracted for always_comb)
    logic        cj_b20, cj_b11;
    logic [9:0]  cj_b10_1;
    logic [7:0]  cj_b19_12;
    assign cj_b20    = cj_off[20];
    assign cj_b11    = cj_off[11];
    assign cj_b10_1  = cj_off[10:1];
    assign cj_b19_12 = cj_off[19:12];

    // CB immediate field splits
    logic        cb_b12, cb_b11;
    logic [5:0]  cb_b10_5;
    logic [3:0]  cb_b4_1;
    assign cb_b12   = cb_off[12];
    assign cb_b11   = cb_off[11];
    assign cb_b10_5 = cb_off[10:5];
    assign cb_b4_1  = cb_off[4:1];

    // rs2 5-bit field (Q2)
    logic [4:0] rs2_5;
    assign rs2_5 = rvc_i[6:2];

    // ── Expander logic (no bit-selects on local signals here) ───────────────
    always_comb begin
        rvi_o   = 32'h0000_0013;  // default: NOP (addi x0,x0,0)
        valid_o = 1'b0;

        case (q)
            // ───────── Q0 ─────────
            2'b00: begin
                case (funct3)
                    3'b000: begin // C.ADDI4SPN → addi rd', sp, nzuimm
                        rvi_o   = {ciw_imm, 5'd2, 3'b000, rs2p, 7'b0010011};
                        valid_o = (ciw_imm != 12'd0);
                    end
                    3'b010: begin // C.LW → lw rd', off(rs1')
                        rvi_o   = {cls_off, rs1p, 3'b010, rs2p, 7'b0000011};
                        valid_o = 1'b1;
                    end
                    3'b110: begin // C.SW → sw rs2', off(rs1')
                        rvi_o   = {sw_hi, rs2p, rs1p, 3'b010, sw_lo, 7'b0100011};
                        valid_o = 1'b1;
                    end
                    default: begin end
                endcase
            end

            // ───────── Q1 ─────────
            2'b01: begin
                case (funct3)
                    3'b000: begin // C.NOP / C.ADDI → addi rd, rd, imm
                        rvi_o   = {ci_imm12, rd5, 3'b000, rd5, 7'b0010011};
                        valid_o = 1'b1;
                    end
                    3'b001: begin // C.JAL (RV32) → jal x1, offset
                        rvi_o   = {cj_b20, cj_b10_1, cj_b11, cj_b19_12, 5'd1, 7'b1101111};
                        valid_o = 1'b1;
                    end
                    3'b010: begin // C.LI → addi rd, x0, imm
                        rvi_o   = {ci_imm12, 5'd0, 3'b000, rd5, 7'b0010011};
                        valid_o = 1'b1;
                    end
                    3'b011: begin
                        if (rd5 == 5'd2) begin // C.ADDI16SP
                            rvi_o   = {addi16sp_imm12, 5'd2, 3'b000, 5'd2, 7'b0010011};
                            valid_o = (addi16sp_imm12 != 12'd0);
                        end else begin // C.LUI
                            rvi_o   = {lui_imm20, rd5, 7'b0110111};
                            valid_o = (lui_imm20 != 20'd0);
                        end
                    end
                    3'b100: begin
                        case (rvc_i[11:10])
                            2'b00: begin // C.SRLI
                                rvi_o   = {7'b000_0000, shamt5, rs1p, 3'b101, rs1p, 7'b0010011};
                                valid_o = 1'b1;
                            end
                            2'b01: begin // C.SRAI
                                rvi_o   = {7'b010_0000, shamt5, rs1p, 3'b101, rs1p, 7'b0010011};
                                valid_o = 1'b1;
                            end
                            2'b10: begin // C.ANDI
                                rvi_o   = {ci_imm12, rs1p, 3'b111, rs1p, 7'b0010011};
                                valid_o = 1'b1;
                            end
                            2'b11: begin // CA sub-group
                                if (!bit12) begin
                                    case (rvc_i[6:5])
                                        2'b00: begin // C.SUB
                                            rvi_o   = {7'b010_0000, rs2p, rs1p, 3'b000, rs1p, 7'b0110011};
                                            valid_o = 1'b1;
                                        end
                                        2'b01: begin // C.XOR
                                            rvi_o   = {7'b000_0000, rs2p, rs1p, 3'b100, rs1p, 7'b0110011};
                                            valid_o = 1'b1;
                                        end
                                        2'b10: begin // C.OR
                                            rvi_o   = {7'b000_0000, rs2p, rs1p, 3'b110, rs1p, 7'b0110011};
                                            valid_o = 1'b1;
                                        end
                                        2'b11: begin // C.AND
                                            rvi_o   = {7'b000_0000, rs2p, rs1p, 3'b111, rs1p, 7'b0110011};
                                            valid_o = 1'b1;
                                        end
                                        default: begin end
                                    endcase
                                end
                                // bit12=1: SUBW/ADDW — RV64 only, leave as NOP/invalid
                            end
                            default: begin end
                        endcase
                    end
                    3'b101: begin // C.J → jal x0, offset
                        rvi_o   = {cj_b20, cj_b10_1, cj_b11, cj_b19_12, 5'd0, 7'b1101111};
                        valid_o = 1'b1;
                    end
                    3'b110: begin // C.BEQZ → beq rs1', x0, offset
                        rvi_o   = {cb_b12, cb_b10_5, 5'd0, rs1p, 3'b000, cb_b4_1, cb_b11, 7'b1100011};
                        valid_o = 1'b1;
                    end
                    3'b111: begin // C.BNEZ → bne rs1', x0, offset
                        rvi_o   = {cb_b12, cb_b10_5, 5'd0, rs1p, 3'b001, cb_b4_1, cb_b11, 7'b1100011};
                        valid_o = 1'b1;
                    end
                    default: begin end
                endcase
            end

            // ───────── Q2 ─────────
            2'b10: begin
                case (funct3)
                    3'b000: begin // C.SLLI → slli rd, rd, shamt
                        rvi_o   = {7'b000_0000, shamt5, rd5, 3'b001, rd5, 7'b0010011};
                        valid_o = (rd5 != 5'd0);
                    end
                    3'b010: begin // C.LWSP → lw rd, off(sp)
                        rvi_o   = {lwsp_off, 5'd2, 3'b010, rd5, 7'b0000011};
                        valid_o = (rd5 != 5'd0);
                    end
                    3'b100: begin
                        if (!bit12) begin
                            if (rs2_5 == 5'd0) begin // C.JR → jalr x0, rs1, 0
                                rvi_o   = {12'd0, rd5, 3'b000, 5'd0, 7'b1100111};
                                valid_o = (rd5 != 5'd0);
                            end else begin // C.MV → add rd, x0, rs2
                                rvi_o   = {7'b000_0000, rs2_5, 5'd0, 3'b000, rd5, 7'b0110011};
                                valid_o = 1'b1;
                            end
                        end else begin
                            if (rd5 == 5'd0 && rs2_5 == 5'd0) begin // C.EBREAK
                                rvi_o   = 32'h0010_0073;
                                valid_o = 1'b1;
                            end else if (rs2_5 == 5'd0) begin // C.JALR → jalr x1, rs1, 0
                                rvi_o   = {12'd0, rd5, 3'b000, 5'd1, 7'b1100111};
                                valid_o = (rd5 != 5'd0);
                            end else begin // C.ADD → add rd, rd, rs2
                                rvi_o   = {7'b000_0000, rs2_5, rd5, 3'b000, rd5, 7'b0110011};
                                valid_o = (rd5 != 5'd0);
                            end
                        end
                    end
                    3'b110: begin // C.SWSP → sw rs2, off(sp)
                        rvi_o   = {swsp_hi, rs2_5, 5'd2, 3'b010, swsp_lo, 7'b0100011};
                        valid_o = 1'b1;
                    end
                    default: begin end
                endcase
            end

            default: begin end
        endcase
    end

endmodule
