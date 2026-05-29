# RISC-V AI SoC — Phase 7 Onwards: FPGA Deployment + AI Platform Blueprint

**Continuation of `SoC_Blueprint_FromScratch` — Phases 7 through 12**

```
Current state (Phases 1–6 complete):
RV32I Core → L1 Cache → AXI4 Crossbar → 4×4 Systolic Array → Full SoC → GDSII

Target state (Phases 7–12):
Portable FPGA SoC · 16×16 INT8 Accelerator · DDR3 Memory · Full Peripheral Suite
· GCC Toolchain · FreeRTOS · Python→Hardware Inference Pipeline
```

---

## What You Are Building

A production-grade, multi-board FPGA AI SoC that students can deploy on hardware they
already own (Basys3, Nexys A7, Arty A7, DE1-SoC) and use as a platform for real AI
projects — not just exercises.

**What makes this SoC worth choosing over alternatives (PicoRV32, VexRiscv, Rocket):**

| Feature | PicoRV32 | VexRiscv | Rocket Chip | This SoC |
|---------|----------|----------|-------------|----------|
| L1 cache | No | Optional | Yes | **Yes** |
| AI accelerator | No | No | No | **16×16 INT8** |
| Plain SystemVerilog | Yes | No (SpinalHDL) | No (Chisel) | **Yes** |
| Multi-board support | Yes | Yes | No | **Yes** |
| Full software stack | No | Partial | Partial | **Yes** |

No other open-source student RISC-V SoC combines an L1 cache with an INT8 AI
accelerator in plain synthesizable SystemVerilog. That is the differentiator.

---

## Master Timeline — Phases 7–12

| Phase | Focus | Duration |
|-------|-------|----------|
| 7 | FPGA portability · M extension · GCC toolchain | 3 weeks |
| 8 | Peripheral suite: UART · GPIO · Timer · SPI · CLINT · PLIC | 3 weeks |
| 9 | 16×16 INT8 accelerator · 128-bit scratchpad · DMA engine | 4 weeks |
| 10 | DDR3 memory interface · multi-board BSP · constraint files | 3 weeks |
| 11 | FreeRTOS · C inference library · Python quantization tool | 3 weeks |
| 12 | Multi-board validation · benchmarks · example projects | 2 weeks |

**Total: ~18 weeks**

---

## Design Principle — Portable Core, Thin Board Wrapper

Every board-specific detail lives in a single wrapper file. The SoC core never changes.

```
fpga_top_nexys_a7_100t.sv  ┐
fpga_top_nexys_a7_50t.sv   ├──→  soc_top.sv  (100% portable, never changes)
fpga_top_arty_a7_100t.sv   ┘
fpga_top_de1_soc.sv
```

The wrapper provides: PLL/MMCM, pin assignments, DDR3 MIG instantiation, reset
synchronizer. Everything else is in the portable core.

---

## PHASE 7 — FPGA Portability · M Extension · GCC Toolchain
### ⏱ Weeks 1–3

The SoC currently runs correctly in simulation. Phase 7 makes it run correctly on
real FPGA hardware across multiple boards, and makes it programmable in C.

Without this phase, you have a simulation toy. After this phase you have hardware.

---

### Week 1 — FPGA Portability Fixes

#### 7.1 BRAM Inference Audit

Every memory in the design must infer FPGA block RAM, not distributed LUT RAM.
LUT-based memories waste 10–30× more resources and fail timing at higher frequencies.

Audit every `logic [N:0] mem [0:M]` array in:
- `cache_tag_array.sv`
- `cache_data_array.sv`
- `axi_sram.sv`
- `instr_rom.sv`

Each must follow this exact pattern — single always_ff for write, separate always_ff or
assign for read-first or write-first behaviour:

```systemverilog
// BRAM inference pattern — works on Xilinx, Intel, Lattice
logic [31:0] mem [0:2047];
logic [31:0] rd_data;

always_ff @(posedge clk) begin
    if (we) mem[addr] <= wr_data;
    rd_data <= mem[addr];          // registered read = BRAM
end
```

Do NOT use async reads (`assign rd_data = mem[addr]`) — this forces LUT RAM.

#### 7.2 Reset Synchronizer

Async reset inputs cause metastability on FPGA. Every board's reset button is
asynchronous. Fix once in the FPGA wrapper — the core never sees an async reset.

```systemverilog
// fpga_top_*.sv — reset synchronizer (2-FF)
logic rst_sync_0, rst_n_sync;
always_ff @(posedge clk or negedge rst_btn_n) begin
    if (!rst_btn_n) {rst_n_sync, rst_sync_0} <= 2'b00;
    else            {rst_n_sync, rst_sync_0} <= {rst_sync_0, 1'b1};
end
// pass rst_n_sync into soc_top
```

#### 7.3 FPGA Top-Level Wrapper (one per board)

Create `fpga/` folder. One wrapper file per supported board:

```
fpga/
├── fpga_top_nexys_a7_50t.sv       ← Nexys A7-50T  (XC7A50T)
├── fpga_top_nexys_a7_100t.sv      ← Nexys A7-100T (XC7A100T)
├── fpga_top_arty_a7_100t.sv       ← Arty A7-100T  (XC7A100T)
├── nexys_a7_50t.xdc               ← pin constraints
├── nexys_a7_100t.xdc              ← pin constraints
└── arty_a7_100t.xdc               ← pin constraints
```

Each wrapper instantiates:
- **MMCM/PLL** — generates clean 100 MHz internal clock from board oscillator
- **Reset synchronizer** — as above
- **soc_top** — the portable core
- **Pin assignments** — UART, LEDs, buttons, PMOD headers

Constraint file minimum (Nexys A7 example):

