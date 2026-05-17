// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_accel_tb.h for the primary calling header

#include "Vcrossbar_accel_tb__pch.h"
#include "Vcrossbar_accel_tb__Syms.h"
#include "Vcrossbar_accel_tb___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__act(Vcrossbar_accel_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vcrossbar_accel_tb___024root___eval_triggers__act(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, (((IData)(vlSelf->crossbar_accel_tb__DOT__clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0))) 
                                     | ((~ (IData)(vlSelf->crossbar_accel_tb__DOT__rst_n)) 
                                        & (IData)(vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__rst_n__0))));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->crossbar_accel_tb__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0))));
    vlSelf->__VactTriggered.set(2U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0 
        = vlSelf->crossbar_accel_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__rst_n__0 
        = vlSelf->crossbar_accel_tb__DOT__rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcrossbar_accel_tb___024root___dump_triggers__act(vlSelf);
    }
#endif
}
