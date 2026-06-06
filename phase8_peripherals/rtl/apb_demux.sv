`timescale 1ns/1ps
// APB demux — fans one APB master to 12 peripheral slaves.
// Decode: paddr[15:12] selects the target slave.
//
// Address map (within 0x1000_xxxx AXI region):
//   sel=0  0x1000_0xxx  apb_regs  (generic register file — Phase 5 backward compat)
//   sel=1  0x1000_1xxx  UART
//   sel=2  0x1000_2xxx  GPIO
//   sel=3  0x1000_3xxx  Timer
//   sel=4  0x1000_4xxx  SPI
//   sel=5  0x1000_5xxx  CLINT
//   sel=6  0x1000_6xxx  PLIC
//   sel=7  0x1000_7xxx  DMA config (Phase 9)
//   sel=8  0x1000_8xxx  I2C master   (Phase 17)
//   sel=9  0x1000_9xxx  WDT          (Phase 17)
//   sel=10 0x1000_Axxx  TRNG         (Phase 17)
//   sel=11 0x1000_Bxxx  UART_DMA     (Phase 17)
module apb_demux (
    // From AXI-APB bridge
    input  logic [31:0] paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    input  logic  [3:0] pstrb,
    output logic [31:0] prdata,
    output logic        pready,
    output logic        pslverr,

    // Slave 0: apb_regs (generic)
    output logic [11:0] regs_paddr,
    output logic        regs_psel,
    output logic        regs_penable,
    output logic        regs_pwrite,
    output logic [31:0] regs_pwdata,
    input  logic [31:0] regs_prdata,
    input  logic        regs_pready,
    input  logic        regs_pslverr,

    // Slave 1: UART
    output logic [11:0] uart_paddr,
    output logic        uart_psel,
    output logic        uart_penable,
    output logic        uart_pwrite,
    output logic [31:0] uart_pwdata,
    input  logic [31:0] uart_prdata,
    input  logic        uart_pready,

    // Slave 2: GPIO
    output logic [11:0] gpio_paddr,
    output logic        gpio_psel,
    output logic        gpio_penable,
    output logic        gpio_pwrite,
    output logic [31:0] gpio_pwdata,
    input  logic [31:0] gpio_prdata,
    input  logic        gpio_pready,

    // Slave 3: Timer
    output logic [11:0] timer_paddr,
    output logic        timer_psel,
    output logic        timer_penable,
    output logic        timer_pwrite,
    output logic [31:0] timer_pwdata,
    input  logic [31:0] timer_prdata,
    input  logic        timer_pready,

    // Slave 4: SPI
    output logic [11:0] spi_paddr,
    output logic        spi_psel,
    output logic        spi_penable,
    output logic        spi_pwrite,
    output logic [31:0] spi_pwdata,
    input  logic [31:0] spi_prdata,
    input  logic        spi_pready,

    // Slave 5: CLINT
    output logic [11:0] clint_paddr,
    output logic        clint_psel,
    output logic        clint_penable,
    output logic        clint_pwrite,
    output logic [31:0] clint_pwdata,
    input  logic [31:0] clint_prdata,
    input  logic        clint_pready,

    // Slave 6: PLIC
    output logic [11:0] plic_paddr,
    output logic        plic_psel,
    output logic        plic_penable,
    output logic        plic_pwrite,
    output logic [31:0] plic_pwdata,
    input  logic [31:0] plic_prdata,
    input  logic        plic_pready,

    // Slave 7: DMA config (Phase 9)
    output logic [11:0] dma_paddr,
    output logic        dma_psel,
    output logic        dma_penable,
    output logic        dma_pwrite,
    output logic [31:0] dma_pwdata,
    input  logic [31:0] dma_prdata,
    input  logic        dma_pready,

    // Slave 8: I2C master (Phase 17)
    output logic [11:0] i2c_paddr,
    output logic        i2c_psel,
    output logic        i2c_penable,
    output logic        i2c_pwrite,
    output logic [31:0] i2c_pwdata,
    input  logic [31:0] i2c_prdata,
    input  logic        i2c_pready,

    // Slave 9: WDT (Phase 17)
    output logic [11:0] wdt_paddr,
    output logic        wdt_psel,
    output logic        wdt_penable,
    output logic        wdt_pwrite,
    output logic [31:0] wdt_pwdata,
    input  logic [31:0] wdt_prdata,
    input  logic        wdt_pready,

    // Slave 10: TRNG (Phase 17)
    output logic [11:0] trng_paddr,
    output logic        trng_psel,
    output logic        trng_penable,
    output logic        trng_pwrite,
    output logic [31:0] trng_pwdata,
    input  logic [31:0] trng_prdata,
    input  logic        trng_pready,

    // Slave 11: UART_DMA (Phase 17)
    output logic [11:0] uart_dma_paddr,
    output logic        uart_dma_psel,
    output logic        uart_dma_penable,
    output logic        uart_dma_pwrite,
    output logic [31:0] uart_dma_pwdata,
    input  logic [31:0] uart_dma_prdata,
    input  logic        uart_dma_pready
);

    // Address decode — bits [15:12] for slave select
    logic [3:0] sel;
    assign sel = paddr[15:12];

    logic [11:0] local_addr;
    assign local_addr = paddr[11:0];

    // psel gating: only the addressed slave sees psel=1
    assign regs_psel  = psel & (sel == 4'd0);
    assign uart_psel  = psel & (sel == 4'd1);
    assign gpio_psel  = psel & (sel == 4'd2);
    assign timer_psel = psel & (sel == 4'd3);
    assign spi_psel   = psel & (sel == 4'd4);
    assign clint_psel = psel & (sel == 4'd5);
    assign plic_psel  = psel & (sel == 4'd6);
    assign dma_psel      = psel & (sel == 4'd7);
    assign i2c_psel      = psel & (sel == 4'd8);
    assign wdt_psel      = psel & (sel == 4'd9);
    assign trng_psel     = psel & (sel == 4'd10);
    assign uart_dma_psel = psel & (sel == 4'd11);

    // Broadcast shared signals
    assign regs_paddr  = local_addr;  assign regs_penable  = penable;
    assign regs_pwrite = pwrite;      assign regs_pwdata   = pwdata;
    assign uart_paddr  = local_addr;  assign uart_penable  = penable;
    assign uart_pwrite = pwrite;      assign uart_pwdata   = pwdata;
    assign gpio_paddr  = local_addr;  assign gpio_penable  = penable;
    assign gpio_pwrite = pwrite;      assign gpio_pwdata   = pwdata;
    assign timer_paddr = local_addr;  assign timer_penable = penable;
    assign timer_pwrite = pwrite;     assign timer_pwdata  = pwdata;
    assign spi_paddr   = local_addr;  assign spi_penable   = penable;
    assign spi_pwrite  = pwrite;      assign spi_pwdata    = pwdata;
    assign clint_paddr = local_addr;  assign clint_penable = penable;
    assign clint_pwrite = pwrite;     assign clint_pwdata  = pwdata;
    assign plic_paddr  = local_addr;  assign plic_penable  = penable;
    assign plic_pwrite = pwrite;      assign plic_pwdata   = pwdata;
    assign dma_paddr      = local_addr;  assign dma_penable      = penable;
    assign dma_pwrite     = pwrite;      assign dma_pwdata       = pwdata;
    assign i2c_paddr      = local_addr;  assign i2c_penable      = penable;
    assign i2c_pwrite     = pwrite;      assign i2c_pwdata       = pwdata;
    assign wdt_paddr      = local_addr;  assign wdt_penable      = penable;
    assign wdt_pwrite     = pwrite;      assign wdt_pwdata       = pwdata;
    assign trng_paddr     = local_addr;  assign trng_penable     = penable;
    assign trng_pwrite    = pwrite;      assign trng_pwdata      = pwdata;
    assign uart_dma_paddr = local_addr;  assign uart_dma_penable = penable;
    assign uart_dma_pwrite = pwrite;     assign uart_dma_pwdata  = pwdata;

    // prdata / pready / pslverr mux
    always_comb begin
        prdata  = 32'b0;
        pready  = 1'b1;
        pslverr = 1'b0;
        case (sel)
            4'd0: begin prdata = regs_prdata;  pready = regs_pready;  pslverr = regs_pslverr; end
            4'd1: begin prdata = uart_prdata;  pready = uart_pready;  end
            4'd2: begin prdata = gpio_prdata;  pready = gpio_pready;  end
            4'd3: begin prdata = timer_prdata; pready = timer_pready; end
            4'd4: begin prdata = spi_prdata;   pready = spi_pready;   end
            4'd5: begin prdata = clint_prdata; pready = clint_pready; end
            4'd6: begin prdata = plic_prdata;  pready = plic_pready;  end
            4'd7:  begin prdata = dma_prdata;      pready = dma_pready;      end
            4'd8:  begin prdata = i2c_prdata;      pready = i2c_pready;      end
            4'd9:  begin prdata = wdt_prdata;      pready = wdt_pready;      end
            4'd10: begin prdata = trng_prdata;     pready = trng_pready;     end
            4'd11: begin prdata = uart_dma_prdata; pready = uart_dma_pready; end
            default: ;
        endcase
    end

endmodule
