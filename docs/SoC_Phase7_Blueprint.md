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

---

# PHASES 13–22: INDUSTRY-STANDARD UPGRADE ROADMAP

After Phase 12 you have a working SoC that boots FreeRTOS, runs inference, and closes timing on Artix-7.  
The phases below transform it from a capable portfolio project into a **professional-grade open SoC** that stands beside NEORV32, Ibex, and CV32E40P.

## Competitive Gap Summary

| Capability | This SoC (post-P12) | NEORV32 | Ibex | CV32E40P |
|------------|---------------------|---------|------|----------|
| RISC-V compliance suite | ❌ | ✅ | ✅ | ✅ |
| Compressed (RVC) | ❌ | ✅ | ✅ | ✅ |
| Atomics (RVA) | ❌ | partial | ✅ | ✅ |
| JTAG / OpenOCD | ❌ | ✅ | ✅ | ✅ |
| Hardware breakpoints | ❌ | ✅ | ✅ | ✅ |
| I-cache | ❌ | ✅ | ✅ | ✅ |
| Branch predictor | ❌ | ❌ | ❌ | ✅ |
| UART bootloader | ❌ | ✅ | — | — |
| newlib / libc | ❌ | ✅ | — | — |
| CI/CD pipeline | ❌ | ✅ | ✅ | ✅ |
| Formal verification | ❌ | ✅ | ✅ | ✅ |
| Zephyr / RTOS port | ❌ | ✅ | ✅ | — |
| AI operator library | ❌ | ❌ | ❌ | ❌ |
| INT4 / quantized AI | ❌ | ❌ | ❌ | ❌ |
| Security (AES/SHA) | ❌ | partial | ❌ | ❌ |
| PMP | ❌ | ✅ | ✅ | ✅ |

## Master Timeline (Phases 13–22)

| Phase | Topic | Duration |
|-------|-------|----------|
| 13 | ISA Completeness & Compliance | 4 weeks |
| 14 | Hardware Debug Infrastructure | 5 weeks |
| 15 | CPU Performance (I-cache, predictor, MUL) | 4 weeks |
| 16 | Firmware Development Stack | 3 weeks |
| 17 | Peripheral Completeness | 4 weeks |
| 18 | AI Accelerator v3 (INT4, DMA, operators) | 6 weeks |
| 19 | Security Subsystem | 4 weeks |
| 20 | SoC Architecture Hardening | 4 weeks |
| 21 | Production Verification | 5 weeks |
| 22 | Platform Portability & Ecosystem | 6 weeks |
| **Total** | | **~45 weeks** |

---

## PHASE 13 — ISA Completeness & Compliance

### ⏱ Weeks 1–4

After Phase 12 you have an RV32IM core that boots FreeRTOS and runs inference.  
However the core still fails the official RISC-V Architecture Compliance Tests (ACT) because it is missing compressed instructions (RVC), atomic instructions (RVA), the mandatory CSRs (`misa`, `mhartid`, `mcycle`, `minstret`), synchronous exception handling (illegal instruction, ECALL, EBREAK, misalign, PMP fault), and Physical Memory Protection.  
Without these, any GCC-compiled binary using `libgcc` or the Linux ABI will silently mis-execute.  
This phase locks down the ISA so the SoC passes the ACT reference suite — the same bar required for Linux-capable cores.

### 13.1 RVC — 16-bit Compressed Instruction Expansion

Insert a 32-bit expander in the fetch stage before the IF/ID register.  
The expander is purely combinational: it reads 16-bit parcels from the instruction bus and emits standard 32-bit encodings.

```systemverilog
// rtl/rvc_expander.sv
module rvc_expander (
    input  logic [31:0] raw_in,   // 32 bits fetched (may contain two 16-bit instrs)
    output logic [31:0] instr_o,  // expanded 32-bit instruction
    output logic        is_rvc_o  // 1 → was a 16-bit instr (PC += 2)
);
    // RVC detection: bits[1:0] != 2'b11
    assign is_rvc_o = (raw_in[1:0] != 2'b11);

    always_comb begin
        if (!is_rvc_o) begin
            instr_o = raw_in;  // already 32-bit
        end else begin
            unique case (raw_in[1:0])
                2'b00: /* Quadrant 0 */ begin /* C.ADDI4SPN, C.LW, C.SW … */ end
                2'b01: /* Quadrant 1 */ begin /* C.ADDI, C.JAL, C.LI … */    end
                2'b10: /* Quadrant 2 */ begin /* C.SLLI, C.LWSP, C.JR … */   end
                default: instr_o = 32'h0000_0013; // NOP on illegal
            endcase
        end
    end
endmodule
```

> ⚠️ **Common Mistake:** Forgetting that RVC requires 16-bit PC increments. Modify `fetch_stage.sv` to add `is_rvc ? 2 : 4` to PC, and make the compressed instruction buffer two-word wide so a misaligned 16-bit instruction spanning a cache line is handled correctly.

### 13.2 RVA — Atomic Instructions (LR/SC + AMO)

Atomics require a hardware reservation register and a single-cycle read-modify-write path to memory.  
LR/SC only needs a flag + address; the five AMO operations (AMOSWAP, AMOADD, AMOAND, AMOOR, AMOXOR) need a read-then-modify-then-write sequence gated by the memory stage.

```systemverilog
// Inside memory_stage.sv — reservation set
always_ff @(posedge clk) begin
    if (lr_valid_i) begin
        reservation_addr <= mem_addr_i;
        reservation_set  <= 1'b1;
    end else if (sc_valid_i) begin
        reservation_set  <= 1'b0;   // always clear on SC
    end
end

assign sc_success = reservation_set && (mem_addr_i == reservation_addr);
assign sc_result  = sc_success ? 32'd0 : 32'd1;  // 0=success, 1=fail (RISC-V spec)
```

### 13.3 Full CSR Bank

Implement the mandatory supervisor and machine-mode CSRs.  
Store all CSRs in a single `csr_file.sv` with a unified read/write port.

```systemverilog
// rtl/csr_file.sv  (key registers)
// misa   — advertise RV32IMAC
assign csr_misa = 32'h4014_1100;   // MXL=01(RV32), A+C+I+M bits

// mcycle / minstret — free-running counters
always_ff @(posedge clk) begin
    if (!rst_n)     mcycle <= 64'd0;
    else            mcycle <= mcycle + 64'd1;
    if (instr_commit) minstret <= minstret + 64'd1;
end

// mtval — captures bad address/instruction on exception
always_ff @(posedge clk) begin
    if (exception_valid) mtval <= exception_tval;
end
```

### 13.4 Synchronous Exception Handling

Exceptions are detected at three points in the pipeline: decode (illegal encoding), execute (ECALL/EBREAK, misalign), and memory (load/store fault from PMP).  
All exceptions funnel into a single exception bus that the hazard unit uses to flush stages and redirect PC to `mtvec`.

```systemverilog
// Exception cause encoding (RISC-V spec mcause)
localparam EXC_ILLEGAL_INSTR = 4'd2;
localparam EXC_EBREAK         = 4'd3;
localparam EXC_LOAD_MISALIGN  = 4'd4;
localparam EXC_LOAD_FAULT     = 4'd5;
localparam EXC_STORE_MISALIGN = 4'd6;
localparam EXC_STORE_FAULT    = 4'd7;
localparam EXC_ECALL_M        = 4'd11;
```

### 13.5 PMP — Physical Memory Protection (8 regions)

PMP enforces R/W/X permissions per memory region.  
Eight `pmpcfg` + `pmpaddr` CSR pairs define the regions; the PMP checker sits on the memory access path.

```systemverilog
// rtl/pmp_checker.sv
module pmp_checker #(parameter N_REGIONS = 8) (
    input  logic [31:0] addr_i,
    input  logic        read_i, write_i, exec_i,
    input  logic [7:0]  pmpcfg  [N_REGIONS],
    input  logic [31:0] pmpaddr [N_REGIONS],
    output logic        fault_o
);
    // NAPOT match: pmpaddr encodes base + size in a single register
    // fault_o = 1 when no matching region grants the requested permission
endmodule
```

### 13.6 RISC-V Architecture Compliance Tests

Clone the official ACT repo and wire it to the simulation flow.  
The test suite drives the core, captures register state at `tohost` write, and diffs against the golden reference model (Spike).

```bash
# Clone ACT
git clone https://github.com/riscv-non-isa/riscv-arch-test.git

# Run a subset targeting RV32I
make RISCV_TARGET=my_soc RISCV_DEVICE=rv32i run

# Compare output signature against reference
python3 scripts/compare_sig.py rv32i/I-ADD-01.signature
```

> 💡 **Tip:** Start with the `rv32i` subset (≈120 tests), then add `rv32m`, `rv32a`, `rv32c` sequentially. Each test writes a deterministic register dump to a known SRAM address; your simulation top reads it and compares byte-by-byte against the `.reference_output` file.

### Phase 13 Completion Checklist

```
☐ rvc_expander.sv passes all 36 official C-extension opcode tests
☐ LR/SC: reservation set on LR, cleared on SC; sc_result=0 on success, 1 on fail
☐ AMO instructions: AMOSWAP/ADD/AND/OR/XOR produce correct results in simulation
☐ CSRs: misa, mhartid, mstatus, mtvec, mepc, mcause, mtval, mscratch, mcycle, minstret readable/writable
☐ All 7 exception causes trigger correct mcause and redirect to mtvec
☐ PMP: R/W/X fault fires when region rule is violated; no fault in idle state
☐ ACT rv32i: 100% pass
☐ ACT rv32m, rv32a, rv32c: 100% pass
☐ FreeRTOS still boots after pipeline changes (regression test)
```

> ✅ **Resume Bullet**
> *"Extended RV32I pipeline with RVC/RVA ISA extensions, full machine-mode CSR bank (misa, mcycle, minstret, PMP), and synchronous exception handling; achieved 100% pass rate on the official RISC-V Architecture Compliance Test suite (rv32imac)."*

