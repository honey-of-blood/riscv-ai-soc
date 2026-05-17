// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::__VnoInFunc_mark(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::__VnoInFunc_mark\n"); );
    // Body
    if ((std::string{"identity_weights"} == tag)) {
        this->__PVT__cov_identity_weights = 1U;
    } else if ((std::string{"full_matmul"} == tag)) {
        this->__PVT__cov_full_matmul = 1U;
    } else if ((std::string{"signed_weights"} == tag)) {
        this->__PVT__cov_signed_weights = 1U;
    } else if ((std::string{"zero_activations"} == tag)) {
        this->__PVT__cov_zero_activations = 1U;
    } else if ((std::string{"back_to_back"} == tag)) {
        this->__PVT__cov_back_to_back = 1U;
    }
    this->__PVT__total_computes = ((IData)(1U) + this->__PVT__total_computes);
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::__VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::__VnoInFunc_report_phase\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    IData/*31:0*/ hits;
    hits = 0;
    hits = (((((IData)(this->__PVT__cov_identity_weights) 
               + (IData)(this->__PVT__cov_full_matmul)) 
              + (IData)(this->__PVT__cov_signed_weights)) 
             + (IData)(this->__PVT__cov_zero_activations)) 
            + (IData)(this->__PVT__cov_back_to_back));
    VL_WRITEF("[COV] %0d/5 scenario bins covered  (computes=%0#)\n[COV] identity_weights=%0b full_matmul=%0b signed_weights=%0b zero_act=%0b back_to_back=%0b\n",
              32,hits,32,this->__PVT__total_computes,
              1,(IData)(this->__PVT__cov_identity_weights),
              1,this->__PVT__cov_full_matmul,1,(IData)(this->__PVT__cov_signed_weights),
              1,this->__PVT__cov_zero_activations,1,
              (IData)(this->__PVT__cov_back_to_back));
    co_return;
}

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage() {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage::to_string_middle\n"); );
    // Body
    std::string out;
    out += "cov_identity_weights:" + VL_TO_STRING(__PVT__cov_identity_weights);
    out += ", cov_full_matmul:" + VL_TO_STRING(__PVT__cov_full_matmul);
    out += ", cov_signed_weights:" + VL_TO_STRING(__PVT__cov_signed_weights);
    out += ", cov_zero_activations:" + VL_TO_STRING(__PVT__cov_zero_activations);
    out += ", cov_back_to_back:" + VL_TO_STRING(__PVT__cov_back_to_back);
    out += ", total_computes:" + VL_TO_STRING(__PVT__total_computes);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string_middle();
    return out;
}
