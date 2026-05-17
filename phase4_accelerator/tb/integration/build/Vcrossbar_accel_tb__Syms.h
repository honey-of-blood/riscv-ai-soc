// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCROSSBAR_ACCEL_TB__SYMS_H_
#define VERILATED_VCROSSBAR_ACCEL_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcrossbar_accel_tb.h"

// INCLUDE MODULE CLASSES
#include "Vcrossbar_accel_tb___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vcrossbar_accel_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcrossbar_accel_tb* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcrossbar_accel_tb___024root   TOP;

    // CONSTRUCTORS
    Vcrossbar_accel_tb__Syms(VerilatedContext* contextp, const char* namep, Vcrossbar_accel_tb* modelp);
    ~Vcrossbar_accel_tb__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
