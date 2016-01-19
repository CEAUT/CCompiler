//
// Created by ahmad on 1/17/16.
//

#ifndef CCOMPILER_IRGEN_H
#define CCOMPILER_IRGEN_H

#include "loader.h"

extern bool seenMain;
extern int lableCounter;

void assignment(char *varaibleName,token *head);
void statement(token *head);
void generateIR(token *head);
char *expressionCal(token *start, token *end);
#endif //CCOMPILER_IRGEN_H
