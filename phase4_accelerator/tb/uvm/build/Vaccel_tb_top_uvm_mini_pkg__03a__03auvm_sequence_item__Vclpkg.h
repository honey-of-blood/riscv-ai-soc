// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_SEQUENCE_ITEM__VCLPKG_H_
#define VERILATED_VACCEL_TB_TOP_UVM_MINI_PKG__03A__03AUVM_SEQUENCE_ITEM__VCLPKG_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg();
    VL_UNCOPYABLE(Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg.h"

class Vaccel_tb_top__Syms;

class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item : public Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object {
  public:
  private:
    void _ctor_var_reset(Vaccel_tb_top__Syms* __restrict vlSymsp);
  public:
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item(Vaccel_tb_top__Syms* __restrict vlSymsp, std::string name);
    std::string to_string() const;
    std::string to_string_middle() const;
    virtual ~Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item();
};

std::string VL_TO_STRING(const VlClassRef<Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item>& obj);

#endif  // guard
