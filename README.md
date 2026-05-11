# RISC-V AI SoC

**A complete RISC-V AI SoC built from scratch — synthesized on Sky130 130nm**

```
RISC-V Core → L1 Cache → AXI4 Interconnect → AI Accelerator → Full Integration
```

## Results

| Metric | Value |
|--------|-------|
| Total cell area | TBD (Phase 6) |
| Fmax (Sky130 130nm) | TBD (Phase 6) |
| Dynamic power | TBD (Phase 6) |
| Formal proofs | 4 SVA properties (Phase 3) |
| Integration test | RISC-V firmware offloads 4×4 matrix multiply |

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
| 0 | Environment + SystemVerilog basics | 🔄 In Progress |
| 1 | 5-stage RV32I pipeline (hazard unit, forwarding) | ⏳ |
| 2 | Direct-mapped write-back L1 cache (4KB) | ⏳ |
| 3 | AXI4 3×3 crossbar + AXI-APB bridge | ⏳ |
| 4 | 4×4 systolic MAC array accelerator | ⏳ |
| 5 | Full SoC integration | ⏳ |
| 6 | OpenLane synthesis (area, Fmax, power) | ⏳ |
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
