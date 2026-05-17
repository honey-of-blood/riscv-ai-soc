// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_report_phase\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    co_await this->__VnoInFunc_drain(vlSymsp);
    co_await VL_NULL_CHECK(this->__PVT__sb, "accel_tb_pkg.sv", 301)->__VnoInFunc_report_phase(vlSymsp, phase);
    co_await VL_NULL_CHECK(this->__PVT__cov, "accel_tb_pkg.sv", 302)->__VnoInFunc_report_phase(vlSymsp, phase);
}
