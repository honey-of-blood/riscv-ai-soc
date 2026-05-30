#include "Vsoc_ph10_tb.h"
#include "verilated.h"
#include "verilated_fst_c.h"
#include <memory>
#include <string>

int main(int argc, char** argv) {
    const std::unique_ptr<VerilatedContext> ctx{new VerilatedContext};
    ctx->commandArgs(argc, argv);
    const std::unique_ptr<Vsoc_ph10_tb> top{new Vsoc_ph10_tb{ctx.get(), "TOP"}};

    VerilatedFstC* tfp = nullptr;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--fst" && i + 1 < argc) {
            Verilated::traceEverOn(true);
            tfp = new VerilatedFstC;
            top->trace(tfp, 99);
            tfp->open(argv[++i]);
        }
    }

    while (!ctx->gotFinish()) {
        ctx->timeInc(1);
        top->eval();
        if (tfp) tfp->dump(ctx->time());
    }

    top->final();
    if (tfp) { tfp->close(); delete tfp; }
    return 0;
}
