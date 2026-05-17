// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing declarations
#include "verilated_fst_c.h"


void Vsoc_tb___024root__traceDeclTypesSub0(VerilatedFst* tracep) {
    {
        const char* __VenumItemNames[]
        = {"IDLE", "COMPUTE", "DONE_ST"};
        const char* __VenumItemValues[]
        = {"0", "1", "10"};
        tracep->declDTypeEnum(1, "accel_top.state_t", 3, 2, __VenumItemNames, __VenumItemValues);
    }
    {
        const char* __VenumItemNames[]
        = {"IDLE", "WR_ADDR", "WR_RESP", "RD_ADDR", 
                                "RD_DATA"};
        const char* __VenumItemValues[]
        = {"0", "1", "10", "11", "100"};
        tracep->declDTypeEnum(2, "dmem_axi_adapter.state_t", 5, 3, __VenumItemNames, __VenumItemValues);
    }
}

void Vsoc_tb___024root__trace_decl_types(VerilatedFst* tracep) {
    Vsoc_tb___024root__traceDeclTypesSub0(tracep);
}
