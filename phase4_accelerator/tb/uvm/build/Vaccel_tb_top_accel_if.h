// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP_ACCEL_IF_H_
#define VERILATED_VACCEL_TB_TOP_ACCEL_IF_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top_accel_if final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    CData/*0:0*/ awvalid;
    CData/*0:0*/ awready;
    CData/*3:0*/ wstrb;
    CData/*0:0*/ wvalid;
    CData/*0:0*/ wready;
    CData/*1:0*/ bresp;
    CData/*0:0*/ bvalid;
    CData/*0:0*/ bready;
    CData/*0:0*/ arvalid;
    CData/*0:0*/ arready;
    CData/*1:0*/ rresp;
    CData/*0:0*/ rvalid;
    CData/*0:0*/ rready;
    IData/*31:0*/ awaddr;
    IData/*31:0*/ wdata;
    IData/*31:0*/ araddr;
    IData/*31:0*/ rdata;

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top_accel_if(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top_accel_if();
    VL_UNCOPYABLE(Vaccel_tb_top_accel_if);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vaccel_tb_top_accel_if* obj);

#endif  // guard
