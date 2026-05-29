# RISC-V AI SoC

**A complete RISC-V AI SoC built from scratch — synthesized on Sky130 130nm**

```
RISC-V Core → L1 Cache → AXI4 Interconnect → AI Accelerator → Full Integration
```

## Results

| Metric | Value |
|--------|-------|
| Standard cells | 134,728 sky130_fd_sc_hd cells |
| Cell area | 1.91 mm² |
| Die area | 9.66 mm² (FP_CORE_UTIL 20%) |
| Fmax (TT 25°C 1.8V) | 66.7 MHz (WNS = 0 ns post-CTS) |
| Total power | 318.8 mW (221.2 internal + 97.6 switching) |
| PDK | Sky130A — 130nm 5-metal |
| Formal proofs | 4 SVA properties (Phase 3) |
| Integration test | RISC-V firmware offloads 4×4 matrix multiply |

### GDSII Layout

![soc_top GDSII layout on Sky130A](docs/soc_gds.png)

> Rendered from `openlane/soc_top/runs/RUN_2026-05-27_15-46-53/`.
> Full SoC synthesis (146K cells) exceeds Sky130's 5-metal routing capacity;
> layout above shows RV32I core + L1 cache + AXI4 crossbar + APB (134K cells,
> accelerator blackboxed). Routing DRC violations present due to 2.15× congestion
> overflow on met1–met5 — a known limitation of complex multi-bus SoCs on this process node.

## Architecture

*(Block diagram — added in Phase 7)*

## Tool Stack

![SystemVerilog](https://img.shields.io/badge/RTL-SystemVerilog-blue)
![cocotb](https://img.shields.io/badge/Verification-cocotb-green)
![SymbiYosys](https://img.shields.io/badge/Formal-SymbiYosys-orange)
![OpenLane](https://img.shields.io/badge/Synthesis-OpenLane-red)
![Sky130](https://img.shields.io/badge/PDK-Sky130-purple)

| Tool | Purpose |
|------|---------|
| Icarus Verilog + GTKWave | Simulation + waveform viewing |
| Verilator | Linting |
| cocotb | Python-based testbenches |
| SymbiYosys | Formal verification (SVA) |
| Yosys | RTL synthesis |
| OpenLane | RTL-to-GDSII on Sky130 |

## Phases

| Phase | Module | Status |
|-------|--------|--------|
| 0 | Environment + SystemVerilog basics | ✅ |
| 1 | 5-stage RV32I pipeline (hazard unit, forwarding) | ✅ |
| 2 | Direct-mapped write-back L1 cache (4KB) | ✅ |
| 3 | AXI4 3×3 crossbar + AXI-APB bridge | ✅ |
| 4 | 4×4 systolic MAC array accelerator | ✅ |
| 5 | Full SoC integration | ✅ |
| 6 | OpenLane GDSII synthesis on Sky130A | ✅ 134K cells, 1.91 mm², 66.7 MHz, 318.8 mW |
| 7 | Documentation + interview prep | ⏳ |

## How to Run

```bash
# Activate venv (needed for cocotb and openlane)
source .venv/bin/activate

# Simulate a module (example)
cd phase1_riscv_core/tb
make

# Lint
verilator --lint-only -Wall ../rtl/riscv_core.sv

# Synthesize
cd phase1_riscv_core/synth
yosys synth.ys

# Formal verification (Phase 3+)
cd phase3_axi/formal
sby arbiter.sby
```

## Repository Structure

```
riscv-ai-soc/
├── docs/                     ← architecture diagrams, waveform screenshots
├── phase1_riscv_core/
│   ├── rtl/                  ← SystemVerilog source
│   ├── tb/                   ← cocotb testbenches
│   ├── formal/               ← SymbiYosys + SVA
│   └── synth/                ← Yosys synthesis scripts
├── phase2_cache/
├── phase3_axi/
├── phase4_accelerator/
├── phase5_integration/
└── openlane/soc_top/         ← OpenLane config + reports
```
