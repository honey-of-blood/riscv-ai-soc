// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_SCOREBOARD__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_ACCEL_TB_PKG__03A__03AACCEL_SCOREBOARD__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __PVT__y_valid;
    IData/*31:0*/ __PVT__pass_count;
    IData/*31:0*/ __PVT__fail_count;
    VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> __PVT__sw_w;
    VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> __PVT__sw_a;
    VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> __PVT__exp_y;
    void __VnoInFunc_compute_expected(Vaccel_tb_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_process_item(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> item);
    virtual VlCoroutine __VnoInFunc_report_phase(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase> phase);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name, VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component> parent);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard>& obj);

#endif  // guard
