//
// Created by smsqo on 2022/4/22.
//

#ifndef IGNITER_PARAM_GEN_H
#define IGNITER_PARAM_GEN_H


#include "codegen/CodeGen.h"
#include <llvm/IR/ValueSymbolTable.h>

class ParamGen : public CodeGen {
    string name;
public:
    ParamGen(string name, Type *type) : name(move(name)) {
        this->type = type;
    }

    llvm::Value *generateCode(llvm::Module *m, llvm::Function *func, llvm::IRBuilder<> &) override {
        if (!value) {
            auto *tbl = func->getValueSymbolTable();
            auto *v = tbl->lookup(name);
            return v;
        }
        return value;
    }
};


#endif //IGNITER_PARAM_GEN_H
