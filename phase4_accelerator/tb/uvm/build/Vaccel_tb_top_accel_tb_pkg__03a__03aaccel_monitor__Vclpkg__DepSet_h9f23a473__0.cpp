// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg.h"

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor____Vfork_1__1(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor____Vfork_1__1\n"); );
    // Init
    VL_KEEP_THIS;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> __Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item;
    // Body
    while (1U) {
        while ((1U & (~ (IData)((VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 141)
                                 ->arvalid && VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 141)
                                 ->arready))))) {
            CData/*0:0*/ __VdynTrigger_hded02bc2__4;
            __VdynTrigger_hded02bc2__4 = 0;
            __VdynTrigger_hded02bc2__4 = 0U;
            CData/*0:0*/ __Vtrigprevexpr_he4b01eec__4;
            __Vtrigprevexpr_he4b01eec__4 = 0;
            __Vtrigprevexpr_he4b01eec__4 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 141)
                ->clk;
            while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__4)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                             "accel_tb_pkg.sv", 
                                                             141);
                __VdynTrigger_hded02bc2__4 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 141)
                                              ->clk 
                                              & (~ (IData)(__Vtrigprevexpr_he4b01eec__4)));
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__4);
                __Vtrigprevexpr_he4b01eec__4 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 141)
                    ->clk;
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         141);
        }
        __Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item 
            = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item, vlSymsp, 
                     std::string{"mon_rd"});
        VL_NULL_CHECK(__Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item, "accel_tb_pkg.sv", 142)->__PVT__dir = 1U;
        VL_NULL_CHECK(__Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item, "accel_tb_pkg.sv", 142)->__PVT__addr 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 142)
            ->araddr;
        while ((1U & (~ (IData)((VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 143)
                                 ->rvalid && VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 143)
                                 ->rready))))) {
            CData/*0:0*/ __VdynTrigger_hded02bc2__5;
            __VdynTrigger_hded02bc2__5 = 0;
            __VdynTrigger_hded02bc2__5 = 0U;
            CData/*0:0*/ __Vtrigprevexpr_he4b01eec__5;
            __Vtrigprevexpr_he4b01eec__5 = 0;
            __Vtrigprevexpr_he4b01eec__5 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 143)
                ->clk;
            while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__5)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                             "accel_tb_pkg.sv", 
                                                             143);
                __VdynTrigger_hded02bc2__5 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 143)
                                              ->clk 
                                              & (~ (IData)(__Vtrigprevexpr_he4b01eec__5)));
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__5);
                __Vtrigprevexpr_he4b01eec__5 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 143)
                    ->clk;
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         143);
        }
        VL_NULL_CHECK(__Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item, "accel_tb_pkg.sv", 144)->__PVT__data 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 144)
            ->rdata;
        VL_NULL_CHECK(__Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item, "accel_tb_pkg.sv", 144)->__PVT__resp 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 144)
            ->rresp;
        VL_NULL_CHECK(this->__PVT__ap, "accel_tb_pkg.sv", 144)->__VnoInFunc_write(vlSymsp, __Vtask___Vfork_stmt__1__5__unnamedblk2__DOT__item);
        CData/*0:0*/ __VdynTrigger_hded02bc2__6;
        __VdynTrigger_hded02bc2__6 = 0;
        __VdynTrigger_hded02bc2__6 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he4b01eec__6;
        __Vtrigprevexpr_he4b01eec__6 = 0;
        __Vtrigprevexpr_he4b01eec__6 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 144)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__6)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         144);
            __VdynTrigger_hded02bc2__6 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 144)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he4b01eec__6)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__6);
            __Vtrigprevexpr_he4b01eec__6 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 144)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     144);
    }
}

