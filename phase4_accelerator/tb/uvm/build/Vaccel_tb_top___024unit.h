// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP___024UNIT_H_
#define VERILATED_VACCEL_TB_TOP___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top___024unit(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top___024unit();
    VL_UNCOPYABLE(Vaccel_tb_top___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
