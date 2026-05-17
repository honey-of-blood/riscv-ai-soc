// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__ico(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vaccel_tb_top___024root___eval_triggers__ico(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
    vlSelf->__VicoTriggered.set(1U, (IData)(vlSelf->__VvifTrigger_h04376982__0));
    vlSelf->__VvifTrigger_h04376982__0 = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaccel_tb_top___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vaccel_tb_top___024root___ico_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->accel_tb_top__DOT__dut__DOT__rdata_comb 
        = ((0x80U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
            ? 0U : ((0x40U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                     ? ((0x20U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                         ? ((0x10U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                             ? 0U : ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                      ? 0U : ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                               ? 0U
                                               : vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                              [3U][3U])))
                         : ((0x10U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                             ? ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [3U][2U] : vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [3U][1U]) : ((4U 
                                                  & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                                  ? 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [3U]
                                                 [0U]
                                                  : 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [2U]
                                                 [3U]))
                             : ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [2U][2U] : vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [2U][1U]) : ((4U 
                                                  & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                                  ? 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [2U]
                                                 [0U]
                                                  : 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [1U]
                                                 [3U]))))
                     : ((0x20U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                         ? ((0x10U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                             ? ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [1U][2U] : vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [1U][1U]) : ((4U 
                                                  & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                                  ? 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [1U]
                                                 [0U]
                                                  : 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [0U]
                                                 [3U]))
                             : ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [0U][2U] : vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                    [0U][1U]) : ((4U 
                                                  & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                                  ? 
                                                 vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                                 [0U]
                                                 [0U]
                                                  : 
                                                 ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [3U] 
                                                   << 0x18U) 
                                                  | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                      [3U]
                                                      [2U] 
                                                      << 0x10U) 
                                                     | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                         [3U]
                                                         [1U] 
                                                         << 8U) 
                                                        | vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                        [3U]
                                                        [0U]))))))
                         : ((0x10U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                             ? ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                         [2U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                            [2U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [2U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [2U][0U])))
                                     : ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                         [1U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                            [1U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [1U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [1U][0U]))))
                                 : ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                         [0U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                            [0U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [0U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [0U][0U])))
                                     : ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                         [3U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                            [3U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                               [3U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                              [3U][0U])))))
                             : ((8U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                 ? ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                         [2U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                            [2U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                               [2U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                              [2U][0U])))
                                     : ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                         [1U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                            [1U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                               [1U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                              [1U][0U]))))
                                 : ((4U & vlSymsp->TOP__accel_tb_top__DOT__aif.araddr)
                                     ? ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                         [0U][3U] << 0x18U) 
                                        | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                            [0U][2U] 
                                            << 0x10U) 
                                           | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                               [0U]
                                               [1U] 
                                               << 8U) 
                                              | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                              [0U][0U])))
                                     : (((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__done_r) 
                                         << 1U) | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__start_r))))))));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__act(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vaccel_tb_top___024root___eval_triggers__act(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, (IData)(vlSelf->__VvifTrigger_h04376982__0));
    vlSelf->__VvifTrigger_h04376982__0 = 0U;
    vlSelf->__VactTriggered.set(1U, (((IData)(vlSelf->accel_tb_top__DOT__clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0))) 
                                     | ((~ (IData)(vlSelf->accel_tb_top__DOT__rst_n)) 
                                        & (IData)(vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__rst_n__0))));
    vlSelf->__VactTriggered.set(2U, ((IData)(vlSelf->accel_tb_top__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0))));
    vlSelf->__VactTriggered.set(3U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__VactTriggered.set(4U, vlSelf->__VdynSched.evaluate());
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0 
        = vlSelf->accel_tb_top__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__accel_tb_top__DOT__rst_n__0 
        = vlSelf->accel_tb_top__DOT__rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaccel_tb_top___024root___dump_triggers__act(vlSelf);
    }
#endif
    vlSelf->__VdynSched.doPostUpdates();
}

