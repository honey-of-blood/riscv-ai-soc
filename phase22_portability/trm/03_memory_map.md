# 3. Memory Map

## Full Address Space

| Base | Top | Size | Region | Access |
|------|-----|------|--------|--------|
| 0x0000_0000 | 0x0000_FFFF | 64 KB | Instruction + Data BRAM | R/W/X |
| 0x2000_0000 | 0x2003_FFFF | 256 KB | External SRAM / DDR3 window | R/W |
| 0x1000_0000 | 0x1000_0FFF | 4 KB | APB register file (Phase 5 compat) | R/W |
| 0x1000_1000 | 0x1000_1FFF | 4 KB | UART0 | R/W |
| 0x1000_2000 | 0x1000_2FFF | 4 KB | GPIO0 | R/W |
| 0x1000_3000 | 0x1000_3FFF | 4 KB | Timer / mtime | R/W |
| 0x1000_4000 | 0x1000_4FFF | 4 KB | SPI0 | R/W |
| 0x1000_5000 | 0x1000_5FFF | 4 KB | CLINT (msip + mtime) | R/W |
| 0x1000_6000 | 0x1000_6FFF | 4 KB | PLIC | R/W |
| 0x1000_7000 | 0x1000_7FFF | 4 KB | I2C0 | R/W |
| 0x1000_8000 | 0x1000_8FFF | 4 KB | WDT | R/W |
| 0x5000_0000 | 0x5000_0FFF | 4 KB | AI Accelerator control regs | R/W |
| 0x5000_1000 | 0x5000_1FFF | 4 KB | AI Accelerator scratchpad | R/W |
| 0x5001_0000 | 0x5001_0FFF | 4 KB | AES-128 accelerator | R/W |
| 0x5002_0000 | 0x5002_0FFF | 4 KB | SHA-256 accelerator | R/W |

## AXI Crossbar Slave Assignment

The AXI4 3×3 crossbar (phase3) routes by address prefix:

| Slave | Address Range | Module |
|-------|---------------|--------|
| S0 | 0x0000_xxxx – 0x1FFF_xxxx | BRAM / DDR3 backend |
| S1 | 0x1000_xxxx | AXI→APB bridge → peripheral bus |
| S2 | 0x5000_xxxx | AI Accelerator v3 |

## Linker Script Regions

Typical linker script layout (64 KB BRAM):

```
MEMORY {
  ROM  (rx)  : ORIGIN = 0x00000000, LENGTH = 32K  /* bootloader + app */
  SRAM (rwx) : ORIGIN = 0x00008000, LENGTH = 32K  /* stack + heap + data */
}
```

For DDR3-based systems (Phase 10+), update SRAM to `0x20000000, LENGTH = 256K`.
