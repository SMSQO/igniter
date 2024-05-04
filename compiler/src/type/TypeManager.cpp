//
// Created by smsqo on 2022/4/22.
//

#include "TypeManager.h"
#include "llvm/IR/Constant.h"
#include "type/AstType.h"

Type *TypeManager::UNIT = Type::getInt1PtrTy(llvmContext); // 这个类型显然不如getVoidTy()好, 但是在BlockGen中, 无法找到其对应的人默认值.
Type *TypeManager::BOOLEAN = Type::getInt1Ty(llvmContext);
Type *TypeManager::DOUBLE = Type::getDoubleTy(llvmContext);
Type *TypeManager::INT = Type::getInt32Ty(llvmContext);
Type *TypeManager::NOTHING = Type::getVoidTy(llvmContext);

Value *TypeManager::UNIT_INSTANCE = Constant::getNullValue(UNIT);

// FIXME 这个之后需要添加
Type *TypeManager::intersect(Type *A, Type *B) {
    if (A == B) return A;
    if (A == NOTHING) return B;
    else if (B == NOTHING) return A;

    // 如果并非两个类型都是数字类型, 则返回Unit类型
    if (!(A == DOUBLE || A == INT) || !(B == DOUBLE || B == INT)) {
        return UNIT;
    }
    if (A == DOUBLE || B == DOUBLE)
        return DOUBLE;
    return INT;
}

Type *TypeManager::getLLVMType(AstType *ty) {
    // TODO 对于复杂类型, 应该如何处理?
    return TypeManager::get(ty->name());
}
