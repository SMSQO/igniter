//
// Created by smsqo on 2022/4/22.
//

#include "FunctionGen.h"
#include "type/TypeManager.h"
#include "llvm/IR/Verifier.h"

Function *FunctionGen::generateCode(llvm::Module *m, LLVMContext &context) {
    if (func) return func;

    vector<Type *> paramType;
    for (auto it: this->params) {
        paramType.push_back(it.second);
    }

    FunctionType *FT = FunctionType::get(
            _returnType,
            paramType,
            false
    );

    auto *fun = Function::Create(FT, Function::ExternalLinkage, name, m);

    this->func = fun;
    if (!block) return func;

    BasicBlock *BB = BasicBlock::Create(context, name, fun);

    auto iter = this->params.begin();

    for (auto &i: func->args()) {
        i.setName(iter->first);
        iter++;
    }

    IRBuilder<> bd(BB);
    Value *ret = block->generate(m, func, bd);
    if (ret->getType() != TypeManager::UNIT && _returnType == TypeManager::UNIT) {
        bd.CreateRet(TypeManager::UNIT_INSTANCE);
    } else {
        bd.CreateRet(ret);
    }
    verifyFunction(*func);
    fpm->run(*func);

    return func;
}
