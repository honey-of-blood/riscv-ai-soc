// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsoc_tb.h for the primary calling header

#include "Vsoc_tb__pch.h"
#include "Vsoc_tb___024root.h"

VL_ATTR_COLD void Vsoc_tb___024root___eval_static__TOP(Vsoc_tb___024root* vlSelf);

VL_ATTR_COLD void Vsoc_tb___024root___eval_static(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_static\n"); );
    // Body
    Vsoc_tb___024root___eval_static__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[4U] = 1U;
    vlSelf->__Vm_traceActivity[3U] = 1U;
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

VL_ATTR_COLD void Vsoc_tb___024root___eval_static__TOP(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_static__TOP\n"); );
    // Body
    vlSelf->soc_tb__DOT__error_count = 0U;
    vlSelf->soc_tb__DOT__y00_valid = 0U;
    vlSelf->soc_tb__DOT__y33_valid = 0U;
}

VL_ATTR_COLD void Vsoc_tb___024root___eval_initial__TOP(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_initial__TOP\n"); );
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    // Body
    vlSelf->soc_tb__DOT__clk = 0U;
    vlSelf->soc_tb__DOT__done_flag = 0U;
    __Vtemp_1[0U] = 0x2e686578U;
    __Vtemp_1[1U] = 0x77617265U;
    __Vtemp_1[2U] = 0x6669726dU;
    VL_READMEM_N(true, 32, 512, 0, VL_CVT_PACK_STR_NW(3, __Vtemp_1)
                 ,  &(vlSelf->soc_tb__DOT__dut__DOT__u_irom__DOT__mem)
                 , 0, ~0ULL);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s = 3U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[0U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[1U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[2U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[0U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[1U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[2U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[0U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[2U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[0U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[1U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[2U] = 1U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[0U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[1U] = 0U;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[2U] = 0U;
}

VL_ATTR_COLD void Vsoc_tb___024root___eval_final(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__stl(Vsoc_tb___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vsoc_tb___024root___eval_phase__stl(Vsoc_tb___024root* vlSelf);

VL_ATTR_COLD void Vsoc_tb___024root___eval_settle(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_settle\n"); );
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
            Vsoc_tb___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("soc_tb.sv", 12, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vsoc_tb___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__stl(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

extern const VlUnpacked<CData/*3:0*/, 512> Vsoc_tb__ConstPool__TABLE_hc47a5df6_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h03c3adda_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h7ca8bf9e_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_ha96ed2bf_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_hd2a3c541_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_h101bb02f_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_he4685dc5_0;
extern const VlUnpacked<CData/*0:0*/, 128> Vsoc_tb__ConstPool__TABLE_hbd434190_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vsoc_tb__ConstPool__TABLE_h4e53dcde_0;

VL_ATTR_COLD void Vsoc_tb___024root___stl_sequent__TOP__0(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___stl_sequent__TOP__0\n"); );
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
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we 
        = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)) 
           & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half 
        = (0xffffU & ((2U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m)
                       ? (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                          >> 0x10U) : vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata));
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [1U];
    } else {
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
               [2U] : 0U);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [1U];
    } else {
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
               [2U] : 0U);
    }
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
               [2U]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
               [2U] : 0U);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i 
        = (((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                        >> 0x1fU))) << 0xcU) | (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                >> 0x14U));
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
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[0U] 
        = (1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[0U] 
        = (1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[0U] 
        = (2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[0U] 
        = (3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[0U] 
        = (4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                            [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                                    [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                           [2U])));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
            [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                            [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                                    [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
                           [2U])));
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
         [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [1U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
            [1U];
    } else {
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp
               [2U] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid
               [2U]);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_rdata;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
                           [2U] : 0U)));
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [0U];
    } else if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [1U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
            [1U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
            [1U];
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
               [2U]);
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
             [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                     [2U]))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1U] 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                [2U];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
                [2U];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1U] = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1U] = 0U;
        }
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[1U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[2U] 
        = vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid;
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (0U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                           [2U])));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1U] 
        = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
            [0U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                    [0U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
           [0U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                    [1U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                            [1U])) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                   [1U] : ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                            [2U] & (1U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                                    [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
                           [2U])));
    if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
         [0U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                 [0U]))) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready
            [0U];
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
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
        if ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
             [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                     [2U]))) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2U] 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp
                [2U];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2U] 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata
                [2U];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2U] = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2U] = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2U] 
            = ((vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
                [2U] & (2U == vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                        [2U])) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid
               [2U]);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e) 
           & ((0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e)) 
              & (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e) 
                  == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                               >> 0xfU))) | ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e) 
                                             == (0x1fU 
                                                 & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                    >> 0x14U))))));
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[0U] 
        = vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r;
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
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val 
        = ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m
                : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m));
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data 
        = ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w
            : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w
                : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w))
                    ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w
                    : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w)));
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_hd3a8a00d__0 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m) 
           & (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m)));
    soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fwd__DOT____VdfgTmp_h9767fbc2__0 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w) 
           & (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w)));
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
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [0U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [0U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [1U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [1U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy
        [2U]) {
        if ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
             [2U])) {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 
                = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb
                [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant
                [2U]];
        } else {
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = 0U;
            vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = 0U;
        }
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0;
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[2U] = 0U;
    }
    if (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy
        [0U]) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [0U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [0U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0U] = 0U;
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [1U]) && vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [1U]]);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [1U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [1U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1U] = 0U;
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
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 
            = ((2U >= vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
                [2U]) ? vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr
               [vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant
               [2U]] : 0U);
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2U] 
            = vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0;
    } else {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[2U] = 0U;
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2U] = 0U;
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if 
        = ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use) 
           | (0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)));
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
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex 
        = ((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state)) 
           & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use) 
              | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken)));
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

