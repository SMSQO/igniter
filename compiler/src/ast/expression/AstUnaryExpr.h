//
// Created by smsqo on 2022/4/27.
//

#ifndef IGNITER_AST_NOT_EXPR_H
#define IGNITER_AST_NOT_EXPR_H

#include "ast/AstNode.h"
#include "codegen/expression/UnaryGen.h"

class AstUnaryExpr : public AstNode {
    int Op;
    AstNode *content;
public:
    explicit AstUnaryExpr(int op, AstNode *cont) : content(cont), Op(op) {}

    CodeGen *makeGen(AstContext *parent) override {
        return new UnaryGen(Op, content->makeGen(parent));
    }
};


#endif //IGNITER_AST_NOT_EXPR_H
