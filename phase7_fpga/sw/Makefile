# GCC toolchain Makefile for RV32IM SoC firmware
# Requires: riscv32-unknown-elf-gcc (or riscv64-unknown-elf-gcc with -m32)
# Output:   firmware.hex  — loaded into instr_rom.sv via $readmemh

CROSS   ?= riscv32-unknown-elf
CC       = $(CROSS)-gcc
OBJCOPY  = $(CROSS)-objcopy
OBJDUMP  = $(CROSS)-objdump

# RV32IM, no float ABI, no standard libs (bare-metal)
ARCH     = -march=rv32im -mabi=ilp32
CFLAGS   = $(ARCH) -O2 -nostdlib -nostartfiles -ffreestanding -Wall -Wextra
LDFLAGS  = $(ARCH) -T linker.ld -nostdlib -nostartfiles

SRCS     = crt0.S main.c
OBJS     = $(SRCS:.c=.o)
OBJS    := $(OBJS:.S=.o)
ELF      = firmware.elf
HEX      = firmware.hex
DUMP     = firmware.dump

.PHONY: all clean

all: $(HEX) $(DUMP)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.S
	$(CC) $(ARCH) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Verilog hex: 32-bit words, big-endian byte order per word
$(HEX): $(ELF)
	$(OBJCOPY) -O verilog --verilog-data-width=4 $< $@

$(DUMP): $(ELF)
	$(OBJDUMP) -D -M no-aliases $< > $@

clean:
	rm -f $(OBJS) $(ELF) $(HEX) $(DUMP)

# Usage:
#   make                    # build with default riscv32-unknown-elf-gcc
#   make CROSS=riscv64-unknown-elf   # if only 64-bit toolchain is installed
