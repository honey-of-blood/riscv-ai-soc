// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing declarations
#include "verilated_fst_c.h"


void Vcrossbar_accel_tb___024root__traceDeclTypesSub0(VerilatedFst* tracep) {
    {
        const char* __VenumItemNames[]
        = {"IDLE", "COMPUTE", "DONE_ST"};
        const char* __VenumItemValues[]
        = {"0", "1", "10"};
        tracep->declDTypeEnum(1, "accel_top.state_t", 3, 2, __VenumItemNames, __VenumItemValues);
    }
}

void Vcrossbar_accel_tb___024root__trace_decl_types(VerilatedFst* tracep) {
    Vcrossbar_accel_tb___024root__traceDeclTypesSub0(tracep);
}
