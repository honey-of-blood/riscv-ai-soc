// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg.h"

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent): Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component(vlSymsp, name, parent) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::new\n"); );
    // Init
    _ctor_var_reset(vlSymsp);
    // Body
    ;
}

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_init_signals(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_init_signals\n"); );
    // Body
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 38)->awvalid = 0U;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 38)->wvalid = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 38)->bready = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 39)->arvalid = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 39)->rready = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 40)->awaddr = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 40)->wdata = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 40)->wstrb = 0U;
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 40)->araddr = 0U;
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*1:0*/ &resp, IData/*31:0*/ addr, IData/*31:0*/ data, CData/*3:0*/ strb) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_he68a865e__0;
    __VdynTrigger_he68a865e__0 = 0;
    __VdynTrigger_he68a865e__0 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__0;
    __Vtrigprevexpr_he0657be0__0 = 0;
    __Vtrigprevexpr_he0657be0__0 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 47)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__0)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     47);
        __VdynTrigger_he68a865e__0 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 47)
                                      ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__0)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__0);
        __Vtrigprevexpr_he0657be0__0 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 47)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 47);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    IData/*31:0*/ __Vintraval_hed052c15__0;
    __Vintraval_hed052c15__0 = 0;
    __Vintraval_hed052c15__0 = addr;
    this->__VnoInFunc_axi_write____Vfork_1__1(vlSymsp, __Vintraval_hed052c15__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h5e4072d0__0;
    __Vintraval_h5e4072d0__0 = 0;
    __Vintraval_h5e4072d0__0 = 1U;
    this->__VnoInFunc_axi_write____Vfork_2__1(vlSymsp, __Vintraval_h5e4072d0__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    IData/*31:0*/ __Vintraval_h39e7fb9c__0;
    __Vintraval_h39e7fb9c__0 = 0;
    __Vintraval_h39e7fb9c__0 = data;
    this->__VnoInFunc_axi_write____Vfork_3__1(vlSymsp, __Vintraval_h39e7fb9c__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*3:0*/ __Vintraval_h8bb5d09c__0;
    __Vintraval_h8bb5d09c__0 = 0;
    __Vintraval_h8bb5d09c__0 = strb;
    this->__VnoInFunc_axi_write____Vfork_4__1(vlSymsp, __Vintraval_h8bb5d09c__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h271fc011__0;
    __Vintraval_h271fc011__0 = 0;
    __Vintraval_h271fc011__0 = 1U;
    this->__VnoInFunc_axi_write____Vfork_5__1(vlSymsp, __Vintraval_h271fc011__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_hee291794__0;
    __Vintraval_hee291794__0 = 0;
    __Vintraval_hee291794__0 = 1U;
    this->__VnoInFunc_axi_write____Vfork_6__1(vlSymsp, __Vintraval_hee291794__0);
    CData/*0:0*/ __VdynTrigger_he68a865e__1;
    __VdynTrigger_he68a865e__1 = 0;
    __VdynTrigger_he68a865e__1 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__1;
    __Vtrigprevexpr_he0657be0__1 = 0;
    __Vtrigprevexpr_he0657be0__1 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 51)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__1)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     51);
        __VdynTrigger_he68a865e__1 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 51)
                                      ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__1)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__1);
        __Vtrigprevexpr_he0657be0__1 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 51)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 51);
    while ((1U & (~ (IData)(VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 52)
                            ->awready)))) {
        CData/*0:0*/ __VdynTrigger_he68a865e__2;
        __VdynTrigger_he68a865e__2 = 0;
        __VdynTrigger_he68a865e__2 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he0657be0__2;
        __Vtrigprevexpr_he0657be0__2 = 0;
        __Vtrigprevexpr_he0657be0__2 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 52)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_he68a865e__2)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         52);
            __VdynTrigger_he68a865e__2 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 52)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__2)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__2);
            __Vtrigprevexpr_he0657be0__2 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 52)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     52);
    }
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h5e455a3c__0;
    __Vintraval_h5e455a3c__0 = 0;
    __Vintraval_h5e455a3c__0 = 0U;
    this->__VnoInFunc_axi_write____Vfork_7__1(vlSymsp, __Vintraval_h5e455a3c__0);
    while ((1U & (~ (IData)(VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 54)
                            ->wready)))) {
        CData/*0:0*/ __VdynTrigger_he68a865e__3;
        __VdynTrigger_he68a865e__3 = 0;
        __VdynTrigger_he68a865e__3 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he0657be0__3;
        __Vtrigprevexpr_he0657be0__3 = 0;
        __Vtrigprevexpr_he0657be0__3 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 54)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_he68a865e__3)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         54);
            __VdynTrigger_he68a865e__3 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 54)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__3)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__3);
            __Vtrigprevexpr_he0657be0__3 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 54)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     54);
    }
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h27221d07__0;
    __Vintraval_h27221d07__0 = 0;
    __Vintraval_h27221d07__0 = 0U;
    this->__VnoInFunc_axi_write____Vfork_8__1(vlSymsp, __Vintraval_h27221d07__0);
    while ((1U & (~ (IData)(VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 56)
                            ->bvalid)))) {
        CData/*0:0*/ __VdynTrigger_he68a865e__4;
        __VdynTrigger_he68a865e__4 = 0;
        __VdynTrigger_he68a865e__4 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he0657be0__4;
        __Vtrigprevexpr_he0657be0__4 = 0;
        __Vtrigprevexpr_he0657be0__4 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 56)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_he68a865e__4)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         56);
            __VdynTrigger_he68a865e__4 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 56)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__4)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__4);
            __Vtrigprevexpr_he0657be0__4 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 56)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     56);
    }
    resp = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 57)
        ->bresp;
    CData/*0:0*/ __VdynTrigger_he68a865e__5;
    __VdynTrigger_he68a865e__5 = 0;
    __VdynTrigger_he68a865e__5 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__5;
    __Vtrigprevexpr_he0657be0__5 = 0;
    __Vtrigprevexpr_he0657be0__5 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 58)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__5)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     58);
        __VdynTrigger_he68a865e__5 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 58)
                                      ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__5)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__5);
        __Vtrigprevexpr_he0657be0__5 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 58)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 58);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_hee2a1988__0;
    __Vintraval_hee2a1988__0 = 0;
    __Vintraval_hee2a1988__0 = 0U;
    this->__VnoInFunc_axi_write____Vfork_9__1(vlSymsp, __Vintraval_hee2a1988__0);
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_9__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hee2a1988__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_9__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__8;
    __VdynTrigger_h72c70d24__8 = 0;
    __VdynTrigger_h72c70d24__8 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__8)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     59);
        __VdynTrigger_h72c70d24__8 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__8);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     59);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 59);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 59)->bready 
        = __Vintraval_hee2a1988__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_8__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h27221d07__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_8__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__7;
    __VdynTrigger_h72c70d24__7 = 0;
    __VdynTrigger_h72c70d24__7 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__7)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     55);
        __VdynTrigger_h72c70d24__7 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__7);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     55);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 55);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 55)->wvalid 
        = __Vintraval_h27221d07__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_7__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h5e455a3c__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_7__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__6;
    __VdynTrigger_h72c70d24__6 = 0;
    __VdynTrigger_h72c70d24__6 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__6)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     53);
        __VdynTrigger_h72c70d24__6 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__6);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     53);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 53);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 53)->awvalid 
        = __Vintraval_h5e455a3c__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_6__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hee291794__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_6__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__5;
    __VdynTrigger_h72c70d24__5 = 0;
    __VdynTrigger_h72c70d24__5 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__5)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     50);
        __VdynTrigger_h72c70d24__5 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__5);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     50);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 50);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 50)->bready 
        = __Vintraval_hee291794__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_5__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h271fc011__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_5__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__4;
    __VdynTrigger_h72c70d24__4 = 0;
    __VdynTrigger_h72c70d24__4 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__4)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        __VdynTrigger_h72c70d24__4 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__4);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 49);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 49)->wvalid 
        = __Vintraval_h271fc011__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_4__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*3:0*/ __Vintraval_h8bb5d09c__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_4__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__3;
    __VdynTrigger_h72c70d24__3 = 0;
    __VdynTrigger_h72c70d24__3 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__3)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        __VdynTrigger_h72c70d24__3 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__3);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 49);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 49)->wstrb 
        = __Vintraval_h8bb5d09c__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_3__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_h39e7fb9c__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_3__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__2;
    __VdynTrigger_h72c70d24__2 = 0;
    __VdynTrigger_h72c70d24__2 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__2)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        __VdynTrigger_h72c70d24__2 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__2);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     49);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 49);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 49)->wdata 
        = __Vintraval_h39e7fb9c__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_2__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h5e4072d0__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_2__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__1;
    __VdynTrigger_h72c70d24__1 = 0;
    __VdynTrigger_h72c70d24__1 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__1)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     48);
        __VdynTrigger_h72c70d24__1 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__1);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     48);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 48);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 48)->awvalid 
        = __Vintraval_h5e4072d0__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_1__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_hed052c15__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_write____Vfork_1__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__0;
    __VdynTrigger_h72c70d24__0 = 0;
    __VdynTrigger_h72c70d24__0 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__0)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     48);
        __VdynTrigger_h72c70d24__0 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__0);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     48);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 48);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 48)->awaddr 
        = __Vintraval_hed052c15__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &data, CData/*1:0*/ &resp, IData/*31:0*/ addr) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_he68a865e__6;
    __VdynTrigger_he68a865e__6 = 0;
    __VdynTrigger_he68a865e__6 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__6;
    __Vtrigprevexpr_he0657be0__6 = 0;
    __Vtrigprevexpr_he0657be0__6 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 65)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__6)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     65);
        __VdynTrigger_he68a865e__6 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 65)
                                      ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__6)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__6);
        __Vtrigprevexpr_he0657be0__6 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 65)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 65);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    IData/*31:0*/ __Vintraval_h79409aa2__0;
    __Vintraval_h79409aa2__0 = 0;
    __Vintraval_h79409aa2__0 = addr;
    this->__VnoInFunc_axi_read____Vfork_10__1(vlSymsp, __Vintraval_h79409aa2__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h714e1601__0;
    __Vintraval_h714e1601__0 = 0;
    __Vintraval_h714e1601__0 = 1U;
    this->__VnoInFunc_axi_read____Vfork_11__1(vlSymsp, __Vintraval_h714e1601__0);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_hdb7e0641__0;
    __Vintraval_hdb7e0641__0 = 0;
    __Vintraval_hdb7e0641__0 = 1U;
    this->__VnoInFunc_axi_read____Vfork_12__1(vlSymsp, __Vintraval_hdb7e0641__0);
    CData/*0:0*/ __VdynTrigger_he68a865e__7;
    __VdynTrigger_he68a865e__7 = 0;
    __VdynTrigger_he68a865e__7 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__7;
    __Vtrigprevexpr_he0657be0__7 = 0;
    __Vtrigprevexpr_he0657be0__7 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 67)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__7)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     67);
        __VdynTrigger_he68a865e__7 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 67)
                                      ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__7)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__7);
        __Vtrigprevexpr_he0657be0__7 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 67)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 67);
    while ((1U & (~ (IData)(VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 68)
                            ->arready)))) {
        CData/*0:0*/ __VdynTrigger_he68a865e__8;
        __VdynTrigger_he68a865e__8 = 0;
        __VdynTrigger_he68a865e__8 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he0657be0__8;
        __Vtrigprevexpr_he0657be0__8 = 0;
        __Vtrigprevexpr_he0657be0__8 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 68)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_he68a865e__8)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         68);
            __VdynTrigger_he68a865e__8 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 68)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__8)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__8);
            __Vtrigprevexpr_he0657be0__8 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 68)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     68);
    }
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_h72231777__0;
    __Vintraval_h72231777__0 = 0;
    __Vintraval_h72231777__0 = 0U;
    this->__VnoInFunc_axi_read____Vfork_13__1(vlSymsp, __Vintraval_h72231777__0);
    while ((1U & (~ (IData)(VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 70)
                            ->rvalid)))) {
        CData/*0:0*/ __VdynTrigger_he68a865e__9;
        __VdynTrigger_he68a865e__9 = 0;
        __VdynTrigger_he68a865e__9 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he0657be0__9;
        __Vtrigprevexpr_he0657be0__9 = 0;
        __Vtrigprevexpr_he0657be0__9 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 70)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_he68a865e__9)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         70);
            __VdynTrigger_he68a865e__9 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 70)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__9)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__9);
            __Vtrigprevexpr_he0657be0__9 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 70)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     70);
    }
    data = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 71)
        ->rdata;
    resp = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 71)
        ->rresp;
    CData/*0:0*/ __VdynTrigger_he68a865e__10;
    __VdynTrigger_he68a865e__10 = 0;
    __VdynTrigger_he68a865e__10 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__10;
    __Vtrigprevexpr_he0657be0__10 = 0;
    __Vtrigprevexpr_he0657be0__10 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 72)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__10)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     72);
        __VdynTrigger_he68a865e__10 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 72)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__10)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__10);
        __Vtrigprevexpr_he0657be0__10 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 72)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 72);
    vlSymsp->TOP.__VnbaEventTrigger = 1U;
    CData/*0:0*/ __Vintraval_hdb936737__0;
    __Vintraval_hdb936737__0 = 0;
    __Vintraval_hdb936737__0 = 0U;
    this->__VnoInFunc_axi_read____Vfork_14__1(vlSymsp, __Vintraval_hdb936737__0);
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_14__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hdb936737__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_14__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__13;
    __VdynTrigger_h72c70d24__13 = 0;
    __VdynTrigger_h72c70d24__13 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__13)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     73);
        __VdynTrigger_h72c70d24__13 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__13);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     73);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 73);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 73)->rready 
        = __Vintraval_hdb936737__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_13__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h72231777__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_13__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__12;
    __VdynTrigger_h72c70d24__12 = 0;
    __VdynTrigger_h72c70d24__12 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__12)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     69);
        __VdynTrigger_h72c70d24__12 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__12);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     69);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 69);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 69)->arvalid 
        = __Vintraval_h72231777__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_12__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hdb7e0641__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_12__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__11;
    __VdynTrigger_h72c70d24__11 = 0;
    __VdynTrigger_h72c70d24__11 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__11)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        __VdynTrigger_h72c70d24__11 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__11);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 66);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 66)->rready 
        = __Vintraval_hdb7e0641__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_11__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h714e1601__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_11__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__10;
    __VdynTrigger_h72c70d24__10 = 0;
    __VdynTrigger_h72c70d24__10 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__10)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        __VdynTrigger_h72c70d24__10 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__10);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 66);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 66)->arvalid 
        = __Vintraval_h714e1601__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_10__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_h79409aa2__0) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_axi_read____Vfork_10__1\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    CData/*0:0*/ __VdynTrigger_h72c70d24__9;
    __VdynTrigger_h72c70d24__9 = 0;
    __VdynTrigger_h72c70d24__9 = 0U;
    while ((1U & (~ (IData)(__VdynTrigger_h72c70d24__9)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        __VdynTrigger_h72c70d24__9 = vlSymsp->TOP.__VnbaEvent.isFired();
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_h72c70d24__9);
        co_await vlSymsp->TOP.__VdynSched.postUpdate(
                                                     nullptr, 
                                                     "@([event] __VnbaEvent)", 
                                                     "accel_tb_pkg.sv", 
                                                     66);
        if (vlSymsp->TOP.__VnbaEvent.isFired()) {
            vlSymsp->TOP.__VnbaEvent.clearFired();
            vlSymsp->enqueueTriggeredEventForClearing(vlSymsp->TOP.__VnbaEvent);
        }
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@([event] __VnbaEvent)", 
                                                 "accel_tb_pkg.sv", 
                                                 66);
    VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 66)->araddr 
        = __Vintraval_h79409aa2__0;
    vlSymsp->TOP.__VvifTrigger_h04376982__0 = 1U;
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_load_weights(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<IData/*31:0*/, 4> rows) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_load_weights\n"); );
    // Init
    VL_KEEP_THIS;
    CData/*1:0*/ __Vtask_axi_write__3__resp;
    __Vtask_axi_write__3__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__4__resp;
    __Vtask_axi_write__4__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__5__resp;
    __Vtask_axi_write__5__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__6__resp;
    __Vtask_axi_write__6__resp = 0;
    // Body
    CData/*1:0*/ r;
    r = 0;
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__3__resp, 0x50000004U, 
                                         rows[0U], 0xfU);
    r = __Vtask_axi_write__3__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__11;
    __VdynTrigger_he68a865e__11 = 0;
    __VdynTrigger_he68a865e__11 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__11;
    __Vtrigprevexpr_he0657be0__11 = 0;
    __Vtrigprevexpr_he0657be0__11 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 87)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__11)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     87);
        __VdynTrigger_he68a865e__11 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 87)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__11)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__11);
        __Vtrigprevexpr_he0657be0__11 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 87)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 87);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__4__resp, 0x50000008U, 
                                         rows[1U], 0xfU);
    r = __Vtask_axi_write__4__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__12;
    __VdynTrigger_he68a865e__12 = 0;
    __VdynTrigger_he68a865e__12 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__12;
    __Vtrigprevexpr_he0657be0__12 = 0;
    __Vtrigprevexpr_he0657be0__12 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 88)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__12)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     88);
        __VdynTrigger_he68a865e__12 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 88)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__12)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__12);
        __Vtrigprevexpr_he0657be0__12 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 88)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 88);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__5__resp, 0x5000000cU, 
                                         rows[2U], 0xfU);
    r = __Vtask_axi_write__5__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__13;
    __VdynTrigger_he68a865e__13 = 0;
    __VdynTrigger_he68a865e__13 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__13;
    __Vtrigprevexpr_he0657be0__13 = 0;
    __Vtrigprevexpr_he0657be0__13 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 89)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__13)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     89);
        __VdynTrigger_he68a865e__13 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 89)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__13)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__13);
        __Vtrigprevexpr_he0657be0__13 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 89)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 89);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__6__resp, 0x50000010U, 
                                         rows[3U], 0xfU);
    r = __Vtask_axi_write__6__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__14;
    __VdynTrigger_he68a865e__14 = 0;
    __VdynTrigger_he68a865e__14 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__14;
    __Vtrigprevexpr_he0657be0__14 = 0;
    __Vtrigprevexpr_he0657be0__14 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 90)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__14)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     90);
        __VdynTrigger_he68a865e__14 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 90)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__14)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__14);
        __Vtrigprevexpr_he0657be0__14 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 90)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 90);
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_load_activations(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<IData/*31:0*/, 4> rows) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_load_activations\n"); );
    // Init
    VL_KEEP_THIS;
    CData/*1:0*/ __Vtask_axi_write__7__resp;
    __Vtask_axi_write__7__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__8__resp;
    __Vtask_axi_write__8__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__9__resp;
    __Vtask_axi_write__9__resp = 0;
    CData/*1:0*/ __Vtask_axi_write__10__resp;
    __Vtask_axi_write__10__resp = 0;
    // Body
    CData/*1:0*/ r;
    r = 0;
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__7__resp, 0x50000014U, 
                                         rows[0U], 0xfU);
    r = __Vtask_axi_write__7__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__15;
    __VdynTrigger_he68a865e__15 = 0;
    __VdynTrigger_he68a865e__15 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__15;
    __Vtrigprevexpr_he0657be0__15 = 0;
    __Vtrigprevexpr_he0657be0__15 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 96)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__15)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     96);
        __VdynTrigger_he68a865e__15 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 96)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__15)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__15);
        __Vtrigprevexpr_he0657be0__15 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 96)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 96);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__8__resp, 0x50000018U, 
                                         rows[1U], 0xfU);
    r = __Vtask_axi_write__8__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__16;
    __VdynTrigger_he68a865e__16 = 0;
    __VdynTrigger_he68a865e__16 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__16;
    __Vtrigprevexpr_he0657be0__16 = 0;
    __Vtrigprevexpr_he0657be0__16 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 97)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__16)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     97);
        __VdynTrigger_he68a865e__16 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 97)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__16)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__16);
        __Vtrigprevexpr_he0657be0__16 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 97)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 97);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__9__resp, 0x5000001cU, 
                                         rows[2U], 0xfU);
    r = __Vtask_axi_write__9__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__17;
    __VdynTrigger_he68a865e__17 = 0;
    __VdynTrigger_he68a865e__17 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__17;
    __Vtrigprevexpr_he0657be0__17 = 0;
    __Vtrigprevexpr_he0657be0__17 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 98)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__17)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     98);
        __VdynTrigger_he68a865e__17 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 98)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__17)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__17);
        __Vtrigprevexpr_he0657be0__17 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 98)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 98);
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__10__resp, 0x50000020U, 
                                         rows[3U], 0xfU);
    r = __Vtask_axi_write__10__resp;
    CData/*0:0*/ __VdynTrigger_he68a865e__18;
    __VdynTrigger_he68a865e__18 = 0;
    __VdynTrigger_he68a865e__18 = 0U;
    CData/*0:0*/ __Vtrigprevexpr_he0657be0__18;
    __Vtrigprevexpr_he0657be0__18 = 0;
    __Vtrigprevexpr_he0657be0__18 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 99)
        ->clk;
    while ((1U & (~ (IData)(__VdynTrigger_he68a865e__18)))) {
        co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     99);
        __VdynTrigger_he68a865e__18 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 99)
                                       ->clk & (~ (IData)(__Vtrigprevexpr_he0657be0__18)));
        vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_he68a865e__18);
        __Vtrigprevexpr_he0657be0__18 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 99)
            ->clk;
    }
    co_await vlSymsp->TOP.__VdynSched.resumption(nullptr, 
                                                 "@(posedge accel_tb_pkg::accel_driver.vif.clk)", 
                                                 "accel_tb_pkg.sv", 
                                                 99);
}

void Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::_ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::_ctor_var_reset\n"); );
    // Body
    if (false && vlSymsp) {}  // Prevent unused
    __PVT__vif = nullptr;
}
