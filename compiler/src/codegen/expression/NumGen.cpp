//
// Created by smsqo on 2022/4/23.
//

#include "NumGen.h"
#include "type/TypeManager.h"

IntNumGen::IntNumGen(int64_t val) {
    this->type = TypeManager::get("Int");
    instance = ConstantInt::getSigned(type, val);
}

llvm::Value *IntNumGen::generateCode(llvm::Module *m, llvm::Function *func, IRBuilder<> &) {
    return instance;
}

DoubleNumGen::DoubleNumGen(double val, LLVMContext &c) {
    this->type = Type::getDoubleTy(c);
    instance = ConstantFP::get(c, APFloat(val));
}

llvm::Value *DoubleNumGen::generateCode(llvm::Module *m, llvm::Function *func, IRBuilder<> &) {
    return instance;
}


