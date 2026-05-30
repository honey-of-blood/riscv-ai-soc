# Phase 12 firmware Makefile
# Builds benchmark.elf and mnist.elf for the RISC-V SoC.
#
# Prerequisites:
#   riscv32-unknown-elf-gcc  (or riscv64-unknown-elf-gcc)
#   weights.h                (run: python3 ../tools/train_mnist.py --quantize
#                             OR:  python3 ../tools/gen_weights_numpy.py)
#
# Usage:
#   make              # build both firmware images
#   make weights      # regenerate weights.h with numpy (no PyTorch needed)
#   make train        # train real MNIST model + quantize (needs PyTorch)
#   make clean

CROSS    ?= riscv32-unknown-elf
CC        = $(CROSS)-gcc
OBJCOPY   = $(CROSS)-objcopy
OBJDUMP   = $(CROSS)-objdump

ROOT      = ../../..
PH7_SW    = $(ROOT)/phase7_fpga/sw
PH8_HAL   = $(ROOT)/phase8_peripherals/sw/hal
PH11_NN   = $(ROOT)/phase11_sw/sw/nn
TOOLS     = ../tools

ARCH      = -march=rv32im -mabi=ilp32
CFLAGS    = $(ARCH) -O2 -nostdlib -nostartfiles -ffreestanding \
            -Wall -Wextra -I. -I$(PH11_NN) -I$(PH8_HAL)
LDFLAGS   = $(ARCH) -T $(PH7_SW)/linker.ld -nostdlib -nostartfiles

CRT0      = $(PH7_SW)/crt0.S
NN_C      = $(PH11_NN)/nn.c

.PHONY: all clean weights train

all: benchmark.elf benchmark.hex benchmark.dump \
     mnist/mnist.elf mnist/mnist.hex mnist/mnist.dump

# ── weights.h ────────────────────────────────────────────────────────────────
weights.h:
	python3 $(TOOLS)/gen_weights_numpy.py --output weights.h

weights: weights.h

train:
	python3 $(TOOLS)/train_mnist.py --quantize

# ── benchmark ────────────────────────────────────────────────────────────────
benchmark.elf: weights.h benchmark.c $(CRT0) $(NN_C)
	$(CC) $(LDFLAGS) $(CFLAGS) $(CRT0) benchmark.c $(NN_C) -o $@

benchmark.hex: benchmark.elf
	$(OBJCOPY) -O verilog --verilog-data-width=4 $< $@

benchmark.dump: benchmark.elf
	$(OBJDUMP) -D -M no-aliases $< > $@

# ── mnist demo ───────────────────────────────────────────────────────────────
mnist/mnist.elf: weights.h mnist/main.c $(CRT0) $(NN_C)
	$(CC) $(LDFLAGS) $(CFLAGS) -I. $(CRT0) mnist/main.c $(NN_C) -o $@

mnist/mnist.hex: mnist/mnist.elf
	$(OBJCOPY) -O verilog --verilog-data-width=4 $< $@

mnist/mnist.dump: mnist/mnist.elf
	$(OBJDUMP) -D -M no-aliases $< > $@

# ── clean ─────────────────────────────────────────────────────────────────────
clean:
	rm -f benchmark.elf benchmark.hex benchmark.dump
	rm -f mnist/mnist.elf mnist/mnist.hex mnist/mnist.dump
