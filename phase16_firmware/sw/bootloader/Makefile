CROSS   ?= riscv32-unknown-elf
CC       = $(CROSS)-gcc
OBJCOPY  = $(CROSS)-objcopy
OBJDUMP  = $(CROSS)-objdump

ARCH    = -march=rv32imc -mabi=ilp32
CFLAGS  = $(ARCH) -O2 -nostdlib -nostartfiles -ffreestanding \
          -Wall -Wextra -Werror
LDFLAGS = $(ARCH) -T linker_boot.ld -nostdlib -nostartfiles

SRCS    = crt0.S uart.c xmodem.c main.c
OBJS    = $(SRCS:.c=.o)
OBJS   := $(OBJS:.S=.o)

ELF     = bootloader.elf
HEX     = bootloader.hex
DUMP    = bootloader.dump

.PHONY: all clean

all: $(HEX) $(DUMP)

$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.S
	$(CC) $(ARCH) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(HEX): $(ELF)
	$(OBJCOPY) -O verilog --verilog-data-width=4 $< $@

$(DUMP): $(ELF)
	$(OBJDUMP) -D -M no-aliases $< > $@

clean:
	rm -f $(OBJS) $(ELF) $(HEX) $(DUMP)
