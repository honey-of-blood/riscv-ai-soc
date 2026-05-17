`timescale 1ns/1ps
// Converts the riscv_core dmem port (simple RE/WE handshake) into an
// AXI4-Lite master.  Stalls the CPU for every access until the bus
// transaction completes.
//
// Note: the phase3 crossbar arbiter is registered — wr_busy/rd_busy
// becomes 1 one cycle after the master first presents AWVALID/ARVALID.
// The slave only sees routed signals the following edge.  This adapter
// naturally handles that by holding AWVALID/ARVALID until AWREADY/
// ARREADY (proper AXI4 handshake), guaranteeing the slave has latched.

module dmem_axi_adapter (
    input  logic        clk,
    input  logic        rst_n,

    // ── CPU dmem port ─────────────────────────────────────────────────────
    input  logic        cpu_re_i,
    input  logic        cpu_we_i,
    input  logic [31:0] cpu_addr_i,
    input  logic [31:0] cpu_wdata_i,
    input  logic  [3:0] cpu_be_i,
    output logic [31:0] cpu_rdata_o,
    output logic        cpu_stall_o,

    // ── AXI4-Lite master ──────────────────────────────────────────────────
    output logic [31:0] m_awaddr,
    output logic        m_awvalid,
    input  logic        m_awready,
    output logic [31:0] m_wdata,
    output logic  [3:0] m_wstrb,
    output logic        m_wvalid,
    input  logic        m_wready,
    input  logic  [1:0] m_bresp,
    input  logic        m_bvalid,
    output logic        m_bready,

    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [31:0] m_rdata,
    input  logic  [1:0] m_rresp,
    input  logic        m_rvalid,
    output logic        m_rready
);

typedef enum logic [2:0] {
    IDLE,
    WR_ADDR,   // driving awvalid+wvalid, waiting for handshake
    WR_RESP,   // waiting for bvalid
    RD_ADDR,   // driving arvalid, waiting for handshake
    RD_DATA    // waiting for rvalid
} state_t;

state_t state;

// Registered transaction parameters
logic [31:0] addr_r;
logic [31:0] wdata_r;
logic  [3:0] wstrb_r;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state      <= IDLE;
        addr_r     <= '0;
        wdata_r    <= '0;
        wstrb_r    <= '0;
        cpu_rdata_o <= '0;
    end else begin
        case (state)
            IDLE: begin
                if (cpu_we_i) begin
                    addr_r  <= cpu_addr_i;
                    wdata_r <= cpu_wdata_i;
                    wstrb_r <= cpu_be_i;
                    state   <= WR_ADDR;
                end else if (cpu_re_i) begin
                    addr_r  <= cpu_addr_i;
                    state   <= RD_ADDR;
                end
            end

            WR_ADDR: begin
                // Deassert when both channels are accepted
                if (m_awready && m_wready)
                    state <= WR_RESP;
            end

            WR_RESP: begin
                if (m_bvalid)
                    state <= IDLE;
            end

            RD_ADDR: begin
                if (m_arready)
                    state <= RD_DATA;
            end

            RD_DATA: begin
                if (m_rvalid) begin
                    cpu_rdata_o <= m_rdata;
                    state       <= IDLE;
                end
            end

            default: state <= IDLE;
        endcase
    end
end

// ── Combinational outputs ─────────────────────────────────────────────────────
always_comb begin
    // AXI write channel defaults
    m_awaddr  = addr_r;
    m_awvalid = (state == WR_ADDR);
    m_wdata   = wdata_r;
    m_wstrb   = wstrb_r;
    m_wvalid  = (state == WR_ADDR);
    m_bready  = (state == WR_RESP);

    // AXI read channel defaults
    m_araddr  = addr_r;
    m_arvalid = (state == RD_ADDR);
    m_rready  = (state == RD_DATA);

    // Stall only while the bus transaction is in flight.
    // When state returns to IDLE the pipeline advances one cycle; any new
    // memory access in the next MEM-stage instruction will restart a transaction.
    cpu_stall_o = (state != IDLE);
end

endmodule
