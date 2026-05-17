// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg.h"

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_wait_done(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_wait_done\n"); );
    // Init
    VL_KEEP_THIS;
    IData/*31:0*/ __Vtask_axi_read__1__data;
    __Vtask_axi_read__1__data = 0;
    CData/*1:0*/ __Vtask_axi_read__1__resp;
    __Vtask_axi_read__1__resp = 0;
    IData/*31:0*/ __Vtask_axi_read__2__data;
    __Vtask_axi_read__2__data = 0;
    CData/*1:0*/ __Vtask_axi_read__2__resp;
    __Vtask_axi_read__2__resp = 0;
    // Body
    IData/*31:0*/ ctrl;
    ctrl = 0;
    CData/*1:0*/ r;
    r = 0;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__1__data, __Vtask_axi_read__1__resp, 0x50000000U);
    ctrl = __Vtask_axi_read__1__data;
    r = __Vtask_axi_read__1__resp;
    while ((1U & (~ (ctrl >> 1U)))) {
        co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__2__data, __Vtask_axi_read__2__resp, 0x50000000U);
        ctrl = __Vtask_axi_read__2__data;
        r = __Vtask_axi_read__2__resp;
    }
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_start_and_wait(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_start_and_wait\n"); );
    // Init
    VL_KEEP_THIS;
    CData/*1:0*/ __Vtask_axi_write__11__resp;
    __Vtask_axi_write__11__resp = 0;
    // Body
    CData/*1:0*/ r;
    r = 0;
    co_await this->__VnoInFunc_axi_write(vlSymsp, __Vtask_axi_write__11__resp, 0x50000000U, 1U, 0xfU);
    r = __Vtask_axi_write__11__resp;
    co_await this->__VnoInFunc_wait_done(vlSymsp);
}

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_read_outputs(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> &y) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::__VnoInFunc_read_outputs\n"); );
    // Init
    VL_KEEP_THIS;
    IData/*31:0*/ __Vtask_axi_read__13__data;
    __Vtask_axi_read__13__data = 0;
    CData/*1:0*/ __Vtask_axi_read__13__resp;
    __Vtask_axi_read__13__resp = 0;
    // Body
    IData/*31:0*/ unnamedblk1__DOT__m;
    unnamedblk1__DOT__m = 0;
    IData/*31:0*/ unnamedblk1__DOT__unnamedblk2__DOT__n;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 0;
    CData/*1:0*/ r;
    r = 0;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000024U);
    y[0U][0U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 1U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000028U);
    y[0U][1U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 2U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x5000002cU);
    y[0U][2U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 3U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000030U);
    y[0U][3U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 4U;
    unnamedblk1__DOT__m = 1U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000034U);
    y[1U][0U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 1U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000038U);
    y[1U][1U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 2U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x5000003cU);
    y[1U][2U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 3U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000040U);
    y[1U][3U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 4U;
    unnamedblk1__DOT__m = 2U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000044U);
    y[2U][0U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 1U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000048U);
    y[2U][1U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 2U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x5000004cU);
    y[2U][2U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 3U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000050U);
    y[2U][3U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 4U;
    unnamedblk1__DOT__m = 3U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000054U);
    y[3U][0U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 1U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000058U);
    y[3U][1U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 2U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x5000005cU);
    y[3U][2U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 3U;
    co_await this->__VnoInFunc_axi_read(vlSymsp, __Vtask_axi_read__13__data, __Vtask_axi_read__13__resp, 0x50000060U);
    y[3U][3U] = __Vtask_axi_read__13__data;
    r = __Vtask_axi_read__13__resp;
    unnamedblk1__DOT__unnamedblk2__DOT__n = 4U;
    unnamedblk1__DOT__m = 4U;
}

Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::~\n"); );
}

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver>& obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->to_string() : "null");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::to_string() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::to_string\n"); );
    // Body
    return (std::string{"'{"} + to_string_middle() + "}");
}

std::string Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::to_string_middle() const {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver::to_string_middle\n"); );
    // Body
    std::string out;
    out += "vif:" + VL_TO_STRING(__PVT__vif);
    out += ", "+ Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::to_string_middle();
    return out;
}
