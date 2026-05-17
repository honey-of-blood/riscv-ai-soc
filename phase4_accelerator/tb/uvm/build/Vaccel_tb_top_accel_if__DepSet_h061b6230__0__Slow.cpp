// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_if.h"

VL_ATTR_COLD void Vaccel_tb_top_accel_if___ctor_var_reset(Vaccel_tb_top_accel_if* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+                Vaccel_tb_top_accel_if___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    vlSelf->awaddr = VL_RAND_RESET_I(32);
    vlSelf->awvalid = VL_RAND_RESET_I(1);
    vlSelf->awready = VL_RAND_RESET_I(1);
    vlSelf->wdata = VL_RAND_RESET_I(32);
    vlSelf->wstrb = VL_RAND_RESET_I(4);
    vlSelf->wvalid = VL_RAND_RESET_I(1);
    vlSelf->wready = VL_RAND_RESET_I(1);
    vlSelf->bresp = VL_RAND_RESET_I(2);
    vlSelf->bvalid = VL_RAND_RESET_I(1);
    vlSelf->bready = VL_RAND_RESET_I(1);
    vlSelf->araddr = VL_RAND_RESET_I(32);
    vlSelf->arvalid = VL_RAND_RESET_I(1);
    vlSelf->arready = VL_RAND_RESET_I(1);
    vlSelf->rdata = VL_RAND_RESET_I(32);
    vlSelf->rresp = VL_RAND_RESET_I(2);
    vlSelf->rvalid = VL_RAND_RESET_I(1);
    vlSelf->rready = VL_RAND_RESET_I(1);
}
