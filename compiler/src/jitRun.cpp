//
// Created by smsqo on 2022/4/19.
//

#include "KaleidoscopeJIT.h"

int jitRun(Module *TheModule) {
    auto *jit = new llvm::orc::KaleidoscopeJIT();
    jit->addModule(std::unique_ptr<Module>(TheModule));
    auto mainFunc = jit->findSymbol("main");
    if (!mainFunc) {
        cout << "fun main() was not defined." << endl;
        return 1;
    }
    int (*FP)() = (int (*)()) mainFunc.getAddress().get();
    auto result = FP();
    cout << endl << "Evaluated to: " << result << endl;
    return 0;
}

