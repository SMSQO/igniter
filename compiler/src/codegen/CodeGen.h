//
// Created by smsqo on 2022/4/20.
//

#ifndef IGNITER_CODEGEN_H
#define IGNITER_CODEGEN_H

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm-10/llvm/IR/IRBuilder.h>

using namespace std;
using namespace llvm;

class CodeGen {
public:
    explicit CodeGen(llvm::Type *t = nullptr);

    llvm::Type *type;
    llvm::Value *value = nullptr;

    llvm::Value *generate(llvm::Module *m, llvm::Function *func, llvm::IRBuilder<> &builder);

    // enum ValueType { ivalue = 0, lvalue, rvalue }; // 无所谓，左值，右值
    // ValueType valueType = ivalue;
    llvm::Value *load(llvm::IRBuilder<> &builder, llvm::Value *v);

protected:
    virtual Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) = 0;
};

#endif //IGNITER_CODEGEN_H
