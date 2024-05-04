//
// Created by smsqo on 2022/4/22.
//

#ifndef IGNITER_AST_VARIABLE_H
#define IGNITER_AST_VARIABLE_H


#include "AstNode.h"

class AstVariable : public AstNode {
public:
    string Name;

    explicit AstVariable(string name);

    CodeGen *makeGen(AstContext *parent) override;
};

#endif //IGNITER_AST_VARIABLE_H
