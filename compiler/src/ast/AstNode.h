//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_ASTNODE_H
#define IGNITER_ASTNODE_H

#include "llvm/ADT/APFloat.h"

#include "llvm/IR/Type.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/Constants.h"
#include "AstContext.h"
#include "codegen/CodeGen.h"

using namespace llvm;

class AstNode {
public:
    virtual ~AstNode() = default;

    virtual CodeGen *makeGen(AstContext *parent) = 0;
};

#endif //IGNITER_ASTNODE_H
