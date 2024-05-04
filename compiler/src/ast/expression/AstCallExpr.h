//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_AST_CALL_EXPR_H
#define IGNITER_AST_CALL_EXPR_H

#include <iostream>
#include <string>
#include <vector>
#include "ast/AstNode.h"

class AstCallExpr: public AstNode {
    std::string Callee;
    std::vector<AstNode *> Args;

public:
    AstCallExpr(std::string Callee, std::vector<AstNode *> Args);

    CodeGen *makeGen(AstContext *parent) override;
};


#endif //IGNITER_AST_CALL_EXPR_H
