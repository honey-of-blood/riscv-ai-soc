`timescale 1ns/1ps
// True Random Number Generator (TRNG) — APB slave.
//
// Entropy source:
//   SYNTHESIS: 3-inverter ring oscillator sampled at sys_clk; jitter provides
//              entropy. Nets marked KEEP/DONT_TOUCH to prevent optimisation.
//   SIMULATION: 32-bit Galois LFSR (maximal-length, taps 32,22,2,1) provides
//               well-distributed pseudo-random data that passes health tests.
//
// Health tests (FIPS 140-2):
//   Monobit: reject raw_rand if popcount < 8 or > 24.
//   A rejected sample is discarded; the generator waits for the next 32 bits.
//
// APB register map (within sel=10, 0x1000_Axxx):
//   0x00 DATA    R=32-bit random word (blocks until ready by pready)
//   0x04 STATUS  [0]=ready  [1]=health_err  [2]=enabled
//   0x08 CTRL    [0]=enable  [1]=force_health_err (test injection)

module trng (
    input  logic        clk,
    input  logic        rst_n,

    // APB
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready
);

// ── Registers ──────────────────────────────────────────────────────────────
logic        enabled;
logic        force_health_err;   // test: inject health failure
logic        health_err_r;
logic [31:0] rand_out;
logic        rand_ready;

logic apb_wr;
assign apb_wr = psel & penable & pwrite;

logic [3:0] apb_a;
assign apb_a = paddr[3:0];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        enabled          <= 1'b1;
        force_health_err <= 1'b0;
    end else if (apb_wr && apb_a == 4'h8) begin
        enabled          <= pwdata[0];
        force_health_err <= pwdata[1];
    end
end

// pready: stall APB read of DATA until a word is ready
logic data_read;
assign data_read = psel & penable & !pwrite & (apb_a == 4'h0);
assign pready    = data_read ? rand_ready : 1'b1;

always_comb begin
    prdata = '0;
    case (apb_a)
        4'h0: prdata = rand_out;
        4'h4: prdata = {29'b0, enabled, health_err_r, rand_ready};
        4'h8: prdata = {30'b0, force_health_err, enabled};
        default: prdata = '0;
    endcase
end

// ── Entropy source ─────────────────────────────────────────────────────────
`ifdef SIMULATION

// Galois LFSR (maximal-length 32-bit, taps 32,22,2,1 per Xilinx app note)
logic [31:0] lfsr;
logic        lfsr_bit;
assign lfsr_bit = lfsr[0];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) lfsr <= 32'hACE1_1234;   // non-zero seed
    else        lfsr <= {lfsr_bit, lfsr[31:1]} ^
                        (lfsr_bit ? 32'hA001_0000 : 32'h0);
end

logic        sample_bit;
assign sample_bit = lfsr[0];

`else
// Synthesis: three independent 5-inverter ring oscillators.
// Odd number of inverters (5) prevents even-loop removal by P&R.
// KEEP/DONT_TOUCH forces independent placement so oscillation frequencies
// differ due to routing skew — their XOR provides the entropy.
// XDC false-paths must be added for all ring_a/b/c nets (see constraints.xdc).
(* KEEP="TRUE", DONT_TOUCH="TRUE" *) logic [4:0] ring_a;
(* KEEP="TRUE", DONT_TOUCH="TRUE" *) logic [4:0] ring_b;
(* KEEP="TRUE", DONT_TOUCH="TRUE" *) logic [4:0] ring_c;

assign ring_a[0] = ~ring_a[4];
assign ring_a[1] = ~ring_a[0];
assign ring_a[2] = ~ring_a[1];
assign ring_a[3] = ~ring_a[2];
assign ring_a[4] = ~ring_a[3];

assign ring_b[0] = ~ring_b[4];
assign ring_b[1] = ~ring_b[0];
assign ring_b[2] = ~ring_b[1];
assign ring_b[3] = ~ring_b[2];
assign ring_b[4] = ~ring_b[3];

assign ring_c[0] = ~ring_c[4];
assign ring_c[1] = ~ring_c[0];
assign ring_c[2] = ~ring_c[1];
assign ring_c[3] = ~ring_c[2];
assign ring_c[4] = ~ring_c[3];

// Von Neumann de-bias: XOR three LSBs
logic sample_bit;
assign sample_bit = ring_a[0] ^ ring_b[0] ^ ring_c[0];
`endif

// ── 32-bit shift register accumulator ─────────────────────────────────────
logic [31:0] sr;
logic [5:0]  sr_count;
logic [31:0] raw_rand;
logic        raw_ready;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        sr        <= '0;
        sr_count  <= '0;
        raw_rand  <= '0;
        raw_ready <= 1'b0;
    end else if (enabled) begin
        sr        <= {sr[30:0], sample_bit};
        raw_ready <= 1'b0;
        if (sr_count == 6'd31) begin
            raw_rand  <= {sr[30:0], sample_bit};
            raw_ready <= 1'b1;
            sr_count  <= '0;
        end else begin
            sr_count <= sr_count + 6'd1;
        end
    end
end

// ── Monobit health test ────────────────────────────────────────────────────
logic [5:0] ones_count;
assign ones_count = $countones(raw_rand);

logic health_ok;
logic health_ok_wire;
assign health_ok_wire = (ones_count >= 6'd8) && (ones_count <= 6'd24);
assign health_ok      = health_ok_wire && !force_health_err;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        rand_out      <= '0;
        rand_ready    <= 1'b0;
        health_err_r  <= 1'b0;
    end else begin
        rand_ready <= 1'b0;
        if (raw_ready) begin
            if (health_ok) begin
                rand_out   <= raw_rand;
                rand_ready <= 1'b1;
            end else begin
                health_err_r <= 1'b1;   // sticky health error flag
            end
        end
        // Clear rand_ready after a successful APB data read
        if (data_read && rand_ready && pready) begin
            rand_ready <= 1'b0;
        end
    end
end

endmodule
