//
// Created by smsqo on 2022/4/24.
//

#ifndef IGNITER_BOOLEAN_GEN_H
#define IGNITER_BOOLEAN_GEN_H


#include "codegen/CodeGen.h"
#include "type/TypeManager.h"

class BooleanGen : public CodeGen {
    bool value;
public:
    explicit BooleanGen(bool value) : value(value) {
        type = TypeManager::BOOLEAN;
    }

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        return ConstantInt::get(TypeManager::BOOLEAN, value ? 1 : 0);
    }
};


#endif //IGNITER_BOOLEAN_GEN_H
