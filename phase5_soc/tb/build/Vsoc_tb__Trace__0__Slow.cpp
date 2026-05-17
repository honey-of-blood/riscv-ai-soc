// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vsoc_tb__Syms.h"


VL_ATTR_COLD void Vsoc_tb___024root__trace_init_sub__TOP__0(Vsoc_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("soc_tb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+467,0,"error_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+251,0,"y00_captured",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+252,0,"y33_captured",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+253,0,"y00_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+254,0,"y33_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::BIT, false,-1);
    tracep->declBit(c+468,0,"done_flag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+287,0,"imem_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"imem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+288,0,"dmem_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+289,0,"dmem_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+290,0,"dmem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+291,0,"dmem_we",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"dmem_re",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"dmem_stall",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+294,0,"dmem_be",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+295,0,"m0_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+296,0,"m0_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+295,0,"m0_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+297,0,"m0_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"m0_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+51,0,"m0_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+52,0,"m0_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+299,0,"m0_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+300,0,"m0_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+299,0,"m0_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+301,0,"m0_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+302,0,"m0_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+303,0,"m0_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+304,0,"m0_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+305,0,"m0_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+306,0,"m0_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+307,0,"m0_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m1_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+475,0,"m1_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+475,0,"m1_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+476,0,"m1_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+477,0,"m1_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+308,0,"m1_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+53,0,"m1_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+54,0,"m1_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+309,0,"m1_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+310,0,"m1_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+311,0,"m1_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+312,0,"m1_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+313,0,"m1_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m2_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+475,0,"m2_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+475,0,"m2_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+476,0,"m2_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+477,0,"m2_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+314,0,"m2_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+55,0,"m2_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+56,0,"m2_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+315,0,"m2_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+316,0,"m2_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+317,0,"m2_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+318,0,"m2_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+319,0,"m2_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+320,0,"s0_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+321,0,"s0_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+322,0,"s0_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+57,0,"s0_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+323,0,"s0_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+478,0,"s0_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+478,0,"s0_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+324,0,"s0_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+325,0,"s0_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"s0_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+326,0,"s0_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+327,0,"s0_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+59,0,"s0_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+328,0,"s0_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+329,0,"s1_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+330,0,"s1_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+331,0,"s1_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+60,0,"s1_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+332,0,"s1_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+478,0,"s1_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+478,0,"s1_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+333,0,"s1_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+334,0,"s1_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"s1_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+335,0,"s1_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"s1_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+62,0,"s1_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+337,0,"s1_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+338,0,"s2_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+339,0,"s2_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+340,0,"s2_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+63,0,"s2_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+341,0,"s2_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+478,0,"s2_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+478,0,"s2_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+342,0,"s2_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+343,0,"s2_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+64,0,"s2_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+344,0,"s2_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+345,0,"s2_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+65,0,"s2_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+346,0,"s2_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_accel", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+338,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+342,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+339,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+341,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+343,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+64,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+344,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+340,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+345,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+65,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+346,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("w_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+66,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+67,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+68,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+69,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+70,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+71,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+72,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+73,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+74,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+75,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+76,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+77,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+78,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+79,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+80,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+81,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("a_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+82,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+83,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+84,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+85,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+86,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+87,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+88,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+89,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+90,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+91,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+92,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+93,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+94,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+95,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+96,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+97,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("y_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+98,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+99,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+100,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+101,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+102,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+103,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+104,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+105,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+106,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+108,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+110,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+111,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+113,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->declBit(c+114,0,"done_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+115,0,"start_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+116,0,"state",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+117,0,"cyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+118,0,"af0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+119,0,"af1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+120,0,"af2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+121,0,"af3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"feed0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"feed1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"feed2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"feed3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+126,0,"y_out0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"y_out1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"y_out2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"y_out3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+347,0,"aw_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+130,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+131,0,"wr_idx_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+132,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+133,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+348,0,"ar_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+349,0,"rdata_comb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_array", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+134,0,"w_row0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+135,0,"w_row1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+136,0,"w_row2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+137,0,"w_row3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"a_feed0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"a_feed1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"a_feed2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"a_feed3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+126,0,"y_out0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"y_out1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"y_out2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"y_out3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+138,0,"ps00",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+139,0,"ps01",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+140,0,"ps02",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+141,0,"ps03",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+142,0,"ps10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+143,0,"ps11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+144,0,"ps12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+145,0,"ps13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"ps20",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"ps21",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+148,0,"ps22",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+149,0,"ps23",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+126,0,"ps30",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"ps31",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"ps32",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"ps33",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("r0c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+150,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+480,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+138,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+150,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+151,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+152,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+480,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+139,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+152,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+153,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+154,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+480,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+140,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+154,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+155,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+156,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+480,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+141,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+156,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+157,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+158,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+138,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+142,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+158,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+159,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+160,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+139,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+143,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+160,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+161,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+162,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+140,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+144,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+162,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+163,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+164,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+141,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+145,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+164,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+165,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+166,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+142,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+166,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+167,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+168,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+143,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+147,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+168,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+169,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+170,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+144,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+148,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+170,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+171,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+172,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+145,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+149,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+172,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+173,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+174,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+146,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+126,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+174,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+175,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+176,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+147,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+176,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+177,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+178,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+148,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+178,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+179,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+180,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+149,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+180,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+181,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+182,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("unnamedblk2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+183,0,"j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_adapter", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"cpu_re_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+291,0,"cpu_we_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+288,0,"cpu_addr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+289,0,"cpu_wdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+294,0,"cpu_be_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+290,0,"cpu_rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+293,0,"cpu_stall_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+295,0,"m_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+299,0,"m_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+300,0,"m_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+296,0,"m_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"m_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+299,0,"m_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+301,0,"m_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+51,0,"m_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+302,0,"m_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+303,0,"m_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+295,0,"m_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+304,0,"m_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+305,0,"m_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+297,0,"m_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"m_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+306,0,"m_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+307,0,"m_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+350,0,"state",2, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+295,0,"addr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+296,0,"wdata_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"wstrb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_cpu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+287,0,"imem_addr_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"imem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+288,0,"dmem_addr_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+289,0,"dmem_wdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+291,0,"dmem_we_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"dmem_re_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+294,0,"dmem_be_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+290,0,"dmem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+293,0,"dmem_stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_if",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+352,0,"flush_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+353,0,"flush_ex",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_id_ex",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_ex_mem",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_mem_wb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+354,0,"branch_taken",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+470,0,"branch_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"wb_reg_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+355,0,"wb_rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+356,0,"wb_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"reg_write_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+357,0,"rd_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+288,0,"alu_result_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"reg_write_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+355,0,"rd_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+287,0,"pc_f",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"instr_f",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+358,0,"instr_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+359,0,"rs1_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+471,0,"rf_rd1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rf_rd2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+361,0,"rd_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+362,0,"funct3_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+471,0,"rs1_data_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rs2_data_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+363,0,"imm_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_d_dec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+364,0,"reg_write_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+365,0,"mem_read_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+366,0,"mem_write_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+367,0,"alu_src_a_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+368,0,"alu_src_b_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+369,0,"branch_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+370,0,"jump_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+371,0,"alu_ctrl_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+372,0,"wb_sel_d",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+187,0,"reg_write_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"mem_read_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"mem_write_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"alu_src_a_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"alu_src_b_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"branch_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"jump_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"alu_ctrl_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+193,0,"wb_sel_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"funct3_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rs1_data_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+195,0,"rs2_data_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"imm_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+197,0,"pc_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+198,0,"rs1_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+199,0,"rs2_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+376,0,"rd_e",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+377,0,"fwd_ex_mem_val",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+378,0,"fwd_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+379,0,"fwd_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+380,0,"ex_alu_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+381,0,"ex_rs2_fwd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+200,0,"ex_pc_plus4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"ex_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+187,0,"ex_reg_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"ex_mem_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"ex_mem_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+193,0,"ex_wb_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"ex_funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+376,0,"ex_rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+382,0,"rs2_data_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"pc_plus4_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"imm_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+292,0,"mem_read_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+291,0,"mem_write_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"wb_sel_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+383,0,"funct3_m",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+288,0,"m_alu_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+384,0,"m_mem_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"m_pc_plus4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"m_imm",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"m_reg_write",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"m_wb_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+357,0,"m_rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+204,0,"alu_result_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+205,0,"mem_rdata_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+206,0,"pc_plus4_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+207,0,"imm_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+208,0,"wb_sel_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->pushPrefix("u_decode", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+358,0,"instr_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+471,0,"rs1_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rs2_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+359,0,"rs1_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+361,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+362,0,"funct3_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+471,0,"rs1_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rs2_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+363,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+364,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+365,0,"mem_read_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+366,0,"mem_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+368,0,"alu_src_b_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+367,0,"alu_src_a_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+369,0,"branch_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+370,0,"jump_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+371,0,"alu_ctrl_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+372,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+481,0,"OP_R",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+482,0,"OP_IMM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+483,0,"OP_LOAD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+484,0,"OP_STORE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+485,0,"OP_BRANCH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+486,0,"OP_JAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+487,0,"OP_JALR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+488,0,"OP_LUI",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+489,0,"OP_AUIPC",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+476,0,"ALU_ADD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+490,0,"ALU_SUB",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+491,0,"ALU_AND",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+492,0,"ALU_OR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+493,0,"ALU_XOR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+494,0,"ALU_SLL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+495,0,"ALU_SRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+496,0,"ALU_SRA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+497,0,"ALU_SLT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+498,0,"ALU_SLTU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+478,0,"WB_ALU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+499,0,"WB_MEM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+500,0,"WB_PC4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+501,0,"WB_IMM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+385,0,"opcode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+359,0,"rs1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+361,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+362,0,"funct3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+386,0,"funct7_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_imm_gen", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+358,0,"instr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+363,0,"imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+483,0,"OP_LOAD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+482,0,"OP_IMM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+487,0,"OP_JALR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+502,0,"OP_SYSTEM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+484,0,"OP_STORE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+485,0,"OP_BRANCH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+488,0,"OP_LUI",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+489,0,"OP_AUIPC",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+486,0,"OP_JAL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+385,0,"opcode",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declBus(c+387,0,"imm_i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+388,0,"imm_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+389,0,"imm_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+390,0,"imm_u",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+391,0,"imm_j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_ex_mem", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+380,0,"alu_result_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+381,0,"rs2_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+200,0,"pc_plus4_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+187,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"mem_read_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"mem_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+193,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"funct3_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+376,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+288,0,"alu_result_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+382,0,"rs2_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"pc_plus4_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"mem_read_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+291,0,"mem_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+383,0,"funct3_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+357,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_execute", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+187,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"mem_read_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"mem_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"alu_src_b_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"alu_src_a_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"branch_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"jump_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"alu_ctrl_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+193,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"funct3_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rs1_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+195,0,"rs2_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+197,0,"pc_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+376,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+378,0,"fwd_a_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+379,0,"fwd_b_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+377,0,"fwd_ex_mem_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+356,0,"fwd_mem_wb_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+380,0,"alu_result_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+381,0,"rs2_fwd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+200,0,"pc_plus4_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+187,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"mem_read_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"mem_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+193,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"funct3_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+376,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+354,0,"branch_taken_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+470,0,"branch_target_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+392,0,"rs1_fwd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+381,0,"rs2_fwd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+393,0,"alu_a",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+394,0,"alu_b",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+380,0,"alu_result",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+395,0,"alu_zero",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+392,0,"rs1_sgn",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+381,0,"rs2_sgn",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+396,0,"branch_cond",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+209,0,"branch_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+473,0,"jump_target",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_alu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+393,0,"a",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+394,0,"b",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+192,0,"alu_ctrl",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+380,0,"result",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+395,0,"zero",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+476,0,"ALU_ADD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+490,0,"ALU_SUB",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+491,0,"ALU_AND",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+492,0,"ALU_OR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+493,0,"ALU_XOR",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+494,0,"ALU_SLL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+495,0,"ALU_SRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+496,0,"ALU_SRA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+497,0,"ALU_SLT",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+498,0,"ALU_SLTU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+397,0,"shamt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_fetch", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+354,0,"branch_taken_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+470,0,"branch_target_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+287,0,"imem_addr_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"imem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+287,0,"pc_if_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"instr_if_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+287,0,"pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+474,0,"pc_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_fwd", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+198,0,"rs1_ex_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+199,0,"rs2_ex_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+357,0,"rd_mem_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+185,0,"reg_write_mem_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+355,0,"rd_wb_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+184,0,"reg_write_wb_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+378,0,"fwd_a_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+379,0,"fwd_b_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_hazard", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+373,0,"mem_read_ex_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+376,0,"rd_ex_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+359,0,"rs1_id_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2_id_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+354,0,"branch_taken_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"cache_stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_if_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_id_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_id_ex_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_ex_mem_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_mem_wb_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+352,0,"flush_id_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+353,0,"flush_ex_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+398,0,"load_use",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_id_ex", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+353,0,"flush_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+364,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+365,0,"mem_read_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+366,0,"mem_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+368,0,"alu_src_b_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+367,0,"alu_src_a_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+369,0,"branch_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+370,0,"jump_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+371,0,"alu_ctrl_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+372,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+362,0,"funct3_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+471,0,"rs1_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rs2_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+363,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+359,0,"rs1_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+361,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+187,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+373,0,"mem_read_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+374,0,"mem_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"alu_src_b_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"alu_src_a_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"branch_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"jump_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"alu_ctrl_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+193,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+375,0,"funct3_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rs1_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+195,0,"rs2_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+197,0,"pc_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+198,0,"rs1_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+199,0,"rs2_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+376,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_if_id", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+351,0,"stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+352,0,"flush_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+287,0,"pc_if_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"instr_if_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"pc_id_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+358,0,"instr_id_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+503,0,"NOP",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_mem_wb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+293,0,"stall_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+288,0,"alu_result_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+384,0,"mem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"pc_plus4_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+357,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+204,0,"alu_result_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+205,0,"mem_rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+206,0,"pc_plus4_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+207,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+208,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+355,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_memory", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+288,0,"alu_result_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+382,0,"rs2_data_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"pc_plus4_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"mem_read_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+291,0,"mem_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+383,0,"funct3_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+357,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+288,0,"dmem_addr_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+289,0,"dmem_wdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+291,0,"dmem_we_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+292,0,"dmem_re_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+294,0,"dmem_be_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+290,0,"dmem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+288,0,"alu_result_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+384,0,"mem_rdata_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"pc_plus4_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"imm_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+185,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+203,0,"wb_sel_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+357,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+399,0,"byte_off",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+400,0,"half_off",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+401,0,"rs2_byte",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+402,0,"rs2_half",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+403,0,"funct3_w",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+404,0,"rdata_b0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+405,0,"rdata_b1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+406,0,"rdata_b2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+407,0,"rdata_b3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+408,0,"rdata_lo",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+409,0,"rdata_hi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+410,0,"rd_byte",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+411,0,"rd_half",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+412,0,"rd_byte_msb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+413,0,"rd_half_msb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("u_regfile", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+469,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+414,0,"we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+359,0,"rs1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+360,0,"rs2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+355,0,"rd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+356,0,"wd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+471,0,"rd1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+472,0,"rd2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("regs", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 31; ++i) {
        tracep->declBus(c+255+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+1), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+286,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_writeback", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+204,0,"alu_result_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+205,0,"mem_rdata_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+206,0,"pc_plus4_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+207,0,"imm_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"reg_write_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+208,0,"wb_sel_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+355,0,"rd_i",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+356,0,"wb_data_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"reg_write_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+355,0,"rd_o",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+478,0,"WB_ALU",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+499,0,"WB_MEM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+500,0,"WB_PC4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+501,0,"WB_IMM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_irom", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+504,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+287,0,"addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+415,0,"word_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_sram0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+505,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+320,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+324,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+321,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+323,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+325,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+58,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+326,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+322,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+327,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+57,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+59,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+328,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+506,0,"AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+416,0,"aw_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBit(c+210,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+211,0,"wr_addr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBus(c+212,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+213,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+417,0,"ar_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_sram1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+505,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+329,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+333,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+330,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+332,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+334,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+61,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+335,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+331,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+60,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+62,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+337,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+506,0,"AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+418,0,"aw_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBit(c+214,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+215,0,"wr_addr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBus(c+216,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+217,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+419,0,"ar_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_xbar", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+465,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+466,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+295,0,"m0_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+299,0,"m0_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+300,0,"m0_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+296,0,"m0_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+298,0,"m0_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+299,0,"m0_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+301,0,"m0_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+51,0,"m0_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+302,0,"m0_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+303,0,"m0_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+295,0,"m0_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+304,0,"m0_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+305,0,"m0_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+297,0,"m0_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"m0_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+306,0,"m0_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+307,0,"m0_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m1_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+477,0,"m1_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+309,0,"m1_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m1_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+476,0,"m1_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+477,0,"m1_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+310,0,"m1_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+53,0,"m1_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+311,0,"m1_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m1_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+477,0,"m1_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+312,0,"m1_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+308,0,"m1_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+54,0,"m1_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+313,0,"m1_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m1_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m2_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+477,0,"m2_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+315,0,"m2_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m2_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+476,0,"m2_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+477,0,"m2_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+316,0,"m2_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+55,0,"m2_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+317,0,"m2_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+475,0,"m2_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+477,0,"m2_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+318,0,"m2_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+314,0,"m2_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+56,0,"m2_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+319,0,"m2_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+477,0,"m2_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+320,0,"s0_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+324,0,"s0_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+321,0,"s0_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+323,0,"s0_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+325,0,"s0_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s0_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+58,0,"s0_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+326,0,"s0_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+322,0,"s0_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+327,0,"s0_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s0_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+57,0,"s0_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s0_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+59,0,"s0_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+328,0,"s0_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+329,0,"s1_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+333,0,"s1_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+330,0,"s1_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+332,0,"s1_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+334,0,"s1_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s1_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+61,0,"s1_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+335,0,"s1_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+331,0,"s1_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"s1_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s1_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+60,0,"s1_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s1_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+62,0,"s1_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+337,0,"s1_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+338,0,"s2_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+342,0,"s2_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+339,0,"s2_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+341,0,"s2_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+343,0,"s2_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+478,0,"s2_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+64,0,"s2_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+344,0,"s2_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+340,0,"s2_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+345,0,"s2_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+479,0,"s2_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"s2_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+478,0,"s2_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+65,0,"s2_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+346,0,"s2_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("m_awaddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+18+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+21+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+420+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+24+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wstrb", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+27+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 3,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+30+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+423+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+218+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+426+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+33+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_araddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+36+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_arvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+39+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_arready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+429+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+432+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+221+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+435+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+42+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awaddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+438+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+441+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+1+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+444+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wstrb", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+447+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 3,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+450+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+4+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_bresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+7+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_bvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+224+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_bready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+453+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_araddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+456+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_arvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+459+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_arready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+10+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+227+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+13+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+230+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+462+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awdec", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+45+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_ardec", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+48+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_grant", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+233+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_busy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+236+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_last", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+239+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_grant", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+242+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_busy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+245+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_last", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+248+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+16,0,"s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_init_top(Vsoc_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_init_top\n"); );
    // Body
    Vsoc_tb___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vsoc_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vsoc_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vsoc_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vsoc_tb___024root__trace_register(Vsoc_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&Vsoc_tb___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vsoc_tb___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vsoc_tb___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vsoc_tb___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_const_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vsoc_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_const_0\n"); );
    // Init
    Vsoc_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_tb___024root*>(voidSelf);
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vsoc_tb___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_const_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_const_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+475,(0U),32);
    bufp->fullCData(oldp+476,(0U),4);
    bufp->fullBit(oldp+477,(0U));
    bufp->fullCData(oldp+478,(0U),2);
    bufp->fullBit(oldp+479,(1U));
    bufp->fullIData(oldp+480,(0U),32);
    bufp->fullCData(oldp+481,(0x33U),7);
    bufp->fullCData(oldp+482,(0x13U),7);
    bufp->fullCData(oldp+483,(3U),7);
    bufp->fullCData(oldp+484,(0x23U),7);
    bufp->fullCData(oldp+485,(0x63U),7);
    bufp->fullCData(oldp+486,(0x6fU),7);
    bufp->fullCData(oldp+487,(0x67U),7);
    bufp->fullCData(oldp+488,(0x37U),7);
    bufp->fullCData(oldp+489,(0x17U),7);
    bufp->fullCData(oldp+490,(1U),4);
    bufp->fullCData(oldp+491,(2U),4);
    bufp->fullCData(oldp+492,(3U),4);
    bufp->fullCData(oldp+493,(4U),4);
    bufp->fullCData(oldp+494,(5U),4);
    bufp->fullCData(oldp+495,(6U),4);
    bufp->fullCData(oldp+496,(7U),4);
    bufp->fullCData(oldp+497,(8U),4);
    bufp->fullCData(oldp+498,(9U),4);
    bufp->fullCData(oldp+499,(1U),2);
    bufp->fullCData(oldp+500,(2U),2);
    bufp->fullCData(oldp+501,(3U),2);
    bufp->fullCData(oldp+502,(0x73U),7);
    bufp->fullIData(oldp+503,(0x13U),32);
    bufp->fullIData(oldp+504,(0x200U),32);
    bufp->fullIData(oldp+505,(0x4000U),32);
    bufp->fullIData(oldp+506,(0xeU),32);
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_full_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vsoc_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_full_0\n"); );
    // Init
    Vsoc_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsoc_tb___024root*>(voidSelf);
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vsoc_tb___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vsoc_tb___024root__trace_full_0_sub_0(Vsoc_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vsoc_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsoc_tb___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[0]));
    bufp->fullBit(oldp+2,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[1]));
    bufp->fullBit(oldp+3,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awready[2]));
    bufp->fullBit(oldp+4,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[0]));
    bufp->fullBit(oldp+5,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[1]));
    bufp->fullBit(oldp+6,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wready[2]));
    bufp->fullCData(oldp+7,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[0]),2);
    bufp->fullCData(oldp+8,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[1]),2);
    bufp->fullCData(oldp+9,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bresp[2]),2);
    bufp->fullBit(oldp+10,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[0]));
    bufp->fullBit(oldp+11,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[1]));
    bufp->fullBit(oldp+12,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arready[2]));
    bufp->fullCData(oldp+13,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[0]),2);
    bufp->fullCData(oldp+14,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[1]),2);
    bufp->fullCData(oldp+15,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rresp[2]),2);
    bufp->fullIData(oldp+16,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s),32);
    bufp->fullIData(oldp+17,(vlSelf->soc_tb__DOT__dut__DOT__u_irom__DOT__mem
                             [(0x1ffU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                                         >> 2U))]),32);
    bufp->fullIData(oldp+18,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[0]),32);
    bufp->fullIData(oldp+19,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[1]),32);
    bufp->fullIData(oldp+20,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awaddr[2]),32);
    bufp->fullBit(oldp+21,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[0]));
    bufp->fullBit(oldp+22,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[1]));
    bufp->fullBit(oldp+23,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awvalid[2]));
    bufp->fullIData(oldp+24,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[0]),32);
    bufp->fullIData(oldp+25,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[1]),32);
    bufp->fullIData(oldp+26,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wdata[2]),32);
    bufp->fullCData(oldp+27,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[0]),4);
    bufp->fullCData(oldp+28,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[1]),4);
    bufp->fullCData(oldp+29,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wstrb[2]),4);
    bufp->fullBit(oldp+30,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[0]));
    bufp->fullBit(oldp+31,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[1]));
    bufp->fullBit(oldp+32,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wvalid[2]));
    bufp->fullBit(oldp+33,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[0]));
    bufp->fullBit(oldp+34,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[1]));
    bufp->fullBit(oldp+35,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bready[2]));
    bufp->fullIData(oldp+36,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[0]),32);
    bufp->fullIData(oldp+37,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[1]),32);
    bufp->fullIData(oldp+38,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_araddr[2]),32);
    bufp->fullBit(oldp+39,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[0]));
    bufp->fullBit(oldp+40,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[1]));
    bufp->fullBit(oldp+41,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arvalid[2]));
    bufp->fullBit(oldp+42,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[0]));
    bufp->fullBit(oldp+43,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[1]));
    bufp->fullBit(oldp+44,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rready[2]));
    bufp->fullCData(oldp+45,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[0]),2);
    bufp->fullCData(oldp+46,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[1]),2);
    bufp->fullCData(oldp+47,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awdec[2]),2);
    bufp->fullCData(oldp+48,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[0]),2);
    bufp->fullCData(oldp+49,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[1]),2);
    bufp->fullCData(oldp+50,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_ardec[2]),2);
    bufp->fullCData(oldp+51,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                             [0U]),2);
    bufp->fullCData(oldp+52,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                             [0U]),2);
    bufp->fullCData(oldp+53,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                             [1U]),2);
    bufp->fullCData(oldp+54,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                             [1U]),2);
    bufp->fullCData(oldp+55,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp
                             [2U]),2);
    bufp->fullCData(oldp+56,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp
                             [2U]),2);
    bufp->fullIData(oldp+57,(vlSelf->soc_tb__DOT__dut__DOT__s0_rdata),32);
    bufp->fullBit(oldp+58,(vlSelf->soc_tb__DOT__dut__DOT__s0_bvalid));
    bufp->fullBit(oldp+59,(vlSelf->soc_tb__DOT__dut__DOT__s0_rvalid));
    bufp->fullIData(oldp+60,(vlSelf->soc_tb__DOT__dut__DOT__s1_rdata),32);
    bufp->fullBit(oldp+61,(vlSelf->soc_tb__DOT__dut__DOT__s1_bvalid));
    bufp->fullBit(oldp+62,(vlSelf->soc_tb__DOT__dut__DOT__s1_rvalid));
    bufp->fullIData(oldp+63,(vlSelf->soc_tb__DOT__dut__DOT__s2_rdata),32);
    bufp->fullBit(oldp+64,(vlSelf->soc_tb__DOT__dut__DOT__s2_bvalid));
    bufp->fullBit(oldp+65,(vlSelf->soc_tb__DOT__dut__DOT__s2_rvalid));
    bufp->fullCData(oldp+66,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [0U][0U]),8);
    bufp->fullCData(oldp+67,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [0U][1U]),8);
    bufp->fullCData(oldp+68,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [0U][2U]),8);
    bufp->fullCData(oldp+69,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [0U][3U]),8);
    bufp->fullCData(oldp+70,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [1U][0U]),8);
    bufp->fullCData(oldp+71,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [1U][1U]),8);
    bufp->fullCData(oldp+72,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [1U][2U]),8);
    bufp->fullCData(oldp+73,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [1U][3U]),8);
    bufp->fullCData(oldp+74,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [2U][0U]),8);
    bufp->fullCData(oldp+75,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [2U][1U]),8);
    bufp->fullCData(oldp+76,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [2U][2U]),8);
    bufp->fullCData(oldp+77,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [2U][3U]),8);
    bufp->fullCData(oldp+78,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [3U][0U]),8);
    bufp->fullCData(oldp+79,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [3U][1U]),8);
    bufp->fullCData(oldp+80,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [3U][2U]),8);
    bufp->fullCData(oldp+81,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__w_reg
                             [3U][3U]),8);
    bufp->fullCData(oldp+82,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [0U][0U]),8);
    bufp->fullCData(oldp+83,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [0U][1U]),8);
    bufp->fullCData(oldp+84,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [0U][2U]),8);
    bufp->fullCData(oldp+85,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [0U][3U]),8);
    bufp->fullCData(oldp+86,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [1U][0U]),8);
    bufp->fullCData(oldp+87,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [1U][1U]),8);
    bufp->fullCData(oldp+88,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [1U][2U]),8);
    bufp->fullCData(oldp+89,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [1U][3U]),8);
    bufp->fullCData(oldp+90,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [2U][0U]),8);
    bufp->fullCData(oldp+91,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [2U][1U]),8);
    bufp->fullCData(oldp+92,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [2U][2U]),8);
    bufp->fullCData(oldp+93,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [2U][3U]),8);
    bufp->fullCData(oldp+94,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [3U][0U]),8);
    bufp->fullCData(oldp+95,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [3U][1U]),8);
    bufp->fullCData(oldp+96,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [3U][2U]),8);
    bufp->fullCData(oldp+97,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                             [3U][3U]),8);
    bufp->fullIData(oldp+98,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                             [0U][0U]),32);
    bufp->fullIData(oldp+99,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                             [0U][1U]),32);
    bufp->fullIData(oldp+100,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [0U][2U]),32);
    bufp->fullIData(oldp+101,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [0U][3U]),32);
    bufp->fullIData(oldp+102,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [1U][0U]),32);
    bufp->fullIData(oldp+103,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [1U][1U]),32);
    bufp->fullIData(oldp+104,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [1U][2U]),32);
    bufp->fullIData(oldp+105,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [1U][3U]),32);
    bufp->fullIData(oldp+106,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [2U][0U]),32);
    bufp->fullIData(oldp+107,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [2U][1U]),32);
    bufp->fullIData(oldp+108,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [2U][2U]),32);
    bufp->fullIData(oldp+109,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [2U][3U]),32);
    bufp->fullIData(oldp+110,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [3U][0U]),32);
    bufp->fullIData(oldp+111,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [3U][1U]),32);
    bufp->fullIData(oldp+112,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [3U][2U]),32);
    bufp->fullIData(oldp+113,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__y_reg
                              [3U][3U]),32);
    bufp->fullBit(oldp+114,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__done_r));
    bufp->fullBit(oldp+115,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__start_r));
    bufp->fullCData(oldp+116,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__state),2);
    bufp->fullCData(oldp+117,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc),3);
    bufp->fullCData(oldp+118,(((0U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                               [0U][0U] : ((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                           [1U][0U]
                                            : ((2U 
                                                == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                               [2U]
                                               [0U]
                                                : (
                                                   (3U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+119,(((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                               [0U][1U] : ((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                           [1U][1U]
                                            : ((3U 
                                                == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                               [2U]
                                               [1U]
                                                : (
                                                   (4U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+120,(((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                               [0U][2U] : ((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                           [1U][2U]
                                            : ((4U 
                                                == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                               [2U]
                                               [2U]
                                                : (
                                                   (5U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+121,(((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                               [0U][3U] : ((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                            ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                           [1U][3U]
                                            : ((5U 
                                                == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                ? vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                               [2U]
                                               [3U]
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+122,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__a_s),8);
    bufp->fullCData(oldp+123,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__a_s),8);
    bufp->fullCData(oldp+124,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__a_s),8);
    bufp->fullCData(oldp+125,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__a_s),8);
    bufp->fullIData(oldp+126,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps30),32);
    bufp->fullIData(oldp+127,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps31),32);
    bufp->fullIData(oldp+128,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps32),32);
    bufp->fullIData(oldp+129,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps33),32);
    bufp->fullBit(oldp+130,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_pending));
    bufp->fullCData(oldp+131,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_idx_r),6);
    bufp->fullIData(oldp+132,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_data_r),32);
    bufp->fullCData(oldp+133,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__wr_strb_r),4);
    bufp->fullIData(oldp+134,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0),32);
    bufp->fullIData(oldp+135,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1),32);
    bufp->fullIData(oldp+136,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2),32);
    bufp->fullIData(oldp+137,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3),32);
    bufp->fullIData(oldp+138,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps00),32);
    bufp->fullIData(oldp+139,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps01),32);
    bufp->fullIData(oldp+140,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps02),32);
    bufp->fullIData(oldp+141,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps03),32);
    bufp->fullIData(oldp+142,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps10),32);
    bufp->fullIData(oldp+143,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps11),32);
    bufp->fullIData(oldp+144,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps12),32);
    bufp->fullIData(oldp+145,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps13),32);
    bufp->fullIData(oldp+146,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps20),32);
    bufp->fullIData(oldp+147,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps21),32);
    bufp->fullIData(oldp+148,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps22),32);
    bufp->fullIData(oldp+149,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__ps23),32);
    bufp->fullCData(oldp+150,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0)),8);
    bufp->fullSData(oldp+151,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c0__DOT__product),16);
    bufp->fullCData(oldp+152,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                        >> 8U))),8);
    bufp->fullSData(oldp+153,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c1__DOT__product),16);
    bufp->fullCData(oldp+154,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+155,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c2__DOT__product),16);
    bufp->fullCData(oldp+156,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row0 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+157,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r0c3__DOT__product),16);
    bufp->fullCData(oldp+158,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1)),8);
    bufp->fullSData(oldp+159,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c0__DOT__product),16);
    bufp->fullCData(oldp+160,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                        >> 8U))),8);
    bufp->fullSData(oldp+161,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c1__DOT__product),16);
    bufp->fullCData(oldp+162,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+163,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c2__DOT__product),16);
    bufp->fullCData(oldp+164,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row1 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+165,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r1c3__DOT__product),16);
    bufp->fullCData(oldp+166,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2)),8);
    bufp->fullSData(oldp+167,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c0__DOT__product),16);
    bufp->fullCData(oldp+168,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                        >> 8U))),8);
    bufp->fullSData(oldp+169,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c1__DOT__product),16);
    bufp->fullCData(oldp+170,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+171,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c2__DOT__product),16);
    bufp->fullCData(oldp+172,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row2 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+173,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r2c3__DOT__product),16);
    bufp->fullCData(oldp+174,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3)),8);
    bufp->fullSData(oldp+175,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c0__DOT__product),16);
    bufp->fullCData(oldp+176,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                        >> 8U))),8);
    bufp->fullSData(oldp+177,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c1__DOT__product),16);
    bufp->fullCData(oldp+178,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+179,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c2__DOT__product),16);
    bufp->fullCData(oldp+180,((vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT____Vcellinp__u_array__w_row3 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+181,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__u_array__DOT__r3c3__DOT__product),16);
    bufp->fullIData(oldp+182,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__i),32);
    bufp->fullIData(oldp+183,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
    bufp->fullBit(oldp+184,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_w));
    bufp->fullBit(oldp+185,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_m));
    bufp->fullIData(oldp+186,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_d),32);
    bufp->fullBit(oldp+187,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_e));
    bufp->fullBit(oldp+188,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e));
    bufp->fullBit(oldp+189,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_e));
    bufp->fullBit(oldp+190,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_e));
    bufp->fullBit(oldp+191,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e));
    bufp->fullCData(oldp+192,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_ctrl_e),4);
    bufp->fullCData(oldp+193,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_e),2);
    bufp->fullIData(oldp+194,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_data_e),32);
    bufp->fullIData(oldp+195,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_e),32);
    bufp->fullIData(oldp+196,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e),32);
    bufp->fullIData(oldp+197,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e),32);
    bufp->fullCData(oldp+198,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs1_e),5);
    bufp->fullCData(oldp+199,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_e),5);
    bufp->fullIData(oldp+200,(((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e)),32);
    bufp->fullIData(oldp+201,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_m),32);
    bufp->fullIData(oldp+202,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_m),32);
    bufp->fullCData(oldp+203,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_m),2);
    bufp->fullIData(oldp+204,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_w),32);
    bufp->fullIData(oldp+205,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_rdata_w),32);
    bufp->fullIData(oldp+206,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_plus4_w),32);
    bufp->fullIData(oldp+207,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_w),32);
    bufp->fullCData(oldp+208,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_w),2);
    bufp->fullIData(oldp+209,((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                               + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e)),32);
    bufp->fullBit(oldp+210,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_pending));
    bufp->fullSData(oldp+211,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_addr_r),14);
    bufp->fullIData(oldp+212,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_data_r),32);
    bufp->fullCData(oldp+213,(vlSelf->soc_tb__DOT__dut__DOT__u_sram0__DOT__wr_strb_r),4);
    bufp->fullBit(oldp+214,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_pending));
    bufp->fullSData(oldp+215,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_addr_r),14);
    bufp->fullIData(oldp+216,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_data_r),32);
    bufp->fullCData(oldp+217,(vlSelf->soc_tb__DOT__dut__DOT__u_sram1__DOT__wr_strb_r),4);
    bufp->fullCData(oldp+218,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[0]),2);
    bufp->fullCData(oldp+219,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[1]),2);
    bufp->fullCData(oldp+220,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bresp[2]),2);
    bufp->fullCData(oldp+221,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[0]),2);
    bufp->fullCData(oldp+222,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[1]),2);
    bufp->fullCData(oldp+223,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rresp[2]),2);
    bufp->fullBit(oldp+224,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[0]));
    bufp->fullBit(oldp+225,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[1]));
    bufp->fullBit(oldp+226,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bvalid[2]));
    bufp->fullIData(oldp+227,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[0]),32);
    bufp->fullIData(oldp+228,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[1]),32);
    bufp->fullIData(oldp+229,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rdata[2]),32);
    bufp->fullBit(oldp+230,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[0]));
    bufp->fullBit(oldp+231,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[1]));
    bufp->fullBit(oldp+232,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rvalid[2]));
    bufp->fullCData(oldp+233,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[0]),2);
    bufp->fullCData(oldp+234,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[1]),2);
    bufp->fullCData(oldp+235,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_grant[2]),2);
    bufp->fullBit(oldp+236,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[0]));
    bufp->fullBit(oldp+237,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[1]));
    bufp->fullBit(oldp+238,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_busy[2]));
    bufp->fullCData(oldp+239,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[0]),2);
    bufp->fullCData(oldp+240,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[1]),2);
    bufp->fullCData(oldp+241,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__wr_last[2]),2);
    bufp->fullCData(oldp+242,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[0]),2);
    bufp->fullCData(oldp+243,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[1]),2);
    bufp->fullCData(oldp+244,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_grant[2]),2);
    bufp->fullBit(oldp+245,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[0]));
    bufp->fullBit(oldp+246,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[1]));
    bufp->fullBit(oldp+247,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_busy[2]));
    bufp->fullCData(oldp+248,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[0]),2);
    bufp->fullCData(oldp+249,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[1]),2);
    bufp->fullCData(oldp+250,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__rd_last[2]),2);
    bufp->fullIData(oldp+251,(vlSelf->soc_tb__DOT__y00_captured),32);
    bufp->fullIData(oldp+252,(vlSelf->soc_tb__DOT__y33_captured),32);
    bufp->fullBit(oldp+253,(vlSelf->soc_tb__DOT__y00_valid));
    bufp->fullBit(oldp+254,(vlSelf->soc_tb__DOT__y33_valid));
    bufp->fullIData(oldp+255,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[0]),32);
    bufp->fullIData(oldp+256,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[1]),32);
    bufp->fullIData(oldp+257,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[2]),32);
    bufp->fullIData(oldp+258,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[3]),32);
    bufp->fullIData(oldp+259,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[4]),32);
    bufp->fullIData(oldp+260,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[5]),32);
    bufp->fullIData(oldp+261,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[6]),32);
    bufp->fullIData(oldp+262,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[7]),32);
    bufp->fullIData(oldp+263,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[8]),32);
    bufp->fullIData(oldp+264,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[9]),32);
    bufp->fullIData(oldp+265,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[10]),32);
    bufp->fullIData(oldp+266,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[11]),32);
    bufp->fullIData(oldp+267,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[12]),32);
    bufp->fullIData(oldp+268,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[13]),32);
    bufp->fullIData(oldp+269,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[14]),32);
    bufp->fullIData(oldp+270,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[15]),32);
    bufp->fullIData(oldp+271,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[16]),32);
    bufp->fullIData(oldp+272,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[17]),32);
    bufp->fullIData(oldp+273,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[18]),32);
    bufp->fullIData(oldp+274,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[19]),32);
    bufp->fullIData(oldp+275,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[20]),32);
    bufp->fullIData(oldp+276,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[21]),32);
    bufp->fullIData(oldp+277,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[22]),32);
    bufp->fullIData(oldp+278,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[23]),32);
    bufp->fullIData(oldp+279,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[24]),32);
    bufp->fullIData(oldp+280,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[25]),32);
    bufp->fullIData(oldp+281,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[26]),32);
    bufp->fullIData(oldp+282,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[27]),32);
    bufp->fullIData(oldp+283,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[28]),32);
    bufp->fullIData(oldp+284,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[29]),32);
    bufp->fullIData(oldp+285,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs[30]),32);
    bufp->fullIData(oldp+286,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__unnamedblk1__DOT__i),32);
    bufp->fullIData(oldp+287,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc),32);
    bufp->fullIData(oldp+288,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m),32);
    bufp->fullIData(oldp+289,(((0U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                                ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                    << 0x18U) | ((0xff0000U 
                                                  & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                                     << 0x10U)) 
                                                 | ((0xff00U 
                                                     & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                                        << 8U)) 
                                                    | (0xffU 
                                                       & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))))
                                : ((1U == (3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m)))
                                    ? ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m 
                                        << 0x10U) | 
                                       (0xffffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))
                                    : vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m))),32);
    bufp->fullIData(oldp+290,(vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata),32);
    bufp->fullBit(oldp+291,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_m));
    bufp->fullBit(oldp+292,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_m));
    bufp->fullBit(oldp+293,((0U != (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
    bufp->fullCData(oldp+294,(vlSelf->soc_tb__DOT__dut__DOT__dmem_be),4);
    bufp->fullIData(oldp+295,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__addr_r),32);
    bufp->fullIData(oldp+296,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wdata_r),32);
    bufp->fullIData(oldp+297,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                              [0U]),32);
    bufp->fullCData(oldp+298,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__wstrb_r),4);
    bufp->fullBit(oldp+299,((1U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
    bufp->fullBit(oldp+300,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                            [0U]));
    bufp->fullBit(oldp+301,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                            [0U]));
    bufp->fullBit(oldp+302,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                            [0U]));
    bufp->fullBit(oldp+303,((2U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
    bufp->fullBit(oldp+304,((3U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
    bufp->fullBit(oldp+305,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                            [0U]));
    bufp->fullBit(oldp+306,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                            [0U]));
    bufp->fullBit(oldp+307,((4U == (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state))));
    bufp->fullIData(oldp+308,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                              [1U]),32);
    bufp->fullBit(oldp+309,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                            [1U]));
    bufp->fullBit(oldp+310,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                            [1U]));
    bufp->fullBit(oldp+311,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                            [1U]));
    bufp->fullBit(oldp+312,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                            [1U]));
    bufp->fullBit(oldp+313,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                            [1U]));
    bufp->fullIData(oldp+314,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata
                              [2U]),32);
    bufp->fullBit(oldp+315,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready
                            [2U]));
    bufp->fullBit(oldp+316,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready
                            [2U]));
    bufp->fullBit(oldp+317,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid
                            [2U]));
    bufp->fullBit(oldp+318,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready
                            [2U]));
    bufp->fullBit(oldp+319,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid
                            [2U]));
    bufp->fullIData(oldp+320,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                              [0U]),32);
    bufp->fullIData(oldp+321,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                              [0U]),32);
    bufp->fullIData(oldp+322,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                              [0U]),32);
    bufp->fullCData(oldp+323,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                              [0U]),4);
    bufp->fullBit(oldp+324,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                            [0U]));
    bufp->fullBit(oldp+325,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                            [0U]));
    bufp->fullBit(oldp+326,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                            [0U]));
    bufp->fullBit(oldp+327,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                            [0U]));
    bufp->fullBit(oldp+328,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                            [0U]));
    bufp->fullIData(oldp+329,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                              [1U]),32);
    bufp->fullIData(oldp+330,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                              [1U]),32);
    bufp->fullIData(oldp+331,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                              [1U]),32);
    bufp->fullCData(oldp+332,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                              [1U]),4);
    bufp->fullBit(oldp+333,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                            [1U]));
    bufp->fullBit(oldp+334,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                            [1U]));
    bufp->fullBit(oldp+335,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                            [1U]));
    bufp->fullBit(oldp+336,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                            [1U]));
    bufp->fullBit(oldp+337,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                            [1U]));
    bufp->fullIData(oldp+338,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                              [2U]),32);
    bufp->fullIData(oldp+339,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata
                              [2U]),32);
    bufp->fullIData(oldp+340,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                              [2U]),32);
    bufp->fullCData(oldp+341,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb
                              [2U]),4);
    bufp->fullBit(oldp+342,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid
                            [2U]));
    bufp->fullBit(oldp+343,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid
                            [2U]));
    bufp->fullBit(oldp+344,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready
                            [2U]));
    bufp->fullBit(oldp+345,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid
                            [2U]));
    bufp->fullBit(oldp+346,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready
                            [2U]));
    bufp->fullCData(oldp+347,((0x3fU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                        [2U] >> 2U))),6);
    bufp->fullCData(oldp+348,((0x3fU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                        [2U] >> 2U))),6);
    bufp->fullIData(oldp+349,(vlSelf->soc_tb__DOT__dut__DOT__u_accel__DOT__rdata_comb),32);
    bufp->fullCData(oldp+350,(vlSelf->soc_tb__DOT__dut__DOT__u_adapter__DOT__state),3);
    bufp->fullBit(oldp+351,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__stall_if));
    bufp->fullBit(oldp+352,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_id));
    bufp->fullBit(oldp+353,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__flush_ex));
    bufp->fullBit(oldp+354,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken));
    bufp->fullCData(oldp+355,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w),5);
    bufp->fullIData(oldp+356,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data),32);
    bufp->fullCData(oldp+357,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_m),5);
    bufp->fullIData(oldp+358,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d),32);
    bufp->fullCData(oldp+359,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                        >> 0xfU))),5);
    bufp->fullCData(oldp+360,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                        >> 0x14U))),5);
    bufp->fullCData(oldp+361,((0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                        >> 7U))),5);
    bufp->fullCData(oldp+362,((7U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                     >> 0xcU))),3);
    bufp->fullIData(oldp+363,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_d),32);
    bufp->fullBit(oldp+364,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__reg_write_d));
    bufp->fullBit(oldp+365,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_d));
    bufp->fullBit(oldp+366,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_d));
    bufp->fullBit(oldp+367,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_d));
    bufp->fullBit(oldp+368,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_b_d));
    bufp->fullBit(oldp+369,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_d));
    bufp->fullBit(oldp+370,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_d));
    bufp->fullCData(oldp+371,((((0x33U == (0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)) 
                                || (0x13U == (0x7fU 
                                              & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                                ? ((0x4000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                    ? ((0x2000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                        ? ((0x1000U 
                                            & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                            ? 2U : 3U)
                                        : ((0x1000U 
                                            & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                            ? ((0x40000000U 
                                                & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                                ? 7U
                                                : 6U)
                                            : 4U)) : 
                                   ((0x2000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                     ? ((0x1000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                         ? 9U : 8U)
                                     : ((0x1000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)
                                         ? 5U : ((IData)(
                                                         (0x40000033U 
                                                          == 
                                                          (0x4000007fU 
                                                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)))
                                                  ? 1U
                                                  : 0U))))
                                : 0U)),4);
    bufp->fullCData(oldp+372,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_sel_d),2);
    bufp->fullBit(oldp+373,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_read_e));
    bufp->fullBit(oldp+374,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__mem_write_e));
    bufp->fullCData(oldp+375,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e),3);
    bufp->fullCData(oldp+376,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_e),5);
    bufp->fullIData(oldp+377,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_ex_mem_val),32);
    bufp->fullCData(oldp+378,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_a),2);
    bufp->fullCData(oldp+379,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__fwd_b),2);
    bufp->fullIData(oldp+380,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result),32);
    bufp->fullIData(oldp+381,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs2_fwd),32);
    bufp->fullIData(oldp+382,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m),32);
    bufp->fullCData(oldp+383,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m),3);
    bufp->fullIData(oldp+384,(((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))
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
    bufp->fullCData(oldp+385,((0x7fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)),7);
    bufp->fullBit(oldp+386,((1U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                   >> 0x1eU))));
    bufp->fullIData(oldp+387,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_decode__DOT__u_imm_gen__DOT__imm_i),32);
    bufp->fullIData(oldp+388,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                            >> 0x1fU))) 
                                << 0xcU) | ((0xfe0U 
                                             & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                >> 0x14U)) 
                                            | (0x1fU 
                                               & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                  >> 7U))))),32);
    bufp->fullIData(oldp+389,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
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
    bufp->fullIData(oldp+390,((0xfffff000U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d)),32);
    bufp->fullIData(oldp+391,((((- (IData)((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
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
    bufp->fullIData(oldp+392,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__rs1_fwd),32);
    bufp->fullIData(oldp+393,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_a),32);
    bufp->fullIData(oldp+394,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b),32);
    bufp->fullBit(oldp+395,((0U == vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result)));
    bufp->fullBit(oldp+396,(((4U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_e))
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
    bufp->fullCData(oldp+397,((0x1fU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_b)),5);
    bufp->fullBit(oldp+398,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_hazard__DOT__load_use));
    bufp->fullCData(oldp+399,((3U & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m)),2);
    bufp->fullBit(oldp+400,((1U & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_result_m 
                                   >> 1U))));
    bufp->fullCData(oldp+401,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m)),8);
    bufp->fullSData(oldp+402,((0xffffU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rs2_data_m)),16);
    bufp->fullCData(oldp+403,((3U & (IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__funct3_m))),2);
    bufp->fullCData(oldp+404,((0xffU & vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata)),8);
    bufp->fullCData(oldp+405,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                        >> 8U))),8);
    bufp->fullCData(oldp+406,((0xffU & (vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                                        >> 0x10U))),8);
    bufp->fullCData(oldp+407,((vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+408,((0xffffU & vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata)),16);
    bufp->fullSData(oldp+409,((vlSelf->soc_tb__DOT__dut__DOT__dmem_rdata 
                               >> 0x10U)),16);
    bufp->fullCData(oldp+410,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte),8);
    bufp->fullSData(oldp+411,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half),16);
    bufp->fullBit(oldp+412,((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_byte) 
                                   >> 7U))));
    bufp->fullBit(oldp+413,((1U & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_memory__DOT__rd_half) 
                                   >> 0xfU))));
    bufp->fullBit(oldp+414,(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we));
    bufp->fullSData(oldp+415,((0x1ffU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc 
                                         >> 2U))),9);
    bufp->fullSData(oldp+416,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                          [0U] >> 2U))),14);
    bufp->fullSData(oldp+417,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                          [0U] >> 2U))),14);
    bufp->fullSData(oldp+418,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr
                                          [1U] >> 2U))),14);
    bufp->fullSData(oldp+419,((0x3fffU & (vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr
                                          [1U] >> 2U))),14);
    bufp->fullBit(oldp+420,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[0]));
    bufp->fullBit(oldp+421,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[1]));
    bufp->fullBit(oldp+422,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_awready[2]));
    bufp->fullBit(oldp+423,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[0]));
    bufp->fullBit(oldp+424,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[1]));
    bufp->fullBit(oldp+425,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_wready[2]));
    bufp->fullBit(oldp+426,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[0]));
    bufp->fullBit(oldp+427,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[1]));
    bufp->fullBit(oldp+428,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_bvalid[2]));
    bufp->fullBit(oldp+429,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[0]));
    bufp->fullBit(oldp+430,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[1]));
    bufp->fullBit(oldp+431,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_arready[2]));
    bufp->fullIData(oldp+432,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[0]),32);
    bufp->fullIData(oldp+433,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[1]),32);
    bufp->fullIData(oldp+434,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rdata[2]),32);
    bufp->fullBit(oldp+435,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[0]));
    bufp->fullBit(oldp+436,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[1]));
    bufp->fullBit(oldp+437,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__m_rvalid[2]));
    bufp->fullIData(oldp+438,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[0]),32);
    bufp->fullIData(oldp+439,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[1]),32);
    bufp->fullIData(oldp+440,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awaddr[2]),32);
    bufp->fullBit(oldp+441,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[0]));
    bufp->fullBit(oldp+442,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[1]));
    bufp->fullBit(oldp+443,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_awvalid[2]));
    bufp->fullIData(oldp+444,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[0]),32);
    bufp->fullIData(oldp+445,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[1]),32);
    bufp->fullIData(oldp+446,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wdata[2]),32);
    bufp->fullCData(oldp+447,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[0]),4);
    bufp->fullCData(oldp+448,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[1]),4);
    bufp->fullCData(oldp+449,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wstrb[2]),4);
    bufp->fullBit(oldp+450,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[0]));
    bufp->fullBit(oldp+451,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[1]));
    bufp->fullBit(oldp+452,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_wvalid[2]));
    bufp->fullBit(oldp+453,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[0]));
    bufp->fullBit(oldp+454,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[1]));
    bufp->fullBit(oldp+455,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_bready[2]));
    bufp->fullIData(oldp+456,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[0]),32);
    bufp->fullIData(oldp+457,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[1]),32);
    bufp->fullIData(oldp+458,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_araddr[2]),32);
    bufp->fullBit(oldp+459,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[0]));
    bufp->fullBit(oldp+460,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[1]));
    bufp->fullBit(oldp+461,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_arvalid[2]));
    bufp->fullBit(oldp+462,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[0]));
    bufp->fullBit(oldp+463,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[1]));
    bufp->fullBit(oldp+464,(vlSelf->soc_tb__DOT__dut__DOT__u_xbar__DOT__s_rready[2]));
    bufp->fullBit(oldp+465,(vlSelf->soc_tb__DOT__clk));
    bufp->fullBit(oldp+466,(vlSelf->soc_tb__DOT__rst_n));
    bufp->fullIData(oldp+467,(vlSelf->soc_tb__DOT__error_count),32);
    bufp->fullBit(oldp+468,(vlSelf->soc_tb__DOT__done_flag));
    bufp->fullBit(oldp+469,((1U & (~ (IData)(vlSelf->soc_tb__DOT__rst_n)))));
    bufp->fullIData(oldp+470,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e)
                                ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                                    ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                                    : (0xfffffffeU 
                                       & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))
                                : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                                   + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e))),32);
    bufp->fullIData(oldp+471,(((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                >> 0xfU)))
                                ? 0U : (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                                         & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                            == (0x1fU 
                                                & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                   >> 0xfU))))
                                         ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                                         : ((0x1eU 
                                             >= (0x1fU 
                                                 & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                     >> 0xfU) 
                                                    - (IData)(1U))))
                                             ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                                            [(0x1fU 
                                              & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                  >> 0xfU) 
                                                 - (IData)(1U)))]
                                             : 0U)))),32);
    bufp->fullIData(oldp+472,(((0U == (0x1fU & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                >> 0x14U)))
                                ? 0U : (((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT____Vcellinp__u_regfile__we) 
                                         & ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__rd_w) 
                                            == (0x1fU 
                                                & (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                   >> 0x14U))))
                                         ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__wb_data
                                         : ((0x1eU 
                                             >= (0x1fU 
                                                 & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                     >> 0x14U) 
                                                    - (IData)(1U))))
                                             ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_regfile__DOT__regs
                                            [(0x1fU 
                                              & ((vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__instr_d 
                                                  >> 0x14U) 
                                                 - (IData)(1U)))]
                                             : 0U)))),32);
    bufp->fullIData(oldp+473,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                                ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                                : (0xfffffffeU & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))),32);
    bufp->fullIData(oldp+474,(((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__branch_taken)
                                ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__jump_e)
                                    ? ((IData)(vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__alu_src_a_e)
                                        ? vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result
                                        : (0xfffffffeU 
                                           & vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_execute__DOT__alu_result))
                                    : (vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__imm_e 
                                       + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__pc_e))
                                : ((IData)(4U) + vlSelf->soc_tb__DOT__dut__DOT__u_cpu__DOT__u_fetch__DOT__pc))),32);
}
