//
// Created by smsqo on 2022/4/27.
//

#ifndef IGNITER_AST_UNIT_EXPR_H
#define IGNITER_AST_UNIT_EXPR_H

#include "ast/AstNode.h"
#include "codegen/expression/UnitGen.h"

class AstUnitExpr: public AstNode {
public:
    explicit AstUnitExpr() {}

    CodeGen * makeGen(AstContext *parent) override {
        return new UnitGen();
    }
};


#endif //IGNITER_AST_UNIT_EXPR_H
