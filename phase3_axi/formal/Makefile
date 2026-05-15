RTL      := ../rtl
BUILD    := ./build
VENV_BIN := /home/bhaavesh/projects/vlsi_projects/soc/.venv/bin
export PATH := $(VENV_BIN):$(PATH)

# Bounded model-check depth (cycles). 20 is enough for all 4 properties.
BMC_DEPTH := 40

.PHONY: all prove clean

all: prove

$(BUILD):
	mkdir -p $(BUILD)

# Step 1: Elaborate with -DFORMAL, write SMT2.
# Properties (P1-P4) are embedded in axi4_crossbar.sv under `ifdef FORMAL.
# crossbar_formal.sv provides a top-level with unconstrained free inputs.
$(BUILD)/crossbar.smt2: crossbar_formal.sv $(RTL)/axi4_crossbar.sv | $(BUILD)
	yosys -p " \
	  read_verilog -sv -formal -DFORMAL \
	    $(RTL)/axi4_crossbar.sv crossbar_formal.sv; \
	  hierarchy -check -top crossbar_formal; \
	  prep -top crossbar_formal; \
	  async2sync; dffunmap; \
	  write_smt2 -wires $(BUILD)/crossbar.smt2" \
	  2>&1 | tee $(BUILD)/yosys.log

# Step 2: Bounded model check — prove all asserts hold for BMC_DEPTH steps.
prove: $(BUILD)/crossbar.smt2
	@echo "Running yosys-smtbmc (solver=z3, depth=$(BMC_DEPTH)) ..."
	yosys-smtbmc -s z3 -t $(BMC_DEPTH) --presat \
	  $(BUILD)/crossbar.smt2 \
	  2>&1 | tee $(BUILD)/smtbmc.log
	@echo ""; \
	if grep -q "FAILED" $(BUILD)/smtbmc.log; then \
	  echo "*** FORMAL: COUNTEREXAMPLE FOUND — see $(BUILD)/smtbmc.log ***"; \
	  exit 1; \
	else \
	  echo "*** FORMAL: ALL PROPERTIES PROVED (depth=$(BMC_DEPTH)) ***"; \
	fi

clean:
	rm -rf $(BUILD)
