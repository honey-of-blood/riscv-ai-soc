`timescale 1ns/1ps
// N×N weight-stationary systolic array using INT4 or INT8 pe_int4 PEs.
//
// Topology: partial sums flow DOWN each column; all PEs in row r share the
// same activation a_feed[r].  One activation vector a[0..N-1] is loaded
// into A_VEC before each run; the FSM stagger-feeds it so that
//   Y[c] = Σ_r  W[r][c] × a[r]
// is valid in y_reg after N+2 clock cycles.
//
// APB register map (12-bit paddr, 9 bits decoded):
//   0x000        CTRL     W:[0]=start,[2]=relu_en  R:[2:0]={relu,done,start}
//   0x008+r*4    W_ROW_r  packed weights row r: {w[r][N-1]..w[r][0]} ACT_W bits each
//   0x028        A_VEC    packed activations:    {a[N-1]..a[0]}       ACT_W bits each
//   0x100+c*4    Y_c      INT32 output column c (valid when done=1)

module systolic_array_v3 #(
    parameter int N     = 4,    // array dimension (N×N)
    parameter int ACT_W = 4,    // 4=INT4, 8=INT8
    parameter int ACCW  = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // APB slave
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready
);

// ── APB helpers ───────────────────────────────────────────────────────────
logic        apb_wr;
logic [8:0]  apb_a;
assign apb_wr = psel & penable & pwrite;
assign pready = 1'b1;
assign apb_a  = paddr[8:0];

// ── Control / data registers (APB-writable) ───────────────────────────────
localparam int VEC_W = N * ACT_W;   // bits per packed row

logic             ctrl_start, ctrl_relu;
logic [VEC_W-1:0] w_row_reg [0:N-1];
logic [VEC_W-1:0] a_vec_reg;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ctrl_start <= 1'b0;
        ctrl_relu  <= 1'b0;
        a_vec_reg  <= '0;
        for (int i = 0; i < N; i++) w_row_reg[i] <= '0;
    end else if (apb_wr) begin
        if (apb_a == 9'h000) begin
            ctrl_start <= pwdata[0];
            ctrl_relu  <= pwdata[2];
        end
        if (apb_a == 9'h028) a_vec_reg <= pwdata[VEC_W-1:0];
        for (int r = 0; r < N; r++) begin
            if (apb_a == 9'h008 + 9'(r * 4))
                w_row_reg[r] <= pwdata[VEC_W-1:0];
        end
    end
end

// ── Unpack weights and activations outside always blocks (Icarus rule) ────
logic signed [ACT_W-1:0] w_mat     [0:N-1][0:N-1];
logic signed [ACT_W-1:0] a_unpacked[0:N-1];

genvar gi, gj;
generate
    for (gi = 0; gi < N; gi++) begin : g_wmat_r
        for (gj = 0; gj < N; gj++) begin : g_wmat_c
            assign w_mat[gi][gj] = w_row_reg[gi][gj*ACT_W +: ACT_W];
        end
    end
    for (gi = 0; gi < N; gi++) begin : g_aunpack
        assign a_unpacked[gi] = a_vec_reg[gi*ACT_W +: ACT_W];
    end
endgenerate

// ── Partial sum array and activation feed ────────────────────────────────
logic signed [ACCW-1:0]  ps      [0:N][0:N-1];
logic signed [ACT_W-1:0] a_feed  [0:N-1];

// Output taps from bottom row
logic signed [ACCW-1:0] y_out [0:N-1];
generate
    for (gi = 0; gi < N; gi++) begin : g_yout
        assign y_out[gi] = ps[N][gi];
        assign ps[0][gi] = '0;      // zero feed into top of each column
    end
endgenerate

// ── N×N pe_int4 instances ────────────────────────────────────────────────
generate
    for (gi = 0; gi < N; gi++) begin : g_row
        for (gj = 0; gj < N; gj++) begin : g_col
            pe_int4 #(.ACT_W(ACT_W), .ACCW(ACCW)) u_pe (
                .clk  (clk),
                .rst_n(rst_n),
                .a_i  (a_feed[gi]),       // activation for row gi
                .b_i  (w_mat[gi][gj]),    // weight at [row=gi, col=gj]
                .c_i  (ps[gi][gj]),       // partial sum from above
                .c_o  (ps[gi+1][gj]),     // partial sum to below
                .a_o  (),
                .b_o  ()
            );
        end
    end
endgenerate

// ── FSM ──────────────────────────────────────────────────────────────────
localparam int FCNT_W = $clog2(N + 1);

typedef enum logic [1:0] { IDLE, FEED, CAPTURE, DONE_ST } state_t;
state_t state;

logic [FCNT_W-1:0] feed_ctr;
logic              ctrl_done;
logic [ACCW-1:0]   y_reg [0:N-1];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state     <= IDLE;
        ctrl_done <= 1'b0;
        feed_ctr  <= '0;
        for (int r = 0; r < N; r++) a_feed[r] <= '0;
        for (int c = 0; c < N; c++) y_reg[c]  <= '0;
    end else begin
        case (state)

        IDLE: begin
            ctrl_done <= 1'b0;
            for (int r = 0; r < N; r++) a_feed[r] <= '0;
            if (ctrl_start) begin
                state    <= FEED;
                feed_ctr <= '0;
                // Pre-load stagger step 0: only a_feed[0] gets a[0]
                a_feed[0] <= a_unpacked[0];
                for (int r = 1; r < N; r++) a_feed[r] <= '0;
            end
        end

        FEED: begin
            // a_feed is already loaded for step feed_ctr (from previous edge).
            // Now prepare a_feed for step feed_ctr+1.
            if (feed_ctr == FCNT_W'(N - 1)) begin
                // Last stagger step — clear feed and capture in next state
                state <= CAPTURE;
                for (int r = 0; r < N; r++) a_feed[r] <= '0;
            end else begin
                feed_ctr <= feed_ctr + FCNT_W'(1);
                for (int r = 0; r < N; r++) begin
                    // Only the PE for row (feed_ctr+1) gets its activation
                    if (r == feed_ctr + FCNT_W'(1))
                        a_feed[r] <= a_unpacked[r];
                    else
                        a_feed[r] <= '0;
                end
            end
        end

        CAPTURE: begin
            // y_out[c] = ps[N][c] is valid (registered from last FEED edge)
            for (int c = 0; c < N; c++) begin
                if (ctrl_relu && y_out[c][ACCW-1])
                    y_reg[c] <= '0;
                else
                    y_reg[c] <= y_out[c];
            end
            ctrl_done <= 1'b1;
            state     <= DONE_ST;
        end

        DONE_ST: begin
            // Wait for CPU to clear start
            if (!ctrl_start) begin
                ctrl_done <= 1'b0;
                state     <= IDLE;
            end
        end

        endcase
    end
end

// ── APB read ──────────────────────────────────────────────────────────────
always_comb begin
    prdata = '0;
    if (apb_a == 9'h000) begin
        prdata = {29'b0, ctrl_relu, ctrl_done, ctrl_start};
    end else begin
        for (int c = 0; c < N; c++) begin
            if (apb_a == 9'h100 + 9'(c * 4))
                prdata = y_reg[c];
        end
    end
end

endmodule
