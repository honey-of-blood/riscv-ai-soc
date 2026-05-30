PH1   := ../../phase1_riscv_core/rtl
PH2   := ../../phase2_cache/rtl
PH3   := ../../phase3_axi/rtl
PH4   := ../../phase4_accelerator/rtl
PH5   := ../../phase5_soc/rtl
PH8   := ../../phase8_peripherals/rtl
PH9   := ../../phase9_accel_v2/rtl
RTL   := ../rtl
FW    := ../../phase9_accel_v2/fw
BUILD := ./build

VFLAGS := --sv --timing \
          -Wno-TIMESCALEMOD -Wno-MULTIDRIVEN -Wno-CASEINCOMPLETE \
          -Wno-INITIALDLY -Wno-UNDRIVEN -Wno-UNUSED \
          --assert --trace-fst --cc --exe --build

BRAM_SRCS  := $(RTL)/mem_bram_backend.sv

SOC_SRCS := $(PH1)/alu.sv \
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
            $(PH1)/riscv_core.sv \
            $(PH2)/cache_tag_array.sv \
            $(PH2)/cache_data_array.sv \
            $(PH2)/cache_controller.sv \
            $(PH2)/cache_top.sv \
            $(PH3)/axi4_crossbar.sv \
            $(PH3)/axi_apb_bridge.sv \
            $(PH4)/pe.sv \
            $(PH9)/systolic_array.sv \
            $(PH9)/scratchpad.sv \
            $(PH9)/accel_top_v2.sv \
            $(PH9)/dma.sv \
            $(PH5)/instr_rom.sv \
            $(PH5)/apb_regs.sv \
            $(PH5)/dmem_axi_adapter.sv \
            $(PH5)/axi4_burst_to_lite.sv \
            $(PH8)/apb_demux.sv \
            $(PH8)/uart.sv \
            $(PH8)/gpio.sv \
            $(PH8)/timer.sv \
            $(PH8)/spi.sv \
            $(PH8)/clint.sv \
            $(PH8)/plic.sv \
            $(PH5)/soc_top.sv \
            $(RTL)/mem_bram_backend.sv

.PHONY: all bram soc_ph10 run_bram run_soc_ph10 waves_bram waves_soc_ph10 clean

all: bram soc_ph10

bram: $(BUILD)/mem_bram_tb
$(BUILD)/mem_bram_tb:
	mkdir -p $(BUILD)
	verilator $(VFLAGS) --top-module mem_bram_tb \
	    -o mem_bram_tb --Mdir $(BUILD) \
	    $(BRAM_SRCS) mem_bram_tb.sv $(abspath bram_main.cpp)

soc_ph10: $(BUILD)/soc_ph10_tb
$(BUILD)/soc_ph10_tb:
	mkdir -p $(BUILD)
	cp $(FW)/firmware.hex $(BUILD)/firmware.hex
	verilator $(VFLAGS) --top-module soc_ph10_tb \
	    -o soc_ph10_tb --Mdir $(BUILD) \
	    $(SOC_SRCS) soc_ph10_tb.sv $(abspath soc_ph10_main.cpp)

run_bram: $(BUILD)/mem_bram_tb
	./$(BUILD)/mem_bram_tb

run_soc_ph10: $(BUILD)/soc_ph10_tb
	cd $(BUILD) && ./soc_ph10_tb

waves_bram: $(BUILD)/mem_bram_tb
	./$(BUILD)/mem_bram_tb --fst $(BUILD)/mem_bram.fst
	gtkwave $(BUILD)/mem_bram.fst &

waves_soc_ph10: $(BUILD)/soc_ph10_tb
	cd $(BUILD) && ./soc_ph10_tb --fst soc_ph10.fst
	gtkwave $(BUILD)/soc_ph10.fst &

clean:
	rm -rf $(BUILD)
