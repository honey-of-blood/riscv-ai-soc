// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_accel_tb.h for the primary calling header

#include "Vcrossbar_accel_tb__pch.h"
#include "Vcrossbar_accel_tb___024root.h"

VL_ATTR_COLD void Vcrossbar_accel_tb___024root___eval_initial__TOP(Vcrossbar_accel_tb___024root* vlSelf);
VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__0(Vcrossbar_accel_tb___024root* vlSelf);
VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__1(Vcrossbar_accel_tb___024root* vlSelf);
VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__2(Vcrossbar_accel_tb___024root* vlSelf);
VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__3(Vcrossbar_accel_tb___024root* vlSelf);

void Vcrossbar_accel_tb___024root___eval_initial(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial\n"); );
    // Body
    Vcrossbar_accel_tb___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[1U] = 1U;
    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__3(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0 
        = vlSelf->crossbar_accel_tb__DOT__clk;
    vlSelf->__Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__rst_n__0 
        = vlSelf->crossbar_accel_tb__DOT__rst_n;
}

VL_INLINE_OPT VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__0(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__rst_n = 0U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       15);
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       15);
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       15);
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       15);
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       15);
    vlSelf->crossbar_accel_tb__DOT__rst_n = 1U;
}

VL_INLINE_OPT VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__1(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Init
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__0__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__0__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__0__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__1__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__1__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__1__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__1__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__2__got;
    __Vtask_crossbar_accel_tb__DOT__check__2__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__2__exp;
    __Vtask_crossbar_accel_tb__DOT__check__2__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__2__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__3__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__3__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__3__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__4__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__4__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__4__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__4__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__5__got;
    __Vtask_crossbar_accel_tb__DOT__check__5__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__5__exp;
    __Vtask_crossbar_accel_tb__DOT__check__5__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__5__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__6__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__6__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__6__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__7__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__7__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__7__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__8__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__8__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__8__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__9__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__9__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__9__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__10__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__10__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__10__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__11__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__11__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__11__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__12__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__12__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__12__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__13__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__13__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__13__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__14__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__14__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__14__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__15__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__15__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__15__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__15__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__16__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__16__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__16__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__16__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__17__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__17__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__17__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__17__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__18__got;
    __Vtask_crossbar_accel_tb__DOT__check__18__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__18__exp;
    __Vtask_crossbar_accel_tb__DOT__check__18__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__18__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__19__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__19__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__19__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__19__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__20__got;
    __Vtask_crossbar_accel_tb__DOT__check__20__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__20__exp;
    __Vtask_crossbar_accel_tb__DOT__check__20__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__20__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__21__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__21__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__21__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__21__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__22__got;
    __Vtask_crossbar_accel_tb__DOT__check__22__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__22__exp;
    __Vtask_crossbar_accel_tb__DOT__check__22__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__22__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__23__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__23__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__23__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__23__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__24__got;
    __Vtask_crossbar_accel_tb__DOT__check__24__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__24__exp;
    __Vtask_crossbar_accel_tb__DOT__check__24__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__24__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__25__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__25__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__25__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__25__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__26__got;
    __Vtask_crossbar_accel_tb__DOT__check__26__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__26__exp;
    __Vtask_crossbar_accel_tb__DOT__check__26__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__26__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__27__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__27__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__27__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__27__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__28__got;
    __Vtask_crossbar_accel_tb__DOT__check__28__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__28__exp;
    __Vtask_crossbar_accel_tb__DOT__check__28__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__28__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__29__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__29__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__29__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__29__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__30__got;
    __Vtask_crossbar_accel_tb__DOT__check__30__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__30__exp;
    __Vtask_crossbar_accel_tb__DOT__check__30__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__30__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__31__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__31__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__31__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__31__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__32__got;
    __Vtask_crossbar_accel_tb__DOT__check__32__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__32__exp;
    __Vtask_crossbar_accel_tb__DOT__check__32__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__32__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__33__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__33__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__33__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__33__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__34__got;
    __Vtask_crossbar_accel_tb__DOT__check__34__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__34__exp;
    __Vtask_crossbar_accel_tb__DOT__check__34__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__34__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__35__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__35__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__35__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__35__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__36__got;
    __Vtask_crossbar_accel_tb__DOT__check__36__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__36__exp;
    __Vtask_crossbar_accel_tb__DOT__check__36__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__36__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__37__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__37__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__37__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__37__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__38__got;
    __Vtask_crossbar_accel_tb__DOT__check__38__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__38__exp;
    __Vtask_crossbar_accel_tb__DOT__check__38__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__38__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__39__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__39__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__39__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__39__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__40__got;
    __Vtask_crossbar_accel_tb__DOT__check__40__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__40__exp;
    __Vtask_crossbar_accel_tb__DOT__check__40__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__40__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__41__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__41__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__41__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__41__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__42__got;
    __Vtask_crossbar_accel_tb__DOT__check__42__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__42__exp;
    __Vtask_crossbar_accel_tb__DOT__check__42__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__42__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__43__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__43__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__43__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__43__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__44__got;
    __Vtask_crossbar_accel_tb__DOT__check__44__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__44__exp;
    __Vtask_crossbar_accel_tb__DOT__check__44__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__44__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__45__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__45__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__45__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__45__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__46__got;
    __Vtask_crossbar_accel_tb__DOT__check__46__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__46__exp;
    __Vtask_crossbar_accel_tb__DOT__check__46__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__46__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__47__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__47__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__47__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__47__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__48__got;
    __Vtask_crossbar_accel_tb__DOT__check__48__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__48__exp;
    __Vtask_crossbar_accel_tb__DOT__check__48__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__48__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__49__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__49__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__49__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__50__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__50__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__50__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__51__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__51__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__51__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__52__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__52__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__52__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__53__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__53__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__53__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__54__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__54__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__54__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__55__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__55__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__55__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__56__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__56__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__56__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__57__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__57__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__57__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__58__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__58__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__58__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__58__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__59__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__59__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__59__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__59__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__60__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__60__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__60__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__60__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__61__got;
    __Vtask_crossbar_accel_tb__DOT__check__61__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__61__exp;
    __Vtask_crossbar_accel_tb__DOT__check__61__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__61__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__62__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__62__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__62__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__62__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__63__got;
    __Vtask_crossbar_accel_tb__DOT__check__63__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__63__exp;
    __Vtask_crossbar_accel_tb__DOT__check__63__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__63__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__64__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__64__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__64__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__64__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__65__got;
    __Vtask_crossbar_accel_tb__DOT__check__65__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__65__exp;
    __Vtask_crossbar_accel_tb__DOT__check__65__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__65__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__66__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__66__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__66__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__67__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__67__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__67__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__67__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__68__got;
    __Vtask_crossbar_accel_tb__DOT__check__68__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__68__exp;
    __Vtask_crossbar_accel_tb__DOT__check__68__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__68__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__69__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__69__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__69__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__70__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__70__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__70__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__71__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__71__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__71__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__72__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__72__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__72__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__73__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__73__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__73__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__74__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__74__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__74__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__75__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__75__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__75__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__76__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__76__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__76__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__77__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__77__data;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__data = 0;
    CData/*3:0*/ __Vtask_crossbar_accel_tb__DOT__axi_write__77__strb;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__strb = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__78__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__78__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__78__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__78__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__79__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__79__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__79__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__79__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__80__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__80__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__80__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__80__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__81__got;
    __Vtask_crossbar_accel_tb__DOT__check__81__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__81__exp;
    __Vtask_crossbar_accel_tb__DOT__check__81__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__81__tag;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__82__addr;
    __Vtask_crossbar_accel_tb__DOT__axi_read__82__addr = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__axi_read__82__data;
    __Vtask_crossbar_accel_tb__DOT__axi_read__82__data = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__83__got;
    __Vtask_crossbar_accel_tb__DOT__check__83__got = 0;
    IData/*31:0*/ __Vtask_crossbar_accel_tb__DOT__check__83__exp;
    __Vtask_crossbar_accel_tb__DOT__check__83__exp = 0;
    std::string __Vtask_crossbar_accel_tb__DOT__check__83__tag;
    // Body
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    while ((1U & (~ (IData)(vlSelf->crossbar_accel_tb__DOT__rst_n)))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           207);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       208);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_WRITEF("\n=== TEST 1: SRAM sanity (0x0000_0004 = 0xDEADBEEF) ===\n");
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__data = 0xdeadbeefU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__0__addr = 4U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__0__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__0__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__0__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__1__addr = 4U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__1__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__1__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__1__data;
    __Vtask_crossbar_accel_tb__DOT__check__2__tag = 
        std::string{"SRAM word write/read"};
    __Vtask_crossbar_accel_tb__DOT__check__2__exp = 0xdeadbeefU;
    __Vtask_crossbar_accel_tb__DOT__check__2__got = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__2__got 
         == __Vtask_crossbar_accel_tb__DOT__check__2__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__2__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__2__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__2__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__2__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__2__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__data = 0xcafebabeU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__3__addr = 8U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__3__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__3__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__3__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__4__addr = 8U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__4__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__4__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__4__data;
    __Vtask_crossbar_accel_tb__DOT__check__5__tag = 
        std::string{"SRAM word 2 write/read"};
    __Vtask_crossbar_accel_tb__DOT__check__5__exp = 0xcafebabeU;
    __Vtask_crossbar_accel_tb__DOT__check__5__got = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__5__got 
         == __Vtask_crossbar_accel_tb__DOT__check__5__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__5__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__5__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__5__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__5__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__5__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    VL_WRITEF("\n=== TEST 2: Identity matmul through crossbar (Y = A) ===\n");
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__data = 1U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__6__addr = 0x50000004U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__6__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__6__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__6__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__data = 0x100U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__7__addr = 0x50000008U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__7__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__7__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__7__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__data = 0x10000U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__8__addr = 0x5000000cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__8__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__8__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__8__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__data = 0x1000000U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__9__addr = 0x50000010U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__9__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__9__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__9__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__data = 0x4030201U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__10__addr = 0x50000014U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__10__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__10__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__10__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__data = 0x8070605U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__11__addr = 0x50000018U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__11__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__11__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__11__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__data = 0xc0b0a09U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__12__addr = 0x5000001cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__12__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__12__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__12__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__data = 0x100f0e0dU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__13__addr = 0x50000020U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__13__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__13__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__13__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__data = 1U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__14__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__14__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__14__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__14__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__15__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__15__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__15__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__15__data;
    while ((1U & (~ (vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
                     >> 1U)))) {
        __Vtask_crossbar_accel_tb__DOT__axi_read__16__addr = 0x50000000U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           165);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__16__addr;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           167);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               168);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           170);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               172);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        __Vtask_crossbar_accel_tb__DOT__axi_read__16__data 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
            [0U];
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           174);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
        vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
            = __Vtask_crossbar_accel_tb__DOT__axi_read__16__data;
    }
    VL_WRITEF("[INT] CTRL=0x%08x (done=1)\n",32,vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd);
    __Vtask_crossbar_accel_tb__DOT__axi_read__17__addr = 0x50000024U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__17__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__17__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__17__data;
    __Vtask_crossbar_accel_tb__DOT__check__18__tag = 
        std::string{"Y[0][0]=1"};
    __Vtask_crossbar_accel_tb__DOT__check__18__exp = 1U;
    __Vtask_crossbar_accel_tb__DOT__check__18__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__18__got 
         == __Vtask_crossbar_accel_tb__DOT__check__18__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__18__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__18__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__18__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__18__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__18__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__19__addr = 0x50000028U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__19__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__19__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__19__data;
    __Vtask_crossbar_accel_tb__DOT__check__20__tag = 
        std::string{"Y[0][1]=2"};
    __Vtask_crossbar_accel_tb__DOT__check__20__exp = 2U;
    __Vtask_crossbar_accel_tb__DOT__check__20__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__20__got 
         == __Vtask_crossbar_accel_tb__DOT__check__20__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__20__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__20__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__20__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__20__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__20__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__21__addr = 0x5000002cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__21__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__21__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__21__data;
    __Vtask_crossbar_accel_tb__DOT__check__22__tag = 
        std::string{"Y[0][2]=3"};
    __Vtask_crossbar_accel_tb__DOT__check__22__exp = 3U;
    __Vtask_crossbar_accel_tb__DOT__check__22__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__22__got 
         == __Vtask_crossbar_accel_tb__DOT__check__22__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__22__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__22__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__22__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__22__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__22__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__23__addr = 0x50000030U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__23__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__23__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__23__data;
    __Vtask_crossbar_accel_tb__DOT__check__24__tag = 
        std::string{"Y[0][3]=4"};
    __Vtask_crossbar_accel_tb__DOT__check__24__exp = 4U;
    __Vtask_crossbar_accel_tb__DOT__check__24__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__24__got 
         == __Vtask_crossbar_accel_tb__DOT__check__24__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__24__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__24__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__24__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__24__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__24__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__25__addr = 0x50000034U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__25__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__25__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__25__data;
    __Vtask_crossbar_accel_tb__DOT__check__26__tag = 
        std::string{"Y[1][0]=5"};
    __Vtask_crossbar_accel_tb__DOT__check__26__exp = 5U;
    __Vtask_crossbar_accel_tb__DOT__check__26__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__26__got 
         == __Vtask_crossbar_accel_tb__DOT__check__26__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__26__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__26__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__26__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__26__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__26__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__27__addr = 0x50000038U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__27__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__27__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__27__data;
    __Vtask_crossbar_accel_tb__DOT__check__28__tag = 
        std::string{"Y[1][1]=6"};
    __Vtask_crossbar_accel_tb__DOT__check__28__exp = 6U;
    __Vtask_crossbar_accel_tb__DOT__check__28__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__28__got 
         == __Vtask_crossbar_accel_tb__DOT__check__28__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__28__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__28__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__28__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__28__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__28__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__29__addr = 0x5000003cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__29__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__29__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__29__data;
    __Vtask_crossbar_accel_tb__DOT__check__30__tag = 
        std::string{"Y[1][2]=7"};
    __Vtask_crossbar_accel_tb__DOT__check__30__exp = 7U;
    __Vtask_crossbar_accel_tb__DOT__check__30__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__30__got 
         == __Vtask_crossbar_accel_tb__DOT__check__30__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__30__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__30__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__30__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__30__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__30__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__31__addr = 0x50000040U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__31__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__31__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__31__data;
    __Vtask_crossbar_accel_tb__DOT__check__32__tag = 
        std::string{"Y[1][3]=8"};
    __Vtask_crossbar_accel_tb__DOT__check__32__exp = 8U;
    __Vtask_crossbar_accel_tb__DOT__check__32__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__32__got 
         == __Vtask_crossbar_accel_tb__DOT__check__32__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__32__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__32__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__32__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__32__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__32__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__33__addr = 0x50000044U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__33__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__33__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__33__data;
    __Vtask_crossbar_accel_tb__DOT__check__34__tag = 
        std::string{"Y[2][0]=9"};
    __Vtask_crossbar_accel_tb__DOT__check__34__exp = 9U;
    __Vtask_crossbar_accel_tb__DOT__check__34__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__34__got 
         == __Vtask_crossbar_accel_tb__DOT__check__34__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__34__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__34__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__34__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__34__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__34__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__35__addr = 0x50000048U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__35__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__35__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__35__data;
    __Vtask_crossbar_accel_tb__DOT__check__36__tag = 
        std::string{"Y[2][1]=10"};
    __Vtask_crossbar_accel_tb__DOT__check__36__exp = 0xaU;
    __Vtask_crossbar_accel_tb__DOT__check__36__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__36__got 
         == __Vtask_crossbar_accel_tb__DOT__check__36__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__36__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__36__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__36__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__36__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__36__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__37__addr = 0x5000004cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__37__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__37__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__37__data;
    __Vtask_crossbar_accel_tb__DOT__check__38__tag = 
        std::string{"Y[2][2]=11"};
    __Vtask_crossbar_accel_tb__DOT__check__38__exp = 0xbU;
    __Vtask_crossbar_accel_tb__DOT__check__38__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__38__got 
         == __Vtask_crossbar_accel_tb__DOT__check__38__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__38__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__38__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__38__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__38__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__38__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__39__addr = 0x50000050U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__39__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__39__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__39__data;
    __Vtask_crossbar_accel_tb__DOT__check__40__tag = 
        std::string{"Y[2][3]=12"};
    __Vtask_crossbar_accel_tb__DOT__check__40__exp = 0xcU;
    __Vtask_crossbar_accel_tb__DOT__check__40__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__40__got 
         == __Vtask_crossbar_accel_tb__DOT__check__40__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__40__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__40__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__40__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__40__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__40__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__41__addr = 0x50000054U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__41__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__41__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__41__data;
    __Vtask_crossbar_accel_tb__DOT__check__42__tag = 
        std::string{"Y[3][0]=13"};
    __Vtask_crossbar_accel_tb__DOT__check__42__exp = 0xdU;
    __Vtask_crossbar_accel_tb__DOT__check__42__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__42__got 
         == __Vtask_crossbar_accel_tb__DOT__check__42__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__42__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__42__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__42__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__42__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__42__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__43__addr = 0x50000058U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__43__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__43__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__43__data;
    __Vtask_crossbar_accel_tb__DOT__check__44__tag = 
        std::string{"Y[3][1]=14"};
    __Vtask_crossbar_accel_tb__DOT__check__44__exp = 0xeU;
    __Vtask_crossbar_accel_tb__DOT__check__44__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__44__got 
         == __Vtask_crossbar_accel_tb__DOT__check__44__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__44__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__44__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__44__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__44__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__44__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__45__addr = 0x5000005cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__45__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__45__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__45__data;
    __Vtask_crossbar_accel_tb__DOT__check__46__tag = 
        std::string{"Y[3][2]=15"};
    __Vtask_crossbar_accel_tb__DOT__check__46__exp = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__check__46__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__46__got 
         == __Vtask_crossbar_accel_tb__DOT__check__46__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__46__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__46__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__46__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__46__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__46__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__47__addr = 0x50000060U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__47__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__47__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__47__data;
    __Vtask_crossbar_accel_tb__DOT__check__48__tag = 
        std::string{"Y[3][3]=16"};
    __Vtask_crossbar_accel_tb__DOT__check__48__exp = 0x10U;
    __Vtask_crossbar_accel_tb__DOT__check__48__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__48__got 
         == __Vtask_crossbar_accel_tb__DOT__check__48__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__48__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__48__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__48__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__48__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__48__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    VL_WRITEF("\n=== TEST 3: Full matmul through crossbar (A=W=[1..16]) ===\n");
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__data = 0x4030201U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__49__addr = 0x50000004U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__49__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__49__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__49__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__data = 0x8070605U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__50__addr = 0x50000008U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__50__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__50__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__50__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__data = 0xc0b0a09U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__51__addr = 0x5000000cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__51__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__51__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__51__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__data = 0x100f0e0dU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__52__addr = 0x50000010U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__52__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__52__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__52__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__data = 0x4030201U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__53__addr = 0x50000014U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__53__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__53__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__53__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__data = 0x8070605U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__54__addr = 0x50000018U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__54__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__54__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__54__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__data = 0xc0b0a09U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__55__addr = 0x5000001cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__55__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__55__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__55__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__data = 0x100f0e0dU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__56__addr = 0x50000020U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__56__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__56__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__56__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__data = 1U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__57__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__57__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__57__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__57__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__58__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__58__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__58__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__58__data;
    while ((1U & (~ (vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
                     >> 1U)))) {
        __Vtask_crossbar_accel_tb__DOT__axi_read__59__addr = 0x50000000U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           165);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__59__addr;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           167);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               168);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           170);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               172);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        __Vtask_crossbar_accel_tb__DOT__axi_read__59__data 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
            [0U];
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           174);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
        vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
            = __Vtask_crossbar_accel_tb__DOT__axi_read__59__data;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__60__addr = 0x50000024U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__60__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__60__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__60__data;
    __Vtask_crossbar_accel_tb__DOT__check__61__tag = 
        std::string{"Y[0][0]=90"};
    __Vtask_crossbar_accel_tb__DOT__check__61__exp = 0x5aU;
    __Vtask_crossbar_accel_tb__DOT__check__61__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__61__got 
         == __Vtask_crossbar_accel_tb__DOT__check__61__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__61__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__61__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__61__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__61__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__61__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__62__addr = 0x50000030U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__62__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__62__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__62__data;
    __Vtask_crossbar_accel_tb__DOT__check__63__tag = 
        std::string{"Y[0][3]=120"};
    __Vtask_crossbar_accel_tb__DOT__check__63__exp = 0x78U;
    __Vtask_crossbar_accel_tb__DOT__check__63__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__63__got 
         == __Vtask_crossbar_accel_tb__DOT__check__63__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__63__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__63__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__63__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__63__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__63__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__64__addr = 0x50000060U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__64__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__64__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__64__data;
    __Vtask_crossbar_accel_tb__DOT__check__65__tag = 
        std::string{"Y[3][3]=600"};
    __Vtask_crossbar_accel_tb__DOT__check__65__exp = 0x258U;
    __Vtask_crossbar_accel_tb__DOT__check__65__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__65__got 
         == __Vtask_crossbar_accel_tb__DOT__check__65__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__65__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__65__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__65__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__65__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__65__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    VL_WRITEF("\n=== TEST 4: Interleaved SRAM + accel access ===\n");
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__data = 0xabcdef01U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__66__addr = 0x100U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__66__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__66__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__66__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__67__addr = 0x100U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__67__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__67__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__67__data;
    __Vtask_crossbar_accel_tb__DOT__check__68__tag = 
        std::string{"SRAM sentinel after accel ops"};
    __Vtask_crossbar_accel_tb__DOT__check__68__exp = 0xabcdef01U;
    __Vtask_crossbar_accel_tb__DOT__check__68__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__68__got 
         == __Vtask_crossbar_accel_tb__DOT__check__68__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__68__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__68__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__68__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__68__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__68__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__69__addr = 0x50000004U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__69__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__69__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__69__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__70__addr = 0x50000008U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__70__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__70__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__70__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__71__addr = 0x5000000cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__71__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__71__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__71__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__72__addr = 0x50000010U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__72__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__72__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__72__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__73__addr = 0x50000014U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__73__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__73__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__73__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__74__addr = 0x50000018U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__74__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__74__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__74__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__75__addr = 0x5000001cU;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__75__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__75__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__75__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__data = 0x7f7f7f7fU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__76__addr = 0x50000020U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__76__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__76__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__76__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__strb = 0xfU;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__data = 1U;
    __Vtask_crossbar_accel_tb__DOT__axi_write__77__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       146);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awaddr = __Vtask_crossbar_accel_tb__DOT__axi_write__77__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_wdata = __Vtask_crossbar_accel_tb__DOT__axi_write__77__data;
    vlSelf->crossbar_accel_tb__DOT__m0_wstrb = __Vtask_crossbar_accel_tb__DOT__axi_write__77__strb;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       150);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           151);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       153);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_awvalid = 0U;
    vlSelf->crossbar_accel_tb__DOT__m0_wvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           156);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       157);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_bready = 0U;
    __Vtask_crossbar_accel_tb__DOT__axi_read__78__addr = 0x50000000U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__78__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__78__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__78__data;
    while ((1U & (~ (vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
                     >> 1U)))) {
        __Vtask_crossbar_accel_tb__DOT__axi_read__79__addr = 0x50000000U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           165);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__79__addr;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           167);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               168);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           170);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
        while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                      [0U]))) {
            co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                               nullptr, 
                                                               "@(posedge crossbar_accel_tb.clk)", 
                                                               "crossbar_accel_tb.sv", 
                                                               172);
            vlSelf->__Vm_traceActivity[2U] = 1U;
        }
        __Vtask_crossbar_accel_tb__DOT__axi_read__79__data 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
            [0U];
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           174);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
        vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
            = __Vtask_crossbar_accel_tb__DOT__axi_read__79__data;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__80__addr = 0x50000024U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__80__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__80__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__80__data;
    __Vtask_crossbar_accel_tb__DOT__check__81__tag = 
        std::string{"Y[0][0] max+ =64516"};
    __Vtask_crossbar_accel_tb__DOT__check__81__exp = 0xfc04U;
    __Vtask_crossbar_accel_tb__DOT__check__81__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__81__got 
         == __Vtask_crossbar_accel_tb__DOT__check__81__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__81__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__81__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__81__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__81__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__81__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__82__addr = 0x100U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       165);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_araddr = __Vtask_crossbar_accel_tb__DOT__axi_read__82__addr;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       167);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           168);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       170);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_arvalid = 0U;
    while ((1U & (~ vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                  [0U]))) {
        co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge crossbar_accel_tb.clk)", 
                                                           "crossbar_accel_tb.sv", 
                                                           172);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    __Vtask_crossbar_accel_tb__DOT__axi_read__82__data 
        = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
        [0U];
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       174);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->crossbar_accel_tb__DOT__m0_rready = 0U;
    vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd 
        = __Vtask_crossbar_accel_tb__DOT__axi_read__82__data;
    __Vtask_crossbar_accel_tb__DOT__check__83__tag = 
        std::string{"SRAM sentinel unchanged after max+ matmul"};
    __Vtask_crossbar_accel_tb__DOT__check__83__exp = 0xabcdef01U;
    __Vtask_crossbar_accel_tb__DOT__check__83__got 
        = vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
    if ((__Vtask_crossbar_accel_tb__DOT__check__83__got 
         == __Vtask_crossbar_accel_tb__DOT__check__83__exp)) {
        VL_WRITEF("[PASS] %@  got=0x%08x\n",-1,&(__Vtask_crossbar_accel_tb__DOT__check__83__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__83__got);
    } else {
        VL_WRITEF("[FAIL] %@  exp=0x%08x  got=0x%08x\n",
                  -1,&(__Vtask_crossbar_accel_tb__DOT__check__83__tag),
                  32,__Vtask_crossbar_accel_tb__DOT__check__83__exp,
                  32,__Vtask_crossbar_accel_tb__DOT__check__83__got);
        vlSelf->crossbar_accel_tb__DOT__error_count 
            = ((IData)(1U) + vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       304);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       304);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       304);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       304);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_h5c6c16d3__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge crossbar_accel_tb.clk)", 
                                                       "crossbar_accel_tb.sv", 
                                                       304);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    if ((0U == vlSelf->crossbar_accel_tb__DOT__error_count)) {
        VL_WRITEF("\n*** INTEGRATION: ALL TESTS PASSED (0 errors) ***\n");
    } else {
        VL_WRITEF("\n*** INTEGRATION: %0d ERRORS ***\n",
                  32,vlSelf->crossbar_accel_tb__DOT__error_count);
    }
    VL_FINISH_MT("crossbar_accel_tb.sv", 309, "");
    vlSelf->__Vm_traceActivity[2U] = 1U;
}

