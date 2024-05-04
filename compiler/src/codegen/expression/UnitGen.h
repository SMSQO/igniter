//
// Created by smsqo on 2022/4/27.
//

#ifndef IGNITER_UNIT_GEN_H
#define IGNITER_UNIT_GEN_H

#include "codegen/CodeGen.h"
#include "type/TypeManager.h"

class UnitGen : public CodeGen {
public:
    explicit UnitGen() {}

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        return TypeManager::UNIT_INSTANCE;
    }
};


#endif //IGNITER_UNIT_GEN_H
