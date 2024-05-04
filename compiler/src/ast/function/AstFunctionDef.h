//
// Created by smsqo on 2022/4/22.
//

#ifndef IGNITER_AST_FUNCTION_H
#define IGNITER_AST_FUNCTION_H

#include "ast/AstNode.h"
#include "ast/expression/AstBlockExpr.h"
#include "codegen/FunctionGen.h"
#include "type/AstType.h"

class AstFunctionDef : public AstNode {
public:
    enum AstFunType {
        UNKNOWN, TOP_LEVEL, IMPORT
    };
private:
    string name;

    vector<pair<string, AstType *>> args;
    AstType *returnType;

    AstBlockExpr *body = nullptr;
    AstContext *parent = nullptr;
    FunctionGen *gen = nullptr;

    // 这个flag用于解决在函数递归生成的问题.
    bool isGeneratingFlag = false;

public:
    AstFunType ScopeType = UNKNOWN;

    explicit AstFunctionDef(string name, vector<pair<string, AstType *>> args)
            : name(move(name)), args(move(args)) {};


    void setBody(AstBlockExpr *body);

    const string &Name() { return name; }

    void setReturnType(AstType *type) { returnType = type; }

    CodeGen *makeGen(AstContext *parent) override;

    FunctionGen *getFunctionGen();
};


#endif //IGNITER_AST_FUNCTION_H