```tcl
# nexys_a7_100t.xdc
set_property PACKAGE_PIN E3 [get_ports clk_100mhz]
set_property IOSTANDARD LVCMOS33 [get_ports clk_100mhz]
create_clock -period 10.000 [get_ports clk_100mhz]

set_property PACKAGE_PIN C12 [get_ports rst_btn_n]
set_property PACKAGE_PIN D10 [get_ports uart_tx]
set_property PACKAGE_PIN A9  [get_ports uart_rx]
```

#### 7.4 Expand Data SRAM to 64 KB

Change `axi_sram.sv` depth parameter from 512 to 16384 words (64 KB).
On Nexys A7, this maps to 8 BRAM36 blocks — 6% of the 135 available. Trivial cost.

---

### Week 2 — RV32IM: Hardware Multiply/Divide (M Extension)

The base RV32I has no `MUL` instruction. GCC emits 30–50 cycle software routines for
every multiply. Every AI calculation — dot products, quantization scaling, activation
normalization — uses multiply. Without M extension the CPU is the bottleneck even with
the accelerator running.

M extension adds 8 instructions: `MUL MULH MULHSU MULHU DIV DIVU REM REMU`

#### Where to add it — `execute_stage.sv`

Add a multiply/divide unit in the execute stage, alongside the ALU:

```systemverilog
// execute_stage.sv — add inside always_comb
logic signed  [31:0] mul_a, mul_b;
logic signed  [63:0] mul_result_64;
logic [31:0] mul_result;

assign mul_a = $signed(rs1_fwd);
assign mul_b = $signed(rs2_fwd);
assign mul_result_64 = mul_a * mul_b;

always_comb begin
    case (funct3)
        3'b000: mul_result = mul_result_64[31:0];   // MUL
        3'b001: mul_result = mul_result_64[63:32];  // MULH
        3'b011: mul_result = $unsigned(rs1_fwd) *   // MULHU
                             $unsigned(rs2_fwd) >> 32;
        default: mul_result = 32'b0;
    endcase
end
```

Division is slower — implement as iterative (32-cycle) or use a single-cycle approximation.
For student projects, 32-cycle divider is acceptable. Add a stall signal from the divider
to the hazard unit while division completes.

Vivado maps 32×32 multipliers directly to DSP48E1 slices (2 DSPs per multiply).

#### Decode changes

Add new opcode `7'b0110011` with `funct7 = 7'b0000001` to `decode_stage.sv`:
generate `is_mext = 1` control signal, route to execute stage multiplier select.

---

### Week 3 — GCC Toolchain Support

Without this, students cannot write C programs. This is the most important usability
gate in the entire project.

#### 3a — Linker Script `sw/linker.ld`

```ld
MEMORY {
    ROM  (rx)  : ORIGIN = 0x00000000, LENGTH = 4K
    RAM  (rwx) : ORIGIN = 0x00010000, LENGTH = 60K
}

SECTIONS {
    .text  : { *(.text.start) *(.text*) } > ROM
    .data  : { *(.data*) }                > RAM AT > ROM
    .bss   : { *(.bss*) *(COMMON) }      > RAM
    .stack : { . = ALIGN(16); . += 2K; } > RAM
}
```

#### 3b — Startup File `sw/crt0.S`

```asm
.section .text.start
.global _start
_start:
    la   sp, _stack_top       # set stack pointer
    la   a0, _bss_start
    la   a1, _bss_end
1:  bge  a0, a1, 2f
    sw   zero, 0(a0)          # zero BSS
    addi a0, a0, 4
    j    1b
2:  call main                 # call C main()
    j    .                    # halt if main returns
```

#### 3c — Compile command

```bash
riscv32-unknown-elf-gcc \
    -march=rv32im -mabi=ilp32 \
    -nostartfiles -nostdlib \
    -T sw/linker.ld \
    sw/crt0.S sw/main.c \
    -o firmware.elf

riscv32-unknown-elf-objcopy -O ihex firmware.elf firmware.hex
```

Verify the hex file loads into `instr_rom.sv` correctly — run the existing SoC
testbench with a simple C program that writes a value to a known address.

---

### Phase 7 Completion Checklist

```
☐ All memories infer BRAM — confirmed in Vivado synthesis report (no LUTRAM warnings)
☐ Reset synchronizer in all FPGA wrappers — no timing violations on reset path
☐ fpga_top_nexys_a7_50t.sv synthesizes cleanly in Vivado — no critical warnings
☐ fpga_top_nexys_a7_100t.sv synthesizes cleanly
☐ Constraint files: clock, reset, UART pins assigned on both boards
☐ Bitstream generated and loaded onto physical Nexys A7 — LED blinks with firmware
☐ M extension: MUL, MULH, DIV instructions produce correct results — cocotb test passes
☐ Hazard unit handles multi-cycle divide stall correctly
☐ linker.ld + crt0.S: "Hello World" C program compiles and runs on hardware
☐ C program output visible (LED pattern or UART — UART added Phase 8)
```

✅ **Resume Bullet**
> Extended RV32I SoC with M extension (hardware multiply/divide, DSP48E1-mapped) and
> ported to FPGA with vendor-neutral RTL, MMCM clock generation, and synchronous reset.
> Verified bitstream on Nexys A7-100T. GCC toolchain (linker script + crt0) enables
> C programming on bare metal.

🎯 **Interview Questions**
- Why does hardware multiply matter for AI workloads?
- What is the difference between synchronous and asynchronous reset, and why does FPGA care?
- What is a linker script and what does it control?
- How does BRAM inference work in Vivado? What pattern forces it?
- What is a pipeline stall and how does your hazard unit handle a multi-cycle operation?

---

## PHASE 8 — Peripheral Suite: UART · GPIO · Timer · SPI · CLINT · PLIC
### ⏱ Weeks 4–6

Without peripherals, firmware cannot communicate with the outside world. This phase
adds every peripheral students need for real projects. All peripherals are APB slaves —
they plug directly into the existing AXI-APB bridge.

