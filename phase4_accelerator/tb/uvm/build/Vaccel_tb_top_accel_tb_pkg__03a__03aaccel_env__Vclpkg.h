// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_ENV__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_ENV__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env {
  public:

    // DESIGN SPECIFIC STATE
    Vaccel_tb_top_accel_if* __PVT__m_vif;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver> __PVT__drv;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor> __PVT__mon;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard> __PVT__sb;
    VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage> __PVT__cov;
    virtual void __VnoInFunc_build_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
    VlCoroutine __VnoInFunc_drain(Vaccel_tb_top__Syms* __restrict vlSymsp);
    virtual VlCoroutine __VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env>& obj);

#endif  // guard
