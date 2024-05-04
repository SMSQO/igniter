//
// Created by smsqo on 2022/4/24.
//

#include "IfGen.h"
#include "type/TypeManager.h"

Value *IfGen::generateCode(Module *m, Function *func, IRBuilder<> &bd) {
    auto &context = m->getContext();

    Value *condV = cond->generate(m, func, bd);
    // condV should be boolean on future use.

    Function *TheFunction = bd.GetInsertBlock()->getParent();

    BasicBlock *ifTrueBB = BasicBlock::Create(context, "then", TheFunction);
    BasicBlock *ifFalseBB = BasicBlock::Create(context, "else");
    BasicBlock *MergeBB = BasicBlock::Create(context, "if-cont");

    bd.CreateCondBr(condV, ifTrueBB, ifFalseBB);

    // 顺序是不能调整的, 尤其是`ifTrue->codegen(parent)`. 这条命令可能会在当前的BasicBlock中插入其他节点.
    // 如插入内嵌if表达式, 就必须要按照顺序来.
    bd.SetInsertPoint(ifTrueBB);
    Value *ifTrueV = thenGen->generate(m, func, bd);
    bd.CreateBr(MergeBB);
    ifTrueBB = bd.GetInsertBlock(); // 如果ifTrue里面修改了当前BasicBlock的位置, 需要这句将ifTrueBB指向最后生成的BB.

    TheFunction->getBasicBlockList().push_back(ifFalseBB);
    bd.SetInsertPoint(ifFalseBB);
    Value *ifFalseV = elseGen->generate(m, func, bd);
    bd.CreateBr(MergeBB);
    ifFalseBB = bd.GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(MergeBB);
    bd.SetInsertPoint(MergeBB);


    PHINode *PN = bd.CreatePHI(
            TypeManager::intersect(ifTrueV->getType(), ifFalseV->getType()),
            2, "iftmp");

    if (PN->getType() == TypeManager::UNIT) {
        PN->addIncoming(TypeManager::UNIT_INSTANCE, ifTrueBB);
        PN->addIncoming(TypeManager::UNIT_INSTANCE, ifFalseBB);
    } else {
        PN->addIncoming(ifTrueV, ifTrueBB);
        PN->addIncoming(ifFalseV, ifFalseBB);
    }
    return PN;
}

IfGen::IfGen(CodeGen *cond, CodeGen *thenGen, CodeGen *elseGen)
        : cond(cond), thenGen(thenGen), elseGen(elseGen) {
    if (cond->type != TypeManager::BOOLEAN) {
        throw std::runtime_error("Condition of IF-EXPRESSION must in type Boolean");
    }
    type = TypeManager::intersect(thenGen->type, elseGen->type);
}
