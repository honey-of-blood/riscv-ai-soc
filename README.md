# RISC-V AI SoC

**A complete RISC-V AI SoC built from scratch in plain SystemVerilog — synthesized on Sky130 130nm.**

The project builds the full stack in twelve phases: a 5-stage RV32I pipeline, an L1 cache, an AXI4 crossbar, a weight-stationary systolic array accelerator, six peripherals, a DDR3/BRAM memory layer, a FreeRTOS M-mode port, and a Python INT8 post-training quantization pipeline that runs MNIST inference on the chip.  Every layer of the stack was written by hand — no HLS, no Chisel, no IP cores.

```
┌────────────────────────────────────────────────────────────────────────────┐
│                           RISC-V AI SoC                                    │
│                                                                            │
│  ┌───────────┐   ┌──────────┐   ┌──────────────────────────────────────┐  │
│  │  RV32IM   │   │  L1 D$   │   │          AXI4 3×3 Crossbar           │  │
│  │ 5-stage   ├──►│  4 KB    ├──►│ ┌────────┐ ┌────────┐ ┌───────────┐ │  │
│  │ pipeline  │   │ write-bk │   │ │  SRAM  │ │  APB   │ │  16×16    │ │  │
│  │ + M-ext   │   │          │   │ │ 512 KB │ │ Bridge │ │ Systolic  │ │  │
│  └───────────┘   └──────────┘   │ │(BRAM/  │ │        │ │  Array    │ │  │
│                                  │ │ DDR3)  │ └───┬────┘ │ + 128 KB  │ │  │
│  ┌────────────────────────────┐  │ └────────┘     │      │ Scratchpad│ │  │
│  │   FreeRTOS M-mode Port     │  └───────────────-┼──────┴───────────┘ │  │
│  │  heap_4  •  tick  •  yield │                   │                    │  │
│  └────────────────────────────┘         ┌─────────▼────────────────┐   │  │
│                                          │  APB Peripheral Bus      │   │  │
│  ┌────────────────────────────┐          │  UART  GPIO  Timer  SPI  │   │  │
│  │  INT8 Inference Library    │          │  CLINT  PLIC             │   │  │
│  │  nn_fc_forward (tiled N=4) │          └──────────────────────────┘   │  │
│  │  nn_requantize  nn_forward │                                          │  │
│  └────────────────────────────┘                                          │  │
└────────────────────────────────────────────────────────────────────────────┘
```

## Synthesis Results (Sky130A)

| Metric | Value |
|--------|-------|
| Standard cells | 134,728 sky130_fd_sc_hd |
| Cell area | 1.91 mm² |
| Die area | 9.66 mm² (FP_CORE_UTIL 20%) |
| Fmax (TT 25°C 1.8V) | 66.7 MHz (WNS = 0 ns post-CTS) |
| Total power | 318.8 mW (221.2 internal + 97.6 switching) |
| PDK | Sky130A — 130 nm, 5-metal |
| Formal proofs | 4 SVA properties (Phase 3) |

### GDSII Layout

![soc_top GDSII layout on Sky130A](docs/soc_gds.png)

> Density heatmap rendered via gdstk + matplotlib.
> Layers: li1 (purple) → met1 (blue) → met2 (red) → met3 (teal) → met4 (yellow) → met5 (magenta).
> Horizontal yellow band = met4 power stripe; magenta dots = met5 vertical power rails.
> Full SoC synthesis (146 K cells) exceeds Sky130's 5-metal routing capacity — layout shows
> RV32I core + L1 cache + AXI4 crossbar + APB (134 K cells, accelerator blackboxed).

## Inference Benchmark (100 MHz simulation)

Measured in Verilator simulation using `mtime` CSR timer; each tile = one 4×4 accelerator invocation.

| Operation | Tiles | Cycles | Time |
|-----------|-------|--------|------|
| FC 784 → 128 | 6 272 | ~658 K | ~6.6 ms |
| FC 128 → 10 | 96 | ~10 K | ~101 µs |
| MNIST forward (full) | 6 368 | ~668 K | ~6.7 ms |
| UART 100-byte burst | — | ~8 700 | ~87 µs |

> Tile overhead breakdown: 4 scratchpad writes + 4 weight writes + 1 CTRL start + ~9 done polls + 4 Y reads ≈ 22 AXI-Lite transactions × ~5 cycles each + 8 COMPUTE cycles = ~118 cycles/tile.

## Phase Status

