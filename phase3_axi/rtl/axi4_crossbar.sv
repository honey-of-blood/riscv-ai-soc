`timescale 1ns/1ps
// AXI4-Lite 3-master × 3-slave crossbar with round-robin arbitration
// Address map (decoded on addr[31:16]):
//   Slave 0 – 0x0000_xxxx : SRAM
//   Slave 1 – 0x1000_xxxx : APB bridge
//   Slave 2 – 0x5000_xxxx : AI accelerator MMIO

module axi4_crossbar (
    input  logic clk,
    input  logic rst_n,

    // ── Master 0 (CPU) ──────────────────────────────────────────────────────
    input  logic [31:0] m0_awaddr,
    input  logic        m0_awvalid,
    output logic        m0_awready,
    input  logic [31:0] m0_wdata,
    input  logic  [3:0] m0_wstrb,
    input  logic        m0_wvalid,
    output logic        m0_wready,
    output logic  [1:0] m0_bresp,
    output logic        m0_bvalid,
    input  logic        m0_bready,
    input  logic [31:0] m0_araddr,
    input  logic        m0_arvalid,
    output logic        m0_arready,
    output logic [31:0] m0_rdata,
    output logic  [1:0] m0_rresp,
    output logic        m0_rvalid,
    input  logic        m0_rready,

    // ── Master 1 (DMA / debug placeholder) ─────────────────────────────────
    input  logic [31:0] m1_awaddr,
    input  logic        m1_awvalid,
    output logic        m1_awready,
    input  logic [31:0] m1_wdata,
    input  logic  [3:0] m1_wstrb,
    input  logic        m1_wvalid,
    output logic        m1_wready,
    output logic  [1:0] m1_bresp,
    output logic        m1_bvalid,
    input  logic        m1_bready,
    input  logic [31:0] m1_araddr,
    input  logic        m1_arvalid,
    output logic        m1_arready,
    output logic [31:0] m1_rdata,
    output logic  [1:0] m1_rresp,
    output logic        m1_rvalid,
    input  logic        m1_rready,

    // ── Master 2 (debug / instrumentation placeholder) ─────────────────────
    input  logic [31:0] m2_awaddr,
    input  logic        m2_awvalid,
    output logic        m2_awready,
    input  logic [31:0] m2_wdata,
    input  logic  [3:0] m2_wstrb,
    input  logic        m2_wvalid,
    output logic        m2_wready,
    output logic  [1:0] m2_bresp,
    output logic        m2_bvalid,
    input  logic        m2_bready,
    input  logic [31:0] m2_araddr,
    input  logic        m2_arvalid,
    output logic        m2_arready,
    output logic [31:0] m2_rdata,
    output logic  [1:0] m2_rresp,
    output logic        m2_rvalid,
    input  logic        m2_rready,

    // ── Slave 0 (SRAM) ──────────────────────────────────────────────────────
    output logic [31:0] s0_awaddr,
    output logic        s0_awvalid,
    input  logic        s0_awready,
    output logic [31:0] s0_wdata,
    output logic  [3:0] s0_wstrb,
    output logic        s0_wvalid,
    input  logic        s0_wready,
    input  logic  [1:0] s0_bresp,
    input  logic        s0_bvalid,
    output logic        s0_bready,
    output logic [31:0] s0_araddr,
    output logic        s0_arvalid,
    input  logic        s0_arready,
    input  logic [31:0] s0_rdata,
    input  logic  [1:0] s0_rresp,
    input  logic        s0_rvalid,
    output logic        s0_rready,

    // ── Slave 1 (APB bridge) ────────────────────────────────────────────────
    output logic [31:0] s1_awaddr,
    output logic        s1_awvalid,
    input  logic        s1_awready,
    output logic [31:0] s1_wdata,
    output logic  [3:0] s1_wstrb,
    output logic        s1_wvalid,
    input  logic        s1_wready,
    input  logic  [1:0] s1_bresp,
    input  logic        s1_bvalid,
    output logic        s1_bready,
    output logic [31:0] s1_araddr,
    output logic        s1_arvalid,
    input  logic        s1_arready,
    input  logic [31:0] s1_rdata,
    input  logic  [1:0] s1_rresp,
    input  logic        s1_rvalid,
    output logic        s1_rready,

    // ── Slave 2 (AI accelerator) ────────────────────────────────────────────
    output logic [31:0] s2_awaddr,
    output logic        s2_awvalid,
    input  logic        s2_awready,
    output logic [31:0] s2_wdata,
    output logic  [3:0] s2_wstrb,
    output logic        s2_wvalid,
    input  logic        s2_wready,
    input  logic  [1:0] s2_bresp,
    input  logic        s2_bvalid,
    output logic        s2_bready,
    output logic [31:0] s2_araddr,
    output logic        s2_arvalid,
    input  logic        s2_arready,
    input  logic [31:0] s2_rdata,
    input  logic  [1:0] s2_rresp,
    input  logic        s2_rvalid,
    output logic        s2_rready
);

// ─── 1. Pack ports into arrays ────────────────────────────────────────────────
logic [31:0] m_awaddr  [3];
logic        m_awvalid [3];
logic        m_awready [3];
logic [31:0] m_wdata   [3];
logic  [3:0] m_wstrb   [3];
logic        m_wvalid  [3];
logic        m_wready  [3];
logic  [1:0] m_bresp   [3];
logic        m_bvalid  [3];
logic        m_bready  [3];
logic [31:0] m_araddr  [3];
logic        m_arvalid [3];
logic        m_arready [3];
logic [31:0] m_rdata   [3];
logic  [1:0] m_rresp   [3];
logic        m_rvalid  [3];
logic        m_rready  [3];

assign m_awaddr[0]=m0_awaddr; assign m_awaddr[1]=m1_awaddr; assign m_awaddr[2]=m2_awaddr;
assign m_awvalid[0]=m0_awvalid; assign m_awvalid[1]=m1_awvalid; assign m_awvalid[2]=m2_awvalid;
assign m_wdata[0]=m0_wdata; assign m_wdata[1]=m1_wdata; assign m_wdata[2]=m2_wdata;
assign m_wstrb[0]=m0_wstrb; assign m_wstrb[1]=m1_wstrb; assign m_wstrb[2]=m2_wstrb;
assign m_wvalid[0]=m0_wvalid; assign m_wvalid[1]=m1_wvalid; assign m_wvalid[2]=m2_wvalid;
assign m_bready[0]=m0_bready; assign m_bready[1]=m1_bready; assign m_bready[2]=m2_bready;
assign m_araddr[0]=m0_araddr; assign m_araddr[1]=m1_araddr; assign m_araddr[2]=m2_araddr;
assign m_arvalid[0]=m0_arvalid; assign m_arvalid[1]=m1_arvalid; assign m_arvalid[2]=m2_arvalid;
assign m_rready[0]=m0_rready; assign m_rready[1]=m1_rready; assign m_rready[2]=m2_rready;

assign m0_awready=m_awready[0]; assign m1_awready=m_awready[1]; assign m2_awready=m_awready[2];
assign m0_wready=m_wready[0];   assign m1_wready=m_wready[1];   assign m2_wready=m_wready[2];
assign m0_bresp=m_bresp[0];     assign m1_bresp=m_bresp[1];     assign m2_bresp=m_bresp[2];
assign m0_bvalid=m_bvalid[0];   assign m1_bvalid=m_bvalid[1];   assign m2_bvalid=m_bvalid[2];
assign m0_arready=m_arready[0]; assign m1_arready=m_arready[1]; assign m2_arready=m_arready[2];
assign m0_rdata=m_rdata[0];     assign m1_rdata=m_rdata[1];     assign m2_rdata=m_rdata[2];
assign m0_rresp=m_rresp[0];     assign m1_rresp=m_rresp[1];     assign m2_rresp=m_rresp[2];
assign m0_rvalid=m_rvalid[0];   assign m1_rvalid=m_rvalid[1];   assign m2_rvalid=m_rvalid[2];

logic [31:0] s_awaddr  [3];
logic        s_awvalid [3];
logic        s_awready [3];
logic [31:0] s_wdata   [3];
logic  [3:0] s_wstrb   [3];
logic        s_wvalid  [3];
logic        s_wready  [3];
logic  [1:0] s_bresp   [3];
logic        s_bvalid  [3];
logic        s_bready  [3];
logic [31:0] s_araddr  [3];
logic        s_arvalid [3];
logic        s_arready [3];
logic [31:0] s_rdata   [3];
logic  [1:0] s_rresp   [3];
logic        s_rvalid  [3];
logic        s_rready  [3];

assign s0_awaddr=s_awaddr[0]; assign s1_awaddr=s_awaddr[1]; assign s2_awaddr=s_awaddr[2];
assign s0_awvalid=s_awvalid[0]; assign s1_awvalid=s_awvalid[1]; assign s2_awvalid=s_awvalid[2];
assign s0_wdata=s_wdata[0]; assign s1_wdata=s_wdata[1]; assign s2_wdata=s_wdata[2];
assign s0_wstrb=s_wstrb[0]; assign s1_wstrb=s_wstrb[1]; assign s2_wstrb=s_wstrb[2];
assign s0_wvalid=s_wvalid[0]; assign s1_wvalid=s_wvalid[1]; assign s2_wvalid=s_wvalid[2];
assign s0_bready=s_bready[0]; assign s1_bready=s_bready[1]; assign s2_bready=s_bready[2];
assign s0_araddr=s_araddr[0]; assign s1_araddr=s_araddr[1]; assign s2_araddr=s_araddr[2];
assign s0_arvalid=s_arvalid[0]; assign s1_arvalid=s_arvalid[1]; assign s2_arvalid=s_arvalid[2];
assign s0_rready=s_rready[0]; assign s1_rready=s_rready[1]; assign s2_rready=s_rready[2];

assign s_awready[0]=s0_awready; assign s_awready[1]=s1_awready; assign s_awready[2]=s2_awready;
assign s_wready[0]=s0_wready; assign s_wready[1]=s1_wready; assign s_wready[2]=s2_wready;
assign s_bresp[0]=s0_bresp; assign s_bresp[1]=s1_bresp; assign s_bresp[2]=s2_bresp;
assign s_bvalid[0]=s0_bvalid; assign s_bvalid[1]=s1_bvalid; assign s_bvalid[2]=s2_bvalid;
assign s_arready[0]=s0_arready; assign s_arready[1]=s1_arready; assign s_arready[2]=s2_arready;
assign s_rdata[0]=s0_rdata; assign s_rdata[1]=s1_rdata; assign s_rdata[2]=s2_rdata;
assign s_rresp[0]=s0_rresp; assign s_rresp[1]=s1_rresp; assign s_rresp[2]=s2_rresp;
assign s_rvalid[0]=s0_rvalid; assign s_rvalid[1]=s1_rvalid; assign s_rvalid[2]=s2_rvalid;

// ─── 2. Address decode ────────────────────────────────────────────────────────
// 2'd3 = unmapped (no slave responds)
logic [1:0] m_awdec [3];
logic [1:0] m_ardec [3];

assign m_awdec[0] = (m_awaddr[0][31:16]==16'h0000) ? 2'd0 :
                    (m_awaddr[0][31:16]==16'h1000) ? 2'd1 :
                    (m_awaddr[0][31:16]==16'h5000) ? 2'd2 : 2'd3;
assign m_awdec[1] = (m_awaddr[1][31:16]==16'h0000) ? 2'd0 :
                    (m_awaddr[1][31:16]==16'h1000) ? 2'd1 :
                    (m_awaddr[1][31:16]==16'h5000) ? 2'd2 : 2'd3;
assign m_awdec[2] = (m_awaddr[2][31:16]==16'h0000) ? 2'd0 :
                    (m_awaddr[2][31:16]==16'h1000) ? 2'd1 :
                    (m_awaddr[2][31:16]==16'h5000) ? 2'd2 : 2'd3;

assign m_ardec[0] = (m_araddr[0][31:16]==16'h0000) ? 2'd0 :
                    (m_araddr[0][31:16]==16'h1000) ? 2'd1 :
                    (m_araddr[0][31:16]==16'h5000) ? 2'd2 : 2'd3;
assign m_ardec[1] = (m_araddr[1][31:16]==16'h0000) ? 2'd0 :
                    (m_araddr[1][31:16]==16'h1000) ? 2'd1 :
                    (m_araddr[1][31:16]==16'h5000) ? 2'd2 : 2'd3;
assign m_ardec[2] = (m_araddr[2][31:16]==16'h0000) ? 2'd0 :
                    (m_araddr[2][31:16]==16'h1000) ? 2'd1 :
                    (m_araddr[2][31:16]==16'h5000) ? 2'd2 : 2'd3;

// ─── 3. Per-slave write arbitration (round-robin) ────────────────────────────
// wr_grant[s]: which master (0-2) currently holds slave s's write channel
// wr_busy[s]:  write channel occupied
// wr_last[s]:  last-granted master for round-robin fairness
logic [1:0] wr_grant [3];
logic       wr_busy  [3];
logic [1:0] wr_last  [3];

// Slave 0 write arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_busy[0]  <= 1'b0;
        wr_grant[0] <= 2'd0;
        wr_last[0]  <= 2'd2;
    end else if (!wr_busy[0]) begin
        // Round-robin: start checking (wr_last+1)%3
        case (wr_last[0])
            2'd0: begin
                if      (m_awvalid[1] && m_awdec[1]==2'd0) begin wr_grant[0]<=2'd1; wr_busy[0]<=1'b1; wr_last[0]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd0) begin wr_grant[0]<=2'd2; wr_busy[0]<=1'b1; wr_last[0]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd0) begin wr_grant[0]<=2'd0; wr_busy[0]<=1'b1; wr_last[0]<=2'd0; end
            end
            2'd1: begin
                if      (m_awvalid[2] && m_awdec[2]==2'd0) begin wr_grant[0]<=2'd2; wr_busy[0]<=1'b1; wr_last[0]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd0) begin wr_grant[0]<=2'd0; wr_busy[0]<=1'b1; wr_last[0]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd0) begin wr_grant[0]<=2'd1; wr_busy[0]<=1'b1; wr_last[0]<=2'd1; end
            end
            default: begin // 2'd2
                if      (m_awvalid[0] && m_awdec[0]==2'd0) begin wr_grant[0]<=2'd0; wr_busy[0]<=1'b1; wr_last[0]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd0) begin wr_grant[0]<=2'd1; wr_busy[0]<=1'b1; wr_last[0]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd0) begin wr_grant[0]<=2'd2; wr_busy[0]<=1'b1; wr_last[0]<=2'd2; end
            end
        endcase
    end else begin
        if (s_bvalid[0] && m_bready[wr_grant[0]])
            wr_busy[0] <= 1'b0;
    end
end

// Slave 1 write arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_busy[1]  <= 1'b0;
        wr_grant[1] <= 2'd0;
        wr_last[1]  <= 2'd2;
    end else if (!wr_busy[1]) begin
        case (wr_last[1])
            2'd0: begin
                if      (m_awvalid[1] && m_awdec[1]==2'd1) begin wr_grant[1]<=2'd1; wr_busy[1]<=1'b1; wr_last[1]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd1) begin wr_grant[1]<=2'd2; wr_busy[1]<=1'b1; wr_last[1]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd1) begin wr_grant[1]<=2'd0; wr_busy[1]<=1'b1; wr_last[1]<=2'd0; end
            end
            2'd1: begin
                if      (m_awvalid[2] && m_awdec[2]==2'd1) begin wr_grant[1]<=2'd2; wr_busy[1]<=1'b1; wr_last[1]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd1) begin wr_grant[1]<=2'd0; wr_busy[1]<=1'b1; wr_last[1]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd1) begin wr_grant[1]<=2'd1; wr_busy[1]<=1'b1; wr_last[1]<=2'd1; end
            end
            default: begin
                if      (m_awvalid[0] && m_awdec[0]==2'd1) begin wr_grant[1]<=2'd0; wr_busy[1]<=1'b1; wr_last[1]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd1) begin wr_grant[1]<=2'd1; wr_busy[1]<=1'b1; wr_last[1]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd1) begin wr_grant[1]<=2'd2; wr_busy[1]<=1'b1; wr_last[1]<=2'd2; end
            end
        endcase
    end else begin
        if (s_bvalid[1] && m_bready[wr_grant[1]])
            wr_busy[1] <= 1'b0;
    end
end

// Slave 2 write arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        wr_busy[2]  <= 1'b0;
        wr_grant[2] <= 2'd0;
        wr_last[2]  <= 2'd2;
    end else if (!wr_busy[2]) begin
        case (wr_last[2])
            2'd0: begin
                if      (m_awvalid[1] && m_awdec[1]==2'd2) begin wr_grant[2]<=2'd1; wr_busy[2]<=1'b1; wr_last[2]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd2) begin wr_grant[2]<=2'd2; wr_busy[2]<=1'b1; wr_last[2]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd2) begin wr_grant[2]<=2'd0; wr_busy[2]<=1'b1; wr_last[2]<=2'd0; end
            end
            2'd1: begin
                if      (m_awvalid[2] && m_awdec[2]==2'd2) begin wr_grant[2]<=2'd2; wr_busy[2]<=1'b1; wr_last[2]<=2'd2; end
                else if (m_awvalid[0] && m_awdec[0]==2'd2) begin wr_grant[2]<=2'd0; wr_busy[2]<=1'b1; wr_last[2]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd2) begin wr_grant[2]<=2'd1; wr_busy[2]<=1'b1; wr_last[2]<=2'd1; end
            end
            default: begin
                if      (m_awvalid[0] && m_awdec[0]==2'd2) begin wr_grant[2]<=2'd0; wr_busy[2]<=1'b1; wr_last[2]<=2'd0; end
                else if (m_awvalid[1] && m_awdec[1]==2'd2) begin wr_grant[2]<=2'd1; wr_busy[2]<=1'b1; wr_last[2]<=2'd1; end
                else if (m_awvalid[2] && m_awdec[2]==2'd2) begin wr_grant[2]<=2'd2; wr_busy[2]<=1'b1; wr_last[2]<=2'd2; end
            end
        endcase
    end else begin
        if (s_bvalid[2] && m_bready[wr_grant[2]])
            wr_busy[2] <= 1'b0;
    end
end

// ─── 4. Per-slave read arbitration (round-robin) ─────────────────────────────
logic [1:0] rd_grant [3];
logic       rd_busy  [3];
logic [1:0] rd_last  [3];

// Slave 0 read arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rd_busy[0]  <= 1'b0;
        rd_grant[0] <= 2'd0;
        rd_last[0]  <= 2'd2;
    end else if (!rd_busy[0]) begin
        case (rd_last[0])
            2'd0: begin
                if      (m_arvalid[1] && m_ardec[1]==2'd0) begin rd_grant[0]<=2'd1; rd_busy[0]<=1'b1; rd_last[0]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd0) begin rd_grant[0]<=2'd2; rd_busy[0]<=1'b1; rd_last[0]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd0) begin rd_grant[0]<=2'd0; rd_busy[0]<=1'b1; rd_last[0]<=2'd0; end
            end
            2'd1: begin
                if      (m_arvalid[2] && m_ardec[2]==2'd0) begin rd_grant[0]<=2'd2; rd_busy[0]<=1'b1; rd_last[0]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd0) begin rd_grant[0]<=2'd0; rd_busy[0]<=1'b1; rd_last[0]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd0) begin rd_grant[0]<=2'd1; rd_busy[0]<=1'b1; rd_last[0]<=2'd1; end
            end
            default: begin
                if      (m_arvalid[0] && m_ardec[0]==2'd0) begin rd_grant[0]<=2'd0; rd_busy[0]<=1'b1; rd_last[0]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd0) begin rd_grant[0]<=2'd1; rd_busy[0]<=1'b1; rd_last[0]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd0) begin rd_grant[0]<=2'd2; rd_busy[0]<=1'b1; rd_last[0]<=2'd2; end
            end
        endcase
    end else begin
        if (s_rvalid[0] && m_rready[rd_grant[0]])
            rd_busy[0] <= 1'b0;
    end
end

// Slave 1 read arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rd_busy[1]  <= 1'b0;
        rd_grant[1] <= 2'd0;
        rd_last[1]  <= 2'd2;
    end else if (!rd_busy[1]) begin
        case (rd_last[1])
            2'd0: begin
                if      (m_arvalid[1] && m_ardec[1]==2'd1) begin rd_grant[1]<=2'd1; rd_busy[1]<=1'b1; rd_last[1]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd1) begin rd_grant[1]<=2'd2; rd_busy[1]<=1'b1; rd_last[1]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd1) begin rd_grant[1]<=2'd0; rd_busy[1]<=1'b1; rd_last[1]<=2'd0; end
            end
            2'd1: begin
                if      (m_arvalid[2] && m_ardec[2]==2'd1) begin rd_grant[1]<=2'd2; rd_busy[1]<=1'b1; rd_last[1]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd1) begin rd_grant[1]<=2'd0; rd_busy[1]<=1'b1; rd_last[1]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd1) begin rd_grant[1]<=2'd1; rd_busy[1]<=1'b1; rd_last[1]<=2'd1; end
            end
            default: begin
                if      (m_arvalid[0] && m_ardec[0]==2'd1) begin rd_grant[1]<=2'd0; rd_busy[1]<=1'b1; rd_last[1]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd1) begin rd_grant[1]<=2'd1; rd_busy[1]<=1'b1; rd_last[1]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd1) begin rd_grant[1]<=2'd2; rd_busy[1]<=1'b1; rd_last[1]<=2'd2; end
            end
        endcase
    end else begin
        if (s_rvalid[1] && m_rready[rd_grant[1]])
            rd_busy[1] <= 1'b0;
    end
end

// Slave 2 read arbiter
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rd_busy[2]  <= 1'b0;
        rd_grant[2] <= 2'd0;
        rd_last[2]  <= 2'd2;
    end else if (!rd_busy[2]) begin
        case (rd_last[2])
            2'd0: begin
                if      (m_arvalid[1] && m_ardec[1]==2'd2) begin rd_grant[2]<=2'd1; rd_busy[2]<=1'b1; rd_last[2]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd2) begin rd_grant[2]<=2'd2; rd_busy[2]<=1'b1; rd_last[2]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd2) begin rd_grant[2]<=2'd0; rd_busy[2]<=1'b1; rd_last[2]<=2'd0; end
            end
            2'd1: begin
                if      (m_arvalid[2] && m_ardec[2]==2'd2) begin rd_grant[2]<=2'd2; rd_busy[2]<=1'b1; rd_last[2]<=2'd2; end
                else if (m_arvalid[0] && m_ardec[0]==2'd2) begin rd_grant[2]<=2'd0; rd_busy[2]<=1'b1; rd_last[2]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd2) begin rd_grant[2]<=2'd1; rd_busy[2]<=1'b1; rd_last[2]<=2'd1; end
            end
            default: begin
                if      (m_arvalid[0] && m_ardec[0]==2'd2) begin rd_grant[2]<=2'd0; rd_busy[2]<=1'b1; rd_last[2]<=2'd0; end
                else if (m_arvalid[1] && m_ardec[1]==2'd2) begin rd_grant[2]<=2'd1; rd_busy[2]<=1'b1; rd_last[2]<=2'd1; end
                else if (m_arvalid[2] && m_ardec[2]==2'd2) begin rd_grant[2]<=2'd2; rd_busy[2]<=1'b1; rd_last[2]<=2'd2; end
            end
        endcase
    end else begin
        if (s_rvalid[2] && m_rready[rd_grant[2]])
            rd_busy[2] <= 1'b0;
    end
end

// ─── 5. Write channel mux ─────────────────────────────────────────────────────
// For each master m: check which slave (if any) has granted it write access
// For each slave s: route AW/W from granted master, B back to granted master

// Slave-side AW/W/B (driven by crossbar toward slaves)
integer s;
always_comb begin
    for (s = 0; s < 3; s++) begin
        if (wr_busy[s]) begin
            s_awaddr[s]  = m_awaddr[wr_grant[s]];
            s_awvalid[s] = m_awvalid[wr_grant[s]];
            s_wdata[s]   = m_wdata[wr_grant[s]];
            s_wstrb[s]   = m_wstrb[wr_grant[s]];
            s_wvalid[s]  = m_wvalid[wr_grant[s]];
            s_bready[s]  = m_bready[wr_grant[s]];
        end else begin
            s_awaddr[s]  = 32'd0;
            s_awvalid[s] = 1'b0;
            s_wdata[s]   = 32'd0;
            s_wstrb[s]   = 4'd0;
            s_wvalid[s]  = 1'b0;
            s_bready[s]  = 1'b0;
        end
    end
end

// Master-side AW/W/B — unrolled to avoid m[1:0] in always_comb (Icarus rule)
always_comb begin
    // Master 0
    if      (wr_busy[0] && wr_grant[0]==2'd0) begin m_awready[0]=s_awready[0]; m_wready[0]=s_wready[0]; m_bresp[0]=s_bresp[0]; m_bvalid[0]=s_bvalid[0]; end
    else if (wr_busy[1] && wr_grant[1]==2'd0) begin m_awready[0]=s_awready[1]; m_wready[0]=s_wready[1]; m_bresp[0]=s_bresp[1]; m_bvalid[0]=s_bvalid[1]; end
    else if (wr_busy[2] && wr_grant[2]==2'd0) begin m_awready[0]=s_awready[2]; m_wready[0]=s_wready[2]; m_bresp[0]=s_bresp[2]; m_bvalid[0]=s_bvalid[2]; end
    else begin m_awready[0]=1'b0; m_wready[0]=1'b0; m_bresp[0]=2'd0; m_bvalid[0]=1'b0; end
    // Master 1
    if      (wr_busy[0] && wr_grant[0]==2'd1) begin m_awready[1]=s_awready[0]; m_wready[1]=s_wready[0]; m_bresp[1]=s_bresp[0]; m_bvalid[1]=s_bvalid[0]; end
    else if (wr_busy[1] && wr_grant[1]==2'd1) begin m_awready[1]=s_awready[1]; m_wready[1]=s_wready[1]; m_bresp[1]=s_bresp[1]; m_bvalid[1]=s_bvalid[1]; end
    else if (wr_busy[2] && wr_grant[2]==2'd1) begin m_awready[1]=s_awready[2]; m_wready[1]=s_wready[2]; m_bresp[1]=s_bresp[2]; m_bvalid[1]=s_bvalid[2]; end
    else begin m_awready[1]=1'b0; m_wready[1]=1'b0; m_bresp[1]=2'd0; m_bvalid[1]=1'b0; end
    // Master 2
    if      (wr_busy[0] && wr_grant[0]==2'd2) begin m_awready[2]=s_awready[0]; m_wready[2]=s_wready[0]; m_bresp[2]=s_bresp[0]; m_bvalid[2]=s_bvalid[0]; end
    else if (wr_busy[1] && wr_grant[1]==2'd2) begin m_awready[2]=s_awready[1]; m_wready[2]=s_wready[1]; m_bresp[2]=s_bresp[1]; m_bvalid[2]=s_bvalid[1]; end
    else if (wr_busy[2] && wr_grant[2]==2'd2) begin m_awready[2]=s_awready[2]; m_wready[2]=s_wready[2]; m_bresp[2]=s_bresp[2]; m_bvalid[2]=s_bvalid[2]; end
    else begin m_awready[2]=1'b0; m_wready[2]=1'b0; m_bresp[2]=2'd0; m_bvalid[2]=1'b0; end
end

// ─── 6. Read channel mux ──────────────────────────────────────────────────────
// Slave-side AR/R
always_comb begin
    for (s = 0; s < 3; s++) begin
        if (rd_busy[s]) begin
            s_araddr[s]  = m_araddr[rd_grant[s]];
            s_arvalid[s] = m_arvalid[rd_grant[s]];
            s_rready[s]  = m_rready[rd_grant[s]];
        end else begin
            s_araddr[s]  = 32'd0;
            s_arvalid[s] = 1'b0;
            s_rready[s]  = 1'b0;
        end
    end
end

// Master-side AR/R — unrolled
always_comb begin
    // Master 0
    if      (rd_busy[0] && rd_grant[0]==2'd0) begin m_arready[0]=s_arready[0]; m_rdata[0]=s_rdata[0]; m_rresp[0]=s_rresp[0]; m_rvalid[0]=s_rvalid[0]; end
    else if (rd_busy[1] && rd_grant[1]==2'd0) begin m_arready[0]=s_arready[1]; m_rdata[0]=s_rdata[1]; m_rresp[0]=s_rresp[1]; m_rvalid[0]=s_rvalid[1]; end
    else if (rd_busy[2] && rd_grant[2]==2'd0) begin m_arready[0]=s_arready[2]; m_rdata[0]=s_rdata[2]; m_rresp[0]=s_rresp[2]; m_rvalid[0]=s_rvalid[2]; end
    else begin m_arready[0]=1'b0; m_rdata[0]=32'd0; m_rresp[0]=2'd0; m_rvalid[0]=1'b0; end
    // Master 1
    if      (rd_busy[0] && rd_grant[0]==2'd1) begin m_arready[1]=s_arready[0]; m_rdata[1]=s_rdata[0]; m_rresp[1]=s_rresp[0]; m_rvalid[1]=s_rvalid[0]; end
    else if (rd_busy[1] && rd_grant[1]==2'd1) begin m_arready[1]=s_arready[1]; m_rdata[1]=s_rdata[1]; m_rresp[1]=s_rresp[1]; m_rvalid[1]=s_rvalid[1]; end
    else if (rd_busy[2] && rd_grant[2]==2'd1) begin m_arready[1]=s_arready[2]; m_rdata[1]=s_rdata[2]; m_rresp[1]=s_rresp[2]; m_rvalid[1]=s_rvalid[2]; end
    else begin m_arready[1]=1'b0; m_rdata[1]=32'd0; m_rresp[1]=2'd0; m_rvalid[1]=1'b0; end
    // Master 2
    if      (rd_busy[0] && rd_grant[0]==2'd2) begin m_arready[2]=s_arready[0]; m_rdata[2]=s_rdata[0]; m_rresp[2]=s_rresp[0]; m_rvalid[2]=s_rvalid[0]; end
    else if (rd_busy[1] && rd_grant[1]==2'd2) begin m_arready[2]=s_arready[1]; m_rdata[2]=s_rdata[1]; m_rresp[2]=s_rresp[1]; m_rvalid[2]=s_rvalid[1]; end
    else if (rd_busy[2] && rd_grant[2]==2'd2) begin m_arready[2]=s_arready[2]; m_rdata[2]=s_rdata[2]; m_rresp[2]=s_rresp[2]; m_rvalid[2]=s_rvalid[2]; end
    else begin m_arready[2]=1'b0; m_rdata[2]=32'd0; m_rresp[2]=2'd0; m_rvalid[2]=1'b0; end
end

`ifdef FORMAL
// ─── Formal verification properties ──────────────────────────────────────────
// Run with: make -C phase3_axi/formal prove   (yosys-smtbmc + z3, depth 20)
//
// P1 decode_consistent: addr[31:16] unambiguously selects a slave
// P2 grant_stable:      wr_grant[s] doesn't change while wr_busy[s] is set
// P3 bvalid_routing:    BVALID/RVALID only reaches the master that was granted
// P4 awvalid_stable:    (assume) master holds AWVALID until AWREADY

