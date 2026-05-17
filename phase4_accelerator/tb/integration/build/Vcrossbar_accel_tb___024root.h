// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcrossbar_accel_tb.h for the primary calling header

#ifndef VERILATED_VCROSSBAR_ACCEL_TB___024ROOT_H_
#define VERILATED_VCROSSBAR_ACCEL_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vcrossbar_accel_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcrossbar_accel_tb___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ crossbar_accel_tb__DOT__clk;
        CData/*0:0*/ crossbar_accel_tb__DOT__rst_n;
        CData/*0:0*/ crossbar_accel_tb__DOT__m0_awvalid;
        CData/*3:0*/ crossbar_accel_tb__DOT__m0_wstrb;
        CData/*0:0*/ crossbar_accel_tb__DOT__m0_wvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__m0_bready;
        CData/*0:0*/ crossbar_accel_tb__DOT__m0_arvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__m0_rready;
        CData/*0:0*/ crossbar_accel_tb__DOT__s0_bvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__s0_rvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__s1_bvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__s1_rvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__s2_bvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__s2_rvalid;
        CData/*0:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h5c2f4fa1__0;
        CData/*3:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hbcf1b5af__0;
        CData/*0:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h8d615ae3__0;
        CData/*0:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h98abfbc2__0;
        CData/*0:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h826c049a__0;
        CData/*0:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h746f52ea__0;
        CData/*0:0*/ crossbar_accel_tb__DOT__sram0__DOT__wr_pending;
        CData/*3:0*/ crossbar_accel_tb__DOT__sram0__DOT__wr_strb_r;
        CData/*0:0*/ crossbar_accel_tb__DOT__sram1__DOT__wr_pending;
        CData/*3:0*/ crossbar_accel_tb__DOT__sram1__DOT__wr_strb_r;
        CData/*0:0*/ crossbar_accel_tb__DOT__accel__DOT__done_r;
        CData/*0:0*/ crossbar_accel_tb__DOT__accel__DOT__start_r;
        CData/*1:0*/ crossbar_accel_tb__DOT__accel__DOT__state;
        CData/*2:0*/ crossbar_accel_tb__DOT__accel__DOT__cyc;
        CData/*0:0*/ crossbar_accel_tb__DOT__accel__DOT__wr_pending;
        CData/*5:0*/ crossbar_accel_tb__DOT__accel__DOT__wr_idx_r;
        CData/*3:0*/ crossbar_accel_tb__DOT__accel__DOT__wr_strb_r;
        CData/*7:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__a_s;
        CData/*7:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__a_s;
        CData/*7:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__a_s;
        CData/*7:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__a_s;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__crossbar_accel_tb__DOT__rst_n__0;
        CData/*0:0*/ __VactContinue;
        SData/*13:0*/ crossbar_accel_tb__DOT__sram0__DOT__wr_addr_r;
        SData/*13:0*/ crossbar_accel_tb__DOT__sram1__DOT__wr_addr_r;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c0__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c1__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c2__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r0c3__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c0__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c1__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c2__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r1c3__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c0__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c1__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c2__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r2c3__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c0__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c1__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c2__DOT__product;
        SData/*15:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__r3c3__DOT__product;
        IData/*31:0*/ crossbar_accel_tb__DOT__error_count;
        IData/*31:0*/ crossbar_accel_tb__DOT__m0_awaddr;
        IData/*31:0*/ crossbar_accel_tb__DOT__m0_wdata;
        IData/*31:0*/ crossbar_accel_tb__DOT__m0_araddr;
        IData/*31:0*/ crossbar_accel_tb__DOT__s0_rdata;
        IData/*31:0*/ crossbar_accel_tb__DOT__s1_rdata;
        IData/*31:0*/ crossbar_accel_tb__DOT__s2_rdata;
    };
    struct {
        IData/*31:0*/ crossbar_accel_tb__DOT__unnamedblk1__DOT__rd;
        IData/*31:0*/ crossbar_accel_tb__DOT__xbar__DOT__s;
        IData/*31:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h626fae99__0;
        IData/*31:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_h88a8ba88__0;
        IData/*31:0*/ crossbar_accel_tb__DOT__xbar__DOT____Vlvbound_hc59dc3bb__0;
        IData/*31:0*/ crossbar_accel_tb__DOT__sram0__DOT__wr_data_r;
        IData/*31:0*/ crossbar_accel_tb__DOT__sram1__DOT__wr_data_r;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row3;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row2;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row1;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT____Vcellinp__u_array__w_row0;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__wr_data_r;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__rdata_comb;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__i;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__unnamedblk1__DOT__unnamedblk2__DOT__j;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps00;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps01;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps02;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps03;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps10;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps11;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps12;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps13;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps20;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps21;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps22;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps23;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps30;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps31;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps32;
        IData/*31:0*/ crossbar_accel_tb__DOT__accel__DOT__u_array__DOT__ps33;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_awaddr;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_awvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_awready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_wdata;
        VlUnpacked<CData/*3:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_wstrb;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_wvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_wready;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_bresp;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_bvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_bready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_araddr;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_arvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_arready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_rdata;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_rresp;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_rvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_rready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_awaddr;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_awvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_awready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_wdata;
        VlUnpacked<CData/*3:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_wstrb;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_wvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_wready;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_bresp;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_bvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_bready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_araddr;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_arvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_arready;
        VlUnpacked<IData/*31:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_rdata;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_rresp;
    };
    struct {
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_rvalid;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__s_rready;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_awdec;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__m_ardec;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__wr_grant;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__wr_busy;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__wr_last;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__rd_grant;
        VlUnpacked<CData/*0:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__rd_busy;
        VlUnpacked<CData/*1:0*/, 3> crossbar_accel_tb__DOT__xbar__DOT__rd_last;
        VlUnpacked<IData/*31:0*/, 16384> crossbar_accel_tb__DOT__sram0__DOT__mem;
        VlUnpacked<IData/*31:0*/, 16384> crossbar_accel_tb__DOT__sram1__DOT__mem;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> crossbar_accel_tb__DOT__accel__DOT__w_reg;
        VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> crossbar_accel_tb__DOT__accel__DOT__a_reg;
        VlUnpacked<VlUnpacked<IData/*31:0*/, 4>, 4> crossbar_accel_tb__DOT__accel__DOT__y_reg;
        VlUnpacked<CData/*0:0*/, 7> __Vm_traceActivity;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h5c6c16d3__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<3> __VactTriggered;
    VlTriggerVec<3> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcrossbar_accel_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcrossbar_accel_tb___024root(Vcrossbar_accel_tb__Syms* symsp, const char* v__name);
    ~Vcrossbar_accel_tb___024root();
    VL_UNCOPYABLE(Vcrossbar_accel_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
