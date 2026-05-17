// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccel_tb_top.h for the primary calling header

#include "Vaccel_tb_top__pch.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg.h"

void Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_get_full_name(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &get_full_name__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component::__VnoInFunc_get_full_name\n"); );
    // Init
    std::string __Vtask_get_full_name__1__Vfuncout;
    std::string __Vfunc_get_name__2__Vfuncout;
    std::string __Vfunc_get_name__3__Vfuncout;
    // Body
    {
        if ((VlNull{} != this->__PVT__m_parent)) {
            get_full_name__Vfuncrtn = VL_CONCATN_NNN(
                                                     VL_CONCATN_NNN(
                                                                    ([&]() {
                            VL_NULL_CHECK(this->__PVT__m_parent, "uvm_mini_pkg.sv", 67)
                                                                     ->__VnoInFunc_get_full_name(vlSymsp, __Vtask_get_full_name__1__Vfuncout);
                        }(), __Vtask_get_full_name__1__Vfuncout), 
                                                                    std::string{"."}), 
                                                     ([&]() {
                        this->__VnoInFunc_get_name(vlSymsp, __Vfunc_get_name__2__Vfuncout);
                    }(), __Vfunc_get_name__2__Vfuncout));
            goto __Vlabel1;
        }
        this->__VnoInFunc_get_name(vlSymsp, __Vfunc_get_name__3__Vfuncout);
        get_full_name__Vfuncrtn = __Vfunc_get_name__3__Vfuncout;
        __Vlabel1: ;
    }
}