---

### APB Peripheral Template

Every peripheral follows the same shell — copy this, fill in the registers:

```systemverilog
module uart (  // replace with gpio, timer, spi
    input  logic        clk, rst_n,
    // APB slave interface
    input  logic [11:0] paddr,
    input  logic        psel, penable, pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,
    // peripheral I/O
    output logic        tx,
    input  logic        rx
);
    assign pready = 1'b1;   // single-cycle APB (extend if needed)

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            /* reset all registers */
        end else if (psel && penable && pwrite) begin
            case (paddr[7:0])
                8'h00: /* write reg 0 */ ;
                8'h04: /* write reg 1 */ ;
            endcase
        end
    end

    always_comb begin
        case (paddr[7:0])
            8'h00: prdata = /* reg 0 */;
            8'h08: prdata = /* status */;
            default: prdata = 32'b0;
        endcase
    end
endmodule
```

---

### 8.1 UART — `rtl/uart.sv`

**Register map (base address 0x1000_0000):**

| Offset | Name | Description |
|--------|------|-------------|
| 0x00 | TXDATA | Write byte to transmit (bit 8 = full flag) |
| 0x04 | RXDATA | Read byte received (bit 31 = valid flag) |
| 0x08 | STATUS | [0]=tx_empty [1]=rx_valid |
| 0x0C | BAUD | Divisor register (default: 100MHz/115200 = 868) |

Implement 8N1 UART: 8 data bits, no parity, 1 stop bit.
TX FIFO depth: 16 bytes. RX FIFO depth: 16 bytes.

This is the first peripheral to implement. Every subsequent test uses UART for output.

### 8.2 GPIO — `rtl/gpio.sv`

**Register map (base 0x1000_1000):**

| Offset | Name | Description |
|--------|------|-------------|
| 0x00 | DATA | Read: input pins. Write: output pins |
| 0x04 | DIR | Direction: 1=output, 0=input (per bit) |
| 0x08 | IEN | Interrupt enable per pin |
| 0x0C | ISTAT | Interrupt status (write 1 to clear) |

16-bit wide. Maps to LEDs (output) and buttons/switches (input) on FPGA board.

### 8.3 Timer — `rtl/timer.sv`

**Register map (base 0x1000_2000):**

| Offset | Name | Description |
|--------|------|-------------|
| 0x00 | MTIME_LO | 64-bit counter, low 32 bits (read-only) |
| 0x04 | MTIME_HI | 64-bit counter, high 32 bits (read-only) |
| 0x08 | MTIMECMP_LO | Compare value, low 32 bits |
| 0x0C | MTIMECMP_HI | Compare value, high 32 bits |
| 0x10 | CTRL | [0]=enable [1]=interrupt enable |

Free-running 64-bit counter. Interrupt fires when MTIME ≥ MTIMECMP.

> ⚠️ **Common Mistake** — Use the RISC-V privileged spec MTIME/MTIMECMP layout
> exactly as above. FreeRTOS and other RTOS ports expect this specific register layout.

### 8.4 SPI Master — `rtl/spi.sv`

**Register map (base 0x1000_3000):**

| Offset | Name | Description |
|--------|------|-------------|
| 0x00 | DATA | Write to transmit byte, read for received byte |
| 0x04 | CTRL | [0]=busy [1]=cpol [2]=cpha [7:3]=clk_div[4:0] |
| 0x08 | CS | Chip select (active low, one-hot per slave) |

Full-duplex 8-bit SPI master. `clk_div` field divides system clock: SPI clock = sysclk / (2 × clk_div).
Connects: SD cards, OLED displays, IMUs (MPU6050 on SPI mode), ADCs.

### 8.5 CLINT — `rtl/clint.sv`

Core Local Interruptor. Required for FreeRTOS tick.

Exposes the RISC-V standard timer interrupt (`mtip`) and software interrupt (`msip`)
signals directly to the CPU's interrupt input pins. Mirrors the timer registers from
`timer.sv` at the standard CLINT memory-mapped address so RISC-V software can find them.

Connect `mtip` to the CPU's `m_timer_irq` input. Add interrupt handling to the CPU:
- CSR registers: `mstatus`, `mie`, `mip`, `mepc`, `mcause`, `mtvec`
- When interrupt fires: save PC to `mepc`, jump to `mtvec`, set `mcause`
- `mret` instruction: restore `mepc` to PC, re-enable interrupts

> ⚠️ **Common Mistake** — Do not implement the full privileged spec. Implement only
> M-mode. Students don't need S-mode or U-mode for bare-metal or FreeRTOS projects.
> Adding them adds months of work and zero benefit at this stage.

### 8.6 PLIC — `rtl/plic.sv`

Platform-Level Interrupt Controller. Routes 8 peripheral interrupt sources to the CPU.

**Sources:**
```
0 — UART RX ready
1 — UART TX empty
2 — GPIO edge detect
3 — Timer compare match
4 — SPI transaction complete
5 — DMA channel 0 done    (Phase 9)
6 — DMA channel 1 done    (Phase 9)
7 — Reserved
```

Registers (base 0x0C00_0000 — standard RISC-V PLIC base):
- Priority registers (one per source)
- Pending register
- Enable register
- Claim/complete register

PLIC output connects to CPU's `m_ext_irq` input.

---

### 8.7 Updated Memory Map

```
0x0000_0000 – 0x0000_0FFF   Instruction ROM (4 KB)
0x0001_0000 – 0x0001_FFFF   Data SRAM (64 KB)
0x1000_0000 – 0x1000_00FF   UART
0x1000_1000 – 0x1000_10FF   GPIO
0x1000_2000 – 0x1000_20FF   Timer / CLINT
0x1000_3000 – 0x1000_30FF   SPI
0x0C00_0000 – 0x0C00_FFFF   PLIC
0x5000_0000 – 0x5FFF_FFFF   AI Accelerator (Phase 9)
0x8000_0000 – 0x8FFF_FFFF   DDR3 / External Memory (Phase 10)
```

