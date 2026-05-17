// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_COMPONENT__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_COMPONENT__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object {
  public:

    // DESIGN SPECIFIC STATE
    VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> __PVT__m_parent;
    virtual void __VnoInFunc_build_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
    virtual void __VnoInFunc_connect_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
    virtual void __VnoInFunc_get_full_name(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &get_full_name__Vfuncrtn);
    virtual VlCoroutine __VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
    virtual void __VnoInFunc_run_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component>& obj);

#endif  // guard
