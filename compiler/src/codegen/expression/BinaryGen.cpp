//
// Created by smsqo on 2022/4/23.
//

#include <iostream>
#include "BinaryGen.h"
#include "type/TypeManager.h"
#include "ast/AstNode.h"
#include "type/AstType.h"
#include "igniter.tab.hpp"

// 如果是函数重载, 应该在makeGen的时候就替换成函数调用了.
// 因此这里只考虑数值计算.
BinaryGen::BinaryGen(CodeGen *LHS, CodeGen *RHS, int Op)
        : LHS(LHS), RHS(RHS), Op(Op) {

    type = isBooleanOp(Op) ?
           TypeManager::BOOLEAN :
           TypeManager::intersect(LHS->type, RHS->type);
}

Value *BinaryGen::generateCode(Module *m, Function *func, IRBuilder<> &bd) {
    Value *L = LHS->generate(m, func, bd);
    Value *R = RHS->generate(m, func, bd);

    if (!L || !R) {
        char text[0x100];
        sprintf(text, "missing LHS/RHS on generate code for operator '%c' when creating function", Op);
        throw std::runtime_error(text);
    }
    // Let it crash! Make no check to whether L / R is nullptr or not.

    return operate(L, R, bd, m->getContext());
}

Value *BinaryGen::operate(Value *L, Value *R, IRBuilder<> &bd, LLVMContext &context) const {
    auto operandType = TypeManager::intersect(L->getType(), R->getType());
    switch (Op) {
        case '+':
            return type == TypeManager::DOUBLE ? bd.CreateFAdd(L, R) : bd.CreateAdd(L, R);
        case '-':
            return type == TypeManager::DOUBLE ? bd.CreateFSub(L, R) : bd.CreateSub(L, R);
        case '*':
            return type == TypeManager::DOUBLE ? bd.CreateFMul(L, R) : bd.CreateMul(L, R);
        case '/':
            return type == TypeManager::DOUBLE ? bd.CreateFDiv(L, R) : bd.CreateSDiv(L, R);
        case '%':
            return type == TypeManager::DOUBLE ? bd.CreateFRem(L, R) : bd.CreateSRem(L, R);

        case '<':
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpULT(L, R) : bd.CreateICmpULT(L, R);
        case '>':
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpUGT(L, R) : bd.CreateICmpUGT(L, R);
        case TOK_LE:
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpULE(L, R) : bd.CreateICmpULE(L, R);
        case TOK_GE:
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpUGE(L, R) : bd.CreateICmpUGE(L, R);


        case TOK_EQUAL:
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpUEQ(L, R) : bd.CreateICmpEQ(L, R);
        case TOK_NON_EQUAL:
            return operandType == TypeManager::DOUBLE ? bd.CreateFCmpUNE(L, R) : bd.CreateICmpNE(L, R);


        case TOK_OR:
            return bd.CreateOr(L, R);
        case TOK_AND:
            return bd.CreateAnd(L, R);

        default:
            char str[128];
            sprintf(str, "invalid binary operator: %d", Op);
            throw std::runtime_error(str);
    }
}

bool BinaryGen::isBooleanOp(int op) {
    return (
            op == '>' || op == '<' || op == TOK_GE || op == TOK_LE
            || op == TOK_EQUAL || op == TOK_NON_EQUAL
            || op == TOK_OR || op == TOK_AND);
}
