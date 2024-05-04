//
// Created by smsqo on 2022/4/25.
//

#ifndef IGNITER_ARRAY_GEN_H
#define IGNITER_ARRAY_GEN_H

#include "codegen/CodeGen.h"

class ArrayGen : public CodeGen {
    Type *compType; // 泛型类型
    vector<CodeGen *> Elems;

public:

    // 如果是个空数组, 则是无法根据vector<CodeGen *>获取到当前数组的伴生类型的
    // 而这个类型信息可以在创建数组AST的阶段得到; 所以还是以参数的形式传入吧,
    // 类型的计算放在第二阶段.
    explicit ArrayGen(vector<CodeGen *> elems, Type *compType)
            : Elems(move(elems)), compType(compType) {
        // check: make sure all the Elems are of the same type as compType announced.
        for (auto elem: Elems) {
            if (elem->type != compType) {
                throw std::runtime_error("Array: elements are not of the declared type.");
            }
        }
        type = compType; // TODO TODO!!!
    }

    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override {
        auto &context = m->getContext();
        auto ITy = Type::getInt32Ty(context);
        auto allocSize = ConstantInt::getSigned(ITy, Elems.size());
        auto p = bd.CreateAlloca(compType, allocSize);

        auto idx = 0;
        for (auto elem: Elems) {
            // 1. 生成对象值
            auto v = elem->generate(m, func, bd);
            // 2. 生成值希望存储到的内存位置(指针)
            auto x = bd.CreateGEP(p, ConstantInt::getSigned(ITy, idx++));

            // FIXME 这里原来还有判断是否是指针类型的, 这里先省略了.

            // 3. 将值安放到该指针指向的位置上.
            bd.CreateStore(v, x);
        }
        return p;
    }
};


#endif //IGNITER_ARRAY_GEN_H
