`timescale 1ns/1ps
// SV32 two-level page-table walker.
// Walk sequence:
//   L1 address = {satp_ppn[21:0], vpn1[9:0], 2'b00}  (root table @ satp.ppn×4096 + vpn1×4)
//   L2 address = {l1_ppn[21:0],   vpn0[9:0], 2'b00}  (L1-pointed table)
// Superpage: if the L1 PTE is a leaf (V=1, R|X ≠ 0), return it directly.
// Faults:
//   page_fault_o:   V=0, reserved (V=1,R=0,W=1), non-leaf L2 pointer
//   access_fault_o: AXI RRESP ≠ OK
// AXI4-Lite read master (AR + R channels only).
module ptw (
    input  logic        clk,
    input  logic        rst,

    // Walk request
    input  logic        req_i,
    input  logic [21:0] satp_ppn_i,
    input  logic [9:0]  vpn1_i,        // vaddr[31:22]
    input  logic [9:0]  vpn0_i,        // vaddr[21:12]

    // Walk result (registered outputs, valid for one cycle after done_o=1)
    output logic        done_o,
    output logic        page_fault_o,
    output logic        access_fault_o,
    output logic [21:0] ppn_o,
    output logic [7:0]  pte_flags_o,   // {D,A,G,U,X,W,R,V}
    output logic        superpage_o,

    // AXI4-Lite read master
    output logic [31:0] axi_araddr_o,
    output logic        axi_arvalid_o,
    input  logic        axi_arready_i,
    input  logic [31:0] axi_rdata_i,
    input  logic [1:0]  axi_rresp_i,
    input  logic        axi_rvalid_i,
    output logic        axi_rready_o
);
    localparam [2:0]
        S_IDLE  = 3'd0,
        S_L1_AR = 3'd1,
        S_L1_R  = 3'd2,
        S_L2_AR = 3'd3,
        S_L2_R  = 3'd4;

    logic [2:0] state;

    // Registered walk parameters
    logic [21:0] satp_ppn_r;
    logic [9:0]  vpn1_r, vpn0_r;
    logic [21:0] l1_ppn_r;   // PPN from L1 PTE (points to L2 table)

    // PTE field extracts from AXI read data (outside always — Icarus rule)
    logic [21:0] pte_ppn;
    logic [7:0]  pte_flags;
    logic        pte_v, pte_r, pte_w, pte_x;
    logic        pte_is_leaf, pte_reserved;

    assign pte_ppn      = axi_rdata_i[31:10];
    assign pte_flags    = axi_rdata_i[7:0];
    assign pte_v        = axi_rdata_i[0];
    assign pte_r        = axi_rdata_i[1];
    assign pte_w        = axi_rdata_i[2];
    assign pte_x        = axi_rdata_i[3];
    assign pte_is_leaf  = pte_v && (pte_r || pte_x);
    assign pte_reserved = pte_v && !pte_r && pte_w;  // V=1,R=0,W=1 is reserved

    // Walk addresses (combinational from registered state)
    logic [31:0] l1_addr, l2_addr;
    assign l1_addr = {satp_ppn_r, vpn1_r, 2'b00};
    assign l2_addr = {l1_ppn_r,   vpn0_r, 2'b00};

    // AXI channel outputs
    assign axi_arvalid_o = (state == S_L1_AR) || (state == S_L2_AR);
    assign axi_araddr_o  = (state == S_L1_AR) ? l1_addr : l2_addr;
    assign axi_rready_o  = (state == S_L1_R) || (state == S_L2_R);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            state          <= S_IDLE;
            satp_ppn_r     <= '0;
            vpn1_r         <= '0;
            vpn0_r         <= '0;
            l1_ppn_r       <= '0;
            done_o         <= 1'b0;
            page_fault_o   <= 1'b0;
            access_fault_o <= 1'b0;
            ppn_o          <= '0;
            pte_flags_o    <= '0;
            superpage_o    <= 1'b0;
        end else begin
            done_o         <= 1'b0;
            page_fault_o   <= 1'b0;
            access_fault_o <= 1'b0;

            case (state)
                S_IDLE: begin
                    if (req_i) begin
                        satp_ppn_r <= satp_ppn_i;
                        vpn1_r     <= vpn1_i;
                        vpn0_r     <= vpn0_i;
                        state      <= S_L1_AR;
                    end
                end

                S_L1_AR: begin
                    if (axi_arready_i) state <= S_L1_R;
                end

                S_L1_R: begin
                    if (axi_rvalid_i) begin
                        if (axi_rresp_i != 2'b00) begin
                            access_fault_o <= 1'b1;
                            done_o         <= 1'b1;
                            state          <= S_IDLE;
                        end else if (!pte_v || pte_reserved) begin
                            page_fault_o <= 1'b1;
                            done_o       <= 1'b1;
                            state        <= S_IDLE;
                        end else if (pte_is_leaf) begin
                            ppn_o       <= pte_ppn;
                            pte_flags_o <= pte_flags;
                            superpage_o <= 1'b1;
                            done_o      <= 1'b1;
                            state       <= S_IDLE;
                        end else begin
                            l1_ppn_r <= pte_ppn;
                            state    <= S_L2_AR;
                        end
                    end
                end

                S_L2_AR: begin
                    if (axi_arready_i) state <= S_L2_R;
                end

                S_L2_R: begin
                    if (axi_rvalid_i) begin
                        if (axi_rresp_i != 2'b00) begin
                            access_fault_o <= 1'b1;
                            done_o         <= 1'b1;
                            state          <= S_IDLE;
                        end else if (!pte_v || pte_reserved || !pte_is_leaf) begin
                            // Non-leaf L2 PTE = page fault (3-level not supported in SV32)
                            page_fault_o <= 1'b1;
                            done_o       <= 1'b1;
                            state        <= S_IDLE;
                        end else begin
                            ppn_o       <= pte_ppn;
                            pte_flags_o <= pte_flags;
                            superpage_o <= 1'b0;
                            done_o      <= 1'b1;
                            state       <= S_IDLE;
                        end
                    end
                end

                default: state <= S_IDLE;
            endcase
        end
    end

endmodule
