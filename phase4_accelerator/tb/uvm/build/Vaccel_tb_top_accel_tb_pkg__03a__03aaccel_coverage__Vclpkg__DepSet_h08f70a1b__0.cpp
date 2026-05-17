// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent): Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component(vlSymsp, name, parent) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__total_computes = 0U;
    ;
}

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::_ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::_ctor_var_reset\n"); );
    // Body
    if (false && vlSymsp) {}  // Prevent unused
    __PVT__cov_identity_weights = 0;
    __PVT__cov_full_matmul = 0;
    __PVT__cov_signed_weights = 0;
    __PVT__cov_zero_activations = 0;
    __PVT__cov_back_to_back = 0;
    __PVT__total_computes = 0;
}
