//
// Created by smsqo on 2022/4/19.
//

#ifndef IGNITER_AST_BLOCK_EXPR_H
#define IGNITER_AST_BLOCK_EXPR_H


#include "ast/AstNode.h"
#include "codegen/BlockGen.h"

class AstBlockExpr : public AstNode {
public:
    vector<AstNode *> Lines;

    explicit AstBlockExpr(vector<AstNode *> Lines);

    // 这里のmakeGen有两个目的:
    // 1. 获取Lines中每个元素的CodeGen;
    // 2. 获取整个块的类型.
    BlockGen *makeGen(AstContext *parent) override {
        Type *lastType = nullptr;
        vector<CodeGen *> gens;
        for (auto it: Lines) {
            auto gen = it->makeGen(parent);
            if (gen) {
                gens.push_back(gen);
                lastType = gen->type;
            } else
                lastType = nullptr;
        }

        Type *retType;
        if (!lastType) {
            retType = TypeManager::UNIT;
        } else {
            parent->pushReturnTy(lastType);
            retType = parent->currentBlockType();
        }

        auto ret = new BlockGen(gens, retType);
        parent->clearCurrentBlockTy();
        return ret;
    };
};


#endif //IGNITER_AST_BLOCK_EXPR_H
