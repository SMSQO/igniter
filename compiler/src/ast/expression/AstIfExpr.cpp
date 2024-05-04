//
// Created by smsqo on 2022/4/18.
//

#include "AstIfExpr.h"

AstIfExpr::AstIfExpr(AstNode *cond, AstBlockExpr *ifTrue, AstBlockExpr *ifFalse)
        : cond(cond), ifTrue(ifTrue), ifFalse(ifFalse) {}
