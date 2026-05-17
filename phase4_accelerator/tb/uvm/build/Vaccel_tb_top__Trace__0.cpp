// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vaccel_tb_top__Syms.h"


void Vaccel_tb_top___024root__trace_chg_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vaccel_tb_top___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_chg_0\n"); );
    // Init
    Vaccel_tb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccel_tb_top___024root*>(voidSelf);
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vaccel_tb_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaccel_tb_top___024root__trace_chg_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[0U])) {
        bufp->chgIData(oldp+0,(vlSymsp->TOP__uvm_mini_pkg.g_error_count),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+1,(vlSymsp->TOP__accel_tb_top__DOT__aif.awready));
        bufp->chgBit(oldp+2,(vlSymsp->TOP__accel_tb_top__DOT__aif.wready));
        bufp->chgCData(oldp+3,(vlSymsp->TOP__accel_tb_top__DOT__aif.bresp),2);
        bufp->chgBit(oldp+4,(vlSymsp->TOP__accel_tb_top__DOT__aif.arready));
        bufp->chgCData(oldp+5,(vlSymsp->TOP__accel_tb_top__DOT__aif.rresp),2);
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[2U]))) {
        bufp->chgIData(oldp+6,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                               [0U][0U]),32);
        bufp->chgIData(oldp+7,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                               [0U][1U]),32);
        bufp->chgIData(oldp+8,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                               [0U][2U]),32);
        bufp->chgIData(oldp+9,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                               [0U][3U]),32);
        bufp->chgIData(oldp+10,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [1U][0U]),32);
        bufp->chgIData(oldp+11,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [1U][1U]),32);
        bufp->chgIData(oldp+12,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [1U][2U]),32);
        bufp->chgIData(oldp+13,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [1U][3U]),32);
        bufp->chgIData(oldp+14,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [2U][0U]),32);
        bufp->chgIData(oldp+15,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [2U][1U]),32);
        bufp->chgIData(oldp+16,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [2U][2U]),32);
        bufp->chgIData(oldp+17,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [2U][3U]),32);
        bufp->chgIData(oldp+18,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [3U][0U]),32);
        bufp->chgIData(oldp+19,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [3U][1U]),32);
        bufp->chgIData(oldp+20,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [3U][2U]),32);
        bufp->chgIData(oldp+21,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                                [3U][3U]),32);
        bufp->chgIData(oldp+22,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0]),32);
        bufp->chgIData(oldp+23,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1]),32);
        bufp->chgIData(oldp+24,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2]),32);
        bufp->chgIData(oldp+25,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3]),32);
        bufp->chgIData(oldp+26,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0]),32);
        bufp->chgIData(oldp+27,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1]),32);
        bufp->chgIData(oldp+28,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2]),32);
        bufp->chgIData(oldp+29,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3]),32);
        bufp->chgIData(oldp+30,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [0U][0U]),32);
        bufp->chgIData(oldp+31,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [0U][1U]),32);
        bufp->chgIData(oldp+32,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [0U][2U]),32);
        bufp->chgIData(oldp+33,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [0U][3U]),32);
        bufp->chgIData(oldp+34,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [1U][0U]),32);
        bufp->chgIData(oldp+35,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [1U][1U]),32);
        bufp->chgIData(oldp+36,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [1U][2U]),32);
        bufp->chgIData(oldp+37,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [1U][3U]),32);
        bufp->chgIData(oldp+38,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [2U][0U]),32);
        bufp->chgIData(oldp+39,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [2U][1U]),32);
        bufp->chgIData(oldp+40,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [2U][2U]),32);
        bufp->chgIData(oldp+41,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [2U][3U]),32);
        bufp->chgIData(oldp+42,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [3U][0U]),32);
        bufp->chgIData(oldp+43,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [3U][1U]),32);
        bufp->chgIData(oldp+44,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [3U][2U]),32);
        bufp->chgIData(oldp+45,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                                [3U][3U]),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgBit(oldp+46,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid));
        bufp->chgIData(oldp+47,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata),32);
        bufp->chgBit(oldp+48,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid));
        bufp->chgCData(oldp+49,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [0U][0U]),8);
        bufp->chgCData(oldp+50,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [0U][1U]),8);
        bufp->chgCData(oldp+51,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [0U][2U]),8);
        bufp->chgCData(oldp+52,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [0U][3U]),8);
        bufp->chgCData(oldp+53,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [1U][0U]),8);
        bufp->chgCData(oldp+54,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [1U][1U]),8);
        bufp->chgCData(oldp+55,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [1U][2U]),8);
        bufp->chgCData(oldp+56,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [1U][3U]),8);
        bufp->chgCData(oldp+57,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [2U][0U]),8);
        bufp->chgCData(oldp+58,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [2U][1U]),8);
        bufp->chgCData(oldp+59,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [2U][2U]),8);
        bufp->chgCData(oldp+60,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [2U][3U]),8);
        bufp->chgCData(oldp+61,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [3U][0U]),8);
        bufp->chgCData(oldp+62,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [3U][1U]),8);
        bufp->chgCData(oldp+63,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [3U][2U]),8);
        bufp->chgCData(oldp+64,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                                [3U][3U]),8);
        bufp->chgCData(oldp+65,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [0U][0U]),8);
        bufp->chgCData(oldp+66,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [0U][1U]),8);
        bufp->chgCData(oldp+67,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [0U][2U]),8);
        bufp->chgCData(oldp+68,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [0U][3U]),8);
        bufp->chgCData(oldp+69,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [1U][0U]),8);
        bufp->chgCData(oldp+70,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [1U][1U]),8);
        bufp->chgCData(oldp+71,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [1U][2U]),8);
        bufp->chgCData(oldp+72,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [1U][3U]),8);
        bufp->chgCData(oldp+73,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [2U][0U]),8);
        bufp->chgCData(oldp+74,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [2U][1U]),8);
        bufp->chgCData(oldp+75,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [2U][2U]),8);
        bufp->chgCData(oldp+76,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [2U][3U]),8);
        bufp->chgCData(oldp+77,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [3U][0U]),8);
        bufp->chgCData(oldp+78,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [3U][1U]),8);
        bufp->chgCData(oldp+79,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [3U][2U]),8);
        bufp->chgCData(oldp+80,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                [3U][3U]),8);
        bufp->chgIData(oldp+81,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [0U][0U]),32);
        bufp->chgIData(oldp+82,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [0U][1U]),32);
        bufp->chgIData(oldp+83,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [0U][2U]),32);
        bufp->chgIData(oldp+84,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [0U][3U]),32);
        bufp->chgIData(oldp+85,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [1U][0U]),32);
        bufp->chgIData(oldp+86,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [1U][1U]),32);
        bufp->chgIData(oldp+87,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [1U][2U]),32);
        bufp->chgIData(oldp+88,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [1U][3U]),32);
        bufp->chgIData(oldp+89,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [2U][0U]),32);
        bufp->chgIData(oldp+90,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [2U][1U]),32);
        bufp->chgIData(oldp+91,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [2U][2U]),32);
        bufp->chgIData(oldp+92,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [2U][3U]),32);
        bufp->chgIData(oldp+93,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [3U][0U]),32);
        bufp->chgIData(oldp+94,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [3U][1U]),32);
        bufp->chgIData(oldp+95,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [3U][2U]),32);
        bufp->chgIData(oldp+96,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                                [3U][3U]),32);
        bufp->chgBit(oldp+97,(vlSelf->accel_tb_top__DOT__dut__DOT__done_r));
        bufp->chgBit(oldp+98,(vlSelf->accel_tb_top__DOT__dut__DOT__start_r));
        bufp->chgCData(oldp+99,(vlSelf->accel_tb_top__DOT__dut__DOT__state),2);
        bufp->chgCData(oldp+100,(vlSelf->accel_tb_top__DOT__dut__DOT__cyc),3);
        bufp->chgCData(oldp+101,(((0U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                   ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                  [0U][0U] : ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                               ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [1U][0U]
                                               : ((2U 
                                                   == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                   ? 
                                                  vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                  [2U]
                                                  [0U]
                                                   : 
                                                  ((3U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+102,(((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                   ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                  [0U][1U] : ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                               ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [1U][1U]
                                               : ((3U 
                                                   == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                   ? 
                                                  vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                  [2U]
                                                  [1U]
                                                   : 
                                                  ((4U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+103,(((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                   ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                  [0U][2U] : ((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                               ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [1U][2U]
                                               : ((4U 
                                                   == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                   ? 
                                                  vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                  [2U]
                                                  [2U]
                                                   : 
                                                  ((5U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+104,(((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                   ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                  [0U][3U] : ((4U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                               ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                              [1U][3U]
                                               : ((5U 
                                                   == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                   ? 
                                                  vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                  [2U]
                                                  [3U]
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
        bufp->chgCData(oldp+105,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s),8);
        bufp->chgCData(oldp+106,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s),8);
        bufp->chgCData(oldp+107,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s),8);
        bufp->chgCData(oldp+108,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s),8);
        bufp->chgIData(oldp+109,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30),32);
        bufp->chgIData(oldp+110,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31),32);
        bufp->chgIData(oldp+111,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32),32);
        bufp->chgIData(oldp+112,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33),32);
        bufp->chgBit(oldp+113,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending));
        bufp->chgCData(oldp+114,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r),6);
        bufp->chgIData(oldp+115,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r),32);
        bufp->chgCData(oldp+116,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r),4);
        bufp->chgIData(oldp+117,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0),32);
        bufp->chgIData(oldp+118,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1),32);
        bufp->chgIData(oldp+119,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2),32);
        bufp->chgIData(oldp+120,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3),32);
        bufp->chgIData(oldp+121,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00),32);
        bufp->chgIData(oldp+122,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01),32);
        bufp->chgIData(oldp+123,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02),32);
        bufp->chgIData(oldp+124,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03),32);
        bufp->chgIData(oldp+125,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10),32);
        bufp->chgIData(oldp+126,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11),32);
        bufp->chgIData(oldp+127,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12),32);
        bufp->chgIData(oldp+128,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13),32);
        bufp->chgIData(oldp+129,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20),32);
        bufp->chgIData(oldp+130,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21),32);
        bufp->chgIData(oldp+131,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22),32);
        bufp->chgIData(oldp+132,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23),32);
        bufp->chgCData(oldp+133,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0)),8);
        bufp->chgSData(oldp+134,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product),16);
        bufp->chgCData(oldp+135,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                           >> 8U))),8);
        bufp->chgSData(oldp+136,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product),16);
        bufp->chgCData(oldp+137,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+138,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product),16);
        bufp->chgCData(oldp+139,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+140,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product),16);
        bufp->chgCData(oldp+141,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1)),8);
        bufp->chgSData(oldp+142,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product),16);
        bufp->chgCData(oldp+143,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                           >> 8U))),8);
        bufp->chgSData(oldp+144,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product),16);
        bufp->chgCData(oldp+145,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+146,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product),16);
        bufp->chgCData(oldp+147,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+148,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product),16);
        bufp->chgCData(oldp+149,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2)),8);
        bufp->chgSData(oldp+150,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product),16);
        bufp->chgCData(oldp+151,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                           >> 8U))),8);
        bufp->chgSData(oldp+152,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product),16);
        bufp->chgCData(oldp+153,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+154,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product),16);
        bufp->chgCData(oldp+155,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+156,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product),16);
        bufp->chgCData(oldp+157,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3)),8);
        bufp->chgSData(oldp+158,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product),16);
        bufp->chgCData(oldp+159,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                           >> 8U))),8);
        bufp->chgSData(oldp+160,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product),16);
        bufp->chgCData(oldp+161,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                           >> 0x10U))),8);
        bufp->chgSData(oldp+162,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product),16);
        bufp->chgCData(oldp+163,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                  >> 0x18U)),8);
        bufp->chgSData(oldp+164,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product),16);
        bufp->chgIData(oldp+165,(vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__i),32);
        bufp->chgIData(oldp+166,(vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
        bufp->chgBit(oldp+167,(vlSymsp->TOP__accel_tb_top__DOT__aif.bvalid));
        bufp->chgIData(oldp+168,(vlSymsp->TOP__accel_tb_top__DOT__aif.rdata),32);
        bufp->chgBit(oldp+169,(vlSymsp->TOP__accel_tb_top__DOT__aif.rvalid));
    }
    bufp->chgBit(oldp+170,(vlSelf->accel_tb_top__DOT__clk));
    bufp->chgBit(oldp+171,(vlSelf->accel_tb_top__DOT__rst_n));
    bufp->chgIData(oldp+172,(vlSelf->accel_tb_top__DOT__dut__DOT__rdata_comb),32);
    bufp->chgBit(oldp+173,(vlSymsp->TOP__accel_tb_top__DOT__aif.clk));
}

void Vaccel_tb_top___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_cleanup\n"); );
    // Init
    Vaccel_tb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccel_tb_top___024root*>(voidSelf);
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
