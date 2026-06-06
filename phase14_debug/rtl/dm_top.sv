`timescale 1ns/1ps

// Phase 14: RISC-V Debug Module 0.13
// AXI4-Lite slave interface.
// Implements: dmcontrol, dmstatus, abstractcs, command, abstractauto,
//             data0, progbuf[0..3].
module dm_top (
    input  logic        clk,
    input  logic        rst_n,

    // AXI4-Lite slave (32-bit address and data)
    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,
    input  logic [31:0] s_wdata,
    input  logic [3:0]  s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,
    output logic [1:0]  s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,
    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [31:0] s_rdata,
    output logic [1:0]  s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready,

    // Hart debug interface
    output logic        dbg_halt_req_o,
    input  logic        dbg_halted_i,
    output logic        dbg_resume_req_o,
    output logic [4:0]  dbg_rf_addr_o,
    input  logic [31:0] dbg_rf_rdata_i,
    output logic [31:0] dbg_rf_wdata_o,
    output logic        dbg_rf_we_o,
    output logic        dbg_imem_ovr_en_o,
    output logic [31:0] dbg_imem_ovr_data_o,
    output logic        dbg_jump_en_o,
    output logic [31:0] dbg_jump_target_o,
    input  logic [31:0] dbg_imem_addr_i   // core imem_addr_o for progbuf mux
);

    // -------------------------------------------------------------------------
    // Register map byte offsets
    // -------------------------------------------------------------------------
    localparam [7:0] ADDR_DATA0      = 8'h10;
    localparam [7:0] ADDR_DMCONTROL  = 8'h40;
    localparam [7:0] ADDR_DMSTATUS   = 8'h44;
    localparam [7:0] ADDR_ABSTRACTCS = 8'h58;
    localparam [7:0] ADDR_COMMAND    = 8'h5C;
    localparam [7:0] ADDR_ABSTAUTO   = 8'h60;
    localparam [7:0] ADDR_PROGBUF0   = 8'h80;
    localparam [7:0] ADDR_PROGBUF1   = 8'h84;
    localparam [7:0] ADDR_PROGBUF2   = 8'h88;
    localparam [7:0] ADDR_PROGBUF3   = 8'h8C;

    localparam [31:0] PROGBUF_BASE   = 32'h0000_F000;

    // -------------------------------------------------------------------------
    // Internal registers
    // -------------------------------------------------------------------------
    logic [31:0] data0_r;
    logic        haltreq_r;       // dmcontrol[31]
    logic        dmactive_r;      // dmcontrol[0]
    logic [2:0]  cmderr_r;        // abstractcs[10:8]
    logic [31:0] abstauto_r;
    logic [31:0] progbuf_r [4];

    // Abstract command state machine
    typedef enum logic [3:0] {
        IDLE       = 4'd0,
        EXEC_CMD   = 4'd1,
        READ_GPR   = 4'd2,
        WRITE_GPR  = 4'd3,
        LAUNCH_PB  = 4'd4,
        PB_RUN     = 4'd5,
        PB_HALT    = 4'd6
    } cmd_state_e;

    cmd_state_e cmd_state;
    logic [7:0]  pb_count;

    // Saved command fields
    logic [7:0]  cmd_type_r;
    logic [2:0]  cmd_aarsize_r;
    logic        cmd_postexec_r;
    logic        cmd_transfer_r;
    logic        cmd_write_r;
    logic [15:0] cmd_regno_r;

    // Derived GPR address from regno (GPR: regno 0x1000-0x101F → addr 0-31)
    logic [4:0] cmd_gpr_addr;
    assign cmd_gpr_addr = cmd_regno_r[4:0];

    // -------------------------------------------------------------------------
    // AXI4-Lite: always ready
    // -------------------------------------------------------------------------
    assign s_awready = 1'b1;
    assign s_wready  = 1'b1;
    assign s_arready = 1'b1;

    // Write channel: both awvalid and wvalid must be high
    logic        wr_valid;
    logic [7:0]  wr_addr;
    logic [31:0] wr_data;
    assign wr_valid = s_awvalid && s_wvalid;
    assign wr_addr  = s_awaddr[7:0];
    assign wr_data  = s_wdata;

    // Read channel: latch on arvalid
    logic [7:0]  rd_addr;
    logic        rd_pending;

    // Write response: 1-cycle delay
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_bvalid <= 1'b0;
            s_bresp  <= 2'b00;
        end else begin
            s_bvalid <= wr_valid;
            s_bresp  <= 2'b00;  // OKAY
        end
    end

    // Read response
    logic [31:0] rd_data_comb;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_rvalid  <= 1'b0;
            s_rdata   <= 32'b0;
            s_rresp   <= 2'b00;
            rd_pending <= 1'b0;
            rd_addr   <= 8'b0;
        end else begin
            if (s_arvalid && !s_rvalid) begin
                rd_addr    <= s_araddr[7:0];
                rd_pending <= 1'b1;
            end
            if (rd_pending) begin
                s_rvalid   <= 1'b1;
                s_rdata    <= rd_data_comb;
                s_rresp    <= 2'b00;
                rd_pending <= 1'b0;
            end else if (s_rvalid && s_rready) begin
                s_rvalid   <= 1'b0;
            end
        end
    end

    // -------------------------------------------------------------------------
    // Register read (combinational)
    // -------------------------------------------------------------------------
    logic cmd_busy;
    assign cmd_busy = (cmd_state != IDLE);

    always_comb begin : read_decode
        case (rd_addr)
            ADDR_DATA0: rd_data_comb = data0_r;

            ADDR_DMCONTROL: rd_data_comb = {
                haltreq_r,    // [31] haltreq
                1'b0,         // [30] resumereq (WO, read 0)
                2'b00,        // [29:28] hartreset, ackhavereset
                1'b0,         // [27] setresethaltreq
                1'b0,         // [26] clrresethaltreq
                22'b0,        // [25:4] hartselhi, hartsello, hasel
                1'b0,         // [3] setresethaltreq
                1'b0,         // [2] clrresethaltreq
                1'b0,         // [1] ndmreset
                dmactive_r    // [0] dmactive
            };

            // dmstatus: [31:12]=0, [11]=allhalted, [10]=anyhalted,
            //           [9]=allrunning, [8]=anyrunning, [7:5]=0,
            //           [4]=authenticated, [3:0]=0
            ADDR_DMSTATUS: rd_data_comb =
                (dbg_halted_i  ? 32'h0000_0C00 : 32'h0000_0300) |
                32'h0000_0010;  // authenticated=1

            ADDR_ABSTRACTCS: rd_data_comb = {
                3'b0,
                5'd4,          // [28:24] progbufsize = 4
                11'b0,
                cmd_busy,      // [12] busy
                1'b0,
                cmderr_r,      // [10:8] cmderr
                4'b0,
                4'd1           // [3:0] datacount = 1
            };

            ADDR_ABSTAUTO: rd_data_comb = abstauto_r;

            ADDR_PROGBUF0: rd_data_comb = progbuf_r[0];
            ADDR_PROGBUF1: rd_data_comb = progbuf_r[1];
            ADDR_PROGBUF2: rd_data_comb = progbuf_r[2];
            ADDR_PROGBUF3: rd_data_comb = progbuf_r[3];

            default: rd_data_comb = 32'b0;
        endcase
    end

    // -------------------------------------------------------------------------
    // Register write and abstract command state machine
    // -------------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            data0_r        <= 32'b0;
            haltreq_r      <= 1'b0;
            dmactive_r     <= 1'b0;
            cmderr_r       <= 3'b0;
            abstauto_r     <= 32'b0;
            progbuf_r[0]   <= 32'b0;
            progbuf_r[1]   <= 32'b0;
            progbuf_r[2]   <= 32'b0;
            progbuf_r[3]   <= 32'b0;
            cmd_state      <= IDLE;
            pb_count       <= 8'b0;
            cmd_type_r     <= 8'b0;
            cmd_aarsize_r  <= 3'b0;
            cmd_postexec_r <= 1'b0;
            cmd_transfer_r <= 1'b0;
            cmd_write_r    <= 1'b0;
            cmd_regno_r    <= 16'b0;
            // outputs
            dbg_halt_req_o    <= 1'b0;
            dbg_resume_req_o  <= 1'b0;
            dbg_rf_addr_o     <= 5'b0;
            dbg_rf_wdata_o    <= 32'b0;
            dbg_rf_we_o       <= 1'b0;
            dbg_imem_ovr_en_o <= 1'b0;
            dbg_imem_ovr_data_o <= 32'b0;
            dbg_jump_en_o     <= 1'b0;
            dbg_jump_target_o <= 32'b0;
        end else begin

            // Default: deassert single-cycle signals
            dbg_resume_req_o <= 1'b0;
            dbg_rf_we_o      <= 1'b0;
            dbg_jump_en_o    <= 1'b0;

            // ----------------------------------------------------------------
            // AXI write processing
            // ----------------------------------------------------------------
            if (wr_valid) begin
                case (wr_addr)
                    ADDR_DATA0: data0_r <= wr_data;

                    ADDR_DMCONTROL: begin
                        dmactive_r <= wr_data[0];
                        if (wr_data[31]) begin
                            haltreq_r        <= 1'b1;
                            dbg_halt_req_o   <= 1'b1;
                        end else begin
                            haltreq_r      <= 1'b0;
                            dbg_halt_req_o <= 1'b0;
                        end
                        if (wr_data[30]) begin
                            // resumereq: pulse for 1 cycle
                            dbg_resume_req_o <= 1'b1;
                        end
                    end

                    ADDR_ABSTRACTCS: begin
                        // cmderr is W1C on bits [10:8]
                        if (wr_data[10]) cmderr_r[2] <= 1'b0;
                        if (wr_data[9])  cmderr_r[1] <= 1'b0;
                        if (wr_data[8])  cmderr_r[0] <= 1'b0;
                    end

                    ADDR_COMMAND: begin
                        if (cmd_state == IDLE) begin
                            cmd_type_r     <= wr_data[31:24];
                            cmd_aarsize_r  <= wr_data[22:20];
                            cmd_postexec_r <= wr_data[18];
                            cmd_transfer_r <= wr_data[17];
                            cmd_write_r    <= wr_data[16];
                            cmd_regno_r    <= wr_data[15:0];
                            cmd_state      <= EXEC_CMD;
                        end else begin
                            // busy: set cmderr=1
                            cmderr_r <= 3'd1;
                        end
                    end

                    ADDR_ABSTAUTO: abstauto_r <= wr_data;
                    ADDR_PROGBUF0: progbuf_r[0] <= wr_data;
                    ADDR_PROGBUF1: progbuf_r[1] <= wr_data;
                    ADDR_PROGBUF2: progbuf_r[2] <= wr_data;
                    ADDR_PROGBUF3: progbuf_r[3] <= wr_data;
                    default: ;
                endcase
            end

            // ----------------------------------------------------------------
            // Abstract command state machine
            // ----------------------------------------------------------------
            case (cmd_state)
                IDLE: begin
                    // Idle: nothing to do
                end

                EXEC_CMD: begin
                    // Validate command
                    if (cmd_type_r != 8'd0) begin
                        cmderr_r  <= 3'd2;  // not supported
                        cmd_state <= IDLE;
                    end else begin
                        if (cmd_transfer_r && !cmd_write_r) begin
                            // Read GPR
                            dbg_rf_addr_o <= cmd_gpr_addr;
                            cmd_state     <= READ_GPR;
                        end else if (cmd_transfer_r && cmd_write_r) begin
                            // Write GPR
                            dbg_rf_addr_o  <= cmd_gpr_addr;
                            dbg_rf_wdata_o <= data0_r;
                            dbg_rf_we_o    <= 1'b1;
                            cmd_state      <= WRITE_GPR;
                        end else if (!cmd_transfer_r && cmd_postexec_r) begin
                            // postexec only
                            cmd_state <= LAUNCH_PB;
                        end else begin
                            cmderr_r  <= 3'd2;  // not supported
                            cmd_state <= IDLE;
                        end
                    end
                end

                READ_GPR: begin
                    // Latch GPR read data into data0
                    data0_r   <= dbg_rf_rdata_i;
                    if (cmd_postexec_r)
                        cmd_state <= LAUNCH_PB;
                    else
                        cmd_state <= IDLE;
                end

                WRITE_GPR: begin
                    // Write was pulsed last cycle
                    if (cmd_postexec_r)
                        cmd_state <= LAUNCH_PB;
                    else
                        cmd_state <= IDLE;
                end

                LAUNCH_PB: begin
                    // Jump core to PROGBUF_BASE, release halt briefly
                    dbg_jump_en_o     <= 1'b1;
                    dbg_jump_target_o <= PROGBUF_BASE;
                    dbg_resume_req_o  <= 1'b1;
                    dbg_imem_ovr_en_o <= 1'b1;
                    pb_count          <= 8'd0;
                    cmd_state         <= PB_RUN;
                end

                PB_RUN: begin
                    dbg_imem_ovr_en_o <= 1'b1;
                    // Drive correct progbuf word based on fetch address
                    if (dbg_imem_addr_i[31:4] == PROGBUF_BASE[31:4]) begin
                        case (dbg_imem_addr_i[3:2])
                            2'd0: dbg_imem_ovr_data_o <= progbuf_r[0];
                            2'd1: dbg_imem_ovr_data_o <= progbuf_r[1];
                            2'd2: dbg_imem_ovr_data_o <= progbuf_r[2];
                            2'd3: dbg_imem_ovr_data_o <= progbuf_r[3];
                        endcase
                    end
                    pb_count <= pb_count + 8'd1;
                    if (pb_count >= 8'd15) begin
                        cmd_state         <= PB_HALT;
                        dbg_imem_ovr_en_o <= 1'b0;
                    end
                end

                PB_HALT: begin
                    // Re-assert halt request
                    dbg_halt_req_o <= 1'b1;
                    haltreq_r      <= 1'b1;
                    if (dbg_halted_i) begin
                        cmd_state <= IDLE;
                    end
                end

                default: cmd_state <= IDLE;
            endcase

        end
    end

endmodule
