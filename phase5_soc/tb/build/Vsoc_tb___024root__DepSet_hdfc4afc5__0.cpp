// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_tb.h for the primary calling header

#include "Vsoc_tb__pch.h"
#include "Vsoc_tb___024root.h"

VL_ATTR_COLD void Vsoc_tb___024root___eval_initial__TOP(Vsoc_tb___024root* vlSelf);
VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__0(Vsoc_tb___024root* vlSelf);
VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__1(Vsoc_tb___024root* vlSelf);
VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__2(Vsoc_tb___024root* vlSelf);
VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__3(Vsoc_tb___024root* vlSelf);

void Vsoc_tb___024root___eval_initial(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial\n"); );
    // Body
    Vsoc_tb___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    Vsoc_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vsoc_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vsoc_tb___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vsoc_tb___024root___eval_initial__TOP__Vtiming__3(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__clk__0 
        = vlSelf->soc_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__rst_n__0 
        = vlSelf->soc_tb__DOT__rst_n;
}

VL_INLINE_OPT VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__0(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Body
    vlSelf->soc_tb__DOT__rst_n = 0U;
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       22);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       22);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       22);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       22);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       22);
    vlSelf->soc_tb__DOT__rst_n = 1U;
}

VL_INLINE_OPT VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__1(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Init
    IData/*31:0*/ soc_tb__DOT____Vrepeat1;
    soc_tb__DOT____Vrepeat1 = 0;
    IData/*31:0*/ soc_tb__DOT____Vrepeat2;
    soc_tb__DOT____Vrepeat2 = 0;
    // Body
    VL_WRITEF("=== Phase 5 SoC boot test ===\nWaiting for firmware to complete (PC=0x70)...\n");
    soc_tb__DOT____Vrepeat1 = 0xc350U;
    {
        while (VL_LTS_III(32, 0U, soc_tb__DOT____Vrepeat1)) {
            co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge soc_tb.clk)", 
                                                               "soc_tb.sv", 
                                                               69);
            if (vlSelf->soc_tb__DOT__done_flag) {
                goto __Vlabel1;
            }
            soc_tb__DOT____Vrepeat1 = (soc_tb__DOT____Vrepeat1 
                                       - (IData)(1U));
        }
        __Vlabel1: ;
    }
    if (vlSelf->soc_tb__DOT__done_flag) {
        VL_WRITEF("[OK] Firmware reached done label at time %0t\n",
                  64,VL_TIME_UNITED_Q(1000),-9);
        soc_tb__DOT____Vrepeat2 = 0xc8U;
        {
            while (VL_LTS_III(32, 0U, soc_tb__DOT____Vrepeat2)) {
                co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                                   nullptr, 
                                                                   "@(posedge soc_tb.clk)", 
                                                                   "soc_tb.sv", 
                                                                   81);
                if (((IData)(vlSelf->soc_tb__DOT__y00_valid) 
                     & (IData)(vlSelf->soc_tb__DOT__y33_valid))) {
                    goto __Vlabel2;
                }
                soc_tb__DOT____Vrepeat2 = (soc_tb__DOT____Vrepeat2 
                                           - (IData)(1U));
            }
            __Vlabel2: ;
        }
        if (VL_UNLIKELY((1U & ((~ (IData)(vlSelf->soc_tb__DOT__y00_valid)) 
                               | (~ (IData)(vlSelf->soc_tb__DOT__y33_valid)))))) {
            VL_WRITEF("[WARN] Timed out waiting for Y captures after done\n");
        }
        if (VL_UNLIKELY((1U & ((~ (IData)(vlSelf->soc_tb__DOT__y00_valid)) 
                               | (~ (IData)(vlSelf->soc_tb__DOT__y33_valid)))))) {
            VL_WRITEF("[FAIL] Y captures incomplete: Y[0][0]_valid=%0b Y[3][3]_valid=%0b\n",
                      1,vlSelf->soc_tb__DOT__y00_valid,
                      1,(IData)(vlSelf->soc_tb__DOT__y33_valid));
            vlSelf->soc_tb__DOT__error_count = ((IData)(1U) 
                                                + vlSelf->soc_tb__DOT__error_count);
        } else {
            if ((1U == vlSelf->soc_tb__DOT__y00_captured)) {
                VL_WRITEF("[PASS] Y[0][0] = %0# (expected 1)\n",
                          32,vlSelf->soc_tb__DOT__y00_captured);
            } else {
                VL_WRITEF("[FAIL] Y[0][0] = %0# (expected 1)\n",
                          32,vlSelf->soc_tb__DOT__y00_captured);
                vlSelf->soc_tb__DOT__error_count = 
                    ((IData)(1U) + vlSelf->soc_tb__DOT__error_count);
            }
            if ((0x10U == vlSelf->soc_tb__DOT__y33_captured)) {
                VL_WRITEF("[PASS] Y[3][3] = %0# (expected 16)\n",
                          32,vlSelf->soc_tb__DOT__y33_captured);
            } else {
                VL_WRITEF("[FAIL] Y[3][3] = %0# (expected 16)\n",
                          32,vlSelf->soc_tb__DOT__y33_captured);
                vlSelf->soc_tb__DOT__error_count = 
                    ((IData)(1U) + vlSelf->soc_tb__DOT__error_count);
            }
        }
    } else {
        VL_WRITEF("[FAIL] Timeout: firmware did not reach done label\n");
        vlSelf->soc_tb__DOT__error_count = ((IData)(1U) 
                                            + vlSelf->soc_tb__DOT__error_count);
    }
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       111);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       111);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       111);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       111);
    co_await vlSelf->__VtrigSched_h724c9e32__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge soc_tb.clk)", 
                                                       "soc_tb.sv", 
                                                       111);
    if ((0U == vlSelf->soc_tb__DOT__error_count)) {
        VL_WRITEF("\n*** ALL TESTS PASSED (0 errors) ***\n");
    } else {
        VL_WRITEF("\n*** %0d ERRORS ***\n",32,vlSelf->soc_tb__DOT__error_count);
    }
    VL_FINISH_MT("soc_tb.sv", 116, "");
}