VL_ATTR_COLD void Vsoc_tb___024root___eval_stl(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vsoc_tb___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[4U] = 1U;
        vlSelf->__Vm_traceActivity[3U] = 1U;
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vsoc_tb___024root___eval_triggers__stl(Vsoc_tb___024root* vlSelf);

VL_ATTR_COLD bool Vsoc_tb___024root___eval_phase__stl(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vsoc_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vsoc_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__act(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge soc_tb.clk)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge soc_tb.clk or negedge soc_tb.rst_n)\n");
    }
    if ((4ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsoc_tb___024root___dump_triggers__nba(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge soc_tb.clk)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge soc_tb.clk or negedge soc_tb.rst_n)\n");
    }
    if ((4ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 2 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vsoc_tb___024root___ctor_var_reset(Vsoc_tb___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->soc_tb__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__error_count = 0;
    vlSelf->soc_tb__DOT__y00_captured = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__y33_captured = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__y00_valid = 0;
    vlSelf->soc_tb__DOT__y33_valid = 0;
    vlSelf->soc_tb__DOT__done_flag = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__dmem_be = VL_RAND_RESET_I(4);
    vlSelf->soc_tb__DOT__dut__DOT__s0_rdata = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__s1_rdata = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__s2_rdata = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_irom__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m = VL_RAND_RESET_I(5);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w = VL_RAND_RESET_I(5);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_d = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_d = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_d = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e = VL_RAND_RESET_I(4);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e = VL_RAND_RESET_I(3);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e = VL_RAND_RESET_I(5);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e = VL_RAND_RESET_I(5);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e = VL_RAND_RESET_I(5);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m = VL_RAND_RESET_I(3);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc_next = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 31; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT____Vlvbound_haf05b89f__0 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte = VL_RAND_RESET_I(8);
    vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[__Vi0] = VL_RAND_RESET_I(4);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[__Vi0] = VL_RAND_RESET_I(4);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[__Vi0] = VL_RAND_RESET_I(32);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[__Vi0] = VL_RAND_RESET_I(2);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[__Vi0] = VL_RAND_RESET_I(1);
    }
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[__Vi0] = VL_RAND_RESET_I(2);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h626fae99__0 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h5c2f4fa1__0 = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h88a8ba88__0 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hbcf1b5af__0 = VL_RAND_RESET_I(4);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h8d615ae3__0 = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h98abfbc2__0 = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_hc59dc3bb__0 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h826c049a__0 = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT____Vlvbound_h746f52ea__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r = VL_RAND_RESET_I(14);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 16384; ++__Vi0) {
        vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r = VL_RAND_RESET_I(14);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(8);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg[__Vi0][__Vi1] = VL_RAND_RESET_I(32);
        }
    }
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc = VL_RAND_RESET_I(3);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending = VL_RAND_RESET_I(1);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r = VL_RAND_RESET_I(6);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r = VL_RAND_RESET_I(4);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__rdata_comb = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j = 0;
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33 = VL_RAND_RESET_I(32);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s = VL_RAND_RESET_I(8);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product = VL_RAND_RESET_I(16);
    vlSelf->__Vdly__soc_tb__DOT__dut__DOT__u_adapter__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__soc_tb__DOT__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 5; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
