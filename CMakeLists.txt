cmake_minimum_required(VERSION 3.16)
project(igniter)

# System configuration

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
INCLUDE_DIRECTORIES("/usr/lib/llvm-10/include")
LINK_DIRECTORIES("/usr/lib/llvm-10/lib")

SET(_GNU_SOURCE 1)
SET(__STDC_CONSTANT_MACROS 1)
SET(__STDC_FORMAT_MACROS 1)
SET(__STDC_LIMIT_MACROS 1)

# Project configuration
INCLUDE_DIRECTORIES(
        compiler/intermediate/
        compiler/src
        stdlib
)
add_subdirectory("compiler")

file(GLOB_RECURSE stdlibs stdlib/*.cpp)

# Target

SET(CMAKE_CXX_FLAGS -rdynamic)
ADD_EXECUTABLE(igniter-lite
        igniter.cpp
        ${stdlibs} core/core.cpp core/core.h)
TARGET_LINK_LIBRARIES(igniter-lite compiler)
