//
// Created by smsqo on 2022/4/23.
//

#ifndef IGNITER_BINARY_GEN_H
#define IGNITER_BINARY_GEN_H


#include "codegen/CodeGen.h"

/*
 * 当前支持的运算符:
 *   +  -   *   /   %
 *   <  >   >=  <=  ==  !=
 *   || &&
 */

class BinaryGen : public CodeGen {
    int Op;
    CodeGen *LHS;
    CodeGen *RHS;

public:
    BinaryGen(CodeGen *LHS, CodeGen *RHS, int Op);


    Value *generateCode(Module *m, Function *func, IRBuilder<> &bd) override;

    bool isBooleanOp(int op);

private:

    Value *operate(Value *A, Value *B, IRBuilder<> &bd, LLVMContext &context) const;
};


#endif //IGNITER_BINARY_GEN_H
