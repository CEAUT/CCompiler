//
// Created by ahmad on 1/16/16.
//

#ifndef CCOMPILER_SYNTAX_H
#define CCOMPILER_SYNTAX_H

#include "loader.h"
#define PUNC_PARAN_OP 1
#define PUNC_PARAN_CL -1
#define PUNC_BRACE_OP 2
#define PUNC_BRACE_CL -2

void checkPunc(token *head);
#endif //CCOMPILER_SYNTAX_H
