//
// Created by smsqo on 2022/4/15.
//

#include "AstCallExpr.h"
#include "llvm/IR/Function.h"
#include "codegen/expression/CallGen.h"

#include <utility>

AstCallExpr::AstCallExpr(std::string Callee, std::vector<AstNode *> Args) :
        Callee(std::move(Callee)), Args(std::move(Args)) {}

CodeGen *AstCallExpr::makeGen(AstContext *parent) {
    FunctionGen *func = parent->getFunctionGen(Callee);

    if (func->paramSize() != Args.size()) {
        char text[0x100];
        sprintf(text, "function %s needs %d arguments, but %ld was provided on calling", Callee.c_str(),
                func->paramSize(), Args.size());
        throw std::runtime_error(text);
    }

    auto params = vector<CodeGen *>();
    params.reserve(Args.size());
    for (auto *it: Args) {
        params.push_back(it->makeGen(parent));
    }
    return new CallGen(func, params);
}


