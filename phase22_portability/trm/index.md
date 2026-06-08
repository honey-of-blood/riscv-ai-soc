# RV32 AI SoC — Technical Reference Manual

**Version:** 1.0  **Date:** 2026-06

This document is the authoritative reference for firmware engineers integrating software with the RV32 AI SoC.

## Contents

| Section | Title |
|---------|-------|
| [01](01_architecture_overview.md) | Architecture Overview |
| [02](02_cpu_reference.md) | CPU Reference |
| [03](03_memory_map.md) | Memory Map |
| [04](04_peripheral_reference.md) | Peripheral Reference |
| [05](05_accelerator_reference.md) | AI Accelerator Reference |
| [06](06_debug_guide.md) | Debug Guide |
| [07](07_getting_started.md) | Getting Started |
| [08](08_benchmarks.md) | Performance Benchmarks |

## Quick Links

- [UART register map](04_peripheral_reference.md#uart)
- [GPIO register map](04_peripheral_reference.md#gpio)
- [Accelerator programming model](05_accelerator_reference.md#programming-model)
- [Hello World in 5 minutes](07_getting_started.md)
- [OpenOCD connection](06_debug_guide.md#openocd-setup)

## Platform Support

| Platform | Toolchain | Status |
|----------|-----------|--------|
| DE1-SoC (Cyclone V) | Quartus 23.x | Supported |
| ULX3S (ECP5) | Yosys + nextpnr | Supported |
| Simulation | Icarus Verilog 12 | Supported |

## Document Conventions

- Register fields use `[bit_high:bit_low]` notation.
- All addresses are byte addresses in hexadecimal (e.g., `0x1000_1000`).
- **RW** = read/write, **RO** = read-only, **WO** = write-only, **W1C** = write-1-to-clear.
- Reserved bits must be written as 0 and ignored on read.

## Revision History

| Rev | Date    | Changes |
|-----|---------|---------|
| 1.0 | 2026-06 | Initial release — all 8 sections |
