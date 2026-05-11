VENV    := $(abspath ../../.venv)
COCOTB_CONFIG := $(VENV)/bin/cocotb-config

# Tell cocotb makefiles to use the venv Python, not the system Python
PYTHON_BIN := $(VENV)/bin/python3

SIM           ?= icarus
TOPLEVEL_LANG  = verilog
VERILOG_SOURCES = $(abspath ../rtl/$(MODULE_RTL).sv)
TOPLEVEL       = $(MODULE_RTL)
MODULE         = test_$(MODULE_RTL)

export PATH := $(VENV)/bin:$(PATH)

include $(shell $(COCOTB_CONFIG) --makefiles)/Makefile.sim

.PHONY: alu regfile clean

alu:
	$(MAKE) MODULE_RTL=alu

regfile:
	$(MAKE) MODULE_RTL=reg_file