🎯 **Interview Questions**
- How does the compressed instruction expander handle a 16-bit instruction that straddles a cache-line boundary?
- What is the difference between LR/SC and AMO instructions, and why can't you implement AMOs using only LR/SC in a multi-core system?
- Walk me through what happens cycle-by-cycle when an illegal instruction is decoded: which stages flush, what writes mepc, what PC does the core jump to?
- What is NAPOT PMP encoding and why is it preferred over TOR for typical firmware memory maps?

---

## PHASE 14 — Hardware Debug Infrastructure

### ⏱ Weeks 5–9

With a compliant RV32IMAC core from Phase 13, the next critical gap is debuggability.  
Currently you can only observe the SoC by examining waveforms in simulation — there is no way to halt the core, inspect registers, or set breakpoints on a real FPGA without rebuilding the bitstream.  
This phase implements the RISC-V Debug Module 0.13 specification, a JTAG TAP controller using Xilinx's free `BSCANE2` primitive, and an OpenOCD configuration that makes the SoC visible to GDB with `set $pc`, `si`, `break`, `watch` commands working out of the box.

### 14.1 RISC-V Debug Module 0.13 (dm_top)

The Debug Module is an AXI-Lite peripheral on the SoC crossbar.  
It implements three key abstract commands: Access Register (read/write any GPR or CSR), Quick Access (execute a short program), and Access Memory.  
The program buffer is a 4-instruction SRAM that the debugger fills with arbitrary code to run on the hart while it is halted.

```systemverilog
// rtl/dm_top.sv  (simplified register map)
// 0x04: data0        — scratch register for abstract commands
// 0x10: dmcontrol    — haltreq, resumereq, ndmreset, dmactive
// 0x11: dmstatus     — allhalted, allrunning, anyunavail
// 0x16: abstractcs   — progbufsize, datacount, cmderr, busy
// 0x17: command      — access register / access memory
// 0x18: abstractauto
// 0x20–0x23: progbuf0–3  — 4-instruction program buffer

always_ff @(posedge clk) begin
    if (haltreq && !halted) begin
        // inject debug ebreak into pipeline via hart_halt_req signal
        hart_halt_req <= 1'b1;
    end
    if (resumereq && halted) begin
        hart_resume_req <= 1'b1;
    end
end
```

### 14.2 JTAG TAP Controller (IEEE 1149.1)

Use Xilinx's `BSCANE2` primitive to tap into the FPGA's existing JTAG chain — no extra JTAG pins needed.  
The TAP exposes four registers on USER1–USER4 scan chains: BYPASS, IDCODE, DTMCS (Debug Transport Module Control/Status), and DMI (Debug Module Interface).

```systemverilog
// rtl/jtag_tap.sv — BSCANE2 instantiation (Xilinx only)
BSCANE2 #(.JTAG_CHAIN(1)) u_bscan (
    .CAPTURE (capture),
    .DRCK    (tck),
    .RESET   (trst),
    .RUNTEST (runtest),
    .SEL     (sel),
    .SHIFT   (shift),
    .TCK     (tck),
    .TDI     (tdi),
    .TMS     (tms),
    .UPDATE  (update),
    .TDO     (tdo)
);

// DTM state machine: Idle → CaptureDR → ShiftDR → UpdateDR
// DMI register: [41:34]=address, [33:2]=data, [1:0]=op (0=nop,1=read,2=write,3=rsvd)
```

> 💡 **Tip:** `BSCANE2` eliminates the need for dedicated JTAG I/O pins. Vivado automatically routes the FPGA's existing JTAG header (used for programming) to your TAP. A single `openocd -f board/digilent_arty.cfg -f target/my_soc.cfg` command connects GDB without any hardware modifications.

### 14.3 OpenOCD Configuration

```tcl
# openocd/my_soc.cfg
adapter driver ftdi
ftdi_vid_pid 0x0403 0x6014
ftdi_layout_init 0x00e8 0x60eb

transport select jtag
jtag newtap my_soc cpu -irlen 6 -expected-id 0x0362D093

target create my_soc.cpu riscv -chain-position my_soc.cpu
my_soc.cpu configure -work-area-phys 0x20000000 -work-area-size 0x4000

# Memory map for OpenOCD flash programming
flash bank my_flash.0 virtual 0x00000000 0 0 0 my_soc.cpu
```

```bash
# Connect GDB to running SoC
riscv32-unknown-elf-gdb firmware.elf
(gdb) target extended-remote localhost:3333
(gdb) monitor halt
(gdb) info registers
(gdb) break main
(gdb) continue
```

### 14.4 Hardware Breakpoints and Watchpoints

Implement the trigger module CSRs (`tselect`, `tdata1`, `tdata2`, `tdata3`) for 4 hardware breakpoints.  
Type-2 address-match triggers halt the core when PC equals `tdata2` (breakpoint) or when a load/store address matches (watchpoint).

```systemverilog
// rtl/trigger_module.sv
// tdata1[31:28] = type (2=address match)
// tdata1[19]    = execute match  → breakpoint
// tdata1[18]    = store match    → watchpoint
// tdata1[17]    = load match     → watchpoint

always_comb begin
    trigger_fire = 1'b0;
    for (int i = 0; i < 4; i++) begin
        if (tdata1[i][31:28] == 4'd2) begin  // type-2
            if (tdata1[i][19] && (pc_ex == tdata2[i]))          trigger_fire = 1'b1;
            if (tdata1[i][18] && store_valid && (mem_addr == tdata2[i])) trigger_fire = 1'b1;
            if (tdata1[i][17] && load_valid  && (mem_addr == tdata2[i])) trigger_fire = 1'b1;
        end
    end
end
```

> ⚠️ **Common Mistake:** Confusing software breakpoints (`EBREAK` instruction inserted by GDB into memory) with hardware breakpoints (trigger module). Software breakpoints require writable memory and cannot be set in ROM or flash. Always implement hardware triggers — GDB uses them automatically when available via the `set can-use-hw-watchpoints` flag.

### Phase 14 Completion Checklist

```
☐ dm_top responds correctly to dmcontrol haltreq / resumereq
☐ Abstract command: read all 32 GPRs while hart is halted
☐ Abstract command: write GPR and confirm value survives resume
☐ Program buffer: 4-instruction sequence executes correctly
☐ BSCANE2 instantiated and DTM IDCODE readable via JTAG
☐ OpenOCD connects without errors on physical Artix-7 board
☐ GDB: halt, read registers, single-step, continue all work
☐ Breakpoint: `break main` halts at correct instruction
☐ Watchpoint: `watch *0x20000100` fires on store to that address
☐ 4 concurrent hardware breakpoints/watchpoints simultaneously active
```

> ✅ **Resume Bullet**
> *"Implemented RISC-V Debug Module 0.13 with JTAG TAP (Xilinx BSCANE2), four hardware breakpoints/watchpoints, and OpenOCD/GDB integration; enables real-time halt, single-step, register inspection, and memory-mapped breakpoints on Artix-7 without additional JTAG hardware."*

🎯 **Interview Questions**
- What is the role of the program buffer in the RISC-V Debug Module, and how does it differ from the abstract command interface?
- Why is `BSCANE2` preferred over dedicated JTAG pins for FPGA prototyping, and what is its main limitation for production silicon?
- Explain how GDB decides whether to use a software or hardware breakpoint on a RISC-V target.
- What is the DTM (Debug Transport Module) and what does the `absbits` field in DTMCS tell the debugger?

---

## PHASE 15 — CPU Performance (I-cache, Branch Predictor, MUL)

### ⏱ Weeks 10–13

Phase 14 gave you full debuggability; now address the three largest CPU performance gaps.  
The current core fetches every instruction from L1 D-cache (shared), has no branch prediction (always predicts not-taken, pays 2-cycle penalty on every taken branch), and implements MUL/DIV purely iteratively (up to 32 cycles).  
Inference workloads are multiply-heavy; missing I-cache means every function call re-fetches code from SRAM with latency.  
This phase adds a 4KB direct-mapped I-cache (reusing the existing D-cache RTL), a 2-bit saturating counter BHT with BTB for loop prediction, and single-cycle MUL via the DSP48E1 hard block.

### 15.1 4KB Direct-Mapped Instruction Cache

Reuse `l1_cache.sv` from Phase 2 with `WRITE_ENABLE = 0` — the I-cache is read-only.  
The only change is adding a `flush_i` port (driven by the hazard unit on FENCE.I) and widening the fetch width to 64 bits to feed both a 32-bit instruction and optionally a pre-fetched second word.

```systemverilog
// Instantiate I-cache in fetch_stage.sv
l1_cache #(
    .CACHE_SIZE_BYTES (4096),
    .LINE_SIZE_BYTES  (32),
    .WRITE_ENABLE     (0)     // read-only
) u_icache (
    .clk      (clk),
    .rst_n    (rst_n),
    .flush_i  (fence_i),      // FENCE.I invalidates I-cache
    .req_i    (1'b1),
    .addr_i   (pc),
    .we_i     (1'b0),
    .wdata_i  (32'd0),
    .rdata_o  (fetch_data),
    .hit_o    (icache_hit),
    .stall_o  (icache_stall)
);
```

> 💡 **Tip:** Because the I-cache and D-cache share the AXI bus, a simultaneous miss from both can cause arbitration contention. Add a simple priority: D-cache misses win (they stall the pipeline anyway); I-cache miss request is re-issued the next cycle if the bus was busy.

### 15.2 Branch Predictor — 2-Bit Saturating BHT + BTB

A 32-entry Branch History Table (BHT) indexed by `PC[6:2]` holds 2-bit saturating counters.  
A 16-entry Branch Target Buffer (BTB) stores `{tag, target_pc}` pairs.  
On a BHT predict-taken hit in BTB, the fetch redirects speculatively; a misprediction in execute flushes IF/ID and ID/EX (same 2-cycle penalty as static not-taken, but loops predict taken after the first iteration).

