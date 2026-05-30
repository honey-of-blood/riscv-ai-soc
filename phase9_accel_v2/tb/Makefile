PH1   := ../../phase1_riscv_core/rtl
PH2   := ../../phase2_cache/rtl
PH3   := ../../phase3_axi/rtl
PH4   := ../../phase4_accelerator/rtl
PH5   := ../../phase5_soc/rtl
PH8   := ../../phase8_peripherals/rtl
RTL   := ../rtl
FW    := ../fw
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

SP_SRCS    := $(RTL)/scratchpad.sv

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
            $(PH3)/axi_sram.sv \
            $(PH3)/axi_apb_bridge.sv \
            $(PH4)/pe.sv \
            $(RTL)/systolic_array.sv \
            $(RTL)/scratchpad.sv \
            $(RTL)/accel_top_v2.sv \
            $(RTL)/dma.sv \
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
            $(PH5)/soc_top.sv

.PHONY: all accel dma scratchpad soc_ph9 \
        run_accel run_dma run_scratchpad run_soc_ph9 \
        waves_accel waves_dma waves_scratchpad waves_soc_ph9 clean

all: scratchpad accel dma soc_ph9

scratchpad: $(BUILD)/scratchpad_tb
$(BUILD)/scratchpad_tb:
	mkdir -p $(BUILD)
	verilator $(VFLAGS) --top-module scratchpad_tb \
	    -o scratchpad_tb --Mdir $(BUILD) \
	    $(SP_SRCS) scratchpad_tb.sv $(abspath scratchpad_main.cpp)

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

soc_ph9: $(BUILD)/soc_ph9_tb
$(BUILD)/soc_ph9_tb:
	mkdir -p $(BUILD)
	cp $(FW)/firmware.hex $(BUILD)/firmware.hex
	verilator $(VFLAGS) --top-module soc_ph9_tb \
	    -o soc_ph9_tb --Mdir $(BUILD) \
	    $(SOC_SRCS) soc_ph9_tb.sv $(abspath soc_ph9_main.cpp)

run_scratchpad: $(BUILD)/scratchpad_tb
	./$(BUILD)/scratchpad_tb

run_accel: $(BUILD)/accel_v2_tb
	./$(BUILD)/accel_v2_tb

run_dma: $(BUILD)/dma_tb
	./$(BUILD)/dma_tb

run_soc_ph9: $(BUILD)/soc_ph9_tb
	cd $(BUILD) && ./soc_ph9_tb

waves_scratchpad: $(BUILD)/scratchpad_tb
	./$(BUILD)/scratchpad_tb --fst $(BUILD)/scratchpad.fst
	gtkwave $(BUILD)/scratchpad.fst &

waves_accel: $(BUILD)/accel_v2_tb
	./$(BUILD)/accel_v2_tb --fst $(BUILD)/accel_v2.fst
	gtkwave $(BUILD)/accel_v2.fst &

waves_dma: $(BUILD)/dma_tb
	./$(BUILD)/dma_tb --fst $(BUILD)/dma.fst
	gtkwave $(BUILD)/dma.fst &

waves_soc_ph9: $(BUILD)/soc_ph9_tb
	cd $(BUILD) && ./soc_ph9_tb --fst soc_ph9.fst
	gtkwave $(BUILD)/soc_ph9.fst &

clean:
	rm -rf $(BUILD)
