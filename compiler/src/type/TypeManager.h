//
// Created by smsqo on 2022/4/22.
//

#ifndef IGNITER_TYPE_MANAGER_H
#define IGNITER_TYPE_MANAGER_H


#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

#include <string>
#include <map>

using namespace std;
using namespace llvm;

extern LLVMContext llvmContext;

class AstType;

class TypeManager {
public:
    static Type *DOUBLE;
    static Type *INT;
    static Type *UNIT;
    static Type *BOOLEAN;
    static Type *NOTHING;

    static Value *UNIT_INSTANCE;

    static Type *get(const string &name) {
        if (name == "Double") {
            return DOUBLE;
        } else if (name == "Int") {
            return INT;
        } else if (name == "Unit") {
            return UNIT;
        } else if (name == "Boolean") {
            return BOOLEAN;
        }
        return nullptr;
    }

    // 取两个类型的交集, 即获取两个类型共同的祖先.
    static Type *intersect(Type *a, Type *b);

    static bool isNumberTy(Type *A) { return A == INT || A == DOUBLE; }

    static Type *getLLVMType(AstType *ty);
};

#endif //IGNITER_TYPE_MANAGER_H
