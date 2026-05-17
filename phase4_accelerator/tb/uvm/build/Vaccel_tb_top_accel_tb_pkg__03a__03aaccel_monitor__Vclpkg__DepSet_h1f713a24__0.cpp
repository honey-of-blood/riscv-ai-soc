// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor\n"); );
    // Body
    this->__VnoInFunc_run_monitor____Vfork_1__0(vlSymsp);
    this->__VnoInFunc_run_monitor____Vfork_1__1(vlSymsp);
}

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::to_string_middle\n"); );
    // Body
    std::string out;
    out += "vif:" + VL_TO_STRING(__PVT__vif);
    out += ", ap:" + VL_TO_STRING(__PVT__ap);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor::to_string_middle();
    return out;
}
