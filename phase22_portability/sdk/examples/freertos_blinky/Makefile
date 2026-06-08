# freertos_blinky/Makefile
CROSS  := riscv32-unknown-elf-
CC     := $(CROSS)gcc
SDK    := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../..
BSP    := $(SDK)/bsp
FREERTOS := $(SDK)/../../freertos

CFLAGS := -march=rv32imac_zicsr -mabi=ilp32 -Os -g \
          -ffunction-sections -fdata-sections \
          -I$(BSP)/include \
          -I$(FREERTOS)/include \
          -I$(FREERTOS)/portable/GCC/RISC-V \
          -DCPU_HZ=100000000UL

LDFLAGS := -T$(BSP)/../../../phase16_firmware/sw/bsp/linker_app.ld \
           -nostartfiles -Wl,--gc-sections

SRCS := main.c \
        $(BSP)/src/uart.c $(BSP)/src/gpio.c $(BSP)/src/syscalls.c \
        $(BSP)/../../../phase16_firmware/sw/bsp/crt0_app.S \
        $(FREERTOS)/tasks.c $(FREERTOS)/list.c $(FREERTOS)/queue.c \
        $(FREERTOS)/timers.c \
        $(FREERTOS)/portable/GCC/RISC-V/port.c \
        $(FREERTOS)/portable/MemMang/heap_4.c

all: freertos_blinky.bin
freertos_blinky.elf: $(SRCS) ; $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
freertos_blinky.bin: freertos_blinky.elf ; $(CROSS)objcopy -O binary $< $@
clean: ; rm -f freertos_blinky.elf freertos_blinky.bin
.PHONY: all clean
