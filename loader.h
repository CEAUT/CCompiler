//
// Created by ahmad on 1/12/16.
//

#ifndef CCOMPILER_LOADER_H
#define CCOMPILER_LOADER_H

#include "errorgen.h"
#include <stdio.h>
#include "limits.h"
#include <string>


struct token{
    int type;
    char value[IDENTIFIER_NAME_LENGHT];
    int lineNumber;
    token *next;
};

// Different type of possible tokens_
#define UNKNOWN_TOKEN -1
#define NAME_TOKEN 0        // General showing of keyword or identifier
#define KEYWORD_TOKEN 1
#define IDENTIFIER_TOKEN 2
#define OPERATOR_TOKEN 3
#define NUM_TOKEN 4
#define CHAR_TOKEN 5
#define PUNC_TOKEN 6

extern int currentLine;
extern int tokenNum;        // Size of the linked list of tokens
extern token *last;
extern token *head;

void pushToStr(char *str,char chr);

void loadfromfile(char *path);

void pushToken(token t);

int getType(char chr);


#endif //CCOMPILER_LOADER_H
