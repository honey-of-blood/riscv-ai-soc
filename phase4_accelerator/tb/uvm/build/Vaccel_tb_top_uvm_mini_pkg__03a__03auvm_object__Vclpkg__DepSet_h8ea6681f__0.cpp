// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg.h"

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_get_name(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &get_name__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_get_name\n"); );
    // Body
    get_name__Vfuncrtn = this->__PVT__m_name;
}

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_get_type_name(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &get_type_name__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_get_type_name\n"); );
    // Body
    get_type_name__Vfuncrtn = std::string{"uvm_object"};
}

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_convert2string(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &convert2string__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::__VnoInFunc_convert2string\n"); );
    // Body
    convert2string__Vfuncrtn = VL_SFORMATF_NX("uvm_object(%@)",
                                              -1,&(this->__PVT__m_name)) ;
}

Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object::to_string_middle\n"); );
    // Body
    std::string out;
    out += "m_name:" + VL_TO_STRING(__PVT__m_name);
    return out;
}
