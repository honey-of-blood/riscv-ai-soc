# secure_ota/Makefile
CROSS  := riscv32-unknown-elf-
CC     := $(CROSS)gcc
SDK    := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../..
BSP    := $(SDK)/bsp
CFLAGS := -march=rv32imac_zicsr -mabi=ilp32 -Os -g \
          -ffunction-sections -fdata-sections \
          -I$(BSP)/include -I. -DCPU_HZ=100000000UL
LDFLAGS := -T$(BSP)/../../../phase16_firmware/sw/bsp/linker_app.ld \
           -nostartfiles -Wl,--gc-sections
SRCS := main.c \
        $(BSP)/src/uart.c $(BSP)/src/syscalls.c \
        $(BSP)/../../../phase16_firmware/sw/bsp/crt0_app.S
all: secure_ota.bin
secure_ota.elf: $(SRCS) ; $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
secure_ota.bin: secure_ota.elf ; $(CROSS)objcopy -O binary $< $@
clean: ; rm -f secure_ota.elf secure_ota.bin
.PHONY: all clean