```systemverilog
// rtl/branch_predictor.sv
module branch_predictor (
    input  logic        clk, rst_n,
    // Prediction request (IF stage)
    input  logic [31:0] pc_if,
    output logic        predict_taken_o,
    output logic [31:0] predict_target_o,
    // Update from EX stage (resolved branch)
    input  logic        branch_resolved_i,
    input  logic        branch_taken_i,
    input  logic [31:0] branch_pc_i,
    input  logic [31:0] branch_target_i
);
    logic [1:0] bht [32];   // 2-bit saturating counters
    logic [31:0] btb_tag    [16];
    logic [31:0] btb_target [16];
    logic        btb_valid  [16];

    wire [4:0] bht_idx = pc_if[6:2];
    wire [3:0] btb_idx = pc_if[5:2];

    assign predict_taken_o  = bht[bht_idx][1] && btb_valid[btb_idx]
                              && (btb_tag[btb_idx] == pc_if);
    assign predict_target_o = btb_target[btb_idx];

    always_ff @(posedge clk) begin
        if (branch_resolved_i) begin
            // Saturating counter update
            if (branch_taken_i) bht[branch_pc_i[6:2]] <= (bht[branch_pc_i[6:2]] == 2'b11) ? 2'b11 : bht[branch_pc_i[6:2]] + 1;
            else                bht[branch_pc_i[6:2]] <= (bht[branch_pc_i[6:2]] == 2'b00) ? 2'b00 : bht[branch_pc_i[6:2]] - 1;
            // BTB write on taken
            if (branch_taken_i) begin
                btb_tag   [branch_pc_i[5:2]] <= branch_pc_i;
                btb_target[branch_pc_i[5:2]] <= branch_target_i;
                btb_valid [branch_pc_i[5:2]] <= 1'b1;
            end
        end
    end
endmodule
```

### 15.3 Single-Cycle MUL via DSP48E1

Replace the iterative multiplier with a DSP48E1 instantiation.  
DSP48E1 delivers a registered product in one clock cycle at 400+ MHz — no iterative shifts needed.

```systemverilog
// rtl/fast_mul.sv — DSP48E1 wrapper for 32×32→64 multiply
module fast_mul (
    input  logic        clk,
    input  logic [31:0] a_i, b_i,
    input  logic        signed_i,   // 1=signed MUL/MULH, 0=unsigned MULHU
    output logic [63:0] result_o    // registered, 1-cycle latency
);
    // Sign-extend to 18-bit (DSP A-port) and 27-bit (DSP B-port)
    // For 32-bit multiply: cascade two DSP48E1 or use ACIN/BCIN chain
    DSP48E1 #(
        .AREG(1), .BREG(1), .PREG(1),
        .USE_MULT("MULTIPLY"),
        .A_INPUT("DIRECT"), .B_INPUT("DIRECT")
    ) u_dsp (
        .CLK (clk),
        .A   ({6{signed_i & a_i[31]}, a_i}),  // sign-extend to 30 bits
        .B   ({3{signed_i & b_i[31]}, b_i}),  // sign-extend to 18 bits
        .P   (result_o[47:0])
        // upper 16 bits handled by second DSP or shift
    );
endmodule
```

> ⚠️ **Common Mistake:** DSP48E1 is a Xilinx-specific primitive. Keep fast_mul parameterised so a `USE_DSP=0` path instantiates a plain `*` operator — this lets the design synthesize on non-Xilinx targets (ECP5, iCE40) without removing MUL support. Gate the DSP path with `` `ifdef XILINX_DSP ``.

### Phase 15 Completion Checklist

```
☐ I-cache: hit on repeated fetches, cold miss triggers AXI refill
☐ FENCE.I: flushes I-cache, subsequent fetch sees updated code
☐ I-cache + D-cache simultaneous miss: arbitration works, no deadlock
☐ BHT: tight loop (100 iterations) predicts taken after iteration 1
☐ BTB: indirect call target predicted correctly on second invocation
☐ Branch misprediction penalty remains exactly 2 cycles
☐ MUL: correct result in 1 cycle for all signed/unsigned variants
☐ MULH/MULHSU/MULHU: upper 32 bits correct for edge cases (negatives, overflow)
☐ Dhrystone MIPS improves ≥30% vs. Phase 12 baseline
☐ No regressions in ACT rv32imac test suite
```

> ✅ **Resume Bullet**
> *"Added 4KB direct-mapped I-cache (reusing D-cache RTL), 2-bit saturating BHT/BTB branch predictor, and single-cycle DSP48E1-based multiplier to RV32I pipeline; achieved ≥30% Dhrystone improvement with zero ACT compliance regressions."*

🎯 **Interview Questions**
- Why is a direct-mapped cache preferred over a 2-way set-associative cache for an I-cache in area-constrained designs?
- What does FENCE.I guarantee, and at what point in the pipeline must the I-cache flush happen to maintain correctness?
- Explain why a 2-bit saturating counter predicts loops better than a 1-bit counter.
- DSP48E1 has a maximum port width of 30-bit (A) and 18-bit (B). How do you implement a full 32×32-bit multiply using it?

---

## PHASE 16 — Firmware Development Stack

### ⏱ Weeks 14–16

After Phase 15 the hardware is fast, compliant, and debuggable.  
The biggest remaining barrier for external users is firmware iteration speed: every change requires rebuilding the Vivado project (15–30 minutes), re-programming the FPGA, and reflashing SRAM manually.  
This phase implements an ELF-over-UART bootloader, newlib syscall stubs so standard C library functions work, a Vivado TCL project script for one-command builds, and a GitHub Actions CI/CD pipeline that compiles firmware and runs cocotb regression on every push.

### 16.1 ELF-over-UART Bootloader (XMODEM/SREC)

The bootloader lives in a dedicated ROM region (0x0000_0000–0x0000_0FFF).  
On power-on it waits 3 seconds for an XMODEM transfer on UART0.  
If a valid ELF arrives it writes it to SRAM starting at 0x2000_0000 and jumps to `_start`.  
If no transfer begins it jumps to the application at 0x2000_0000 directly.

```c
// sw/bootloader/main.c
#define UART_BASE   0x4000_0000UL
#define SRAM_BASE   0x2000_0000UL
#define TIMEOUT_MS  3000

void boot(void) {
    uart_puts("RV32 Bootloader v1.0 — send SREC or press any key to skip\r\n");
    if (uart_wait_char(TIMEOUT_MS) != -1) {
        size_t len = xmodem_receive((uint8_t*)SRAM_BASE);
        if (len > 0) {
            uart_puts("OK — jumping to 0x20000000\r\n");
        }
    }
    void (*app)(void) = (void (*)(void))SRAM_BASE;
    app();
}
```

```python
# tools/upload.py — host-side upload helper
import serial, sys
from xmodem import XMODEM

def send(port, elf_path):
    with serial.Serial(port, 115200, timeout=5) as s:
        with open(elf_path, 'rb') as f:
            modem = XMODEM(lambda size: s.read(size), lambda data: s.write(data))
            modem.send(f)
    print(f"Uploaded {elf_path} to SoC")
```

> 💡 **Tip:** Include a magic-header check in the bootloader: if the first 4 bytes at SRAM_BASE are not `0x7f 'E' 'L' 'F'`, print a warning instead of jumping into garbage. This saves hours of puzzling over a silent hang.

### 16.2 newlib Syscall Stubs

GCC's `libc` calls seven platform stubs that must be provided by the BSP.  
Without these, linking any program that uses `printf`, `malloc`, or file I/O fails.

```c
// sw/bsp/syscalls.c
#include <sys/stat.h>
#include <errno.h>

extern char _heap_start, _heap_end;  // defined in linker script
static char *heap_ptr = &_heap_start;

void *_sbrk(int incr) {
    char *prev = heap_ptr;
    if (heap_ptr + incr > &_heap_end) { errno = ENOMEM; return (void*)-1; }
    heap_ptr += incr;
    return prev;
}

int _write(int fd, char *buf, int len) {
    // Route stdout/stderr to UART0
    for (int i = 0; i < len; i++) uart_putc(buf[i]);
    return len;
}

int _read(int fd, char *buf, int len) {
    for (int i = 0; i < len; i++) buf[i] = uart_getc();
    return len;
}

// Stubs: _close, _fstat, _isatty, _lseek — return ENOSYS
int _close (int fd)             { errno = ENOSYS; return -1; }
int _fstat (int fd, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd)             { return 1; }
int _lseek (int fd, int off, int whence) { errno = ENOSYS; return -1; }
```

### 16.3 Vivado TCL Build Automation

```tcl
# scripts/vivado_build.tcl
create_project my_soc ./vivado_proj -part xc7a35tcpg236-1
set_property target_language SystemVerilog [current_project]

