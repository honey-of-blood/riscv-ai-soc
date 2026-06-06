CROSS   ?= riscv32-unknown-elf
ARCH    ?= -march=rv32imc -mabi=ilp32

.PHONY: all bootloader hello clean test

all: bootloader hello

bootloader:
	$(MAKE) -C sw/bootloader CROSS=$(CROSS) ARCH="$(ARCH)"

hello: bootloader
	$(CROSS)-gcc $(ARCH) -O2 -Wall -Werror \
	    -T sw/bsp/linker_app.ld -nostartfiles \
	    sw/bsp/crt0_app.S sw/bsp/syscalls.c sw/hello/main.c \
	    -o hello.elf
	$(CROSS)-objcopy -O verilog --verilog-data-width=4 hello.elf hello.hex
	$(CROSS)-size hello.elf

test:
	python tb/run_tests.py

clean:
	$(MAKE) -C sw/bootloader clean
	rm -f hello.elf hello.hex
