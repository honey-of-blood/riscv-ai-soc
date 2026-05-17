// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vaccel_tb_top__Syms.h"


VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__uvm_mini_pkg__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_pkg__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep);
VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_top__DOT__aif__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("uvm_mini_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vaccel_tb_top___024root__trace_init_sub__TOP__uvm_mini_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("accel_tb_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("accel_tb_top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("aif", VerilatedTracePrefixType::SCOPE_INTERFACE);
    Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_top__DOT__aif__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->pushPrefix("run_matmul__Vstatic__y", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+7,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+11,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+12,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+13,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+14,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+15,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+16,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+17,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+18,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+19,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+20,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+21,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+22,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+175,0,"s_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+176,0,"s_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+177,0,"s_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+178,0,"s_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+179,0,"s_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+180,0,"s_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+177,0,"s_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+181,0,"s_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+47,0,"s_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+182,0,"s_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+183,0,"s_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"s_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+177,0,"s_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+48,0,"s_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+181,0,"s_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+49,0,"s_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+185,0,"s_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("w_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+50,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+51,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+52,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+53,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+54,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+55,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+56,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+57,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+58,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+59,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+60,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+61,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+62,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+63,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+64,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+65,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("a_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
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
    tracep->pushPrefix("y_reg", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+82,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+83,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+84,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+85,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+86,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+87,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+88,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+89,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+90,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+91,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+92,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+93,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+94,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+95,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+96,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+97,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->declBit(c+98,0,"done_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"start_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+100,0,"state",1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+101,0,"cyc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+102,0,"af0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+103,0,"af1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+104,0,"af2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+105,0,"af3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+106,0,"feed0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"feed1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"feed2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"feed3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+110,0,"y_out0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+111,0,"y_out1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"y_out2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+113,0,"y_out3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+186,0,"aw_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+114,0,"wr_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+115,0,"wr_idx_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+116,0,"wr_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+117,0,"wr_strb_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+187,0,"ar_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+173,0,"rdata_comb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("u_array", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+118,0,"w_row0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+119,0,"w_row1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+120,0,"w_row2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+121,0,"w_row3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"a_feed0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"a_feed1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"a_feed2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"a_feed3",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+110,0,"y_out0",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+111,0,"y_out1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"y_out2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+113,0,"y_out3",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"ps00",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"ps01",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"ps02",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"ps03",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+126,0,"ps10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"ps11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"ps12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"ps13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+130,0,"ps20",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+131,0,"ps21",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+132,0,"ps22",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+133,0,"ps23",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"ps30",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+111,0,"ps31",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"ps32",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+113,0,"ps33",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("r0c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+134,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+106,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+188,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+122,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+134,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+135,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+136,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+106,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+188,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+123,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+136,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+137,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+138,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+106,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+188,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+124,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+138,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+139,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r0c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+140,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+106,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+188,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+125,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+106,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+140,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+141,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+142,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+122,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+126,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+142,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+143,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+144,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+123,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+127,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+144,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+145,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+146,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+124,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+128,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+146,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+147,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r1c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+148,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+107,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+125,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+129,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+148,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+149,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+150,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+126,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+130,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+108,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+150,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+151,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+152,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+127,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+131,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+108,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+152,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+153,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+154,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+128,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+132,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+108,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+154,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+155,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r2c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+156,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+108,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+129,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+133,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+108,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+156,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+157,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c0", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+158,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+130,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+110,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+158,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+159,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+160,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+131,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+111,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+160,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+161,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+162,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+132,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+112,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+162,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+163,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("r3c3", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+171,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+164,0,"w_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+109,0,"a_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+133,0,"p_in",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+113,0,"p_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+109,0,"a_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+164,0,"w_s",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+165,0,"product",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+166,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->pushPrefix("unnamedblk2", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+167,0,"j",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->pushPrefix("w", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+23+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("a", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+27+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 31,0);
    }
    tracep->popPrefix();
    tracep->pushPrefix("y", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->pushPrefix("[0]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+31,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+32,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+33,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+34,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[1]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+35,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+36,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+37,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+38,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[2]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+39,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+40,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("[3]", VerilatedTracePrefixType::ARRAY_UNPACKED);
    tracep->declBus(c+43,0,"[0]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+44,0,"[1]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+45,0,"[2]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+46,0,"[3]",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->declBus(c+189,0,"resp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_pkg__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_pkg__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+190,0,"BASE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+191,0,"CTRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+192,0,"W_ROW0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+193,0,"A_ROW0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+194,0,"Y_BASE",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__uvm_mini_pkg__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_init_sub__TOP__uvm_mini_pkg__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+1,0,"g_error_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_top__DOT__aif__0(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_init_sub__TOP__accel_tb_top__DOT__aif__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+174,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+175,0,"awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+176,0,"awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+178,0,"wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+179,0,"wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+180,0,"wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+168,0,"bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+182,0,"bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+183,0,"araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+184,0,"arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+5,0,"arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+169,0,"rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+6,0,"rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+170,0,"rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+185,0,"rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_init_top(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_init_top\n"); );
    // Body
    Vaccel_tb_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp);
VL_ATTR_COLD void Vaccel_tb_top___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vaccel_tb_top___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vaccel_tb_top___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_register(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&Vaccel_tb_top___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vaccel_tb_top___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vaccel_tb_top___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vaccel_tb_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_const_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_const_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_const_0\n"); );
    // Init
    Vaccel_tb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccel_tb_top___024root*>(voidSelf);
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vaccel_tb_top___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_const_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_const_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+175,(vlSymsp->TOP__accel_tb_top__DOT__aif.awaddr),32);
    bufp->fullBit(oldp+176,(vlSymsp->TOP__accel_tb_top__DOT__aif.awvalid));
    bufp->fullBit(oldp+177,(1U));
    bufp->fullIData(oldp+178,(vlSymsp->TOP__accel_tb_top__DOT__aif.wdata),32);
    bufp->fullCData(oldp+179,(vlSymsp->TOP__accel_tb_top__DOT__aif.wstrb),4);
    bufp->fullBit(oldp+180,(vlSymsp->TOP__accel_tb_top__DOT__aif.wvalid));
    bufp->fullCData(oldp+181,(0U),2);
    bufp->fullBit(oldp+182,(vlSymsp->TOP__accel_tb_top__DOT__aif.bready));
    bufp->fullIData(oldp+183,(vlSymsp->TOP__accel_tb_top__DOT__aif.araddr),32);
    bufp->fullBit(oldp+184,(vlSymsp->TOP__accel_tb_top__DOT__aif.arvalid));
    bufp->fullBit(oldp+185,(vlSymsp->TOP__accel_tb_top__DOT__aif.rready));
    bufp->fullCData(oldp+186,((0x3fU & (vlSymsp->TOP__accel_tb_top__DOT__aif.awaddr 
                                        >> 2U))),6);
    bufp->fullCData(oldp+187,((0x3fU & (vlSymsp->TOP__accel_tb_top__DOT__aif.araddr 
                                        >> 2U))),6);
    bufp->fullIData(oldp+188,(0U),32);
    bufp->fullCData(oldp+189,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__resp),2);
    bufp->fullIData(oldp+190,(0x50000000U),32);
    bufp->fullIData(oldp+191,(0U),32);
    bufp->fullIData(oldp+192,(4U),32);
    bufp->fullIData(oldp+193,(0x14U),32);
    bufp->fullIData(oldp+194,(0x24U),32);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_full_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_full_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_full_0\n"); );
    // Init
    Vaccel_tb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccel_tb_top___024root*>(voidSelf);
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vaccel_tb_top___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_full_0_sub_0(Vaccel_tb_top___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSymsp->TOP__uvm_mini_pkg.g_error_count),32);
    bufp->fullBit(oldp+2,(vlSymsp->TOP__accel_tb_top__DOT__aif.awready));
    bufp->fullBit(oldp+3,(vlSymsp->TOP__accel_tb_top__DOT__aif.wready));
    bufp->fullCData(oldp+4,(vlSymsp->TOP__accel_tb_top__DOT__aif.bresp),2);
    bufp->fullBit(oldp+5,(vlSymsp->TOP__accel_tb_top__DOT__aif.arready));
    bufp->fullCData(oldp+6,(vlSymsp->TOP__accel_tb_top__DOT__aif.rresp),2);
    bufp->fullIData(oldp+7,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                            [0U][0U]),32);
    bufp->fullIData(oldp+8,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                            [0U][1U]),32);
    bufp->fullIData(oldp+9,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                            [0U][2U]),32);
    bufp->fullIData(oldp+10,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [0U][3U]),32);
    bufp->fullIData(oldp+11,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [1U][0U]),32);
    bufp->fullIData(oldp+12,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [1U][1U]),32);
    bufp->fullIData(oldp+13,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [1U][2U]),32);
    bufp->fullIData(oldp+14,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [1U][3U]),32);
    bufp->fullIData(oldp+15,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [2U][0U]),32);
    bufp->fullIData(oldp+16,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [2U][1U]),32);
    bufp->fullIData(oldp+17,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [2U][2U]),32);
    bufp->fullIData(oldp+18,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [2U][3U]),32);
    bufp->fullIData(oldp+19,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [3U][0U]),32);
    bufp->fullIData(oldp+20,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [3U][1U]),32);
    bufp->fullIData(oldp+21,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [3U][2U]),32);
    bufp->fullIData(oldp+22,(vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y
                             [3U][3U]),32);
    bufp->fullIData(oldp+23,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0]),32);
    bufp->fullIData(oldp+24,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1]),32);
    bufp->fullIData(oldp+25,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2]),32);
    bufp->fullIData(oldp+26,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3]),32);
    bufp->fullIData(oldp+27,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0]),32);
    bufp->fullIData(oldp+28,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1]),32);
    bufp->fullIData(oldp+29,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2]),32);
    bufp->fullIData(oldp+30,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3]),32);
    bufp->fullIData(oldp+31,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [0U][0U]),32);
    bufp->fullIData(oldp+32,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [0U][1U]),32);
    bufp->fullIData(oldp+33,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [0U][2U]),32);
    bufp->fullIData(oldp+34,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [0U][3U]),32);
    bufp->fullIData(oldp+35,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [1U][0U]),32);
    bufp->fullIData(oldp+36,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [1U][1U]),32);
    bufp->fullIData(oldp+37,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [1U][2U]),32);
    bufp->fullIData(oldp+38,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [1U][3U]),32);
    bufp->fullIData(oldp+39,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [2U][0U]),32);
    bufp->fullIData(oldp+40,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [2U][1U]),32);
    bufp->fullIData(oldp+41,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [2U][2U]),32);
    bufp->fullIData(oldp+42,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [2U][3U]),32);
    bufp->fullIData(oldp+43,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [3U][0U]),32);
    bufp->fullIData(oldp+44,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [3U][1U]),32);
    bufp->fullIData(oldp+45,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [3U][2U]),32);
    bufp->fullIData(oldp+46,(vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y
                             [3U][3U]),32);
    bufp->fullBit(oldp+47,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_bvalid));
    bufp->fullIData(oldp+48,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rdata),32);
    bufp->fullBit(oldp+49,(vlSelf->accel_tb_top__DOT____Vcellout__dut__s_rvalid));
    bufp->fullCData(oldp+50,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [0U][0U]),8);
    bufp->fullCData(oldp+51,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [0U][1U]),8);
    bufp->fullCData(oldp+52,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [0U][2U]),8);
    bufp->fullCData(oldp+53,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [0U][3U]),8);
    bufp->fullCData(oldp+54,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [1U][0U]),8);
    bufp->fullCData(oldp+55,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [1U][1U]),8);
    bufp->fullCData(oldp+56,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [1U][2U]),8);
    bufp->fullCData(oldp+57,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [1U][3U]),8);
    bufp->fullCData(oldp+58,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [2U][0U]),8);
    bufp->fullCData(oldp+59,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [2U][1U]),8);
    bufp->fullCData(oldp+60,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [2U][2U]),8);
    bufp->fullCData(oldp+61,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [2U][3U]),8);
    bufp->fullCData(oldp+62,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [3U][0U]),8);
    bufp->fullCData(oldp+63,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [3U][1U]),8);
    bufp->fullCData(oldp+64,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [3U][2U]),8);
    bufp->fullCData(oldp+65,(vlSelf->accel_tb_top__DOT__dut__DOT__w_reg
                             [3U][3U]),8);
    bufp->fullCData(oldp+66,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [0U][0U]),8);
    bufp->fullCData(oldp+67,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [0U][1U]),8);
    bufp->fullCData(oldp+68,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [0U][2U]),8);
    bufp->fullCData(oldp+69,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [0U][3U]),8);
    bufp->fullCData(oldp+70,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [1U][0U]),8);
    bufp->fullCData(oldp+71,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [1U][1U]),8);
    bufp->fullCData(oldp+72,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [1U][2U]),8);
    bufp->fullCData(oldp+73,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [1U][3U]),8);
    bufp->fullCData(oldp+74,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [2U][0U]),8);
    bufp->fullCData(oldp+75,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [2U][1U]),8);
    bufp->fullCData(oldp+76,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [2U][2U]),8);
    bufp->fullCData(oldp+77,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [2U][3U]),8);
    bufp->fullCData(oldp+78,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [3U][0U]),8);
    bufp->fullCData(oldp+79,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [3U][1U]),8);
    bufp->fullCData(oldp+80,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [3U][2U]),8);
    bufp->fullCData(oldp+81,(vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                             [3U][3U]),8);
    bufp->fullIData(oldp+82,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [0U][0U]),32);
    bufp->fullIData(oldp+83,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [0U][1U]),32);
    bufp->fullIData(oldp+84,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [0U][2U]),32);
    bufp->fullIData(oldp+85,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [0U][3U]),32);
    bufp->fullIData(oldp+86,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [1U][0U]),32);
    bufp->fullIData(oldp+87,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [1U][1U]),32);
    bufp->fullIData(oldp+88,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [1U][2U]),32);
    bufp->fullIData(oldp+89,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [1U][3U]),32);
    bufp->fullIData(oldp+90,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [2U][0U]),32);
    bufp->fullIData(oldp+91,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [2U][1U]),32);
    bufp->fullIData(oldp+92,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [2U][2U]),32);
    bufp->fullIData(oldp+93,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [2U][3U]),32);
    bufp->fullIData(oldp+94,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [3U][0U]),32);
    bufp->fullIData(oldp+95,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [3U][1U]),32);
    bufp->fullIData(oldp+96,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [3U][2U]),32);
    bufp->fullIData(oldp+97,(vlSelf->accel_tb_top__DOT__dut__DOT__y_reg
                             [3U][3U]),32);
    bufp->fullBit(oldp+98,(vlSelf->accel_tb_top__DOT__dut__DOT__done_r));
    bufp->fullBit(oldp+99,(vlSelf->accel_tb_top__DOT__dut__DOT__start_r));
    bufp->fullCData(oldp+100,(vlSelf->accel_tb_top__DOT__dut__DOT__state),2);
    bufp->fullCData(oldp+101,(vlSelf->accel_tb_top__DOT__dut__DOT__cyc),3);
    bufp->fullCData(oldp+102,(((0U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                               [0U][0U] : ((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                           [1U][0U]
                                            : ((2U 
                                                == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [2U]
                                               [0U]
                                                : (
                                                   (3U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [0U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+103,(((1U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                               [0U][1U] : ((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                           [1U][1U]
                                            : ((3U 
                                                == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [2U]
                                               [1U]
                                                : (
                                                   (4U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [1U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+104,(((2U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                               [0U][2U] : ((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                           [1U][2U]
                                            : ((4U 
                                                == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [2U]
                                               [2U]
                                                : (
                                                   (5U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [2U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+105,(((3U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                               [0U][3U] : ((4U == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                            ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                           [1U][3U]
                                            : ((5U 
                                                == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                ? vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                               [2U]
                                               [3U]
                                                : (
                                                   (6U 
                                                    == (IData)(vlSelf->accel_tb_top__DOT__dut__DOT__cyc))
                                                    ? 
                                                   vlSelf->accel_tb_top__DOT__dut__DOT__a_reg
                                                   [3U]
                                                   [3U]
                                                    : 0U))))),8);
    bufp->fullCData(oldp+106,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s),8);
    bufp->fullCData(oldp+107,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s),8);
    bufp->fullCData(oldp+108,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s),8);
    bufp->fullCData(oldp+109,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s),8);
    bufp->fullIData(oldp+110,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30),32);
    bufp->fullIData(oldp+111,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31),32);
    bufp->fullIData(oldp+112,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32),32);
    bufp->fullIData(oldp+113,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33),32);
    bufp->fullBit(oldp+114,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_pending));
    bufp->fullCData(oldp+115,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_idx_r),6);
    bufp->fullIData(oldp+116,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_data_r),32);
    bufp->fullCData(oldp+117,(vlSelf->accel_tb_top__DOT__dut__DOT__wr_strb_r),4);
    bufp->fullIData(oldp+118,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0),32);
    bufp->fullIData(oldp+119,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1),32);
    bufp->fullIData(oldp+120,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2),32);
    bufp->fullIData(oldp+121,(vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3),32);
    bufp->fullIData(oldp+122,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00),32);
    bufp->fullIData(oldp+123,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01),32);
    bufp->fullIData(oldp+124,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02),32);
    bufp->fullIData(oldp+125,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03),32);
    bufp->fullIData(oldp+126,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10),32);
    bufp->fullIData(oldp+127,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11),32);
    bufp->fullIData(oldp+128,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12),32);
    bufp->fullIData(oldp+129,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13),32);
    bufp->fullIData(oldp+130,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20),32);
    bufp->fullIData(oldp+131,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21),32);
    bufp->fullIData(oldp+132,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22),32);
    bufp->fullIData(oldp+133,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23),32);
    bufp->fullCData(oldp+134,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0)),8);
    bufp->fullSData(oldp+135,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product),16);
    bufp->fullCData(oldp+136,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                        >> 8U))),8);
    bufp->fullSData(oldp+137,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product),16);
    bufp->fullCData(oldp+138,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+139,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product),16);
    bufp->fullCData(oldp+140,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+141,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product),16);
    bufp->fullCData(oldp+142,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1)),8);
    bufp->fullSData(oldp+143,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product),16);
    bufp->fullCData(oldp+144,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                        >> 8U))),8);
    bufp->fullSData(oldp+145,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product),16);
    bufp->fullCData(oldp+146,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+147,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product),16);
    bufp->fullCData(oldp+148,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+149,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product),16);
    bufp->fullCData(oldp+150,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2)),8);
    bufp->fullSData(oldp+151,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product),16);
    bufp->fullCData(oldp+152,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                        >> 8U))),8);
    bufp->fullSData(oldp+153,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product),16);
    bufp->fullCData(oldp+154,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+155,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product),16);
    bufp->fullCData(oldp+156,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+157,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product),16);
    bufp->fullCData(oldp+158,((0xffU & vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3)),8);
    bufp->fullSData(oldp+159,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product),16);
    bufp->fullCData(oldp+160,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                        >> 8U))),8);
    bufp->fullSData(oldp+161,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product),16);
    bufp->fullCData(oldp+162,((0xffU & (vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                                        >> 0x10U))),8);
    bufp->fullSData(oldp+163,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product),16);
    bufp->fullCData(oldp+164,((vlSelf->accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3 
                               >> 0x18U)),8);
    bufp->fullSData(oldp+165,(vlSelf->accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product),16);
    bufp->fullIData(oldp+166,(vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__i),32);
    bufp->fullIData(oldp+167,(vlSelf->accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j),32);
    bufp->fullBit(oldp+168,(vlSymsp->TOP__accel_tb_top__DOT__aif.bvalid));
    bufp->fullIData(oldp+169,(vlSymsp->TOP__accel_tb_top__DOT__aif.rdata),32);
    bufp->fullBit(oldp+170,(vlSymsp->TOP__accel_tb_top__DOT__aif.rvalid));
    bufp->fullBit(oldp+171,(vlSelf->accel_tb_top__DOT__clk));
    bufp->fullBit(oldp+172,(vlSelf->accel_tb_top__DOT__rst_n));
    bufp->fullIData(oldp+173,(vlSelf->accel_tb_top__DOT__dut__DOT__rdata_comb),32);
    bufp->fullBit(oldp+174,(vlSymsp->TOP__accel_tb_top__DOT__aif.clk));
}
