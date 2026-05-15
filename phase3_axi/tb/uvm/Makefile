RTL  := ../../rtl
TB   := .
BUILD := ./build

VLTOR_FLAGS := --sv --timing --top-module crossbar_tb_top -Wno-TIMESCALEMOD \
               -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE --assert --trace-fst \
               --cc --exe --build

SRCS := $(RTL)/axi4_crossbar.sv \
        $(RTL)/axi_sram.sv \
        $(TB)/axi4_if.sv \
        $(TB)/uvm_mini_pkg.sv \
        $(TB)/crossbar_tb_pkg.sv \
        $(TB)/crossbar_tb_top.sv

.PHONY: all run clean

all: $(BUILD)/crossbar_tb_top

$(BUILD)/crossbar_tb_top:
	mkdir -p $(BUILD)
	verilator $(VLTOR_FLAGS) \
	    -o crossbar_tb_top \
	    --Mdir $(BUILD) \
	    $(SRCS) \
	    tb_main.cpp

run: $(BUILD)/crossbar_tb_top
	$(BUILD)/crossbar_tb_top

waves: run
	gtkwave $(BUILD)/crossbar_tb_top.fst &

clean:
	rm -rf $(BUILD)