### 8.8 C Hardware Abstraction Layer — `sw/hal/`

Write a thin C library so students use function calls, not register addresses:

```c
// hal/uart.h
void uart_init(uint32_t baud);
void uart_putc(char c);
char uart_getc(void);
void uart_puts(const char *s);
int  uart_printf(const char *fmt, ...);  // basic printf subset

// hal/gpio.h
void gpio_set_dir(uint16_t pin_mask, uint16_t dir_mask);
void gpio_write(uint16_t val);
uint16_t gpio_read(void);

// hal/timer.h
void     timer_init(uint32_t period_us);
void     timer_delay_ms(uint32_t ms);
uint64_t timer_get_ticks(void);

// hal/spi.h
void    spi_init(uint8_t clk_div, uint8_t mode);
uint8_t spi_transfer(uint8_t cs, uint8_t data);
```

---

### Phase 8 Completion Checklist

```
☐ UART: transmit and receive verified on hardware — terminal shows output
☐ GPIO: LEDs toggle from firmware, button presses read correctly
☐ Timer: 1-second periodic interrupt fires — LED blinks at 1 Hz
☐ SPI: byte transfer to a PMOD device (e.g. SPI flash or test loopback)
☐ CLINT: timer interrupt reaches CPU correctly — ISR executes
☐ PLIC: two simultaneous interrupt sources handled in correct priority order
☐ CSR registers: mtvec, mepc, mcause, mstatus, mie, mip implemented in CPU
☐ mret instruction executes correctly — context restore verified
☐ HAL library: uart_printf works — "Hello World" prints over UART to PC terminal
☐ All peripherals verified on physical Nexys A7 hardware
```

✅ **Resume Bullet**
> Implemented full peripheral suite (UART, GPIO, Timer, SPI, CLINT, PLIC) as APB
> slaves on RISC-V SoC. Added M-mode interrupt handling (CSR registers, trap vector,
> mret). HAL library provides clean C API. Verified on Nexys A7 — timer-driven LED
> blink and UART printf both functional on hardware.

🎯 **Interview Questions**
- What is the difference between polling and interrupt-driven I/O?
- What is the purpose of the mtvec register?
- What happens at the hardware level when an interrupt fires on a RISC-V core?
- What is PLIC and how does it differ from CLINT?
- Why does SPI need a clock divisor register?

---

## PHASE 9 — 16×16 INT8 Accelerator · 128-bit Scratchpad · DMA Engine
### ⏱ Weeks 7–10

The existing 4×4 accelerator is functional but too small for real AI projects.
This phase replaces it with a 16×16 parametric array that handles real inference
workloads, backed by a wide scratchpad memory and a DMA engine that feeds it without
CPU involvement.

---

### 9.1 Parametric Systolic Array — `rtl/systolic_array.sv`

The PE (`pe.sv`) already uses INT8 — it does not change at all.
Replace the hardcoded 4×4 instantiation with `generate` loops:

```systemverilog
module systolic_array #(
    parameter N = 16   // array dimension: 8 for small boards, 16 for 100T-class
)(
    input  logic              clk, rst_n,
    input  logic [N*8-1:0]    w_row [0:N-1],   // N weights per row, packed
    input  logic [7:0]        a_feed [0:N-1],  // N staggered activation feeds
    output logic [31:0]       y_out  [0:N-1]   // N accumulated outputs
);
    // Partial sum wires: ps[row][col]
    logic [31:0] ps [0:N][0:N-1];

    // Top row receives zero partial sum
    genvar r, c;
    generate
        for (r = 0; r < N; r++) begin : row
            assign ps[0][r] = 32'b0;            // zero feed into first row
            for (c = 0; c < N; c++) begin : col
                pe u_pe (
                    .clk   (clk),
                    .rst_n (rst_n),
                    .w_in  (w_row[r][c*8 +: 8]),
                    .a_in  (a_feed[r]),
                    .p_in  (ps[r][c]),
                    .p_out (ps[r+1][c])
                );
            end
        end
    endgenerate

    // Bottom row outputs
    generate
        for (c = 0; c < N; c++) begin : out
            assign y_out[c] = ps[N][c];
        end
    endgenerate
endmodule
```

To change array size: set `N = 8` for Basys3/Nexys50T, `N = 16` for Nexys100T/Arty100T.

> 💡 **Tip** — In Vivado, `N = 16` maps 256 PEs to DSP48E1 slices automatically.
> The XC7A100T has 240 DSPs; the 16 overflow PEs use LUT multipliers — functionally
> identical, with negligible timing impact at 100 MHz.

### 9.2 128 KB Scratchpad with 128-bit Internal Bus — `rtl/scratchpad.sv`

The scratchpad is the key to feeding a 16×16 array at full speed. A 16×16 array
consumes 16 INT8 activations per cycle = 16 bytes/cycle = 1.6 GB/s at 100 MHz.
A 32-bit AXI bus delivers 400 MB/s — 4× too slow to keep the array fed.

Solution: 4 BRAM banks in parallel, each 32-bit wide, providing 128-bit/cycle read.

```systemverilog
module scratchpad #(
    parameter DEPTH = 32768  // 128 KB / 4 bytes per word
)(
    input  logic        clk,
    // AXI4 slave port — for DMA/CPU writes (32-bit)
    input  logic [14:0] axi_addr,
    input  logic [31:0] axi_wdata,
    input  logic        axi_we,
    // 128-bit read port — direct to accelerator
    input  logic [12:0] accel_addr,     // word-aligned, 16-byte stride
    output logic [127:0] accel_rdata   // 16 bytes in one cycle
);
    // 4 banks, each DEPTH/4 deep × 32 bits wide
    logic [31:0] bank[0:3][0:DEPTH/4-1];
    // ... bank-interleaved read/write logic
endmodule
```

