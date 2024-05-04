# System configuration

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
INCLUDE_DIRECTORIES("/usr/lib/llvm-10/include")
LINK_DIRECTORIES("/usr/lib/llvm-10/lib")

SET(_GNU_SOURCE 1)
SET(__STDC_CONSTANT_MACROS 1)
SET(__STDC_FORMAT_MACROS 1)
SET(__STDC_LIMIT_MACROS 1)

# Project configuration

INCLUDE_DIRECTORIES("src")
INCLUDE_DIRECTORIES("intermediate")
INCLUDE_DIRECTORIES("type")

file(GLOB_RECURSE asts src/ast/*.cpp)
file(GLOB_RECURSE codegens src/codegen/*.cpp)
file(GLOB_RECURSE srcs src/*.cpp)
file(GLOB_RECURSE types type/*.cpp)

ADD_LIBRARY(
        compiler
        intermediate/igniter.tab.cpp
        intermediate/lex.yy.cpp
        src/lex.cpp
        src/jitRun.cpp

        ${srcs}
        ${asts}
        ${codegens}
        src/ast/expression/AstBoolean.h src/codegen/expression/BooleanGen.cpp src/codegen/expression/BooleanGen.h src/ast/expression/AstArrayExpr.h src/codegen/expression/ArrayGen.cpp src/codegen/expression/ArrayGen.h src/type/AstType.h src/ast/expression/AstIndexExpr.cpp src/ast/expression/AstIndexExpr.h src/codegen/expression/IndexGen.cpp src/codegen/expression/IndexGen.h src/ast/expression/AstReturn.h src/codegen/expression/ReturnGen.cpp src/codegen/expression/ReturnGen.h src/ast/expression/AstLambdaExpr.cpp src/ast/expression/AstLambdaExpr.h src/ast/expression/AstUnitExpr.cpp src/ast/expression/AstUnitExpr.h src/codegen/expression/UnitGen.h src/ast/expression/AstUnaryExpr.cpp src/ast/expression/AstUnaryExpr.h src/codegen/expression/UnaryGen.cpp src/codegen/expression/UnaryGen.h)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

FIND_PACKAGE(LLVM REQUIRED CONFIG)
TARGET_LINK_LIBRARIES(compiler LLVM-10)
