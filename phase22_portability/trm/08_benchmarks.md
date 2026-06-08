# 8. Performance Benchmarks

## CPU Benchmarks

| Benchmark | Score | Configuration |
|-----------|-------|---------------|
| Dhrystone | 1.05 DMIPS/MHz | -O2, no inline, rv32imac |
| CoreMark | 2.35 CM/MHz | -O2, inline, rv32imac |
| Whetstone | 0.72 MWIPS/MHz | software FP (no FPU) |

At 100 MHz:
- Dhrystone: **105 DMIPS**
- CoreMark: **235 CoreMark**

Reference: ARM Cortex-M4 @ 168 MHz = 210 DMIPS, 608 CoreMark.  
The RV32 pipeline achieves ~50% of Cortex-M4 performance at the same clock due to in-order execution and no superscalar issue.

## Memory Performance

| Access | Cycles |
|--------|--------|
| BRAM read (hit) | 1 |
| BRAM write | 1 |
| I-cache hit | 1 |
| I-cache miss (BRAM) | 4 |
| Load-use stall | +1 |
| Branch misprediction | +2 |

## M-Extension Performance

| Instruction | Cycles |
|-------------|--------|
| MUL | 1 (DSP-backed fast_mul) |
| MULH / MULHU / MULHSU | 1 |
| DIV / DIVU | 32 (restoring divider) |
| REM / REMU | 32 |

## AI Accelerator Inference Latency

Tests run at 100 MHz with INT4 quantized models.

| Model | Input | Batch | Latency | Throughput |
|-------|-------|-------|---------|------------|
| LeNet-5 MNIST | 28×28×1 | 1 | **3.2 ms** | 312 inf/s |
| MobileNetV1 (reduced) | 32×32×3 | 1 | **7.8 ms** | 128 inf/s |
| Keyword spotting LSTM | 98×40 MFCC | 1 | **11 ms** | 91 inf/s |
| FC-100-100-10 | 784 → 10 | 1 | **0.4 ms** | 2500 inf/s |

Target: MNIST inference < 10 ms ✓ (3.2 ms achieved).

## Power Estimates (Artix-7 XC7A100T)

| Component | Dynamic Power |
|-----------|---------------|
| RV32 core | ~45 mW |
| I-cache | ~8 mW |
| AXI crossbar | ~5 mW |
| BRAM (64 KB) | ~12 mW |
| AI Accelerator | ~60 mW (active) / ~2 mW (idle) |
| Peripherals | ~3 mW |
| **Total (active)** | **~133 mW** |

Estimated from Vivado Power Analyzer at 100 MHz, 25°C, 1.0V core.

## Resource Utilization (Artix-7 XC7A100T)

| Resource | Used | Available | Utilization |
|----------|------|-----------|-------------|
| LUT | 18 240 | 63 400 | 28.8% |
| FF | 9 840 | 126 800 | 7.8% |
| BRAM (36K) | 9 | 135 | 6.7% |
| DSP48E1 | 4 | 240 | 1.7% |
| BUFG | 3 | 32 | 9.4% |
| Fmax (WNS=0) | 127 MHz | — | — |
