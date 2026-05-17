// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_TLM_ANALYSIS_FIFO__TZ1__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_TLM_ANALYSIS_FIFO__TZ1__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item;
class Vaccel_tb_top_std__03a__03amailbox__Tz1;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vaccel_tb_top__Syms;

class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1 : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlClassRef<Vaccel_tb_top_std__03a__03amailbox__Tz1> __PVT__m_mbx;
    VlCoroutine __VnoInFunc_get(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &item);
    void __VnoInFunc_used(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &used__Vfuncrtn);
    void __VnoInFunc_write(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> item);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ depth);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1>& obj);

#endif  // guard
