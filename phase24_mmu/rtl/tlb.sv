`timescale 1ns/1ps
// 16-entry fully-associative TLB for SV32.
// Each entry holds VPN[19:0], ASID[8:0] and the leaf PTE permission fields.
// Superpage (4MB): fill_superpage_i=1 → only vpn[19:10] compared;
//   returned ppn[9:0] is replaced by vpn_i[9:0] (pass-through from VA).
// SFENCE.VMA: sfence_all_i → flush all; else flush entries with matching ASID
//   (global entries, G=1, are immune to ASID-specific flushes per spec).
// Replacement: FIFO (write-pointer wraps at 16).
//
// Icarus 12.0 compatibility: all array access uses generate blocks with
// constant genvar indices; no variable-indexed array access in always blocks.
// Output mux uses one-hot OR-reduce: outputs are 0 (not X) when no entry hits.
module tlb (
    input  logic        clk,
    input  logic        rst,

    // Lookup (combinational)
    input  logic [19:0] vpn_i,
    input  logic [8:0]  asid_i,
    output logic        hit_o,
    output logic [21:0] ppn_o,
    output logic        pte_r_o,
    output logic        pte_w_o,
    output logic        pte_x_o,
    output logic        pte_u_o,
    output logic        pte_d_o,
    output logic        pte_a_o,
    output logic        pte_g_o,
    output logic        superpage_o,

    // Fill (from PTW — fires for one cycle when walk completes successfully)
    input  logic        fill_i,
    input  logic [19:0] fill_vpn_i,
    input  logic [8:0]  fill_asid_i,
    input  logic [21:0] fill_ppn_i,
    input  logic        fill_r_i,
    input  logic        fill_w_i,
    input  logic        fill_x_i,
    input  logic        fill_u_i,
    input  logic        fill_d_i,
    input  logic        fill_a_i,
    input  logic        fill_g_i,
    input  logic        fill_superpage_i,

    // SFENCE.VMA
    input  logic        sfence_i,
    input  logic [8:0]  sfence_asid_i,
    input  logic        sfence_all_i
);
    localparam N   = 16;
    localparam IDX = 4;   // clog2(16)

    // ── Entry storage (unpacked arrays) ─────────────────────────────────────
    logic        valid_r    [N];
    logic [19:0] vpn_r      [N];
    logic [8:0]  asid_r     [N];
    logic [21:0] ppn_r      [N];
    logic        pte_r_r    [N];
    logic        pte_w_r    [N];
    logic        pte_x_r    [N];
    logic        pte_u_r    [N];
    logic        pte_d_r    [N];
    logic        pte_a_r    [N];
    logic        pte_g_r    [N];
    logic        superpage_r[N];

    logic [IDX-1:0] wr_ptr;

    // ── Per-entry VPN1 (upper 10 bits of VPN) extracted via generate ────────
    // Icarus rule: constant bit-selects inside generate assign are OK.
    logic [9:0] vpn1_r [N];
    genvar gi;
    generate
        for (gi = 0; gi < N; gi++) begin : g_vpn1
            assign vpn1_r[gi] = vpn_r[gi][19:10];
        end
    endgenerate

    // ── Match logic — one signal per entry (generate, constant indices) ──────
    logic asid_ok   [N];
    logic vpn_ok    [N];
    logic entry_hit [N];

    generate
        for (gi = 0; gi < N; gi++) begin : g_hit
            assign asid_ok[gi]   = pte_g_r[gi] || (asid_r[gi] == asid_i);
            assign vpn_ok[gi]    = superpage_r[gi]
                                    ? (vpn1_r[gi] == vpn_i[19:10])
                                    : (vpn_r[gi]  == vpn_i);
            assign entry_hit[gi] = valid_r[gi] && asid_ok[gi] && vpn_ok[gi];
        end
    endgenerate

    // ── hit_o: pack entry_hit into a vector then OR-reduce ───────────────────
    logic [N-1:0] hit_packed;
    generate
        for (gi = 0; gi < N; gi++) begin : g_hp
            assign hit_packed[gi] = entry_hit[gi];
        end
    endgenerate
    assign hit_o = |hit_packed;

    // ── Output mux: generate-based one-hot OR-reduce ─────────────────────────
    // For each entry, contribute its fields when it hits.
    // OR-reduce gives 0 (not X) when no entry matches — safe for downstream.
    // All indices are genvar compile-time constants; no always_comb needed.
    logic [N-1:0] r_c, w_c, x_c, u_c, d_c, a_c, g_c, sp_c;
    logic [N-1:0] ppn_c [22];   // ppn_c[bit][entry]

    genvar gj, gb;
    generate
        for (gj = 0; gj < N; gj++) begin : g_out
            assign r_c[gj]  = entry_hit[gj] && pte_r_r[gj];
            assign w_c[gj]  = entry_hit[gj] && pte_w_r[gj];
            assign x_c[gj]  = entry_hit[gj] && pte_x_r[gj];
            assign u_c[gj]  = entry_hit[gj] && pte_u_r[gj];
            assign d_c[gj]  = entry_hit[gj] && pte_d_r[gj];
            assign a_c[gj]  = entry_hit[gj] && pte_a_r[gj];
            assign g_c[gj]  = entry_hit[gj] && pte_g_r[gj];
            assign sp_c[gj] = entry_hit[gj] && superpage_r[gj];
            for (gb = 0; gb < 22; gb++) begin : g_ppn
                assign ppn_c[gb][gj] = entry_hit[gj] && ppn_r[gj][gb];
            end
        end
    endgenerate

    assign pte_r_o    = |r_c;
    assign pte_w_o    = |w_c;
    assign pte_x_o    = |x_c;
    assign pte_u_o    = |u_c;
    assign pte_d_o    = |d_c;
    assign pte_a_o    = |a_c;
    assign pte_g_o    = |g_c;
    assign superpage_o = |sp_c;

    // PPN: 22-bit OR-reduce, bit by bit
    logic [21:0] raw_ppn;
    genvar gb2;
    generate
        for (gb2 = 0; gb2 < 22; gb2++) begin : g_ppn_red
            assign raw_ppn[gb2] = |ppn_c[gb2];
        end
    endgenerate

    // Superpage PA: ppn[21:10] from PTE, ppn[9:0] from VA (vpn_i[9:0])
    logic [9:0] ppn_lo;
    assign ppn_lo = superpage_o ? vpn_i[9:0] : raw_ppn[9:0];
    assign ppn_o  = {raw_ppn[21:10], ppn_lo};

    // ── Sequential: fill and flush ────────────────────────────────────────────
    // Icarus 12.0: for loops in always_ff are unrolled at elaboration, giving
    // constant-indexed write targets — this is safe.
    integer i;
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            wr_ptr <= '0;
            for (i = 0; i < N; i++) valid_r[i] <= 1'b0;
        end else if (sfence_i) begin
            for (i = 0; i < N; i++) begin
                if (sfence_all_i) begin
                    valid_r[i] <= 1'b0;
                end else if (!pte_g_r[i] && (asid_r[i] == sfence_asid_i)) begin
                    valid_r[i] <= 1'b0;
                end
            end
        end else if (fill_i) begin
            valid_r    [wr_ptr] <= 1'b1;
            vpn_r      [wr_ptr] <= fill_vpn_i;
            asid_r     [wr_ptr] <= fill_asid_i;
            ppn_r      [wr_ptr] <= fill_ppn_i;
            pte_r_r    [wr_ptr] <= fill_r_i;
            pte_w_r    [wr_ptr] <= fill_w_i;
            pte_x_r    [wr_ptr] <= fill_x_i;
            pte_u_r    [wr_ptr] <= fill_u_i;
            pte_d_r    [wr_ptr] <= fill_d_i;
            pte_a_r    [wr_ptr] <= fill_a_i;
            pte_g_r    [wr_ptr] <= fill_g_i;
            superpage_r[wr_ptr] <= fill_superpage_i;
            wr_ptr <= wr_ptr + 1'b1;
        end
    end

endmodule
