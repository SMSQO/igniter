//
// Created by smsqo on 2022/4/23.
//

#ifndef IGNITER_CALL_GEN_H
#define IGNITER_CALL_GEN_H


#include "codegen/CodeGen.h"
#include "ast/function/AstFunctionDef.h"

class CallGen : public CodeGen {
    FunctionGen *func;
    vector<CodeGen *> params;

public:

    explicit CallGen(FunctionGen *func, vector<CodeGen *> params)
            : func(func), params(move(params)) {
        type = func->returnType();
    };

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override;
};


#endif //IGNITER_CALL_GEN_H
