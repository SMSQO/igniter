//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_AST_BINARY_EXPR_H
#define IGNITER_AST_BINARY_EXPR_H


#include "ast/AstNode.h"

class AstBinaryExpr: public AstNode {
    int Op; // 如果是单独的字符(如'+'), 则就是字符本身的ASCII码;
    // 如果不是, 则尝试查看`igniter.tab.hpp`中的`enum yytokentype`枚举.

    AstNode *LHS, *RHS;

public:
    AstBinaryExpr(int Op, AstNode *LHS, AstNode *RHS);

    CodeGen *makeGen(AstContext *parent) override;
};


#endif //IGNITER_AST_BINARY_EXPR_H
