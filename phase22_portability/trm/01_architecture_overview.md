# 1. Architecture Overview

## Block Diagram

```
 ┌─────────────────────────────────────────────────────────────────────┐
 │                          RV32 AI SoC                                │
 │                                                                     │
 │  ┌────────────────┐    AXI4       ┌──────────────────────────────┐  │
 │  │  RV32IMAC Core │◄─────────────►│  AXI4 3×3 Crossbar           │  │
 │  │  5-stage pipe  │    (128-bit)  │                              │  │
 │  │  I-cache 4KB   │              │  S0: BRAM/DDR3  0x0000_xxxx  │  │
 │  │  BHT + BTB     │              │  S1: APB bridge 0x1000_xxxx  │  │
 │  │  HW MUL/DIV    │              │  S2: Accelerator 0x5000_xxxx  │  │
 │  │  RVC expander  │              └──────────────────────────────┘  │
 │  │  JTAG debug    │                         │                      │
 │  └────────────────┘               APB bridge│                      │
 │                                             ▼                      │
 │                              ┌──────────────────────────────────┐  │
 │                              │  APB Peripheral Bus (25 MHz)     │  │
 │                              │  UART · GPIO · Timer · SPI       │  │
 │                              │  CLINT · PLIC · I2C · WDT       │  │
 │                              └──────────────────────────────────┘  │
 │                                             │                      │
 │                              ┌──────────────────────────────────┐  │
 │                              │  AI Accelerator v3               │  │
 │                              │  16×16 INT4 systolic array       │  │
 │                              │  4 KB scratchpad + scatter-gather │  │
 │                              │  DMA + AES-128 + SHA-256         │  │
 │                              └──────────────────────────────────┘  │
 └─────────────────────────────────────────────────────────────────────┘
```

## Key Parameters

| Parameter | Value |
|-----------|-------|
| ISA | RV32IMAC + Zicsr |
| Pipeline | 5-stage in-order |
| CPU clock | 100 MHz (Artix-7 / DE1-SoC) |
| Peripheral clock | 25 MHz |
| I-cache | 4 KB direct-mapped |
| Branch predictor | 1-bit BHT + 8-entry BTB |
| Data memory | 64 KB BRAM (phase1–7) / external DDR3 (phase10+) |
| Debug | DM 0.13, JTAG TAP, 8 hardware breakpoints |
| PMP | 8 regions |

## Clock Domains

| Domain | Frequency | Source |
|--------|-----------|--------|
| `clk_cpu` | 100 MHz | MMCM/PLL from 100 MHz oscillator |
| `clk_peri` | 25 MHz | MMCM/PLL ÷ 4 |
| `clk_jtag` | ≤ 25 MHz | External JTAG TCK |

All clock-domain crossings use 2-FF synchronizers. The AXI crossbar runs at `clk_cpu`. The APB bus runs at `clk_peri` (AXI→APB bridge handles the crossing).

## FPGA Support Matrix

| Feature | Artix-7 | Cyclone V | ECP5 |
|---------|---------|-----------|------|
| Synthesis | Vivado 2023.1 | Quartus Prime 18.1 | Yosys 0.33 |
| P&R | Vivado | Quartus | nextpnr-ecp5 |
| BRAM | RAMB36E1 | M10K | EBR |
| PLL | MMCME2_ADV | altpll | EHXPLLL |
| DSP MUL | DSP48E1 | lpm_mult | MULT18X18D |
| JTAG | BSCANE2 | altera_jtag_sld_node | JTAGG |
| Max Fmax | ~130 MHz | ~120 MHz | ~100 MHz |
