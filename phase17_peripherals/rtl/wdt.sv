`timescale 1ns/1ps
// Watchdog Timer (WDT) — APB slave, magic-value kick protection.
//
// APB register map (within sel=9, 0x1000_9xxx):
//   0x00 CTRL     [0]=enable  [1]=nmi_mode (1=NMI, 0=system reset)
//   0x04 TIMEOUT  countdown load value (clock cycles)
//   0x08 KICK     write magic sequence to reload counter:
//                   step 1: write 0x1ACCE551
//                   step 2: write 0xDEAD5AFE  → counter reloads
//                   any wrong value resets the unlock state
//   0x0C STATUS   [0]=timeout_flag (W1C)
//
// Outputs:
//   wdt_reset_o  — asserted one cycle when timeout fires in reset mode
//   wdt_nmi_o    — asserted one cycle when timeout fires in NMI mode
//
// Magic-value protection prevents accidental kicks from runaway code.
// The unlock state is cleared by any incorrect KICK write, not just after
// two correct writes.

module wdt (
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

    // WDT outputs
    output logic        wdt_reset_o,
    output logic        wdt_nmi_o
);

localparam MAGIC_STEP1 = 32'h1ACCE551;
localparam MAGIC_STEP2 = 32'hDEAD5AFE;

// Registers
logic        enable;
logic        nmi_mode;
logic [31:0] timeout_val;
logic [31:0] counter;
logic        timeout_flag;
logic        unlock_step;   // 1 after STEP1 written

logic apb_wr;
assign apb_wr = psel & penable & pwrite;
assign pready = 1'b1;

logic [3:0] apb_a;
assign apb_a = paddr[3:0];

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        enable       <= 1'b0;
        nmi_mode     <= 1'b0;
        timeout_val  <= 32'hFFFF_FFFF;
        counter      <= 32'hFFFF_FFFF;
        timeout_flag <= 1'b0;
        unlock_step  <= 1'b0;
        wdt_reset_o  <= 1'b0;
        wdt_nmi_o    <= 1'b0;
    end else begin
        // Default: clear one-cycle pulses
        wdt_reset_o <= 1'b0;
        wdt_nmi_o   <= 1'b0;

        // Counter decrement first (lower NBA priority)
        if (enable) begin
            if (counter == 32'd0) begin
                timeout_flag <= 1'b1;
                counter      <= timeout_val;
                if (nmi_mode)
                    wdt_nmi_o   <= 1'b1;
                else
                    wdt_reset_o <= 1'b1;
            end else begin
                counter <= counter - 32'd1;
            end
        end

        // APB writes second (higher NBA priority — last assignment wins)
        if (apb_wr) begin
            case (apb_a)
                4'h0: begin
                    enable   <= pwdata[0];
                    nmi_mode <= pwdata[1];
                end
                4'h4: begin
                    timeout_val <= pwdata;
                    counter     <= pwdata;  // immediate reload on timeout change
                end
                4'h8: begin
                    if (pwdata == MAGIC_STEP1) begin
                        unlock_step <= 1'b1;
                    end else if (unlock_step && pwdata == MAGIC_STEP2) begin
                        counter     <= timeout_val;   // reload
                        unlock_step <= 1'b0;
                    end else begin
                        unlock_step <= 1'b0;          // wrong value → lock
                    end
                end
                4'hC: begin
                    if (pwdata[0]) timeout_flag <= 1'b0;  // W1C
                end
                default: ;
            endcase
        end
    end
end

always_comb begin
    prdata = '0;
    case (apb_a)
        4'h0: prdata = {30'b0, nmi_mode, enable};
        4'h4: prdata = timeout_val;
        4'h8: prdata = {31'b0, unlock_step};
        4'hC: prdata = {31'b0, timeout_flag};
        default: prdata = '0;
    endcase
end

endmodule