VL_INLINE_OPT VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__2(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial__TOP__Vtiming__2\n"); );
    // Body
    co_await vlSelf->__VdlySched.delay(0x2540be400ULL, 
                                       nullptr, "soc_tb.sv", 
                                       120);
    VL_WRITEF("[TIMEOUT] SoC test exceeded 10ms\n");
    VL_FINISH_MT("soc_tb.sv", 122, "");
}

VL_INLINE_OPT VlCoroutine Vsoc_tb___024root___eval_initial__TOP__Vtiming__3(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial__TOP__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "soc_tb.sv", 
                                           18);
        vlSelf->soc_tb__DOT__clk = (1U & (~ (IData)(vlSelf->soc_tb__DOT__clk)));
    }
}

void Vsoc_tb___024root___eval_act(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vsoc_tb___024root___nba_sequent__TOP__0(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v22;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v22 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v32;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v32 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v22;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v22 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v32;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v32 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0;
    SData/*13:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0;
    CData/*4:0*/ __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3;
    __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid = 0;
    CData/*1:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state = 0;
    CData/*2:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v2;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v2 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v3;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v3 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v5;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v5 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v6;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v6 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v7;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v7 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v9;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v9 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v10;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v10 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v11;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v11 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v13;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v13 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v14;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v14 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v15;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v15 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v16;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v16 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v16;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v16 = 0;
    CData/*0:0*/ __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid = 0;
    // Body
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v16 = 0U;
    __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid = vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid = vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid = vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid;
    __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending 
        = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending 
        = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid = vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid;
    __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid = vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v22 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v32 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v22 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v32 = 0U;
    vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending 
        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending;
    __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid = vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v16 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12 = 0U;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc 
        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state 
        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state;
    __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r 
        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r;
    if (vlSelf->soc_tb__DOT__rst_n) {
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [2U]) {
            __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid = 1U;
        } else if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid) 
                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                    [2U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid = 0U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [1U]) {
            __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid = 1U;
        } else if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid) 
                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                    [1U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid = 0U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [0U]) {
            __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid = 1U;
        } else if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid) 
                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                    [0U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid = 0U;
        }
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [1U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [1U])) {
            __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending) {
            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 
                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r);
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 = 0U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r;
            }
            __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending = 0U;
            __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid = 1U;
            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 
                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r 
                                >> 8U));
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 = 8U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r;
            }
            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 
                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r 
                                >> 0x10U));
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r;
            }
            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 
                    = (vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r 
                       >> 0x18U);
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r;
            }
        }
        if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid) 
             & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
             [1U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid = 0U;
        }
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [0U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [0U])) {
            __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending) {
            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 
                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r);
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 = 0U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r;
            }
            __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending = 0U;
            __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid = 1U;
            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 
                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r 
                                >> 8U));
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 = 8U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r;
            }
            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 
                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r 
                                >> 0x10U));
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r;
            }
            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 
                    = (vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r 
                       >> 0x18U);
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 1U;
                __Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r;
            }
        }
        if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid) 
             & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
             [0U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid = 0U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                 [0U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                          [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                         [0U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v0 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [0U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [0U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8 = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [1U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                 [1U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                          [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                         [1U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v11 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [1U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [1U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18 = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [2U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                 [2U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                          [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                         [2U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v22 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [2U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last
                    [2U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                 [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                        [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
                    [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28 = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                 [0U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                          [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                         [0U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v0 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [0U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [0U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8 = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [1U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                 [1U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                          [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                         [1U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v11 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [1U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [1U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18 = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [2U]) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                 [2U] & ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                          [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
                         [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                         [2U]]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v22 = 1U;
            }
        } else if ((0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [2U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22 = 1U;
            }
        } else if ((1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last
                    [2U])) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                 [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24 = 1U;
            } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                        [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25 = 1U;
            }
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27 = 1U;
        } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
                    [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28 = 1U;
        }
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state))) {
            if (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r) {
                __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state = 1U;
                __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc = 0U;
                __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = 0U;
            }
        } else if ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state))) {
            __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc 
                = (7U & ((IData)(1U) + (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc)));
            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))) {
                if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))) {
                    if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))) {
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30;
                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0 = 1U;
                        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state = 2U;
                        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = 1U;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31;
                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1 = 1U;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v2 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v3 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33;
                    } else {
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30;
                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4 = 1U;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v5 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v6 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32;
                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v7 
                            = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33;
                    }
                } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))) {
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30;
                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8 = 1U;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v9 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v10 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v11 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33;
                } else {
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30;
                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12 = 1U;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v13 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v14 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32;
                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v15 
                        = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33;
                }
            }
        } else if ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state))) {
            if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r) 
                 & (~ (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r)))) {
                __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state = 1U;
                __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc = 0U;
            }
        }
    } else {
        __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid = 0U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10 = 1U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21 = 1U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v32 = 1U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10 = 1U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21 = 1U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v32 = 1U;
        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = 0U;
    }
    if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__rst_n)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 4U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__i = 4U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v16 = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r = 0U;
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [2U]) {
            vlSelf->soc_tb__DOT__dut__DOT__s2_rdata 
                = vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__rdata_comb;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [1U]) {
            vlSelf->soc_tb__DOT__dut__DOT__s1_rdata 
                = vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem
                [(0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                             [1U] >> 2U))];
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
            [0U]) {
            vlSelf->soc_tb__DOT__dut__DOT__s0_rdata 
                = vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem
                [(0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                             [0U] >> 2U))];
        }
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w 
                = ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                    ? ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                        ? vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata
                        : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                            ? (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half)
                            : (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte)))
                    : ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                        ? vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata
                        : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                            ? (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half) 
                                                  >> 0xfU)))) 
                                << 0x10U) | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half))
                            : (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte) 
                                                  >> 7U)))) 
                                << 8U) | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte)))));
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m 
                = ((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e);
        }
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [1U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [1U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                [1U];
            vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                [1U];
            vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r 
                = (0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                              [1U] >> 2U));
        }
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [0U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [0U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                [0U];
            vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                [0U];
            vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r 
                = (0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                              [0U] >> 2U));
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product)));
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [2U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [2U])) {
            __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending = 1U;
        }
        if (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending) {
            __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending = 0U;
            __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid = 1U;
            if ((1U & (~ ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r) 
                          >> 5U)))) {
                if ((1U & (~ ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r) 
                              >> 4U)))) {
                    if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                        if ((1U & (~ ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r) 
                                      >> 2U)))) {
                            if ((1U & (~ ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r) 
                                          >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r)))) {
                                    if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0 
                                            = (0xffU 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0 = 1U;
                                    }
                                    if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1 
                                            = (0xffU 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                  >> 8U));
                                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1 = 1U;
                                    }
                                    if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2 
                                            = (0xffU 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                  >> 0x10U));
                                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2 = 1U;
                                    }
                                    if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3 
                                            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                               >> 0x18U);
                                        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3 = 1U;
                                    }
                                }
                            }
                        }
                    } else if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                        if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                                if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4 
                                        = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5 
                                        = (0xffU & 
                                           (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6 
                                        = (0xffU & 
                                           (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7 
                                        = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7 = 1U;
                                }
                            } else {
                                if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8 
                                        = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9 
                                        = (0xffU & 
                                           (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10 
                                        = (0xffU & 
                                           (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11 
                                        = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11 = 1U;
                                }
                            }
                        } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12 
                                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15 
                                    = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0 
                                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3 
                                    = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3 = 1U;
                            }
                        }
                    } else if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4 
                                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7 
                                    = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8 
                                    = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10 
                                    = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                                __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11 
                                    = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11 = 1U;
                            }
                        }
                    } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                            __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12 
                                = (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r);
                            __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12 = 1U;
                        }
                        if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                            __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13 
                                = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 8U));
                            __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13 = 1U;
                        }
                        if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                            __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14 
                                = (0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                            >> 0x10U));
                            __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14 = 1U;
                        }
                        if ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                            __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15 
                                = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                                   >> 0x18U);
                            __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15 = 1U;
                        }
                    } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r))) {
                        if ((1U & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r)) {
                            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r = 1U;
                            __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = 0U;
                        } else {
                            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r = 0U;
                        }
                    }
                }
            }
        }
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
             [2U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
             [2U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r 
                = (0x3fU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                            [2U] >> 2U));
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                [2U];
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                [2U];
        }
        if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid) 
             & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
             [2U])) {
            __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13 
            = (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03 
               + (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product)));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00 
            = (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01 
            = (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02 
            = (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03 
            = (((- (IData)((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product));
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__s2_rdata = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__s1_rdata = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__s0_rdata = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33 = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending = 0U;
        __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid = 0U;
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v16 = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02 = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03 = 0U;
    }
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e = 0U;
    } else if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e 
            = (((0x33U == (0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)) 
                || (0x13U == (0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                ? ((0x4000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                    ? ((0x2000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                        ? ((0x1000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                            ? 2U : 3U) : ((0x1000U 
                                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? ((0x40000000U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? 7U
                                               : 6U)
                                           : 4U)) : 
                   ((0x2000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                     ? ((0x1000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                         ? 9U : 8U) : ((0x1000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                        ? 5U : ((IData)(
                                                        (0x40000033U 
                                                         == 
                                                         (0x4000007fU 
                                                          & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                                                 ? 1U
                                                 : 0U))))
                : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e 
            = (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                        >> 0x14U));
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e 
            = (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                        >> 0xfU));
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e 
            = ((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                >> 0xfU))) ? 0U : (
                                                   ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                                                    & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                                       == 
                                                       (0x1fU 
                                                        & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                           >> 0xfU))))
                                                    ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                                                    : 
                                                   ((0x1eU 
                                                     >= 
                                                     (0x1fU 
                                                      & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                          >> 0xfU) 
                                                         - (IData)(1U))))
                                                     ? 
                                                    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                                                    [
                                                    (0x1fU 
                                                     & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                         >> 0xfU) 
                                                        - (IData)(1U)))]
                                                     : 0U)));
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e 
            = ((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                >> 0x14U))) ? 0U : 
               (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                 & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                    == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                 >> 0x14U)))) ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                 : ((0x1eU >= (0x1fU & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                         >> 0x14U) 
                                        - (IData)(1U))))
                     ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                    [(0x1fU & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                >> 0x14U) - (IData)(1U)))]
                     : 0U)));
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_d;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d;
    }
    vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid = __Vdly__soc_tb__DOT__dut__DOT__s2_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid = __Vdly__soc_tb__DOT__dut__DOT__s1_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid = __Vdly__soc_tb__DOT__dut__DOT__s0_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending 
        = __Vdly__soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending;
    vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid = __Vdly__soc_tb__DOT__dut__DOT__s1_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending 
        = __Vdly__soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending;
    vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid = __Vdly__soc_tb__DOT__dut__DOT__s0_bvalid;
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v17) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v18) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v20) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v23) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v24) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v25) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v26) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v27) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant__v28) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy__v32) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v17) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v18) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v20) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v21) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v22) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v23) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v24) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v25) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v26) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v27) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant__v28) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy__v32) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2U] = 0U;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v0;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v1;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v2;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v3;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v4;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v5;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v6;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v7;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v8;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v9;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v10;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v11;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v12;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v13;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v14;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v15;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[0U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[1U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[2U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[3U][3U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state 
        = __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__state;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc 
        = __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__cyc;
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v0))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v1))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v2))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram1__DOT__mem__v3))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v0))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v1))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v2))));
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3))) 
                & vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem
                [__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3) 
                                   << (IData)(__Vdlyvlsb__soc_tb__DOT__dut__DOT__u_sram0__DOT__mem__v3))));
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                            [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                            [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                    [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                            [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
                           [2U] : 0U)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending 
        = __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r 
        = __Vdly__soc_tb__DOT__dut__DOT__u_accel__DOT__done_r;
    vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid = __Vdly__soc_tb__DOT__dut__DOT__s2_bvalid;
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v0;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v1;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v2;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v3;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v4;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v5;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v6;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v7;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v8;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v9;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v10;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v11;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v12;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v13;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v14;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v15;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v0;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v1;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v2;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v3;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v4;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v5;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v6;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v7;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v8;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v9;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v10;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v11;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][0U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v12;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][1U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v13;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][2U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v14;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][3U] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg__v15;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg__v16) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[0U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[1U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[2U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[3U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[0U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[1U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[2U][3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[3U][3U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
            [3U][3U] << 0x18U) | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                   [3U][2U] << 0x10U) 
                                  | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                      [3U][1U] << 8U) 
                                     | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                     [3U][0U])));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
            [2U][3U] << 0x18U) | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                   [2U][2U] << 0x10U) 
                                  | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                      [2U][1U] << 8U) 
                                     | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                     [2U][0U])));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
            [1U][3U] << 0x18U) | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                   [1U][2U] << 0x10U) 
                                  | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                      [1U][1U] << 8U) 
                                     | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                     [1U][0U])));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
            [0U][3U] << 0x18U) | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                   [0U][2U] << 0x10U) 
                                  | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                      [0U][1U] << 8U) 
                                     | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                     [0U][0U])));
    if ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s 
            = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
               [0U][0U] : ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                           [1U][0U] : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                       [2U][0U] : (
                                                   (3U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s 
            = ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
               [0U][1U] : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                           [1U][1U] : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                       [2U][1U] : (
                                                   (4U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s 
            = ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
               [0U][2U] : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                           [1U][2U] : ((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                       [2U][2U] : (
                                                   (5U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))));
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s 
            = ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
               [0U][3U] : ((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                           [1U][3U] : ((5U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                       [2U][3U] : (
                                                   (6U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))));
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                                              >> 8U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                                              >> 0x10U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                                           >> 0x18U)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                                              >> 8U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                                              >> 0x10U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                                           >> 0x18U)))));
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d = 0U;
    } else if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                                              >> 8U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                                              >> 0x10U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                                           >> 0x18U)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                                              >> 8U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (0xffU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                                              >> 0x10U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product 
        = (0xffffU & VL_MULS_III(16, (0xffffU & VL_EXTENDS_II(16,8, (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s))), 
                                 (0xffffU & VL_EXTENDS_II(16,8, 
                                                          (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                                           >> 0x18U)))));
}

