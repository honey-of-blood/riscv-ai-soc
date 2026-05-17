// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top___024root.h"

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_initial__TOP(Vaccel_tb_top___024root* vlSelf);
VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__0(Vaccel_tb_top___024root* vlSelf);
VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__1(Vaccel_tb_top___024root* vlSelf);
VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__2(Vaccel_tb_top___024root* vlSelf);
VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__3(Vaccel_tb_top___024root* vlSelf);

void Vaccel_tb_top___024root___eval_initial(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial\n"); );
    // Body
    Vaccel_tb_top___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__3(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0 
        = vlSelf->accel_tb_top__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__rst_n__0 
        = vlSelf->accel_tb_top__DOT__rst_n;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__0(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Body
    vlSelf->accel_tb_top__DOT__rst_n = 0U;
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       16);
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       16);
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       16);
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       16);
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       16);
    vlSelf->accel_tb_top__DOT__rst_n = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__2(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__2\n"); );
    // Body
    co_await vlSelf->__VdlySched.delay(0xbebc200ULL, 
                                       nullptr, "accel_tb_top.sv", 
                                       151);
    VL_WRITEF("[TIMEOUT] Exceeded 200us\n");
    VL_FINISH_MT("accel_tb_top.sv", 153, "");
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__3(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "accel_tb_top.sv", 
                                           12);
        vlSelf->accel_tb_top__DOT__clk = (1U & (~ (IData)(vlSelf->accel_tb_top__DOT__clk)));
    }
}

void Vaccel_tb_top___024root___ico_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf);

void Vaccel_tb_top___024root___eval_ico(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_ico\n"); );
    // Body
    if ((2ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vaccel_tb_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vaccel_tb_top___024root___eval_triggers__ico(Vaccel_tb_top___024root* vlSelf);

bool Vaccel_tb_top___024root___eval_phase__ico(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vaccel_tb_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vaccel_tb_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vaccel_tb_top___024root___act_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf);

void Vaccel_tb_top___024root___eval_act(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_act\n"); );
    // Body
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        Vaccel_tb_top___024root___act_sequent__TOP__0(vlSelf);
    }
}

void Vaccel_tb_top___024root___nba_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf);

void Vaccel_tb_top___024root___eval_nba(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_nba\n"); );
    // Body
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vaccel_tb_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
    }
    if ((8ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vaccel_tb_top___024root___act_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vaccel_tb_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vaccel_tb_top___024root___timing_resume(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___timing_resume\n"); );
    // Body
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_hb580a06f__0.resume("@(posedge accel_tb_top.clk)");
    }
    if ((0x10ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdynSched.resume();
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vaccel_tb_top___024root___timing_commit(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___timing_commit\n"); );
    // Body
    if ((! (4ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_hb580a06f__0.commit("@(posedge accel_tb_top.clk)");
    }
}

void Vaccel_tb_top___024root___eval_triggers__act(Vaccel_tb_top___024root* vlSelf);

bool Vaccel_tb_top___024root___eval_phase__act(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<5> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vaccel_tb_top___024root___eval_triggers__act(vlSelf);
    Vaccel_tb_top___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vaccel_tb_top___024root___timing_resume(vlSelf);
        Vaccel_tb_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vaccel_tb_top___024root___eval_phase__nba(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vaccel_tb_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    if (vlSelf->__VnbaEventTrigger) {
        __VnbaExecute = 1U;
        vlSelf->__VnbaEventTrigger = 0U;
        vlSelf->__VnbaEvent.fire();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__ico(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__nba(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__act(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vaccel_tb_top___024root___eval(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vaccel_tb_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("accel_tb_top.sv", 8, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vaccel_tb_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vaccel_tb_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("accel_tb_top.sv", 8, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vaccel_tb_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("accel_tb_top.sv", 8, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vaccel_tb_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vaccel_tb_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vaccel_tb_top___024root___eval_debug_assertions(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
