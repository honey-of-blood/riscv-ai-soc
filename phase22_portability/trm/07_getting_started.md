# 7. Getting Started

## Prerequisites

```bash
# Install toolchain
sudo apt install gcc-riscv64-unknown-elf   # or build from source
# OR use the prebuilt toolchain:
# https://github.com/xpack-dev-tools/riscv-none-elf-gcc-xpack/releases

# Install Yosys (synthesis check)
sudo apt install yosys

# Install Python dependencies
pip install cocotb cocotb-tools pyelftools
```

## 5-Minute Hello World {#hello-world}

**Step 1: Clone and configure**

```bash
git clone https://github.com/your-org/rv32-ai-soc.git
cd rv32-ai-soc
```

**Step 2: Build Hello World firmware**

```bash
cd phase22_portability/sdk/examples/hello_world
make
# → hello_world.bin (should be < 4 KB)
```

**Step 3: Flash to FPGA**

*Artix-7 / Nexys A7:*
```bash
# Open Vivado Hardware Manager, program FPGA with phase7/build/top.bit
# Then upload firmware:
python3 ../../tools/upload.py hello_world.bin
```

*DE1-SoC:*
```bash
# quartus_pgm -m jtag -o "p;build/rv32_soc_de1.sof"
# Then upload:
python3 ../../tools/upload.py hello_world.bin --port /dev/ttyUSB0
```

**Step 4: Open serial console**

```bash
screen /dev/ttyUSB0 115200
# Or:
minicom -D /dev/ttyUSB0 -b 115200
```

Expected output:
```
=== RV32 AI SoC Hello World ===
CPU clock : 100 MHz
UART baud : 115200
Fibonacci : 0 1 1 2 3 5 8 13 21 34 55 89
Blinking LEDs — press any key to stop
```

## Running Tests

```bash
# Phase 21 production verification (all 76 tests)
cd phase21_production/tb
source ../../.venv/bin/activate
python run_tests.py all

# Phase 22 portability tests
cd phase22_portability/tb
python run_tests.py
```

## Yosys Synthesis CI Check

```bash
# Verify no Yosys synthesis errors (no Vivado needed):
bash phase22_portability/scripts/ci_yosys_check.sh
```

## Directory Structure

```
rv32-ai-soc/
├── phase1_riscv_core/rtl/   — RV32IMAC pipeline RTL
├── phase8_peripherals/rtl/  — UART/GPIO/Timer/SPI/CLINT/PLIC
├── phase15_perf/rtl/        — I-cache, branch predictor
├── phase22_portability/
│   ├── rtl/                 — DE1-SoC FPGA top + Intel tech cells
│   ├── constraints/         — SDC + LPF pin constraints
│   ├── scripts/             — Quartus TCL, ECP5 Makefile, CI check
│   ├── zephyr/              — Board DTS + Kconfig
│   ├── sdk/                 — BSP headers + 5 example projects
│   └── trm/                 — This Technical Reference Manual
├── phase21_production/tb/   — 76-test production verification suite
└── README.md
```
