// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VACCEL_TB_TOP__SYMS_H_
#define VERILATED_VACCEL_TB_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vaccel_tb_top.h"

// INCLUDE MODULE CLASSES
#include "Vaccel_tb_top___024root.h"
#include "Vaccel_tb_top___024unit.h"
#include "Vaccel_tb_top_std.h"
#include "Vaccel_tb_top_accel_tb_pkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg.h"
#include "Vaccel_tb_top_accel_if.h"
#include "Vaccel_tb_top_std__03a__03asemaphore__Vclpkg.h"
#include "Vaccel_tb_top_std__03a__03aprocess__Vclpkg.h"
#include "Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg.h"
#include "Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_agent__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_test__Vclpkg.h"
#include "Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vaccel_tb_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vaccel_tb_top* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    std::vector<VlEvent*> __Vm_triggeredEvents;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vaccel_tb_top___024root        TOP;
    Vaccel_tb_top_accel_tb_pkg     TOP__accel_tb_pkg;
    Vaccel_tb_top_accel_if         TOP__accel_tb_top__DOT__aif;
    Vaccel_tb_top_std              TOP__std;
    Vaccel_tb_top_uvm_mini_pkg     TOP__uvm_mini_pkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_coverage__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_driver__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_env__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_monitor__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg TOP__accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg;
    Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg TOP__std__03a__03amailbox__Tz1__Vclpkg;
    Vaccel_tb_top_std__03a__03aprocess__Vclpkg TOP__std__03a__03aprocess__Vclpkg;
    Vaccel_tb_top_std__03a__03asemaphore__Vclpkg TOP__std__03a__03asemaphore__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_agent__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_agent__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_component__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_env__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_monitor__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_object__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_phase__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_test__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_test__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg TOP__uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg;

    // SCOPE NAMES
    VerilatedScope __Vscope_std__process;
    VerilatedScope __Vscope_std__process__suspend;

    // CONSTRUCTORS
    Vaccel_tb_top__Syms(VerilatedContext* contextp, const char* namep, Vaccel_tb_top* modelp);
    ~Vaccel_tb_top__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
    void enqueueTriggeredEventForClearing(VlEvent& event) {
#ifdef VL_DEBUG
        if (VL_UNLIKELY(!event.isTriggered())) {
            VL_FATAL_MT(__FILE__, __LINE__, __FILE__, "event passed to 'enqueueTriggeredEventForClearing' was not triggered");
        }
#endif
        __Vm_triggeredEvents.push_back(&event);
    }
    void clearTriggeredEvents() {
        for (const auto eventp : __Vm_triggeredEvents) eventp->clearTriggered();
        __Vm_triggeredEvents.clear();
    }
};

#endif  // guard
