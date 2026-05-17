// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vcrossbar_accel_tb__Syms.h"


void Vcrossbar_accel_tb___024root__trace_chg_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vcrossbar_accel_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_chg_0\n"); );
    // Init
    Vcrossbar_accel_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcrossbar_accel_tb___024root*>(voidSelf);
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vcrossbar_accel_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vcrossbar_accel_tb___024root__trace_chg_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[0]));
        bufp->chgBit(oldp+1,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[1]));
        bufp->chgBit(oldp+2,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[2]));
        bufp->chgBit(oldp+3,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[0]));
        bufp->chgBit(oldp+4,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[1]));
        bufp->chgBit(oldp+5,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[2]));
        bufp->chgCData(oldp+6,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[0]),2);
        bufp->chgCData(oldp+7,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[1]),2);
        bufp->chgCData(oldp+8,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[2]),2);
        bufp->chgBit(oldp+9,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[0]));
        bufp->chgBit(oldp+10,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[1]));
        bufp->chgBit(oldp+11,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[2]));
        bufp->chgCData(oldp+12,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[0]),2);
        bufp->chgCData(oldp+13,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[1]),2);
        bufp->chgCData(oldp+14,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[2]),2);
        bufp->chgIData(oldp+15,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s),32);
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[2U]))) {
        bufp->chgIData(oldp+16,(vlSelf->crossbar_accel_tb__DOT__error_count),32);
        bufp->chgIData(oldp+17,(vlSelf->crossbar_accel_tb__DOT__m0_awaddr),32);
        bufp->chgBit(oldp+18,(vlSelf->crossbar_accel_tb__DOT__m0_awvalid));
        bufp->chgIData(oldp+19,(vlSelf->crossbar_accel_tb__DOT__m0_wdata),32);
        bufp->chgCData(oldp+20,(vlSelf->crossbar_accel_tb__DOT__m0_wstrb),4);
        bufp->chgBit(oldp+21,(vlSelf->crossbar_accel_tb__DOT__m0_wvalid));
        bufp->chgBit(oldp+22,(vlSelf->crossbar_accel_tb__DOT__m0_bready));
        bufp->chgIData(oldp+23,(vlSelf->crossbar_accel_tb__DOT__m0_araddr),32);
        bufp->chgBit(oldp+24,(vlSelf->crossbar_accel_tb__DOT__m0_arvalid));
        bufp->chgBit(oldp+25,(vlSelf->crossbar_accel_tb__DOT__m0_rready));
        bufp->chgIData(oldp+26,(vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd),32);
    }
    if (VL_UNLIKELY(((vlSelf->__Vm_traceActivity[1U] 
                      | vlSelf->__Vm_traceActivity[3U]) 
                     | vlSelf->__Vm_traceActivity[5U]))) {
        bufp->chgIData(oldp+27,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[0]),32);
        bufp->chgIData(oldp+28,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[1]),32);
        bufp->chgIData(oldp+29,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[2]),32);
        bufp->chgBit(oldp+30,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[0]));
        bufp->chgBit(oldp+31,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[1]));
        bufp->chgBit(oldp+32,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[2]));
        bufp->chgIData(oldp+33,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[0]),32);
        bufp->chgIData(oldp+34,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[1]),32);
        bufp->chgIData(oldp+35,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[2]),32);
        bufp->chgCData(oldp+36,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[0]),4);
        bufp->chgCData(oldp+37,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[1]),4);
        bufp->chgCData(oldp+38,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[2]),4);
        bufp->chgBit(oldp+39,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[0]));
        bufp->chgBit(oldp+40,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[1]));
        bufp->chgBit(oldp+41,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[2]));
        bufp->chgBit(oldp+42,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[0]));
        bufp->chgBit(oldp+43,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[1]));
        bufp->chgBit(oldp+44,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[2]));
        bufp->chgIData(oldp+45,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[0]),32);
        bufp->chgIData(oldp+46,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[1]),32);
        bufp->chgIData(oldp+47,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[2]),32);
        bufp->chgBit(oldp+48,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[0]));
        bufp->chgBit(oldp+49,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[1]));
        bufp->chgBit(oldp+50,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[2]));
        bufp->chgBit(oldp+51,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[0]));
        bufp->chgBit(oldp+52,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[1]));
        bufp->chgBit(oldp+53,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[2]));
        bufp->chgCData(oldp+54,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[0]),2);
        bufp->chgCData(oldp+55,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[1]),2);
        bufp->chgCData(oldp+56,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[2]),2);
        bufp->chgCData(oldp+57,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[0]),2);
        bufp->chgCData(oldp+58,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[1]),2);
        bufp->chgCData(oldp+59,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[2]),2);
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[3U] 
                     | vlSelf->__Vm_traceActivity[6U]))) {
        bufp->chgIData(oldp+60,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                [0U]),32);
        bufp->chgIData(oldp+61,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                                [0U]),32);
        bufp->chgIData(oldp+62,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                [0U]),32);
        bufp->chgCData(oldp+63,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                                [0U]),4);
        bufp->chgBit(oldp+64,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                              [0U]));
        bufp->chgBit(oldp+65,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                              [0U]));
        bufp->chgBit(oldp+66,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                              [0U]));
        bufp->chgBit(oldp+67,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                              [0U]));
        bufp->chgBit(oldp+68,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                              [0U]));
        bufp->chgIData(oldp+69,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                [1U]),32);
        bufp->chgIData(oldp+70,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                                [1U]),32);
        bufp->chgIData(oldp+71,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                [1U]),32);
        bufp->chgCData(oldp+72,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                                [1U]),4);
        bufp->chgBit(oldp+73,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                              [1U]));
        bufp->chgBit(oldp+74,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                              [1U]));
        bufp->chgBit(oldp+75,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                              [1U]));
        bufp->chgBit(oldp+76,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                              [1U]));
        bufp->chgBit(oldp+77,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                              [1U]));
        bufp->chgIData(oldp+78,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                [2U]),32);
        bufp->chgIData(oldp+79,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                                [2U]),32);
        bufp->chgIData(oldp+80,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                [2U]),32);
        bufp->chgCData(oldp+81,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                                [2U]),4);
        bufp->chgBit(oldp+82,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                              [2U]));
        bufp->chgBit(oldp+83,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                              [2U]));
        bufp->chgBit(oldp+84,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                              [2U]));
        bufp->chgBit(oldp+85,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                              [2U]));
        bufp->chgBit(oldp+86,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                              [2U]));
        bufp->chgCData(oldp+87,((0x3fU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                          [2U] >> 2U))),6);
        bufp->chgCData(oldp+88,((0x3fU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                          [2U] >> 2U))),6);
        bufp->chgIData(oldp+89,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__rdata_comb),32);
        bufp->chgSData(oldp+90,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                            [0U] >> 2U))),14);
        bufp->chgSData(oldp+91,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                            [0U] >> 2U))),14);
        bufp->chgSData(oldp+92,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                            [1U] >> 2U))),14);
        bufp->chgSData(oldp+93,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                            [1U] >> 2U))),14);
        bufp->chgIData(oldp+94,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[0]),32);
        bufp->chgIData(oldp+95,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[1]),32);
        bufp->chgIData(oldp+96,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[2]),32);
        bufp->chgBit(oldp+97,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0]));
        bufp->chgBit(oldp+98,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1]));
        bufp->chgBit(oldp+99,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2]));
        bufp->chgIData(oldp+100,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[0]),32);
        bufp->chgIData(oldp+101,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[1]),32);
        bufp->chgIData(oldp+102,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[2]),32);
        bufp->chgCData(oldp+103,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[0]),4);
        bufp->chgCData(oldp+104,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[1]),4);
        bufp->chgCData(oldp+105,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[2]),4);
        bufp->chgBit(oldp+106,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[0]));
        bufp->chgBit(oldp+107,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[1]));
        bufp->chgBit(oldp+108,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[2]));
        bufp->chgBit(oldp+109,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[0]));
        bufp->chgBit(oldp+110,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[1]));
        bufp->chgBit(oldp+111,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[2]));
        bufp->chgIData(oldp+112,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0]),32);
        bufp->chgIData(oldp+113,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1]),32);
        bufp->chgIData(oldp+114,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2]),32);
        bufp->chgBit(oldp+115,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0]));
        bufp->chgBit(oldp+116,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1]));
        bufp->chgBit(oldp+117,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2]));
        bufp->chgBit(oldp+118,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0]));
        bufp->chgBit(oldp+119,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1]));
        bufp->chgBit(oldp+120,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2]));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[4U])) {
        bufp->chgBit(oldp+121,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                               [0U]));
        bufp->chgBit(oldp+122,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                               [0U]));
        bufp->chgCData(oldp+123,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                                 [0U]),2);
        bufp->chgBit(oldp+124,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                               [0U]));
        bufp->chgBit(oldp+125,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                               [0U]));
        bufp->chgIData(oldp+126,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                                 [0U]),32);
        bufp->chgCData(oldp+127,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                                 [0U]),2);
        bufp->chgBit(oldp+128,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                               [0U]));
        bufp->chgIData(oldp+129,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                                 [1U]),32);
        bufp->chgCData(oldp+130,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                                 [1U]),2);
        bufp->chgCData(oldp+131,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                                 [1U]),2);
        bufp->chgBit(oldp+132,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                               [1U]));
        bufp->chgBit(oldp+133,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                               [1U]));
        bufp->chgBit(oldp+134,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                               [1U]));
        bufp->chgBit(oldp+135,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                               [1U]));
        bufp->chgBit(oldp+136,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                               [1U]));
        bufp->chgIData(oldp+137,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                                 [2U]),32);
        bufp->chgCData(oldp+138,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                                 [2U]),2);
        bufp->chgCData(oldp+139,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                                 [2U]),2);
        bufp->chgBit(oldp+140,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                               [2U]));
        bufp->chgBit(oldp+141,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                               [2U]));
        bufp->chgBit(oldp+142,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                               [2U]));
        bufp->chgBit(oldp+143,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                               [2U]));
        bufp->chgBit(oldp+144,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                               [2U]));
        bufp->chgIData(oldp+145,(vlSelf->crossbar_accel_tb__DOT__s0_rdata),32);
        bufp->chgBit(oldp+146,(vlSelf->crossbar_accel_tb__DOT__s0_bvalid));
        bufp->chgBit(oldp+147,(vlSelf->crossbar_accel_tb__DOT__s0_rvalid));
        bufp->chgIData(oldp+148,(vlSelf->crossbar_accel_tb__DOT__s1_rdata),32);
        bufp->chgBit(oldp+149,(vlSelf->crossbar_accel_tb__DOT__s1_bvalid));
        bufp->chgBit(oldp+150,(vlSelf->crossbar_accel_tb__DOT__s1_rvalid));
        bufp->chgIData(oldp+151,(vlSelf->crossbar_accel_tb__DOT__s2_rdata),32);
        bufp->chgBit(oldp+152,(vlSelf->crossbar_accel_tb__DOT__s2_bvalid));
        bufp->chgBit(oldp+153,(vlSelf->crossbar_accel_tb__DOT__s2_rvalid));
        bufp->chgCData(oldp+154,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [0U][0U]),8);
        bufp->chgCData(oldp+155,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [0U][1U]),8);
        bufp->chgCData(oldp+156,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [0U][2U]),8);
        bufp->chgCData(oldp+157,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [0U][3U]),8);
        bufp->chgCData(oldp+158,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [1U][0U]),8);
        bufp->chgCData(oldp+159,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [1U][1U]),8);
        bufp->chgCData(oldp+160,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [1U][2U]),8);
        bufp->chgCData(oldp+161,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [1U][3U]),8);
        bufp->chgCData(oldp+162,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [2U][0U]),8);
        bufp->chgCData(oldp+163,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [2U][1U]),8);
        bufp->chgCData(oldp+164,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [2U][2U]),8);
        bufp->chgCData(oldp+165,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [2U][3U]),8);
        bufp->chgCData(oldp+166,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [3U][0U]),8);
        bufp->chgCData(oldp+167,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [3U][1U]),8);
        bufp->chgCData(oldp+168,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [3U][2U]),8);
        bufp->chgCData(oldp+169,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                                 [3U][3U]),8);
        bufp->chgCData(oldp+170,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [0U][0U]),8);
        bufp->chgCData(oldp+171,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [0U][1U]),8);
        bufp->chgCData(oldp+172,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [0U][2U]),8);
        bufp->chgCData(oldp+173,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [0U][3U]),8);
        bufp->chgCData(oldp+174,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [1U][0U]),8);
        bufp->chgCData(oldp+175,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [1U][1U]),8);
        bufp->chgCData(oldp+176,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [1U][2U]),8);
        bufp->chgCData(oldp+177,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [1U][3U]),8);
        bufp->chgCData(oldp+178,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [2U][0U]),8);
        bufp->chgCData(oldp+179,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [2U][1U]),8);
        bufp->chgCData(oldp+180,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [2U][2U]),8);
        bufp->chgCData(oldp+181,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [2U][3U]),8);
        bufp->chgCData(oldp+182,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [3U][0U]),8);
        bufp->chgCData(oldp+183,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [3U][1U]),8);
        bufp->chgCData(oldp+184,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [3U][2U]),8);
        bufp->chgCData(oldp+185,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                 [3U][3U]),8);
        bufp->chgIData(oldp+186,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [0U][0U]),32);
        bufp->chgIData(oldp+187,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [0U][1U]),32);
        bufp->chgIData(oldp+188,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [0U][2U]),32);
        bufp->chgIData(oldp+189,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [0U][3U]),32);
        bufp->chgIData(oldp+190,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [1U][0U]),32);
        bufp->chgIData(oldp+191,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [1U][1U]),32);
        bufp->chgIData(oldp+192,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [1U][2U]),32);
        bufp->chgIData(oldp+193,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [1U][3U]),32);
        bufp->chgIData(oldp+194,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [2U][0U]),32);
        bufp->chgIData(oldp+195,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [2U][1U]),32);
        bufp->chgIData(oldp+196,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [2U][2U]),32);
        bufp->chgIData(oldp+197,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [2U][3U]),32);
        bufp->chgIData(oldp+198,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [3U][0U]),32);
        bufp->chgIData(oldp+199,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [3U][1U]),32);
        bufp->chgIData(oldp+200,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [3U][2U]),32);
        bufp->chgIData(oldp+201,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                                 [3U][3U]),32);
        bufp->chgBit(oldp+202,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r));
        bufp->chgBit(oldp+203,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r));
        bufp->chgCData(oldp+204,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state),2);
        bufp->chgCData(oldp+205,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc),3);
        bufp->chgCData(oldp+206,(((0U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                   ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                  [0U][0U] : ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                               ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                              [1U][0U]
                                               : ((2U 
                                                   == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [2U]
                                                  [0U]
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+207,(((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                   ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                  [0U][1U] : ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                               ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                              [1U][1U]
                                               : ((3U 
                                                   == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [2U]
                                                  [1U]
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+208,(((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                   ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                  [0U][2U] : ((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                               ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                              [1U][2U]
                                               : ((4U 
                                                   == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [2U]
                                                  [2U]
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+209,(((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                   ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                  [0U][3U] : ((4U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                               ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                              [1U][3U]
                                               : ((5U 
                                                   == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                   ? 
                                                  vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                  [2U]
                                                  [3U]
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+210,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s),8);
        bufp->chgCData(oldp+211,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s),8);
        bufp->chgCData(oldp+212,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s),8);
        bufp->chgCData(oldp+213,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s),8);
        bufp->chgIData(oldp+214,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30),32);
        bufp->chgIData(oldp+215,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31),32);
        bufp->chgIData(oldp+216,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32),32);
        bufp->chgIData(oldp+217,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33),32);
        bufp->chgBit(oldp+218,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending));
        bufp->chgCData(oldp+219,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r),6);
        bufp->chgIData(oldp+220,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r),32);
        bufp->chgCData(oldp+221,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r),4);
        bufp->chgIData(oldp+222,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0),32);
        bufp->chgIData(oldp+223,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1),32);
        bufp->chgIData(oldp+224,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2),32);
        bufp->chgIData(oldp+225,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3),32);
        bufp->chgIData(oldp+226,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00),32);
        bufp->chgIData(oldp+227,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01),32);
        bufp->chgIData(oldp+228,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02),32);
        bufp->chgIData(oldp+229,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03),32);
        bufp->chgIData(oldp+230,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10),32);
        bufp->chgIData(oldp+231,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11),32);
        bufp->chgIData(oldp+232,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12),32);
        bufp->chgIData(oldp+233,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13),32);
        bufp->chgIData(oldp+234,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20),32);
        bufp->chgIData(oldp+235,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21),32);
        bufp->chgIData(oldp+236,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22),32);
        bufp->chgIData(oldp+237,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23),32);
        bufp->chgCData(oldp+238,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0)),8);
        bufp->chgSData(oldp+239,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product),16);
        bufp->chgCData(oldp+240,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                           >> 8U))),8);
        bufp->chgSData(oldp+241,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product),16);
        bufp->chgCData(oldp+242,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+243,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product),16);
        bufp->chgCData(oldp+244,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+245,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product),16);
        bufp->chgCData(oldp+246,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1)),8);
        bufp->chgSData(oldp+247,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product),16);
        bufp->chgCData(oldp+248,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                           >> 8U))),8);
        bufp->chgSData(oldp+249,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product),16);
        bufp->chgCData(oldp+250,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+251,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product),16);
        bufp->chgCData(oldp+252,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+253,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product),16);
        bufp->chgCData(oldp+254,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2)),8);
        bufp->chgSData(oldp+255,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product),16);
        bufp->chgCData(oldp+256,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                           >> 8U))),8);
        bufp->chgSData(oldp+257,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product),16);
        bufp->chgCData(oldp+258,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+259,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product),16);
        bufp->chgCData(oldp+260,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+261,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product),16);
        bufp->chgCData(oldp+262,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3)),8);
        bufp->chgSData(oldp+263,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product),16);
        bufp->chgCData(oldp+264,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                           >> 8U))),8);
        bufp->chgSData(oldp+265,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product),16);
        bufp->chgCData(oldp+266,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+267,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product),16);
        bufp->chgCData(oldp+268,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+269,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product),16);
        bufp->chgIData(oldp+270,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__i),32);
        bufp->chgIData(oldp+271,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
        bufp->chgBit(oldp+272,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending));
        bufp->chgSData(oldp+273,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r),14);
        bufp->chgIData(oldp+274,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r),32);
        bufp->chgCData(oldp+275,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r),4);
        bufp->chgBit(oldp+276,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending));
        bufp->chgSData(oldp+277,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r),14);
        bufp->chgIData(oldp+278,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r),32);
        bufp->chgCData(oldp+279,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r),4);
        bufp->chgBit(oldp+280,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[0]));
        bufp->chgBit(oldp+281,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[1]));
        bufp->chgBit(oldp+282,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[2]));
        bufp->chgBit(oldp+283,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[0]));
        bufp->chgBit(oldp+284,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[1]));
        bufp->chgBit(oldp+285,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[2]));
        bufp->chgCData(oldp+286,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[0]),2);
        bufp->chgCData(oldp+287,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[1]),2);
        bufp->chgCData(oldp+288,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[2]),2);
        bufp->chgBit(oldp+289,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[0]));
        bufp->chgBit(oldp+290,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[1]));
        bufp->chgBit(oldp+291,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[2]));
        bufp->chgBit(oldp+292,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0]));
        bufp->chgBit(oldp+293,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1]));
        bufp->chgBit(oldp+294,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2]));
        bufp->chgIData(oldp+295,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[0]),32);
        bufp->chgIData(oldp+296,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1]),32);
        bufp->chgIData(oldp+297,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2]),32);
        bufp->chgCData(oldp+298,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0]),2);
        bufp->chgCData(oldp+299,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1]),2);
        bufp->chgCData(oldp+300,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2]),2);
        bufp->chgBit(oldp+301,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0]));
        bufp->chgBit(oldp+302,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1]));
        bufp->chgBit(oldp+303,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2]));
        bufp->chgBit(oldp+304,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[0]));
        bufp->chgBit(oldp+305,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[1]));
        bufp->chgBit(oldp+306,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[2]));
        bufp->chgIData(oldp+307,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[0]),32);
        bufp->chgIData(oldp+308,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[1]),32);
        bufp->chgIData(oldp+309,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[2]),32);
        bufp->chgBit(oldp+310,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[0]));
        bufp->chgBit(oldp+311,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[1]));
        bufp->chgBit(oldp+312,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[2]));
        bufp->chgCData(oldp+313,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0]),2);
        bufp->chgCData(oldp+314,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1]),2);
        bufp->chgCData(oldp+315,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2]),2);
        bufp->chgBit(oldp+316,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0]));
        bufp->chgBit(oldp+317,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1]));
        bufp->chgBit(oldp+318,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2]));
        bufp->chgCData(oldp+319,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0]),2);
        bufp->chgCData(oldp+320,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1]),2);
        bufp->chgCData(oldp+321,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2]),2);
        bufp->chgCData(oldp+322,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0]),2);
        bufp->chgCData(oldp+323,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1]),2);
        bufp->chgCData(oldp+324,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2]),2);
        bufp->chgBit(oldp+325,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0]));
        bufp->chgBit(oldp+326,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1]));
        bufp->chgBit(oldp+327,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2]));
        bufp->chgCData(oldp+328,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0]),2);
        bufp->chgCData(oldp+329,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1]),2);
        bufp->chgCData(oldp+330,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2]),2);
    }
    bufp->chgBit(oldp+331,(vlSelf->crossbar_accel_tb__DOT__clk));
    bufp->chgBit(oldp+332,(vlSelf->crossbar_accel_tb__DOT__rst_n));
}

void Vcrossbar_accel_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_cleanup\n"); );
    // Init
    Vcrossbar_accel_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcrossbar_accel_tb___024root*>(voidSelf);
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[5U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[6U] = 0U;
}
