# 6. Debug Guide

## JTAG Hardware Connections

| JTAG Signal | Artix-7 (JD header) | DE1-SoC (GPIO_0) | ULX3S (J1) |
|-------------|---------------------|------------------|------------|
| TCK | JD[1] | GPIO_0[4] | GP[9] |
| TMS | JD[2] | GPIO_0[5] | GP[10] |
| TDI | JD[3] | GPIO_0[6] | GP[11] |
| TDO | JD[4] | GPIO_0[7] | GP[12] |
| GND | JD[5] | GPIO_0[8] | GND |

## OpenOCD Setup {#openocd-setup}

### OpenOCD Configuration

Create `openocd.cfg`:

```tcl
# openocd.cfg — RV32 AI SoC debug configuration
adapter driver ftdi
ftdi vid_pid 0x0403 0x6011   ;# FTDI 4232H (adjust for your adapter)
ftdi layout_init 0x0008 0x000b
ftdi layout_signal nSRST -data 0x0020

transport select jtag

set _CHIPNAME rv32soc
jtag newtap $_CHIPNAME cpu -irlen 5 -expected-id 0x00000001

set _TARGETNAME $_CHIPNAME.cpu
target create $_TARGETNAME riscv -chain-position $_CHIPNAME.cpu

# DM 0.13 compliant
riscv set_ir_idcode 0x11
riscv set_ir_dtmcs  0x10
riscv set_ir_dmi    0x11

init
reset halt
```

### Connecting

```bash
# Start OpenOCD (leave running in background)
openocd -f openocd.cfg &

# Connect GDB
riscv32-unknown-elf-gdb firmware.elf
(gdb) target extended-remote :3333
(gdb) monitor reset halt
(gdb) break main
(gdb) continue
```

## Common Debug Recipes

### Reset and Halt

```
(gdb) monitor reset halt
```

### Read CSRs

```
(gdb) info registers
(gdb) print/x $mcause
(gdb) print/x $mepc
```

### Set Hardware Breakpoint

```
(gdb) hbreak *0x00001234    ;# break at instruction address
```

### Read/Write Memory

```
(gdb) x/4wx 0x10001000      ;# read 4 words from UART base
(gdb) set {int}0x10001000 = 0x41  ;# write 'A' to UART THR
```

### Load and Run Firmware

```
(gdb) load firmware.elf
(gdb) continue
```

## Hardware Triggers

The debug module supports 8 hardware triggers (breakpoints or watchpoints):

```
(gdb) watch variable_name      ;# data watchpoint
(gdb) rwatch *0x20001000       ;# read watchpoint
(gdb) awatch *0x20001000       ;# access watchpoint (read + write)
```

## Debug Memory Map

| Address | Description |
|---------|-------------|
| 0x0000_F000 | Debug program buffer (16 instructions) |
| 0x0000_F040 | Debug data registers (dm_data0..dm_data11) |
| 0x0000_F800 | Debug ROM (DM 0.13 implementation) |
