//
// Created by smsqo on 2022/4/26.
//

#ifndef IGNITER_AST_LAMBDA_EXPR_H
#define IGNITER_AST_LAMBDA_EXPR_H

#include "ast/AstNode.h"
#include "type/AstType.h"

class AstLambdaExpr : public AstNode {
    vector<pair<string, AstType *>> args;
    AstType *returnType; // however, we couldn't infer this smoothly,
    // unless we ignite the type-infer feature

public:
    explicit AstLambdaExpr() {

    }

    CodeGen *makeGen(AstContext *parent) override {
        return nullptr;
    }

    void setReturnType(AstType *type) { returnType = type; }
};


#endif //IGNITER_AST_LAMBDA_EXPR_H