VL_INLINE_OPT VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__2(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__2\n"); );
    // Body
    co_await vlSelf->__VdlySched.delay(0x3b9aca00ULL, 
                                       nullptr, "crossbar_accel_tb.sv", 
                                       313);
    VL_WRITEF("[TIMEOUT] Integration test exceeded 1ms\n");
    VL_FINISH_MT("crossbar_accel_tb.sv", 315, "");
}

VL_INLINE_OPT VlCoroutine Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__3(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_initial__TOP__Vtiming__3\n"); );
    // Body
    while (1U) {
        co_await vlSelf->__VdlySched.delay(0x1388ULL, 
                                           nullptr, 
                                           "crossbar_accel_tb.sv", 
                                           11);
        vlSelf->crossbar_accel_tb__DOT__clk = (1U & 
                                               (~ (IData)(vlSelf->crossbar_accel_tb__DOT__clk)));
    }
}

VL_INLINE_OPT void Vcrossbar_accel_tb___024root___act_sequent__TOP__0(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___act_sequent__TOP__0\n"); );
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
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_araddr;
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

void Vcrossbar_accel_tb___024root___eval_act(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___eval_act\n"); );
    // Body
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        Vcrossbar_accel_tb___024root___act_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
    }
}

VL_INLINE_OPT void Vcrossbar_accel_tb___024root___nba_sequent__TOP__0(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v22;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v22 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v32;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v32 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v22;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v22 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v32;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v32 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v0;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v0;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v0;
    __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s0_bvalid;
    __Vdly__crossbar_accel_tb__DOT__s0_bvalid = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v1;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v1;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v1;
    __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v2;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v2;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v2;
    __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v3;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v3;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v3;
    __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s0_rvalid;
    __Vdly__crossbar_accel_tb__DOT__s0_rvalid = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v0;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v0;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v0;
    __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s1_bvalid;
    __Vdly__crossbar_accel_tb__DOT__s1_bvalid = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v1;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v1;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v1;
    __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v2;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v2;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v2;
    __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0;
    SData/*13:0*/ __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v3;
    __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0;
    CData/*4:0*/ __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v3;
    __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v3;
    __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s1_rvalid;
    __Vdly__crossbar_accel_tb__DOT__s1_rvalid = 0;
    CData/*1:0*/ __Vdly__crossbar_accel_tb__DOT__accel__DOT__state;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__state = 0;
    CData/*2:0*/ __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v2;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v2 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v3;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v3 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v5;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v5 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v6;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v6 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v7;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v7 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v9;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v9 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v10;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v10 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v11;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v11 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v13;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v13 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v14;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v14 = 0;
    IData/*31:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v15;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v15 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s2_bvalid;
    __Vdly__crossbar_accel_tb__DOT__s2_bvalid = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14 = 0;
    CData/*7:0*/ __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15;
    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v16;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v16 = 0;
    CData/*0:0*/ __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v16;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v16 = 0;
    CData/*0:0*/ __Vdly__crossbar_accel_tb__DOT__s2_rvalid;
    __Vdly__crossbar_accel_tb__DOT__s2_rvalid = 0;
    // Body
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v16 = 0U;
    __Vdly__crossbar_accel_tb__DOT__s2_rvalid = vlSelf->crossbar_accel_tb__DOT__s2_rvalid;
    __Vdly__crossbar_accel_tb__DOT__s1_rvalid = vlSelf->crossbar_accel_tb__DOT__s1_rvalid;
    __Vdly__crossbar_accel_tb__DOT__s0_rvalid = vlSelf->crossbar_accel_tb__DOT__s0_rvalid;
    __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending 
        = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending 
        = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__s1_bvalid = vlSelf->crossbar_accel_tb__DOT__s1_bvalid;
    __Vdly__crossbar_accel_tb__DOT__s0_bvalid = vlSelf->crossbar_accel_tb__DOT__s0_bvalid;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v22 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v32 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v22 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v32 = 0U;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending 
        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending;
    __Vdly__crossbar_accel_tb__DOT__s2_bvalid = vlSelf->crossbar_accel_tb__DOT__s2_bvalid;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v16 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8 = 0U;
    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12 = 0U;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc 
        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__state 
        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__state;
    __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r 
        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r;
    if (vlSelf->crossbar_accel_tb__DOT__rst_n) {
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [2U]) {
            __Vdly__crossbar_accel_tb__DOT__s2_rvalid = 1U;
        } else if (((IData)(vlSelf->crossbar_accel_tb__DOT__s2_rvalid) 
                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                    [2U])) {
            __Vdly__crossbar_accel_tb__DOT__s2_rvalid = 0U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [1U]) {
            __Vdly__crossbar_accel_tb__DOT__s1_rvalid = 1U;
        } else if (((IData)(vlSelf->crossbar_accel_tb__DOT__s1_rvalid) 
                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                    [1U])) {
            __Vdly__crossbar_accel_tb__DOT__s1_rvalid = 0U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [0U]) {
            __Vdly__crossbar_accel_tb__DOT__s0_rvalid = 1U;
        } else if (((IData)(vlSelf->crossbar_accel_tb__DOT__s0_rvalid) 
                    & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                    [0U])) {
            __Vdly__crossbar_accel_tb__DOT__s0_rvalid = 0U;
        }
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [1U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [1U])) {
            __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending) {
            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 
                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r);
                __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 = 0U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v0 
                    = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r;
            }
            __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending = 0U;
            __Vdly__crossbar_accel_tb__DOT__s1_bvalid = 1U;
            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 
                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r 
                                >> 8U));
                __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 = 8U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v1 
                    = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r;
            }
            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 
                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r 
                                >> 0x10U));
                __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v2 
                    = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r;
            }
            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 
                    = (vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r 
                       >> 0x18U);
                __Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v3 
                    = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r;
            }
        }
        if (((IData)(vlSelf->crossbar_accel_tb__DOT__s1_bvalid) 
             & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
             [1U])) {
            __Vdly__crossbar_accel_tb__DOT__s1_bvalid = 0U;
        }
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [0U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [0U])) {
            __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending) {
            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 
                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r);
                __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 = 0U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v0 
                    = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r;
            }
            __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending = 0U;
            __Vdly__crossbar_accel_tb__DOT__s0_bvalid = 1U;
            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 
                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r 
                                >> 8U));
                __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 = 8U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v1 
                    = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r;
            }
            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 
                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r 
                                >> 0x10U));
                __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v2 
                    = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r;
            }
            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r))) {
                __Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 
                    = (vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r 
                       >> 0x18U);
                __Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 1U;
                __Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v3 
                    = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r;
            }
        }
        if (((IData)(vlSelf->crossbar_accel_tb__DOT__s0_bvalid) 
             & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
             [0U])) {
            __Vdly__crossbar_accel_tb__DOT__s0_bvalid = 0U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [0U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                 [0U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                          [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                         [0U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v0 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [0U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [0U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8 = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [1U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                 [1U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                          [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                         [1U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v11 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [1U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [1U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18 = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [2U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
                 [2U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                          [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                         [2U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v22 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [2U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last
                    [2U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                 [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                        [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
                    [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28 = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
            [0U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                 [0U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                          [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                         [0U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v0 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [0U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [0U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [1U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8 = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
            [1U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                 [1U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                          [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                         [1U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v11 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [1U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [1U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18 = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy
            [2U]) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid
                 [2U] & ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                          [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready
                         [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                         [2U]]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v22 = 1U;
            }
        } else if ((0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [2U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22 = 1U;
            }
        } else if ((1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last
                    [2U])) {
            if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                 [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                         [2U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [0U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24 = 1U;
            } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                        [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                                [1U]))) {
                __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25 = 1U;
            }
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [0U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [1U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [1U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27 = 1U;
        } else if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
                    [2U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec
                            [2U]))) {
            __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28 = 1U;
        }
        if ((0U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state))) {
            if (vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r) {
                __Vdly__crossbar_accel_tb__DOT__accel__DOT__state = 1U;
                __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc = 0U;
                __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r = 0U;
            }
        } else if ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state))) {
            __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc 
                = (7U & ((IData)(1U) + (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc)));
            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))) {
                if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))) {
                    if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))) {
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30;
                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0 = 1U;
                        __Vdly__crossbar_accel_tb__DOT__accel__DOT__state = 2U;
                        __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r = 1U;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31;
                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1 = 1U;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v2 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v3 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33;
                    } else {
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30;
                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4 = 1U;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v5 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v6 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32;
                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v7 
                            = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33;
                    }
                } else if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))) {
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30;
                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8 = 1U;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v9 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v10 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v11 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33;
                } else {
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30;
                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12 = 1U;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v13 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v14 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32;
                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v15 
                        = vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33;
                }
            }
        } else if ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state))) {
            if (((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r) 
                 & (~ (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r)))) {
                __Vdly__crossbar_accel_tb__DOT__accel__DOT__state = 1U;
                __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc = 0U;
            }
        }
    } else {
        __Vdly__crossbar_accel_tb__DOT__s2_rvalid = 0U;
        __Vdly__crossbar_accel_tb__DOT__s1_rvalid = 0U;
        __Vdly__crossbar_accel_tb__DOT__s0_rvalid = 0U;
        __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending = 0U;
        __Vdly__crossbar_accel_tb__DOT__s1_bvalid = 0U;
        __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending = 0U;
        __Vdly__crossbar_accel_tb__DOT__s0_bvalid = 0U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10 = 1U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21 = 1U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v32 = 1U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10 = 1U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21 = 1U;
        __Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v32 = 1U;
        __Vdly__crossbar_accel_tb__DOT__accel__DOT__state = 0U;
        __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc = 0U;
        __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r = 0U;
    }
    if ((1U & (~ (IData)(vlSelf->crossbar_accel_tb__DOT__rst_n)))) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 4U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__i = 4U;
        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v16 = 1U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__rst_n) {
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [2U]) {
            vlSelf->crossbar_accel_tb__DOT__s2_rdata 
                = vlSelf->crossbar_accel_tb__DOT__accel__DOT__rdata_comb;
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [1U]) {
            vlSelf->crossbar_accel_tb__DOT__s1_rdata 
                = vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem
                [(0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                             [1U] >> 2U))];
        }
        if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
            [0U]) {
            vlSelf->crossbar_accel_tb__DOT__s0_rdata 
                = vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem
                [(0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                             [0U] >> 2U))];
        }
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [1U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [1U])) {
            vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                [1U];
            vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                [1U];
            vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r 
                = (0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                              [1U] >> 2U));
        }
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [0U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [0U])) {
            vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                [0U];
            vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                [0U];
            vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r 
                = (0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                              [0U] >> 2U));
        }
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product)));
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [2U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [2U])) {
            __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending = 1U;
        }
        if (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending) {
            __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending = 0U;
            __Vdly__crossbar_accel_tb__DOT__s2_bvalid = 1U;
            if ((1U & (~ ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r) 
                          >> 5U)))) {
                if ((1U & (~ ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r) 
                              >> 4U)))) {
                    if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                        if ((1U & (~ ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r) 
                                      >> 2U)))) {
                            if ((1U & (~ ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r) 
                                          >> 1U)))) {
                                if ((1U & (~ (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r)))) {
                                    if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0 
                                            = (0xffU 
                                               & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0 = 1U;
                                    }
                                    if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1 
                                            = (0xffU 
                                               & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                  >> 8U));
                                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1 = 1U;
                                    }
                                    if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2 
                                            = (0xffU 
                                               & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                  >> 0x10U));
                                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2 = 1U;
                                    }
                                    if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                        __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3 
                                            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                               >> 0x18U);
                                        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3 = 1U;
                                    }
                                }
                            }
                        }
                    } else if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                        if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                                if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4 
                                        = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5 
                                        = (0xffU & 
                                           (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6 
                                        = (0xffU & 
                                           (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7 
                                        = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7 = 1U;
                                }
                            } else {
                                if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8 
                                        = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8 = 1U;
                                }
                                if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9 
                                        = (0xffU & 
                                           (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 8U));
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9 = 1U;
                                }
                                if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10 
                                        = (0xffU & 
                                           (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 0x10U));
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10 = 1U;
                                }
                                if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                    __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11 
                                        = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                           >> 0x18U);
                                    __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11 = 1U;
                                }
                            }
                        } else if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12 
                                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15 
                                    = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0 
                                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3 
                                    = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3 = 1U;
                            }
                        }
                    } else if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4 
                                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7 
                                    = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7 = 1U;
                            }
                        } else {
                            if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8 
                                    = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8 = 1U;
                            }
                            if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 8U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9 = 1U;
                            }
                            if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10 
                                    = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                                >> 0x10U));
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10 = 1U;
                            }
                            if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                                __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11 
                                    = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                       >> 0x18U);
                                __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11 = 1U;
                            }
                        }
                    } else if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r))) {
                        if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                            __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12 
                                = (0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r);
                            __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12 = 1U;
                        }
                        if ((2U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                            __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13 
                                = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 8U));
                            __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13 = 1U;
                        }
                        if ((4U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                            __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14 
                                = (0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                            >> 0x10U));
                            __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14 = 1U;
                        }
                        if ((8U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                            __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15 
                                = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                                   >> 0x18U);
                            __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15 = 1U;
                        }
                    } else if ((1U & (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r))) {
                        if ((1U & vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r)) {
                            vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r = 1U;
                            __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r = 0U;
                        } else {
                            vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r = 0U;
                        }
                    }
                }
            }
        }
        if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
             [2U] & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
             [2U])) {
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r 
                = (0x3fU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                            [2U] >> 2U));
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                [2U];
            vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r 
                = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                [2U];
        }
        if (((IData)(vlSelf->crossbar_accel_tb__DOT__s2_bvalid) 
             & vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
             [2U])) {
            __Vdly__crossbar_accel_tb__DOT__s2_bvalid = 0U;
        }
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13 
            = (vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03 
               + (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product) 
                                     >> 0xfU)))) << 0x10U) 
                  | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product)));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00 
            = (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01 
            = (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02 
            = (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product));
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03 
            = (((- (IData)((1U & ((IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product) 
                                  >> 0xfU)))) << 0x10U) 
               | (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product));
    } else {
        vlSelf->crossbar_accel_tb__DOT__s2_rdata = 0U;
        vlSelf->crossbar_accel_tb__DOT__s1_rdata = 0U;
        vlSelf->crossbar_accel_tb__DOT__s0_rdata = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33 = 0U;
        __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending = 0U;
        __Vdly__crossbar_accel_tb__DOT__s2_bvalid = 0U;
        __Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v16 = 1U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02 = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03 = 0U;
    }
    vlSelf->crossbar_accel_tb__DOT__s2_rvalid = __Vdly__crossbar_accel_tb__DOT__s2_rvalid;
    vlSelf->crossbar_accel_tb__DOT__s1_rvalid = __Vdly__crossbar_accel_tb__DOT__s1_rvalid;
    vlSelf->crossbar_accel_tb__DOT__s0_rvalid = __Vdly__crossbar_accel_tb__DOT__s0_rvalid;
    vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending 
        = __Vdly__crossbar_accel_tb__DOT__sram1__DOT__wr_pending;
    vlSelf->crossbar_accel_tb__DOT__s1_bvalid = __Vdly__crossbar_accel_tb__DOT__s1_bvalid;
    vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending 
        = __Vdly__crossbar_accel_tb__DOT__sram0__DOT__wr_pending;
    vlSelf->crossbar_accel_tb__DOT__s0_bvalid = __Vdly__crossbar_accel_tb__DOT__s0_bvalid;
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v1) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v2) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v3) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v4) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v5) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v6) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v7) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v8) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v12) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v13) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v14) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v15) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v16) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v17) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v18) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v20) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v23) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v24) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v25) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v26) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v27) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_grant__v28) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__rd_busy__v32) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 1U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 2U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v0) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v1) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v2) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v3) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v4) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v5) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v6) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v7) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v8) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v10) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v11) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v12) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v13) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v14) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v15) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v16) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v17) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v18) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v20) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v21) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v22) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v23) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v24) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v25) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v26) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v27) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_grant__v28) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 1U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__xbar__DOT__wr_busy__v32) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2U] = 2U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2U] = 0U;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v0;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v1;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v2;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v3;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v4;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v5;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v6;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v7;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v8;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v9;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v10;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v11;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v12;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v13;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v14;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__y_reg__v15;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__y_reg__v16) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[0U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[1U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[2U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg[3U][3U] = 0U;
    }
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__state 
        = __Vdly__crossbar_accel_tb__DOT__accel__DOT__state;
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc 
        = __Vdly__crossbar_accel_tb__DOT__accel__DOT__cyc;
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v0) {
        vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v0))) 
                & vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v0]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v0) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v0))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v1) {
        vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v1))) 
                & vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v1]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v1) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v1))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v2) {
        vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v2))) 
                & vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v2]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v2) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v2))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram1__DOT__mem__v3) {
        vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v3))) 
                & vlSelf->crossbar_accel_tb__DOT__sram1__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram1__DOT__mem__v3]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram1__DOT__mem__v3) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram1__DOT__mem__v3))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v0) {
        vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v0))) 
                & vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v0]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v0) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v0))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v1) {
        vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v1))) 
                & vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v1]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v1) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v1))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v2) {
        vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v2))) 
                & vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v2]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v2) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v2))));
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__sram0__DOT__mem__v3) {
        vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem[__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v3))) 
                & vlSelf->crossbar_accel_tb__DOT__sram0__DOT__mem
                [__Vdlyvdim0__crossbar_accel_tb__DOT__sram0__DOT__mem__v3]) 
               | (0xffffffffULL & ((IData)(__Vdlyvval__crossbar_accel_tb__DOT__sram0__DOT__mem__v3) 
                                   << (IData)(__Vdlyvlsb__crossbar_accel_tb__DOT__sram0__DOT__mem__v3))));
    }
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[2U] 
        = vlSelf->crossbar_accel_tb__DOT__s2_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_rvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_bvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_bvalid;
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
               [2U]);
    }
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
            [1U];
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
               [2U]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
               [2U] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1U] 
            = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                        [2U])) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
               [2U]);
    }
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
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[2U] 
        = vlSelf->crossbar_accel_tb__DOT__s2_rdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[1U] 
        = vlSelf->crossbar_accel_tb__DOT__s1_rdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[0U] 
        = vlSelf->crossbar_accel_tb__DOT__s0_rdata;
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
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1U] 
        = ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
            [0U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                    [0U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
           [0U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                    [1U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                            [1U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                   [1U] : ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
                            [2U] & (1U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
                           [2U] : 0U)));
    if ((vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
         [0U] & (2U == vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
            [0U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid
            [1U];
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata
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
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending 
        = __Vdly__crossbar_accel_tb__DOT__accel__DOT__wr_pending;
    vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r 
        = __Vdly__crossbar_accel_tb__DOT__accel__DOT__done_r;
    vlSelf->crossbar_accel_tb__DOT__s2_bvalid = __Vdly__crossbar_accel_tb__DOT__s2_bvalid;
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v0;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v1;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v2;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v3;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v4;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v5;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v6;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v7;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v8;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v9;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v10;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v11;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v12;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v13;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v14;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__w_reg__v15;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v0;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v1;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v2;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v3;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v4;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v5;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v6;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v7;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v8;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v9;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v10;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v11;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][0U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v12;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][1U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v13;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][2U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v14;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][3U] 
            = __Vdlyvval__crossbar_accel_tb__DOT__accel__DOT__a_reg__v15;
    }
    if (__Vdlyvset__crossbar_accel_tb__DOT__accel__DOT__w_reg__v16) {
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[0U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[1U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[2U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg[3U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[0U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[1U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[2U][3U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg[3U][3U] = 0U;
    }
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
}

VL_INLINE_OPT void Vcrossbar_accel_tb___024root___nba_sequent__TOP__1(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_awaddr;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wdata;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wstrb;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_wvalid;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_araddr;
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
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_rready;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_arvalid;
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
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_bready;
    vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[0U] 
        = vlSelf->crossbar_accel_tb__DOT__m0_awvalid;
}

VL_INLINE_OPT void Vcrossbar_accel_tb___024root___nba_comb__TOP__0(Vcrossbar_accel_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root___nba_comb__TOP__0\n"); );
    // Body
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0U] = 0U;
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1U] = 0U;
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
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [0U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [0U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [0U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [1U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [1U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [1U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1U] = 0U;
    }
    if (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy
        [2U]) {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) ? vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]] : 0U);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
                [2U]) && vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid
               [vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant
               [2U]]);
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2U] 
            = vlSelf->crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
    } else {
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2U] = 0U;
        vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2U] = 0U;
    }
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
