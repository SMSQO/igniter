#include "AstVariable.h"

AstVariable::AstVariable(string name) : Name(move(name)) {}

CodeGen *AstVariable::makeGen(AstContext *parent) {
    auto ret = parent->findSymbolGen(Name, true);
    if (ret) return ret;
    throw std::runtime_error("找不到符号: " + Name);
}
