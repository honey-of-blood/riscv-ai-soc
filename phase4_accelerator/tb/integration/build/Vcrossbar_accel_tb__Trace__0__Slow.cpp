// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vcrossbar_accel_tb__Syms.h"


VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_init_sub__TOP__0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("crossbar_accel_tb", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"error_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+18,0,"m0_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+19,0,"m0_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+122,0,"m0_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+20,0,"m0_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+21,0,"m0_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+22,0,"m0_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"m0_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+124,0,"m0_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+125,0,"m0_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"m0_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"m0_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+25,0,"m0_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+126,0,"m0_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+127,0,"m0_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"m0_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+129,0,"m0_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"m0_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m1_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+334,0,"m1_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+334,0,"m1_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+335,0,"m1_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+336,0,"m1_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+130,0,"m1_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+131,0,"m1_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+132,0,"m1_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+133,0,"m1_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+134,0,"m1_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+135,0,"m1_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+136,0,"m1_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+137,0,"m1_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m2_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+334,0,"m2_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+334,0,"m2_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+335,0,"m2_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+336,0,"m2_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+138,0,"m2_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+139,0,"m2_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+140,0,"m2_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+141,0,"m2_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+142,0,"m2_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+143,0,"m2_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+144,0,"m2_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+145,0,"m2_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+61,0,"s0_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+62,0,"s0_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+63,0,"s0_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+146,0,"s0_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"s0_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+337,0,"s0_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+337,0,"s0_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+65,0,"s0_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"s0_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+147,0,"s0_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"s0_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+68,0,"s0_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+148,0,"s0_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"s0_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+70,0,"s1_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+71,0,"s1_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+72,0,"s1_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+149,0,"s1_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+73,0,"s1_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+337,0,"s1_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+337,0,"s1_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+74,0,"s1_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+75,0,"s1_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+150,0,"s1_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"s1_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+77,0,"s1_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+151,0,"s1_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+78,0,"s1_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"s2_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+80,0,"s2_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+81,0,"s2_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+152,0,"s2_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+82,0,"s2_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+337,0,"s2_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+337,0,"s2_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+83,0,"s2_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"s2_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+153,0,"s2_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+85,0,"s2_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"s2_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+154,0,"s2_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"s2_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+339,0,"ACCEL_BASE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+340,0,"SRAM_BASE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+341,0,"CTRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+342,0,"W_ROW0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+343,0,"A_ROW0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+344,0,"Y_BASE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("accel", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+83,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+80,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+82,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+84,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+153,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+85,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+81,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+86,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+152,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+154,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("w_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+155,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+156,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+157,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+158,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+159,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+160,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+161,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+162,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+163,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+164,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+165,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+166,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+167,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+168,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+169,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+170,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("a_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+171,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+172,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+173,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+174,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+175,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+176,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+177,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+178,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+179,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+180,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+181,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+182,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+183,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+184,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+185,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+186,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("y_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+187,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+188,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+189,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+190,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+191,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+192,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+193,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+194,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+195,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+196,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+197,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+198,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+199,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+200,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+201,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+202,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->declBit(c+203,0,"done_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+204,0,"start_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+205,0,"state",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+206,0,"cyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+207,0,"af0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+208,0,"af1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+209,0,"af2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+210,0,"af3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"feed0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"feed1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"feed2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"feed3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+215,0,"y_out0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+216,0,"y_out1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+217,0,"y_out2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+218,0,"y_out3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+88,0,"aw_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+219,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+220,0,"wr_idx_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+221,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+222,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+89,0,"ar_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+90,0,"rdata_comb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_array", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+223,0,"w_row0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+224,0,"w_row1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+225,0,"w_row2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+226,0,"w_row3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+211,0,"a_feed0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"a_feed1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"a_feed2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"a_feed3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+215,0,"y_out0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+216,0,"y_out1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+217,0,"y_out2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+218,0,"y_out3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"ps00",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+228,0,"ps01",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+229,0,"ps02",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+230,0,"ps03",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+231,0,"ps10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+232,0,"ps11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+233,0,"ps12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+234,0,"ps13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+235,0,"ps20",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+236,0,"ps21",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+237,0,"ps22",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+238,0,"ps23",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+215,0,"ps30",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+216,0,"ps31",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+217,0,"ps32",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+218,0,"ps33",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("r0c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+239,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+340,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+227,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+211,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+239,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+240,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+241,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+340,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+228,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+211,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+241,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+242,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+243,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+340,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+229,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+211,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+243,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+244,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+245,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+211,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+340,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+230,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+211,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+245,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+246,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+247,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+227,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+231,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+212,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+247,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+248,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+249,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+228,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+232,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+212,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+249,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+250,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+251,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+229,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+233,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+212,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+251,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+252,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+253,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+212,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+230,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+234,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+212,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+253,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+254,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+255,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+231,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+235,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+213,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+255,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+256,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+257,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+232,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+236,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+213,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+257,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+258,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+259,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+233,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+237,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+213,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+259,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+260,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+261,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+213,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+234,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+238,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+213,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+261,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+262,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+263,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+235,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+215,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+214,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+263,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+264,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+265,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+236,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+216,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+214,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+265,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+266,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+267,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+237,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+217,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+214,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+267,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+268,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+269,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+214,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+238,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+218,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+214,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+269,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+270,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+271,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("unnamedblk2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+272,0,"j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("sram0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+345,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+61,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+65,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+62,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+66,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+147,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+68,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+148,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+346,0,"AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+91,0,"aw_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBit(c+273,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+274,0,"wr_addr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBus(c+275,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+276,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+92,0,"ar_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->popPrefix();
    tracep->pushPrefix("sram1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+345,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+70,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+74,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+71,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+73,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+75,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+150,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+72,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+77,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+149,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+151,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+78,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+346,0,"AW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"aw_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBit(c+277,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+278,0,"wr_addr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->declBus(c+279,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+280,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+94,0,"ar_waddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 13,0);
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+27,0,"rd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("xbar", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+332,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+333,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+18,0,"m0_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+19,0,"m0_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+122,0,"m0_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+20,0,"m0_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+21,0,"m0_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+22,0,"m0_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+123,0,"m0_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+124,0,"m0_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+125,0,"m0_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"m0_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+24,0,"m0_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+25,0,"m0_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+126,0,"m0_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+127,0,"m0_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"m0_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+129,0,"m0_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"m0_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m1_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"m1_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+133,0,"m1_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m1_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+335,0,"m1_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+336,0,"m1_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+134,0,"m1_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+132,0,"m1_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+135,0,"m1_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m1_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"m1_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+136,0,"m1_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+130,0,"m1_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+131,0,"m1_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+137,0,"m1_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m1_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m2_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"m2_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+141,0,"m2_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m2_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+335,0,"m2_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+336,0,"m2_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+142,0,"m2_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+140,0,"m2_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+143,0,"m2_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+334,0,"m2_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+336,0,"m2_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+144,0,"m2_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+138,0,"m2_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+139,0,"m2_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+145,0,"m2_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+336,0,"m2_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+61,0,"s0_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+65,0,"s0_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+62,0,"s0_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+64,0,"s0_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+66,0,"s0_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s0_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+147,0,"s0_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"s0_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"s0_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+68,0,"s0_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s0_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"s0_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s0_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+148,0,"s0_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"s0_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+70,0,"s1_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+74,0,"s1_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+71,0,"s1_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+73,0,"s1_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+75,0,"s1_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s1_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+150,0,"s1_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"s1_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+72,0,"s1_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+77,0,"s1_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s1_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+149,0,"s1_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s1_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+151,0,"s1_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+78,0,"s1_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+79,0,"s2_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+83,0,"s2_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+80,0,"s2_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+82,0,"s2_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+84,0,"s2_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+337,0,"s2_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+153,0,"s2_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+85,0,"s2_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+81,0,"s2_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+86,0,"s2_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+338,0,"s2_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+152,0,"s2_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+337,0,"s2_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+154,0,"s2_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"s2_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("m_awaddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+28+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+31+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+281+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+34+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wstrb", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+37+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 3,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+40+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_wready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+284+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+287+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+290+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_bready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+43+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_araddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+46+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_arvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+49+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_arready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+293+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+296+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+299+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+302+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_rready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+52+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awaddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+95+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+98+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_awready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+1+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+101+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wstrb", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+104+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 3,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_wvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+107+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
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
        tracep->declBit(c+305+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_bready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+110+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_araddr", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+113+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_arvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+116+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_arready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+10+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rdata", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+308+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rresp", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+13+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rvalid", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+311+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("s_rready", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+119+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_awdec", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+55+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("m_ardec", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+58+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_grant", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+314+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_busy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+317+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("wr_last", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+320+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_grant", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+323+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_busy", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBit(c+326+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0));
    }
    tracep->popPrefix();
    tracep->pushPrefix("rd_last", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 3; ++i) {
        tracep->declBus(c+329+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 1,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+16,0,"s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_init_top(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_init_top\n"); );
    // Body
    Vcrossbar_accel_tb___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vcrossbar_accel_tb___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vcrossbar_accel_tb___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_register(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&Vcrossbar_accel_tb___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vcrossbar_accel_tb___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vcrossbar_accel_tb___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vcrossbar_accel_tb___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_const_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_const_0\n"); );
    // Init
    Vcrossbar_accel_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcrossbar_accel_tb___024root*>(voidSelf);
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vcrossbar_accel_tb___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_const_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_const_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+334,(0U),32);
    bufp->fullCData(oldp+335,(0U),4);
    bufp->fullBit(oldp+336,(0U));
    bufp->fullCData(oldp+337,(0U),2);
    bufp->fullBit(oldp+338,(1U));
    bufp->fullIData(oldp+339,(0x50000000U),32);
    bufp->fullIData(oldp+340,(0U),32);
    bufp->fullIData(oldp+341,(0U),32);
    bufp->fullIData(oldp+342,(4U),32);
    bufp->fullIData(oldp+343,(0x14U),32);
    bufp->fullIData(oldp+344,(0x24U),32);
    bufp->fullIData(oldp+345,(0x4000U),32);
    bufp->fullIData(oldp+346,(0xeU),32);
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_full_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_full_0\n"); );
    // Init
    Vcrossbar_accel_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcrossbar_accel_tb___024root*>(voidSelf);
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vcrossbar_accel_tb___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_full_0_sub_0(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_accel_tb___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[0]));
    bufp->fullBit(oldp+2,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[1]));
    bufp->fullBit(oldp+3,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awready[2]));
    bufp->fullBit(oldp+4,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[0]));
    bufp->fullBit(oldp+5,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[1]));
    bufp->fullBit(oldp+6,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wready[2]));
    bufp->fullCData(oldp+7,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[0]),2);
    bufp->fullCData(oldp+8,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[1]),2);
    bufp->fullCData(oldp+9,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bresp[2]),2);
    bufp->fullBit(oldp+10,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[0]));
    bufp->fullBit(oldp+11,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[1]));
    bufp->fullBit(oldp+12,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arready[2]));
    bufp->fullCData(oldp+13,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[0]),2);
    bufp->fullCData(oldp+14,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[1]),2);
    bufp->fullCData(oldp+15,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rresp[2]),2);
    bufp->fullIData(oldp+16,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s),32);
    bufp->fullIData(oldp+17,(vlSelf->crossbar_accel_tb__DOT__error_count),32);
    bufp->fullIData(oldp+18,(vlSelf->crossbar_accel_tb__DOT__m0_awaddr),32);
    bufp->fullBit(oldp+19,(vlSelf->crossbar_accel_tb__DOT__m0_awvalid));
    bufp->fullIData(oldp+20,(vlSelf->crossbar_accel_tb__DOT__m0_wdata),32);
    bufp->fullCData(oldp+21,(vlSelf->crossbar_accel_tb__DOT__m0_wstrb),4);
    bufp->fullBit(oldp+22,(vlSelf->crossbar_accel_tb__DOT__m0_wvalid));
    bufp->fullBit(oldp+23,(vlSelf->crossbar_accel_tb__DOT__m0_bready));
    bufp->fullIData(oldp+24,(vlSelf->crossbar_accel_tb__DOT__m0_araddr),32);
    bufp->fullBit(oldp+25,(vlSelf->crossbar_accel_tb__DOT__m0_arvalid));
    bufp->fullBit(oldp+26,(vlSelf->crossbar_accel_tb__DOT__m0_rready));
    bufp->fullIData(oldp+27,(vlSelf->crossbar_accel_tb__DOT__unnamedblk1__DOT__rd),32);
    bufp->fullIData(oldp+28,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[0]),32);
    bufp->fullIData(oldp+29,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[1]),32);
    bufp->fullIData(oldp+30,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awaddr[2]),32);
    bufp->fullBit(oldp+31,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[0]));
    bufp->fullBit(oldp+32,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[1]));
    bufp->fullBit(oldp+33,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awvalid[2]));
    bufp->fullIData(oldp+34,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[0]),32);
    bufp->fullIData(oldp+35,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[1]),32);
    bufp->fullIData(oldp+36,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wdata[2]),32);
    bufp->fullCData(oldp+37,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[0]),4);
    bufp->fullCData(oldp+38,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[1]),4);
    bufp->fullCData(oldp+39,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wstrb[2]),4);
    bufp->fullBit(oldp+40,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[0]));
    bufp->fullBit(oldp+41,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[1]));
    bufp->fullBit(oldp+42,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wvalid[2]));
    bufp->fullBit(oldp+43,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[0]));
    bufp->fullBit(oldp+44,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[1]));
    bufp->fullBit(oldp+45,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bready[2]));
    bufp->fullIData(oldp+46,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[0]),32);
    bufp->fullIData(oldp+47,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[1]),32);
    bufp->fullIData(oldp+48,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_araddr[2]),32);
    bufp->fullBit(oldp+49,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[0]));
    bufp->fullBit(oldp+50,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[1]));
    bufp->fullBit(oldp+51,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arvalid[2]));
    bufp->fullBit(oldp+52,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[0]));
    bufp->fullBit(oldp+53,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[1]));
    bufp->fullBit(oldp+54,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rready[2]));
    bufp->fullCData(oldp+55,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[0]),2);
    bufp->fullCData(oldp+56,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[1]),2);
    bufp->fullCData(oldp+57,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awdec[2]),2);
    bufp->fullCData(oldp+58,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[0]),2);
    bufp->fullCData(oldp+59,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[1]),2);
    bufp->fullCData(oldp+60,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_ardec[2]),2);
    bufp->fullIData(oldp+61,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                             [0U]),32);
    bufp->fullIData(oldp+62,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                             [0U]),32);
    bufp->fullIData(oldp+63,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                             [0U]),32);
    bufp->fullCData(oldp+64,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                             [0U]),4);
    bufp->fullBit(oldp+65,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                           [0U]));
    bufp->fullBit(oldp+66,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                           [0U]));
    bufp->fullBit(oldp+67,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                           [0U]));
    bufp->fullBit(oldp+68,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                           [0U]));
    bufp->fullBit(oldp+69,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                           [0U]));
    bufp->fullIData(oldp+70,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                             [1U]),32);
    bufp->fullIData(oldp+71,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                             [1U]),32);
    bufp->fullIData(oldp+72,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                             [1U]),32);
    bufp->fullCData(oldp+73,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                             [1U]),4);
    bufp->fullBit(oldp+74,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                           [1U]));
    bufp->fullBit(oldp+75,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                           [1U]));
    bufp->fullBit(oldp+76,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                           [1U]));
    bufp->fullBit(oldp+77,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                           [1U]));
    bufp->fullBit(oldp+78,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                           [1U]));
    bufp->fullIData(oldp+79,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                             [2U]),32);
    bufp->fullIData(oldp+80,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata
                             [2U]),32);
    bufp->fullIData(oldp+81,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                             [2U]),32);
    bufp->fullCData(oldp+82,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb
                             [2U]),4);
    bufp->fullBit(oldp+83,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid
                           [2U]));
    bufp->fullBit(oldp+84,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid
                           [2U]));
    bufp->fullBit(oldp+85,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready
                           [2U]));
    bufp->fullBit(oldp+86,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid
                           [2U]));
    bufp->fullBit(oldp+87,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready
                           [2U]));
    bufp->fullCData(oldp+88,((0x3fU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                       [2U] >> 2U))),6);
    bufp->fullCData(oldp+89,((0x3fU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                       [2U] >> 2U))),6);
    bufp->fullIData(oldp+90,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__rdata_comb),32);
    bufp->fullSData(oldp+91,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                         [0U] >> 2U))),14);
    bufp->fullSData(oldp+92,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                         [0U] >> 2U))),14);
    bufp->fullSData(oldp+93,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr
                                         [1U] >> 2U))),14);
    bufp->fullSData(oldp+94,((0x3fffU & (vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr
                                         [1U] >> 2U))),14);
    bufp->fullIData(oldp+95,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[0]),32);
    bufp->fullIData(oldp+96,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[1]),32);
    bufp->fullIData(oldp+97,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awaddr[2]),32);
    bufp->fullBit(oldp+98,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[0]));
    bufp->fullBit(oldp+99,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[1]));
    bufp->fullBit(oldp+100,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_awvalid[2]));
    bufp->fullIData(oldp+101,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[0]),32);
    bufp->fullIData(oldp+102,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[1]),32);
    bufp->fullIData(oldp+103,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wdata[2]),32);
    bufp->fullCData(oldp+104,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[0]),4);
    bufp->fullCData(oldp+105,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[1]),4);
    bufp->fullCData(oldp+106,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wstrb[2]),4);
    bufp->fullBit(oldp+107,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[0]));
    bufp->fullBit(oldp+108,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[1]));
    bufp->fullBit(oldp+109,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_wvalid[2]));
    bufp->fullBit(oldp+110,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[0]));
    bufp->fullBit(oldp+111,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[1]));
    bufp->fullBit(oldp+112,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bready[2]));
    bufp->fullIData(oldp+113,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[0]),32);
    bufp->fullIData(oldp+114,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[1]),32);
    bufp->fullIData(oldp+115,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_araddr[2]),32);
    bufp->fullBit(oldp+116,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[0]));
    bufp->fullBit(oldp+117,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[1]));
    bufp->fullBit(oldp+118,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_arvalid[2]));
    bufp->fullBit(oldp+119,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[0]));
    bufp->fullBit(oldp+120,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[1]));
    bufp->fullBit(oldp+121,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rready[2]));
    bufp->fullBit(oldp+122,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                            [0U]));
    bufp->fullBit(oldp+123,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                            [0U]));
    bufp->fullCData(oldp+124,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                              [0U]),2);
    bufp->fullBit(oldp+125,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                            [0U]));
    bufp->fullBit(oldp+126,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                            [0U]));
    bufp->fullIData(oldp+127,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                              [0U]),32);
    bufp->fullCData(oldp+128,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                              [0U]),2);
    bufp->fullBit(oldp+129,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                            [0U]));
    bufp->fullIData(oldp+130,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                              [1U]),32);
    bufp->fullCData(oldp+131,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                              [1U]),2);
    bufp->fullCData(oldp+132,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                              [1U]),2);
    bufp->fullBit(oldp+133,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                            [1U]));
    bufp->fullBit(oldp+134,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                            [1U]));
    bufp->fullBit(oldp+135,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                            [1U]));
    bufp->fullBit(oldp+136,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                            [1U]));
    bufp->fullBit(oldp+137,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                            [1U]));
    bufp->fullIData(oldp+138,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata
                              [2U]),32);
    bufp->fullCData(oldp+139,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp
                              [2U]),2);
    bufp->fullCData(oldp+140,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp
                              [2U]),2);
    bufp->fullBit(oldp+141,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready
                            [2U]));
    bufp->fullBit(oldp+142,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready
                            [2U]));
    bufp->fullBit(oldp+143,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid
                            [2U]));
    bufp->fullBit(oldp+144,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready
                            [2U]));
    bufp->fullBit(oldp+145,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid
                            [2U]));
    bufp->fullIData(oldp+146,(vlSelf->crossbar_accel_tb__DOT__s0_rdata),32);
    bufp->fullBit(oldp+147,(vlSelf->crossbar_accel_tb__DOT__s0_bvalid));
    bufp->fullBit(oldp+148,(vlSelf->crossbar_accel_tb__DOT__s0_rvalid));
    bufp->fullIData(oldp+149,(vlSelf->crossbar_accel_tb__DOT__s1_rdata),32);
    bufp->fullBit(oldp+150,(vlSelf->crossbar_accel_tb__DOT__s1_bvalid));
    bufp->fullBit(oldp+151,(vlSelf->crossbar_accel_tb__DOT__s1_rvalid));
    bufp->fullIData(oldp+152,(vlSelf->crossbar_accel_tb__DOT__s2_rdata),32);
    bufp->fullBit(oldp+153,(vlSelf->crossbar_accel_tb__DOT__s2_bvalid));
    bufp->fullBit(oldp+154,(vlSelf->crossbar_accel_tb__DOT__s2_rvalid));
    bufp->fullCData(oldp+155,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [0U][0U]),8);
    bufp->fullCData(oldp+156,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [0U][1U]),8);
    bufp->fullCData(oldp+157,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [0U][2U]),8);
    bufp->fullCData(oldp+158,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [0U][3U]),8);
    bufp->fullCData(oldp+159,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [1U][0U]),8);
    bufp->fullCData(oldp+160,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [1U][1U]),8);
    bufp->fullCData(oldp+161,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [1U][2U]),8);
    bufp->fullCData(oldp+162,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [1U][3U]),8);
    bufp->fullCData(oldp+163,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [2U][0U]),8);
    bufp->fullCData(oldp+164,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [2U][1U]),8);
    bufp->fullCData(oldp+165,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [2U][2U]),8);
    bufp->fullCData(oldp+166,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [2U][3U]),8);
    bufp->fullCData(oldp+167,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [3U][0U]),8);
    bufp->fullCData(oldp+168,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [3U][1U]),8);
    bufp->fullCData(oldp+169,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [3U][2U]),8);
    bufp->fullCData(oldp+170,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__w_reg
                              [3U][3U]),8);
    bufp->fullCData(oldp+171,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [0U][0U]),8);
    bufp->fullCData(oldp+172,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [0U][1U]),8);
    bufp->fullCData(oldp+173,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [0U][2U]),8);
    bufp->fullCData(oldp+174,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [0U][3U]),8);
    bufp->fullCData(oldp+175,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [1U][0U]),8);
    bufp->fullCData(oldp+176,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [1U][1U]),8);
    bufp->fullCData(oldp+177,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [1U][2U]),8);
    bufp->fullCData(oldp+178,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [1U][3U]),8);
    bufp->fullCData(oldp+179,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [2U][0U]),8);
    bufp->fullCData(oldp+180,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [2U][1U]),8);
    bufp->fullCData(oldp+181,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [2U][2U]),8);
    bufp->fullCData(oldp+182,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [2U][3U]),8);
    bufp->fullCData(oldp+183,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [3U][0U]),8);
    bufp->fullCData(oldp+184,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [3U][1U]),8);
    bufp->fullCData(oldp+185,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [3U][2U]),8);
    bufp->fullCData(oldp+186,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                              [3U][3U]),8);
    bufp->fullIData(oldp+187,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [0U][0U]),32);
    bufp->fullIData(oldp+188,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [0U][1U]),32);
    bufp->fullIData(oldp+189,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [0U][2U]),32);
    bufp->fullIData(oldp+190,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [0U][3U]),32);
    bufp->fullIData(oldp+191,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [1U][0U]),32);
    bufp->fullIData(oldp+192,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [1U][1U]),32);
    bufp->fullIData(oldp+193,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [1U][2U]),32);
    bufp->fullIData(oldp+194,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [1U][3U]),32);
    bufp->fullIData(oldp+195,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [2U][0U]),32);
    bufp->fullIData(oldp+196,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [2U][1U]),32);
    bufp->fullIData(oldp+197,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [2U][2U]),32);
    bufp->fullIData(oldp+198,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [2U][3U]),32);
    bufp->fullIData(oldp+199,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [3U][0U]),32);
    bufp->fullIData(oldp+200,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [3U][1U]),32);
    bufp->fullIData(oldp+201,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [3U][2U]),32);
    bufp->fullIData(oldp+202,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__y_reg
                              [3U][3U]),32);
    bufp->fullBit(oldp+203,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__done_r));
    bufp->fullBit(oldp+204,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__start_r));
    bufp->fullCData(oldp+205,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__state),2);
    bufp->fullCData(oldp+206,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc),3);
    bufp->fullCData(oldp+207,(((0U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                               [0U][0U] : ((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                           [1U][0U]
                                            : ((2U 
                                                == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                               [2U]
                                               [0U]
                                                : (
                                                   (3U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+208,(((1U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                               [0U][1U] : ((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                           [1U][1U]
                                            : ((3U 
                                                == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                               [2U]
                                               [1U]
                                                : (
                                                   (4U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+209,(((2U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                               [0U][2U] : ((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                           [1U][2U]
                                            : ((4U 
                                                == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                               [2U]
                                               [2U]
                                                : (
                                                   (5U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+210,(((3U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                               [0U][3U] : ((4U == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                            ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                           [1U][3U]
                                            : ((5U 
                                                == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                ? vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                               [2U]
                                               [3U]
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelf->crossbar_accel_tb__DOT__accel__DOT__cyc))
                                                    ? 
                                                   vlSelf->crossbar_accel_tb__DOT__accel__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+211,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s),8);
    bufp->fullCData(oldp+212,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s),8);
    bufp->fullCData(oldp+213,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s),8);
    bufp->fullCData(oldp+214,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s),8);
    bufp->fullIData(oldp+215,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30),32);
    bufp->fullIData(oldp+216,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31),32);
    bufp->fullIData(oldp+217,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32),32);
    bufp->fullIData(oldp+218,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33),32);
    bufp->fullBit(oldp+219,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_pending));
    bufp->fullCData(oldp+220,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_idx_r),6);
    bufp->fullIData(oldp+221,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_data_r),32);
    bufp->fullCData(oldp+222,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__wr_strb_r),4);
    bufp->fullIData(oldp+223,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0),32);
    bufp->fullIData(oldp+224,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1),32);
    bufp->fullIData(oldp+225,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2),32);
    bufp->fullIData(oldp+226,(vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3),32);
    bufp->fullIData(oldp+227,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00),32);
    bufp->fullIData(oldp+228,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01),32);
    bufp->fullIData(oldp+229,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02),32);
    bufp->fullIData(oldp+230,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03),32);
    bufp->fullIData(oldp+231,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10),32);
    bufp->fullIData(oldp+232,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11),32);
    bufp->fullIData(oldp+233,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12),32);
    bufp->fullIData(oldp+234,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13),32);
    bufp->fullIData(oldp+235,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20),32);
    bufp->fullIData(oldp+236,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21),32);
    bufp->fullIData(oldp+237,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22),32);
    bufp->fullIData(oldp+238,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23),32);
    bufp->fullCData(oldp+239,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0)),8);
    bufp->fullSData(oldp+240,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product),16);
    bufp->fullCData(oldp+241,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                        >> 8U))),8);
    bufp->fullSData(oldp+242,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product),16);
    bufp->fullCData(oldp+243,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+244,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product),16);
    bufp->fullCData(oldp+245,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+246,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product),16);
    bufp->fullCData(oldp+247,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1)),8);
    bufp->fullSData(oldp+248,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product),16);
    bufp->fullCData(oldp+249,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                        >> 8U))),8);
    bufp->fullSData(oldp+250,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product),16);
    bufp->fullCData(oldp+251,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+252,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product),16);
    bufp->fullCData(oldp+253,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+254,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product),16);
    bufp->fullCData(oldp+255,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2)),8);
    bufp->fullSData(oldp+256,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product),16);
    bufp->fullCData(oldp+257,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                        >> 8U))),8);
    bufp->fullSData(oldp+258,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product),16);
    bufp->fullCData(oldp+259,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+260,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product),16);
    bufp->fullCData(oldp+261,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+262,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product),16);
    bufp->fullCData(oldp+263,((0xffU & vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3)),8);
    bufp->fullSData(oldp+264,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product),16);
    bufp->fullCData(oldp+265,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                        >> 8U))),8);
    bufp->fullSData(oldp+266,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product),16);
    bufp->fullCData(oldp+267,((0xffU & (vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+268,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product),16);
    bufp->fullCData(oldp+269,((vlSelf->crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+270,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product),16);
    bufp->fullIData(oldp+271,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__i),32);
    bufp->fullIData(oldp+272,(vlSelf->crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
    bufp->fullBit(oldp+273,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_pending));
    bufp->fullSData(oldp+274,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r),14);
    bufp->fullIData(oldp+275,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_data_r),32);
    bufp->fullCData(oldp+276,(vlSelf->crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r),4);
    bufp->fullBit(oldp+277,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_pending));
    bufp->fullSData(oldp+278,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r),14);
    bufp->fullIData(oldp+279,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_data_r),32);
    bufp->fullCData(oldp+280,(vlSelf->crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r),4);
    bufp->fullBit(oldp+281,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[0]));
    bufp->fullBit(oldp+282,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[1]));
    bufp->fullBit(oldp+283,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_awready[2]));
    bufp->fullBit(oldp+284,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[0]));
    bufp->fullBit(oldp+285,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[1]));
    bufp->fullBit(oldp+286,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_wready[2]));
    bufp->fullCData(oldp+287,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[0]),2);
    bufp->fullCData(oldp+288,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[1]),2);
    bufp->fullCData(oldp+289,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bresp[2]),2);
    bufp->fullBit(oldp+290,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[0]));
    bufp->fullBit(oldp+291,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[1]));
    bufp->fullBit(oldp+292,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_bvalid[2]));
    bufp->fullBit(oldp+293,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[0]));
    bufp->fullBit(oldp+294,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[1]));
    bufp->fullBit(oldp+295,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_arready[2]));
    bufp->fullIData(oldp+296,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[0]),32);
    bufp->fullIData(oldp+297,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[1]),32);
    bufp->fullIData(oldp+298,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rdata[2]),32);
    bufp->fullCData(oldp+299,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[0]),2);
    bufp->fullCData(oldp+300,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[1]),2);
    bufp->fullCData(oldp+301,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rresp[2]),2);
    bufp->fullBit(oldp+302,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[0]));
    bufp->fullBit(oldp+303,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[1]));
    bufp->fullBit(oldp+304,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__m_rvalid[2]));
    bufp->fullBit(oldp+305,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[0]));
    bufp->fullBit(oldp+306,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[1]));
    bufp->fullBit(oldp+307,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_bvalid[2]));
    bufp->fullIData(oldp+308,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[0]),32);
    bufp->fullIData(oldp+309,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[1]),32);
    bufp->fullIData(oldp+310,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rdata[2]),32);
    bufp->fullBit(oldp+311,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[0]));
    bufp->fullBit(oldp+312,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[1]));
    bufp->fullBit(oldp+313,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__s_rvalid[2]));
    bufp->fullCData(oldp+314,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[0]),2);
    bufp->fullCData(oldp+315,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[1]),2);
    bufp->fullCData(oldp+316,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_grant[2]),2);
    bufp->fullBit(oldp+317,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[0]));
    bufp->fullBit(oldp+318,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[1]));
    bufp->fullBit(oldp+319,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_busy[2]));
    bufp->fullCData(oldp+320,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[0]),2);
    bufp->fullCData(oldp+321,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[1]),2);
    bufp->fullCData(oldp+322,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__wr_last[2]),2);
    bufp->fullCData(oldp+323,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[0]),2);
    bufp->fullCData(oldp+324,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[1]),2);
    bufp->fullCData(oldp+325,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_grant[2]),2);
    bufp->fullBit(oldp+326,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[0]));
    bufp->fullBit(oldp+327,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[1]));
    bufp->fullBit(oldp+328,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_busy[2]));
    bufp->fullCData(oldp+329,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[0]),2);
    bufp->fullCData(oldp+330,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[1]),2);
    bufp->fullCData(oldp+331,(vlSelf->crossbar_accel_tb__DOT__xbar__DOT__rd_last[2]),2);
    bufp->fullBit(oldp+332,(vlSelf->crossbar_accel_tb__DOT__clk));
    bufp->fullBit(oldp+333,(vlSelf->crossbar_accel_tb__DOT__rst_n));
}
