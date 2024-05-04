//
// Created by smsqo on 2022/4/25.
//

#ifndef IGNITER_AST_ARRAY_EXPR_H
#define IGNITER_AST_ARRAY_EXPR_H


#include "ast/AstNode.h"
#include "ast/AstList.h"
#include "codegen/expression/ArrayGen.h"
#include "type/TypeManager.h"

class AstArrayExpr : public AstNode {
    vector<AstNode *> elems;
    string compTypeName;
public:
    explicit AstArrayExpr(AstList *exprs) : elems(exprs->Lines) {}

    CodeGen *makeGen(AstContext *parent) override {
        bool typeNotGiven = compTypeName == "";

        if (typeNotGiven && elems.size() == 0) {
            throw std::runtime_error("could not infer type of array");
        }

        auto iter = elems.begin();
        vector<CodeGen *> params;
        Type *type;

        CodeGen *first = (*iter)->makeGen(parent);
        if (first == nullptr)
            goto not_an_expression;
        params.push_back(first);

        type = typeNotGiven ?
               first->type :
               TypeManager::get(compTypeName);

        iter++;
        for (; iter != elems.end(); iter++) {
            auto gen = (*iter)->makeGen(parent);
            if (!gen) goto not_an_expression;
            if (typeNotGiven) {
                type = TypeManager::intersect(type, gen->type);
            }
            params.push_back(gen);
        }
        return new ArrayGen(params, type);

        not_an_expression:
        throw std::runtime_error("a non-expression was found while creating an array.");
    }
};


#endif //IGNITER_AST_ARRAY_EXPR_H
