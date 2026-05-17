// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaccel_tb_top__pch.h"
#include "verilated_fst_c.h"

//============================================================
// Constructors

Vaccel_tb_top::Vaccel_tb_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaccel_tb_top__Syms(contextp(), _vcname__, this)}
    , __PVT__std{vlSymsp->TOP.__PVT__std}
    , __PVT__accel_tb_pkg{vlSymsp->TOP.__PVT__accel_tb_pkg}
    , __PVT__uvm_mini_pkg{vlSymsp->TOP.__PVT__uvm_mini_pkg}
    , __PVT__accel_tb_top__DOT__aif{vlSymsp->TOP.__PVT__accel_tb_top__DOT__aif}
    , std__03a__03asemaphore__Vclpkg{vlSymsp->TOP.std__03a__03asemaphore__Vclpkg}
    , std__03a__03aprocess__Vclpkg{vlSymsp->TOP.std__03a__03aprocess__Vclpkg}
    , std__03a__03amailbox__Tz1__Vclpkg{vlSymsp->TOP.std__03a__03amailbox__Tz1__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_seq_item__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_driver__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_driver__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_monitor__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_monitor__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_scoreboard__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_coverage__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_coverage__Vclpkg}
    , accel_tb_pkg__03a__03aaccel_env__Vclpkg{vlSymsp->TOP.accel_tb_pkg__03a__03aaccel_env__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_phase__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_phase__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_object__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_object__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_component__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_component__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_sequence_item__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_monitor__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_monitor__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_scoreboard__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_agent__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_agent__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_env__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_env__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_test__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_test__Vclpkg}
    , uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg{vlSymsp->TOP.uvm_mini_pkg__03a__03auvm_tlm_analysis_fifo__Tz1__Vclpkg}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vaccel_tb_top::Vaccel_tb_top(const char* _vcname__)
    : Vaccel_tb_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaccel_tb_top::~Vaccel_tb_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaccel_tb_top___024root___eval_debug_assertions(Vaccel_tb_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vaccel_tb_top___024root___eval_static(Vaccel_tb_top___024root* vlSelf);
void Vaccel_tb_top___024root___eval_initial(Vaccel_tb_top___024root* vlSelf);
void Vaccel_tb_top___024root___eval_settle(Vaccel_tb_top___024root* vlSelf);
void Vaccel_tb_top___024root___eval(Vaccel_tb_top___024root* vlSelf);

void Vaccel_tb_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaccel_tb_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaccel_tb_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->clearTriggeredEvents();
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaccel_tb_top___024root___eval_static(&(vlSymsp->TOP));
        Vaccel_tb_top___024root___eval_initial(&(vlSymsp->TOP));
        Vaccel_tb_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaccel_tb_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaccel_tb_top::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty(); }

uint64_t Vaccel_tb_top::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vaccel_tb_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaccel_tb_top___024root___eval_final(Vaccel_tb_top___024root* vlSelf);

VL_ATTR_COLD void Vaccel_tb_top::final() {
    Vaccel_tb_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaccel_tb_top::hierName() const { return vlSymsp->name(); }
const char* Vaccel_tb_top::modelName() const { return "Vaccel_tb_top"; }
unsigned Vaccel_tb_top::threads() const { return 1; }
void Vaccel_tb_top::prepareClone() const { contextp()->prepareClone(); }
void Vaccel_tb_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaccel_tb_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaccel_tb_top___024root__trace_decl_types(VerilatedFst* tracep);

void Vaccel_tb_top___024root__trace_init_top(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedFst* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaccel_tb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccel_tb_top___024root*>(voidSelf);
    Vaccel_tb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vaccel_tb_top___024root__trace_decl_types(tracep);
    Vaccel_tb_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaccel_tb_top___024root__trace_register(Vaccel_tb_top___024root* vlSelf, VerilatedFst* tracep);

VL_ATTR_COLD void Vaccel_tb_top::trace(VerilatedFstC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaccel_tb_top::trace()' shall not be called after 'VerilatedFstC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vaccel_tb_top___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
