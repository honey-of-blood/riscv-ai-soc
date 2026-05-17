// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent): Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard(vlSymsp, name, parent) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__fail_count = 0U;
    this->__PVT__pass_count = 0U;
    ;
    this->__PVT__y_valid = 0U;
}

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::_ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard::_ctor_var_reset\n"); );
    // Body
    if (false && vlSymsp) {}  // Prevent unused
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __PVT__sw_w[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __PVT__sw_a[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __PVT__exp_y[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    __PVT__y_valid = 0;
    __PVT__pass_count = 0;
    __PVT__fail_count = 0;
}
