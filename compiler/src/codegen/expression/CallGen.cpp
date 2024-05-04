//
// Created by smsqo on 2022/4/23.
//

#include "CallGen.h"

Value *CallGen::generateCode(Module *m, Function *fun, IRBuilder<> &bd) {
    auto llvmFunc = func->generateCode(m, m->getContext());

    vector<Value *> argVs;
    argVs.reserve(params.size());
    for (auto *it : params) {
        argVs.push_back(it->generate(m, fun, bd));
        if (!argVs.back())
            return nullptr;
    }
    return bd.CreateCall(llvmFunc, argVs);
}
