// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_STD__03A__03ASEMAPHORE__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_STD__03A__03ASEMAPHORE__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_std__03a__03asemaphore__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_std__03a__03asemaphore__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_std__03a__03asemaphore__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_std__03a__03asemaphore__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


class Vaccel_tb_top__Syms;

class Vaccel_tb_top_std__03a__03asemaphore : public VlClass {
  public:

    // DESIGN SPECIFIC STATE
    IData/*31:0*/ __PVT__m_keyCount;
    VlCoroutine __VnoInFunc_get(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_put(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    void __VnoInFunc_try_get(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount, IData/*31:0*/ &try_get__Vfuncrtn);
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_std__03a__03asemaphore(Vaccel_tb_top__Syms* __restrict vlSymsp, IData/*31:0*/ keyCount);
    std::string to_string() const;
    std::string to_string_middle() const;
    ~Vaccel_tb_top_std__03a__03asemaphore();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_std__03a__03asemaphore>& obj);

#endif  // guard
