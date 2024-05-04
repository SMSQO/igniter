//
// Created by smsqo on 2022/4/15.
//

#include "lex.h"

#include <utility>
#include "ast/expression/AstNumber.h"
#include "ast/expression/AstCallExpr.h"
#include "ast/AstVariable.h"
#include "ast/AstList.h"
#include "ast/expression/AstBinaryExpr.h"
#include "ast/expression/AstUnaryExpr.h"
#include "ast/expression/AstIfExpr.h"
#include "ast/expression/AstBlockExpr.h"
#include "ast/expression/AstBoolean.h"
#include "ast/AstValAssign.h"
#include "ast/function/AstVariableDef.h"
#include "ast/function/AstFunctionDef.h"
#include "ast/expression/AstArrayExpr.h"
#include "ast/expression/AstIndexExpr.h"
#include "ast/expression/AstReturn.h"
#include "ast/expression/AstLambdaExpr.h"
#include "ast/expression/AstUnitExpr.h"

#include <string>

using namespace std;
using std::vector;

AstNode *makeNumber(double number) {
    return new AstNumberDouble(number);
}

AstNode *makeNumber(int number) {
    return new AstNumberInt(number);
}

AstNode *makeBoolean(bool value) {
    return new AstBoolean(value);
}

AstNode *makeUnit() {
    return new AstUnitExpr();
}

AstNode *makeCall(const char *callee, const AstNode *args) {
    return new AstCallExpr(callee, ((AstList *) args)->Lines);
}

AstNode *makeIndex(const char *callee, const AstNode *args) {
    return new AstIndexExpr(callee, ((AstList *) args)->Lines);
}

AstNode *makeReturn(AstNode *node) {
    return new AstReturn(node);
}

AstNode *makeValue(const char *name) {
    return new AstVariable(name);
}

AstNode *makeVariableDef(const char *name, AstNode *type) {
    return new AstVariableDef(name, (AstType *) type);
}

AstNode *makeBinaryExpr(AstNode *lhs, int optr, AstNode *rhs) {
    return new AstBinaryExpr(optr, lhs, rhs);
}

AstNode *makeUnaryExpr(int optr, AstNode *content) {
    return new AstUnaryExpr(optr, content);
}

AstNode *makePrototype(const char *name, AstNode *params) {
    auto variables = ((AstList *) params)->Lines;
    vector<pair<string, AstType *>> names;
    names.reserve(variables.size());
    for (auto it: variables) {
        auto jt = (AstVariableDef *) it;
        names.emplace_back(jt->name, jt->type);
    }
    return new AstFunctionDef(name, names);
}

AstNode *makeFunDef(AstNode *prototype, AstNode *body) {
    auto *f = (AstFunctionDef *) prototype;
    f->setBody((AstBlockExpr *) body);
    return f;
}

AstNode *makeImport(AstNode *prototype) {
    auto *f = (AstFunctionDef *) prototype;
    f->ScopeType = AstFunctionDef::IMPORT;
    return f;
}

AstPackage *makePackage(AstNode *lines) {
    currentPackage->Lines = std::move(((AstList *) lines)->Lines);
    return currentPackage;
}

AstList *link() { return new AstList(); }

AstList *link(AstNode *curr) {
    return new AstList(curr);
}

AstList *link(AstNode *prev, AstNode *curr) {
    return new AstList((AstList *) prev, curr);
}

AstNode *makeIf(AstNode *cond, AstNode *ifTrue, AstNode *ifFalse) {
    return new AstIfExpr(cond, (AstBlockExpr *) ifTrue, (AstBlockExpr *) ifFalse);
}

AstNode *makeExprBlock(AstNode *list) {
    auto tmp = (AstList *) list;
    return new AstBlockExpr(tmp->Lines);
}

AstNode *makeExprBlock() {
    return new AstBlockExpr({});
}

AstNode *makeAssignVal(AstNode *variable, AstNode *expr) {
    auto *var = (AstVariableDef *) variable;
    return new AstValAssign(var, expr);
}

AstNode *setPrototypeReturnType(AstNode *prototype, AstNode *returnType) {
    auto *proto = (AstFunctionDef *) prototype;
    proto->setReturnType((AstType *) returnType);
    return proto;
}

AstNode *makeArray(AstNode *exprs) {
    return new AstArrayExpr((AstList *) exprs);
}

AstNode *makeType(string typeName) {
    return new AstType(typeName);
}

AstNode *makeType(string typeName, AstNode *typeArgs) {
    auto typeArgsLines = ((AstList *) typeArgs)->Lines;

    vector<AstType *> types;
    vector<int> numbers;
    for (auto it: typeArgsLines) {
        if (typeid(*it) == typeid(AstType)) {
            types.push_back((AstType *) it);
        } else {
            numbers.push_back(((AstNumberInt *) it)->value());
        }
    }
    return new AstType(typeName, types, numbers);
}

AstNode *makeFunctionType(AstNode *args, AstNode *ret) {
    return makeType("Function", link(args, ret));
}

AstNode *makeLambda(AstNode *params, AstNode *body) {
    return new AstLambdaExpr();
}
