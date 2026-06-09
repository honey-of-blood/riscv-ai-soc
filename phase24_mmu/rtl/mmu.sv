`timescale 1ns/1ps
// SV32 MMU: TLB lookup → PTW on miss → permission check.
//
// BARE mode (satp[31]=0 or priv=M): paddr = vaddr, no faults.
// SV32 mode: TLB hit → permission check → PA;
//            TLB miss → PTW walk (stall_o=1) → M_RESULT (stall_o=0) → fill TLB.
//
// Privilege levels: 2'b11=M, 2'b01=S, 2'b00=U
// Access types:     2'b00=fetch, 2'b01=load, 2'b10=store
//
// Permission rules (RISC-V ISA spec, SV32):
//   fetch: PTE.X required
//   load:  PTE.R required
//   store: PTE.W required
//   U-mode can only access U=1 pages
//   S-mode can only access U=0 pages (unless mstatus.SUM=1 for loads/stores)
//   S-mode cannot execute U=1 pages (regardless of SUM)
module mmu (
    input  logic        clk,
    input  logic        rst,

    // Translation request
    input  logic [31:0] vaddr_i,
    input  logic [1:0]  priv_i,         // current privilege level
    input  logic [1:0]  access_type_i,
    input  logic        req_i,

    // CSR inputs
    input  logic [31:0] satp_i,
    input  logic        sum_i,          // mstatus.SUM

    // Result
    output logic [31:0] paddr_o,
    output logic        stall_o,
    output logic        page_fault_o,
    output logic        access_fault_o,

    // PTW AXI4-Lite read master
    output logic [31:0] ptw_araddr_o,
    output logic        ptw_arvalid_o,
    input  logic        ptw_arready_i,
    input  logic [31:0] ptw_rdata_i,
    input  logic [1:0]  ptw_rresp_i,
    input  logic        ptw_rvalid_i,
    output logic        ptw_rready_o,

    // SFENCE.VMA
    input  logic        sfence_i,
    input  logic [8:0]  sfence_asid_i,
    input  logic        sfence_all_i
);
    // satp fields (Icarus: assign, not inside always_comb)
    logic        sv32_mode;
    logic [8:0]  satp_asid;
    logic [21:0] satp_ppn;
    assign sv32_mode = satp_i[31];
    assign satp_asid = satp_i[30:22];
    assign satp_ppn  = satp_i[21:0];

    // Virtual address decomposition
    logic [19:0] vpn;
    logic [9:0]  vpn1, vpn0;
    logic [11:0] page_offset;
    assign vpn         = vaddr_i[31:12];
    assign vpn1        = vaddr_i[31:22];
    assign vpn0        = vaddr_i[21:12];
    assign page_offset = vaddr_i[11:0];

    // BARE mode when satp.MODE=0 or in M-mode
    logic bare;
    assign bare = !sv32_mode || (priv_i == 2'b11);

    // TLB outputs
    logic        tlb_hit;
    logic [21:0] tlb_ppn;
    logic        tlb_r, tlb_w, tlb_x, tlb_u;
    logic        tlb_d, tlb_a, tlb_g;
    logic        tlb_sp;

    // PTW outputs
    logic        ptw_req;
    logic        ptw_done, ptw_pfault, ptw_afault;
    logic [21:0] ptw_ppn;
    logic [7:0]  ptw_flags;
    logic        ptw_sp;

    tlb u_tlb (
        .clk            (clk),
        .rst            (rst),
        .vpn_i          (vpn),
        .asid_i         (satp_asid),
        .hit_o          (tlb_hit),
        .ppn_o          (tlb_ppn),
        .pte_r_o        (tlb_r),
        .pte_w_o        (tlb_w),
        .pte_x_o        (tlb_x),
        .pte_u_o        (tlb_u),
        .pte_d_o        (tlb_d),
        .pte_a_o        (tlb_a),
        .pte_g_o        (tlb_g),
        .superpage_o    (tlb_sp),
        // Fill on successful PTW walk (flags[1]=R, [2]=W, [3]=X, [4]=U, [5]=G, [6]=A, [7]=D)
        .fill_i         (ptw_done && !ptw_pfault && !ptw_afault),
        .fill_vpn_i     (vpn),
        .fill_asid_i    (satp_asid),
        .fill_ppn_i     (ptw_ppn),
        .fill_r_i       (ptw_flags[1]),
        .fill_w_i       (ptw_flags[2]),
        .fill_x_i       (ptw_flags[3]),
        .fill_u_i       (ptw_flags[4]),
        .fill_d_i       (ptw_flags[7]),
        .fill_a_i       (ptw_flags[6]),
        .fill_g_i       (ptw_flags[5]),
        .fill_superpage_i(ptw_sp),
        .sfence_i       (sfence_i),
        .sfence_asid_i  (sfence_asid_i),
        .sfence_all_i   (sfence_all_i)
    );

    ptw u_ptw (
        .clk            (clk),
        .rst            (rst),
        .req_i          (ptw_req),
        .satp_ppn_i     (satp_ppn),
        .vpn1_i         (vpn1),
        .vpn0_i         (vpn0),
        .done_o         (ptw_done),
        .page_fault_o   (ptw_pfault),
        .access_fault_o (ptw_afault),
        .ppn_o          (ptw_ppn),
        .pte_flags_o    (ptw_flags),
        .superpage_o    (ptw_sp),
        .axi_araddr_o   (ptw_araddr_o),
        .axi_arvalid_o  (ptw_arvalid_o),
        .axi_arready_i  (ptw_arready_i),
        .axi_rdata_i    (ptw_rdata_i),
        .axi_rresp_i    (ptw_rresp_i),
        .axi_rvalid_i   (ptw_rvalid_i),
        .axi_rready_o   (ptw_rready_o)
    );

    // ── MMU state machine ─────────────────────────────────────────────────────
    localparam [1:0]
        M_IDLE   = 2'd0,
        M_WALK   = 2'd1,
        M_RESULT = 2'd2;   // 1-cycle window: present PTW result before returning to IDLE

    logic [1:0] mmu_state;

    // Latched PTW result (captured at M_WALK → M_RESULT transition)
    logic [21:0] lat_ppn;
    logic [7:0]  lat_flags;
    logic        lat_sp;
    logic        lat_pfault, lat_afault;

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            mmu_state  <= M_IDLE;
            lat_ppn    <= '0;
            lat_flags  <= '0;
            lat_sp     <= 1'b0;
            lat_pfault <= 1'b0;
            lat_afault <= 1'b0;
        end else begin
            case (mmu_state)
                M_IDLE: begin
                    if (req_i && !bare && !tlb_hit)
                        mmu_state <= M_WALK;
                end
                M_WALK: begin
                    if (ptw_done) begin
                        lat_ppn    <= ptw_ppn;
                        lat_flags  <= ptw_flags;
                        lat_sp     <= ptw_sp;
                        lat_pfault <= ptw_pfault;
                        lat_afault <= ptw_afault;
                        mmu_state  <= M_RESULT;
                    end
                end
                M_RESULT: begin
                    mmu_state <= M_IDLE;
                end
                default: mmu_state <= M_IDLE;
            endcase
        end
    end

    // Kick PTW from the registered M_WALK state.
    // Using a combinational expression (mmu_state==M_IDLE && req_i && ...) creates
    // a Verilog simulation race with Icarus when the Python VPI write and clock
    // posedge land in the same delta cycle.  Driving from the registered M_WALK
    // signal (stable one cycle after MMU enters M_WALK) eliminates the race.
    // Gate with !ptw_done: at the posedge when PTW asserts done_o (state→S_IDLE),
    // mmu_state is still M_WALK during that posedge's evaluation, which would
    // spuriously restart PTW.  !ptw_done drops ptw_req to 0 on that exact cycle.
    assign ptw_req = (mmu_state == M_WALK) && !ptw_done;

    // ── Permission check (combinational from TLB output or latched PTW result) ──
    // Use TLB fields when hit or on M_RESULT (where TLB was just filled)
    logic [7:0]  perm_flags;
    logic [21:0] perm_ppn;
    logic        perm_sp;

    always_comb begin
        if (mmu_state == M_RESULT) begin
            perm_flags = lat_flags;
            perm_ppn   = lat_ppn;
            perm_sp    = lat_sp;
        end else begin
            perm_flags = {tlb_d, tlb_a, tlb_g, tlb_u, tlb_x, tlb_w, tlb_r, 1'b1};
            perm_ppn   = tlb_ppn;
            perm_sp    = tlb_sp;
        end
    end

    logic pf_perm;    // permission page fault
    logic pf_priv;    // privilege page fault

    logic perm_r, perm_w, perm_x, perm_u;
    assign perm_r = perm_flags[1];
    assign perm_w = perm_flags[2];
    assign perm_x = perm_flags[3];
    assign perm_u = perm_flags[4];

    always_comb begin
        pf_perm = 1'b0;
        pf_priv = 1'b0;
        case (access_type_i)
            2'b00: begin  // fetch: X required; S-mode cannot execute U pages
                pf_perm = !perm_x;
                pf_priv = (priv_i == 2'b00 && !perm_u) ||
                           (priv_i == 2'b01 &&  perm_u);
            end
            2'b01: begin  // load: R required
                pf_perm = !perm_r;
                pf_priv = (priv_i == 2'b00 && !perm_u) ||
                           (priv_i == 2'b01 &&  perm_u && !sum_i);
            end
            2'b10: begin  // store: W required
                pf_perm = !perm_w;
                pf_priv = (priv_i == 2'b00 && !perm_u) ||
                           (priv_i == 2'b01 &&  perm_u && !sum_i);
            end
            default: begin pf_perm = 1'b1; pf_priv = 1'b0; end
        endcase
    end

    // ── Physical address construction ─────────────────────────────────────────
    // Superpage: ppn[9:0] passes through from vpn0 (VA[21:12])
    logic [9:0]  pa_ppn_lo;
    logic [21:0] pa_ppn;
    assign pa_ppn_lo = perm_sp ? vaddr_i[21:12] : perm_ppn[9:0];
    assign pa_ppn    = {perm_ppn[21:10], pa_ppn_lo};

    assign paddr_o = bare ? vaddr_i : {pa_ppn, page_offset};

    // stall during walk AND during the M_IDLE miss cycle (before first clock edge
    // can register M_WALK), so callers that sample immediately after req_i=1 see
    // stall=1 rather than returning a pre-walk (wrong) physical address.
    assign stall_o = (mmu_state == M_WALK) ||
                     ((mmu_state == M_IDLE) && req_i && !bare && !tlb_hit);

    // ── Fault outputs ─────────────────────────────────────────────────────────
    logic sv32_active;
    assign sv32_active = !bare && req_i;

    // page_fault: from PTW on walk failure, or from permission check on TLB hit / result
    logic pf_ptw;
    assign pf_ptw = (mmu_state == M_RESULT) && lat_pfault;

    logic pf_perm_active;
    assign pf_perm_active = sv32_active && (tlb_hit || (mmu_state == M_RESULT && !lat_afault))
                            && (pf_perm || pf_priv);

    assign page_fault_o   = sv32_active && (pf_ptw || pf_perm_active);
    assign access_fault_o = sv32_active && (mmu_state == M_RESULT) && lat_afault;

endmodule