VL_INLINE_OPT void Vaccel_tb_top___024root___act_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___act_sequent__TOP__0\n"); );
    // Body
    vlSymsp->TOP__accel_tb_top__DOT__aif.clk = vlSelf->accel_tb_top__DOT__clk;
    vlSelf->__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT void Vaccel_tb_top___024root___nba_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*1:0*/ __Vdly__accel_tb_top__DOT__dut__DOT__state;
    __Vdly__accel_tb_top__DOT__dut__DOT__state = 0;
    CData/*2:0*/ __Vdly__accel_tb_top__DOT__dut__DOT__cyc;
    __Vdly__accel_tb_top__DOT__dut__DOT__cyc = 0;
    CData/*0:0*/ __Vdly__accel_tb_top__DOT__dut__DOT__done_r;
    __Vdly__accel_tb_top__DOT__dut__DOT__done_r = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v0;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v0;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v0 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v1;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v1;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v1 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v2;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v2 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v3;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v3 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v4;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v4;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v4 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v5;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v5 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v6;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v6 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v7;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v7 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v8;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v8;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v8 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v9;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v9 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v10;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v10 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v11;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v11 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v12;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v12;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v12 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v13;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v13 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v14;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v14 = 0;
    IData/*31:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v15;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v15 = 0;
    CData/*0:0*/ __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending;
    __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending = 0;
    CData/*0:0*/ __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid;
    __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v0;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v0;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v1;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v1;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v2;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v2;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v3;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v3;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v4;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v4;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v5;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v5;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v6;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v6;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v7;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v7;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v8;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v8;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v9;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v9;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v10;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v10;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v11;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v11;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v12;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v12;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v13;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v13;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v14;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v14;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v15;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v15;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v15 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v0;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v0;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v1;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v1;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v2;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v2;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v3;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v3;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v4;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v4;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v5;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v5;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v6;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v6;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v7;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v7;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v8;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v8;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v9;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v9;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v10;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v10;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v11;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v11;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v12;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v12;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v13;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v13;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v14;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v14;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v15;
    __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v15;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v16;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v16 = 0;
    CData/*0:0*/ __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v16;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v16 = 0;
    CData/*0:0*/ __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid;
    __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid = 0;
    // Body
    __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid 
        = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v16 = 0U;
    __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending 
        = vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending;
    __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid 
        = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v0 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v1 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v2 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v3 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v4 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v5 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v6 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v7 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v8 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v9 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v10 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v11 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v12 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v13 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v14 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v15 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v0 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v1 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v2 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v3 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v4 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v5 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v6 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v7 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v8 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v9 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v10 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v11 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v12 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v13 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v14 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v15 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v16 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v0 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v1 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v4 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v8 = 0U;
    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v12 = 0U;
    __Vdly__accel_tb_top__DOT__dut__DOT__cyc = vlSelf->accel_tb_top__DOT__dut__DOT__cyc;
    __Vdly__accel_tb_top__DOT__dut__DOT__state = vlSelf->accel_tb_top__DOT__dut__DOT__state;
    __Vdly__accel_tb_top__DOT__dut__DOT__done_r = vlSelf->accel_tb_top__DOT__dut__DOT__done_r;
    if (vlSelf->accel_tb_top__DOT__rst_n) {
        if (vlSymsp->TOP__accel_tb_top__DOT__aif.arvalid) {
            __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid = 1U;
        } else if (((IData)(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid) 
                    & (IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.rready))) {
            __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid = 0U;
        }
        if ((0U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__state))) {
            if (vlSelf->accel_tb_top__DOT__dut__DOT__start_r) {
                __Vdly__accel_tb_top__DOT__dut__DOT__state = 1U;
                __Vdly__accel_tb_top__DOT__dut__DOT__cyc = 0U;
                __Vdly__accel_tb_top__DOT__dut__DOT__done_r = 0U;
            }
        } else if ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__state))) {
            __Vdly__accel_tb_top__DOT__dut__DOT__cyc 
                = (7U & ((IData)(1U) + (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc)));
            if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))) {
                if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))) {
                    if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))) {
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v0 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30;
                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v0 = 1U;
                        __Vdly__accel_tb_top__DOT__dut__DOT__state = 2U;
                        __Vdly__accel_tb_top__DOT__dut__DOT__done_r = 1U;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v1 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31;
                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v1 = 1U;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v2 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v3 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33;
                    } else {
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v4 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30;
                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v4 = 1U;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v5 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v6 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32;
                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v7 
                            = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33;
                    }
                } else if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))) {
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v8 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30;
                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v8 = 1U;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v9 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v10 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v11 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33;
                } else {
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v12 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30;
                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v12 = 1U;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v13 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v14 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32;
                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v15 
                        = vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33;
                }
            }
        } else if ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__state))) {
            if (((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__start_r) 
                 & (~ (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__done_r)))) {
                __Vdly__accel_tb_top__DOT__dut__DOT__state = 1U;
                __Vdly__accel_tb_top__DOT__dut__DOT__cyc = 0U;
            }
        }
    } else {
        __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid = 0U;
        __Vdly__accel_tb_top__DOT__dut__DOT__state = 0U;
        __Vdly__accel_tb_top__DOT__dut__DOT__cyc = 0U;
        __Vdly__accel_tb_top__DOT__dut__DOT__done_r = 0U;
    }
    if ((1U & (~ (IData)(vlSelf->accel_tb_top__DOT__rst_n)))) {
        vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 4U;
        vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__i = 4U;
        __Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v16 = 1U;
        vlSelf->accel_tb_top__DOT__dut__DOT__start_r = 0U;
    }
    if (vlSelf->accel_tb_top__DOT__rst_n) {
        if (vlSymsp->TOP__accel_tb_top__DOT__aif.arvalid) {
            vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata 
                = vlSelf->accel_tb_top__DOT__dut__DOT__rdata_comb;
        }
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product)));
        if (((IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.awvalid) 
             & (IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.wvalid))) {
            __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending = 1U;
        }
        if (vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending) {
            __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending = 0U;
            __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid = 1U;
            if ((1U & (~ ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r) 
                          >> 5U)))) {
                if ((1U & (~ ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r) 
                              >> 4U)))) {
                    if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                        if ((1U & (~ ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r) 
                                      >> 2U)))) {
                            if ((1U & (~ ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r) 
                                          >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r)))) {
                                    if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v0 
                                            = (0xffU 
                                               & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v0 = 1U;
                                    }
                                    if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v1 
                                            = (0xffU 
                                               & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                  >> 8U));
                                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v1 = 1U;
                                    }
                                    if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v2 
                                            = (0xffU 
                                               & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                  >> 0x10U));
                                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v2 = 1U;
                                    }
                                    if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                        __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v3 
                                            = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                               >> 0x18U);
                                        __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v3 = 1U;
                                    }
                                }
                            }
                        }
                    } else if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                        if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                                if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v4 
                                        = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v4 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v5 
                                        = (0xffU & 
                                           (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v5 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v6 
                                        = (0xffU & 
                                           (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v6 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v7 
                                        = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v7 = 1U;
                                }
                            } else {
                                if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v8 
                                        = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v8 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v9 
                                        = (0xffU & 
                                           (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v9 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v10 
                                        = (0xffU & 
                                           (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v10 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                    __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v11 
                                        = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v11 = 1U;
                                }
                            }
                        } else if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v12 
                                    = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v12 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v13 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v13 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v14 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v14 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v15 
                                    = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v15 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v0 
                                    = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v0 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v1 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v1 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v2 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v2 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v3 
                                    = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v3 = 1U;
                            }
                        }
                    } else if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v4 
                                    = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v4 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v5 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v5 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v6 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v6 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v7 
                                    = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v7 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v8 
                                    = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v8 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v9 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v9 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v10 
                                    = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v10 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                                __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v11 
                                    = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v11 = 1U;
                            }
                        }
                    } else if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                            __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v12 
                                = (0xffU & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r);
                            __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v12 = 1U;
                        }
                        if ((2U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                            __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v13 
                                = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 8U));
                            __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v13 = 1U;
                        }
                        if ((4U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                            __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v14 
                                = (0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                            >> 0x10U));
                            __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v14 = 1U;
                        }
                        if ((8U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                            __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v15 
                                = (vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                                   >> 0x18U);
                            __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v15 = 1U;
                        }
                    } else if ((1U & (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r))) {
                        if ((1U & vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r)) {
                            vlSelf->accel_tb_top__DOT__dut__DOT__start_r = 1U;
                            __Vdly__accel_tb_top__DOT__dut__DOT__done_r = 0U;
                        } else {
                            vlSelf->accel_tb_top__DOT__dut__DOT__start_r = 0U;
                        }
                    }
                }
            }
        }
        if (((IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.awvalid) 
             & (IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.wvalid))) {
            vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r 
                = (0x3fU & (vlSymsp->TOP__accel_tb_top__DOT__aif.awaddr 
                            >> 2U));
            vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r 
                = vlSymsp->TOP__accel_tb_top__DOT__aif.wstrb;
            vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r 
                = vlSymsp->TOP__accel_tb_top__DOT__aif.wdata;
        }
        if (((IData)(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid) 
             & (IData)(vlSymsp->TOP__accel_tb_top__DOT__aif.bready))) {
            __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid = 0U;
        }
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13 
            = (vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03 
               + (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product)));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00 
            = (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01 
            = (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02 
            = (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03 
            = (((- (IData)((1U & ((IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product));
    } else {
        vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33 = 0U;
        __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending = 0U;
        __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid = 0U;
        __Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v16 = 1U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02 = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03 = 0U;
    }
    vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid 
        = __Vdly__accel_tb_top__DOT____Vcellout__dut__s_rvalid;
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v0) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v0;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v1) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v1;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v2;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v3;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v4) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v4;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v5;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v6;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v7;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v8) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v8;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v9;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v10;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v11;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v12) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v12;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v13;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v14;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__y_reg__v15;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__y_reg__v16) {
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[0U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[1U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[2U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__y_reg[3U][3U] = 0U;
    }
    vlSelf->accel_tb_top__DOT__dut__DOT__state = __Vdly__accel_tb_top__DOT__dut__DOT__state;
    vlSelf->accel_tb_top__DOT__dut__DOT__cyc = __Vdly__accel_tb_top__DOT__dut__DOT__cyc;
    vlSymsp->TOP__accel_tb_top__DOT__aif.rvalid = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid;
    vlSymsp->TOP__accel_tb_top__DOT__aif.rdata = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata;
    vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending 
        = __Vdly__accel_tb_top__DOT__dut__DOT__wr_pending;
    vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid 
        = __Vdly__accel_tb_top__DOT____Vcellout__dut__s_bvalid;
    vlSelf->accel_tb_top__DOT__dut__DOT__done_r = __Vdly__accel_tb_top__DOT__dut__DOT__done_r;
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v0) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v0;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v1) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v1;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v2) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v2;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v3) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v3;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v4) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v4;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v5) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v5;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v6) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v6;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v7) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v7;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v8) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v8;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v9) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v9;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v10) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v10;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v11) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v11;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v12) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v12;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v13) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v13;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v14) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v14;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v15) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__w_reg__v15;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v0) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v0;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v1) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v1;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v2) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v2;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v3) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v3;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v4) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v4;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v5) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v5;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v6) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v6;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v7) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v7;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v8) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v8;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v9) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v9;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v10) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v10;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v11) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v11;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v12) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][0U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v12;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v13) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][1U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v13;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v14) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][2U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v14;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__a_reg__v15) {
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][3U] 
            = __Vdlyvval__accel_tb_top__DOT__dut__DOT__a_reg__v15;
    }
    if (__Vdlyvset__accel_tb_top__DOT__dut__DOT__w_reg__v16) {
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[0U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[1U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[2U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__w_reg[3U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[0U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[1U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[2U][3U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][0U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][1U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][2U] = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__a_reg[3U][3U] = 0U;
    }
    vlSymsp->TOP__accel_tb_top__DOT__aif.bvalid = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid;
    vlSelf->__VvifTrigger_h04376982__0 = 1U;
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
        = ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
            [3U][3U] << 0x18U) | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                   [3U][2U] << 0x10U) 
                                  | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                      [3U][1U] << 8U) 
                                     | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                     [3U][0U])));
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
        = ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
            [2U][3U] << 0x18U) | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                   [2U][2U] << 0x10U) 
                                  | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                      [2U][1U] << 8U) 
                                     | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                     [2U][0U])));
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
        = ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
            [1U][3U] << 0x18U) | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                   [1U][2U] << 0x10U) 
                                  | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                      [1U][1U] << 8U) 
                                     | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                     [1U][0U])));
    vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
        = ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
            [0U][3U] << 0x18U) | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                   [0U][2U] << 0x10U) 
                                  | ((vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                      [0U][1U] << 8U) 
                                     | vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                     [0U][0U])));
    if ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__state))) {
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s 
            = ((0U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
               [0U][0U] : ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                           [1U][0U] : ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                        ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                       [2U][0U] : (
                                                   (3U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s 
            = ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
               [0U][1U] : ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                           [1U][1U] : ((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                        ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                       [2U][1U] : (
                                                   (4U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s 
            = ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
               [0U][2U] : ((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                           [1U][2U] : ((4U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                        ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                       [2U][2U] : (
                                                   (5U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))));
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s 
            = ((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
               [0U][3U] : ((4U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                           [1U][3U] : ((5U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                        ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                       [2U][3U] : (
                                                   (6U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))));
    } else {
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s = 0U;
        vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s = 0U;
    }
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                                              >> 8U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                                              >> 0x10U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                                           >> 0x18U)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                                              >> 8U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                                              >> 0x10U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                                           >> 0x18U)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                                              >> 8U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                                              >> 0x10U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                                           >> 0x18U)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0)))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                                              >> 8U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                                              >> 0x10U))))));
    vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                                           >> 0x18U)))));
}
