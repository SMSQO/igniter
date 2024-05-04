//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_AST_NUMBER_H
#define IGNITER_AST_NUMBER_H

#include <cstdint>
#include "ast/AstNode.h"

class AstNumber : public AstNode {
};

class AstNumberInt : public AstNumber {
    int64_t val;
public:
    explicit AstNumberInt(int val);

    CodeGen *makeGen(AstContext *parent) override;

    int value() { return val; }
};


class AstNumberDouble : public AstNumber {
    double val;
public:
    explicit AstNumberDouble(double val);

    CodeGen *makeGen(AstContext *parent) override;
};

#endif //IGNITER_AST_NUMBER_H
