// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top__Syms.h"
#include "Vaccel_tb_top___024root.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg.h"

VL_INLINE_OPT VlCoroutine Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__1(Vaccel_tb_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccel_tb_top___024root___eval_initial__TOP__Vtiming__1\n"); );
    // Init
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env> accel_tb_top__DOT__env;
    VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> accel_tb_top__DOT__ph;
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows[__Vi0] = 0;
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows[__Vi0] = 0;
    }
    std::string __Vtask_accel_tb_top__DOT__run_matmul__5__tag;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__9__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__9__y[__Vi0][__Vi1] = 0;
        }
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows[__Vi0] = 0;
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows[__Vi0] = 0;
    }
    std::string __Vtask_accel_tb_top__DOT__run_matmul__12__tag;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__16__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__16__y[__Vi0][__Vi1] = 0;
        }
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows[__Vi0] = 0;
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows[__Vi0] = 0;
    }
    std::string __Vtask_accel_tb_top__DOT__run_matmul__19__tag;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__23__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__23__y[__Vi0][__Vi1] = 0;
        }
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows[__Vi0] = 0;
    }
    VlUnpacked<IData/*31:0*/, 4> __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows[__Vi0] = 0;
    }
    std::string __Vtask_accel_tb_top__DOT__run_matmul__26__tag;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__30__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__30__y[__Vi0][__Vi1] = 0;
        }
    }
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__36__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__36__y[__Vi0][__Vi1] = 0;
        }
    }
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __Vtask_read_outputs__40__y;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            __Vtask_read_outputs__40__y[__Vi0][__Vi1] = 0;
        }
    }
    // Body
    accel_tb_top__DOT__ph = VL_NEW(Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase, vlSymsp, 
                                   std::string{"run"});
    accel_tb_top__DOT__env = VL_NEW(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env, vlSymsp, 
                                    std::string{"env"}, VlNull{});
    VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 58)->__PVT__m_vif 
        = (&vlSymsp->TOP__accel_tb_top__DOT__aif);
    VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 59)->__VnoInFunc_build_phase(vlSymsp, accel_tb_top__DOT__ph);
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 60)
                  ->__PVT__drv, "accel_tb_top.sv", 60)->__VnoInFunc_init_signals(vlSymsp);
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 63)
                  ->__PVT__mon, "accel_tb_top.sv", 63)->__VnoInFunc_run_monitor(vlSymsp);
    while ((1U & (~ (IData)(vlSelf->accel_tb_top__DOT__rst_n)))) {
        co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                           nullptr, 
                                                           "@(posedge accel_tb_top.clk)", 
                                                           "accel_tb_top.sv", 
                                                           66);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       67);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_WRITEF("\n=== TEST 1: Identity weight matrix (Y = A) ===\n");
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1U] = 0x100U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2U] = 0x10000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3U] = 0x1000000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 0x4030201U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0x100f0e0dU;
    __Vtask_accel_tb_top__DOT__run_matmul__5__tag = 
        std::string{"identity_weights"};
    __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [3U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [3U];
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 44)
                           ->__PVT__drv, "accel_tb_top.sv", 44)->__VnoInFunc_load_weights(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__5__w_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 45)
                           ->__PVT__drv, "accel_tb_top.sv", 45)->__VnoInFunc_load_activations(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__5__a_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 46)
                           ->__PVT__drv, "accel_tb_top.sv", 46)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 47)
                           ->__PVT__drv, "accel_tb_top.sv", 47)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__9__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][0U] 
        = __Vtask_read_outputs__9__y[0U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][1U] 
        = __Vtask_read_outputs__9__y[0U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][2U] 
        = __Vtask_read_outputs__9__y[0U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][3U] 
        = __Vtask_read_outputs__9__y[0U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][0U] 
        = __Vtask_read_outputs__9__y[1U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][1U] 
        = __Vtask_read_outputs__9__y[1U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][2U] 
        = __Vtask_read_outputs__9__y[1U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][3U] 
        = __Vtask_read_outputs__9__y[1U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][0U] 
        = __Vtask_read_outputs__9__y[2U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][1U] 
        = __Vtask_read_outputs__9__y[2U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][2U] 
        = __Vtask_read_outputs__9__y[2U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][3U] 
        = __Vtask_read_outputs__9__y[2U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][0U] 
        = __Vtask_read_outputs__9__y[3U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][1U] 
        = __Vtask_read_outputs__9__y[3U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][2U] 
        = __Vtask_read_outputs__9__y[3U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][3U] 
        = __Vtask_read_outputs__9__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 48)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 49)
                  ->__PVT__cov, "accel_tb_top.sv", 49)->__VnoInFunc_mark(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__5__tag);
    VL_WRITEF("\n=== TEST 2: Full 4\303\2274 matmul (A=[1..16], W=[1..16]) ===\n");
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0U] = 0x4030201U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3U] = 0x100f0e0dU;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 0x4030201U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0x100f0e0dU;
    __Vtask_accel_tb_top__DOT__run_matmul__12__tag = 
        std::string{"full_matmul"};
    __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [3U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [3U];
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 44)
                           ->__PVT__drv, "accel_tb_top.sv", 44)->__VnoInFunc_load_weights(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__12__w_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 45)
                           ->__PVT__drv, "accel_tb_top.sv", 45)->__VnoInFunc_load_activations(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__12__a_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 46)
                           ->__PVT__drv, "accel_tb_top.sv", 46)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 47)
                           ->__PVT__drv, "accel_tb_top.sv", 47)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__16__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][0U] 
        = __Vtask_read_outputs__16__y[0U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][1U] 
        = __Vtask_read_outputs__16__y[0U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][2U] 
        = __Vtask_read_outputs__16__y[0U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][3U] 
        = __Vtask_read_outputs__16__y[0U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][0U] 
        = __Vtask_read_outputs__16__y[1U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][1U] 
        = __Vtask_read_outputs__16__y[1U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][2U] 
        = __Vtask_read_outputs__16__y[1U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][3U] 
        = __Vtask_read_outputs__16__y[1U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][0U] 
        = __Vtask_read_outputs__16__y[2U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][1U] 
        = __Vtask_read_outputs__16__y[2U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][2U] 
        = __Vtask_read_outputs__16__y[2U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][3U] 
        = __Vtask_read_outputs__16__y[2U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][0U] 
        = __Vtask_read_outputs__16__y[3U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][1U] 
        = __Vtask_read_outputs__16__y[3U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][2U] 
        = __Vtask_read_outputs__16__y[3U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][3U] 
        = __Vtask_read_outputs__16__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 48)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 49)
                  ->__PVT__cov, "accel_tb_top.sv", 49)->__VnoInFunc_mark(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__12__tag);
    VL_WRITEF("\n=== TEST 3: Signed negative weights (W = -I, A = I) ===\n");
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0U] = 0xffU;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1U] = 0xff00U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2U] = 0xff0000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3U] = 0xff000000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0x100U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0x10000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0x1000000U;
    __Vtask_accel_tb_top__DOT__run_matmul__19__tag = 
        std::string{"signed_weights"};
    __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [3U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [3U];
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 44)
                           ->__PVT__drv, "accel_tb_top.sv", 44)->__VnoInFunc_load_weights(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__19__w_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 45)
                           ->__PVT__drv, "accel_tb_top.sv", 45)->__VnoInFunc_load_activations(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__19__a_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 46)
                           ->__PVT__drv, "accel_tb_top.sv", 46)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 47)
                           ->__PVT__drv, "accel_tb_top.sv", 47)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__23__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][0U] 
        = __Vtask_read_outputs__23__y[0U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][1U] 
        = __Vtask_read_outputs__23__y[0U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][2U] 
        = __Vtask_read_outputs__23__y[0U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][3U] 
        = __Vtask_read_outputs__23__y[0U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][0U] 
        = __Vtask_read_outputs__23__y[1U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][1U] 
        = __Vtask_read_outputs__23__y[1U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][2U] 
        = __Vtask_read_outputs__23__y[1U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][3U] 
        = __Vtask_read_outputs__23__y[1U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][0U] 
        = __Vtask_read_outputs__23__y[2U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][1U] 
        = __Vtask_read_outputs__23__y[2U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][2U] 
        = __Vtask_read_outputs__23__y[2U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][3U] 
        = __Vtask_read_outputs__23__y[2U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][0U] 
        = __Vtask_read_outputs__23__y[3U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][1U] 
        = __Vtask_read_outputs__23__y[3U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][2U] 
        = __Vtask_read_outputs__23__y[3U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][3U] 
        = __Vtask_read_outputs__23__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 48)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 49)
                  ->__PVT__cov, "accel_tb_top.sv", 49)->__VnoInFunc_mark(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__19__tag);
    VL_WRITEF("\n=== TEST 4: Zero activations (Y = 0) ===\n");
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0U] = 0x4030201U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3U] = 0x100f0e0dU;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 0U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0U;
    __Vtask_accel_tb_top__DOT__run_matmul__26__tag = 
        std::string{"zero_activations"};
    __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a
        [3U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows[0U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [0U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows[1U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [1U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows[2U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [2U];
    __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows[3U] 
        = vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w
        [3U];
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 44)
                           ->__PVT__drv, "accel_tb_top.sv", 44)->__VnoInFunc_load_weights(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__26__w_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 45)
                           ->__PVT__drv, "accel_tb_top.sv", 45)->__VnoInFunc_load_activations(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__26__a_rows);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 46)
                           ->__PVT__drv, "accel_tb_top.sv", 46)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 47)
                           ->__PVT__drv, "accel_tb_top.sv", 47)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__30__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][0U] 
        = __Vtask_read_outputs__30__y[0U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][1U] 
        = __Vtask_read_outputs__30__y[0U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][2U] 
        = __Vtask_read_outputs__30__y[0U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[0U][3U] 
        = __Vtask_read_outputs__30__y[0U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][0U] 
        = __Vtask_read_outputs__30__y[1U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][1U] 
        = __Vtask_read_outputs__30__y[1U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][2U] 
        = __Vtask_read_outputs__30__y[1U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[1U][3U] 
        = __Vtask_read_outputs__30__y[1U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][0U] 
        = __Vtask_read_outputs__30__y[2U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][1U] 
        = __Vtask_read_outputs__30__y[2U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][2U] 
        = __Vtask_read_outputs__30__y[2U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[2U][3U] 
        = __Vtask_read_outputs__30__y[2U][3U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][0U] 
        = __Vtask_read_outputs__30__y[3U][0U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][1U] 
        = __Vtask_read_outputs__30__y[3U][1U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][2U] 
        = __Vtask_read_outputs__30__y[3U][2U];
    vlSelf->accel_tb_top__DOT__run_matmul__Vstatic__y[3U][3U] 
        = __Vtask_read_outputs__30__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 48)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 49)
                  ->__PVT__cov, "accel_tb_top.sv", 49)->__VnoInFunc_mark(vlSymsp, __Vtask_accel_tb_top__DOT__run_matmul__26__tag);
    VL_WRITEF("\n=== TEST 5: Back-to-back (identity weights, two consecutive runs) ===\n");
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[0U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[1U] = 0x100U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[2U] = 0x10000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w[3U] = 0x1000000U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 0x4030201U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0x100f0e0dU;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 124)
                           ->__PVT__drv, "accel_tb_top.sv", 124)->__VnoInFunc_load_weights(vlSymsp, vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__w);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 125)
                           ->__PVT__drv, "accel_tb_top.sv", 125)->__VnoInFunc_load_activations(vlSymsp, vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 126)
                           ->__PVT__drv, "accel_tb_top.sv", 126)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 127)
                           ->__PVT__drv, "accel_tb_top.sv", 127)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__36__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][0U] 
        = __Vtask_read_outputs__36__y[0U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][1U] 
        = __Vtask_read_outputs__36__y[0U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][2U] 
        = __Vtask_read_outputs__36__y[0U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][3U] 
        = __Vtask_read_outputs__36__y[0U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][0U] 
        = __Vtask_read_outputs__36__y[1U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][1U] 
        = __Vtask_read_outputs__36__y[1U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][2U] 
        = __Vtask_read_outputs__36__y[1U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][3U] 
        = __Vtask_read_outputs__36__y[1U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][0U] 
        = __Vtask_read_outputs__36__y[2U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][1U] 
        = __Vtask_read_outputs__36__y[2U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][2U] 
        = __Vtask_read_outputs__36__y[2U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][3U] 
        = __Vtask_read_outputs__36__y[2U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][0U] 
        = __Vtask_read_outputs__36__y[3U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][1U] 
        = __Vtask_read_outputs__36__y[3U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][2U] 
        = __Vtask_read_outputs__36__y[3U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][3U] 
        = __Vtask_read_outputs__36__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 128)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[0U] = 0x8070605U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[1U] = 0xc0b0a09U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[2U] = 0x100f0e0dU;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a[3U] = 0x14131211U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 132)
                           ->__PVT__drv, "accel_tb_top.sv", 132)->__VnoInFunc_load_activations(vlSymsp, vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__a);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 133)
                           ->__PVT__drv, "accel_tb_top.sv", 133)->__VnoInFunc_start_and_wait(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 134)
                           ->__PVT__drv, "accel_tb_top.sv", 134)->__VnoInFunc_read_outputs(vlSymsp, __Vtask_read_outputs__40__y);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][0U] 
        = __Vtask_read_outputs__40__y[0U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][1U] 
        = __Vtask_read_outputs__40__y[0U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][2U] 
        = __Vtask_read_outputs__40__y[0U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[0U][3U] 
        = __Vtask_read_outputs__40__y[0U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][0U] 
        = __Vtask_read_outputs__40__y[1U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][1U] 
        = __Vtask_read_outputs__40__y[1U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][2U] 
        = __Vtask_read_outputs__40__y[1U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[1U][3U] 
        = __Vtask_read_outputs__40__y[1U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][0U] 
        = __Vtask_read_outputs__40__y[2U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][1U] 
        = __Vtask_read_outputs__40__y[2U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][2U] 
        = __Vtask_read_outputs__40__y[2U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[2U][3U] 
        = __Vtask_read_outputs__40__y[2U][3U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][0U] 
        = __Vtask_read_outputs__40__y[3U][0U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][1U] 
        = __Vtask_read_outputs__40__y[3U][1U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][2U] 
        = __Vtask_read_outputs__40__y[3U][2U];
    vlSelf->accel_tb_top__DOT__unnamedblk1__DOT__y[3U][3U] 
        = __Vtask_read_outputs__40__y[3U][3U];
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 135)->__VnoInFunc_drain(vlSymsp);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    VL_NULL_CHECK(VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 136)
                  ->__PVT__cov, "accel_tb_top.sv", 136)->__VnoInFunc_mark(vlSymsp, 
                                                                          std::string{"back_to_back"});
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       139);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       139);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       139);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       139);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await vlSelf->__VtrigSched_hb580a06f__0.trigger(0U, 
                                                       nullptr, 
                                                       "@(posedge accel_tb_top.clk)", 
                                                       "accel_tb_top.sv", 
                                                       139);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    co_await VL_NULL_CHECK(accel_tb_top__DOT__env, "accel_tb_top.sv", 140)->__VnoInFunc_report_phase(vlSymsp, accel_tb_top__DOT__ph);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    if ((0U == vlSymsp->TOP__uvm_mini_pkg.g_error_count)) {
        VL_WRITEF("\n*** ALL TESTS PASSED (0 errors) ***\n");
    } else {
        VL_WRITEF("\n*** %0# ERRORS DETECTED ***\n",
                  32,vlSymsp->TOP__uvm_mini_pkg.g_error_count);
    }
    VL_FINISH_MT("accel_tb_top.sv", 147, "");
    vlSelf->__Vm_traceActivity[2U] = 1U;
}