VL_INLINE_OPT VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor____Vfork_1__0(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor::__VnoInFunc_run_monitor____Vfork_1__0\n"); );
    // Init
    VL_KEEP_THIS;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> __Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item;
    // Body
    while (1U) {
        while ((1U & (~ (IData)((VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 132)
                                 ->awvalid && VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 132)
                                 ->awready))))) {
            CData/*0:0*/ __VdynTrigger_hded02bc2__0;
            __VdynTrigger_hded02bc2__0 = 0;
            __VdynTrigger_hded02bc2__0 = 0U;
            CData/*0:0*/ __Vtrigprevexpr_he4b01eec__0;
            __Vtrigprevexpr_he4b01eec__0 = 0;
            __Vtrigprevexpr_he4b01eec__0 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 132)
                ->clk;
            while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__0)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                             "accel_tb_pkg.sv", 
                                                             132);
                __VdynTrigger_hded02bc2__0 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 132)
                                              ->clk 
                                              & (~ (IData)(__Vtrigprevexpr_he4b01eec__0)));
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__0);
                __Vtrigprevexpr_he4b01eec__0 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 132)
                    ->clk;
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         132);
        }
        __Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item 
            = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item, vlSymsp, 
                     std::string{"mon_wr"});
        VL_NULL_CHECK(__Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item, "accel_tb_pkg.sv", 133)->__PVT__dir = 0U;
        VL_NULL_CHECK(__Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item, "accel_tb_pkg.sv", 133)->__PVT__addr 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 133)
            ->awaddr;
        while ((1U & (~ (IData)((VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 134)
                                 ->wvalid && VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 134)
                                 ->wready))))) {
            CData/*0:0*/ __VdynTrigger_hded02bc2__1;
            __VdynTrigger_hded02bc2__1 = 0;
            __VdynTrigger_hded02bc2__1 = 0U;
            CData/*0:0*/ __Vtrigprevexpr_he4b01eec__1;
            __Vtrigprevexpr_he4b01eec__1 = 0;
            __Vtrigprevexpr_he4b01eec__1 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 134)
                ->clk;
            while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__1)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                             "accel_tb_pkg.sv", 
                                                             134);
                __VdynTrigger_hded02bc2__1 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 134)
                                              ->clk 
                                              & (~ (IData)(__Vtrigprevexpr_he4b01eec__1)));
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__1);
                __Vtrigprevexpr_he4b01eec__1 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 134)
                    ->clk;
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         134);
        }
        VL_NULL_CHECK(__Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item, "accel_tb_pkg.sv", 135)->__PVT__data 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 135)
            ->wdata;
        VL_NULL_CHECK(__Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item, "accel_tb_pkg.sv", 135)->__PVT__wstrb 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 135)
            ->wstrb;
        while ((1U & (~ (IData)((VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 136)
                                 ->bvalid && VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 136)
                                 ->bready))))) {
            CData/*0:0*/ __VdynTrigger_hded02bc2__2;
            __VdynTrigger_hded02bc2__2 = 0;
            __VdynTrigger_hded02bc2__2 = 0U;
            CData/*0:0*/ __Vtrigprevexpr_he4b01eec__2;
            __Vtrigprevexpr_he4b01eec__2 = 0;
            __Vtrigprevexpr_he4b01eec__2 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 136)
                ->clk;
            while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__2)))) {
                co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                             nullptr, 
                                                             "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                             "accel_tb_pkg.sv", 
                                                             136);
                __VdynTrigger_hded02bc2__2 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 136)
                                              ->clk 
                                              & (~ (IData)(__Vtrigprevexpr_he4b01eec__2)));
                vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__2);
                __Vtrigprevexpr_he4b01eec__2 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 136)
                    ->clk;
            }
            co_await vlSymsp->TOP.__VdynSched.resumption(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         136);
        }
        VL_NULL_CHECK(__Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item, "accel_tb_pkg.sv", 137)->__PVT__resp 
            = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 137)
            ->bresp;
        VL_NULL_CHECK(this->__PVT__ap, "accel_tb_pkg.sv", 137)->__VnoInFunc_write(vlSymsp, __Vtask___Vfork_stmt__0__2__unnamedblk1__DOT__item);
        CData/*0:0*/ __VdynTrigger_hded02bc2__3;
        __VdynTrigger_hded02bc2__3 = 0;
        __VdynTrigger_hded02bc2__3 = 0U;
        CData/*0:0*/ __Vtrigprevexpr_he4b01eec__3;
        __Vtrigprevexpr_he4b01eec__3 = 0;
        __Vtrigprevexpr_he4b01eec__3 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 137)
            ->clk;
        while ((1U & (~ (IData)(__VdynTrigger_hded02bc2__3)))) {
            co_await vlSymsp->TOP.__VdynSched.evaluation(
                                                         nullptr, 
                                                         "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                         "accel_tb_pkg.sv", 
                                                         137);
            __VdynTrigger_hded02bc2__3 = (VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 137)
                                          ->clk & (~ (IData)(__Vtrigprevexpr_he4b01eec__3)));
            vlSymsp->TOP.__VdynSched.anyTriggered(__VdynTrigger_hded02bc2__3);
            __Vtrigprevexpr_he4b01eec__3 = VL_NULL_CHECK(this->__PVT__vif, "accel_tb_pkg.sv", 137)
                ->clk;
        }
        co_await vlSymsp->TOP.__VdynSched.resumption(
                                                     nullptr, 
                                                     "@(posedge accel_tb_pkg::accel_monitor.vif.clk)", 
                                                     "accel_tb_pkg.sv", 
                                                     137);
    }
}
