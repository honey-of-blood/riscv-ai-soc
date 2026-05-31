`timescale 1ns/1ps

// ID stage: decodes instruction fields, generates control signals and immediate.
// Purely combinational — no clock. The ID/EX pipeline register is separate.
// Register file is external; rs1_data_i/rs2_data_i are pre-read by the caller.
module decode_stage (
    // From IF/ID pipeline register
    input  logic [31:0] instr_i,
    input  logic [31:0] pc_i,

    // Register file read data (external — driven by riscv_core)
    input  logic [31:0] rs1_data_i,
    input  logic [31:0] rs2_data_i,

    // Register addresses — to reg_file read ports, hazard unit, forwarding unit
    output logic [4:0]  rs1_o,
    output logic [4:0]  rs2_o,
    output logic [4:0]  rd_o,
    output logic [2:0]  funct3_o,

    // Data to ID/EX pipeline register
    output logic [31:0] rs1_data_o,
    output logic [31:0] rs2_data_o,
    output logic [31:0] imm_o,
    output logic [31:0] pc_o,

    // Control signals to ID/EX pipeline register
    output logic        reg_write_o,    // write result to rd
    output logic        mem_read_o,     // LOAD: read data memory
    output logic        mem_write_o,    // STORE: write data memory
    output logic        alu_src_b_o,    // 0=rs2_data, 1=immediate
    output logic        alu_src_a_o,    // 0=rs1_data, 1=PC (AUIPC/JAL)
    output logic        branch_o,       // is a branch instruction
    output logic        jump_o,         // is JAL or JALR
    output logic [3:0]  alu_ctrl_o,     // ALU operation (matches alu.sv encodings)
    output logic [1:0]  wb_sel_o,       // writeback mux: 00=ALU 01=MEM 10=PC+4 11=IMM
    output logic        is_mext_o,      // RV32IM M-extension instruction (funct7=0000001)
    output logic        is_csr_o,       // CSR instruction (SYSTEM, funct3 != 000)
    output logic        is_mret_o,      // MRET instruction
    output logic [11:0] csr_addr_o,     // CSR register address (instr[31:20])
    // Phase 13: synchronous exception signals
    output logic        is_ecall_o,     // ECALL instruction
    output logic        is_ebreak_o,    // EBREAK instruction
    output logic        is_illegal_o,   // unrecognised encoding
    // Phase 13: RVA atomic signals
    output logic        is_lr_o,        // LR.W
    output logic        is_sc_o,        // SC.W
    output logic        is_amo_o,       // other AMO instruction
    output logic [4:0]  amo_funct5_o   // instr[31:27] for AMO sub-opcode
);

    // -------------------------------------------------------------------------
    // Opcode encodings
    // -------------------------------------------------------------------------
    localparam OP_R      = 7'b011_0011;
    localparam OP_IMM    = 7'b001_0011;
    localparam OP_LOAD   = 7'b000_0011;
    localparam OP_STORE  = 7'b010_0011;
    localparam OP_BRANCH = 7'b110_0011;
    localparam OP_JAL    = 7'b110_1111;
    localparam OP_JALR   = 7'b110_0111;
    localparam OP_LUI    = 7'b011_0111;
    localparam OP_AUIPC  = 7'b001_0111;
    localparam OP_SYSTEM = 7'b111_0011;
    localparam OP_AMO    = 7'b010_1111;  // RV32A atomic

    // ALU control encodings (must match alu.sv)
    localparam ALU_ADD  = 4'b0000;
    localparam ALU_SUB  = 4'b0001;
    localparam ALU_AND  = 4'b0010;
    localparam ALU_OR   = 4'b0011;
    localparam ALU_XOR  = 4'b0100;
    localparam ALU_SLL  = 4'b0101;
    localparam ALU_SRL  = 4'b0110;
    localparam ALU_SRA  = 4'b0111;
    localparam ALU_SLT  = 4'b1000;
    localparam ALU_SLTU = 4'b1001;

    // Writeback source select
    localparam WB_ALU = 2'b00;
    localparam WB_MEM = 2'b01;
    localparam WB_PC4 = 2'b10;
    localparam WB_IMM = 2'b11;

    // -------------------------------------------------------------------------
    // Field extraction — assigns outside always_comb (Icarus compat)
    // -------------------------------------------------------------------------
    logic [6:0]  opcode;
    logic [4:0]  rs1, rs2, rd;
    logic [2:0]  funct3;
    logic [6:0]  funct7;
    logic        funct7_5;    // instr[30]: ADD/SUB and SRL/SRA disambiguation
    logic [11:0] csr_addr;    // CSR address in SYSTEM instructions

    assign opcode   = instr_i[6:0];
    assign rd       = instr_i[11:7];
    assign funct3   = instr_i[14:12];
    assign rs1      = instr_i[19:15];
    assign rs2      = instr_i[24:20];
    assign funct7   = instr_i[31:25];
    assign funct7_5 = instr_i[30];
    assign csr_addr = instr_i[31:20];
    assign csr_addr_o   = csr_addr;
    assign amo_funct5_o = instr_i[31:27];

    // -------------------------------------------------------------------------
    // Immediate generation (instantiate shared imm_gen)
    // -------------------------------------------------------------------------
    imm_gen u_imm_gen (
        .instr (instr_i),
        .imm   (imm_o)
    );

    // -------------------------------------------------------------------------
    // Pass-throughs
    // -------------------------------------------------------------------------
    assign rs1_o      = rs1;
    assign rs2_o      = rs2;
    assign rd_o       = rd;
    assign funct3_o   = funct3;
    assign rs1_data_o = rs1_data_i;
    assign rs2_data_o = rs2_data_i;
    assign pc_o       = pc_i;

    // -------------------------------------------------------------------------
    // Main control decoder
    // -------------------------------------------------------------------------
    always_comb begin
        // Safe defaults — every signal gets a value (no latches)
        reg_write_o = 1'b0;
        mem_read_o  = 1'b0;
        mem_write_o = 1'b0;
        alu_src_b_o = 1'b0;
        alu_src_a_o = 1'b0;
        branch_o    = 1'b0;
        jump_o      = 1'b0;
        wb_sel_o    = WB_ALU;
        is_mext_o   = 1'b0;
        is_csr_o    = 1'b0;
        is_mret_o   = 1'b0;
        is_ecall_o  = 1'b0;
        is_ebreak_o = 1'b0;
        is_illegal_o= 1'b0;
        is_lr_o     = 1'b0;
        is_sc_o     = 1'b0;
        is_amo_o    = 1'b0;

        case (opcode)
            OP_R:     begin
                reg_write_o = 1'b1;
                is_mext_o   = (funct7 == 7'b000_0001);
            end
            OP_IMM:   begin
                reg_write_o = 1'b1;
                alu_src_b_o = 1'b1;
            end
            OP_LOAD:  begin
                reg_write_o = 1'b1;
                mem_read_o  = 1'b1;
                alu_src_b_o = 1'b1;
                wb_sel_o    = WB_MEM;
            end
            OP_STORE: begin
                mem_write_o = 1'b1;
                alu_src_b_o = 1'b1;
            end
            OP_BRANCH: begin
                branch_o = 1'b1;
            end
            OP_JAL:   begin
                reg_write_o = 1'b1;
                jump_o      = 1'b1;
                alu_src_a_o = 1'b1;  // PC as ALU A input → target = PC + imm
                alu_src_b_o = 1'b1;
                wb_sel_o    = WB_PC4;
            end
            OP_JALR:  begin
                reg_write_o = 1'b1;
                jump_o      = 1'b1;
                alu_src_b_o = 1'b1;  // rs1 as ALU A input → target = rs1 + imm
                wb_sel_o    = WB_PC4;
            end
            OP_LUI:   begin
                reg_write_o = 1'b1;
                wb_sel_o    = WB_IMM;
            end
            OP_AUIPC: begin
                reg_write_o = 1'b1;
                alu_src_a_o = 1'b1;  // PC as ALU A input → result = PC + imm
                alu_src_b_o = 1'b1;
            end
            OP_SYSTEM: begin
                if (funct3 != 3'b000) begin
                    // CSRRW/CSRRS/CSRRC (funct3=001/010/011)
                    is_csr_o    = 1'b1;
                    reg_write_o = (rd != 5'b0);
                end else begin
                    case (csr_addr)
                        12'h000: is_ecall_o  = 1'b1;  // ECALL
                        12'h001: is_ebreak_o = 1'b1;  // EBREAK
                        12'h302: begin                  // MRET
                            is_mret_o   = 1'b1;
                            jump_o      = 1'b1;
                            alu_src_a_o = 1'b1;
                            alu_src_b_o = 1'b1;
                        end
                        default: is_illegal_o = 1'b1;
                    endcase
                end
            end
            OP_AMO: begin   // RV32A
                reg_write_o = 1'b1;
                alu_src_b_o = 1'b1;   // addr = rs1 + 0 (imm_gen outputs 0 for OP_AMO)
                mem_read_o  = 1'b1;   // all AMOs read first
                wb_sel_o    = WB_MEM; // rd ← old memory value
                // amo_funct5_o = instr_i[31:27] pre-assigned outside always_comb
                case (amo_funct5_o)
                    5'b00010: is_lr_o  = 1'b1;   // LR.W
                    5'b00011: begin               // SC.W
                        is_sc_o     = 1'b1;
                        mem_read_o  = 1'b0;      // SC doesn't read; rd ← sc_result
                        mem_write_o = 1'b1;      // conditional write (gated in MEM stage)
                        wb_sel_o    = WB_IMM;    // rd ← sc_result routed through imm channel
                    end
                    default: begin                // AMOSWAP/ADD/AND/OR/XOR/MIN/MAX
                        is_amo_o    = 1'b1;
                        mem_write_o = 1'b1;
                    end
                endcase
            end
            default: is_illegal_o = 1'b1;
        endcase
    end

    // -------------------------------------------------------------------------
    // ALU control decoder
    // -------------------------------------------------------------------------
    always_comb begin
        alu_ctrl_o = ALU_ADD;  // default covers LOAD, STORE, JAL, JALR, AUIPC, LUI

        case (opcode)
            OP_R, OP_IMM: begin
                case (funct3)
                    3'b000: alu_ctrl_o = (opcode == OP_R && funct7_5) ? ALU_SUB : ALU_ADD;
                    3'b001: alu_ctrl_o = ALU_SLL;
                    3'b010: alu_ctrl_o = ALU_SLT;
                    3'b011: alu_ctrl_o = ALU_SLTU;
                    3'b100: alu_ctrl_o = ALU_XOR;
                    3'b101: alu_ctrl_o = funct7_5 ? ALU_SRA : ALU_SRL;
                    3'b110: alu_ctrl_o = ALU_OR;
                    3'b111: alu_ctrl_o = ALU_AND;
                    default: alu_ctrl_o = ALU_ADD;
                endcase
            end
            default: alu_ctrl_o = ALU_ADD;
        endcase
    end

endmodule
