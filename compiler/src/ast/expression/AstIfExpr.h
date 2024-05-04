//
// Created by smsqo on 2022/4/18.
//

#ifndef IGNITER_AST_IF_EXPR_H
#define IGNITER_AST_IF_EXPR_H


#include "ast/AstNode.h"
#include "codegen/expression/IfGen.h"
#include "ast/expression/AstBlockExpr.h"

class AstIfExpr : public AstNode {
    AstNode *cond;
    AstBlockExpr *ifTrue;
    AstBlockExpr *ifFalse;

public:
    AstIfExpr(AstNode *cond, AstBlockExpr *ifTrue, AstBlockExpr *ifFalse);

    CodeGen *makeGen(AstContext *parent) override {

        return new IfGen(
                cond->makeGen(parent),
                ifTrue->makeGen(parent),
                ifFalse->makeGen(parent)
        );
    };
};


#endif //IGNITER_AST_IF_EXPR_H