initial assume(!rst_n);

reg f_past_valid;
initial f_past_valid = 0;
always @(posedge clk) f_past_valid <= 1;

// P4: AXI protocol assumption — master must not drop VALID before READY
always @(posedge clk) begin
    if (f_past_valid && $past(rst_n)) begin
        if ($past(m_awvalid[0]) && !$past(m_awready[0])) assume(m_awvalid[0]);
        if ($past(m_awvalid[1]) && !$past(m_awready[1])) assume(m_awvalid[1]);
        if ($past(m_awvalid[2]) && !$past(m_awready[2])) assume(m_awvalid[2]);
        if ($past(m_wvalid[0])  && !$past(m_wready[0]))  assume(m_wvalid[0]);
        if ($past(m_wvalid[1])  && !$past(m_wready[1]))  assume(m_wvalid[1]);
        if ($past(m_wvalid[2])  && !$past(m_wready[2]))  assume(m_wvalid[2]);
        if ($past(m_arvalid[0]) && !$past(m_arready[0])) assume(m_arvalid[0]);
        if ($past(m_arvalid[1]) && !$past(m_arready[1])) assume(m_arvalid[1]);
        if ($past(m_arvalid[2]) && !$past(m_arready[2])) assume(m_arvalid[2]);
    end
end

// P1: decode_consistent — address decode is deterministic function of addr[31:16]
always @(*) begin
    // Master 0
    if (m_awvalid[0]) begin
        if (m_awaddr[0][31:16] == 16'h0000) assert(m_awdec[0] == 2'd0);
        if (m_awaddr[0][31:16] == 16'h1000) assert(m_awdec[0] == 2'd1);
        if (m_awaddr[0][31:16] == 16'h5000) assert(m_awdec[0] == 2'd2);
    end
    if (m_arvalid[0]) begin
        if (m_araddr[0][31:16] == 16'h0000) assert(m_ardec[0] == 2'd0);
        if (m_araddr[0][31:16] == 16'h1000) assert(m_ardec[0] == 2'd1);
        if (m_araddr[0][31:16] == 16'h5000) assert(m_ardec[0] == 2'd2);
    end
    // Master 1
    if (m_awvalid[1]) begin
        if (m_awaddr[1][31:16] == 16'h0000) assert(m_awdec[1] == 2'd0);
        if (m_awaddr[1][31:16] == 16'h1000) assert(m_awdec[1] == 2'd1);
        if (m_awaddr[1][31:16] == 16'h5000) assert(m_awdec[1] == 2'd2);
    end
    if (m_arvalid[1]) begin
        if (m_araddr[1][31:16] == 16'h0000) assert(m_ardec[1] == 2'd0);
        if (m_araddr[1][31:16] == 16'h1000) assert(m_ardec[1] == 2'd1);
        if (m_araddr[1][31:16] == 16'h5000) assert(m_ardec[1] == 2'd2);
    end
    // Master 2
    if (m_awvalid[2]) begin
        if (m_awaddr[2][31:16] == 16'h0000) assert(m_awdec[2] == 2'd0);
        if (m_awaddr[2][31:16] == 16'h1000) assert(m_awdec[2] == 2'd1);
        if (m_awaddr[2][31:16] == 16'h5000) assert(m_awdec[2] == 2'd2);
    end
    if (m_arvalid[2]) begin
        if (m_araddr[2][31:16] == 16'h0000) assert(m_ardec[2] == 2'd0);
        if (m_araddr[2][31:16] == 16'h1000) assert(m_ardec[2] == 2'd1);
        if (m_araddr[2][31:16] == 16'h5000) assert(m_ardec[2] == 2'd2);
    end
