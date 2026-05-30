PH4   := ../../phase4_accelerator/rtl
RTL   := ../rtl
BUILD := ./build

VFLAGS := --sv --timing \
          -Wno-TIMESCALEMOD -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE \
          -Wno-INITIALDLY -Wno-UNDRIVEN -Wno-UNUSED \
          --assert --trace-fst --cc --exe --build

ACCEL_SRCS := $(PH4)/pe.sv \
              $(RTL)/systolic_array.sv \
              $(RTL)/scratchpad.sv \
              $(RTL)/accel_top_v2.sv

DMA_SRCS   := $(RTL)/dma.sv

.PHONY: all accel dma run_accel run_dma waves_accel waves_dma clean

all: accel dma

accel: $(BUILD)/accel_v2_tb
$(BUILD)/accel_v2_tb:
	mkdir -p $(BUILD)
	verilator $(VFLAGS) --top-module accel_v2_tb \
	    -o accel_v2_tb --Mdir $(BUILD) \
	    $(ACCEL_SRCS) accel_v2_tb.sv $(abspath accel_v2_main.cpp)

dma: $(BUILD)/dma_tb
$(BUILD)/dma_tb:
	mkdir -p $(BUILD)
	verilator $(VFLAGS) --top-module dma_tb \
	    -o dma_tb --Mdir $(BUILD) \
	    $(DMA_SRCS) dma_tb.sv $(abspath dma_main.cpp)

run_accel: $(BUILD)/accel_v2_tb
	./$(BUILD)/accel_v2_tb

run_dma: $(BUILD)/dma_tb
	./$(BUILD)/dma_tb

waves_accel: $(BUILD)/accel_v2_tb
	./$(BUILD)/accel_v2_tb --fst $(BUILD)/accel_v2.fst
	gtkwave $(BUILD)/accel_v2.fst &

waves_dma: $(BUILD)/dma_tb
	./$(BUILD)/dma_tb --fst $(BUILD)/dma.fst
	gtkwave $(BUILD)/dma.fst &

clean:
	rm -rf $(BUILD)
