// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_if.h"

std::string VL_TO_STRING(const Vaccel_tb_top_accel_if* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_accel_if::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->name() : "null");
}
