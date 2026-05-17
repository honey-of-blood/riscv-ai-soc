PH3_RTL := ../../../../phase3_axi/rtl
PH4_RTL := ../../../rtl
BUILD   := ./build

VLTOR_FLAGS := --sv --timing --top-module crossbar_accel_tb \
               -Wno-TIMESCALEMOD -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE -Wno-INITIALDLY \
               --assert --trace-fst --cc --exe --build

SRCS := $(PH3_RTL)/axi4_crossbar.sv \
        $(PH3_RTL)/axi_sram.sv \
        $(PH4_RTL)/pe.sv \
        $(PH4_RTL)/systolic_array.sv \
        $(PH4_RTL)/accel_top.sv \
        crossbar_accel_tb.sv

.PHONY: all run clean waves

all: $(BUILD)/crossbar_accel_tb

$(BUILD)/crossbar_accel_tb:
	mkdir -p $(BUILD)
	verilator $(VLTOR_FLAGS) \
	    -o crossbar_accel_tb \
	    --Mdir $(BUILD) \
	    $(SRCS) \
	    tb_main.cpp

run: $(BUILD)/crossbar_accel_tb
	$(BUILD)/crossbar_accel_tb

waves: $(BUILD)/crossbar_accel_tb
	$(BUILD)/crossbar_accel_tb --fst $(BUILD)/crossbar_accel_tb.fst
	gtkwave $(BUILD)/crossbar_accel_tb.fst &

clean:
	rm -rf $(BUILD)