# Add RTL sources
add_files -fileset sources_1 [glob ../rtl/*.sv]
add_files -fileset constrs_1 ../constraints/arty_a7.xdc

# Set top
set_property top riscv_soc_top [current_fileset]

# Synthesize + Implement + Bitstream in one call
launch_runs synth_1 -jobs 8
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1

puts "Bitstream written to: [get_property DIRECTORY [current_run]]/my_soc.bit"
```

```bash
# One-command build from the repo root
vivado -mode batch -source scripts/vivado_build.tcl
```

### 16.4 GitHub Actions CI/CD Pipeline

```yaml
# .github/workflows/ci.yml
name: SoC CI
on: [push, pull_request]

jobs:
  cocotb_regression:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install deps
        run: |
          sudo apt-get install -y iverilog
          pip install cocotb cocotb-bus
      - name: Run Phase 1 tests
        run: cd phase1_riscv_core/tb && python run_tests.py
      - name: Run Phase 3 crossbar tests
        run: cd phase3_axi/tb && python run_tests.py axi4_crossbar
      - name: Run Phase 5 adapter tests
        run: cd phase5_soc/tb && python run_unit_tests.py dmem_axi_adapter

  firmware_build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install RISC-V GCC
        run: sudo apt-get install -y gcc-riscv64-unknown-elf
      - name: Build firmware
        run: make -C phase11_sw/sw all
      - name: Run host-side C tests
        run: make -C phase11_sw/sw/nn run_all
```

> ⚠️ **Common Mistake:** Running Vivado synthesis in CI is impractical (license + 30-min runtime). The CI pipeline should cover cocotb simulation, firmware compilation, and host-side unit tests only. Gate synthesis behind a manual `workflow_dispatch` trigger or a release tag.

### Phase 16 Completion Checklist

```
☐ Bootloader: 3-second timeout, XMODEM receive, ELF magic check, jump to app
☐ tools/upload.py: successfully transfers a 20KB ELF in < 10 seconds at 115200 baud
☐ newlib: printf("Hello %d\n", 42) outputs correctly via UART on hardware
☐ malloc/free: basic heap allocation works with newlib + _sbrk stub
☐ Linker script defines _heap_start, _heap_end, _stack_top correctly
☐ Vivado TCL: one command produces .bit file from clean checkout
☐ GitHub Actions: all cocotb tests pass in CI on each push
☐ GitHub Actions: firmware builds without warnings in CI
☐ README updated with "Quick Start: flash + run Hello World in 5 minutes"
```

> ✅ **Resume Bullet**
> *"Developed a complete firmware stack: ELF-over-UART XMODEM bootloader (eliminating 30-min FPGA rebuilds), newlib syscall stubs enabling printf/malloc, Vivado TCL automation, and GitHub Actions CI running cocotb regression + firmware build on every commit."*

🎯 **Interview Questions**
- Why does `_sbrk` need to check against `_heap_end` and what happens if you don't?
- Walk through the XMODEM protocol: what does the receiver send first, and how does error recovery work?
- What is the difference between a bare-metal linker script section `.text`, `.data`, and `.bss` in terms of FLASH/RAM placement?
- Why is it a bad idea to run Vivado synthesis in GitHub Actions even if you had a license?

---

## PHASE 17 — Peripheral Completeness

### ⏱ Weeks 17–20

Phase 8 added UART, GPIO, Timer, SPI, CLINT, and PLIC.  
This phase fills the remaining peripheral gaps that real-world embedded applications demand: I2C (used by nearly every sensor), a Watchdog Timer (mandatory for safety-critical use), a hardware TRNG (needed for TLS), and DMA-capable UART and SPI (eliminating CPU-in-the-loop byte-at-a-time transfers).

### 17.1 I2C Master/Slave Controller

The I2C controller supports 100 kHz (standard) and 400 kHz (fast) modes, 7-bit and 10-bit addressing, and clock stretching.  
It is APB-mapped (same bus as other peripherals from Phase 8).

```systemverilog
// rtl/i2c_master.sv — key registers (APB mapped)
// 0x00: CTRL  — [0]=enable, [1]=irq_en, [2]=400kHz_mode
// 0x04: ADDR  — [9:0]=slave_addr, [10]=10bit_mode
// 0x08: DATA  — write=TX byte, read=RX byte
// 0x0C: CMD   — [0]=start, [1]=stop, [2]=read, [3]=write, [4]=ack
// 0x10: STATUS— [0]=busy, [1]=arb_lost, [2]=nack, [3]=irq

// SCL generation: divide sys_clk by (clk_div) to get 4× I2C clock
// SDA/SCL are open-drain — output 0 to drive low, tri-state to release high
assign scl_oe = !scl_out;   // drive low when scl_out==0
assign sda_oe = !sda_out;   // drive low when sda_out==0
```

### 17.2 Watchdog Timer (WDT) with Magic-Value Protection

The WDT resets or triggers an NMI if firmware fails to "kick" it within the timeout window.  
Magic-value protection requires firmware to write a two-step sequence (`0x1ACCE551` then `0xDEAD5AFE`) to unlock the kick register, preventing accidental resets from runaway code that coincidentally writes to the WDT address.

```systemverilog
// rtl/wdt.sv
localparam MAGIC_STEP1 = 32'h1ACCE551;
localparam MAGIC_STEP2 = 32'hDEAD5AFE;

always_ff @(posedge clk) begin
    if (apb_write && apb_addr == WDT_KICK) begin
        if (apb_wdata == MAGIC_STEP1) unlock_step <= 1'b1;
        else if (unlock_step && apb_wdata == MAGIC_STEP2) begin
            counter    <= timeout_val;  // reload
            unlock_step <= 1'b0;
        end else unlock_step <= 1'b0;  // wrong value resets unlock
    end else begin
        counter <= (counter == 0) ? 0 : counter - 1;
    end
    wdt_timeout <= (counter == 0);
end
```

> ⚠️ **Common Mistake:** Allowing a single-write unlock lets stray writes accidentally prevent WDT resets — defeating its safety purpose. Always require a two-step sequence with the unlocked state cleared on any incorrect write.

### 17.3 TRNG — True Random Number Generator

A ring oscillator TRNG samples the free-running jitter of several inverter chains.  
Mandatory FIPS 140-2 health tests (monobit test and runs test) are implemented in RTL to detect stuck-at faults.

```systemverilog
// rtl/trng.sv
// Ring oscillator: 3 inverters in a loop — technology-mapped by synthesiser
(* KEEP = "TRUE" *) logic [2:0] ring;
assign ring[0] = !ring[2];
assign ring[1] = !ring[0];
assign ring[2] = !ring[1];

// Sample the LSB of ring at sys_clk — jitter provides entropy
always_ff @(posedge clk) begin
    sr <= {sr[30:0], ring[0]};   // 32-bit shift register
    if (sr_count == 31) begin
        raw_rand  <= sr;
        rand_ready <= 1'b1;
        sr_count  <= 0;
    end else begin
        sr_count  <= sr_count + 1;
        rand_ready <= 1'b0;
    end
end

// Monobit health test: reject if popcount(raw_rand) < 8 or > 24
wire [5:0] ones = $countones(raw_rand);
assign health_ok = (ones >= 6'd8) && (ones <= 6'd24);
```

> 💡 **Tip:** Mark all ring oscillator nets with `(* KEEP = "TRUE" *)` and `(* DONT_TOUCH = "TRUE" *)` to prevent the synthesizer from optimizing them away. Without these attributes, Vivado will collapse the combinational loop in logic optimization.

### 17.4 DMA-Capable UART (16-byte FIFO)

Replace the Phase 8 UART byte-pump with a 16-byte TX/RX FIFO and a simple DMA request interface.  
When TX FIFO is below half-full, the UART asserts `dma_req_o`; the DMA (Phase 18) shovels the next block in automatically.

```systemverilog
// rtl/uart_dma.sv — FIFO thresholds
localparam FIFO_DEPTH = 16;
always_comb begin
    tx_dma_req = (tx_fifo_count < (FIFO_DEPTH / 2));  // request when half-empty
    rx_dma_req = (rx_fifo_count > (FIFO_DEPTH / 2));  // request when half-full
end
```

### Phase 17 Completion Checklist

```
☐ I2C master: writes/reads a real I2C EEPROM (24C02 or similar) on Artix-7
☐ I2C clock stretching: slave stretch detected and SCL held
☐ I2C arbitration lost: detected when SDA mismatch occurs
☐ WDT: fires NMI if not kicked within timeout; reset path also verified
☐ WDT magic sequence: wrong second value resets unlock state
☐ TRNG: raw_rand ready within 32 clocks; monobit health test rejects stuck-at-0
☐ UART FIFO: 16-byte TX burst completes without CPU involvement using DMA req
☐ All Phase 8 peripheral tests still pass (no regressions)
☐ FreeRTOS driver wrappers: i2c_read(), i2c_write(), wdt_kick(), trng_get32()
```

> ✅ **Resume Bullet**
> *"Completed the peripheral suite with I2C master/slave (100/400 kHz, clock stretching), magic-value-protected WDT, ring-oscillator TRNG with FIPS 140-2 health checks, and DMA-ready 16-byte UART/SPI FIFOs; all peripherals APB-mapped and tested on Artix-7 hardware."*

🎯 **Interview Questions**
- How does I2C clock stretching work, and what hardware change is needed in your SCL output stage to support it?
- Why does a ring oscillator produce entropy, and what physical phenomenon provides the randomness?
- What is the monobit test, and what does it detect?
- Explain why a magic-value WDT sequence must clear the unlock state on any wrong write, not just after two correct writes.

---

## PHASE 18 — AI Accelerator v3 (INT4, Operator Library, DMA Burst)

### ⏱ Weeks 21–26

Phase 9 delivered a 16×16 INT8 systolic array with a 128-bit scratchpad DMA.  
This phase pushes inference throughput to production levels: INT4 quantization doubles MAC density, a complete operator library (softmax, pooling, residual add, depthwise conv) eliminates the CPU fallback for common layers, a scatter-gather DMA engine handles non-contiguous weight tensors, and a Python ONNX→weights.h tool closes the model import pipeline end-to-end.

### 18.1 INT4 Support — PE Parameter and Weight Packing

Parameterize each PE to accept an `ACTIVATION_WIDTH` parameter (4 or 8).  
When INT4 is selected, two INT4 weights are packed per INT8 slot and unpacked inside the PE.

```systemverilog
// rtl/pe_int4.sv — parameterized PE
module systolic_pe #(
    parameter int ACT_W  = 8,  // 4 or 8
    parameter int ACCW   = 32
) (
    input  logic signed [ACT_W-1:0] a_i, b_i,
    input  logic signed [ACCW-1:0]  c_i,
    output logic signed [ACCW-1:0]  c_o,
    output logic signed [ACT_W-1:0] a_o, b_o
);
    always_ff @(posedge clk) begin
        c_o <= c_i + (a_i * b_i);
        a_o <= a_i;
        b_o <= b_i;
    end
endmodule
```

```c
// sw/nn/int4_pack.c — pack two INT4 values into one byte
static inline uint8_t pack_int4(int8_t hi, int8_t lo) {
    return ((hi & 0xF) << 4) | (lo & 0xF);
}
static inline void unpack_int4(uint8_t packed, int8_t *hi, int8_t *lo) {
    *hi = (int8_t)(packed >> 4);
    if (*hi & 0x8) *hi |= 0xF0;   // sign-extend
    *lo = (int8_t)(packed & 0xF);
    if (*lo & 0x8) *lo |= 0xF0;
}
```

### 18.2 Conv2D Tiling — Firmware-Level Mapping

Map arbitrary Conv2D layers (HW×HW×C input, K×K×C×OC kernel) onto the 16×16 systolic array using output-stationary tiling.  
The outer loop tiles output channels in groups of 16; the inner loop streams input activations and weights through the array.

```c
// sw/nn/conv2d.c
void conv2d_tiled(
    int8_t *input,   // H×W×C, NHWC layout
    int8_t *weights, // OC×K×K×C, weight-stationary
    int32_t *output, // H_out×W_out×OC
    int H, int W, int C, int K, int OC,
    int stride, int pad)
{
    for (int oc = 0; oc < OC; oc += 16) {       // tile output channels
        for (int oh = 0; oh < (H-K+1)/stride; oh++) {
            for (int ow = 0; ow < (W-K+1)/stride; ow++) {
                // Preload K×K×C input patch into scratchpad
                accel_load_patch(input, oh, ow, H, W, C, K, stride, pad);
                // Preload 16 output-channel weight slices
                accel_load_weights(weights, oc, C, K);
                // Trigger systolic array compute
                accel_run();
                // Read back 16 partial sums into output
                accel_read_output(output, oh, ow, W, OC, oc);
            }
        }
    }
}
```

### 18.3 Complete Operator Library

Implement all operators needed to run MobileNetV2 / ResNet-8 entirely on the SoC.

```c
// sw/nn/ops.h
void softmax_f32    (float *x, int n);
void layernorm_q    (int8_t *x, int n, float scale, int8_t zero_point);
void maxpool2d      (int8_t *in, int8_t *out, int H, int W, int C, int k, int stride);
void avgpool2d      (int8_t *in, int32_t *out, int H, int W, int C, int k, int stride);
void depthwise_conv2d(int8_t *in, int8_t *w, int32_t *out, int H, int W, int C, int K);
void residual_add   (int8_t *a, int8_t *b, int8_t *out, int32_t scale_a,
                     int32_t scale_b, int n);
```

```c
// sw/nn/ops.c — residual_add example (saturating int8 add with requantization)
void residual_add(int8_t *a, int8_t *b, int8_t *out,
                  int32_t scale_a, int32_t scale_b, int n) {
    for (int i = 0; i < n; i++) {
        int32_t sum = ((int32_t)a[i] * scale_a + (int32_t)b[i] * scale_b) >> 16;
        out[i] = (int8_t)CLAMP(sum, -128, 127);
    }
}
```

### 18.4 Scatter-Gather DMA Engine

The Phase 9 DMA transferred a single contiguous buffer.  
For ONNX models, weight tensors are packed non-contiguously in flash.  
A scatter-gather engine traverses a linked-list descriptor chain in SRAM.

```c
// sw/bsp/dma.h — descriptor structure
typedef struct dma_desc {
    uint32_t src_addr;
    uint32_t dst_addr;
    uint32_t byte_count;      // bytes to transfer in this descriptor
    uint32_t next_desc_addr;  // 0 = last descriptor in chain
    uint32_t flags;           // [0]=irq_on_complete, [1]=src_inc, [2]=dst_inc
} dma_desc_t;

// Kick off a chain
void dma_start_chain(dma_desc_t *first) {
    DMA_REG(DMA_DESC_ADDR) = (uint32_t)first;
    DMA_REG(DMA_CTRL)      = DMA_CTRL_START | DMA_CTRL_CHAIN;
}
```

### 18.5 ONNX → weights.h Conversion Tool

```python
# tools/onnx_to_c.py
import onnx
import numpy as np

def export_weights(onnx_path, out_header):
    model = onnx.load(onnx_path)
    with open(out_header, 'w') as f:
        f.write("// Auto-generated by tools/onnx_to_c.py\n")
        f.write("#pragma once\n#include <stdint.h>\n\n")
        for init in model.graph.initializer:
            arr = np.frombuffer(init.raw_data, dtype=np.float32)
            # Quantize to INT8: scale = max(|arr|) / 127
            scale = np.max(np.abs(arr)) / 127.0
            q = np.clip(np.round(arr / scale), -128, 127).astype(np.int8)
            name = init.name.replace('/', '_').replace('.', '_')
            f.write(f"// scale={scale:.6f}\n")
            f.write(f"static const int8_t {name}[] = {{{','.join(map(str, q))}}};\n\n")

if __name__ == "__main__":
    import sys
    export_weights(sys.argv[1], sys.argv[2])
```

> ⚠️ **Common Mistake:** Using per-tensor min-max quantization for weights but per-layer quantization for activations creates mismatched scales at residual-add nodes. Always track and propagate the quantization scale for every tensor through the graph before generating weights.h.

> 💡 **Tip:** Validate the ONNX export against a golden float reference: run the same input through the original float model and the INT8 model, and verify top-1 accuracy degrades by less than 2% on a 1000-image sample before integrating into firmware.

### Phase 18 Completion Checklist

```
☐ INT4 PE: functional simulation shows correct 4-bit MAC accumulation
☐ INT4 throughput: 2× vs INT8 on same tile size (measured in cycles)
☐ Conv2D tiling: 3×3 and 1×1 convolution produce bit-exact output vs. Python reference
☐ softmax, layernorm, maxpool2d, avgpool2d, depthwise_conv2d, residual_add all tested
☐ Scatter-gather DMA: 3-descriptor chain transfers 3 non-contiguous buffers correctly
☐ DMA interrupt fires after last descriptor completes
☐ onnx_to_c.py: export MobileNetV2 INT8 weights without error
☐ MobileNetV2 INT8 top-1 accuracy on 1000 CIFAR-10 samples ≥ 85%
☐ End-to-end inference on hardware: image in → class out, < 50 ms
```

> ✅ **Resume Bullet**
> *"Extended AI accelerator to INT4 (2× throughput), built full operator library (softmax, pooling, depthwise conv, residual add), added scatter-gather DMA for non-contiguous weight loading, and implemented ONNX→INT8 weight export pipeline; achieved MobileNetV2 inference in < 50 ms on Artix-7."*

🎯 **Interview Questions**
- How do you handle the mismatch between INT4 weight packing (2 per byte) and the systolic array's byte-wide data path without doubling array area?
- What is the key correctness requirement when combining activations from two branches with different quantization scales in a residual add?
- Why does a scatter-gather DMA need a linked-list of descriptors rather than just a base address and length?
- Explain the output-stationary tiling strategy: what data remains stationary, what streams through, and what is the memory bandwidth for a 16×16×3 convolution?

---

## PHASE 19 — Security Subsystem

### ⏱ Weeks 27–30

Phase 16's bootloader runs whatever ELF it receives over UART — including malicious firmware.  
This phase adds secure boot (firmware must be signed with SHA-256 before the bootloader will execute it), hardware AES-128/256 and SHA-256/SHA-3 accelerators for fast cryptographic primitives without CPU overhead, and PMP-based memory isolation to prevent compromised peripherals from overwriting kernel code.  
Together these qualify the SoC for IoT security certifications (PSA Certified Level 1, SESIP).

### 19.1 Secure Boot — SHA-256 Firmware Verification

The bootloader reads a 32-byte SHA-256 digest appended to every firmware image and verifies it against a digest stored in a write-once OTP region (emulated in BRAM for FPGA).  
Only images with a matching digest are executed.

```c
// sw/bootloader/secure_boot.c
#define DIGEST_OFFSET  0x20   // last 32 bytes of firmware image
#define OTP_BASE       0xF000_0000UL

bool verify_firmware(uint8_t *image, size_t len) {
    uint8_t computed[32], stored[32];
    sha256_compute(image, len - 32, computed);
    memcpy(stored, (uint8_t*)OTP_BASE, 32);
    // Constant-time compare — avoid timing side-channels
    uint8_t diff = 0;
    for (int i = 0; i < 32; i++) diff |= computed[i] ^ stored[i];
    return (diff == 0);
}
```

> ⚠️ **Common Mistake:** Using `memcmp` for digest comparison introduces a timing side-channel (returns early on first mismatch). Always use a constant-time compare loop — every byte is compared regardless of where the first difference is.

### 19.2 AES-128/256 Hardware Accelerator

Map AES to an APB peripheral.  
The core uses 128-bit data registers and a 32-bit control register for mode selection (ECB, CBC, CTR) and key length.

```systemverilog
// rtl/aes_top.sv — APB register map
// 0x00: CTRL — [0]=start, [1]=decrypt, [2:1]=mode(00=ECB,01=CBC,10=CTR), [4:3]=keylen
// 0x04–0x10: KEY0–KEY3   — 128-bit key (4×32-bit)
// 0x14–0x20: KEY4–KEY7   — upper 128 bits for AES-256
// 0x24–0x30: IV0–IV3     — 128-bit IV for CBC/CTR
// 0x34–0x40: DIN0–DIN3   — 128-bit plaintext input
// 0x44–0x50: DOUT0–DOUT3 — 128-bit ciphertext output
// 0x54: STATUS — [0]=done, [1]=busy

// AES round function: SubBytes, ShiftRows, MixColumns, AddRoundKey
// Implement using lookup tables (S-boxes) stored in BRAM for area efficiency
```

### 19.3 SHA-256 and SHA-3 Accelerators

```systemverilog
// rtl/sha256_top.sv — APB register map
// 0x00: CTRL   — [0]=start, [1]=reset_hash
// 0x04–0x40: MSG0–MSG15 — 512-bit message block (16×32-bit)
// 0x44–0x60: HASH0–HASH7 — 256-bit output
// 0x64: STATUS — [0]=done

// SHA-256: 64 rounds of message schedule + compression function
// SHA-3 (Keccak): 24 rounds of θ, ρ, π, χ, ι permutation on 1600-bit state
```

```c
// sw/crypto/sha256.c — driver
void sha256_hw_compute(uint8_t *data, size_t len, uint8_t *digest) {
    // Pad message to 512-bit boundary
    sha256_pad(data, len);
    // Process each 512-bit block
    for (size_t i = 0; i < (len + 72) / 64; i++) {
        memcpy_to_mmio(SHA256_BASE + 0x04, data + i*64, 64);
        SHA256_REG(SHA256_CTRL) = SHA256_START;
        while (!(SHA256_REG(SHA256_STATUS) & SHA256_DONE));
    }
    memcpy_from_mmio(digest, SHA256_BASE + 0x44, 32);
}
```

### 19.4 PMP-Based Memory Isolation

Use the Phase 13 PMP to enforce privilege boundaries at runtime.  
The bootloader configures PMP before jumping to application: ROM is RX-only, SRAM is RWX, peripheral MMIO is RW-only (no execute), and DMA regions are RW for M-mode only.

```c
// sw/bsp/pmp_config.c
void pmp_setup_isolation(void) {
    // Region 0: ROM  0x0000_0000–0x0FFF_FFFF — RX only
    write_csr(pmpaddr0, 0x0000_0000 >> 2 | (0x0FFF_FFFF >> 3));
    write_csr(pmpcfg0,  PMP_R | PMP_X | PMP_NAPOT);

    // Region 1: SRAM 0x2000_0000–0x2003_FFFF — RWX
    write_csr(pmpaddr1, 0x2000_0000 >> 2 | (0x0003_FFFF >> 3));
    write_csr(pmpcfg0,  (PMP_R | PMP_W | PMP_X | PMP_NAPOT) << 8);

    // Region 2: MMIO 0x4000_0000–0x4FFF_FFFF — RW, no execute
    write_csr(pmpaddr2, 0x4000_0000 >> 2 | (0x0FFF_FFFF >> 3));
    write_csr(pmpcfg0,  (PMP_R | PMP_W | PMP_NAPOT) << 16);
}
```

> 💡 **Tip:** Configure the "default deny" rule by leaving any unmatched region access as a fault. On a 3-region config, a fourth region entry covering the full 4GB address space with no R/W/X bits acts as a catch-all fault — this is the RISC-V spec's recommended pattern.

### Phase 19 Completion Checklist

```
☐ Secure boot: modified firmware (1-bit flip) rejected; valid firmware accepted
☐ Constant-time compare: timing of pass/fail is identical (verified with cycle counter)
☐ AES-128 ECB: NIST test vectors pass (encrypt + decrypt)
☐ AES-256 CBC: NIST test vectors pass
☐ AES CTR: keystream matches reference
☐ SHA-256: NIST FIPS 180-4 test vectors pass (short + long messages)
☐ SHA-3-256: NIST test vectors pass
☐ PMP: store to ROM region faults with mcause=7 (store fault)
☐ PMP: fetch from MMIO region faults with mcause=1 (instruction fault)
☐ FreeRTOS task isolated: task A cannot write task B's stack (PMP region per task)
```

> ✅ **Resume Bullet**
> *"Implemented a security subsystem including SHA-256 secure boot with constant-time verification, AES-128/256 hardware accelerator (ECB/CBC/CTR), SHA-256/SHA-3 hash cores, and PMP-enforced memory isolation (ROM RX-only, MMIO no-execute); qualifies for PSA Certified Level 1."*

🎯 **Interview Questions**
- Why is constant-time comparison necessary for MAC/digest verification, and what constitutes a timing oracle attack?
- What is the difference between ECB and CBC modes of AES, and why is ECB unsuitable for encrypting images?
- Describe the RISC-V PMP NAPOT encoding: given pmpaddr=0x08001FFF, what address range does it cover?
- How does the S-box in AES provide non-linearity, and why is it implemented as a lookup table rather than arithmetic in hardware?

---

## PHASE 20 — SoC Architecture Hardening

### ⏱ Weeks 31–34

After 19 phases of feature addition, the SoC has accrued architectural debt: the AXI crossbar is hardcoded for 3 masters and 3 slaves, the clock network is single-domain (vulnerable to I/O timing closure failures on multi-board targets), and there are no DFT scan hooks (making post-silicon test impossible).  
This phase refactors the crossbar into a generate-based parameterized interconnect, adds a Clock and Reset Management Unit (CRU) that partitions the design into safe clock domains, and inserts scan chain hooks for DFT compliance.

### 20.1 Parameterized AXI4 Crossbar (NM × NS)

Replace the hand-coded 3×3 crossbar with a generate-loop based implementation.  
Parameters: `NM` (number of masters), `NS` (number of slaves), `DATA_W`, `ADDR_W`, and a compile-time address map array.

```systemverilog
// rtl/axi4_crossbar_param.sv
module axi4_crossbar #(
    parameter int NM     = 3,
    parameter int NS     = 3,
    parameter int DATA_W = 32,
    parameter int ADDR_W = 32,
    parameter logic [ADDR_W-1:0] SLAVE_BASE [NS] = '{default:'0},
    parameter logic [ADDR_W-1:0] SLAVE_MASK [NS] = '{default:'0}
) (
    input  logic clk, rst_n,
    // NM master ports (AXI4-Lite)
    axi4_lite_if.slave  m_if [NM],
    // NS slave ports
    axi4_lite_if.master s_if [NS]
);
    // Address decode: for each master request, find matching slave
    function automatic int decode_addr(input logic [ADDR_W-1:0] addr);
        for (int s = 0; s < NS; s++)
            if ((addr & SLAVE_MASK[s]) == SLAVE_BASE[s]) return s;
        return -1;  // no match → bus error
    endfunction

    // Generate arbiters for each slave (round-robin across NM masters)
    genvar s;
    generate
        for (s = 0; s < NS; s++) begin : gen_slave_arb
            rr_arbiter #(.N(NM)) u_arb (
                .clk    (clk),
                .rst_n  (rst_n),
                .req_i  (slave_req[s]),
                .grant_o(slave_grant[s])
            );
        end
    endgenerate
endmodule
```

> 💡 **Tip:** Parameterized interfaces (`axi4_lite_if.slave m_if [NM]`) require SystemVerilog interface arrays. Vivado supports this but some older tools do not — add a flat-port fallback using `generate` for portability to Quartus.

### 20.2 Clock and Reset Management Unit (CRU)

Divide the SoC into three clock domains: `clk_cpu` (50/100 MHz core), `clk_peri` (25 MHz peripherals), `clk_ddr` (200 MHz memory).  
Synchronize reset signals through two-flop synchronizers at every domain crossing.  
Use Xilinx MMCM to generate all clocks from a single 100 MHz board input.

```systemverilog
// rtl/cru.sv
module cru (
    input  logic clk_100m_i,   // 100 MHz board oscillator
    input  logic rst_btn_i,    // active-high pushbutton
    output logic clk_cpu_o,    // 100 MHz (can be throttled to 50 MHz via MMCM)
    output logic clk_peri_o,   // 25 MHz
    output logic clk_ddr_o,    // 200 MHz
    output logic rst_cpu_n_o,  // synchronized reset for CPU domain
    output logic rst_peri_n_o  // synchronized reset for peri domain
);
    MMCME2_BASE #(
        .CLKFBOUT_MULT_F(10.0),    // VCO = 1000 MHz
        .CLKOUT0_DIVIDE_F(10.0),   // clk_cpu  = 100 MHz
        .CLKOUT1_DIVIDE  (40),     // clk_peri =  25 MHz
        .CLKOUT2_DIVIDE  (5)       // clk_ddr  = 200 MHz
    ) u_mmcm (...);

    // Two-flop reset synchronizer per domain
    always_ff @(posedge clk_cpu_o or posedge rst_btn_i) begin
        if (rst_btn_i) {rst_cpu_n_o, rst_sync_cpu} <= 2'b00;
        else           {rst_cpu_n_o, rst_sync_cpu} <= {rst_sync_cpu, 1'b1};
    end
endmodule
```

### 20.3 DFT Scan Chain Hooks

Insert scan enable (`scan_en`) and scan in/out (`scan_in`, `scan_out`) ports at the top level.  
All flip-flops with a `(* SCAN_ENABLE = "TRUE" *)` attribute are connected into a single shift register chain during test mode.

```systemverilog
// rtl/riscv_soc_top.sv — DFT ports
module riscv_soc_top (
    // ... functional ports ...
    // DFT ports (tie-off in normal use; connected to ATE in test)
    input  logic scan_en_i,
    input  logic scan_clk_i,
    input  logic scan_in_i,
    output logic scan_out_o
);
    // Mux functional clock with scan clock
    logic clk_muxed;
    BUFGMUX u_scan_clk_mux (.I0(clk_cpu), .I1(scan_clk_i), .S(scan_en_i), .O(clk_muxed));
```

> ⚠️ **Common Mistake:** Forgetting to mux the functional clock with the scan clock causes ATPG tools to generate incorrect test patterns — the DFT chain must shift at `scan_clk_i` frequency, not `clk_cpu`. Always use a clock MUX primitive (BUFGMUX on Xilinx) so synthesis doesn't insert a logic gate that introduces glitches.

### Phase 20 Completion Checklist

```
☐ Parameterized crossbar: NM=2, NS=4 instantiation passes all previous crossbar tests
☐ Parameterized crossbar: NM=4, NS=8 instantiation synthesizes without errors
☐ Address decode: unmapped address returns SLVERR on both read and write channels
☐ CRU: all three clocks locked (MMCM LOCKED asserted) within 10 μs of reset release
☐ Reset synchronizer: no reset glitch visible in timing simulation
☐ CDC analysis: no asynchronous paths between clk_cpu and clk_peri domains (Vivado report_cdc)
☐ DFT: scan_en=1 shifts a known pattern through all flip-flops; readback matches
☐ All previous phase tests pass with parameterized crossbar
```

> ✅ **Resume Bullet**
> *"Refactored AXI4 crossbar into a generate-based parameterized NM×NS interconnect, added a CRU with MMCM-derived multi-clock domains and two-flop reset synchronizers, and inserted IEEE 1149.1-compatible DFT scan chain hooks for post-silicon test access."*

🎯 **Interview Questions**
- What is the difference between a bus and a crossbar, and at what point does the extra area of a crossbar become worthwhile?
- Why must reset signals be synchronized through two flip-flops when crossing clock domains?
- What is the purpose of the MMCM LOCKED signal, and what should the SoC do while LOCKED is low?
- Explain ATPG (Automatic Test Pattern Generation) and what the scan chain provides that functional tests cannot.

---

## PHASE 21 — Production Verification

### ⏱ Weeks 35–39

The SoC now has hardware parity with industry-standard cores.  
This phase validates it to production standards: constrained-random instruction generation with ISS comparison (riscv-dv + Spike), formal verification of the pipeline FSM and hazard logic using SVA, and coverage-driven closure ensuring ≥95% line/branch coverage and 100% FSM state/transition coverage across all RTL modules.

### 21.1 Constrained-Random Instruction Generation — riscv-dv + Spike

Google's `riscv-dv` generates random RISC-V instruction sequences, runs them on both the RTL simulation and the Spike ISS golden reference, and compares final register state.

```bash
# Install riscv-dv
git clone https://github.com/google/riscv-dv.git && cd riscv-dv
pip install -r requirements.txt

# Generate 1000 random RV32IMAC programs
python3 run.py --test riscv_rand_instr_test \
               --iss spike \
               --target rv32imc \
               --num_tests 1000 \
               --o out/

# Compare RTL output against Spike reference
python3 scripts/compare_trace_csv.py \
    --csv1 out/spike/riscv_rand_instr_test_0.csv \
    --csv2 out/rtl/riscv_rand_instr_test_0.csv
```

```python
# ci/run_riscv_dv.py — automation wrapper for CI
import subprocess, sys

def run_dv(n_tests=100):
    result = subprocess.run([
        "python3", "riscv-dv/run.py",
        "--test", "riscv_rand_instr_test",
        "--iss", "spike",
        "--num_tests", str(n_tests),
        "--target", "rv32imc",
        "--simulator", "vcs"   # or icarus
    ], capture_output=True, text=True)
    if result.returncode != 0:
        print(result.stderr)
        sys.exit(1)
    print(f"riscv-dv: {n_tests} tests PASS")
```

> 💡 **Tip:** Start with `riscv_arithmetic_basic_test` (arithmetic-only, no branches) and confirm it passes before enabling full random tests. A first-time riscv-dv run almost always reveals a CSR edge case or a forwarding path missed in directed tests.

### 21.2 Formal Verification of Pipeline Properties (SVA)

Write SystemVerilog Assertions for the five most critical pipeline invariants and verify them with Symbiyosys (open-source) or Cadence JasperGold.

```systemverilog
// tb/formal/pipeline_props.sv
module pipeline_props (
    input logic clk, rst_n,
    // Bind to riscv_core internals
    // Property 1: x0 is always zero
    property p_x0_zero;
        @(posedge clk) disable iff (!rst_n)
        reg_file.rf[0] == 32'd0;
    endproperty
    assert property (p_x0_zero) else $error("x0 violated");

    // Property 2: Load-use stall inserts exactly one bubble
    property p_load_use_stall;
        @(posedge clk) disable iff (!rst_n)
        (id_ex_load && (id_ex_rd == if_id_rs1 || id_ex_rd == if_id_rs2))
        |=> (hazard_stall == 1'b1) ##1 (hazard_stall == 1'b0);
    endproperty
    assert property (p_load_use_stall) else $error("Load-use stall wrong");

    // Property 3: No write to rd when exception is in flight
    property p_no_write_on_exception;
        @(posedge clk) disable iff (!rst_n)
        exception_valid |-> !wb_reg_write;
    endproperty
    assert property (p_no_write_on_exception);

    // Property 4: PC always word-aligned (or 2-byte aligned with RVC)
    property p_pc_aligned;
        @(posedge clk) disable iff (!rst_n)
        pc[0] == 1'b0;  // LSB always 0 (16-bit minimum)
    endproperty
    assert property (p_pc_aligned);

    // Property 5: CSR mepc holds the faulting PC
    property p_mepc_on_exception;
        @(posedge clk) disable iff (!rst_n)
        $rose(exception_valid) |=> (csr_mepc == $past(pc_ex));
    endproperty
    assert property (p_mepc_on_exception);
endmodule
```

```bash
# Run formal check with SymbiYosys
cat > pipeline.sby << 'EOF'
[options]
mode prove
depth 20

[engines]
smtbmc

[script]
read -sv rtl/riscv_core.sv tb/formal/pipeline_props.sv
prep -top riscv_core
EOF
sby -f pipeline.sby
```

### 21.3 Coverage-Driven Closure

Target: ≥95% line/branch coverage, 100% FSM state and transition coverage across all RTL modules.  
Use Verilator's coverage instrumentation for the cocotb simulation flow.

```makefile
# Makefile — coverage build
SIM = verilator
EXTRA_ARGS = --coverage --coverage-underscore

coverage:
    $(MAKE) SIM=$(SIM) EXTRA_ARGS="$(EXTRA_ARGS)"
    verilator_coverage --annotate annotated_coverage/ coverage.dat
    python3 scripts/check_coverage.py --min-line 95 --min-branch 95 coverage.dat
```

```python
# scripts/check_coverage.py
import xml.etree.ElementTree as ET, sys, argparse

def check(cov_file, min_line, min_branch):
    tree = ET.parse(cov_file)
    line_cov   = float(tree.find('.//coverage[@type="line"]').get('value'))
    branch_cov = float(tree.find('.//coverage[@type="branch"]').get('value'))
    print(f"Line: {line_cov:.1f}%  Branch: {branch_cov:.1f}%")
    if line_cov < min_line or branch_cov < min_branch:
        print(f"FAIL — below minimums ({min_line}% / {min_branch}%)")
        sys.exit(1)
    print("PASS")
```

> ⚠️ **Common Mistake:** Targeting 100% line coverage often requires adding unreachable-code checkers for defensive `default` branches in case statements. Instead, annotate these with `// synthesis translate_off` or a `// pragma coverage off` directive so the tool excludes them from the denominator — aiming for 100% on reachable code only.

### Phase 21 Completion Checklist

```
☐ riscv-dv: 100 arithmetic tests PASS vs. Spike reference
☐ riscv-dv: 100 full random RV32IMAC tests PASS vs. Spike reference
☐ riscv-dv: 10 CSR-stress tests PASS (mcycle, minstret, exception entry/exit)
☐ Formal: p_x0_zero PROVEN for depth ≥ 20 cycles
☐ Formal: p_load_use_stall PROVEN
☐ Formal: p_no_write_on_exception PROVEN
☐ Formal: p_pc_aligned PROVEN
☐ Formal: p_mepc_on_exception PROVEN
☐ Coverage: ≥95% line coverage across all RTL files
☐ Coverage: ≥95% branch coverage
☐ Coverage: 100% FSM state coverage (AXI adapter, crossbar arbiter, debug module)
☐ Coverage: 100% FSM transition coverage
```

> ✅ **Resume Bullet**
> *"Achieved production verification closure: 1000 constrained-random RV32IMAC programs verified against Spike ISS golden reference (riscv-dv), 5 formal pipeline invariants proven with SymbiYosys (x0, load-use stall, exception guard, PC alignment, mepc), ≥95% line/branch coverage and 100% FSM coverage."*

🎯 **Interview Questions**
- What is the key advantage of ISS comparison (Spike) over a self-checking testbench for CPU verification?
- What is the difference between a liveness property and a safety property in formal verification?
- Why does increasing formal verification depth past a certain point add runtime exponentially?
- What does 100% FSM transition coverage mean that 100% FSM state coverage does not capture?

---

## PHASE 22 — Platform Portability & Ecosystem

### ⏱ Weeks 40–45

Phase 21 proved the SoC is correct.  
This final phase makes it *accessible* — to students, researchers, and engineers on different FPGA families and operating systems.  
Delivering a Zephyr RTOS board definition, Intel/Altera port (DE1-SoC), open-source Yosys+nextpnr port (ECP5/iCE40), a rich SDK with documented example projects, and a Technical Reference Manual transforms this from a personal project into a community platform.

### 22.1 Intel/Altera DE1-SoC Port (Cyclone V)

Port the SoC to Cyclone V using Quartus Prime.  
Replace Xilinx-specific primitives: MMCM → PLL, BSCANE2 → JTAG Atom, DSP48E1 → lpm_mult, BUFGMUX → altclkctrl.

```tcl
# scripts/quartus_build.tcl
package require ::quartus::project
package require ::quartus::flow

project_new my_soc -overwrite
set_global_assignment -name DEVICE 5CSEMA5F31C6
set_global_assignment -name TOP_LEVEL_ENTITY riscv_soc_top
set_global_assignment -name SYSTEMVERILOG_FILE {*[glob ../rtl/*.sv]}
set_global_assignment -name SDC_FILE ../constraints/de1_soc.sdc

# Replace Xilinx primitives
set_global_assignment -name VERILOG_MACRO "INTEL_FPGA=1"
execute_flow -compile
project_close
```

```systemverilog
// rtl/tech_cells_intel.sv — wrapper mapping Xilinx primitives to Intel
`ifdef INTEL_FPGA
  // Replace MMCME2_BASE with Cyclone V PLL
  altpll u_pll (.inclk0(clk_100m_i), .c0(clk_cpu_o), .c1(clk_peri_o), .locked(pll_locked));

  // Replace DSP48E1 with lpm_mult
  lpm_mult #(.lpm_widtha(32), .lpm_widthb(32), .lpm_widthp(64))
    u_mul (.dataa(a_i), .datab(b_i), .result(result_o));
`endif
```

### 22.2 Yosys + nextpnr Open-Source Toolchain (ECP5)

Ensure all RTL is pure-SystemVerilog with no vendor primitives in the default build path.  
The `XILINX_DSP` and `INTEL_FPGA` guards keep vendor code conditional.

```makefile
# Makefile.ecp5
YOSYS  = yosys
NEXTPNR = nextpnr-ecp5
DEVICE  = --device LFE5U-85F-6BG381C

synth:
    $(YOSYS) -p "synth_ecp5 -top riscv_soc_top -json build/my_soc.json" \
             rtl/*.sv

pnr:
    $(NEXTPNR) $(DEVICE) --json build/my_soc.json \
               --lpf constraints/ulx3s.lpf \
               --textcfg build/my_soc_out.config

pack:
    ecppack build/my_soc_out.config build/my_soc.bit

all: synth pnr pack
```

> ⚠️ **Common Mistake:** Yosys's SystemVerilog support (`read_verilog -sv`) is less complete than Vivado's. Common failure modes: `interface` arrays not supported, `$countones` not recognized, `unique case` treated as plain `case`. Add a CI step that specifically tests the Yosys synthesis flow so regressions are caught immediately.

### 22.3 Zephyr RTOS Board Definition

Zephyr uses a Device Tree Source (DTS) file for hardware description and Kconfig for feature flags.  
Adding a board definition lets users write Zephyr applications that run on the SoC out of the box.

```dts
/* boards/riscv/rv32_soc/rv32_soc.dts */
/dts-v1/;
#include <mem.h>

/ {
    model = "RV32 AI SoC on Artix-7";
    compatible = "rv32-soc";
    chosen {
        zephyr,sram = &sram0;
        zephyr,flash = &flash0;
        zephyr,console = &uart0;
    };
    cpus {
        cpu0: cpu@0 {
            compatible = "riscv";
            riscv,isa = "rv32imac";
            clock-frequency = <100000000>;
        };
    };
    sram0: memory@20000000 { reg = <0x20000000 DT_SIZE_K(256)>; };
    uart0: serial@40000000 {
        compatible = "ns16550";
        reg = <0x40000000 0x1000>;
        clock-frequency = <25000000>;
        current-speed = <115200>;
    };
};
```

```kconfig
# boards/riscv/rv32_soc/Kconfig.board
config BOARD_RV32_SOC
    bool "RV32 AI SoC"
    depends on SOC_SERIES_RISCV32
    select SOC_RV32_SOC
```

### 22.4 SDK and Example Projects

Structure the SDK so a new user can clone the repo and have a running demo in under 30 minutes.

```
sdk/
├── README_quickstart.md
├── examples/
│   ├── hello_world/          — UART hello world (5 min)
│   ├── freertos_blinky/      — FreeRTOS LED blinky (10 min)
│   ├── mnist_inference/      — Quantized MNIST CNN, < 10 ms/frame
│   ├── keyword_spotting/     — MFCC + LSTM, < 20 ms/utterance
│   └── secure_ota/           — UART OTA update with SHA-256 verify
├── bsp/
│   ├── include/
│   │   ├── soc.h             — MMIO base addresses
│   │   ├── uart.h            — UART driver API
│   │   ├── i2c.h             — I2C driver API
│   │   ├── accel.h           — Accelerator driver API
│   │   └── crypto.h          — AES/SHA driver API
│   └── src/
│       ├── uart.c
│       ├── i2c.c
│       ├── accel.c
│       └── syscalls.c        — newlib stubs
└── tools/
    ├── upload.py             — XMODEM firmware upload
    └── onnx_to_c.py          — ONNX weight export
```

### 22.5 Technical Reference Manual (TRM)

The TRM is the document that separates toy projects from real products.  
It must cover:

1. **Architecture Overview** — block diagram, clock domains, address map table
2. **CPU Reference** — pipeline diagram, ISA extensions (IMAC), CSR table, exception/interrupt handling
3. **Memory Map** — full 4GB address space table with permissions
4. **Peripheral Reference** — one section per peripheral: register map, timing diagrams, driver examples
5. **AI Accelerator Reference** — systolic array architecture, instruction set, performance model, quantization guide
6. **Debug Guide** — JTAG connection, OpenOCD setup, GDB commands, common debug recipes
7. **Getting Started** — board setup, building firmware, uploading, Hello World in 5 minutes
8. **Performance Benchmarks** — Dhrystone MIPS, CoreMark, inference latency table (MNIST, MobileNetV2)

> 💡 **Tip:** Write the TRM as Markdown, auto-generate PDFs with Pandoc + a LaTeX template, and host it on GitHub Pages. Every example project README links to the relevant TRM section. A well-written TRM signals professionalism immediately to anyone who opens the repo.

### Phase 22 Completion Checklist

```
☐ DE1-SoC: SoC boots and runs Hello World on Cyclone V hardware
☐ DE1-SoC: all Intel primitive wrappers synthesize without warnings
☐ ECP5: Yosys synthesis completes without errors on ULX3S board
☐ ECP5: nextpnr place-and-route meets 50 MHz timing
☐ Zephyr: board boots Zephyr kernel and prints to UART console
☐ Zephyr: Zephyr UART and GPIO drivers functional
☐ hello_world example: works on Artix-7, DE1-SoC, and ECP5
☐ mnist_inference example: ≥95% test accuracy, < 10 ms inference time
☐ secure_ota example: bad firmware rejected, good firmware accepted and runs
☐ TRM: all 8 sections written, each peripheral has a register map table
☐ GitHub Pages: TRM hosted and linked from main README
☐ CI: Yosys synthesis added as a CI step (no Vivado required)
```

> ✅ **Resume Bullet**
> *"Achieved multi-platform portability (Artix-7 / Cyclone V / ECP5 ULX3S), wrote a Zephyr RTOS board definition (DTS + Kconfig), published a complete SDK with 5 example projects (Hello World → MobileNetV2 inference → secure OTA), and authored a Technical Reference Manual covering CPU pipeline, peripherals, accelerator, and debug subsystem."*

🎯 **Interview Questions**
- What is the primary source of Xilinx-to-Intel porting effort when migrating FPGA designs, beyond just renaming primitives?
- Describe the Zephyr DTS compilation pipeline: how does a DTS file become C header constants that your driver code uses?
- What is the minimum information a Technical Reference Manual needs for an external engineer to integrate a peripheral into their firmware without reading the RTL?
- If you were prioritizing which of these 10 phases to complete first for a demo at a conference, which would you pick and why?

---

## Complete Phase Status Table

| Phase | Module | Duration | Status |
|-------|--------|----------|--------|
| 0 | Environment + SystemVerilog basics | — | ✅ |
| 1 | 5-stage RV32I pipeline | — | ✅ |
| 2 | Direct-mapped write-back L1 cache | — | ✅ |
| 3 | AXI4 3×3 crossbar + AXI-APB bridge | — | ✅ |
| 4 | 4×4 systolic MAC array accelerator | — | ✅ |
| 5 | Full SoC integration | — | ✅ |
| 6 | OpenLane GDSII synthesis on Sky130A | — | ✅ |
| 7 | FPGA portability · M extension · GCC toolchain | 4 weeks | ⏳ |
| 8 | Peripheral suite: UART · GPIO · Timer · SPI · CLINT · PLIC | 4 weeks | ⏳ |
| 9 | 16×16 INT8 accelerator · 128-bit scratchpad · DMA | 4 weeks | ⏳ |
| 10 | DDR3 memory · multi-board BSP | 3 weeks | ⏳ |
| 11 | FreeRTOS · C inference library · Python quant tool | 4 weeks | ⏳ |
| 12 | Multi-board validation · benchmarks · example projects | 3 weeks | ⏳ |
| 13 | ISA completeness: RVC + RVA + CSRs + exceptions + PMP + ACT | 4 weeks | ⏳ |
| 14 | Hardware debug: DM 0.13 + JTAG TAP + OpenOCD/GDB + HW breakpoints | 5 weeks | ⏳ |
| 15 | CPU performance: I-cache + branch predictor + DSP MUL | 4 weeks | ⏳ |
| 16 | Firmware stack: UART bootloader + newlib + Vivado TCL + CI/CD | 3 weeks | ⏳ |
| 17 | Peripheral completeness: I2C + WDT + TRNG + DMA UART/SPI | 4 weeks | ⏳ |
| 18 | AI accelerator v3: INT4 + operator lib + scatter-gather DMA + ONNX | 6 weeks | ⏳ |
| 19 | Security: secure boot + AES-128/256 + SHA-256/SHA-3 + PMP isolation | 4 weeks | ⏳ |
| 20 | Architecture hardening: parameterized crossbar + CRU + DFT scan | 4 weeks | ⏳ |
| 21 | Production verification: riscv-dv + formal SVA + coverage closure | 5 weeks | ⏳ |
| 22 | Portability & ecosystem: DE1-SoC + ECP5 + Zephyr + SDK + TRM | 6 weeks | ⏳ |
| **Total (P13–22)** | | **~45 weeks** | |
