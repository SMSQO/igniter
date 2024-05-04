//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_LEX_H
#define IGNITER_LEX_H

#include <vector>
#include "type/AstType.h"
#include "ast/AstNode.h"
#include "ast/AstPackage.h"

using namespace std;

class AstNode;

class AstType;

extern AstPackage *currentPackage;

AstNode *makeNumber(double number);

AstNode *makeNumber(int number);

AstNode *makeBoolean(bool value);

AstNode *makeUnit();

AstNode *makeCall(const char *callee, const AstNode *args);

AstNode *makeIndex(const char *callee, const AstNode *args);

AstNode *makeReturn(AstNode *node);

AstNode *makeValue(const char *name);

AstNode *makeVariableDef(const char *name, AstNode *type);

AstList *link();

AstList *link(AstNode *curr);

AstList *link(AstNode *prev, AstNode *curr);

AstNode *makeBinaryExpr(AstNode *lhs, int optr, AstNode *rhs);

AstNode *makeUnaryExpr(int optr, AstNode *content);

AstNode *makePrototype(const char *name, AstNode *params);

AstNode *makeFunDef(AstNode *prototype, AstNode *body);

AstNode *makeImport(AstNode *prototype);

AstPackage *makePackage(AstNode *lines);

AstNode *makeIf(AstNode *cond, AstNode *ifTrue, AstNode *ifFalse);

AstNode *makeExprBlock(AstNode *list);

AstNode *makeExprBlock();

AstNode *makeAssignVal(AstNode *variable, AstNode *expr);

AstNode *setPrototypeReturnType(AstNode *prototype, AstNode *returnType);

AstNode *makeArray(AstNode *exprs);

AstNode *makeType(string typeName);

AstNode *makeType(string name, AstNode *typeArgs);

AstNode *makeFunctionType(AstNode *args, AstNode *ret);

AstNode *makeLambda(AstNode *params, AstNode *body);

#endif //IGNITER_LEX_H
