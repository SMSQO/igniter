//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_AST_VARIABLE_DEF_H
#define IGNITER_AST_VARIABLE_DEF_H

#include <iostream>
#include "ast/AstNode.h"
#include "type/AstType.h"

class AstVariableDef: public AstNode {
public:
    string name;
    AstType *type;

public:
    explicit AstVariableDef(string name, AstType *type);

    CodeGen * makeGen(AstContext *parent) override;

    void setType(AstType *ty) { this->type = ty; };
};

#endif //IGNITER_AST_VARIABLE_DEF_H