The accelerator reads 128 bits (16 INT8 activations) per cycle directly from scratchpad.
The DMA writes to scratchpad over the normal 32-bit AXI port.

### 9.3 Hardware ReLU and Layer Accumulation — `accel_top.sv`

Add a post-processing pipeline after the array outputs:

```systemverilog
// After each tile completes, accumulate partial sums across tiles
logic [31:0] accum [0:N-1];

always_ff @(posedge clk) begin
    if (start_tile)
        for (int i = 0; i < N; i++) accum[i] <= 32'b0;
    else if (tile_done)
        for (int i = 0; i < N; i++) accum[i] <= accum[i] + y_out[i];
end

// ReLU: max(0, x) — one comparator per output
logic [31:0] relu_out [0:N-1];
generate
    for (genvar i = 0; i < N; i++)
        assign relu_out[i] = accum[i][31] ? 32'b0 : accum[i]; // negative → 0
endgenerate
```

Firmware sets a control register to enable/disable ReLU per layer.

### 9.4 DMA Engine — `rtl/dma.sv`

Two-channel DMA: channel 0 for weight loading (DDR3 → scratchpad), channel 1
for activation loading (DDR3 → scratchpad ping-pong buffer).

**Register map (AXI slave, base 0x5100_0000):**

| Offset | Name | Description |
|--------|------|-------------|
| 0x00 | CH0_SRC | Source address (DDR3 or SRAM) |
| 0x04 | CH0_DST | Destination address (scratchpad) |
| 0x08 | CH0_LEN | Transfer length in bytes |
| 0x0C | CH0_CTRL | [0]=start [1]=done [2]=irq_enable |
| 0x10 | CH1_SRC | Channel 1 source |
| 0x14 | CH1_DST | Channel 1 destination |
| 0x18 | CH1_LEN | Channel 1 length |
| 0x1C | CH1_CTRL | Channel 1 control |

DMA engine is an AXI **master** — add it as Master 3 to the crossbar.
This requires expanding the crossbar from 3×3 to **5×4**:

```
Masters:  CPU imem | CPU dmem | (was accel) | DMA
Slaves:   SRAM     | APB      | Accelerator | Scratchpad | DDR3 (Phase 10)
```

Update `axi4_crossbar.sv` — the NxM is now parametric so this is a parameter change,
not a rewrite.

### 9.5 Updated Accelerator Firmware Flow

With DMA + scratchpad + ReLU, a full inference layer in firmware is now:

```c
// 1. Load weights into scratchpad (DMA, one-time per layer)
dma_transfer(CH0, ddr3_weight_addr, scratchpad_weight_base, weight_size);
dma_wait(CH0);

// 2. Load input activations (DMA, per inference)
dma_transfer(CH1, ddr3_input_addr, scratchpad_act_base, input_size);
dma_wait(CH1);

// 3. Configure and start accelerator
accel_write(ACCEL_ROWS,    input_rows);
accel_write(ACCEL_COLS,    output_cols);
accel_write(ACCEL_K,       inner_dim);
accel_write(ACCEL_CTRL,    ACCEL_START | ACCEL_RELU_EN);

// 4. Wait for done interrupt (or poll)
while (!accel_read(ACCEL_STATUS) & ACCEL_DONE);

// 5. Read results
accel_read_outputs(result_buffer, output_cols);
```

---

### Phase 9 Completion Checklist

```
☐ systolic_array.sv: N=8 and N=16 both synthesize — DSP count reported in Vivado
☐ N=16 on Nexys A7-100T: 240 DSP18s utilized, timing met at 100 MHz
☐ scratchpad.sv: 128-bit read port delivers 16 bytes/cycle — verified in simulation
☐ Hardware ReLU: negative outputs clamp to 0, positive pass through unchanged
☐ Accumulation: multi-tile matrix multiply produces same result as numpy reference
☐ DMA channel 0: 64 KB transfer completes, interrupt fires
☐ DMA channel 1: back-to-back transfers with ping-pong — no data corruption
☐ Crossbar expanded to 5×4 — all master/slave combinations route correctly
☐ Full layer inference: firmware runs one FC layer, output matches numpy golden model
☐ UVM testbench updated for 16×16 array — all existing tests pass
```

✅ **Resume Bullet**
> Upgraded 4×4 AI accelerator to parametric 16×16 INT8 systolic array (256 MACs,
> 25.6 GOPS at 100 MHz) with 128-bit-wide scratchpad SRAM for sustained data feed.
> Added 2-channel DMA engine and hardware ReLU. AXI4 crossbar expanded to 5×4.
> Full FC layer inference (784→128) verified against numpy golden model.

🎯 **Interview Questions**
- Why does a 16×16 array need a 128-bit data bus to achieve full throughput?
- What is a DMA engine and why is it faster than CPU-driven data movement?
- How does weight-stationary dataflow work in a systolic array?
- What is the difference between scratchpad memory and cache?
- How does hardware ReLU save power compared to software ReLU?

---

## PHASE 10 — DDR3 Memory Interface · Multi-board BSP
### ⏱ Weeks 11–13

On-chip scratchpad holds 128 KB. A tiny MobileNet has 470 KB of weights. Without
external memory you cannot run real models. The Nexys A7 (both variants) has 128 MB
of DDR3L on board — Phase 10 connects it.

---

### 10.1 Abstract Memory Port Design

Do NOT instantiate Xilinx MIG directly in `soc_top.sv`. Instead define a generic
AXI4 memory slave interface at the SoC boundary and provide multiple backends:

