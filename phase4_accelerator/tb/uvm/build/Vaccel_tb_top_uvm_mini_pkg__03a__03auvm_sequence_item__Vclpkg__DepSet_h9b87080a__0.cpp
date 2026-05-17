// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg.h"

Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item::to_string_middle\n"); );
    // Body
    std::string out;
    out += Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string_middle();
    return out;
}
