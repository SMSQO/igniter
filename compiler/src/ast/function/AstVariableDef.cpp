//
// Created by smsqo on 2022/4/15.
//

#include "AstVariableDef.h"
#include "codegen/function/ParamGen.h"
#include "type/TypeManager.h"


#include <utility>


CodeGen *AstVariableDef::makeGen(AstContext *parent) {
    if (!type) {
        throw std::runtime_error("无法推断变量" + name + "的类型");
    }
    parent->setSymbolGen(name, new ParamGen(name, TypeManager::get(type->name())));
    return nullptr;
}

AstVariableDef::AstVariableDef(string name, AstType *type) : name(move(name)), type(type) {}

