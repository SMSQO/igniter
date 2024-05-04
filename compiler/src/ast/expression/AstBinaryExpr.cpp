//
// Created by smsqo on 2022/4/15.
//

#include "AstBinaryExpr.h"
#include "codegen/expression/BinaryGen.h"

AstBinaryExpr::AstBinaryExpr(int Op, AstNode *LHS, AstNode *RHS) :
        Op(Op), LHS(LHS), RHS(RHS) {}

CodeGen *AstBinaryExpr::makeGen(AstContext *parent) {
    return new BinaryGen(LHS->makeGen(parent), RHS->makeGen(parent), Op);
}


