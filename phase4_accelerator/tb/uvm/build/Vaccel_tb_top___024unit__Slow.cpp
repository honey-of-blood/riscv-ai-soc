// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top___024unit.h"

void Vaccel_tb_top___024unit___ctor_var_reset(Vaccel_tb_top___024unit* vlSelf);

Vaccel_tb_top___024unit::Vaccel_tb_top___024unit(Vaccel_tb_top__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vaccel_tb_top___024unit___ctor_var_reset(this);
}

void Vaccel_tb_top___024unit::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vaccel_tb_top___024unit::~Vaccel_tb_top___024unit() {
}
