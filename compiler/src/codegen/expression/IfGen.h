//
// Created by smsqo on 2022/4/24.
//

#ifndef IGNITER_IF_GEN_H
#define IGNITER_IF_GEN_H


#include "codegen/CodeGen.h"

class IfGen: public CodeGen {
    CodeGen *cond;
    CodeGen *thenGen;
    CodeGen *elseGen;

public:
    IfGen(CodeGen *cond, CodeGen *thenGen, CodeGen *elseGen);


    Value * generateCode(Module *m, Function *func, IRBuilder<> &bd) override;
};


#endif //IGNITER_IF_GEN_H
