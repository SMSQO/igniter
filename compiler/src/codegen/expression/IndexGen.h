//
// Created by smsqo on 2022/4/26.
//

#ifndef IGNITER_INDEX_GEN_H
#define IGNITER_INDEX_GEN_H

#include "codegen/CodeGen.h"

class IndexGen : public CodeGen {
    CodeGen *indexed;

    vector<CodeGen *> args;

public:
    explicit IndexGen(CodeGen *indexed, vector<CodeGen *> args) :
            indexed(indexed), args(move(args)) {}


            Value * generateCode(Module *m, Function *func, IRBuilder<> &bd) override;
};


#endif //IGNITER_INDEX_GEN_H
