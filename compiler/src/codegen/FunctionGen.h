//
// Created by smsqo on 2022/4/22.
//

#ifndef IGNITER_FUNCTION_GEN_H
#define IGNITER_FUNCTION_GEN_H


#include <utility>

#include "CodeGen.h"
#include "AstContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "codegen/BlockGen.h"

class FunctionGen {
    string name;

    vector<pair<string, Type *>> params;
    Type *_returnType = nullptr;

    BlockGen *block = nullptr;

    legacy::FunctionPassManager *fpm;

public:
    FunctionGen(string name, vector<pair<string, Type *>> params, Type *returnType, legacy::FunctionPassManager *fpm) :
            name(std::move(name)), params(std::move(params)), _returnType(returnType), fpm(fpm) {}

    Function *generateCode(llvm::Module *m, LLVMContext &context);

    void setBlock(BlockGen *blk) {
        // 这里还可以是兼容类型(父子类关系), 但现在简单, 只能两个类型一致.
        do {
            if (_returnType == TypeManager::UNIT)
                break;
            if (_returnType != blk->type) {
                throw std::runtime_error("函数" + name + "的返回值类型和声明的不一致");
            }
        } while (false);
        this->block = blk;
    };

    Type *returnType() { return _returnType; }

    const string &Name() { return name; }

    int paramSize() const { return params.size(); }

private:
    Function *func = nullptr;
};


#endif //IGNITER_FUNCTION_GEN_H
