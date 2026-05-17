RTL   := ../../../rtl
TB    := .
BUILD := ./build

VLTOR_FLAGS := --sv --timing --top-module accel_tb_top -Wno-TIMESCALEMOD \
               -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE --assert --trace-fst \
               --cc --exe --build

SRCS := $(RTL)/pe.sv \
        $(RTL)/systolic_array.sv \
        $(RTL)/accel_top.sv \
        $(TB)/accel_if.sv \
        $(TB)/uvm_mini_pkg.sv \
        $(TB)/accel_tb_pkg.sv \
        $(TB)/accel_tb_top.sv

.PHONY: all run clean waves

all: $(BUILD)/accel_tb_top

$(BUILD)/accel_tb_top:
	mkdir -p $(BUILD)
	verilator $(VLTOR_FLAGS) \
	    -o accel_tb_top \
	    --Mdir $(BUILD) \
	    $(SRCS) \
	    tb_main.cpp

run: $(BUILD)/accel_tb_top
	$(BUILD)/accel_tb_top

waves: $(BUILD)/accel_tb_top
	$(BUILD)/accel_tb_top --fst $(BUILD)/accel_tb_top.fst
	gtkwave $(BUILD)/accel_tb_top.fst &

clean:
	rm -rf $(BUILD)
