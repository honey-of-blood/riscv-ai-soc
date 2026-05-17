// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccel_tb_top.h for the primary calling header

#ifndef VERILATED_VACCEL_TB_TOP___024ROOT_H_
#define VERILATED_VACCEL_TB_TOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vaccel_tb_top_accel_if;
class Vaccel_tb_top_accel_tb_pkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg;
class Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg;
class Vaccel_tb_top_std;
class Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg;
class Vaccel_tb_top_std__03a__03aprocess__Vclpkg;
class Vaccel_tb_top_std__03a__03asemaphore__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_agent__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_test__Vclpkg;
class Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg;


class Vaccel_tb_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top___024root final : public VerilatedModule {
  public:
    // CELLS
    Vaccel_tb_top_std* __PVT__std;
    Vaccel_tb_top_accel_tb_pkg* __PVT__accel_tb_pkg;
    Vaccel_tb_top_uvm_mini_pkg* __PVT__uvm_mini_pkg;
    Vaccel_tb_top_accel_if* __PVT__accel_tb_top__DOT__aif;
    Vaccel_tb_top_std__03a__03asemaphore__Vclpkg* std__03a__03asemaphore__Vclpkg;
    Vaccel_tb_top_std__03a__03aprocess__Vclpkg* std__03a__03aprocess__Vclpkg;
    Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg* std__03a__03amailbox__Tz1__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg* accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg* accel_tb_pkg__03a__03aaccel_driver__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg* accel_tb_pkg__03a__03aaccel_monitor__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg* accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg* accel_tb_pkg__03a__03aaccel_coverage__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg* accel_tb_pkg__03a__03aaccel_env__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg* uvm_mini_pkg__03a__03auvm_phase__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg* uvm_mini_pkg__03a__03auvm_object__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg* uvm_mini_pkg__03a__03auvm_component__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg* uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg* uvm_mini_pkg__03a__03auvm_monitor__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg* uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_agent__Vclpkg* uvm_mini_pkg__03a__03auvm_agent__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg* uvm_mini_pkg__03a__03auvm_env__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_test__Vclpkg* uvm_mini_pkg__03a__03auvm_test__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg* uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ accel_tb_top__DOT__clk;
        CData/*0:0*/ accel_tb_top__DOT__rst_n;
        CData/*0:0*/ accel_tb_top__DOT____Vcellout__dut__s_rvalid;
        CData/*0:0*/ accel_tb_top__DOT____Vcellout__dut__s_bvalid;
        CData/*1:0*/ accel_tb_top__DOT__unnamedblk1__DOT__resp;
        CData/*0:0*/ accel_tb_top__DOT__dut__DOT__done_r;
        CData/*0:0*/ accel_tb_top__DOT__dut__DOT__start_r;
        CData/*1:0*/ accel_tb_top__DOT__dut__DOT__state;
        CData/*2:0*/ accel_tb_top__DOT__dut__DOT__cyc;
        CData/*0:0*/ accel_tb_top__DOT__dut__DOT__wr_pending;
        CData/*5:0*/ accel_tb_top__DOT__dut__DOT__wr_idx_r;
        CData/*3:0*/ accel_tb_top__DOT__dut__DOT__wr_strb_r;
        CData/*7:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__a_s;
        CData/*7:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__a_s;
        CData/*7:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__a_s;
        CData/*7:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__a_s;
        CData/*0:0*/ __VnbaEventTrigger;
        CData/*0:0*/ __VvifTrigger_h04376982__0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__accel_tb_top__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__accel_tb_top__DOT__rst_n__0;
        CData/*0:0*/ __VactContinue;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c0__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c1__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c2__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r0c3__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c0__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c1__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c2__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r1c3__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c0__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c1__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c2__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r2c3__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c0__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c1__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c2__DOT__product;
        SData/*15:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__r3c3__DOT__product;
        IData/*31:0*/ accel_tb_top__DOT____Vcellout__dut__s_rdata;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row3;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row2;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row1;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT____Vcellinp__u_array__w_row0;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__wr_data_r;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__rdata_comb;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__i;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps00;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps01;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps02;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps03;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps10;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps11;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps12;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps13;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps20;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps21;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps22;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps23;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps30;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps31;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps32;
        IData/*31:0*/ accel_tb_top__DOT__dut__DOT__u_array__DOT__ps33;
    };
    struct {
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> accel_tb_top__DOT__run_matmul__Vstatic__y;
        VlUnpacked<IData/*31:0*/, 4> accel_tb_top__DOT__unnamedblk1__DOT__w;
        VlUnpacked<IData/*31:0*/, 4> accel_tb_top__DOT__unnamedblk1__DOT__a;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> accel_tb_top__DOT__unnamedblk1__DOT__y;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> accel_tb_top__DOT__dut__DOT__w_reg;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> accel_tb_top__DOT__dut__DOT__a_reg;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> accel_tb_top__DOT__dut__DOT__y_reg;
        VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hb580a06f__0;
    VlDynamicTriggerScheduler __VdynSched;
    VlEvent __VnbaEvent;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<2> __VicoTriggered;
    VlTriggerVec<5> __VactTriggered;
    VlTriggerVec<5> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vaccel_tb_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vaccel_tb_top___024root(Vaccel_tb_top__Syms* symsp, const char* v__name);
    ~Vaccel_tb_top___024root();
    VL_UNCOPYABLE(Vaccel_tb_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
