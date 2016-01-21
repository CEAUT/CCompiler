//
// Created by ahmad on 1/17/16.
//

#ifndef CCOMPILER_IRGEN_H
#define CCOMPILER_IRGEN_H

#include "loader.h"

extern bool seenMain;
extern int lableCounter;
extern FILE *irfile;

token *mainAnalyser(token *head);
token *ifStatement(char *condition,token *head);
token *whiilestatement(token *head);
token *statement(token *head);
void generateIR(token *head,char *path);
char *expressionCal(token *start, token *end);
bool valideOperator(char *opr);
#endif //CCOMPILER_IRGEN_H
