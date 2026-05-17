// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_STD__03A__03AMAILBOX__TZ1__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_STD__03A__03AMAILBOX__TZ1__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vaccel_tb_top__Syms;

class Vaccel_tb_top_std__03a__03amailbox__Tz1 : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_bound;
    VlQueue<VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item>> __PVT__m_queue;
    VlCoroutine __VnoInFunc_get(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message);
    void __VnoInFunc_num(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &num__Vfuncrtn);
    VlCoroutine __VnoInFunc_peek(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message);
    VlCoroutine __VnoInFunc_put(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> message);
    void __VnoInFunc_try_get(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message, IData/*31:0*/ &try_get__Vfuncrtn);
    void __VnoInFunc_try_peek(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> &message, IData/*31:0*/ &try_peek__Vfuncrtn);
    void __VnoInFunc_try_put(Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item> message, IData/*31:0*/ &try_put__Vfuncrtn);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_std__03a__03amailbox__Tz1(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ bound);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vaccel_tb_top_std__03a__03amailbox__Tz1();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_std__03a__03amailbox__Tz1>& obj);

#endif  // guard
