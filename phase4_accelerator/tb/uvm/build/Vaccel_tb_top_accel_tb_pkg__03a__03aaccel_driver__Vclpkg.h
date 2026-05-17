// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_DRIVER__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_DRIVER__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component {
  public:

    // DESIGN SPECIFIC STATE
    Vaccel_tb_top_accel_if* __PVT__vif;
    VlCoroutine __VnoInFunc_axi_read(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &data, CData/*1:0*/ &resp, IData/*31:0*/ addr);
  private:
    VlCoroutine __VnoInFunc_axi_read____Vfork_10__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_h79409aa2__0);
    VlCoroutine __VnoInFunc_axi_read____Vfork_11__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h714e1601__0);
    VlCoroutine __VnoInFunc_axi_read____Vfork_12__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hdb7e0641__0);
    VlCoroutine __VnoInFunc_axi_read____Vfork_13__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h72231777__0);
    VlCoroutine __VnoInFunc_axi_read____Vfork_14__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hdb936737__0);
  public:
    VlCoroutine __VnoInFunc_axi_write(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*1:0*/ &resp, IData/*31:0*/ addr, IData/*31:0*/ data, CData/*3:0*/ strb);
  private:
    VlCoroutine __VnoInFunc_axi_write____Vfork_1__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_hed052c15__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_2__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h5e4072d0__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_3__1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ __Vintraval_h39e7fb9c__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_4__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*3:0*/ __Vintraval_h8bb5d09c__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_5__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h271fc011__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_6__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hee291794__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_7__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h5e455a3c__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_8__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_h27221d07__0);
    VlCoroutine __VnoInFunc_axi_write____Vfork_9__1(Vaccel_tb_top__Syms* __restrict vlSymsp, CData/*0:0*/ __Vintraval_hee2a1988__0);
  public:
    void __VnoInFunc_init_signals(Vaccel_tb_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_load_activations(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<IData/*31:0*/, 4> rows);
    VlCoroutine __VnoInFunc_load_weights(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<IData/*31:0*/, 4> rows);
    VlCoroutine __VnoInFunc_read_outputs(Vaccel_tb_top__Syms* __restrict vlSymsp, VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> &y);
    VlCoroutine __VnoInFunc_start_and_wait(Vaccel_tb_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_wait_done(Vaccel_tb_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver>& obj);

#endif  // guard
