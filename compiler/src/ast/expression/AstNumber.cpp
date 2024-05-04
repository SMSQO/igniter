//
// Created by smsqo on 2022/4/15.
//

#include "AstNumber.h"
#include "codegen/expression/NumGen.h"

AstNumberInt::AstNumberInt(int val) : val(val) {}

AstNumberDouble::AstNumberDouble(double val) : val(val) {}

CodeGen *AstNumberDouble::makeGen(AstContext *parent) {
    return new DoubleNumGen(val, parent->context());
}

CodeGen *AstNumberInt::makeGen(AstContext *parent) {
    return new IntNumGen(val);
}


