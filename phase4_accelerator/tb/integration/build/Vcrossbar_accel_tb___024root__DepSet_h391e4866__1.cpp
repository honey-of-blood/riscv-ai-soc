// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_accel_tb.h for the primary calling header

#include "Vcrossbar_accel_tb__pch.h"
#include "Vcrossbar_accel_tb___024root.h"

void Vcrossbar_accel_tb___024root___nba_sequent__TOP__0(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___nba_sequent__TOP__1(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___nba_comb__TOP__0(Vcrossbar_accel_tb___024root* vlSelf);

void Vcrossbar_accel_tb___024root___eval_nba(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcrossbar_accel_tb___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[4U] = 1U;
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcrossbar_accel_tb___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[5U] = 1U;
    }
    if ((3ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vcrossbar_accel_tb___024root___nba_comb__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[6U] = 1U;
    }
}

void Vcrossbar_accel_tb___024root___timing_resume(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___timing_resume\n"); );
    // Body
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h5c6c16d3__0.resume("@(posedge crossbar_accel_tb.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vcrossbar_accel_tb___024root___timing_commit(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___timing_commit\n"); );
    // Body
    if ((! (2ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h5c6c16d3__0.commit("@(posedge crossbar_accel_tb.clk)");
    }
}

void Vcrossbar_accel_tb___024root___eval_triggers__act(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___eval_act(Vcrossbar_accel_tb___024root* vlSelf);

bool Vcrossbar_accel_tb___024root___eval_phase__act(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vcrossbar_accel_tb___024root___eval_triggers__act(vlSelf);
    Vcrossbar_accel_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vcrossbar_accel_tb___024root___timing_resume(vlSelf);
        Vcrossbar_accel_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcrossbar_accel_tb___024root___eval_phase__nba(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vcrossbar_accel_tb___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__nba(Vcrossbar_accel_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__act(Vcrossbar_accel_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vcrossbar_accel_tb___024root___eval(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vcrossbar_accel_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("crossbar_accel_tb.sv", 6, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vcrossbar_accel_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("crossbar_accel_tb.sv", 6, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vcrossbar_accel_tb___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vcrossbar_accel_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vcrossbar_accel_tb___024root___eval_debug_assertions(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