VL_INLINE_OPT void Vsoc_tb___024root___nba_sequent__TOP__1(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___nba_sequent__TOP__1\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0;
    __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 = 0;
    IData/*31:0*/ __Vdlyvval__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0;
    __Vdlyvval__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 = 0;
    CData/*0:0*/ __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v1;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v1 = 0;
    // Body
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 = 0U;
    __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v1 = 0U;
    if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__rst_n)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__unnamedblk1__DOT__i = 0x20U;
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
             & (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w)))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT____Vlvbound_haf05b89f__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data;
            if ((0x1eU >= (0x1fU & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                    - (IData)(1U))))) {
                __Vdlyvval__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT____Vlvbound_haf05b89f__0;
                __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 = 1U;
                __Vdlyvdim0__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0 
                    = (0x1fU & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                - (IData)(1U)));
            }
        }
    } else {
        __Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v1 = 1U;
    }
    if (((IData)(vlSelf->soc_tb__DOT__rst_n) & (0x70U 
                                                == vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc))) {
        vlSelf->soc_tb__DOT__done_flag = 1U;
    }
    if ((((IData)(vlSelf->soc_tb__DOT__rst_n) & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
          [0U]) & (4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)))) {
        if ((0x50000024U == vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r)) {
            vlSelf->soc_tb__DOT__y00_valid = 1U;
            vlSelf->soc_tb__DOT__y00_captured = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                [0U];
        }
        if ((0x50000060U == vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r)) {
            vlSelf->soc_tb__DOT__y33_valid = 1U;
            vlSelf->soc_tb__DOT__y33_captured = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                [0U];
        }
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[__Vdlyvdim0__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0] 
            = __Vdlyvval__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v0;
    }
    if (__Vdlyvset__soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs__v1) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[3U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[4U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[5U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[6U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[7U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[8U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[9U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xaU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xbU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xcU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xdU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xeU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0xfU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x10U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x11U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x12U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x13U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x14U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x15U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x16U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x17U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x18U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x19U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x1aU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x1bU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x1cU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x1dU] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0x1eU] = 0U;
    }
}

extern const VlUnpacked<CData/*3:0*/, 512> Vsoc_tb__ConstPool__TABLE_hc47a5df6_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h03c3adda_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h7ca8bf9e_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_ha96ed2bf_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_hd2a3c541_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h101bb02f_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_he4685dc5_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_hbd434190_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vsoc_tb__ConstPool__TABLE_h4e53dcde_0;

VL_INLINE_OPT void Vsoc_tb___024root___nba_sequent__TOP__2(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___nba_sequent__TOP__2\n"); );
    // Init
    CData/*0:0*/ soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0;
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0 = 0;
    CData/*0:0*/ soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0;
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0 = 0;
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data 
        = ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w
                : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
                    ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w
                    : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w)));
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m;
        }
        if ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
                vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 0U;
            } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
                vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 0U;
            } else if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                       [0U]) {
                vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                    = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                    [0U];
                vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 0U;
            }
        } else if ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
                if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                    [0U]) {
                    vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 4U;
                }
            } else if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                       [0U]) {
                vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 0U;
            }
        } else if ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                 [0U] & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                 [0U])) {
                vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 2U;
            }
        } else if (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m) {
            vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m;
            vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r 
                = ((0U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                    ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                        << 0x18U) | ((0xff0000U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                                   << 0x10U)) 
                                     | ((0xff00U & 
                                         (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                          << 8U)) | 
                                        (0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))))
                    : ((1U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                        ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                            << 0x10U) | (0xffffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))
                        : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m));
            vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r 
                = vlSelf->soc_tb__DOT__dut__DOT__dmem_be;
            vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 1U;
        } else if (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m) {
            vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m;
            vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 3U;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w = 0U;
        vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata = 0U;
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
               [2U] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
               [2U]);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
               [2U] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
               [2U]);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
               [2U] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
               [2U]);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
               [2U]);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
               [2U]);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
               [2U]);
    }
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w) 
           & (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w)));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r;
    if ((0U == (vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r 
                >> 0x10U))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0U] = 0U;
    } else if ((0x1000U == (vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r 
                            >> 0x10U))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0U] = 1U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0U] = 1U;
    } else if ((0x5000U == (vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r 
                            >> 0x10U))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0U] = 2U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0U] = 2U;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0U] = 3U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0U] = 3U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r;
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m = 0U;
    }
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m) 
           & (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m)));
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e = 0U;
    } else if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e 
            = (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                        >> 7U));
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result;
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m = 0U;
    }
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e = 0U;
    } else if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_d;
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m = 0U;
    }
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e = 0U;
    } else if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e 
            = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_d;
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m = 0U;
    }
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e = 0U;
    } else if ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e 
            = (7U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                     >> 0xcU));
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [1U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [1U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [1U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [2U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [2U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [2U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__rdata_comb 
        = ((0x80U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
            [2U]) ? 0U : ((0x40U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                           [2U]) ? ((0x20U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                     [2U]) ? ((0x10U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                               [2U])
                                               ? 0U
                                               : ((8U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 0U
                                                   : 
                                                  ((4U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 0U
                                                    : 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [3U]
                                                   [3U])))
                                     : ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                         [2U]) ? ((8U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 
                                                  ((4U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [3U]
                                                   [2U]
                                                    : 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [3U]
                                                   [1U])
                                                   : 
                                                  ((4U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [3U]
                                                   [0U]
                                                    : 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [2U]
                                                   [3U]))
                                         : ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                              [2U])
                                              ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                             [2U][2U]
                                              : vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                             [2U][1U])
                                             : ((4U 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                [2U]
                                                [0U]
                                                 : 
                                                vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                [1U]
                                                [3U]))))
                           : ((0x20U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                               [2U]) ? ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                         [2U]) ? ((8U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                   [2U])
                                                   ? 
                                                  ((4U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [1U]
                                                   [2U]
                                                    : 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [1U]
                                                   [1U])
                                                   : 
                                                  ((4U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                    [2U])
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [1U]
                                                   [0U]
                                                    : 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                   [0U]
                                                   [3U]))
                                         : ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                              [2U])
                                              ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                             [0U][2U]
                                              : vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                             [0U][1U])
                                             : ((4U 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                                [0U]
                                                [0U]
                                                 : 
                                                ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [3U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                     [3U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                        [3U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                       [3U]
                                                       [0U]))))))
                               : ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                   [2U]) ? ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                             [2U]) ? 
                                            ((4U & 
                                              vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                              [2U])
                                              ? ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [2U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                     [2U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                        [2U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                       [2U]
                                                       [0U])))
                                              : ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [1U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                     [1U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                        [1U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                       [1U]
                                                       [0U]))))
                                             : ((4U 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [0U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                     [0U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                        [0U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                       [0U]
                                                       [0U])))
                                                 : 
                                                ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                  [3U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                     [3U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                        [3U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                       [3U]
                                                       [0U])))))
                                   : ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                       [2U]) ? ((4U 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                                 [2U])
                                                 ? 
                                                ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                  [2U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                     [2U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                        [2U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                       [2U]
                                                       [0U])))
                                                 : 
                                                ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                  [1U]
                                                  [3U] 
                                                  << 0x18U) 
                                                 | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                     [1U]
                                                     [2U] 
                                                     << 0x10U) 
                                                    | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                        [1U]
                                                        [1U] 
                                                        << 8U) 
                                                       | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                       [1U]
                                                       [0U]))))
                                       : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                           [2U]) ? 
                                          ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                            [0U][3U] 
                                            << 0x18U) 
                                           | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                               [0U]
                                               [2U] 
                                               << 0x10U) 
                                              | ((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                  [0U]
                                                  [1U] 
                                                  << 8U) 
                                                 | vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                                 [0U]
                                                 [0U])))
                                           : (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r) 
                                               << 1U) 
                                              | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r))))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte 
        = (0xffU & ((0U == (3U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m))
                     ? vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata
                     : ((1U == (3U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m))
                         ? (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                            >> 8U) : ((2U == (3U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m))
                                       ? (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                          >> 0x10U)
                                       : (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                          >> 0x18U)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half 
        = (0xffffU & ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m)
                       ? (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                          >> 0x10U) : vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val 
        = ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m
                : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m));
    __Vtableidx2 = ((((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m)
                       ? 0xcU : 3U) << 5U) | ((0x18U 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m 
                                                  << 3U)) 
                                              | ((6U 
                                                  & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m) 
                                                     << 1U)) 
                                                 | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m))));
    vlSelf->soc_tb__DOT__dut__DOT__dmem_be = Vsoc_tb__ConstPool__TABLE_hc47a5df6_0
        [__Vtableidx2];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a 
        = (((IData)(soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0) 
            & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m) 
               == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e)))
            ? 1U : (((IData)(soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0) 
                     & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                        == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e)))
                     ? 2U : 0U));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b 
        = (((IData)(soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0) 
            & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m) 
               == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e)))
            ? 1U : (((IData)(soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0) 
                     & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                        == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e)))
                     ? 2U : 0U));
    vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state 
        = vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state;
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
        = ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd 
        = ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we 
        = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)) 
           & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[0U] 
        = (1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [0U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [0U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[0U] 
        = (1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [1U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [1U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[1U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[0U] 
        = (2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [1U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [2U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [2U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [2U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [2U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [2U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[2U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[0U] 
        = (3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [1U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[1U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[0U] 
        = (4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [1U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [2U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [2U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [2U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [2U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[2U] = 0U;
    }
    if ((1U & ((~ (IData)(vlSelf->soc_tb__DOT__rst_n)) 
               | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d = 0x13U;
    } else if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if)))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
            = vlSelf->soc_tb__DOT__dut__DOT__u_irom__DOT__mem
            [(0x1ffU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                        >> 2U))];
    }
    if (vlSelf->soc_tb__DOT__rst_n) {
        if ((1U & (~ (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if)))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                = vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc_next;
        }
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e
            : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e)
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e
            : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken 
        = (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e) 
            & ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                ? ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                    ? ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                        ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                           >= vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd)
                        : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                           < vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd))
                    : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                        ? VL_GTES_III(32, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd)
                        : VL_LTS_III(32, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd)))
                : ((1U & (~ ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e) 
                             >> 1U))) && ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                                           ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                                              != vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd)
                                           : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                                              == vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd))))) 
           | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result 
        = ((8U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
            ? ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                ? 0U : ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                         ? 0U : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                                  ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                                     < vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)
                                  : VL_LTS_III(32, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b))))
            : ((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                ? ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                    ? ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                        ? VL_SHIFTRS_III(32,32,5, vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a, 
                                         (0x1fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b))
                        : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           >> (0x1fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)))
                    : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                        ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           << (0x1fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b))
                        : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           ^ vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)))
                : ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                    ? ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                        ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           | vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)
                        : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b))
                    : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e))
                        ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           - vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)
                        : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a 
                           + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)))));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id 
        = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)) 
           & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i 
        = (((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                        >> 0x1fU))) << 0xcU) | (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                >> 0x14U));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e) 
           & ((0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e)) 
              & (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e) 
                  == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                               >> 0xfU))) | ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e) 
                                             == (0x1fU 
                                                 & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                    >> 0x14U))))));
    __Vtableidx1 = (0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_d 
        = Vsoc_tb__ConstPool__TABLE_h03c3adda_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_d 
        = Vsoc_tb__ConstPool__TABLE_h7ca8bf9e_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_d 
        = Vsoc_tb__ConstPool__TABLE_ha96ed2bf_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_d 
        = Vsoc_tb__ConstPool__TABLE_hd2a3c541_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_d 
        = Vsoc_tb__ConstPool__TABLE_h101bb02f_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_d 
        = Vsoc_tb__ConstPool__TABLE_he4685dc5_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_d 
        = Vsoc_tb__ConstPool__TABLE_hbd434190_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_d 
        = Vsoc_tb__ConstPool__TABLE_h4e53dcde_0[__Vtableidx1];
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_d 
        = ((0x40U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
            ? ((0x20U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                ? ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                    ? ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                        ? 0U : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                 ? 0U : ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                          ? ((1U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                              ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i
                                              : 0U)
                                          : 0U))) : 
                   ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                     ? ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                         ? ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                             ? ((1U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                 ? (((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                 >> 0x1fU))) 
                                     << 0x15U) | ((0x100000U 
                                                   & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                      >> 0xbU)) 
                                                  | ((0xff000U 
                                                      & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d) 
                                                     | ((0x800U 
                                                         & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                            >> 9U)) 
                                                        | (0x7feU 
                                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                              >> 0x14U))))))
                                 : 0U) : 0U) : 0U) : 
                    ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                      ? ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                          ? ((1U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                              ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i
                              : 0U) : 0U) : ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                              ? ((1U 
                                                  & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                  ? 
                                                 (((- (IData)(
                                                              (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                               >> 0x1fU))) 
                                                   << 0xdU) 
                                                  | ((0x1000U 
                                                      & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                         >> 0x13U)) 
                                                     | ((0x800U 
                                                         & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                            << 4U)) 
                                                        | ((0x7e0U 
                                                            & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                               >> 0x14U)) 
                                                           | (0x1eU 
                                                              & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                                 >> 7U))))))
                                                  : 0U)
                                              : 0U))))
                : 0U) : ((0x20U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                          ? ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                              ? ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                  ? 0U : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? ((1U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   : 0U)
                                               : 0U)
                                           : 0U)) : 
                             ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                               ? 0U : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                        ? 0U : ((2U 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                 ? 
                                                ((1U 
                                                  & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                  ? 
                                                 (((- (IData)(
                                                              (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                               >> 0x1fU))) 
                                                   << 0xcU) 
                                                  | ((0xfe0U 
                                                      & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                         >> 0x14U)) 
                                                     | (0x1fU 
                                                        & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                           >> 7U))))
                                                  : 0U)
                                                 : 0U))))
                          : ((0x10U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                              ? ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                  ? 0U : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? ((1U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   ? 
                                                  (0xfffff000U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   : 0U)
                                               : 0U)
                                           : ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? ((1U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i
                                                   : 0U)
                                               : 0U)))
                              : ((8U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                  ? 0U : ((4U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? 0U : (
                                                   (2U 
                                                    & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                    ? 
                                                   ((1U 
                                                     & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                     ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i
                                                     : 0U)
                                                    : 0U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex 
        = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)) 
           & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use) 
              | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken)));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use) 
           | (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc_next 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken)
            ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e)
                ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                    ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                    : (0xfffffffeU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))
                : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                   + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e))
            : ((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc));
}

