// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_STD__03A__03APROCESS__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_STD__03A__03APROCESS__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_std__03a__03aprocess;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_std__03a__03aprocess__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_std__03a__03aprocess__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_std__03a__03aprocess__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_std__03a__03aprocess__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __VnoInFunc_self(VlProcessRef vlProcess, Vaccel_tb_top__Syms* __restrict vlSymsp, VlClassRef<Vaccel_tb_top_std__03a__03aprocess> &self__Vfuncrtn);
};


class Vaccel_tb_top__Syms;

class Vaccel_tb_top_std__03a__03aprocess : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    VlProcessRef __PVT__m_process;
    VlCoroutine __VnoInFunc_await(Vaccel_tb_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_get_randstate(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string &get_randstate__Vfuncrtn);
    void __VnoInFunc_kill(Vaccel_tb_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_resume(Vaccel_tb_top__Syms* __restrict vlSymsp);
    void __VnoInFunc_set_randstate(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string s);
    void __VnoInFunc_set_status(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ s);
    void __VnoInFunc_status(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ &status__Vfuncrtn);
    void __VnoInFunc_suspend(Vaccel_tb_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_std__03a__03aprocess(Vaccel_tb_top__Syms* __restrict vlSymsp);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vaccel_tb_top_std__03a__03aprocess();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_std__03a__03aprocess>& obj);

#endif  // guard
