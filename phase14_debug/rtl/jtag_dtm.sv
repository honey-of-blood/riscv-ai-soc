`timescale 1ns/1ps

// Phase 14: JTAG Debug Transport Module (DTM) per RISC-V Debug Spec 0.13
// IEEE 1149.1 TAP with DTMCS and DMI access registers.
// Connects JTAG pins to DM AXI4-Lite interface.
module jtag_dtm (
    // JTAG pins
    input  logic        tck,
    input  logic        tdi,
    input  logic        tms,
    input  logic        trst_n,
    output logic        tdo,

    // DMI interface to dm_top
    output logic        dmi_req_valid,
    output logic [1:0]  dmi_req_op,
    output logic [5:0]  dmi_req_addr,
    output logic [31:0] dmi_req_data,
    input  logic        dmi_resp_valid,
    input  logic [31:0] dmi_resp_data,
    input  logic [1:0]  dmi_resp_op
);

    // -------------------------------------------------------------------------
    // TAP State Machine (16 states)
    // -------------------------------------------------------------------------
    typedef enum logic [3:0] {
        TEST_LOGIC_RESET = 4'd0,
        RUN_TEST_IDLE    = 4'd1,
        SELECT_DR_SCAN   = 4'd2,
        CAPTURE_DR       = 4'd3,
        SHIFT_DR         = 4'd4,
        EXIT1_DR         = 4'd5,
        PAUSE_DR         = 4'd6,
        EXIT2_DR         = 4'd7,
        UPDATE_DR        = 4'd8,
        SELECT_IR_SCAN   = 4'd9,
        CAPTURE_IR       = 4'd10,
        SHIFT_IR         = 4'd11,
        EXIT1_IR         = 4'd12,
        PAUSE_IR         = 4'd13,
        EXIT2_IR         = 4'd14,
        UPDATE_IR        = 4'd15
    } tap_state_e;

    tap_state_e tap_state;

    // TAP state transitions
    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) begin
            tap_state <= TEST_LOGIC_RESET;
        end else begin
            case (tap_state)
                TEST_LOGIC_RESET: tap_state <= tms ? TEST_LOGIC_RESET : RUN_TEST_IDLE;
                RUN_TEST_IDLE:    tap_state <= tms ? SELECT_DR_SCAN   : RUN_TEST_IDLE;
                SELECT_DR_SCAN:   tap_state <= tms ? SELECT_IR_SCAN   : CAPTURE_DR;
                CAPTURE_DR:       tap_state <= tms ? EXIT1_DR         : SHIFT_DR;
                SHIFT_DR:         tap_state <= tms ? EXIT1_DR         : SHIFT_DR;
                EXIT1_DR:         tap_state <= tms ? UPDATE_DR        : PAUSE_DR;
                PAUSE_DR:         tap_state <= tms ? EXIT2_DR         : PAUSE_DR;
                EXIT2_DR:         tap_state <= tms ? UPDATE_DR        : SHIFT_DR;
                UPDATE_DR:        tap_state <= tms ? SELECT_DR_SCAN   : RUN_TEST_IDLE;
                SELECT_IR_SCAN:   tap_state <= tms ? TEST_LOGIC_RESET : CAPTURE_IR;
                CAPTURE_IR:       tap_state <= tms ? EXIT1_IR         : SHIFT_IR;
                SHIFT_IR:         tap_state <= tms ? EXIT1_IR         : SHIFT_IR;
                EXIT1_IR:         tap_state <= tms ? UPDATE_IR        : PAUSE_IR;
                PAUSE_IR:         tap_state <= tms ? EXIT2_IR         : PAUSE_IR;
                EXIT2_IR:         tap_state <= tms ? UPDATE_IR        : SHIFT_IR;
                UPDATE_IR:        tap_state <= tms ? SELECT_DR_SCAN   : RUN_TEST_IDLE;
                default:          tap_state <= TEST_LOGIC_RESET;
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // Instruction register (6-bit)
    // -------------------------------------------------------------------------
    localparam [5:0] IR_IDCODE = 6'h01;
    localparam [5:0] IR_DTMCS  = 6'h10;
    localparam [5:0] IR_DMI    = 6'h11;
    localparam [5:0] IR_BYPASS = 6'h3F;

    localparam [31:0] IDCODE_VAL = 32'h0362_D093;

    logic [5:0] ir_r;      // latched IR
    logic [5:0] ir_shift;  // shift register for IR

    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) begin
            ir_r     <= IR_BYPASS;
            ir_shift <= 6'h3F;
        end else begin
            case (tap_state)
                CAPTURE_IR: ir_shift <= {4'b0001, 2'b01};  // standard capture value
                SHIFT_IR:   ir_shift <= {tdi, ir_shift[5:1]};
                UPDATE_IR:  ir_r     <= ir_shift;
                TEST_LOGIC_RESET: ir_r <= IR_IDCODE;
                default: ;
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // Data registers
    // -------------------------------------------------------------------------

    // BYPASS register (1-bit)
    logic bypass_r;
    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) bypass_r <= 1'b0;
        else if (tap_state == SHIFT_DR && ir_r == IR_BYPASS)
            bypass_r <= tdi;
    end

    // IDCODE register (32-bit shift register)
    logic [31:0] idcode_shift;
    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) begin
            idcode_shift <= IDCODE_VAL;
        end else begin
            case (tap_state)
                CAPTURE_DR: if (ir_r == IR_IDCODE) idcode_shift <= IDCODE_VAL;
                SHIFT_DR:   if (ir_r == IR_IDCODE) idcode_shift <= {tdi, idcode_shift[31:1]};
                default: ;
            endcase
        end
    end

    // DTMCS register (32-bit)
    // [17:16]=idle=5, [15:12]=dmistat, [11:10]=absbits=7, [9:4]=abits=6, [3:0]=version=1
    logic [15:0] dmistat_r;
    assign dmistat_r = 16'b0;  // no sticky error

    logic [31:0] dtmcs_val;
    assign dtmcs_val = {
        14'b0,
        2'd5,           // [17:16] idle
        dmistat_r[3:0], // [15:12] dmistat
        2'd7,           // [11:10] absbits (abstractcs size)
        6'd6,           // [9:4]   abits (DMI addr bits)
        4'd1            // [3:0]   version
    };

    logic [31:0] dtmcs_shift;
    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) begin
            dtmcs_shift <= 32'b0;
        end else begin
            case (tap_state)
                CAPTURE_DR: if (ir_r == IR_DTMCS) dtmcs_shift <= dtmcs_val;
                SHIFT_DR:   if (ir_r == IR_DTMCS) dtmcs_shift <= {tdi, dtmcs_shift[31:1]};
                default: ;
            endcase
        end
    end

    // DMI register (42-bit: [41:36]=addr, [35:4]=data, [3:2]=op, [1:0]=status)
    logic [41:0] dmi_shift;
    logic [41:0] dmi_r;

    // DMI response status
    logic [1:0] dmi_status_r;

    always_ff @(posedge tck or negedge trst_n) begin
        if (!trst_n) begin
            dmi_shift    <= 42'b0;
            dmi_r        <= 42'b0;
            dmi_status_r <= 2'b0;
            dmi_req_valid <= 1'b0;
            dmi_req_op    <= 2'b0;
            dmi_req_addr  <= 6'b0;
            dmi_req_data  <= 32'b0;
        end else begin
            dmi_req_valid <= 1'b0;

            case (tap_state)
                CAPTURE_DR: begin
                    if (ir_r == IR_DMI) begin
                        // Load response into shift register
                        if (dmi_resp_valid)
                            dmi_shift <= {dmi_r[41:36], dmi_resp_data, dmi_resp_op};
                        else
                            dmi_shift <= {dmi_r[41:36], dmi_r[35:4], dmi_status_r};
                    end
                end

                SHIFT_DR: begin
                    if (ir_r == IR_DMI)
                        dmi_shift <= {tdi, dmi_shift[41:1]};
                end

                UPDATE_DR: begin
                    if (ir_r == IR_DMI) begin
                        dmi_r <= dmi_shift;
                        // Issue DMI request if op != 0
                        if (dmi_shift[3:2] != 2'b00) begin
                            dmi_req_valid <= 1'b1;
                            dmi_req_op    <= dmi_shift[3:2];
                            dmi_req_addr  <= dmi_shift[41:36];
                            dmi_req_data  <= dmi_shift[35:4];
                        end
                    end
                end

                default: ;
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // TDO multiplexer (output on negedge TCK per IEEE 1149.1)
    // -------------------------------------------------------------------------
    logic tdo_pre;
    always_comb begin
        case (tap_state)
            SHIFT_IR: tdo_pre = ir_shift[0];
            SHIFT_DR: begin
                case (ir_r)
                    IR_IDCODE: tdo_pre = idcode_shift[0];
                    IR_DTMCS:  tdo_pre = dtmcs_shift[0];
                    IR_DMI:    tdo_pre = dmi_shift[0];
                    default:   tdo_pre = bypass_r;
                endcase
            end
            default: tdo_pre = 1'b0;
        endcase
    end

    // Register TDO on negedge
    always_ff @(negedge tck or negedge trst_n) begin
        if (!trst_n) tdo <= 1'b0;
        else         tdo <= tdo_pre;
    end

endmodule
