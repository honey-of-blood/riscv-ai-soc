// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item::Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name): Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item(vlSymsp, name) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    ;
}

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item::_ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item::_ctor_var_reset\n"); );
    // Body
    if (false && vlSymsp) {}  // Prevent unused
    __PVT__dir = VL_RAND_RESET_I(1);
    __PVT__addr = VL_RAND_RESET_I(32);
    __PVT__data = VL_RAND_RESET_I(32);
    __PVT__wstrb = VL_RAND_RESET_I(4);
    __PVT__resp = VL_RAND_RESET_I(2);
}
