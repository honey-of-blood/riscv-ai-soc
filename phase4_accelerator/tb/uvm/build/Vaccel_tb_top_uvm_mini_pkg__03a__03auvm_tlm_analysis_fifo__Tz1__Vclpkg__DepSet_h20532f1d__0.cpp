// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg.h"

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_write(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> item) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_write\n"); );
    // Init
    IData/*31:0*/ __Vtask_try_put__1__Vfuncout;
    __Vtask_try_put__1__Vfuncout = 0;
    // Body
    VL_NULL_CHECK(this->__PVT__m_mbx, "uvm_mini_pkg.sv", 142)->__VnoInFunc_try_put(vlSymsp, item, __Vtask_try_put__1__Vfuncout);
}

VlCoroutine Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_get(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &item) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_get\n"); );
    // Init
    VL_KEEP_THIS;
    // Body
    co_await VL_NULL_CHECK(this->__PVT__m_mbx, "uvm_mini_pkg.sv", 143)->__VnoInFunc_get(vlSymsp, item);
}

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_used(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &used__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1::__VnoInFunc_used\n"); );
    // Init
    IData/*31:0*/ __Vtask_num__3__Vfuncout;
    __Vtask_num__3__Vfuncout = 0;
    // Body
    VL_NULL_CHECK(this->__PVT__m_mbx, "uvm_mini_pkg.sv", 144)->__VnoInFunc_num(vlSymsp, __Vtask_num__3__Vfuncout);
    used__Vfuncrtn = __Vtask_num__3__Vfuncout;
}
