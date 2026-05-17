// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vsoc_tb__Syms.h"


void Vsoc_tb___024root__trace_chg_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vsoc_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_chg_0\n"); );
    // Init
    Vsoc_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_tb___024root*>(voidSelf);
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vsoc_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vsoc_tb___024root__trace_chg_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[0]));
        bufp->chgBit(oldp+1,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[1]));
        bufp->chgBit(oldp+2,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[2]));
        bufp->chgBit(oldp+3,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[0]));
        bufp->chgBit(oldp+4,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[1]));
        bufp->chgBit(oldp+5,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[2]));
        bufp->chgCData(oldp+6,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[0]),2);
        bufp->chgCData(oldp+7,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[1]),2);
        bufp->chgCData(oldp+8,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[2]),2);
        bufp->chgBit(oldp+9,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[0]));
        bufp->chgBit(oldp+10,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[1]));
        bufp->chgBit(oldp+11,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[2]));
        bufp->chgCData(oldp+12,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[0]),2);
        bufp->chgCData(oldp+13,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[1]),2);
        bufp->chgCData(oldp+14,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[2]),2);
        bufp->chgIData(oldp+15,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s),32);
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[4U]))) {
        bufp->chgIData(oldp+16,(vlSelf->soc_tb__DOT__dut__DOT__u_irom__DOT__mem
                                [(0x1ffU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                                            >> 2U))]),32);
        bufp->chgIData(oldp+17,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[0]),32);
        bufp->chgIData(oldp+18,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[1]),32);
        bufp->chgIData(oldp+19,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[2]),32);
        bufp->chgBit(oldp+20,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[0]));
        bufp->chgBit(oldp+21,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[1]));
        bufp->chgBit(oldp+22,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[2]));
        bufp->chgIData(oldp+23,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[0]),32);
        bufp->chgIData(oldp+24,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[1]),32);
        bufp->chgIData(oldp+25,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[2]),32);
        bufp->chgCData(oldp+26,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[0]),4);
        bufp->chgCData(oldp+27,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[1]),4);
        bufp->chgCData(oldp+28,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[2]),4);
        bufp->chgBit(oldp+29,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[0]));
        bufp->chgBit(oldp+30,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[1]));
        bufp->chgBit(oldp+31,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[2]));
        bufp->chgBit(oldp+32,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[0]));
        bufp->chgBit(oldp+33,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[1]));
        bufp->chgBit(oldp+34,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[2]));
        bufp->chgIData(oldp+35,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[0]),32);
        bufp->chgIData(oldp+36,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[1]),32);
        bufp->chgIData(oldp+37,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[2]),32);
        bufp->chgBit(oldp+38,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[0]));
        bufp->chgBit(oldp+39,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[1]));
        bufp->chgBit(oldp+40,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[2]));
        bufp->chgBit(oldp+41,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[0]));
        bufp->chgBit(oldp+42,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[1]));
        bufp->chgBit(oldp+43,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[2]));
        bufp->chgCData(oldp+44,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0]),2);
        bufp->chgCData(oldp+45,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[1]),2);
        bufp->chgCData(oldp+46,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[2]),2);
        bufp->chgCData(oldp+47,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0]),2);
        bufp->chgCData(oldp+48,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[1]),2);
        bufp->chgCData(oldp+49,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[2]),2);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgCData(oldp+50,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                                [0U]),2);
        bufp->chgCData(oldp+51,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                                [0U]),2);
        bufp->chgCData(oldp+52,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                                [1U]),2);
        bufp->chgCData(oldp+53,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                                [1U]),2);
        bufp->chgCData(oldp+54,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                                [2U]),2);
        bufp->chgCData(oldp+55,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                                [2U]),2);
        bufp->chgIData(oldp+56,(vlSelf->soc_tb__DOT__dut__DOT__s0_rdata),32);
        bufp->chgBit(oldp+57,(vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid));
        bufp->chgBit(oldp+58,(vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid));
        bufp->chgIData(oldp+59,(vlSelf->soc_tb__DOT__dut__DOT__s1_rdata),32);
        bufp->chgBit(oldp+60,(vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid));
        bufp->chgBit(oldp+61,(vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid));
        bufp->chgIData(oldp+62,(vlSelf->soc_tb__DOT__dut__DOT__s2_rdata),32);
        bufp->chgBit(oldp+63,(vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid));
        bufp->chgBit(oldp+64,(vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid));
        bufp->chgCData(oldp+65,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [0U][0U]),8);
        bufp->chgCData(oldp+66,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [0U][1U]),8);
        bufp->chgCData(oldp+67,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [0U][2U]),8);
        bufp->chgCData(oldp+68,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [0U][3U]),8);
        bufp->chgCData(oldp+69,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [1U][0U]),8);
        bufp->chgCData(oldp+70,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [1U][1U]),8);
        bufp->chgCData(oldp+71,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [1U][2U]),8);
        bufp->chgCData(oldp+72,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [1U][3U]),8);
        bufp->chgCData(oldp+73,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [2U][0U]),8);
        bufp->chgCData(oldp+74,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [2U][1U]),8);
        bufp->chgCData(oldp+75,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [2U][2U]),8);
        bufp->chgCData(oldp+76,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [2U][3U]),8);
        bufp->chgCData(oldp+77,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [3U][0U]),8);
        bufp->chgCData(oldp+78,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [3U][1U]),8);
        bufp->chgCData(oldp+79,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [3U][2U]),8);
        bufp->chgCData(oldp+80,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                                [3U][3U]),8);
        bufp->chgCData(oldp+81,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [0U][0U]),8);
        bufp->chgCData(oldp+82,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [0U][1U]),8);
        bufp->chgCData(oldp+83,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [0U][2U]),8);
        bufp->chgCData(oldp+84,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [0U][3U]),8);
        bufp->chgCData(oldp+85,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [1U][0U]),8);
        bufp->chgCData(oldp+86,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [1U][1U]),8);
        bufp->chgCData(oldp+87,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [1U][2U]),8);
        bufp->chgCData(oldp+88,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [1U][3U]),8);
        bufp->chgCData(oldp+89,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [2U][0U]),8);
        bufp->chgCData(oldp+90,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [2U][1U]),8);
        bufp->chgCData(oldp+91,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [2U][2U]),8);
        bufp->chgCData(oldp+92,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [2U][3U]),8);
        bufp->chgCData(oldp+93,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [3U][0U]),8);
        bufp->chgCData(oldp+94,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [3U][1U]),8);
        bufp->chgCData(oldp+95,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [3U][2U]),8);
        bufp->chgCData(oldp+96,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                [3U][3U]),8);
        bufp->chgIData(oldp+97,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                [0U][0U]),32);
        bufp->chgIData(oldp+98,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                [0U][1U]),32);
        bufp->chgIData(oldp+99,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                [0U][2U]),32);
        bufp->chgIData(oldp+100,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [0U][3U]),32);
        bufp->chgIData(oldp+101,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [1U][0U]),32);
        bufp->chgIData(oldp+102,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [1U][1U]),32);
        bufp->chgIData(oldp+103,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [1U][2U]),32);
        bufp->chgIData(oldp+104,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [1U][3U]),32);
        bufp->chgIData(oldp+105,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [2U][0U]),32);
        bufp->chgIData(oldp+106,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [2U][1U]),32);
        bufp->chgIData(oldp+107,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [2U][2U]),32);
        bufp->chgIData(oldp+108,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [2U][3U]),32);
        bufp->chgIData(oldp+109,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [3U][0U]),32);
        bufp->chgIData(oldp+110,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [3U][1U]),32);
        bufp->chgIData(oldp+111,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [3U][2U]),32);
        bufp->chgIData(oldp+112,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                                 [3U][3U]),32);
        bufp->chgBit(oldp+113,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r));
        bufp->chgBit(oldp+114,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r));
        bufp->chgCData(oldp+115,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state),2);
        bufp->chgCData(oldp+116,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc),3);
        bufp->chgCData(oldp+117,(((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                  [0U][0U] : ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                               ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                              [1U][0U]
                                               : ((2U 
                                                   == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [2U]
                                                  [0U]
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+118,(((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                  [0U][1U] : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                               ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                              [1U][1U]
                                               : ((3U 
                                                   == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [2U]
                                                  [1U]
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+119,(((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                  [0U][2U] : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                               ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                              [1U][2U]
                                               : ((4U 
                                                   == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [2U]
                                                  [2U]
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+120,(((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                  [0U][3U] : ((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                               ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                              [1U][3U]
                                               : ((5U 
                                                   == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                  [2U]
                                                  [3U]
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+121,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s),8);
        bufp->chgCData(oldp+122,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s),8);
        bufp->chgCData(oldp+123,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s),8);
        bufp->chgCData(oldp+124,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s),8);
        bufp->chgIData(oldp+125,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30),32);
        bufp->chgIData(oldp+126,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31),32);
        bufp->chgIData(oldp+127,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32),32);
        bufp->chgIData(oldp+128,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33),32);
        bufp->chgBit(oldp+129,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending));
        bufp->chgCData(oldp+130,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r),6);
        bufp->chgIData(oldp+131,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r),32);
        bufp->chgCData(oldp+132,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r),4);
        bufp->chgIData(oldp+133,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0),32);
        bufp->chgIData(oldp+134,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1),32);
        bufp->chgIData(oldp+135,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2),32);
        bufp->chgIData(oldp+136,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3),32);
        bufp->chgIData(oldp+137,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00),32);
        bufp->chgIData(oldp+138,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01),32);
        bufp->chgIData(oldp+139,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02),32);
        bufp->chgIData(oldp+140,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03),32);
        bufp->chgIData(oldp+141,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10),32);
        bufp->chgIData(oldp+142,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11),32);
        bufp->chgIData(oldp+143,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12),32);
        bufp->chgIData(oldp+144,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13),32);
        bufp->chgIData(oldp+145,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20),32);
        bufp->chgIData(oldp+146,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21),32);
        bufp->chgIData(oldp+147,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22),32);
        bufp->chgIData(oldp+148,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23),32);
        bufp->chgCData(oldp+149,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0)),8);
        bufp->chgSData(oldp+150,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product),16);
        bufp->chgCData(oldp+151,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                           >> 8U))),8);
        bufp->chgSData(oldp+152,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product),16);
        bufp->chgCData(oldp+153,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+154,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product),16);
        bufp->chgCData(oldp+155,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+156,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product),16);
        bufp->chgCData(oldp+157,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1)),8);
        bufp->chgSData(oldp+158,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product),16);
        bufp->chgCData(oldp+159,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                           >> 8U))),8);
        bufp->chgSData(oldp+160,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product),16);
        bufp->chgCData(oldp+161,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+162,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product),16);
        bufp->chgCData(oldp+163,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+164,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product),16);
        bufp->chgCData(oldp+165,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2)),8);
        bufp->chgSData(oldp+166,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product),16);
        bufp->chgCData(oldp+167,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                           >> 8U))),8);
        bufp->chgSData(oldp+168,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product),16);
        bufp->chgCData(oldp+169,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+170,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product),16);
        bufp->chgCData(oldp+171,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+172,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product),16);
        bufp->chgCData(oldp+173,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3)),8);
        bufp->chgSData(oldp+174,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product),16);
        bufp->chgCData(oldp+175,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                           >> 8U))),8);
        bufp->chgSData(oldp+176,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product),16);
        bufp->chgCData(oldp+177,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+178,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product),16);
        bufp->chgCData(oldp+179,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+180,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product),16);
        bufp->chgIData(oldp+181,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__i),32);
        bufp->chgIData(oldp+182,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
        bufp->chgBit(oldp+183,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w));
        bufp->chgBit(oldp+184,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m));
        bufp->chgIData(oldp+185,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d),32);
        bufp->chgBit(oldp+186,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e));
        bufp->chgBit(oldp+187,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e));
        bufp->chgBit(oldp+188,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e));
        bufp->chgBit(oldp+189,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e));
        bufp->chgBit(oldp+190,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e));
        bufp->chgCData(oldp+191,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e),4);
        bufp->chgCData(oldp+192,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e),2);
        bufp->chgIData(oldp+193,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e),32);
        bufp->chgIData(oldp+194,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e),32);
        bufp->chgIData(oldp+195,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e),32);
        bufp->chgIData(oldp+196,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e),32);
        bufp->chgCData(oldp+197,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e),5);
        bufp->chgCData(oldp+198,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e),5);
        bufp->chgIData(oldp+199,(((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e)),32);
        bufp->chgIData(oldp+200,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m),32);
        bufp->chgIData(oldp+201,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m),32);
        bufp->chgCData(oldp+202,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m),2);
        bufp->chgIData(oldp+203,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w),32);
        bufp->chgIData(oldp+204,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w),32);
        bufp->chgIData(oldp+205,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w),32);
        bufp->chgIData(oldp+206,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w),32);
        bufp->chgCData(oldp+207,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w),2);
        bufp->chgIData(oldp+208,((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                                  + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e)),32);
        bufp->chgBit(oldp+209,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending));
        bufp->chgSData(oldp+210,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r),14);
        bufp->chgIData(oldp+211,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r),32);
        bufp->chgCData(oldp+212,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r),4);
        bufp->chgBit(oldp+213,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending));
        bufp->chgSData(oldp+214,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r),14);
        bufp->chgIData(oldp+215,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r),32);
        bufp->chgCData(oldp+216,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r),4);
        bufp->chgCData(oldp+217,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0]),2);
        bufp->chgCData(oldp+218,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1]),2);
        bufp->chgCData(oldp+219,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2]),2);
        bufp->chgCData(oldp+220,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0]),2);
        bufp->chgCData(oldp+221,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1]),2);
        bufp->chgCData(oldp+222,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2]),2);
        bufp->chgBit(oldp+223,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[0]));
        bufp->chgBit(oldp+224,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[1]));
        bufp->chgBit(oldp+225,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[2]));
        bufp->chgIData(oldp+226,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[0]),32);
        bufp->chgIData(oldp+227,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[1]),32);
        bufp->chgIData(oldp+228,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[2]),32);
        bufp->chgBit(oldp+229,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[0]));
        bufp->chgBit(oldp+230,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[1]));
        bufp->chgBit(oldp+231,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[2]));
        bufp->chgCData(oldp+232,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0]),2);
        bufp->chgCData(oldp+233,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1]),2);
        bufp->chgCData(oldp+234,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2]),2);
        bufp->chgBit(oldp+235,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0]));
        bufp->chgBit(oldp+236,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1]));
        bufp->chgBit(oldp+237,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2]));
        bufp->chgCData(oldp+238,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0]),2);
        bufp->chgCData(oldp+239,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1]),2);
        bufp->chgCData(oldp+240,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2]),2);
        bufp->chgCData(oldp+241,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0]),2);
        bufp->chgCData(oldp+242,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1]),2);
        bufp->chgCData(oldp+243,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2]),2);
        bufp->chgBit(oldp+244,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0]));
        bufp->chgBit(oldp+245,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1]));
        bufp->chgBit(oldp+246,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2]));
        bufp->chgCData(oldp+247,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0]),2);
        bufp->chgCData(oldp+248,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1]),2);
        bufp->chgCData(oldp+249,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2]),2);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgIData(oldp+250,(vlSelf->soc_tb__DOT__y00_captured),32);
        bufp->chgIData(oldp+251,(vlSelf->soc_tb__DOT__y33_captured),32);
        bufp->chgBit(oldp+252,(vlSelf->soc_tb__DOT__y00_valid));
        bufp->chgBit(oldp+253,(vlSelf->soc_tb__DOT__y33_valid));
        bufp->chgIData(oldp+254,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0]),32);
        bufp->chgIData(oldp+255,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[1]),32);
        bufp->chgIData(oldp+256,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[2]),32);
        bufp->chgIData(oldp+257,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[3]),32);
        bufp->chgIData(oldp+258,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[4]),32);
        bufp->chgIData(oldp+259,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[5]),32);
        bufp->chgIData(oldp+260,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[6]),32);
        bufp->chgIData(oldp+261,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[7]),32);
        bufp->chgIData(oldp+262,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[8]),32);
        bufp->chgIData(oldp+263,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[9]),32);
        bufp->chgIData(oldp+264,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[10]),32);
        bufp->chgIData(oldp+265,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[11]),32);
        bufp->chgIData(oldp+266,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[12]),32);
        bufp->chgIData(oldp+267,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[13]),32);
        bufp->chgIData(oldp+268,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[14]),32);
        bufp->chgIData(oldp+269,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[15]),32);
        bufp->chgIData(oldp+270,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[16]),32);
        bufp->chgIData(oldp+271,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[17]),32);
        bufp->chgIData(oldp+272,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[18]),32);
        bufp->chgIData(oldp+273,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[19]),32);
        bufp->chgIData(oldp+274,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[20]),32);
        bufp->chgIData(oldp+275,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[21]),32);
        bufp->chgIData(oldp+276,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[22]),32);
        bufp->chgIData(oldp+277,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[23]),32);
        bufp->chgIData(oldp+278,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[24]),32);
        bufp->chgIData(oldp+279,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[25]),32);
        bufp->chgIData(oldp+280,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[26]),32);
        bufp->chgIData(oldp+281,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[27]),32);
        bufp->chgIData(oldp+282,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[28]),32);
        bufp->chgIData(oldp+283,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[29]),32);
        bufp->chgIData(oldp+284,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[30]),32);
        bufp->chgIData(oldp+285,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__unnamedblk1__DOT__i),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[4U])) {
        bufp->chgIData(oldp+286,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc),32);
        bufp->chgIData(oldp+287,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m),32);
        bufp->chgIData(oldp+288,(((0U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                                   ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                       << 0x18U) | 
                                      ((0xff0000U & 
                                        (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                         << 0x10U)) 
                                       | ((0xff00U 
                                           & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                              << 8U)) 
                                          | (0xffU 
                                             & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))))
                                   : ((1U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                                       ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                           << 0x10U) 
                                          | (0xffffU 
                                             & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))
                                       : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))),32);
        bufp->chgIData(oldp+289,(vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata),32);
        bufp->chgBit(oldp+290,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m));
        bufp->chgBit(oldp+291,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m));
        bufp->chgBit(oldp+292,((0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
        bufp->chgCData(oldp+293,(vlSelf->soc_tb__DOT__dut__DOT__dmem_be),4);
        bufp->chgIData(oldp+294,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r),32);
        bufp->chgIData(oldp+295,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r),32);
        bufp->chgIData(oldp+296,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                                 [0U]),32);
        bufp->chgCData(oldp+297,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r),4);
        bufp->chgBit(oldp+298,((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
        bufp->chgBit(oldp+299,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                               [0U]));
        bufp->chgBit(oldp+300,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                               [0U]));
        bufp->chgBit(oldp+301,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                               [0U]));
        bufp->chgBit(oldp+302,((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
        bufp->chgBit(oldp+303,((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
        bufp->chgBit(oldp+304,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                               [0U]));
        bufp->chgBit(oldp+305,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                               [0U]));
        bufp->chgBit(oldp+306,((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
        bufp->chgIData(oldp+307,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                                 [1U]),32);
        bufp->chgBit(oldp+308,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                               [1U]));
        bufp->chgBit(oldp+309,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                               [1U]));
        bufp->chgBit(oldp+310,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                               [1U]));
        bufp->chgBit(oldp+311,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                               [1U]));
        bufp->chgBit(oldp+312,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                               [1U]));
        bufp->chgIData(oldp+313,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                                 [2U]),32);
        bufp->chgBit(oldp+314,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                               [2U]));
        bufp->chgBit(oldp+315,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                               [2U]));
        bufp->chgBit(oldp+316,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                               [2U]));
        bufp->chgBit(oldp+317,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                               [2U]));
        bufp->chgBit(oldp+318,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                               [2U]));
        bufp->chgIData(oldp+319,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                 [0U]),32);
        bufp->chgIData(oldp+320,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                                 [0U]),32);
        bufp->chgIData(oldp+321,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                 [0U]),32);
        bufp->chgCData(oldp+322,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                                 [0U]),4);
        bufp->chgBit(oldp+323,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                               [0U]));
        bufp->chgBit(oldp+324,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                               [0U]));
        bufp->chgBit(oldp+325,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                               [0U]));
        bufp->chgBit(oldp+326,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                               [0U]));
        bufp->chgBit(oldp+327,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                               [0U]));
        bufp->chgIData(oldp+328,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                 [1U]),32);
        bufp->chgIData(oldp+329,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                                 [1U]),32);
        bufp->chgIData(oldp+330,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                 [1U]),32);
        bufp->chgCData(oldp+331,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                                 [1U]),4);
        bufp->chgBit(oldp+332,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                               [1U]));
        bufp->chgBit(oldp+333,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                               [1U]));
        bufp->chgBit(oldp+334,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                               [1U]));
        bufp->chgBit(oldp+335,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                               [1U]));
        bufp->chgBit(oldp+336,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                               [1U]));
        bufp->chgIData(oldp+337,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                 [2U]),32);
        bufp->chgIData(oldp+338,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                                 [2U]),32);
        bufp->chgIData(oldp+339,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                 [2U]),32);
        bufp->chgCData(oldp+340,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                                 [2U]),4);
        bufp->chgBit(oldp+341,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                               [2U]));
        bufp->chgBit(oldp+342,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                               [2U]));
        bufp->chgBit(oldp+343,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                               [2U]));
        bufp->chgBit(oldp+344,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                               [2U]));
        bufp->chgBit(oldp+345,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                               [2U]));
        bufp->chgCData(oldp+346,((0x3fU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                           [2U] >> 2U))),6);
        bufp->chgCData(oldp+347,((0x3fU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                           [2U] >> 2U))),6);
        bufp->chgIData(oldp+348,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__rdata_comb),32);
        bufp->chgCData(oldp+349,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state),3);
        bufp->chgBit(oldp+350,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if));
        bufp->chgBit(oldp+351,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id));
        bufp->chgBit(oldp+352,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex));
        bufp->chgBit(oldp+353,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken));
        bufp->chgCData(oldp+354,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w),5);
        bufp->chgIData(oldp+355,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data),32);
        bufp->chgCData(oldp+356,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m),5);
        bufp->chgIData(oldp+357,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d),32);
        bufp->chgCData(oldp+358,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                           >> 0xfU))),5);
        bufp->chgCData(oldp+359,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                           >> 0x14U))),5);
        bufp->chgCData(oldp+360,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                           >> 7U))),5);
        bufp->chgCData(oldp+361,((7U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                        >> 0xcU))),3);
        bufp->chgIData(oldp+362,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_d),32);
        bufp->chgBit(oldp+363,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_d));
        bufp->chgBit(oldp+364,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_d));
        bufp->chgBit(oldp+365,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_d));
        bufp->chgBit(oldp+366,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_d));
        bufp->chgBit(oldp+367,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_d));
        bufp->chgBit(oldp+368,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_d));
        bufp->chgBit(oldp+369,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_d));
        bufp->chgCData(oldp+370,((((0x33U == (0x7fU 
                                              & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)) 
                                   || (0x13U == (0x7fU 
                                                 & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                                   ? ((0x4000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                       ? ((0x2000U 
                                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? ((0x1000U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? 2U
                                               : 3U)
                                           : ((0x1000U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? ((0x40000000U 
                                                   & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                   ? 7U
                                                   : 6U)
                                               : 4U))
                                       : ((0x2000U 
                                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                           ? ((0x1000U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? 9U
                                               : 8U)
                                           : ((0x1000U 
                                               & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                               ? 5U
                                               : ((IData)(
                                                          (0x40000033U 
                                                           == 
                                                           (0x4000007fU 
                                                            & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                                                   ? 1U
                                                   : 0U))))
                                   : 0U)),4);
        bufp->chgCData(oldp+371,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_d),2);
        bufp->chgBit(oldp+372,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e));
        bufp->chgBit(oldp+373,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e));
        bufp->chgCData(oldp+374,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e),3);
        bufp->chgCData(oldp+375,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e),5);
        bufp->chgIData(oldp+376,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val),32);
        bufp->chgCData(oldp+377,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a),2);
        bufp->chgCData(oldp+378,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b),2);
        bufp->chgIData(oldp+379,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result),32);
        bufp->chgIData(oldp+380,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd),32);
        bufp->chgIData(oldp+381,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m),32);
        bufp->chgCData(oldp+382,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m),3);
        bufp->chgIData(oldp+383,(((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                                   ? ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                                       ? vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata
                                       : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                                           ? (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half)
                                           : (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte)))
                                   : ((2U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                                       ? vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata
                                       : ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
                                           ? (((- (IData)(
                                                          (1U 
                                                           & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half) 
                                                              >> 0xfU)))) 
                                               << 0x10U) 
                                              | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half))
                                           : (((- (IData)(
                                                          (1U 
                                                           & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte) 
                                                              >> 7U)))) 
                                               << 8U) 
                                              | (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte)))))),32);
        bufp->chgCData(oldp+384,((0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)),7);
        bufp->chgBit(oldp+385,((1U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                      >> 0x1eU))));
        bufp->chgIData(oldp+386,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i),32);
        bufp->chgIData(oldp+387,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                               >> 0x1fU))) 
                                   << 0xcU) | ((0xfe0U 
                                                & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                   >> 0x14U)) 
                                               | (0x1fU 
                                                  & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                     >> 7U))))),32);
        bufp->chgIData(oldp+388,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                               >> 0x1fU))) 
                                   << 0xdU) | ((0x1000U 
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
                                                           >> 7U))))))),32);
        bufp->chgIData(oldp+389,((0xfffff000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)),32);
        bufp->chgIData(oldp+390,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
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
                                                            >> 0x14U))))))),32);
        bufp->chgIData(oldp+391,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd),32);
        bufp->chgIData(oldp+392,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a),32);
        bufp->chgIData(oldp+393,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b),32);
        bufp->chgBit(oldp+394,((0U == vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result)));
        bufp->chgBit(oldp+395,(((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
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
                                              >> 1U))) 
                                    && ((1U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
                                         ? (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                                            != vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd)
                                         : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd 
                                            == vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd))))));
        bufp->chgCData(oldp+396,((0x1fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)),5);
        bufp->chgBit(oldp+397,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use));
        bufp->chgCData(oldp+398,((3U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m)),2);
        bufp->chgBit(oldp+399,((1U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m 
                                      >> 1U))));
        bufp->chgCData(oldp+400,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m)),8);
        bufp->chgSData(oldp+401,((0xffffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m)),16);
        bufp->chgCData(oldp+402,((3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))),2);
        bufp->chgCData(oldp+403,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata)),8);
        bufp->chgCData(oldp+404,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                           >> 8U))),8);
        bufp->chgCData(oldp+405,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                           >> 0x10U))),8);
        bufp->chgCData(oldp+406,((vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+407,((0xffffU & vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata)),16);
        bufp->chgSData(oldp+408,((vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                  >> 0x10U)),16);
        bufp->chgCData(oldp+409,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte),8);
        bufp->chgSData(oldp+410,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half),16);
        bufp->chgBit(oldp+411,((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte) 
                                      >> 7U))));
        bufp->chgBit(oldp+412,((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half) 
                                      >> 0xfU))));
        bufp->chgBit(oldp+413,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we));
        bufp->chgSData(oldp+414,((0x1ffU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                                            >> 2U))),9);
        bufp->chgSData(oldp+415,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                             [0U] >> 2U))),14);
        bufp->chgSData(oldp+416,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                             [0U] >> 2U))),14);
        bufp->chgSData(oldp+417,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                             [1U] >> 2U))),14);
        bufp->chgSData(oldp+418,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                             [1U] >> 2U))),14);
        bufp->chgBit(oldp+419,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0]));
        bufp->chgBit(oldp+420,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1]));
        bufp->chgBit(oldp+421,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2]));
        bufp->chgBit(oldp+422,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0]));
        bufp->chgBit(oldp+423,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1]));
        bufp->chgBit(oldp+424,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2]));
        bufp->chgBit(oldp+425,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0]));
        bufp->chgBit(oldp+426,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1]));
        bufp->chgBit(oldp+427,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2]));
        bufp->chgBit(oldp+428,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0]));
        bufp->chgBit(oldp+429,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1]));
        bufp->chgBit(oldp+430,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2]));
        bufp->chgIData(oldp+431,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0]),32);
        bufp->chgIData(oldp+432,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1]),32);
        bufp->chgIData(oldp+433,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2]),32);
        bufp->chgBit(oldp+434,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0]));
        bufp->chgBit(oldp+435,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1]));
        bufp->chgBit(oldp+436,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2]));
        bufp->chgIData(oldp+437,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0]),32);
        bufp->chgIData(oldp+438,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1]),32);
        bufp->chgIData(oldp+439,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2]),32);
        bufp->chgBit(oldp+440,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0]));
        bufp->chgBit(oldp+441,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[1]));
        bufp->chgBit(oldp+442,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[2]));
        bufp->chgIData(oldp+443,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0]),32);
        bufp->chgIData(oldp+444,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1]),32);
        bufp->chgIData(oldp+445,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2]),32);
        bufp->chgCData(oldp+446,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0]),4);
        bufp->chgCData(oldp+447,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1]),4);
        bufp->chgCData(oldp+448,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2]),4);
        bufp->chgBit(oldp+449,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0]));
        bufp->chgBit(oldp+450,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[1]));
        bufp->chgBit(oldp+451,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[2]));
        bufp->chgBit(oldp+452,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0]));
        bufp->chgBit(oldp+453,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1]));
        bufp->chgBit(oldp+454,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[2]));
        bufp->chgIData(oldp+455,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0]),32);
        bufp->chgIData(oldp+456,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1]),32);
        bufp->chgIData(oldp+457,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2]),32);
        bufp->chgBit(oldp+458,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0]));
        bufp->chgBit(oldp+459,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[1]));
        bufp->chgBit(oldp+460,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[2]));
        bufp->chgBit(oldp+461,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0]));
        bufp->chgBit(oldp+462,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1]));
        bufp->chgBit(oldp+463,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[2]));
    }
    bufp->chgBit(oldp+464,(vlSelf->soc_tb__DOT__clk));
    bufp->chgBit(oldp+465,(vlSelf->soc_tb__DOT__rst_n));
    bufp->chgIData(oldp+466,(vlSelf->soc_tb__DOT__error_count),32);
    bufp->chgBit(oldp+467,(vlSelf->soc_tb__DOT__done_flag));
    bufp->chgBit(oldp+468,((1U & (~ (IData)(vlSelf->soc_tb__DOT__rst_n)))));
    bufp->chgIData(oldp+469,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e)
                               ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                                   ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                                   : (0xfffffffeU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))
                               : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                                  + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e))),32);
    bufp->chgIData(oldp+470,(((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                               >> 0xfU)))
                               ? 0U : (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                                        & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                           == (0x1fU 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                  >> 0xfU))))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                                        : ((0x1eU >= 
                                            (0x1fU 
                                             & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                 >> 0xfU) 
                                                - (IData)(1U))))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                                           [(0x1fU 
                                             & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                 >> 0xfU) 
                                                - (IData)(1U)))]
                                            : 0U)))),32);
    bufp->chgIData(oldp+471,(((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                               >> 0x14U)))
                               ? 0U : (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                                        & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                           == (0x1fU 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                  >> 0x14U))))
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                                        : ((0x1eU >= 
                                            (0x1fU 
                                             & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                 >> 0x14U) 
                                                - (IData)(1U))))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                                           [(0x1fU 
                                             & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                 >> 0x14U) 
                                                - (IData)(1U)))]
                                            : 0U)))),32);
    bufp->chgIData(oldp+472,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                               ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                               : (0xfffffffeU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))),32);
    bufp->chgIData(oldp+473,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken)
                               ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e)
                                   ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                                       ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                                       : (0xfffffffeU 
                                          & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))
                                   : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                                      + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e))
                               : ((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc))),32);
}

void Vsoc_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_cleanup\n"); );
    // Init
    Vsoc_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_tb___024root*>(voidSelf);
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
}
