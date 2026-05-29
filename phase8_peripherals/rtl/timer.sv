`timescale 1ns/1ps

// 64-bit free-running timer with compare register, APB slave.
// Implements the RISC-V MTIME / MTIMECMP layout (required for FreeRTOS tick).
//
// Register map (byte offsets from base address 0x1000_2000):
//   0x00  MTIME_LO     mtime[31:0]  — read-only
//   0x04  MTIME_HI     mtime[63:32] — read-only
//   0x08  MTIMECMP_LO  mtimecmp[31:0]
//   0x0C  MTIMECMP_HI  mtimecmp[63:32]
//   0x10  CTRL         [0]=enable  [1]=irq_en
//
// mtip asserts when ctrl[1] && ctrl[0] && mtime >= mtimecmp.
// Write MTIMECMP to a future value to re-arm the interrupt.

module timer (
    input  logic        clk,
    input  logic        rst_n,

    // APB slave
    input  logic [11:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,

    // Timer interrupt pending
    output logic        mtip
);

    // -------------------------------------------------------------------------
    // Icarus: extract bit-selects of paddr
    // -------------------------------------------------------------------------
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    // -------------------------------------------------------------------------
    // Registers
    // -------------------------------------------------------------------------
    logic [63:0] mtime;
    logic [63:0] mtimecmp;
    logic [1:0]  ctrl;  // [0]=enable [1]=irq_en

    // Compare: mtime >= mtimecmp (unsigned 64-bit)
    logic cmp_ge;
    assign cmp_ge = (mtime >= mtimecmp);
    assign mtip   = ctrl[1] & ctrl[0] & cmp_ge;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mtime    <= 64'd0;
            mtimecmp <= 64'hFFFF_FFFF_FFFF_FFFF;  // disabled by default (max value)
            ctrl     <= 2'b00;
        end else begin
            // Free-running counter when enabled
            if (ctrl[0])
                mtime <= mtime + 64'd1;

            // APB writes
            if (psel && penable && pwrite) begin
                case (apb_addr)
                    8'h08: mtimecmp[31:0]  <= pwdata;
                    8'h0C: mtimecmp[63:32] <= pwdata;
                    8'h10: ctrl            <= pwdata[1:0];
                endcase
            end
        end
    end

    // -------------------------------------------------------------------------
    // APB read
    // -------------------------------------------------------------------------
    always_comb begin
        case (apb_addr)
            8'h00:   prdata = mtime[31:0];
            8'h04:   prdata = mtime[63:32];
            8'h08:   prdata = mtimecmp[31:0];
            8'h0C:   prdata = mtimecmp[63:32];
            8'h10:   prdata = {30'b0, ctrl};
            default: prdata = 32'b0;
        endcase
    end

    assign pready = 1'b1;

endmodule
