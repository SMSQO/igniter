//
// Created by smsqo on 2022/4/24.
//

#ifndef IGNITER_AST_BOOLEAN_H
#define IGNITER_AST_BOOLEAN_H


#include "ast/AstNode.h"
#include "codegen/expression/BooleanGen.h"

class AstBoolean: public AstNode {
    bool value;
public:
    explicit AstBoolean(bool value): value(value) {}

    CodeGen * makeGen(AstContext *parent) override {
        return new BooleanGen(value);
    }
};


#endif //IGNITER_AST_BOOLEAN_H
