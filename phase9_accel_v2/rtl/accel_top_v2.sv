`timescale 1ns/1ps
// Phase 9 accelerator top-level.
//
// Upgrades over Phase 4 accel_top:
//   · Parametric N×N systolic array (default N=4)
//   · 128 KB scratchpad fed by DMA (128-bit/cycle to the array)
//   · Hardware ReLU (CTRL[2] enables)
//   · Same AXI4-Lite slave interface, extended address range
//
// AXI4-Lite address map (full 32-bit addr from crossbar):
//   addr[16]=0  (0x5000_0xxx)  Control registers
//   addr[16]=1  (0x5001_xxxx)  Scratchpad write port for DMA
//
// Control register offsets (addr[16]=0):
//   0x00  CTRL      [0]=start  [1]=done(RO)  [2]=relu_en
//   0x04  ACT_BASE  scratchpad row# of first activation (row = byte_addr/16)
//   0x08..0x08+4*(N-1)  W_row[0..N-1]  N×N weight rows, packed INT8 (N bytes each)
//   0x100..0x100+4*(N-1) Y[0..N-1]     INT32 outputs (read-only)
//
// Operation:
//   1. DMA writes activations to scratchpad at 0x5001_0000.
//   2. CPU writes W_row[0..N-1] and ACT_BASE via control registers.
//   3. CPU writes CTRL[0]=1 (start).
//   4. FSM reads N activation rows from scratchpad (one per cycle).
//   5. Array drains for N+N cycles; outputs captured; ReLU applied.
//   6. CTRL[1] (done) set. CPU reads Y[0..N-1].

module accel_top_v2 #(
    parameter int N    = 4,
    parameter int ROWS = 8192
)(
    input  logic clk,
    input  logic rst_n,

    // AXI4-Lite slave (32-bit)
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

    output logic        irq_done
);

    // ── Scratchpad ────────────────────────────────────────────────────────
    logic [16:0] sp_awaddr;
    logic        sp_awvalid, sp_awready;
    logic [31:0] sp_wdata;
    logic  [3:0] sp_wstrb;
    logic        sp_wvalid, sp_wready;
    logic  [1:0] sp_bresp;
    logic        sp_bvalid, sp_bready;
    logic [16:0] sp_araddr;
    logic        sp_arvalid, sp_arready;
    logic [31:0] sp_rdata;
    logic  [1:0] sp_rresp;
    logic        sp_rvalid, sp_rready;
    logic [12:0] sp_accel_addr;
    logic [127:0] sp_accel_rdata;

    scratchpad #(.ROWS(ROWS)) u_scratch (
        .clk        (clk),
        .rst_n      (rst_n),
        .s_awaddr   (sp_awaddr),   .s_awvalid (sp_awvalid), .s_awready(sp_awready),
        .s_wdata    (sp_wdata),    .s_wstrb   (sp_wstrb),   .s_wvalid (sp_wvalid),
        .s_wready   (sp_wready),   .s_bresp   (sp_bresp),   .s_bvalid (sp_bvalid),
        .s_bready   (sp_bready),
        .s_araddr   (sp_araddr),   .s_arvalid (sp_arvalid), .s_arready(sp_arready),
        .s_rdata    (sp_rdata),    .s_rresp   (sp_rresp),   .s_rvalid (sp_rvalid),
        .s_rready   (sp_rready),
        .accel_addr (sp_accel_addr), .accel_rdata(sp_accel_rdata)
    );

    // Route scratchpad write/read through AXI demux (addr[16]=1)
    assign sp_awaddr  = s_awaddr[16:0];
    assign sp_awvalid = s_awvalid & s_awaddr[16];
    assign sp_wdata   = s_wdata;
    assign sp_wstrb   = s_wstrb;
    assign sp_wvalid  = s_wvalid & s_awaddr[16];
    assign sp_araddr  = s_araddr[16:0];
    assign sp_arvalid = s_arvalid & s_araddr[16];
    assign sp_rready  = s_rready;
    assign sp_bready  = s_bready;

    // ── Control registers ─────────────────────────────────────────────────
    logic        ctrl_start, ctrl_done, ctrl_relu;
    logic [31:0] act_base;
    logic [N*8-1:0] w_row_reg [0:N-1];
    logic [31:0]    y_reg     [0:N-1];

    // ── Systolic array wires ──────────────────────────────────────────────
    logic [N*8-1:0] w_row  [0:N-1];
    logic [7:0]     a_feed [0:N-1];
    logic [31:0]    y_out  [0:N-1];

    systolic_array #(.N(N)) u_array (
        .clk    (clk),
        .rst_n  (rst_n),
        .w_row  (w_row),
        .a_feed (a_feed),
        .y_out  (y_out)
    );

    // Weights always come from registers (loaded by CPU via AXI)
    genvar gi;
    generate
        for (gi = 0; gi < N; gi++) begin : g_wrow
            assign w_row[gi] = w_row_reg[gi];
        end
    endgenerate

    // ── FSM ───────────────────────────────────────────────────────────────
    // Staggered feed: row r sees its activation r+1 feed-cycles in.
    // After the last feed cycle (ctr=N), ps[N] is valid ONE drain cycle later.
    localparam int DRAIN = 1;

    typedef enum logic [1:0] {
        IDLE, FEED, DRAIN_ST, DONE_ST
    } state_t;
    state_t state;

    // Use integer counters to avoid width-cast issues
    integer feed_ctr;   // 0..N-1 during FEED
    integer drain_ctr;  // 0..DRAIN during DRAIN_ST
    logic [12:0] act_row_ptr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state       <= IDLE;
            ctrl_done   <= 1'b0;
            feed_ctr    <= 0;
            drain_ctr   <= 0;
            act_row_ptr <= 13'h0;
            sp_accel_addr <= 13'h0;
            for (int i = 0; i < N; i++) begin
                a_feed[i] <= 8'h0;
                y_reg[i]  <= 32'h0;
            end
        end else begin
            case (state)

            IDLE: begin
                if (ctrl_start && !ctrl_done) begin
                    state       <= FEED;
                    feed_ctr    <= 0;
                    drain_ctr   <= 0;
                    act_row_ptr <= act_base[15:3];
                    // Pre-prime scratchpad: address row 0 one cycle early so
                    // data is available at the first read in FEED.
                    sp_accel_addr <= act_base[15:3];
                    for (int i = 0; i < N; i++) a_feed[i] <= 8'h0;
                end
            end

            FEED: begin
                // Look-ahead addressing: request row feed_ctr+1 now so
                // row feed_ctr data (requested last cycle) is ready this cycle.
                sp_accel_addr <= act_row_ptr + feed_ctr[12:0] + 13'd1;
                // From cycle 1 onward latch the previous cycle's scratchpad data.
                if (feed_ctr > 0) begin
                    for (int r = 0; r < N; r++) begin
                        a_feed[r] <= sp_accel_rdata[r*8 +: 8];
                    end
                end
                if (feed_ctr == N) begin
                    state     <= DRAIN_ST;
                    drain_ctr <= 0;
                end else begin
                    feed_ctr  <= feed_ctr + 1;
                end
            end

            DRAIN_ST: begin
                // Zero-feed the array while pipeline drains
                for (int i = 0; i < N; i++) a_feed[i] <= 8'h0;
                if (drain_ctr == DRAIN) begin
                    // Capture outputs
                    for (int c = 0; c < N; c++) begin
                        if (ctrl_relu && y_out[c][31])
                            y_reg[c] <= 32'h0;
                        else
                            y_reg[c] <= y_out[c];
                    end
                    ctrl_done <= 1'b1;
                    state     <= DONE_ST;
                end else begin
                    drain_ctr <= drain_ctr + 1;
                end
            end

            DONE_ST: begin
                if (!ctrl_start) begin
                    ctrl_done <= 1'b0;
                    state     <= IDLE;
                end
            end

            default: state <= IDLE;
            endcase
        end
    end

    assign irq_done = ctrl_done;

    // ── AXI4-Lite write — control registers (addr[16]=0) ─────────────────
    assign s_awready = 1'b1;
    assign s_wready  = 1'b1;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ctrl_start <= 1'b0;
            ctrl_relu  <= 1'b0;
            act_base   <= 32'h0;
            for (int i = 0; i < N; i++) w_row_reg[i] <= '0;
        end else if (s_awvalid && s_wvalid && !s_awaddr[16]) begin
            if (s_awaddr[8:0] == 9'h00) begin
                ctrl_start <= s_wdata[0];
                ctrl_relu  <= s_wdata[2];
            end else if (s_awaddr[8:0] == 9'h04) begin
                act_base <= s_wdata;
            end else begin
                // W_row[i] at offsets 0x08, 0x0C, 0x10, 0x14 ...
                for (int i = 0; i < N; i++) begin
                    if (s_awaddr[7:0] == 8'h08 + 8'(i*4))
                        w_row_reg[i] <= s_wdata[N*8-1:0];
                end
            end
        end
    end

    // BRESP for control writes
    logic ctrl_bvalid_r;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) ctrl_bvalid_r <= 1'b0;
        else ctrl_bvalid_r <= (s_awvalid && s_wvalid && !s_awaddr[16]) ||
                              (ctrl_bvalid_r && !s_bready);
    end

    // ── AXI4-Lite read — control registers (addr[16]=0) ──────────────────
    logic ctrl_rvalid_r;
    logic [31:0] ctrl_rdata_r;

    assign s_arready = 1'b1;
    assign s_rresp   = 2'b00;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ctrl_rvalid_r <= 1'b0;
            ctrl_rdata_r  <= 32'h0;
        end else if (s_arvalid && !s_araddr[16]) begin
            ctrl_rvalid_r <= 1'b1;
            if (s_araddr[8:0] == 9'h00)
                ctrl_rdata_r <= {29'h0, ctrl_relu, ctrl_done, ctrl_start};
            else if (s_araddr[8:0] == 9'h04)
                ctrl_rdata_r <= act_base;
            else begin
                ctrl_rdata_r <= 32'h0;
                for (int i = 0; i < N; i++) begin
                    if (s_araddr[7:0] == 8'h08 + 8'(i*4))
                        ctrl_rdata_r <= {{(32-N*8){1'b0}}, w_row_reg[i]};
                    // Y outputs at 0x100+i*4
                    if (s_araddr[8:0] == 9'h100 + 9'(i*4))
                        ctrl_rdata_r <= y_reg[i];
                end
            end
        end else if (s_rready) begin
            ctrl_rvalid_r <= 1'b0;
        end
    end

    // ── Output mux: scratchpad vs control ─────────────────────────────────
    assign s_rvalid = s_araddr[16] ? sp_rvalid : ctrl_rvalid_r;
    assign s_rdata  = s_araddr[16] ? sp_rdata  : ctrl_rdata_r;
    assign s_bvalid = s_awaddr[16] ? sp_bvalid : ctrl_bvalid_r;
    assign s_bresp  = 2'b00;

endmodule
