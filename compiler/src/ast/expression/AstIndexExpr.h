//
// Created by smsqo on 2022/4/25.
//

#ifndef IGNITER_AST_INDEX_EXPR_H
#define IGNITER_AST_INDEX_EXPR_H

#include "ast/AstNode.h"

class AstIndexExpr : public AstNode {
    std::string Indexed;
    vector<AstNode *> Args;
public:
    AstIndexExpr(string name, vector<AstNode *> args) :
            Indexed(name), Args(move(args)) {};

    CodeGen * makeGen(AstContext *parent) override;
};


#endif //IGNITER_AST_INDEX_EXPR_H
