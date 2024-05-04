//
// Created by smsqo on 2022/4/25.
//

#include "AstIndexExpr.h"
#include "codegen/expression/IndexGen.h"

CodeGen *AstIndexExpr::makeGen(AstContext *parent) {
    auto callee = parent->findSymbolGen(Indexed, true);
    if (!callee) {
        throw std::runtime_error("引用数组时找不到符号: " + Indexed);
    }

    vector<CodeGen *> args;
    for (auto it: Args) {
        args.push_back(it->makeGen(parent));
    }
    return new IndexGen(callee, args);
}
