//
// Created by smsqo on 2022/4/27.
//

#ifndef IGNITER_NOT_GEN_H
#define IGNITER_NOT_GEN_H

#include "codegen/CodeGen.h"
#include "type/TypeManager.h"

class UnaryGen : public CodeGen {
    int op;
    CodeGen *content;

public:
    explicit UnaryGen(int op, CodeGen *cont) : op(op), content(cont) {
        type = TypeManager::BOOLEAN;
    }

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        if (op == '!')
            return bd.CreateNot(content->generate(m, func, bd));
        throw runtime_error("could not find unary operator: " + to_string(op));
    }
};


#endif //IGNITER_NOT_GEN_H
