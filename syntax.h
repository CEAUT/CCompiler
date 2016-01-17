//
// Created by ahmad on 1/16/16.
//

#ifndef CCOMPILER_SYNTAX_H
#define CCOMPILER_SYNTAX_H

#include "loader.h"
#define PUNC_PARAN_OP 11
#define PUNC_PARAN_CL -11
#define PUNC_BRACE_OP 12
#define PUNC_BRACE_CL -12

void checkPunc(token *head);
#endif //CCOMPILER_SYNTAX_H
