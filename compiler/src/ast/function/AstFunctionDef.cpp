//
// Created by smsqo on 2022/4/22.
//

#include "AstFunctionDef.h"
#include "codegen/function/ParamGen.h"
#include "type/TypeManager.h"

void AstFunctionDef::setBody(AstBlockExpr *bd) {
    this->body = bd;
}


// 这里makeGen()绝对不应该返回FunctionGen实例, 因为这是一个"函数定义"语句,
// 该语句没有生成一个函数实例, 只是定义了一个函数.
// 若返回FunctionGen, 则比如在列表中定义了一个函数,
// 则该函数则被视为列表的一个表达式项, 这显然不是我们所期望的.
CodeGen *AstFunctionDef::makeGen(AstContext *context) {
    this->parent = context;
    parent->defineFunction(name, this);
    gen = getFunctionGen();
    return nullptr;
}

// 如何获取一个FunctionGen?
FunctionGen *AstFunctionDef::getFunctionGen() {
    // 如果之前就生成过, 直接返回就可以了.
    if (gen) return gen;

    // 后面我们会看到, 函数(会尽可能)先生成prototype, 然后再生成body的代码.
    // 但如果没有在prototype中标注返回值类型的时候, 就只能先生成body, 根据body的type再生成prototype.
    // 另外, 调用此方法的时机只有: ① 生成包内函数; ② 生成CallGen() 这两种时候.
    // 那么, 如果发现正在生成函数代码(isGeneratingFlag == true), 而且gen == nullptr时,
    // 只能说明出现了函数的递归调用, 且还没标注返回值类型.
    // (这种情况下的代码并非总是无法推断出返回值的类型, 但之后再修改吧)
    // 在我们的系统里, 这种情况是无法推断出类型的, 所以报错.
    if (isGeneratingFlag) {
        throw std::runtime_error("函数" + name + "递归调用且没有标注返回值类型, 无法自动推断其类型且生成代码.");
    }

    isGeneratingFlag = true;
    // 1. 创建属于该函数的作用域
    auto *s = new AstContext(*parent);

    // 2. 准备该函数的参数, 包括参数名和参数的类型
    vector<pair<string, Type *>> params;
    params.reserve(args.size());

    for (auto &it: args) {
        auto *type = TypeManager::get(it.second->name()); // mock
        auto parName = it.first;

        auto *p = new ParamGen(parName, type);
        s->setSymbolGen(parName, p);
        params.emplace_back(parName, type);
    }

    // 考虑一下, 如果函数体和函数签名同时生成, 那如何应对递归调用?
    // 毕竟, 生成函数体的时候会AstCall的makeGen(), 而这又重新调用了此函数
    // 如果我们可以先把函数声明了, 然后再将函数体添加到该函数上, 这会很好.

    if (!returnType && !body) {
        throw std::runtime_error("对函数" + name + "的声明不能省略返回值类型.");
    }

    BlockGen *bodyGen = nullptr;
    Type *llvmRetTy;

    if (!returnType) {
        // 如果返回值省略了, 则先创建函数体, 然后根据函数体推断类型.
        bodyGen = body->makeGen(s);
        llvmRetTy = bodyGen->type;
    } else {
        llvmRetTy = TypeManager::getLLVMType(returnType);
    }
    // llvmRetTy is set.

    auto *funcGen = new FunctionGen(
            name,
            params,
            llvmRetTy,
            parent->getFPM()
    );
    this->gen = funcGen; // 这样, 之后调用此函数就会在函数第一行就返回了.

    // 如果是函数声明, 则可以直接返回完事儿了.
    if (!body) {
        return funcGen;
    }

    // 返回值没有省略的分支
    if (!bodyGen) {
        bodyGen = body->makeGen(s);
    }
    funcGen->setBlock(bodyGen);

    isGeneratingFlag = false;
    return funcGen;
}
