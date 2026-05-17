// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg.h"

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_build_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_build_phase\n"); );
}

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_connect_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_connect_phase\n"); );
}

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_run_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_run_phase\n"); );
}

VlCoroutine Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_report_phase\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    co_return;
}

Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_parent:" + VL_TO_STRING(__PVT__m_parent);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string_middle();
    return out;
}
