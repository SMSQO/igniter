//
// Created by smsqo on 2022/4/15.
//

#ifndef IGNITER_AST_CONTEXT_H
#define IGNITER_AST_CONTEXT_H

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "KaleidoscopeJIT.h"
#include "codegen/CodeGen.h"
#include "type/TypeManager.h"

class AstFunctionDef;

class FunctionGen;

using namespace llvm;

extern LLVMContext llvmContext;

class AstContext {
    LLVMContext &_context = llvmContext;
    Module *_module;
    legacy::FunctionPassManager *_fpm;

    AstContext *_parent = nullptr;

    map<string, CodeGen *> _symbols;
    map<string, AstFunctionDef *> _functions;

public:
    explicit AstContext(AstContext *parent);

    llvm::LLVMContext &context() { return _context; }

    CodeGen *findSymbolGen(const string &name, bool recursive);

    void setSymbolGen(const string &name, CodeGen *gen) {
        _symbols[name] = gen;
    }

    Module *module() { return _module; }

    FunctionGen *getFunctionGen(const string &name);

    void defineFunction(const string &name, AstFunctionDef *f);

    // TODO mock. this function haven't appear in SimpLang
    void generateFunctions();

    legacy::FunctionPassManager *getFPM() { return _fpm; }


private:
    Type *currentBlockTy = TypeManager::NOTHING;
public:
    void pushReturnTy(Type *ty) { currentBlockTy = TypeManager::intersect(currentBlockTy, ty); }

    Type *currentBlockType() { return currentBlockTy; }

    void clearCurrentBlockTy() { currentBlockTy = TypeManager::NOTHING; }
};


#endif //IGNITER_AST_CONTEXT_H
