# 2. CPU Reference

## Pipeline Diagram

```
  PC    │  IF  │  ID  │  EX  │  MEM │  WB
  ──────┼──────┼──────┼──────┼──────┼──────
  +0    │ Fetch│      │      │      │
  +4    │      │Decode│      │      │
  +8    │      │      │Execute│     │
  +12   │      │      │      │Memory│
  +16   │      │      │      │      │ WriteB
```

**Forwarding:** EX→EX and MEM→EX paths eliminate all RAW hazards except load-use.  
**Load-use stall:** 1-cycle bubble inserted when a load result is used in the immediately following instruction.  
**Branch:** Resolved in EX stage with static not-taken prediction; 2-cycle flush penalty on misprediction.

## ISA Extensions

| Extension | Description |
|-----------|-------------|
| I | Base 32-bit integer |
| M | Hardware multiply/divide (32-cycle DIV, 1-cycle MUL) |
| A | Atomic: LR.W/SC.W/AMO{ADD,AND,OR,XOR,SWAP,MIN,MAX}W |
| C | Compressed 16-bit instructions (software expander in fetch stage) |
| Zicsr | Control and Status Registers |

## CSR Table

| CSR Address | Name | Access | Description |
|-------------|------|--------|-------------|
| 0xF11 | mvendorid | RO | Vendor ID (0x00000000 = non-commercial) |
| 0xF12 | marchid | RO | Architecture ID (0x00000001) |
| 0xF13 | mimpid | RO | Implementation ID (0x20260601) |
| 0xF14 | mhartid | RO | Hart ID (0 = single core) |
| 0x300 | mstatus | RW | Machine status (MIE, MPIE, MPP) |
| 0x301 | misa | RO | ISA and extensions (RV32IMAC) |
| 0x304 | mie | RW | Machine interrupt enable (MSIE, MTIE, MEIE) |
| 0x305 | mtvec | RW | Machine trap vector base (direct or vectored) |
| 0x340 | mscratch | RW | Scratch register for trap handlers |
| 0x341 | mepc | RW | Machine exception PC |
| 0x342 | mcause | RW | Machine trap cause |
| 0x343 | mtval | RW | Machine trap value (fault address for load/store) |
| 0x344 | mip | RW | Machine interrupt pending |
| 0x3A0 | pmpcfg0 | RW | PMP configuration for regions 0–3 |
| 0x3A1 | pmpcfg1 | RW | PMP configuration for regions 4–7 |
| 0x3B0–0x3B7 | pmpaddr0–7 | RW | PMP address registers (NAPOT encoding) |
| 0xB00 | mcycle | RW | Machine cycle counter (low 32 bits) |
| 0xB80 | mcycleh | RW | Machine cycle counter (high 32 bits) |
| 0xB02 | minstret | RW | Instructions retired (low 32 bits) |
| 0xB82 | minstreth | RW | Instructions retired (high 32 bits) |

## Exception/Interrupt Handling

Traps are taken to `mtvec` in direct mode (bit[1:0] = 00) or vectored mode (bit[1:0] = 01).

| mcause | Source |
|--------|--------|
| 0x80000003 | Machine software interrupt (MSIP via CLINT) |
| 0x80000007 | Machine timer interrupt (MTIP via CLINT) |
| 0x8000000B | Machine external interrupt (MEIP via PLIC) |
| 0x00000000 | Instruction address misaligned |
| 0x00000002 | Illegal instruction |
| 0x00000003 | Breakpoint (EBREAK / hardware trigger) |
| 0x00000004 | Load address misaligned |
| 0x00000006 | Store address misaligned |
| 0x00000008 | Environment call from M-mode (ECALL) |

## PMP Regions

8 regions; addresses in NAPOT encoding: `pmpaddr = (base >> 2) | ((size >> 3) - 1)`.

Typical firmware configuration (see `phase19_security/sw/pmp_config.c`):
- Region 0: ROM (0x0000_0000 – 0x0000_7FFF), R+X
- Region 1: SRAM (0x2000_0000 – 0x2003_FFFF), R+W+X
- Region 2: MMIO (0x1000_0000 – 0x1FFF_FFFF), R+W