| Phase | What was built | Tests |
|-------|---------------|-------|
| 1 | RV32I 5-stage pipeline (hazard unit, forwarding, bubblesort) | 22 / 22 |
| 2 | Direct-mapped write-back L1 D-cache (4 KB, 6-state FSM) | 18 / 18 |
| 3 | AXI4 3×3 crossbar + AXI-APB bridge + 4 SVA formal proofs | 12 cocotb + 12 UVM + 4 formal |
| 4 | 4×4 weight-stationary systolic array + UVM scoreboard | 160 / 160 UVM checks |
| 5 | Full SoC integration (core + cache + crossbar + accelerator) | 44 / 44 |
| 6 | OpenLane GDSII on Sky130A | 134 K cells, 1.91 mm², 66.7 MHz |
| 7 | FPGA BSP (Nexys/Arty A7) + RV32IM M-extension + GCC toolchain | 10 / 10 M-ext tests |
| 8 | UART · GPIO · Timer · SPI · CLINT · PLIC + C HAL | 73 / 73 |
| 9 | 16×16 parametric systolic array + 128 KB scratchpad + 2-ch DMA | E2E firmware PASS |
| 10 | BRAM/DDR3 memory layer + multi-board BSP (Nexys/Arty A7) | 350 / 350 |
| 11 | FreeRTOS M-mode port + C INT8 inference library + Python PTQ tool | 51 C + 34 Python |
| 12 | Benchmark suite + MNIST demo firmware + this README | 23 / 23 host checks |

## Quick Start

### Simulate Phase 1 (RV32I core)
```bash
source .venv/bin/activate
cd phase1_riscv_core/tb
python3 run_tests.py        # 22 cocotb tests — RV32I opcodes, hazards, bubblesort
```

### Run the Phase 11 test suite
```bash
cd phase11_sw/sw/nn
make run                    # 51/51 C tests (29 FC shapes, 11 RQ, 5 forward, 6 port)
make run_quantize           # 34/34 Python tests (quantize.py helpers)
```

### Train MNIST + run firmware (needs riscv32-unknown-elf-gcc + PyTorch)
```bash
# 1. Train and quantize
cd phase12_validation
python3 tools/train_mnist.py --quantize   # → sw/weights.h  (~98% accuracy)

# 2. Build firmware
cd sw
make                          # benchmark.elf + mnist/mnist.elf

# 3. Load into SoC simulation (Verilator, once instr_rom.sv is updated)
#    Copy mnist/mnist.hex → phase5_soc/fw/firmware.hex, then:
cd phase5_soc/tb
make run
```

### Generate synthetic weights (no PyTorch required)
```bash
cd phase12_validation
python3 tools/gen_weights_numpy.py        # → sw/weights.h (random, for compile testing)
cd sw && mkdir -p build
gcc -O2 -DTEST_HOST -I. -I../../phase11_sw/sw/nn \
    test_weights.c ../../phase11_sw/sw/nn/nn_host.c -o build/test_weights
./build/test_weights          # 23/23 PASS
```

### Formal verification (Phase 3)
```bash
cd phase3_axi/formal
sby crossbar_formal.sby       # 4 SVA proofs, bounded depth 20
```

## Multi-Board Validation Matrix

| Test | Nexys A7-50T | Nexys A7-100T | Arty A7-100T |
|------|:-----------:|:------------:|:------------:|
| Boot + UART hello | ✓ sim | ✓ sim | ✓ sim |
| GPIO LED blink | ✓ sim | ✓ sim | ✓ sim |
| Timer interrupt | ✓ sim | ✓ sim | ✓ sim |
| FreeRTOS 2-task demo | ✓ port | ✓ port | ✓ port |
| MNIST inference (BRAM) | ✓ sim | ✓ sim | ✓ sim |
| MNIST inference (DDR3) | — (no DDR3) | ✓ BSP ready | ✓ BSP ready |

> "sim" = verified in Verilator simulation. "port" = port written and unit-tested. BSP files are in `phase10_memory/fpga/boards/`.

## Tool Stack

| Tool | Version | Purpose |
|------|---------|---------|
| Icarus Verilog | 12.0 | RTL simulation |
| Verilator | 5.020 | Cycle-accurate C++ simulation + UVM harness |
| cocotb | 2.0.1 | Python-driven testbenches |
| SymbiYosys + z3 | — | Formal SVA verification |
| Yosys | — | RTL synthesis |
| OpenLane | 2.3.10 | RTL-to-GDSII on Sky130A |
| riscv32-unknown-elf-gcc | — | Bare-metal firmware (RV32IM) |
| Python + NumPy | 3.x / 1.26 | Test vector generation, INT8 PTQ tool |
| PyTorch + torchvision | optional | MNIST training (Phase 12) |

