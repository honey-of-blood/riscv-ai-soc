// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg.h"

Vaccel_tb_top_std__03a__03amailbox__Tz1::Vaccel_tb_top_std__03a__03amailbox__Tz1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ bound) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_std__03a__03amailbox__Tz1::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    this->__PVT__m_bound = bound;
}

VlCoroutine Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_put(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_put\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    if ((0U != this->__PVT__m_bound)) {
        if (VL_GTES_III(32, this->__PVT__m_queue.size(), this->__PVT__m_bound)) {
            CData/*0:0*/ __VdynTrigger_h0b0ecd0c__0;
            __VdynTrigger_h0b0ecd0c__0 = 0;
            __VdynTrigger_h0b0ecd0c__0 = 0U;
            CData/*0:0*/ __Vtrigcurrexpr_hf8e1bd88__0;
            __Vtrigcurrexpr_hf8e1bd88__0 = 0;
            while ((1U & (~ (IData)(__VdynTrigger_h0b0ecd0c__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@([true] (std::mailbox__Tz1.m_queue.size() < std::mailbox__Tz1.m_bound))", 
                                                             "/usr/share/verilator/include/verilated_std.sv", 
                                                             44);
                __Vtrigcurrexpr_hf8e1bd88__0 = VL_LTS_III(32, this->__PVT__m_queue.size(), this->__PVT__m_bound);
                __VdynTrigger_h0b0ecd0c__0 = __Vtrigcurrexpr_hf8e1bd88__0;
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h0b0ecd0c__0);
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@([true] (std::mailbox__Tz1.m_queue.size() < std::mailbox__Tz1.m_bound))", 
                                                         "/usr/share/verilator/include/verilated_std.sv", 
                                                         44);
        }
    }
    this->__PVT__m_queue.push_back(message);
}

VlCoroutine Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_get(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_get\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    if (VL_GTES_III(32, 0U, this->__PVT__m_queue.size())) {
        CData/*0:0*/ __VdynTrigger_ha003271a__0;
        __VdynTrigger_ha003271a__0 = 0;
        __VdynTrigger_ha003271a__0 = 0U;
        CData/*0:0*/ __Vtrigcurrexpr_ha5fd1ac6__0;
        __Vtrigcurrexpr_ha5fd1ac6__0 = 0;
        while ((1U & (~ (IData)(__VdynTrigger_ha003271a__0)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                         "/usr/share/verilator/include/verilated_std.sv", 
                                                         59);
            __Vtrigcurrexpr_ha5fd1ac6__0 = VL_LTS_III(32, 0U, this->__PVT__m_queue.size());
            __VdynTrigger_ha003271a__0 = __Vtrigcurrexpr_ha5fd1ac6__0;
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_ha003271a__0);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                     "/usr/share/verilator/include/verilated_std.sv", 
                                                     59);
    }
    message = this->__PVT__m_queue.pop_front();
}

VlCoroutine Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_peek(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_std__03a__03amailbox__Tz1::__VnoInFunc_peek\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    if (VL_GTES_III(32, 0U, this->__PVT__m_queue.size())) {
        CData/*0:0*/ __VdynTrigger_ha003271a__1;
        __VdynTrigger_ha003271a__1 = 0;
        __VdynTrigger_ha003271a__1 = 0U;
        CData/*0:0*/ __Vtrigcurrexpr_ha5fd1ac6__1;
        __Vtrigcurrexpr_ha5fd1ac6__1 = 0;
        while ((1U & (~ (IData)(__VdynTrigger_ha003271a__1)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                         "/usr/share/verilator/include/verilated_std.sv", 
                                                         74);
            __Vtrigcurrexpr_ha5fd1ac6__1 = VL_LTS_III(32, 0U, this->__PVT__m_queue.size());
            __VdynTrigger_ha003271a__1 = __Vtrigcurrexpr_ha5fd1ac6__1;
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_ha003271a__1);
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@([true] (32'sh0 < std::mailbox__Tz1.m_queue.size()))", 
                                                     "/usr/share/verilator/include/verilated_std.sv", 
                                                     74);
    }
    message = this->__PVT__m_queue.at(0U);
}

void Vaccel_tb_top_std__03a__03amailbox__Tz1::_ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_std__03a__03amailbox__Tz1::_ctor_var_reset\n"); );
    // Body
    if (false && vlSymsp) {}  // Prevent unused
    __PVT__m_bound = 0;
    }