```
soc_top.sv
└── axi_mem_port (AXI4 slave, 32-bit, 30-bit address)
        ↓
    [board wrapper selects:]
    mem_bram_backend.sv      — pure BRAM, 512 KB, any board, no DDR needed
    mem_ddr3_xilinx.sv       — wraps Xilinx MIG, Nexys A7 / Arty A7
    mem_ddr3_intel.sv        — wraps Intel EMIF, DE1-SoC (Phase 10 extension)
```

This means the SoC core compiles and runs on any board — boards without DDR3 use
the BRAM backend with reduced model size.

### 10.2 BRAM Backend — `mem_bram_backend.sv`

512 KB using 128 BRAM36 blocks. Covers the full Basys3 BRAM budget.
Any board can use this backend — no DDR controller needed.

Works for: MNIST MLP (100 KB weights), keyword spotting DS-CNN (100 KB weights).

### 10.3 DDR3 Xilinx Backend — `mem_ddr3_xilinx.sv`

Wraps Vivado's Memory Interface Generator (MIG) IP and exposes an AXI4 slave port
matching the abstract `axi_mem_port` interface:

```systemverilog
module mem_ddr3_xilinx (
    input  logic        clk_ref_200mhz,   // MIG needs 200 MHz reference
    input  logic        sys_rst_n,
    // AXI4 slave port to SoC
    axi4_if.slave       s_axi,
    // DDR3 physical pins (to board)
    output logic [14:0] ddr3_addr,
    output logic [2:0]  ddr3_ba,
    inout  logic [15:0] ddr3_dq,
    // ... all DDR3 pins
    output logic        init_calib_complete  // hold SoC in reset until DDR3 ready
);
    // Instantiate Vivado MIG IP here
    mig_7series_0 u_mig ( ... );
endmodule
```

> ⚠️ **Common Mistake** — DDR3 calibration takes ~10 ms on power-up. Hold `soc_rst_n`
> low until `init_calib_complete` goes high. If you release reset before calibration
> completes, every DDR3 access will return garbage.

> 💡 **Tip** — Generate the MIG IP in Vivado first, inspect its AXI port widths
> (MIG uses 128-bit AXI by default on 7-series). Add an AXI data width converter
> (Xilinx IP: `axi_dwidth_converter`) to bridge from the SoC's 32-bit AXI to MIG's
> 128-bit AXI. This is a standard pattern.

### 10.4 Board Support Packages

Create one constraint file and one wrapper per supported board:

```
fpga/
├── boards/
│   ├── nexys_a7_50t/
│   │   ├── fpga_top.sv          ← MMCM + DDR3 + reset sync + soc_top
│   │   ├── constraints.xdc      ← all pin assignments + timing
│   │   └── README.md            ← how to synthesize for this board
│   ├── nexys_a7_100t/
│   │   ├── fpga_top.sv
│   │   ├── constraints.xdc
│   │   └── README.md
│   └── arty_a7_100t/
│       ├── fpga_top.sv
│       ├── constraints.xdc
│       └── README.md
```

Each BSP README specifies: ARRAY_SIZE parameter, memory backend, expected resource
utilization, synthesis command.

### 10.5 Resource Utilization Targets

After Phase 10, synthesize all three boards and record:

| Board | ARRAY_SIZE | LUTs | DSPs | BRAM36 | Fmax |
|-------|-----------|------|------|--------|------|
| Nexys A7-50T | 8 | ~12K | 64 | 32 | ≥100 MHz |
| Nexys A7-100T | 16 | ~18K | 240 | 48 | ≥100 MHz |
| Arty A7-100T | 16 | ~18K | 240 | 48 | ≥100 MHz |

---

### Phase 10 Completion Checklist

```
☐ Abstract AXI memory port defined — soc_top.sv has no vendor primitives
☐ BRAM backend: 512 KB, synthesizes on Basys3 — verified in simulation
☐ DDR3 Xilinx backend: MIG calibration completes on Nexys A7-100T hardware
☐ AXI width converter: 32-bit SoC ↔ 128-bit MIG — no data corruption
☐ DDR3 read/write test: 1 MB sequential write then read-back — zero errors
☐ init_calib_complete reset interlock: SoC held in reset until DDR3 ready
☐ All three BSPs synthesize in Vivado without critical warnings
☐ Resource utilization within targets — recorded in docs/
☐ Firmware reads weight file from DDR3 and loads into scratchpad via DMA
```

✅ **Resume Bullet**
> Integrated 128 MB DDR3L via Xilinx MIG IP (AXI4, 128-bit) with portable SoC memory
> abstraction layer supporting BRAM and DDR3 backends. Implemented Board Support
> Packages for Nexys A7-50T/100T and Arty A7-100T. DDR3 calibration interlock prevents
> premature SoC operation. Verified 1 MB round-trip read/write on hardware.

🎯 **Interview Questions**
- What is a Memory Interface Generator and why is a calibration phase needed for DDR3?
- Why would you put an AXI data width converter between a 32-bit bus and a 128-bit memory?
- What is the purpose of abstracting the memory interface at the SoC boundary?
- How do you handle board-specific IP without polluting the portable RTL?

---

## PHASE 11 — FreeRTOS · C Inference Library · Python Quantization Tool
### ⏱ Weeks 14–16

Phase 11 is entirely software. The hardware is done. This phase makes the SoC
accessible to students who want to write AI applications without understanding AXI
protocol or systolic array timing.

---

### 11.1 FreeRTOS Port — `sw/freertos/`

FreeRTOS requires: timer tick interrupt, context switch (save/restore registers),
heap, and a minimal BSP. Your CLINT + M-mode interrupt support from Phase 8 provides
the hardware foundation.

**Files to create:**

```
sw/freertos/
├── port.c           ← context switch, interrupt entry/exit
├── port.h
├── portmacro.h      ← stack alignment, critical section macros
├── FreeRTOSConfig.h ← tick rate, heap size, max tasks
└── heap_4.c         ← FreeRTOS heap allocator (copy from FreeRTOS source)
```

