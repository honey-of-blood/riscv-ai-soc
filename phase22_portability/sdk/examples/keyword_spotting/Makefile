# keyword_spotting/Makefile
CROSS  := riscv32-unknown-elf-
CC     := $(CROSS)gcc
SDK    := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../..
BSP    := $(SDK)/bsp
CFLAGS := -march=rv32imac_zicsr -mabi=ilp32 -O2 -g \
          -ffunction-sections -fdata-sections \
          -I$(BSP)/include -I. -DCPU_HZ=100000000UL
LDFLAGS := -T$(BSP)/../../../phase16_firmware/sw/bsp/linker_app.ld \
           -nostartfiles -Wl,--gc-sections -lm
SRCS := main.c \
        $(BSP)/src/uart.c $(BSP)/src/accel.c $(BSP)/src/syscalls.c \
        $(BSP)/../../../phase16_firmware/sw/bsp/crt0_app.S
all: keyword_spotting.bin
keyword_spotting.elf: $(SRCS) ; $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
keyword_spotting.bin: keyword_spotting.elf ; $(CROSS)objcopy -O binary $< $@
clean: ; rm -f keyword_spotting.elf keyword_spotting.bin
.PHONY: all clean
