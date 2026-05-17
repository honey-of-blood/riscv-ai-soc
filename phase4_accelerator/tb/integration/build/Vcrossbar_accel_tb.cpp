// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcrossbar_accel_tb__pch.h"
#include "verilated_fst_c.h"

//============================================================
// Constructors

Vcrossbar_accel_tb::Vcrossbar_accel_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcrossbar_accel_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcrossbar_accel_tb::Vcrossbar_accel_tb(const char* _vcname__)
    : Vcrossbar_accel_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcrossbar_accel_tb::~Vcrossbar_accel_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcrossbar_accel_tb___024root___eval_debug_assertions(Vcrossbar_accel_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vcrossbar_accel_tb___024root___eval_static(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___eval_initial(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___eval_settle(Vcrossbar_accel_tb___024root* vlSelf);
void Vcrossbar_accel_tb___024root___eval(Vcrossbar_accel_tb___024root* vlSelf);

void Vcrossbar_accel_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcrossbar_accel_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcrossbar_accel_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcrossbar_accel_tb___024root___eval_static(&(vlSymsp->TOP));
        Vcrossbar_accel_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vcrossbar_accel_tb___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcrossbar_accel_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcrossbar_accel_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vcrossbar_accel_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vcrossbar_accel_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcrossbar_accel_tb___024root___eval_final(Vcrossbar_accel_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_accel_tb::final() {
    Vcrossbar_accel_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcrossbar_accel_tb::hierName() const { return vlSymsp->name(); }
const char* Vcrossbar_accel_tb::modelName() const { return "Vcrossbar_accel_tb"; }
unsigned Vcrossbar_accel_tb::threads() const { return 1; }
void Vcrossbar_accel_tb::prepareClone() const { contextp()->prepareClone(); }
void Vcrossbar_accel_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vcrossbar_accel_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vcrossbar_accel_tb___024root__trace_decl_types(VerilatedFst* tracep);

void Vcrossbar_accel_tb___024root__trace_init_top(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedFst* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcrossbar_accel_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcrossbar_accel_tb___024root*>(voidSelf);
    Vcrossbar_accel_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vcrossbar_accel_tb___024root__trace_decl_types(tracep);
    Vcrossbar_accel_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vcrossbar_accel_tb___024root__trace_register(Vcrossbar_accel_tb___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vcrossbar_accel_tb::trace(VerilatedFstC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcrossbar_accel_tb::trace()' shall not be called after 'VerilatedFstC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vcrossbar_accel_tb___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
