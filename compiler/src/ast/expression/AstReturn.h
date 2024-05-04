//
// Created by smsqo on 2022/4/26.
//

#ifndef IGNITER_AST_RETURN_H
#define IGNITER_AST_RETURN_H

#include "ast/AstNode.h"
#include "codegen/expression/ReturnGen.h"

class AstReturn : public AstNode {
    AstNode *value;
public:
    explicit AstReturn(AstNode *value) : value(value) {}

    CodeGen * makeGen(AstContext *parent) override {
        auto gen = value->makeGen(parent);
        parent->pushReturnTy(gen->type);
        return new ReturnGen(gen);
    }
};


#endif //IGNITER_AST_RETURN_H
