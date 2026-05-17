// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent): Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor(vlSymsp, name, parent) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    ;
    this->__PVT__ap = VL_NEW(Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1, vlSymsp, 0U);
}