**Tick interrupt handler in `port.c`:**

```c
void timer_irq_handler(void) {
    // reload timer compare for next tick
    uint64_t next = timer_get_mtime() + (SYSCLK_HZ / configTICK_RATE_HZ);
    timer_set_mtimecmp(next);

    // FreeRTOS tick — may trigger context switch
    if (xTaskIncrementTick() != pdFALSE)
        vTaskSwitchContext();
}
```

Verify FreeRTOS with a two-task demo: Task A blinks LED, Task B prints UART every
second. Both run concurrently — confirms context switch and timer tick work.

### 11.2 C Inference Library — `sw/nn/`

A thin C library that hides all accelerator complexity:

```c
// sw/nn/nn.h

typedef struct {
    uint32_t in_size;     // input dimension
    uint32_t out_size;    // output dimension
    int8_t  *weights;     // INT8 weight matrix (in_size × out_size)
    int32_t *bias;        // INT32 bias vector (out_size)
    uint8_t  relu;        // 1 = apply ReLU after this layer
} nn_layer_t;

// Load weights into DDR3 and scratchpad
void nn_load_weights(nn_layer_t *layer, const uint8_t *hex_data);

// Run one fully-connected layer through the accelerator
void nn_fc_forward(nn_layer_t *layer, int8_t *input, int32_t *output);

// Run ReLU quantize: clip INT32 accumulator to INT8 for next layer
void nn_requantize(int32_t *in, int8_t *out, int32_t scale, int32_t zero_point,
                   uint32_t len);

// Run a complete multi-layer network
void nn_forward(nn_layer_t *layers, int n_layers, int8_t *input, int32_t *output);
```

With this library, a student's MNIST inference program is:

```c
#include "nn.h"
#include "weights_mnist.h"    // generated by Python tool

nn_layer_t net[] = {
    {784, 128, w1, b1, 1},   // FC layer 1, ReLU
    {128,  10, w2, b2, 0},   // FC layer 2, no ReLU
};

int main(void) {
    uint8_t image[784] = { /* pixel data */ };
    int32_t logits[10];

    nn_forward(net, 2, image, logits);

    int predicted = argmax(logits, 10);
    uart_printf("Predicted digit: %d\n", predicted);
}
```

### 11.3 Python INT8 Quantization Tool — `tools/quantize.py`

Takes a trained PyTorch model and exports INT8 weight files the firmware can load.

```python
# tools/quantize.py
# Usage: python3 quantize.py --model mnist_model.pth --output weights_mnist.h

import torch, numpy as np, argparse

def quantize_tensor(t, bits=8):
    """Symmetric per-tensor quantization → INT8"""
    max_val = t.abs().max().item()
    scale   = max_val / (2**(bits-1) - 1)
    q = torch.clamp(torch.round(t / scale),
                    -(2**(bits-1)), 2**(bits-1)-1).to(torch.int8)
    return q.numpy(), scale

def export_layer(weight, bias, layer_idx, out_f):
    w_q, w_scale = quantize_tensor(weight)
    out_f.write(f"// Layer {layer_idx} weights\n")
    out_f.write(f"static const int8_t w{layer_idx}[] = {{\n")
    for val in w_q.flatten():
        out_f.write(f"  {int(val)},\n")
    out_f.write("};\n\n")
    # export bias as INT32
    out_f.write(f"static const int32_t b{layer_idx}[] = {{\n")
    for val in bias.detach().numpy():
        out_f.write(f"  {int(val / w_scale)},\n")
    out_f.write("};\n\n")
```

Workflow for students:
1. Train model in PyTorch/Keras on laptop
2. `python3 tools/quantize.py --model model.pth --output sw/weights.h`
3. Include `weights.h` in firmware, call `nn_forward()`
4. Flash bitstream + firmware to FPGA board
5. Run inference on real hardware

---

### Phase 11 Completion Checklist

```
☐ FreeRTOS port: two-task LED + UART demo runs on Nexys A7 hardware
☐ Context switch: verified under JTAG — task stacks intact after 1000 switches
☐ Timer tick: 1 ms tick verified with timer_get_ticks() — accurate to <1%
☐ nn_fc_forward: single layer output matches numpy reference — zero errors
☐ nn_forward: two-layer MNIST MLP on hardware matches PC softmax output
☐ quantize.py: PyTorch MNIST model → weights.h → firmware → hardware inference
☐ End-to-end demo: digit image → UART prints correct class — verified with 10 test images
☐ Inference latency: measured with timer_get_ticks() — documented in docs/
```

✅ **Resume Bullet**
> Ported FreeRTOS to custom RISC-V SoC (M-mode timer interrupt, context switch,
> heap). Implemented C inference library wrapping 16×16 INT8 systolic accelerator.
> Built Python INT8 post-training quantization tool (PyTorch → hex weights).
> End-to-end demo: MNIST digit classification on FPGA in under 10 ms.

🎯 **Interview Questions**
- What does a context switch save and restore?
- What is post-training quantization and what accuracy trade-off does INT8 impose?
- What is the difference between per-tensor and per-channel quantization?
- Why does requantization happen between layers?
- What is the role of the zero point in INT8 quantization?

---

## PHASE 12 — Multi-board Validation · Benchmarks · Example Projects
### ⏱ Weeks 17–18

Phase 12 validates the full system across all supported boards, measures real
performance numbers, and creates example projects that demonstrate the SoC's
capabilities. This is what students and researchers see first.

---

### 12.1 Multi-board Validation Matrix

Test the complete software stack on every supported board:

