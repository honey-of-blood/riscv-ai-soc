// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VACCEL_TB_TOP_H_
#define VERILATED_VACCEL_TB_TOP_H_  // guard

#include "verilated.h"

class Vaccel_tb_top__Syms;
class Vaccel_tb_top___024root;
class VerilatedFstC;
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


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vaccel_tb_top VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vaccel_tb_top__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vaccel_tb_top_std* const __PVT__std;
    Vaccel_tb_top_accel_tb_pkg* const __PVT__accel_tb_pkg;
    Vaccel_tb_top_uvm_mini_pkg* const __PVT__uvm_mini_pkg;
    Vaccel_tb_top_accel_if* const __PVT__accel_tb_top__DOT__aif;
    Vaccel_tb_top_std__03a__03asemaphore__Vclpkg* const std__03a__03asemaphore__Vclpkg;
    Vaccel_tb_top_std__03a__03aprocess__Vclpkg* const std__03a__03aprocess__Vclpkg;
    Vaccel_tb_top_std__03a__03amailbox__Tz1__Vclpkg* const std__03a__03amailbox__Tz1__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg* const accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_driver__Vclpkg* const accel_tb_pkg__03a__03aaccel_driver__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_monitor__Vclpkg* const accel_tb_pkg__03a__03aaccel_monitor__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg* const accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_coverage__Vclpkg* const accel_tb_pkg__03a__03aaccel_coverage__Vclpkg;
    Vaccel_tb_top_accel_tb_pkg__03a__03aaccel_env__Vclpkg* const accel_tb_pkg__03a__03aaccel_env__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_phase__Vclpkg* const uvm_mini_pkg__03a__03auvm_phase__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_object__Vclpkg* const uvm_mini_pkg__03a__03auvm_object__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_component__Vclpkg* const uvm_mini_pkg__03a__03auvm_component__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg* const uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_monitor__Vclpkg* const uvm_mini_pkg__03a__03auvm_monitor__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg* const uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_agent__Vclpkg* const uvm_mini_pkg__03a__03auvm_agent__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_env__Vclpkg* const uvm_mini_pkg__03a__03auvm_env__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_test__Vclpkg* const uvm_mini_pkg__03a__03auvm_test__Vclpkg;
    Vaccel_tb_top_uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg* const uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vaccel_tb_top___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vaccel_tb_top(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vaccel_tb_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vaccel_tb_top();
  private:
    VL_UNCOPYABLE(Vaccel_tb_top);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedFstC* tfp, int levels, int options = 0);
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
    std::unique_ptr<VerilatedTraceConfig> traceConfig() const override final;
};

#endif  // guard