end

// P2: grant_stable — wr_grant[s] holds constant while wr_busy[s] is asserted
always @(posedge clk) begin
    if (f_past_valid && $past(rst_n)) begin
        if ($past(wr_busy[0]) && wr_busy[0]) assert(wr_grant[0] == $past(wr_grant[0]));
        if ($past(wr_busy[1]) && wr_busy[1]) assert(wr_grant[1] == $past(wr_grant[1]));
        if ($past(wr_busy[2]) && wr_busy[2]) assert(wr_grant[2] == $past(wr_grant[2]));
        if ($past(rd_busy[0]) && rd_busy[0]) assert(rd_grant[0] == $past(rd_grant[0]));
        if ($past(rd_busy[1]) && rd_busy[1]) assert(rd_grant[1] == $past(rd_grant[1]));
        if ($past(rd_busy[2]) && rd_busy[2]) assert(rd_grant[2] == $past(rd_grant[2]));
    end
end

// P3: bvalid_routing — response channels route to the correct (granted) master
always @(*) begin
    if (rst_n) begin
        // Write response
        if (m_bvalid[0])
            assert((wr_busy[0] && wr_grant[0]==2'd0) ||
                   (wr_busy[1] && wr_grant[1]==2'd0) ||
                   (wr_busy[2] && wr_grant[2]==2'd0));
        if (m_bvalid[1])
            assert((wr_busy[0] && wr_grant[0]==2'd1) ||
                   (wr_busy[1] && wr_grant[1]==2'd1) ||
                   (wr_busy[2] && wr_grant[2]==2'd1));
        if (m_bvalid[2])
            assert((wr_busy[0] && wr_grant[0]==2'd2) ||
                   (wr_busy[1] && wr_grant[1]==2'd2) ||
                   (wr_busy[2] && wr_grant[2]==2'd2));
        // Read response
        if (m_rvalid[0])
            assert((rd_busy[0] && rd_grant[0]==2'd0) ||
                   (rd_busy[1] && rd_grant[1]==2'd0) ||
                   (rd_busy[2] && rd_grant[2]==2'd0));
        if (m_rvalid[1])
            assert((rd_busy[0] && rd_grant[0]==2'd1) ||
                   (rd_busy[1] && rd_grant[1]==2'd1) ||
                   (rd_busy[2] && rd_grant[2]==2'd1));
        if (m_rvalid[2])
            assert((rd_busy[0] && rd_grant[0]==2'd2) ||
                   (rd_busy[1] && rd_grant[1]==2'd2) ||
                   (rd_busy[2] && rd_grant[2]==2'd2));
    end
end

// P5: slave_idle_no_valid — an idle slave receives no AW/W/AR valid signals
always @(*) begin
    if (!wr_busy[0]) begin assert(!s_awvalid[0]); assert(!s_wvalid[0]); end
    if (!wr_busy[1]) begin assert(!s_awvalid[1]); assert(!s_wvalid[1]); end
    if (!wr_busy[2]) begin assert(!s_awvalid[2]); assert(!s_wvalid[2]); end
    if (!rd_busy[0]) assert(!s_arvalid[0]);
    if (!rd_busy[1]) assert(!s_arvalid[1]);
    if (!rd_busy[2]) assert(!s_arvalid[2]);
end

// P6: awready_implies_busy — AWREADY to master m only when a slave has granted m
always @(*) begin
    if (rst_n) begin
        if (m_awready[0])
            assert((wr_busy[0]&&wr_grant[0]==2'd0)||(wr_busy[1]&&wr_grant[1]==2'd0)||(wr_busy[2]&&wr_grant[2]==2'd0));
        if (m_awready[1])
            assert((wr_busy[0]&&wr_grant[0]==2'd1)||(wr_busy[1]&&wr_grant[1]==2'd1)||(wr_busy[2]&&wr_grant[2]==2'd1));
        if (m_awready[2])
            assert((wr_busy[0]&&wr_grant[0]==2'd2)||(wr_busy[1]&&wr_grant[1]==2'd2)||(wr_busy[2]&&wr_grant[2]==2'd2));
    end
end
`endif

endmodule
