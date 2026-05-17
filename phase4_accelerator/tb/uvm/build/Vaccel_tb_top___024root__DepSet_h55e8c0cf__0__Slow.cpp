// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top___024root.h"

VL_ATTR_COLD void Vaccel_tb_top_uvm_mini_pkg___eval_static__TOP__uvm_mini_pkg(Vaccel_tb_top_uvm_mini_pkg* vlSelf);

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_static(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_static\n"); );
    // Body
    Vaccel_tb_top_uvm_mini_pkg___eval_static__TOP__uvm_mini_pkg((&vlSymsp->TOP__uvm_mini_pkg));
    vlSelf->__Vm_traceActivity[3U] = 1U;
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
}

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_initial__TOP(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->accel_tb_top__DOT__clk = 0U;
    vlSymsp->TOP__accel_tb_top__DOT__aif.rresp = 0U;
    vlSymsp->TOP__accel_tb_top__DOT__aif.arready = 1U;
    vlSymsp->TOP__accel_tb_top__DOT__aif.bresp = 0U;
    vlSymsp->TOP__accel_tb_top__DOT__aif.wready = 1U;
    vlSymsp->TOP__accel_tb_top__DOT__aif.awready = 1U;
    vlSelf->__VvifTrigger_h04376982__0 = 1U;
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccel_tb_top___024root___dump_triggers__stl(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaccel_tb_top___024root___eval_triggers__stl(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaccel_tb_top___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vaccel_tb_top___024root___stl_sequent__TOP__0(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___stl_sequent__TOP__0\n"); );
    // Body
    vlSymsp->TOP__accel_tb_top__DOT__aif.clk = vlSelf->accel_tb_top__DOT__clk;
    vlSymsp->TOP__accel_tb_top__DOT__aif.rvalid = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid;
    vlSymsp->TOP__accel_tb_top__DOT__aif.rdata = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata;
    vlSymsp->TOP__accel_tb_top__DOT__aif.bvalid = vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid;
    vlSelf->__VvifTrigger_h04376982__0 = 1U;
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
}
