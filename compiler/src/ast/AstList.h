//
// Created by smsqo on 2022/4/16.
//

#ifndef IGNITER_AST_LIST_H
#define IGNITER_AST_LIST_H


#include "AstNode.h"

class AstList : public AstNode {
public:
    std::vector<AstNode *> Lines;
public:
    AstList();

    explicit AstList(AstNode *curr);

    AstList(AstList *prev, AstNode *curr);

    CodeGen *makeGen(AstContext *parent) override { return nullptr; };
};


#endif //IGNITER_AST_LIST_H
