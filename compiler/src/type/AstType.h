//
// Created by smsqo on 2022/4/25.
//

#ifndef IGNITER_AST_TYPE_H
#define IGNITER_AST_TYPE_H


#include <vector>
#include <string>
#include "ast/AstNode.h"

using namespace std;

class AstType : public AstNode {
protected:
    string _name;
    vector<AstType *> compType;
    vector<int> comParam;

public:
    explicit AstType(
            string name,
            vector<AstType *> compType = vector<AstType *>(),
            vector<int> comParam = vector<int>()
    ) : _name(name), compType(move(compType)), comParam(move(comParam)) {};

    CodeGen *makeGen(AstContext *parent) override { return nullptr; }

    string name() { return _name; }
};


#endif //IGNITER_AST_TYPE_H
