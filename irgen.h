//
// Created by ahmad on 1/17/16.
//

#ifndef CCOMPILER_IRGEN_H
#define CCOMPILER_IRGEN_H

#include "loader.h"

extern bool seenMain;
extern int lableCounter;

token *ifStatement(char *condition,token *head);
token *whiilestatement(token *head);
token *statement(token *head);
void generateIR(token *head);
char *expressionCal(token *start, token *end);
#endif //CCOMPILER_IRGEN_H
