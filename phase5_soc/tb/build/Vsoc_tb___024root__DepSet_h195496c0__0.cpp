// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_tb.h for the primary calling header

#include "Vsoc_tb__pch.h"
#include "Vsoc_tb__Syms.h"
#include "Vsoc_tb___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__act(Vsoc_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vsoc_tb___024root___eval_triggers__act(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->soc_tb__DOT__clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__clk__0))));
    vlSelf->__VactTriggered.set(1U, (((IData)(vlSelf->soc_tb__DOT__clk) 
                                      & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__clk__0))) 
                                     | ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
                                        & (IData)(vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__rst_n__0))));
    vlSelf->__VactTriggered.set(2U, vlSelf->__VdlySched.awaitingCurrentTime());
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__clk__0 
        = vlSelf->soc_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__rst_n__0 
        = vlSelf->soc_tb__DOT__rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsoc_tb___024root___dump_triggers__act(vlSelf);
    }
#endif
}
