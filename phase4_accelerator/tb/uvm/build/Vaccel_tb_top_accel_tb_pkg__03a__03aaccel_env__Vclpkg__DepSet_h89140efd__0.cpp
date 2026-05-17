// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_build_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_build_phase\n"); );
    // Body
    this->__PVT__drv = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver, vlSymsp, 
                              std::string{"drv"}, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>{this});
    VL_NULL_CHECK(this->__PVT__drv, "accel_tb_pkg.sv", 285)->__PVT__vif 
        = this->__PVT__m_vif;
    this->__PVT__mon = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor, vlSymsp, 
                              std::string{"mon"}, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>{this});
    VL_NULL_CHECK(this->__PVT__mon, "accel_tb_pkg.sv", 286)->__PVT__vif 
        = this->__PVT__m_vif;
    this->__PVT__sb = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard, vlSymsp, 
                             std::string{"sb"}, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>{this});
    this->__PVT__cov = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage, vlSymsp, 
                              std::string{"cov"}, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>{this});
}