void Vsoc_tb___024root___eval_nba(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_nba\n"); );
    // Body
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_tb___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_tb___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vsoc_tb___024root___nba_sequent__TOP__2(vlSelf);
        vlSelf->__Vm_traceActivity[4U] = 1U;
    }
}

void Vsoc_tb___024root___timing_resume(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___timing_resume\n"); );
    // Body
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VtrigSched_h724c9e32__0.resume("@(posedge soc_tb.clk)");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        vlSelf->__VdlySched.resume();
    }
}

void Vsoc_tb___024root___timing_commit(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___timing_commit\n"); );
    // Body
    if ((! (1ULL & vlSelf->__VactTriggered.word(0U)))) {
        vlSelf->__VtrigSched_h724c9e32__0.commit("@(posedge soc_tb.clk)");
    }
}

void Vsoc_tb___024root___eval_triggers__act(Vsoc_tb___024root* vlSelf);

bool Vsoc_tb___024root___eval_phase__act(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<3> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vsoc_tb___024root___eval_triggers__act(vlSelf);
    Vsoc_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vsoc_tb___024root___timing_resume(vlSelf);
        Vsoc_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vsoc_tb___024root___eval_phase__nba(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vsoc_tb___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__nba(Vsoc_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__act(Vsoc_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vsoc_tb___024root___eval(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vsoc_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("soc_tb.sv", 12, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vsoc_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("soc_tb.sv", 12, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vsoc_tb___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vsoc_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vsoc_tb___024root___eval_debug_assertions(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG
