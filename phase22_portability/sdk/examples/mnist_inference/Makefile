# mnist_inference/Makefile
CROSS  := riscv32-unknown-elf-
CC     := $(CROSS)gcc
SDK    := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))../..
BSP    := $(SDK)/bsp

CFLAGS := -march=rv32imac_zicsr -mabi=ilp32 -O2 -g \
          -ffunction-sections -fdata-sections \
          -I$(BSP)/include -I. \
          -DCPU_HZ=100000000UL
LDFLAGS := -T$(BSP)/../../../phase16_firmware/sw/bsp/linker_app.ld \
           -nostartfiles -Wl,--gc-sections
SRCS := main.c \
        $(BSP)/src/uart.c $(BSP)/src/accel.c \
        $(BSP)/src/syscalls.c \
        $(BSP)/../../../phase16_firmware/sw/bsp/crt0_app.S

# Generate weights from ONNX model (requires Python + onnx + numpy)
weights_mnist_int4.h: model_mnist.onnx
	python3 $(SDK)/../../tools/onnx_to_c.py $< --out $@ --quantize int4

all: mnist_inference.bin
mnist_inference.elf: $(SRCS) ; $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
mnist_inference.bin: mnist_inference.elf ; $(CROSS)objcopy -O binary $< $@
clean: ; rm -f mnist_inference.elf mnist_inference.bin
.PHONY: all clean
