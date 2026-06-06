PH1   := ../../phase1_riscv_core/rtl
PH2   := ../../phase2_cache/rtl
PH3   := ../../phase3_axi/rtl
PH4   := ../../phase4_accelerator/rtl
PH8   := ../../phase8_peripherals/rtl
PH9   := ../../phase9_accel_v2/rtl
PH15  := ../../phase15_perf/rtl
RTL   := ../rtl
FW    := ../fw
BUILD := ./build

VLTOR_FLAGS := --sv --timing --top-module soc_tb \
               -Wno-TIMESCALEMOD -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE \
               -Wno-INITIALDLY -Wno-UNDRIVEN -Wno-UNUSED \
               -Wno-WIDTHTRUNC -Wno-UNSIGNED \
               --assert --trace-fst --cc --exe --build

SRCS := $(PH1)/rvc_expander.sv \
        $(PH1)/csr_file.sv \
        $(PH1)/pmp_checker.sv \
        $(PH1)/atomic_unit.sv \
        $(PH1)/alu.sv \
        $(PH1)/reg_file.sv \
        $(PH1)/imm_gen.sv \
        $(PH1)/fetch_stage.sv \
        $(PH1)/pipeline_reg_IF_ID.sv \
        $(PH1)/decode_stage.sv \
        $(PH1)/pipeline_reg_ID_EX.sv \
        $(PH1)/execute_stage.sv \
        $(PH1)/pipeline_reg_EX_MEM.sv \
        $(PH1)/memory_stage.sv \
        $(PH1)/pipeline_reg_MEM_WB.sv \
        $(PH1)/writeback_stage.sv \
        $(PH1)/hazard_unit.sv \
        $(PH1)/forwarding_unit.sv \
        $(PH1)/mext_unit.sv \
        $(PH15)/branch_predictor.sv \
        $(PH1)/riscv_core.sv \
        $(PH2)/cache_tag_array.sv \
        $(PH2)/cache_data_array.sv \
        $(PH2)/cache_controller.sv \
        $(PH2)/cache_top.sv \
        $(PH3)/axi4_crossbar.sv \
        $(PH3)/axi_sram.sv \
        $(PH3)/axi_apb_bridge.sv \
        $(PH4)/pe.sv \
        $(PH9)/systolic_array.sv \
        $(PH9)/scratchpad.sv \
        $(PH9)/accel_top_v2.sv \
        $(PH9)/dma.sv \
        $(RTL)/instr_rom.sv \
        $(RTL)/apb_regs.sv \
        $(RTL)/dmem_axi_adapter.sv \
        $(RTL)/axi4_burst_to_lite.sv \
        $(PH8)/apb_demux.sv \
        $(PH8)/uart.sv \
        $(PH8)/gpio.sv \
        $(PH8)/timer.sv \
        $(PH8)/spi.sv \
        $(PH8)/clint.sv \
        $(PH8)/plic.sv \
        $(RTL)/soc_top.sv \
        soc_tb.sv

.PHONY: all run clean waves

all: $(BUILD)/soc_tb

$(BUILD)/soc_tb:
	mkdir -p $(BUILD)
	cp $(FW)/firmware.hex $(BUILD)/firmware.hex
	verilator $(VLTOR_FLAGS) \
	    -o soc_tb \
	    --Mdir $(BUILD) \
	    $(SRCS) \
	    tb_main.cpp

run: $(BUILD)/soc_tb
	cd $(BUILD) && ./soc_tb

waves: $(BUILD)/soc_tb
	cd $(BUILD) && ./soc_tb --fst soc_tb.fst
	gtkwave $(BUILD)/soc_tb.fst &

clean:
	rm -rf $(BUILD)
