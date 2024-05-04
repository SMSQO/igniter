//
// Created by smsqo on 2022/4/26.
//

#include "IndexGen.h"

Value *IndexGen::generateCode(Module *m, Function *func, IRBuilder<> &bd) {
    // 都走到这里了, 可以肯定这是个数组了.
    // 不然应该在上个层次中de-sugar成函数调用了(指运算符重载).
    auto llvmArray = indexed->generate(m, func, bd);

    // 这里假定输入的参数一定是整数.
    vector<Value *> argVs;
    for (auto it: args) {
        argVs.push_back(it->generate(m, func, bd));
    }


    auto *p = bd.CreateGEP(llvmArray, argVs[0]);
    return bd.CreateLoad(p);
}
