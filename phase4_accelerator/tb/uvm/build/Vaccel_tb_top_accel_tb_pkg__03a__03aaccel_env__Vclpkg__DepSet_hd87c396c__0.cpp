// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg.h"

VlCoroutine Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_drain(Vaccel_tb_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env::__VnoInFunc_drain\n"); );
    // Init
    VL_KEEP_THIS;
    IData/*31:0*/ __Vtask_used__5__Vfuncout;
    __Vtask_used__5__Vfuncout = 0;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> __Vtask_get__6__item;
    // Body
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> item;
    while ((0U < ([&]() {
                    VL_NULL_CHECK(VL_NULL_CHECK(this->__PVT__mon, "accel_tb_pkg.sv", 293)
                                  ->__PVT__ap, "accel_tb_pkg.sv", 293)
                  ->__VnoInFunc_used(vlSymsp, __Vtask_used__5__Vfuncout);
                }(), __Vtask_used__5__Vfuncout))) {
        co_await VL_NULL_CHECK(VL_NULL_CHECK(this->__PVT__mon, "accel_tb_pkg.sv", 294)
                               ->__PVT__ap, "accel_tb_pkg.sv", 294)->__VnoInFunc_get(vlSymsp, __Vtask_get__6__item);
        item = __Vtask_get__6__item;
        VL_NULL_CHECK(this->__PVT__sb, "accel_tb_pkg.sv", 295)->__VnoInFunc_process_item(vlSymsp, item);
    }
}
