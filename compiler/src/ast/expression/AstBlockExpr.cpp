//
// Created by smsqo on 2022/4/19.
//

#include "AstBlockExpr.h"
#include "ast/AstNode.h"

#include <utility>

AstBlockExpr::AstBlockExpr(vector<AstNode *> Lines) : Lines(std::move(Lines)) {}
