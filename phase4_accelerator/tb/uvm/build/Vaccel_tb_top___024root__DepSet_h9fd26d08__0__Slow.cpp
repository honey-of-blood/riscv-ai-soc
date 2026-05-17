// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top___024root.h"

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_final(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__stl(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaccel_tb_top___024root___eval_phase__stl(Vaccel_tb_top___024root* vlSelf);

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_settle(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vaccel_tb_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("accel_tb_top.sv", 8, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vaccel_tb_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__stl(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaccel_tb_top___024root___stl_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf);

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_stl(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vaccel_tb_top___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_triggers__stl(Vaccel_tb_top___024root* vlSelf);

VL_ATTR_COLD bool Vaccel_tb_top___024root___eval_phase__stl(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaccel_tb_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vaccel_tb_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__ico(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
    if ((2ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 1 is active: Internal 'ico' trigger - virtual interface: accel_if\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__act(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: Internal 'act' trigger - virtual interface: accel_if\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge accel_tb_top.clk or negedge accel_tb_top.rst_n)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @(posedge accel_tb_top.clk)\n");
    }
    if ((8ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 3 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((0x10ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 4 is active: @([true] __VdynSched.evaluate())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__nba(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: Internal 'nba' trigger - virtual interface: accel_if\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge accel_tb_top.clk or negedge accel_tb_top.rst_n)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @(posedge accel_tb_top.clk)\n");
    }
    if ((8ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 3 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((0x10ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 4 is active: @([true] __VdynSched.evaluate())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaccel_tb_top___024root___ctor_var_reset(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->accel_tb_top__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__resp = VL_RAND_RESET_I(2);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    vlSelf->accel_tb_top__DOT__dut__DOT__done_r = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT__dut__DOT__start_r = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT__dut__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->accel_tb_top__DOT__dut__DOT__cyc = VL_RAND_RESET_I(3);
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r = VL_RAND_RESET_I(6);
    vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    vlSelf->accel_tb_top__DOT__dut__DOT__rdata_comb = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 0;
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33 = VL_RAND_RESET_I(32);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->__VnbaEventTrigger = 0;
    vlSelf->__VvifTrigger_h04376982__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