## Repository Structure

```
soc/
├── docs/                               ← build logs, blueprints, GDS screenshot
├── openlane/soc_top/                   ← OpenLane config + synthesis stubs
│
├── phase1_riscv_core/
│   ├── rtl/                            ← alu, reg_file, imm_gen, 5 pipeline stages,
│   │                                      hazard_unit, forwarding_unit, riscv_core
│   └── tb/                             ← 6 cocotb test modules, run_tests.py
│
├── phase2_cache/
│   ├── rtl/                            ← cache_top, cache_controller (6-state FSM),
│   │                                      cache_tag_array, cache_data_array
│   └── tb/                             ← 3 cocotb test modules
│
├── phase3_axi/
│   ├── rtl/                            ← axi4_crossbar (3M×3S), axi_apb_bridge, axi_sram
│   ├── formal/                         ← 4 SVA properties, SymbiYosys makefile
│   └── tb/                             ← cocotb tests + UVM-mini crossbar testbench
│
├── phase4_accelerator/
│   ├── rtl/                            ← pe, systolic_array (4×4), accel_top
│   └── tb/
│       ├── uvm/                        ← UVM-mini testbench, 10 tests, scoreboard
│       └── integration/                ← crossbar + accelerator integration tests
│
├── phase5_soc/
│   ├── rtl/                            ← soc_top, dmem_axi_adapter, axi4_burst_to_lite,
│   │                                      instr_rom, apb_regs
│   ├── fw/                             ← hand-assembled RISC-V firmware (assemble.py)
│   └── tb/                             ← Verilator full-SoC testbench
│
├── phase7_fpga/
│   ├── rtl/                            ← fpga_top_nexys_a7, fpga_top_arty_a7
│   ├── constraints/                    ← XDC pin constraint files
│   └── sw/                             ← crt0.S, linker.ld, GCC Makefile
│
├── phase8_peripherals/
│   ├── rtl/                            ← uart, gpio, timer, spi, clint, plic, apb_demux
│   ├── sw/hal/                         ← header-only C HAL for all 6 peripherals
│   └── sw/fw_hello/                    ← timer ISR + UART "Hello, World!" demo firmware
│
├── phase9_accel_v2/
│   ├── rtl/                            ← accel_top_v2 (N=16, scratchpad 128KB, 2-ch DMA)
│   └── tb/                             ← Verilator corner-case testbench
│
├── phase10_memory/
│   ├── rtl/                            ← mem_bram_backend, axi_width_32to128,
│   │                                      mem_ddr3_xilinx (MIG wrapper)
│   ├── fpga/boards/                    ← nexys_a7_50t, nexys_a7_100t, arty_a7_100t BSPs
│   └── tb/                             ← BRAM + SoC E2E testbenches
│
├── phase11_sw/
│   ├── sw/
│   │   ├── nn/                         ← nn.h, nn.c (tiled INT8 FC), nn_host.c,
│   │   │                                  test_nn.c (51 checks), test_vectors.h (29 FC+10 RQ)
│   │   └── freertos/                   ← portmacro.h, port.h, port.c (trap handler,
│   │                                      stack init, CLINT timer), heap_4.c, demo.c
│   └── tools/
│       ├── quantize.py                 ← INT8 PTQ: symmetric per-tensor, exports C header
│       ├── gen_test_vectors.py         ← generates test_vectors.h via numpy
│       └── test_quantize.py           ← 34 Python checks for quantize.py helpers
│
├── phase12_validation/
│   ├── tools/
│   │   ├── train_mnist.py              ← PyTorch 784→128→10 MLP training (~98% accuracy)
│   │   └── gen_weights_numpy.py        ← numpy-only weight generator for sim (no PyTorch)
│   └── sw/
│       ├── weights.h                   ← INT8 weights + nn_layer_t initialisers
│       ├── benchmark.c                 ← RISC-V firmware: times FC 784→128, FC 128→10,
│       │                                  full MNIST forward, UART throughput
│       ├── test_weights.c              ← host-side smoke test (23/23 PASS, no toolchain needed)
│       ├── Makefile                    ← builds benchmark.elf + mnist/mnist.elf
│       └── mnist/
│           └── main.c                  ← RISC-V MNIST demo: infers 10 images, prints results
│
├── README.md
└── CLAUDE.md
```
