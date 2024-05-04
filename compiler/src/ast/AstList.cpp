//
// Created by smsqo on 2022/4/16.
//

#include "AstList.h"

#include <utility>

AstList::AstList(AstList *prev, AstNode *curr) {
    Lines = move(prev->Lines);
    Lines.push_back(curr);
}

AstList::AstList() {
    Lines = std::vector<AstNode *>();
}

AstList::AstList(AstNode *curr) {
    Lines = std::vector<AstNode *>();
    Lines.push_back(curr);
}

