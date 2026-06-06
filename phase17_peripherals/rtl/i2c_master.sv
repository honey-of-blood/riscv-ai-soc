`timescale 1ns/1ps
// I2C Master — APB slave, open-drain SCL/SDA, 7-bit & 10-bit addressing,
// 100 kHz / 400 kHz modes, clock stretching, arbitration-lost detection.
//
// APB register map (within sel=8, 0x1000_8xxx):
//   0x00 CTRL     [0]=enable  [1]=irq_en  [2]=fast_400k
//   0x04 ADDR     [9:0]=slave_addr  [10]=10bit_mode
//   0x08 DATA     W=TX byte  R=last RX byte
//   0x0C CMD      [0]=start  [1]=stop  [2]=read  [3]=write  [4]=master_ack
//   0x10 STATUS   [0]=busy  [1]=arb_lost  [2]=nack  [3]=irq  (W1C on [3])
//   0x14 PRESCALE quarter-period in sys_clk cycles (default 249 → 100 kHz @ 100 MHz)
//
// Open-drain convention:
//   scl_oe=1 drives SCL low;  scl_oe=0 releases SCL (pull-up drives high)
//   sda_oe=1 drives SDA low;  sda_oe=0 releases SDA
//
// Commands are one-shot: write CMD, FSM executes and clears BUSY.
//   START → generate start condition
//   WRITE → shift tx_byte out (8 bits, MSB first), then receive ACK
//   READ  → receive 8 bits into rx_byte, then send master_ack bit
//   STOP  → generate stop condition

module i2c_master (
    input  logic        clk,
    input  logic        rst_n,

    // APB
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // I2C open-drain
    output logic        scl_oe,
    input  logic        scl_i,
    output logic        sda_oe,
    input  logic        sda_i,

    output logic        irq_o
);

// ── Registers ─────────────────────────────────────────────────────────────
logic [2:0]  ctrl_r;
logic [10:0] addr_r;
logic [7:0]  tx_byte;
logic [7:0]  rx_byte;
logic [4:0]  cmd_r;
logic [3:0]  status_r;   // busy | arb_lost | nack | irq
logic [15:0] prescale;   // default 249

logic apb_wr;
assign apb_wr  = psel & penable & pwrite;
assign pready  = 1'b1;
assign irq_o   = status_r[3] & ctrl_r[1];

// addr bits for Icarus (no bit-select in always_comb)
logic [4:0] apb_a;
assign apb_a = paddr[4:0];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ctrl_r   <= '0;
        addr_r   <= '0;
        tx_byte  <= '0;
        cmd_r    <= '0;
        prescale <= 16'd249;
    end else if (apb_wr) begin
        case (apb_a)
            5'h00: ctrl_r   <= pwdata[2:0];
            5'h04: addr_r   <= pwdata[10:0];
            5'h08: tx_byte  <= pwdata[7:0];
            5'h0C: cmd_r    <= pwdata[4:0];
            5'h10: if (pwdata[3]) status_r[3] <= 1'b0;  // W1C irq
            5'h14: prescale <= pwdata[15:0];
            default: ;
        endcase
    end
end

always_comb begin
    prdata = '0;
    case (apb_a)
        5'h00: prdata = {29'b0, ctrl_r};
        5'h04: prdata = {21'b0, addr_r};
        5'h08: prdata = {24'b0, rx_byte};
        5'h0C: prdata = {27'b0, cmd_r};
        5'h10: prdata = {28'b0, status_r};
        5'h14: prdata = {16'b0, prescale};
        default: prdata = '0;
    endcase
end

// ── SCL/SDA outputs ────────────────────────────────────────────────────────
logic scl_out, sda_out;
assign scl_oe = !scl_out;   // drive low when scl_out=0
assign sda_oe = !sda_out;   // drive low when sda_out=0

// ── Clock divider ──────────────────────────────────────────────────────────
// stretch: pause divider during clock-stretching (slave holds SCL low).
// Declared here; driven combinatorially from state machine below.
logic stretch;

// Reset clk_cnt when prescale register is written — prevents the
// counter being stuck above the new prescale value for 65K cycles.
logic prescale_wr;
assign prescale_wr = apb_wr & (apb_a == 5'h14);

logic [15:0] clk_cnt;
logic        quarter_tick;   // pulses once every prescale+1 cycles
assign quarter_tick = (clk_cnt == 16'd0);

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n || prescale_wr) begin
        clk_cnt <= '0;
    end else if (!stretch) begin
        if (clk_cnt == prescale)
            clk_cnt <= '0;
        else
            clk_cnt <= clk_cnt + 16'd1;
    end
    // When stretch=1: hold clk_cnt (implicit: no NBA → register holds)
end

// ── State machine ──────────────────────────────────────────────────────────
typedef enum logic [3:0] {
    ST_IDLE,
    ST_START1,   // SCL=1,SDA=1 → SCL=1,SDA=0 (start pulse)
    ST_START2,   // SCL=1→0 after start
    ST_BIT_LO,   // SCL=0, set SDA
    ST_BIT_HI,   // SCL=1, sample/check (with stretch)
    ST_RACK1,    // Receive ACK: SCL=0, release SDA
    ST_RACK2,    // Receive ACK: SCL=1, sample
    ST_SACK1,    // Send ACK: SCL=0, drive SDA
    ST_SACK2,    // Send ACK: SCL=1
    ST_STOP1,    // SCL=0→1 (before stop)
    ST_STOP2     // SCL=1, SDA=0→1 (stop pulse)
} state_t;

state_t      state;
logic [2:0]  bit_idx;    // 7..0, counts bits in byte
logic [7:0]  shift_reg;  // shift register for TX/RX
logic        doing_read; // 1=receiving byte from slave

// stretch: high when SCL is released but slave still pulls it low
assign stretch = ((state == ST_BIT_HI) || (state == ST_RACK2)) && !scl_i;

// Snapshot CMD fields to avoid bit-selects inside always_ff reading pwdata
logic cmd_start, cmd_stop, cmd_read, cmd_write, cmd_mack;
assign cmd_start = cmd_r[0];
assign cmd_stop  = cmd_r[1];
assign cmd_read  = cmd_r[2];
assign cmd_write = cmd_r[3];
assign cmd_mack  = cmd_r[4];

logic new_cmd;
assign new_cmd = (apb_wr && (apb_a == 5'h0C));

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state      <= ST_IDLE;
        scl_out    <= 1'b1;
        sda_out    <= 1'b1;
        bit_idx    <= 3'd7;
        shift_reg  <= '0;
        rx_byte    <= '0;
        doing_read <= 1'b0;
        status_r   <= '0;
    end else begin

        case (state)
        // ── IDLE ─────────────────────────────────────────────────────────
        ST_IDLE: begin
            scl_out <= 1'b1;
            sda_out <= 1'b1;
            if (new_cmd) begin
                status_r[0] <= 1'b1;   // busy
                status_r[3] <= 1'b0;   // clear irq
                if (pwdata[0]) begin           // start
                    state   <= ST_START1;
                end else if (pwdata[3]) begin  // write
                    shift_reg  <= tx_byte;
                    bit_idx    <= 3'd7;
                    doing_read <= 1'b0;
                    state      <= ST_BIT_LO;
                end else if (pwdata[2]) begin  // read
                    bit_idx    <= 3'd7;
                    doing_read <= 1'b1;
                    state      <= ST_BIT_LO;
                end else if (pwdata[1]) begin  // stop
                    state <= ST_STOP1;
                end
            end else begin
                status_r[0] <= 1'b0;   // clear busy when truly idle
            end
        end

        // ── START condition ───────────────────────────────────────────────
        ST_START1: begin
            if (quarter_tick) begin
                scl_out <= 1'b1;
                sda_out <= 1'b0;   // SDA low while SCL high → START
                state   <= ST_START2;
            end
        end
        ST_START2: begin
            if (quarter_tick) begin
                scl_out     <= 1'b0;   // pull SCL low after start
                state       <= ST_IDLE;
                status_r[0] <= 1'b0;
                if (ctrl_r[1]) status_r[3] <= 1'b1;
            end
        end

        // ── STOP condition ────────────────────────────────────────────────
        ST_STOP1: begin
            if (quarter_tick) begin
                sda_out <= 1'b0;
                scl_out <= 1'b1;   // SCL goes high first
                state   <= ST_STOP2;
            end
        end
        ST_STOP2: begin
            if (quarter_tick) begin
                sda_out     <= 1'b1;  // SDA high while SCL high → STOP
                state       <= ST_IDLE;
                status_r[0] <= 1'b0;
                if (ctrl_r[1]) status_r[3] <= 1'b1;
            end
        end

        // ── Data bit: SCL low phase ────────────────────────────────────────
        ST_BIT_LO: begin
            scl_out <= 1'b0;
            sda_out <= doing_read ? 1'b1 : shift_reg[7];  // release for RX
            if (quarter_tick) state <= ST_BIT_HI;
        end

        // ── Data bit: SCL high phase (clock stretch via stretch signal) ────
        ST_BIT_HI: begin
            scl_out <= 1'b1;
            // When stretch=1, clk_cnt is frozen → quarter_tick won't fire
            // Act only when SCL is released by slave
            if (quarter_tick && scl_i) begin
                // Arbitration: we sent 1 (released SDA) but bus is low (another master wins)
                if (!doing_read && shift_reg[7] && !sda_i) begin
                    status_r[1] <= 1'b1;  // arbitration lost
                    state       <= ST_IDLE;
                    status_r[0] <= 1'b0;
                    if (ctrl_r[1]) status_r[3] <= 1'b1;
                end else begin
                    // Sample for RX
                    if (doing_read)
                        shift_reg <= {shift_reg[6:0], sda_i};

                    if (bit_idx == 3'd0) begin
                        // Byte complete
                        if (!doing_read) begin
                            state <= ST_RACK1;   // TX done → receive ACK
                        end else begin
                            rx_byte <= {shift_reg[6:0], sda_i};
                            state   <= ST_SACK1; // RX done → send ACK
                        end
                    end else begin
                        bit_idx <= bit_idx - 3'd1;
                        state   <= ST_BIT_LO;
                    end
                end
            end
        end

        // ── Receive ACK from slave ─────────────────────────────────────────
        ST_RACK1: begin
            scl_out <= 1'b0;
            sda_out <= 1'b1;    // release SDA
            if (quarter_tick) state <= ST_RACK2;
        end
        ST_RACK2: begin
            scl_out <= 1'b1;
            // stretch handled by clk_cnt freeze via stretch signal
            if (quarter_tick && scl_i) begin
                status_r[2] <= sda_i;   // 0=ACK, 1=NACK
                scl_out     <= 1'b0;
                state       <= ST_IDLE;
                status_r[0] <= 1'b0;
                if (ctrl_r[1]) status_r[3] <= 1'b1;
            end
        end

        // ── Send ACK to slave ──────────────────────────────────────────────
        ST_SACK1: begin
            scl_out <= 1'b0;
            sda_out <= cmd_mack;  // 0=ACK, 1=NACK
            if (quarter_tick) state <= ST_SACK2;
        end
        ST_SACK2: begin
            scl_out <= 1'b1;
            if (quarter_tick) begin
                scl_out     <= 1'b0;
                state       <= ST_IDLE;
                status_r[0] <= 1'b0;
                if (ctrl_r[1]) status_r[3] <= 1'b1;
            end
        end

        default: state <= ST_IDLE;
        endcase
    end
end

endmodule
