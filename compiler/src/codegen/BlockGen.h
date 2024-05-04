//
// Created by smsqo on 2022/4/24.
//

#ifndef IGNITER_BLOCK_GEN_H
#define IGNITER_BLOCK_GEN_H


#include "CodeGen.h"
#include "type/TypeManager.h"

class BlockGen : public CodeGen {
    vector<CodeGen *> lines;
public:
    explicit BlockGen(vector<CodeGen *> lines, Type *ty) : lines(move(lines)) {
        type = ty;
    }

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        Value *ret = Constant::getNullValue(TypeManager::UNIT);
        for (auto it: lines) {
            ret = it->generate(m, func, bd);
        }
        return ret;
    }
};


#endif //IGNITER_BLOCK_GEN_H
