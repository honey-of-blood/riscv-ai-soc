// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG_H_
#define VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_uvm_mini_pkg final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ g_error_count;

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_uvm_mini_pkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_uvm_mini_pkg();
    VL_UNCOPYABLE(Vaccel_tb_top_uvm_mini_pkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
