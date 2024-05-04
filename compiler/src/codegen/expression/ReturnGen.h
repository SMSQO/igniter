//
// Created by smsqo on 2022/4/26.
//

#ifndef IGNITER_RETURN_GEN_H
#define IGNITER_RETURN_GEN_H

#include "codegen/CodeGen.h"
#include "type/TypeManager.h"

class ReturnGen : public CodeGen {
    CodeGen *value;

public:
    explicit ReturnGen(CodeGen *value) : value(value) {
        type = TypeManager::NOTHING;
    }

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        Value *ret = value->generate(m, func, bd);
        if (!ret)
            throw std::runtime_error("没有返回一个表达式!");
        return bd.CreateRet(ret);
    }
};


#endif //IGNITER_RETURN_GEN_H
