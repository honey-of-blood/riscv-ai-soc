`timescale 1ns/1ps
// Parameterized AXI4-Lite crossbar  NM masters × NS slaves
// Parameters:
//   NM, NS       – master/slave count (max 8 each)
//   DATA_W       – data bus width (default 32)
//   ADDR_W       – address bus width (default 32)
//   SLAVE_BASE   – flat packed [8*32-1:0]: slave s base at bits [s*32+:32]
//   SLAVE_MASK   – flat packed [8*32-1:0]: slave s mask at bits [s*32+:32]
//     match iff (addr & SLAVE_MASK[s*32+:32]) == SLAVE_BASE[s*32+:32]
//
// Flat port buses (all [NM*W-1:0] or [NS*W-1:0]):
//   master index m occupies bits [m*W+:W]
//   slave  index s occupies bits [s*W+:W]
//
// Icarus 12 compatibility:
//   - No packed bit-selects inside always_comb/always_ff
//   - All dynamic indexing done via assign or unpacked-array access
//   - Non-automatic functions for address decode and round-robin
//   - Module-scope integers for always_comb loops

module axi4_crossbar_param #(
    parameter int NM     = 3,
    parameter int NS     = 3,
    parameter int DATA_W = 32,
    parameter int ADDR_W = 32,
    parameter [8*32-1:0] SLAVE_BASE = '0,
    parameter [8*32-1:0] SLAVE_MASK = '0
)(
    input  logic clk,
    input  logic rst_n,

    // ── Master AW ────────────────────────────────────────────────────────────
    input  logic [NM-1:0]           m_awvalid,
    input  logic [NM*ADDR_W-1:0]    m_awaddr,
    output logic [NM-1:0]           m_awready,
    // ── Master W ─────────────────────────────────────────────────────────────
    input  logic [NM-1:0]           m_wvalid,
    input  logic [NM*DATA_W-1:0]    m_wdata,
    input  logic [NM*4-1:0]         m_wstrb,
    output logic [NM-1:0]           m_wready,
    // ── Master B ─────────────────────────────────────────────────────────────
    output logic [NM-1:0]           m_bvalid,
    output logic [NM*2-1:0]         m_bresp,
    input  logic [NM-1:0]           m_bready,
    // ── Master AR ────────────────────────────────────────────────────────────
    input  logic [NM-1:0]           m_arvalid,
    input  logic [NM*ADDR_W-1:0]    m_araddr,
    output logic [NM-1:0]           m_arready,
    // ── Master R ─────────────────────────────────────────────────────────────
    output logic [NM-1:0]           m_rvalid,
    output logic [NM*DATA_W-1:0]    m_rdata,
    output logic [NM*2-1:0]         m_rresp,
    input  logic [NM-1:0]           m_rready,

    // ── Slave AW ─────────────────────────────────────────────────────────────
    output logic [NS-1:0]           s_awvalid,
    output logic [NS*ADDR_W-1:0]    s_awaddr,
    input  logic [NS-1:0]           s_awready,
    // ── Slave W ──────────────────────────────────────────────────────────────
    output logic [NS-1:0]           s_wvalid,
    output logic [NS*DATA_W-1:0]    s_wdata,
    output logic [NS*4-1:0]         s_wstrb,
    input  logic [NS-1:0]           s_wready,
    // ── Slave B ──────────────────────────────────────────────────────────────
    input  logic [NS-1:0]           s_bvalid,
    input  logic [NS*2-1:0]         s_bresp,
    output logic [NS-1:0]           s_bready,
    // ── Slave AR ─────────────────────────────────────────────────────────────
    output logic [NS-1:0]           s_arvalid,
    output logic [NS*ADDR_W-1:0]    s_araddr,
    input  logic [NS-1:0]           s_arready,
    // ── Slave R ──────────────────────────────────────────────────────────────
    input  logic [NS-1:0]           s_rvalid,
    input  logic [NS*DATA_W-1:0]    s_rdata,
    input  logic [NS*2-1:0]         s_rresp,
    output logic [NS-1:0]           s_rready
);

// ──────────────────────────────────────────────────────────────────────────────
// 1. Unpack flat port buses into unpacked arrays (generate + assign)
// ──────────────────────────────────────────────────────────────────────────────
logic [ADDR_W-1:0] m_awaddr_a [0:NM-1];
logic              m_awvalid_a[0:NM-1];
logic [DATA_W-1:0] m_wdata_a  [0:NM-1];
logic [3:0]        m_wstrb_a  [0:NM-1];
logic              m_wvalid_a [0:NM-1];
logic              m_bready_a [0:NM-1];
logic [ADDR_W-1:0] m_araddr_a [0:NM-1];
logic              m_arvalid_a[0:NM-1];
logic              m_rready_a [0:NM-1];

logic              s_awready_a[0:NS-1];
logic              s_wready_a [0:NS-1];
logic [1:0]        s_bresp_a  [0:NS-1];
logic              s_bvalid_a [0:NS-1];
logic              s_arready_a[0:NS-1];
logic [DATA_W-1:0] s_rdata_a  [0:NS-1];
logic [1:0]        s_rresp_a  [0:NS-1];
logic              s_rvalid_a [0:NS-1];

// Outputs (arrays, packed back to flat ports at bottom)
logic [ADDR_W-1:0] s_awaddr_a [0:NS-1];
logic              s_awvalid_a[0:NS-1];
logic [DATA_W-1:0] s_wdata_a  [0:NS-1];
logic [3:0]        s_wstrb_a  [0:NS-1];
logic              s_wvalid_a [0:NS-1];
logic              s_bready_a [0:NS-1];
logic [ADDR_W-1:0] s_araddr_a [0:NS-1];
logic              s_arvalid_a[0:NS-1];
logic              s_rready_a [0:NS-1];

logic              m_awready_a[0:NM-1];
logic              m_wready_a [0:NM-1];
logic [1:0]        m_bresp_a  [0:NM-1];
logic              m_bvalid_a [0:NM-1];
logic              m_arready_a[0:NM-1];
logic [DATA_W-1:0] m_rdata_a  [0:NM-1];
logic [1:0]        m_rresp_a  [0:NM-1];
logic              m_rvalid_a [0:NM-1];

genvar gm, gs;

generate
    for (gm = 0; gm < NM; gm++) begin : gen_m_unpack
        assign m_awaddr_a [gm] = m_awaddr [gm*ADDR_W+:ADDR_W];
        assign m_awvalid_a[gm] = m_awvalid[gm];
        assign m_wdata_a  [gm] = m_wdata  [gm*DATA_W+:DATA_W];
        assign m_wstrb_a  [gm] = m_wstrb  [gm*4+:4];
        assign m_wvalid_a [gm] = m_wvalid [gm];
        assign m_bready_a [gm] = m_bready [gm];
        assign m_araddr_a [gm] = m_araddr [gm*ADDR_W+:ADDR_W];
        assign m_arvalid_a[gm] = m_arvalid[gm];
        assign m_rready_a [gm] = m_rready [gm];
        // pack outputs back
        assign m_awready[gm]          = m_awready_a[gm];
        assign m_wready [gm]          = m_wready_a [gm];
        assign m_bvalid [gm]          = m_bvalid_a [gm];
        assign m_bresp  [gm*2+:2]     = m_bresp_a  [gm];
        assign m_arready[gm]          = m_arready_a[gm];
        assign m_rvalid [gm]          = m_rvalid_a [gm];
        assign m_rdata  [gm*DATA_W+:DATA_W] = m_rdata_a[gm];
        assign m_rresp  [gm*2+:2]     = m_rresp_a  [gm];
    end
    for (gs = 0; gs < NS; gs++) begin : gen_s_unpack
        assign s_awready_a[gs] = s_awready[gs];
        assign s_wready_a [gs] = s_wready [gs];
        assign s_bresp_a  [gs] = s_bresp  [gs*2+:2];
        assign s_bvalid_a [gs] = s_bvalid [gs];
        assign s_arready_a[gs] = s_arready[gs];
        assign s_rdata_a  [gs] = s_rdata  [gs*DATA_W+:DATA_W];
        assign s_rresp_a  [gs] = s_rresp  [gs*2+:2];
        assign s_rvalid_a [gs] = s_rvalid [gs];
        // pack outputs back
        assign s_awvalid[gs]           = s_awvalid_a[gs];
        assign s_awaddr [gs*ADDR_W+:ADDR_W] = s_awaddr_a[gs];
        assign s_wvalid [gs]           = s_wvalid_a [gs];
        assign s_wdata  [gs*DATA_W+:DATA_W] = s_wdata_a[gs];
        assign s_wstrb  [gs*4+:4]      = s_wstrb_a  [gs];
        assign s_bready [gs]           = s_bready_a [gs];
        assign s_arvalid[gs]           = s_arvalid_a[gs];
        assign s_araddr [gs*ADDR_W+:ADDR_W] = s_araddr_a[gs];
        assign s_rready [gs]           = s_rready_a [gs];
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 2. Unpack slave address map from flat parameters
// ──────────────────────────────────────────────────────────────────────────────
logic [31:0] slave_base_a[0:7];
logic [31:0] slave_mask_a[0:7];

generate
    for (gs = 0; gs < 8; gs++) begin : gen_map_unpack
        assign slave_base_a[gs] = SLAVE_BASE[gs*32+:32];
        assign slave_mask_a[gs] = SLAVE_MASK[gs*32+:32];
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 3. Address decode — non-automatic function (integer loop vars, bit-selects OK)
// ──────────────────────────────────────────────────────────────────────────────
function [3:0] addr_decode;
    input [ADDR_W-1:0] addr;
    integer s;
    begin
        addr_decode = 4'(NS);  // default: unmapped
        for (s = NS-1; s >= 0; s = s - 1) begin
            if ((addr & slave_mask_a[s]) == slave_base_a[s])
                addr_decode = 4'(s);
        end
    end
endfunction

// ──────────────────────────────────────────────────────────────────────────────
// 4. Round-robin grant — non-automatic function
// ──────────────────────────────────────────────────────────────────────────────
// Returns binary master index, or NM if no request.
// Iterates priority 0..NM-1 (rotated from last+1), last-write-wins → highest wins.
function [3:0] rr_grant;
    input [NM-1:0] req;
    input [3:0]    last;   // last-granted master index
    integer i;
    integer cand;
    begin
        rr_grant = 4'(NM);  // default: no grant
        for (i = NM-1; i >= 0; i = i - 1) begin
            cand = (last + 1 + i) % NM;
            if (req[cand])
                rr_grant = 4'(cand);
        end
    end
endfunction

// ──────────────────────────────────────────────────────────────────────────────
// 5. Address decode wires per master
// ──────────────────────────────────────────────────────────────────────────────
logic [3:0] m_awdec[0:NM-1];  // slave index for AW (NS = unmapped)
logic [3:0] m_ardec[0:NM-1];  // slave index for AR

generate
    for (gm = 0; gm < NM; gm++) begin : gen_decode
        assign m_awdec[gm] = addr_decode(m_awaddr_a[gm]);
        assign m_ardec[gm] = addr_decode(m_araddr_a[gm]);
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 6. Per-slave request vectors (packed, for RR function input)
// ──────────────────────────────────────────────────────────────────────────────
logic [NM-1:0] wr_req_pvec[0:NS-1];  // bit m set = master m wants write to slave s
logic [NM-1:0] rd_req_pvec[0:NS-1];

generate
    for (gs = 0; gs < NS; gs++) begin : gen_req
        for (gm = 0; gm < NM; gm++) begin : gen_req_m
            assign wr_req_pvec[gs][gm] = m_awvalid_a[gm] && (m_awdec[gm] == 4'(gs));
            assign rd_req_pvec[gs][gm] = m_arvalid_a[gm] && (m_ardec[gm] == 4'(gs));
        end
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 7. Combinational next-grant wires (called from assign, no always restriction)
// ──────────────────────────────────────────────────────────────────────────────
logic [3:0] wr_grant_comb[0:NS-1];
logic [3:0] rd_grant_comb[0:NS-1];
logic [3:0] wr_last [0:NS-1];
logic [3:0] rd_last [0:NS-1];

generate
    for (gs = 0; gs < NS; gs++) begin : gen_grant_comb
        assign wr_grant_comb[gs] = rr_grant(wr_req_pvec[gs], wr_last[gs]);
        assign rd_grant_comb[gs] = rr_grant(rd_req_pvec[gs], rd_last[gs]);
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 8. Per-slave arbiters (generate + always_ff)
// ──────────────────────────────────────────────────────────────────────────────
logic [3:0] wr_grant[0:NS-1];  // binary master index holding write grant
logic [3:0] rd_grant[0:NS-1];  // binary master index holding read grant
logic       wr_busy [0:NS-1];
logic       rd_busy [0:NS-1];

generate
    for (gs = 0; gs < NS; gs++) begin : gen_wr_arb
        always_ff @(posedge clk or negedge rst_n) begin
            if (!rst_n) begin
                wr_busy [gs] <= 1'b0;
                wr_grant[gs] <= 4'd0;
                wr_last [gs] <= 4'(NM-1);
            end else if (!wr_busy[gs]) begin
                if (|wr_req_pvec[gs]) begin
                    wr_grant[gs] <= wr_grant_comb[gs];
                    wr_last [gs] <= wr_grant_comb[gs];
                    wr_busy [gs] <= 1'b1;
                end
            end else begin
                if (s_bvalid_a[gs] && m_bready_a[wr_grant[gs]])
                    wr_busy[gs] <= 1'b0;
            end
        end
    end
    for (gs = 0; gs < NS; gs++) begin : gen_rd_arb
        always_ff @(posedge clk or negedge rst_n) begin
            if (!rst_n) begin
                rd_busy [gs] <= 1'b0;
                rd_grant[gs] <= 4'd0;
                rd_last [gs] <= 4'(NM-1);
            end else if (!rd_busy[gs]) begin
                if (|rd_req_pvec[gs]) begin
                    rd_grant[gs] <= rd_grant_comb[gs];
                    rd_last [gs] <= rd_grant_comb[gs];
                    rd_busy [gs] <= 1'b1;
                end
            end else begin
                if (s_rvalid_a[gs] && m_rready_a[rd_grant[gs]])
                    rd_busy[gs] <= 1'b0;
            end
        end
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 9. SLVERR FSM — per master (unmapped address → immediate SLVERR response)
// ──────────────────────────────────────────────────────────────────────────────
logic slverr_wr_busy[0:NM-1];  // sent B-channel SLVERR pending
logic slverr_rd_busy[0:NM-1];  // sent R-channel SLVERR pending
logic slverr_wr_w   [0:NM-1];  // waiting for W before sending B

generate
    for (gm = 0; gm < NM; gm++) begin : gen_slverr
        always_ff @(posedge clk or negedge rst_n) begin
            if (!rst_n) begin
                slverr_wr_busy[gm] <= 1'b0;
                slverr_wr_w   [gm] <= 1'b0;
                slverr_rd_busy[gm] <= 1'b0;
            end else begin
                // Write: AW unmapped
                if (!slverr_wr_busy[gm] && !slverr_wr_w[gm]) begin
                    if (m_awvalid_a[gm] && (m_awdec[gm] == 4'(NS))) begin
                        if (m_wvalid_a[gm])
                            slverr_wr_busy[gm] <= 1'b1;  // AW+W same cycle
                        else
                            slverr_wr_w[gm] <= 1'b1;    // wait for W
                    end
                end else if (slverr_wr_w[gm]) begin
                    if (m_wvalid_a[gm]) begin
                        slverr_wr_w   [gm] <= 1'b0;
                        slverr_wr_busy[gm] <= 1'b1;
                    end
                end else begin  // slverr_wr_busy
                    if (m_bready_a[gm]) slverr_wr_busy[gm] <= 1'b0;
                end
                // Read: AR unmapped
                if (!slverr_rd_busy[gm]) begin
                    if (m_arvalid_a[gm] && (m_ardec[gm] == 4'(NS)))
                        slverr_rd_busy[gm] <= 1'b1;
                end else begin
                    if (m_rready_a[gm]) slverr_rd_busy[gm] <= 1'b0;
                end
            end
        end
    end
endgenerate

// ──────────────────────────────────────────────────────────────────────────────
// 10. Write channel mux  (slave side driven from granted master)
// ──────────────────────────────────────────────────────────────────────────────
integer mux_s;
always_comb begin
    for (mux_s = 0; mux_s < NS; mux_s = mux_s + 1) begin
        if (wr_busy[mux_s]) begin
            s_awaddr_a [mux_s] = m_awaddr_a [wr_grant[mux_s]];
            s_awvalid_a[mux_s] = m_awvalid_a[wr_grant[mux_s]];
            s_wdata_a  [mux_s] = m_wdata_a  [wr_grant[mux_s]];
            s_wstrb_a  [mux_s] = m_wstrb_a  [wr_grant[mux_s]];
            s_wvalid_a [mux_s] = m_wvalid_a [wr_grant[mux_s]];
            s_bready_a [mux_s] = m_bready_a [wr_grant[mux_s]];
        end else begin
            s_awaddr_a [mux_s] = '0;
            s_awvalid_a[mux_s] = 1'b0;
            s_wdata_a  [mux_s] = '0;
            s_wstrb_a  [mux_s] = 4'd0;
            s_wvalid_a [mux_s] = 1'b0;
            s_bready_a [mux_s] = 1'b0;
        end
    end
end

// ──────────────────────────────────────────────────────────────────────────────
// 11. Read channel mux  (slave side)
// ──────────────────────────────────────────────────────────────────────────────
integer mux_rs;
always_comb begin
    for (mux_rs = 0; mux_rs < NS; mux_rs = mux_rs + 1) begin
        if (rd_busy[mux_rs]) begin
            s_araddr_a [mux_rs] = m_araddr_a [rd_grant[mux_rs]];
            s_arvalid_a[mux_rs] = m_arvalid_a[rd_grant[mux_rs]];
            s_rready_a [mux_rs] = m_rready_a [rd_grant[mux_rs]];
        end else begin
            s_araddr_a [mux_rs] = '0;
            s_arvalid_a[mux_rs] = 1'b0;
            s_rready_a [mux_rs] = 1'b0;
        end
    end
end

// ──────────────────────────────────────────────────────────────────────────────
// 12. Master-side write response mux + SLVERR injection
// ──────────────────────────────────────────────────────────────────────────────
integer mux_m;
always_comb begin
    for (mux_m = 0; mux_m < NM; mux_m = mux_m + 1) begin
        // defaults
        m_awready_a[mux_m] = 1'b0;
        m_wready_a [mux_m] = 1'b0;
        m_bvalid_a [mux_m] = 1'b0;
        m_bresp_a  [mux_m] = 2'd0;
        // SLVERR override (unmapped write)
        if (slverr_wr_busy[mux_m]) begin
            m_awready_a[mux_m] = 1'b0;  // already accepted
            m_wready_a [mux_m] = 1'b0;
            m_bvalid_a [mux_m] = 1'b1;
            m_bresp_a  [mux_m] = 2'b10;  // SLVERR
        end else if (slverr_wr_w[mux_m]) begin
            // accepted AW, now waiting for W
            m_awready_a[mux_m] = 1'b0;
            m_wready_a [mux_m] = 1'b1;
            m_bvalid_a [mux_m] = 1'b0;
        end else if (m_awvalid_a[mux_m] && (m_awdec[mux_m] == 4'(NS))) begin
            // unmapped, take AW immediately (and W if available)
            m_awready_a[mux_m] = 1'b1;
            m_wready_a [mux_m] = m_wvalid_a[mux_m];
            m_bvalid_a [mux_m] = 1'b0;
        end
    end
    // Normal (mapped) slave responses — scan all slaves for each master
    for (mux_m = 0; mux_m < NM; mux_m = mux_m + 1) begin
        if (!slverr_wr_busy[mux_m] && !slverr_wr_w[mux_m] &&
            !(m_awvalid_a[mux_m] && (m_awdec[mux_m] == 4'(NS)))) begin
            for (mux_s = 0; mux_s < NS; mux_s = mux_s + 1) begin
                if (wr_busy[mux_s] && (wr_grant[mux_s] == 4'(mux_m))) begin
                    m_awready_a[mux_m] = s_awready_a[mux_s];
                    m_wready_a [mux_m] = s_wready_a [mux_s];
                    m_bvalid_a [mux_m] = s_bvalid_a [mux_s];
                    m_bresp_a  [mux_m] = s_bresp_a  [mux_s];
                end
            end
        end
    end
end

// ──────────────────────────────────────────────────────────────────────────────
// 13. Master-side read response mux + SLVERR injection
// ──────────────────────────────────────────────────────────────────────────────
integer mux_rm;
always_comb begin
    for (mux_rm = 0; mux_rm < NM; mux_rm = mux_rm + 1) begin
        m_arready_a[mux_rm] = 1'b0;
        m_rvalid_a [mux_rm] = 1'b0;
        m_rdata_a  [mux_rm] = '0;
        m_rresp_a  [mux_rm] = 2'd0;
        // SLVERR
        if (slverr_rd_busy[mux_rm]) begin
            m_arready_a[mux_rm] = 1'b0;
            m_rvalid_a [mux_rm] = 1'b1;
            m_rdata_a  [mux_rm] = '0;
            m_rresp_a  [mux_rm] = 2'b10;
        end else if (m_arvalid_a[mux_rm] && (m_ardec[mux_rm] == 4'(NS))) begin
            m_arready_a[mux_rm] = 1'b1;  // accept immediately
            m_rvalid_a [mux_rm] = 1'b0;
        end
    end
    // Normal slave responses
    for (mux_rm = 0; mux_rm < NM; mux_rm = mux_rm + 1) begin
        if (!slverr_rd_busy[mux_rm] &&
            !(m_arvalid_a[mux_rm] && (m_ardec[mux_rm] == 4'(NS)))) begin
            for (mux_rs = 0; mux_rs < NS; mux_rs = mux_rs + 1) begin
                if (rd_busy[mux_rs] && (rd_grant[mux_rs] == 4'(mux_rm))) begin
                    m_arready_a[mux_rm] = s_arready_a[mux_rs];
                    m_rvalid_a [mux_rm] = s_rvalid_a [mux_rs];
                    m_rdata_a  [mux_rm] = s_rdata_a  [mux_rs];
                    m_rresp_a  [mux_rm] = s_rresp_a  [mux_rs];
                end
            end
        end
    end
end

endmodule
