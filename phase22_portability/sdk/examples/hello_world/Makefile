# hello_world/Makefile — Build RV32 Hello World firmware
CROSS  := riscv32-unknown-elf-
CC     := $(CROSS)gcc
LD     := $(CROSS)gcc
OBJCOPY:= $(CROSS)objcopy

SDK    := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../..
BSP    := $(SDK)/bsp
LINKER := $(BSP)/../../../phase16_firmware/sw/bsp/linker_app.ld

CFLAGS := -march=rv32imac_zicsr -mabi=ilp32 -Os -g \
          -ffunction-sections -fdata-sections \
          -I$(BSP)/include \
          -Wall -Wextra -DCPU_HZ=100000000UL

LDFLAGS := -T$(LINKER) -nostartfiles -Wl,--gc-sections

SRCS   := main.c \
          $(BSP)/src/uart.c \
          $(BSP)/src/gpio.c \
          $(BSP)/src/syscalls.c \
          $(SDK)/../../../phase16_firmware/sw/bsp/crt0_app.S

TARGET := hello_world

all: $(TARGET).bin

$(TARGET).elf: $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	@echo "Built $(TARGET).bin ($$(wc -c < $(TARGET).bin) bytes)"

flash: $(TARGET).bin
	python3 $(SDK)/../../tools/upload.py $(TARGET).bin

clean:
	rm -f $(TARGET).elf $(TARGET).bin

.PHONY: all flash clean
