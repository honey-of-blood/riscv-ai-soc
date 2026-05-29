`timescale 1ns/1ps

// 16-bit GPIO with direction control, edge-detect interrupts, APB slave.
//
// Register map (byte offsets from base address 0x1000_1000):
//   0x00  DATA   R: synchronized input pins  W: output register
//   0x04  DIR    1=output, 0=input  (per bit)
//   0x08  IEN    interrupt enable per bit (any edge)
//   0x0C  ISTAT  interrupt status; write 1 to clear (W1C)

module gpio (
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

    // GPIO pins
    input  logic [15:0] gpio_in,    // raw input (from pads)
    output logic [15:0] gpio_out,   // output data register
    output logic [15:0] gpio_oe,    // output enable (1=drive pad)

    // Interrupt
    output logic        irq
);

    // -------------------------------------------------------------------------
    // Icarus: extract bit-select of paddr
    // -------------------------------------------------------------------------
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    // -------------------------------------------------------------------------
    // Registers
    // -------------------------------------------------------------------------
    logic [15:0] dir_r;    // 1=output
    logic [15:0] ien_r;    // interrupt enable
    logic [15:0] istat_r;  // interrupt status

    // 2-FF input synchronizer
    logic [15:0] in_s0, in_s1, in_prev;

    // Edge detect: any change on enabled input pins
    logic [15:0] edge_det;
    assign edge_det = (in_s1 ^ in_prev) & ~dir_r & ien_r;

    assign gpio_oe = dir_r;
    assign irq     = |istat_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            gpio_out <= 16'h0;
            dir_r    <= 16'h0;
            ien_r    <= 16'h0;
            istat_r  <= 16'h0;
            in_s0    <= 16'h0;
            in_s1    <= 16'h0;
            in_prev  <= 16'h0;
        end else begin
            // Synchronize inputs
            in_s0   <= gpio_in;
            in_s1   <= in_s0;
            in_prev <= in_s1;

            // Latch new edge-detect flags
            istat_r <= istat_r | edge_det;

            // APB writes
            if (psel && penable && pwrite) begin
                case (apb_addr)
                    8'h00: gpio_out <= pwdata[15:0];
                    8'h04: dir_r    <= pwdata[15:0];
                    8'h08: ien_r    <= pwdata[15:0];
                    8'h0C: istat_r  <= istat_r & ~pwdata[15:0]; // W1C
                endcase
            end
        end
    end

    // -------------------------------------------------------------------------
    // APB read
    // -------------------------------------------------------------------------
    always_comb begin
        case (apb_addr)
            8'h00:   prdata = {16'b0, in_s1};    // read synchronized inputs
            8'h04:   prdata = {16'b0, dir_r};
            8'h08:   prdata = {16'b0, ien_r};
            8'h0C:   prdata = {16'b0, istat_r};
            default: prdata = 32'b0;
        endcase
    end

    assign pready = 1'b1;

endmodule
