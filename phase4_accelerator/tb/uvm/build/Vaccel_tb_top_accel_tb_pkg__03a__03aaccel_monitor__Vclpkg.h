// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_MONITOR__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_MONITOR__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor {
  public:

    // DESIGN SPECIFIC STATE
    Vaccel_tb_top_accel_if* __PVT__vif;
    VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1> __PVT__ap;
    void __VnoInFunc_run_monitor(Vaccel_tb_top__Syms* __restrict vlSymsp);
  private:
    VlCoroutine __VnoInFunc_run_monitor____Vfork_1__0(Vaccel_tb_top__Syms* __restrict vlSymsp);
    VlCoroutine __VnoInFunc_run_monitor____Vfork_1__1(Vaccel_tb_top__Syms* __restrict vlSymsp);
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor>& obj);

#endif  // guard
