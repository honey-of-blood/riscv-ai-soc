// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env() {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::to_string_middle\n"); );
    // Body
    std::string out;
    out += "drv:" + VL_TO_STRING(__PVT__drv);
    out += ", mon:" + VL_TO_STRING(__PVT__mon);
    out += ", sb:" + VL_TO_STRING(__PVT__sb);
    out += ", cov:" + VL_TO_STRING(__PVT__cov);
    out += ", m_vif:" + VL_TO_STRING(__PVT__m_vif);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env::to_string_middle();
    return out;
}
