// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg.h"

Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase::to_string_middle\n"); );
    // Body
    std::string out;
    out += "name:" + VL_TO_STRING(__PVT__name);
    return out;
}
