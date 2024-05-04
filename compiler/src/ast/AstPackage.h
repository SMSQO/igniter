//
// Created by smsqo on 2022/4/17.
//

#ifndef IGNITER_AST_PACKAGE_H
#define IGNITER_AST_PACKAGE_H


#include "AstNode.h"
#include "AstList.h"

using namespace std;

class AstPackage {
public:
    vector<AstNode *> Lines;

public:
    explicit AstPackage(AstContext &context): context(context) {};

    void makeGen(AstContext *parent);

    void generate();
private:

    AstContext &context;
    vector<CodeGen *> gens;
};


#endif //IGNITER_AST_PACKAGE_H
