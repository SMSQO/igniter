//
// Created by smsqo on 2022/4/20.
//

#ifndef IGNITER_AST_VAL_ASSIGN_H
#define IGNITER_AST_VAL_ASSIGN_H


#include "ast/AstVariable.h"
#include "ast/function/AstVariableDef.h"
#include "AstNode.h"


class AstValAssign : public AstNode {
    AstVariableDef *Variable;
    AstNode *expr;
public:
    AstValAssign(AstVariableDef *var, AstNode *expr);

    CodeGen *makeGen(AstContext *parent) override;
};


#endif //IGNITER_AST_VAL_ASSIGN_H
