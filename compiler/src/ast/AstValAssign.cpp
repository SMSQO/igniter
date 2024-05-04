//
// Created by smsqo on 2022/4/20.
//

#include "AstVariable.h"
#include "AstValAssign.h"

#include "type/TypeManager.h"

AstValAssign::AstValAssign(AstVariableDef *var, AstNode *expr)
        : Variable(var), expr(expr) {}

CodeGen *AstValAssign::makeGen(AstContext *parent) {
    auto codegen = expr->makeGen(parent);

    if (Variable->type) {
        auto declaredLLVMType = TypeManager::getLLVMType(Variable->type);
        if (declaredLLVMType != codegen->type) {
            throw std::runtime_error("对变量" + Variable->name + "声明的类型和实际类型不一致!");
        }
    }

    parent->setSymbolGen(Variable->name, codegen);
    return nullptr;
}
