//
// Created by smsqo on 2022/4/23.
//

#ifndef IGNITER_NUM_GEN_H
#define IGNITER_NUM_GEN_H


#include "codegen/CodeGen.h"

class NumGen : public CodeGen {

    llvm::Value *generateCode(
            llvm::Module *m,
            llvm::Function *func,
            llvm::IRBuilder<> &
    ) override = 0;
};

class IntNumGen : public NumGen {
    Value *instance = nullptr;
public:
    explicit IntNumGen(int64_t val);

    llvm::Value *generateCode(llvm::Module *m, llvm::Function *func, llvm::IRBuilder<> &) override;
};

class DoubleNumGen : public NumGen {
    Value *instance = nullptr;
public:
    explicit DoubleNumGen(double val, LLVMContext &c);

    llvm::Value *generateCode(llvm::Module *m, llvm::Function *func, llvm::IRBuilder<> &) override;
};

#endif //IGNITER_NUM_GEN_H
