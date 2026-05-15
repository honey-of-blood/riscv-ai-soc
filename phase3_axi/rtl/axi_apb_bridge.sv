`timescale 1ns/1ps
// AXI4-Lite to APB bridge
// AXI side: slave port (connects to crossbar slave port)
// APB side: master port (connects to peripheral)
// APB transaction: SETUP (1 cycle) → ENABLE (1+ cycles until PREADY)

module axi_apb_bridge (
    input  logic        clk,
    input  logic        rst_n,

    // AXI4-Lite slave
    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,
    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,
    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,
    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready,

    // APB master
    output logic [31:0] p_paddr,
    output logic        p_psel,
    output logic        p_penable,
    output logic        p_pwrite,
    output logic [31:0] p_pwdata,
    output logic  [3:0] p_pstrb,
    input  logic [31:0] p_prdata,
    input  logic        p_pready,
    input  logic        p_pslverr
);

// FSM states
typedef enum logic [2:0] {
    IDLE      = 3'd0,
    AXI_RD    = 3'd1,   // latch AR channel
    AXI_WR    = 3'd2,   // latch AW+W channels
    APB_SETUP = 3'd3,   // assert PSEL, de-assert PENABLE
    APB_ENAB  = 3'd4,   // assert PENABLE, wait for PREADY
    AXI_BRESP = 3'd5,   // return B to AXI master
    AXI_RRESP = 3'd6    // return R to AXI master
} state_t;

state_t state;

logic [31:0] lat_addr;
logic [31:0] lat_wdata;
logic  [3:0] lat_wstrb;
logic        lat_write;
logic [31:0] lat_rdata;
logic        lat_err;

// AXI handshake signals — combinationally driven from state
always_comb begin
    s_awready = 1'b0;
    s_wready  = 1'b0;
    s_arready = 1'b0;
    case (state)
        IDLE:   begin s_awready = s_awvalid && s_wvalid; s_wready = s_awvalid && s_wvalid; s_arready = s_arvalid && !s_awvalid; end
        AXI_WR: begin s_awready = 1'b1; s_wready = 1'b1; end
        default: begin end
    endcase
end

// APB outputs — driven from state
always_comb begin
    p_paddr   = lat_addr;
    p_psel    = (state == APB_SETUP) || (state == APB_ENAB);
    p_penable = (state == APB_ENAB);
    p_pwrite  = lat_write;
    p_pwdata  = lat_wdata;
    p_pstrb   = lat_wstrb;
end

// AXI response outputs
always_comb begin
    s_bvalid = (state == AXI_BRESP);
    s_bresp  = lat_err ? 2'b10 : 2'b00;  // SLVERR or OKAY
    s_rvalid = (state == AXI_RRESP);
    s_rdata  = lat_rdata;
    s_rresp  = lat_err ? 2'b10 : 2'b00;
end

// Main FSM
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state     <= IDLE;
        lat_addr  <= 32'd0;
        lat_wdata <= 32'd0;
        lat_wstrb <= 4'd0;
        lat_write <= 1'b0;
        lat_rdata <= 32'd0;
        lat_err   <= 1'b0;
    end else begin
        case (state)
            IDLE: begin
                // Prioritise write over read when both arrive simultaneously
                if (s_awvalid && s_wvalid) begin
                    lat_addr  <= s_awaddr;
                    lat_wdata <= s_wdata;
                    lat_wstrb <= s_wstrb;
                    lat_write <= 1'b1;
                    state     <= APB_SETUP;
                end else if (s_arvalid) begin
                    lat_addr  <= s_araddr;
                    lat_write <= 1'b0;
                    state     <= APB_SETUP;
                end
            end

            APB_SETUP: begin
                state <= APB_ENAB;
            end

            APB_ENAB: begin
                if (p_pready) begin
                    lat_rdata <= p_prdata;
                    lat_err   <= p_pslverr;
                    state     <= lat_write ? AXI_BRESP : AXI_RRESP;
                end
            end

            AXI_BRESP: begin
                if (s_bready) state <= IDLE;
            end

            AXI_RRESP: begin
                if (s_rready) state <= IDLE;
            end

            default: state <= IDLE;
        endcase
    end
end

endmodule