| Test | Nexys A7-50T | Nexys A7-100T | Arty A7-100T |
|------|-------------|--------------|-------------|
| Boot + UART hello | ✓ | ✓ | ✓ |
| GPIO LED blink | ✓ | ✓ | ✓ |
| Timer interrupt | ✓ | ✓ | ✓ |
| SPI PMOD device | ✓ | ✓ | ✓ |
| FreeRTOS 2-task | ✓ | ✓ | ✓ |
| MNIST inference (BRAM) | ✓ | ✓ | ✓ |
| MNIST inference (DDR3) | ✓ | ✓ | ✓ |
| CIFAR-10 CNN (DDR3) | — | ✓ | ✓ |
| Keyword spotting | ✓ | ✓ | ✓ |

### 12.2 Performance Benchmark Suite

Measure and document these numbers for the project README:

```c
// benchmark.c — run on hardware, print via UART
void bench_matmul(void) {
    uint64_t t0 = timer_get_ticks();
    nn_fc_forward(&layer_784_128, input, output);
    uint64_t t1 = timer_get_ticks();
    uart_printf("FC 784→128: %lu us\n", (t1-t0) / (SYSCLK_HZ/1000000));
}
```

Target numbers (Nexys A7-100T, N=16, 100 MHz):

| Operation | Target latency |
|-----------|---------------|
| FC 784→128 | < 5 ms |
| FC 128→10 | < 0.5 ms |
| MNIST 2-layer MLP | < 6 ms |
| Keyword spotting (DS-CNN) | < 15 ms |
| CIFAR-10 small CNN | < 80 ms |

### 12.3 Example Projects

Create three fully documented example projects in `examples/`:

**Example 1 — MNIST Digit Classifier** (`examples/mnist/`)
- 2-layer MLP: 784→128→10
- PyTorch training script included
- `quantize.py` exports weights
- Firmware reads digit from UART, returns prediction
- README with step-by-step instructions

**Example 2 — Keyword Spotter** (`examples/keyword_spotting/`)
- DS-CNN model trained on Google Speech Commands dataset (10 words)
- Audio features from an I2S microphone over SPI PMOD
- Real-time inference at 10 Hz
- LED shows detected keyword

**Example 3 — Anomaly Detector** (`examples/anomaly_detect/`)
- Autoencoder trained on normal vibration data (IMU over SPI)
- Reconstruction error threshold triggers GPIO alert
- FreeRTOS: one task for data collection, one for inference
- Demonstrates real industrial edge AI use case

---

### Phase 12 Completion Checklist

```
☐ All boards in validation matrix: every cell passes
☐ Benchmark numbers measured and documented in README
☐ Example 1 (MNIST): end-to-end reproducible from scratch — tested by running README
☐ Example 2 (Keyword): real-time inference on hardware with physical microphone
☐ Example 3 (Anomaly): FreeRTOS multi-task inference running on Nexys A7
☐ Synthesis reports for all three boards committed to docs/synth_reports/
☐ Resource utilization table in README
☐ Getting started guide: new user to running MNIST in under 30 minutes
```

✅ **Resume Bullet**
> Delivered multi-board RISC-V AI SoC platform targeting Nexys A7-50T/100T and
> Arty A7-100T. Features 16×16 INT8 systolic accelerator (25.6 GOPS), 128 MB DDR3,
> full peripheral suite, FreeRTOS, and Python→hardware inference pipeline.
> Three example projects: MNIST digit classifier, keyword spotter, anomaly detector.
> All verified on physical hardware.

---

## Complete Phase 7–12 File Manifest

```
soc/
├── fpga/
│   └── boards/
│       ├── nexys_a7_50t/     fpga_top.sv  constraints.xdc  README.md
│       ├── nexys_a7_100t/    fpga_top.sv  constraints.xdc  README.md
│       └── arty_a7_100t/     fpga_top.sv  constraints.xdc  README.md
│
├── phase7_fpga/
│   └── rtl/
│       └── mem_bram_backend.sv  mem_ddr3_xilinx.sv
│
├── phase8_peripherals/
│   └── rtl/
│       uart.sv  gpio.sv  timer.sv  spi.sv  clint.sv  plic.sv
│
├── phase9_accel_v2/
│   └── rtl/
│       systolic_array.sv (parametric N)
│       scratchpad.sv
│       dma.sv
│       accel_top.sv (updated controller)
│
├── sw/
│   ├── linker.ld
│   ├── crt0.S
│   ├── hal/
│   │   uart.h/c  gpio.h/c  timer.h/c  spi.h/c  accel.h/c
│   ├── freertos/
│   │   port.c  port.h  portmacro.h  FreeRTOSConfig.h  heap_4.c
│   └── nn/
│       nn.h/c
│
├── tools/
│   └── quantize.py
│
└── examples/
    ├── mnist/
    ├── keyword_spotting/
    └── anomaly_detect/
```

---

## Updated Phase Status Table

| Phase | Module | Status |
|-------|--------|--------|
| 0 | Environment + SystemVerilog basics | ✅ |
| 1 | 5-stage RV32I pipeline | ✅ |
| 2 | Direct-mapped write-back L1 cache | ✅ |
| 3 | AXI4 3×3 crossbar + AXI-APB bridge | ✅ |
| 4 | 4×4 systolic MAC array accelerator | ✅ |
| 5 | Full SoC integration | ✅ |
| 6 | OpenLane GDSII synthesis on Sky130A | ✅ |
| 7 | FPGA portability · M extension · GCC toolchain | ⏳ |
| 8 | Peripheral suite: UART · GPIO · Timer · SPI · CLINT · PLIC | ⏳ |
| 9 | 16×16 INT8 accelerator · 128-bit scratchpad · DMA | ⏳ |
| 10 | DDR3 memory · multi-board BSP | ⏳ |
| 11 | FreeRTOS · C inference library · Python quant tool | ⏳ |
| 12 | Multi-board validation · benchmarks · example projects | ⏳ |
