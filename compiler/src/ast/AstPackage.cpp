//
// Created by smsqo on 2022/4/17.
//

#include "AstPackage.h"

#include <utility>
#include "AstNode.h"

void AstPackage::makeGen(AstContext *parent) {
    for (auto *it: Lines) {
        it->makeGen(parent);
    }
}

void AstPackage::generate() {
    context.generateFunctions();
}


