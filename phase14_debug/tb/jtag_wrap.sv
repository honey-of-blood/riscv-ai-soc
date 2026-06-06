`timescale 1ns/1ps

// Phase 14 JTAG Wrapper
// Connects jtag_dtm + dm_top with a simple AXI4-Lite bridge.
// The JTAG DTM generates DMI requests which are converted to AXI4-Lite
// transactions for the debug module.
module jtag_wrap (
    input  logic        sys_clk,
    input  logic        sys_rst_n,

    // JTAG pins
    input  logic        tck,
    input  logic        tdi,
    input  logic        tms,
    input  logic        trst_n,
    output logic        tdo,

    // Expose DM status for test probing
    output logic        dbg_halted,
    output logic        dbg_halt_req,
    output logic        dbg_resume_req
);

    // -------------------------------------------------------------------------
    // DMI wires between jtag_dtm and the AXI bridge
    // -------------------------------------------------------------------------
    logic        dmi_req_valid;
    logic [1:0]  dmi_req_op;
    logic [5:0]  dmi_req_addr;
    logic [31:0] dmi_req_data;
    logic        dmi_resp_valid;
    logic [31:0] dmi_resp_data;
    logic [1:0]  dmi_resp_op;

    // -------------------------------------------------------------------------
    // AXI4-Lite wires to dm_top
    // -------------------------------------------------------------------------
    logic [31:0] s_awaddr;
    logic        s_awvalid;
    logic        s_awready;
    logic [31:0] s_wdata;
    logic [3:0]  s_wstrb;
    logic        s_wvalid;
    logic        s_wready;
    logic [1:0]  s_bresp;
    logic        s_bvalid;
    logic        s_bready;
    logic [31:0] s_araddr;
    logic        s_arvalid;
    logic        s_arready;
    logic [31:0] s_rdata;
    logic [1:0]  s_rresp;
    logic        s_rvalid;
    logic        s_rready;

    // DM hart signals (not connected to core in this wrapper — just DM alone)
    logic        dbg_halt_req_w;
    logic        dbg_resume_req_w;

    assign dbg_halt_req   = dbg_halt_req_w;
    assign dbg_resume_req = dbg_resume_req_w;
    assign dbg_halted     = 1'b0;  // No core in this wrapper

    // -------------------------------------------------------------------------
    // JTAG DTM
    // -------------------------------------------------------------------------
    jtag_dtm u_dtm (
        .tck            (tck),
        .tdi            (tdi),
        .tms            (tms),
        .trst_n         (trst_n),
        .tdo            (tdo),
        .dmi_req_valid  (dmi_req_valid),
        .dmi_req_op     (dmi_req_op),
        .dmi_req_addr   (dmi_req_addr),
        .dmi_req_data   (dmi_req_data),
        .dmi_resp_valid (dmi_resp_valid),
        .dmi_resp_data  (dmi_resp_data),
        .dmi_resp_op    (dmi_resp_op)
    );

    // -------------------------------------------------------------------------
    // Simple DMI to AXI4-Lite bridge
    // DMI addresses map directly to DM register byte offsets
    // DMI addr[5:0] → AXI addr = {24'b0, dmi_addr, 2'b0} (word-addressed)
    // -------------------------------------------------------------------------
    typedef enum logic [1:0] {
        BRIDGE_IDLE  = 2'd0,
        BRIDGE_WRITE = 2'd1,
        BRIDGE_READ  = 2'd2,
        BRIDGE_RESP  = 2'd3
    } bridge_state_e;

    bridge_state_e bridge_state;
    logic [31:0] bridge_resp_data;

    always_ff @(posedge sys_clk or negedge sys_rst_n) begin
        if (!sys_rst_n) begin
            bridge_state    <= BRIDGE_IDLE;
            s_awvalid       <= 1'b0;
            s_wvalid        <= 1'b0;
            s_arvalid       <= 1'b0;
            s_bready        <= 1'b1;
            s_rready        <= 1'b1;
            s_awaddr        <= 32'b0;
            s_wdata         <= 32'b0;
            s_wstrb         <= 4'hF;
            s_araddr        <= 32'b0;
            dmi_resp_valid  <= 1'b0;
            dmi_resp_data   <= 32'b0;
            dmi_resp_op     <= 2'b0;
        end else begin
            dmi_resp_valid <= 1'b0;

            case (bridge_state)
                BRIDGE_IDLE: begin
                    s_awvalid <= 1'b0;
                    s_wvalid  <= 1'b0;
                    s_arvalid <= 1'b0;
                    if (dmi_req_valid) begin
                        if (dmi_req_op == 2'd2) begin  // write
                            s_awaddr      <= {24'b0, dmi_req_addr, 2'b0};
                            s_wdata       <= dmi_req_data;
                            s_wstrb       <= 4'hF;
                            s_awvalid     <= 1'b1;
                            s_wvalid      <= 1'b1;
                            bridge_state  <= BRIDGE_WRITE;
                        end else if (dmi_req_op == 2'd1) begin  // read
                            s_araddr     <= {24'b0, dmi_req_addr, 2'b0};
                            s_arvalid    <= 1'b1;
                            bridge_state <= BRIDGE_READ;
                        end
                    end
                end

                BRIDGE_WRITE: begin
                    if (s_awready && s_wready) begin
                        s_awvalid    <= 1'b0;
                        s_wvalid     <= 1'b0;
                        bridge_state <= BRIDGE_RESP;
                    end
                end

                BRIDGE_READ: begin
                    if (s_arready) s_arvalid <= 1'b0;
                    if (s_rvalid) begin
                        bridge_resp_data <= s_rdata;
                        bridge_state     <= BRIDGE_RESP;
                    end
                end

                BRIDGE_RESP: begin
                    dmi_resp_valid <= 1'b1;
                    dmi_resp_data  <= bridge_resp_data;
                    dmi_resp_op    <= 2'b00;  // success
                    bridge_state   <= BRIDGE_IDLE;
                end

                default: bridge_state <= BRIDGE_IDLE;
            endcase
        end
    end

    // -------------------------------------------------------------------------
    // dm_top instantiation (no core connected — just DM registers)
    // -------------------------------------------------------------------------
    dm_top u_dm (
        .clk                  (sys_clk),
        .rst_n                (sys_rst_n),
        .s_awaddr             (s_awaddr),
        .s_awvalid            (s_awvalid),
        .s_awready            (s_awready),
        .s_wdata              (s_wdata),
        .s_wstrb              (s_wstrb),
        .s_wvalid             (s_wvalid),
        .s_wready             (s_wready),
        .s_bresp              (s_bresp),
        .s_bvalid             (s_bvalid),
        .s_bready             (s_bready),
        .s_araddr             (s_araddr),
        .s_arvalid            (s_arvalid),
        .s_arready            (s_arready),
        .s_rdata              (s_rdata),
        .s_rresp              (s_rresp),
        .s_rvalid             (s_rvalid),
        .s_rready             (s_rready),
        .dbg_halt_req_o       (dbg_halt_req_w),
        .dbg_halted_i         (1'b0),
        .dbg_resume_req_o     (dbg_resume_req_w),
        .dbg_rf_addr_o        (),
        .dbg_rf_rdata_i       (32'b0),
        .dbg_rf_wdata_o       (),
        .dbg_rf_we_o          (),
        .dbg_imem_ovr_en_o    (),
        .dbg_imem_ovr_data_o  (),
        .dbg_jump_en_o        (),
        .dbg_jump_target_o    (),
        .dbg_imem_addr_i      (32'b0)
    );

endmodule
