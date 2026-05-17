// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top___024root.h"

void Vaccel_tb_top___024root___ctor_var_reset(Vaccel_tb_top___024root* vlSelf);

Vaccel_tb_top___024root::Vaccel_tb_top___024root(Vaccel_tb_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vaccel_tb_top___024root___ctor_var_reset(this);
}

void Vaccel_tb_top___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vaccel_tb_top___024root::~Vaccel_tb_top___024root() {
}
