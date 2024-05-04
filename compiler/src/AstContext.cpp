//
// Created by smsqo on 2022/4/15.
//

#include <llvm/Transforms/Scalar/GVN.h>
#include "AstContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils.h"

#include "ast/function/AstFunctionDef.h"

LLVMContext llvmContext;

AstContext::AstContext(AstContext *parent) :
        _module(new Module("igniter", _context)),
        _fpm(new legacy::FunctionPassManager(_module)),
        _parent(parent) {

    _fpm->add(createInstructionCombiningPass());
    _fpm->add(createReassociatePass());
    _fpm->add(createGVNPass());
    // _fpm->add(createCFGSimplificationPass());                    // 这个PASS可能错误地优化掉一些内容.
    _fpm->add(createPromoteMemoryToRegisterPass());

    _fpm->doInitialization();
}

void AstContext::defineFunction(const string &name, AstFunctionDef *f) {
    _functions[name] = f;
}

FunctionGen *AstContext::getFunctionGen(const string &name) {
    auto *def = _functions[name];
    if (!def) {
        cout << "Function " + name + " is not defined yet when calling in function" << endl;
        return nullptr;
    }
    return def->getFunctionGen();
}

void AstContext::generateFunctions() {
    for (auto &it: _functions) {
        it.second->getFunctionGen()->generateCode(_module, _context);
    }
}

CodeGen *AstContext::findSymbolGen(const string &name, bool recursive = true) {
    auto *value = _symbols[name];
    if (value) return value;
    if (_parent && recursive) {
        return _parent->findSymbolGen(name, recursive);
    }
    return nullptr;
}
