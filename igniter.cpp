#include <iostream>

#include "lex.h"
#include "igniter.tab.hpp"
#include "ast/AstPackage.h"
#include <vector>


#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "KaleidoscopeJIT.h"

#include "llvm/Target/TargetOptions.h"
#include <llvm/Support/FileSystem.h>


using namespace std;

extern FILE *yyin;
extern int yydebug;
int llvmdebug;

AstPackage *currentPackage;

int generateCode(Module *);

int main(int argc, char *argv[]) {
    yydebug = 0;        // 是否开启语法分析日志输出
    llvmdebug = 0;      // 是否开启LLVM-IR输出

    if (argc <= 1) {
        cerr << "filename not specified, reading from stdin." << endl;
    } else {
        char *filename = argv[1];
        yyin = fopen(filename, "r");
    }

    AstContext context(nullptr);
    currentPackage = new AstPackage(context);

    try {

        bool success = yyparse() == 0;

        if (!success) {
            cout << "parsing failed" << endl;
            exit(1);
        }
        cerr << "\n====< 已完成语法分析, 准备生成代码. >=====\n" << endl;

        // currentPackage->codegen(parent);
        currentPackage->makeGen(&context);
        currentPackage->generate();
        if (llvmdebug)
            context.module()->print(errs(), nullptr);
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    auto module = context.module();
    generateCode(module);
    if (!module->getFunction("main")) {
        cout << "还没有定义main函数!" << endl;
        return 1;
    }
    // jitRun(module);
    return 0;
}

int generateCode(Module *TheModule) {

    // 这三个是用来生成代码的.
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeAllAsmParsers();

    auto TargetTriple = sys::getDefaultTargetTriple();
    TheModule->setTargetTriple(TargetTriple);

    std::string Error;
    auto Target = TargetRegistry::lookupTarget(TargetTriple, Error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!Target) {
        errs() << Error;
        return 1;
    }

    auto CPU = "generic";
    auto Features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto TheTargetMachine =
            Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

    TheModule->setDataLayout(TheTargetMachine->createDataLayout());

    auto Filename = "output.o";
    std::error_code EC;
    raw_fd_ostream dest(Filename, EC, sys::fs::OF_None);

    if (EC) {
        errs() << "Could not open file: " << EC.message();
        return 1;
    }

    legacy::PassManager pass;
    auto FileType = CGFT_ObjectFile;

    if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        errs() << "TheTargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(*TheModule);
    dest.flush();

    cerr << "Wrote to " << Filename << "\n";
    return 0;
}
