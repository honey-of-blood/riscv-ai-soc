// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_accel_tb.h for the primary calling header

#include "Vcrossbar_accel_tb__pch.h"
#include "Vcrossbar_accel_tb___024root.h"

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_static__TOP(Vcrossbar_accel_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_static(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_static\n"); );
    // Body
    Vcrossbar_accel_tb___024root___eval_static__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[6U] = 1U;
    vlSelf->__Vm_traceActivity[5U] = 1U;
    vlSelf->__Vm_traceActivity[4U] = 1U;
    vlSelf->__Vm_traceActivity[3U] = 1U;
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_static__TOP(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__error_count = 0U;
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_initial__TOP(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__clk = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s = 3U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[0U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[1U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[0U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[1U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[0U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[2U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[0U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[1U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[0U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[1U] = 0U;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[2U] = 0U;
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_final(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__stl(Vcrossbar_accel_tb___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcrossbar_accel_tb___024root___eval_phase__stl(Vcrossbar_accel_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_settle(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_settle\n"); );
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
            Vcrossbar_accel_tb___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("crossbar_accel_tb.sv", 6, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vcrossbar_accel_tb___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__stl(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___stl_sequent__TOP__0(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[0U] 
        = ((0U == (vlSelf->crossbar_accel_tb__DOT__m0_awaddr 
                   >> 0x10U)) ? 0U : ((0x1000U == (vlSelf->crossbar_accel_tb__DOT__m0_awaddr 
                                                   >> 0x10U))
                                       ? 1U : ((0x5000U 
                                                == 
                                                (vlSelf->crossbar_accel_tb__DOT__m0_awaddr 
                                                 >> 0x10U))
                                                ? 2U
                                                : 3U)));
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[0U] 
        = ((0U == (vlSelf->crossbar_accel_tb__DOT__m0_araddr 
                   >> 0x10U)) ? 0U : ((0x1000U == (vlSelf->crossbar_accel_tb__DOT__m0_araddr 
                                                   >> 0x10U))
                                       ? 1U : ((0x5000U 
                                                == 
                                                (vlSelf->crossbar_accel_tb__DOT__m0_araddr 
                                                 >> 0x10U))
                                                ? 2U
                                                : 3U)));
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
         [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
               [2U] : 0U);
    }
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
         [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
               [2U] : 0U);
    }
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
               [2U] : 0U);
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_awaddr;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wstrb;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_awvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_bready;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_arvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_rready;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_bvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_bvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[2U] 
        = vlSelf->crossbar_accel_tb__DOT__s2_bvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[0U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
            [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                    [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                            [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                                    [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                           [2U])));
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[1U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
            [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                    [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                            [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                                    [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                           [2U])));
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
         [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp
               [2U] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
               [2U]);
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_rdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_rdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[2U] 
        = vlSelf->crossbar_accel_tb__DOT__s2_rdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[0U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                    [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                            [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                           [2U] : 0U)));
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
               [2U]);
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
             [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                     [2U]))) {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
                [2U];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1U] 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                [2U];
        } else {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1U] = 0U;
        }
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[2U] 
        = vlSelf->crossbar_accel_tb__DOT__s2_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                    [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                            [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                                    [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                           [2U])));
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                    [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                            [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                                    [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                           [2U])));
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
            [0U];
    } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
               [2U]);
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
             [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                     [2U]))) {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2U] 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
                [2U];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                [2U];
        } else {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2U] = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] = 0U;
        }
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
               [2U]);
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_araddr;
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
        = ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
            [3U][3U] << 0x18U) | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                   [3U][2U] << 0x10U) 
                                  | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                      [3U][1U] << 8U) 
                                     | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                     [3U][0U])));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
        = ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
            [2U][3U] << 0x18U) | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                   [2U][2U] << 0x10U) 
                                  | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                      [2U][1U] << 8U) 
                                     | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                     [2U][0U])));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
        = ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
            [1U][3U] << 0x18U) | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                   [1U][2U] << 0x10U) 
                                  | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                      [1U][1U] << 8U) 
                                     | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                     [1U][0U])));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
        = ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
            [0U][3U] << 0x18U) | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                   [0U][2U] << 0x10U) 
                                  | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                      [0U][1U] << 8U) 
                                     | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                     [0U][0U])));
    if ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state))) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s 
            = ((0U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
               [0U][0U] : ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                           [1U][0U] : ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                        ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                       [2U][0U] : (
                                                   (3U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s 
            = ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
               [0U][1U] : ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                           [1U][1U] : ((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                        ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                       [2U][1U] : (
                                                   (4U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s 
            = ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
               [0U][2U] : ((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                           [1U][2U] : ((4U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                        ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                       [2U][2U] : (
                                                   (5U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s 
            = ((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
               [0U][3U] : ((4U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                           [1U][3U] : ((5U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                        ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                       [2U][3U] : (
                                                   (6U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))));
    } else {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
        [0U]) {
        if ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
             [0U])) {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]];
        } else {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[0U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
        [1U]) {
        if ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
             [1U])) {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]];
        } else {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[1U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
        [2U]) {
        if ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
             [2U])) {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]];
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb
                [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]];
        } else {
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[2U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [0U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [1U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [2U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2U] = 0U;
    }
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                                              >> 8U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                                              >> 0x10U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                                           >> 0x18U)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                                              >> 8U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                                              >> 0x10U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                                           >> 0x18U)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                                              >> 8U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                                              >> 0x10U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                                           >> 0x18U)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                                              >> 8U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                                              >> 0x10U))))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                                           >> 0x18U)))));
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__rdata_comb 
        = ((0x80U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
            [2U]) ? 0U : ((0x40U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                           [2U]) ? ((0x20U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                     [2U]) ? ((0x10U 
                                               & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                               [2U])
                                               ? 0U
                                               : ((8U 
                                                   & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 0U
                                                    : 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [3U]
                                                   [3U])))
                                     : ((0x10U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                         [2U]) ? ((8U 
                                                   & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 
                                                  ((4U 
                                                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [3U]
                                                   [2U]
                                                    : 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [3U]
                                                   [1U])
                                                   : 
                                                  ((4U 
                                                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [3U]
                                                   [0U]
                                                    : 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [2U]
                                                   [3U]))
                                         : ((8U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                              [2U])
                                              ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                             [2U][2U]
                                              : vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                             [2U][1U])
                                             : ((4U 
                                                 & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                [2U]
                                                [0U]
                                                 : 
                                                vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                [1U]
                                                [3U]))))
                           : ((0x20U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                               [2U]) ? ((0x10U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                         [2U]) ? ((8U 
                                                   & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 
                                                  ((4U 
                                                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [1U]
                                                   [2U]
                                                    : 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [1U]
                                                   [1U])
                                                   : 
                                                  ((4U 
                                                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [1U]
                                                   [0U]
                                                    : 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                   [0U]
                                                   [3U]))
                                         : ((8U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                              [2U])
                                              ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                             [0U][2U]
                                              : vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                             [0U][1U])
                                             : ((4U 
                                                 & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                                [0U]
                                                [0U]
                                                 : 
                                                ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [3U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                     [3U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                        [3U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                       [3U]
                                                       [0U]))))))
                               : ((0x10U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                   [2U]) ? ((8U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                              [2U])
                                              ? ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [2U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                     [2U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                        [2U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                       [2U]
                                                       [0U])))
                                              : ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [1U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                     [1U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                        [1U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                       [1U]
                                                       [0U]))))
                                             : ((4U 
                                                 & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [0U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                     [0U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                        [0U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                       [0U]
                                                       [0U])))
                                                 : 
                                                ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                  [3U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                     [3U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                        [3U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                       [3U]
                                                       [0U])))))
                                   : ((8U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                       [2U]) ? ((4U 
                                                 & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                  [2U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                     [2U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                        [2U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                       [2U]
                                                       [0U])))
                                                 : 
                                                ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                  [1U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                     [1U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                        [1U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                       [1U]
                                                       [0U]))))
                                       : ((4U & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                           [2U]) ? 
                                          ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                            [0U][3U] 
                                            << 0x18U) 
                                           | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                               [0U]
                                               [2U] 
                                               << 0x10U) 
                                              | ((vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                  [0U]
                                                  [1U] 
                                                  << 8U) 
                                                 | vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                                 [0U]
                                                 [0U])))
                                           : (((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r) 
                                               << 1U) 
                                              | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r))))))));
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_stl(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vcrossbar_accel_tb___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[6U] = 1U;
        vlSelf->__Vm_traceActivity[5U] = 1U;
        vlSelf->__Vm_traceActivity[4U] = 1U;
        vlSelf->__Vm_traceActivity[3U] = 1U;
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_triggers__stl(Vcrossbar_accel_tb___024root* vlSelf);

VL_ATTR_COLD bool Vcrossbar_accel_tb___024root___eval_phase__stl(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcrossbar_accel_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vcrossbar_accel_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__act(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge crossbar_accel_tb.clk or negedge crossbar_accel_tb.rst_n)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge crossbar_accel_tb.clk)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_accel_tb___024root___dump_triggers__nba(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge crossbar_accel_tb.clk or negedge crossbar_accel_tb.rst_n)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge crossbar_accel_tb.clk)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___ctor_var_reset(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__error_count = 0;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = VL_RAND_RESET_I(4);
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__m0_bready = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__m0_rready = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s0_rdata = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__s0_bvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s0_rvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s1_rdata = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__s1_bvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s1_rvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s2_rdata = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__s2_bvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__s2_rvalid = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[__Vi0] = VL_RAND_RESET_I(4);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[__Vi0] = VL_RAND_RESET_I(4);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[__Vi0] = VL_RAND_RESET_I(2);
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0 = VL_RAND_RESET_I(4);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0 = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0 = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r = VL_RAND_RESET_I(14);
    vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r = VL_RAND_RESET_I(14);
    vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc = VL_RAND_RESET_I(3);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r = VL_RAND_RESET_I(6);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__rdata_comb = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 0;
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33 = VL_RAND_RESET_I(32);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 7; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
