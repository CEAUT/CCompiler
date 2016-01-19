//
// Created by ahmad on 1/12/16.
//

#ifndef CCOMPILER_LOADER_H
#define CCOMPILER_LOADER_H

#include "errorgen.h"
#include <stdio.h>
#include "limits.h"
#include <string>
#include <vector>

struct token{
    int type;
    char value[IDENTIFIER_NAME_LEN_LIM];
    int lineNumber;
    token *next;
    char fileName[FILE_PATH_LEN_LIM];
};

// Different type of possible tokens_
#define UNKNOWN_TOKEN -2
#define SPACE_TOKEN -1
#define NAME_TOKEN 0        // General showing of keyword or identifier
#define KEYWORD_TOKEN 1
#define IDENTIFIER_TOKEN 2
#define OPERATOR_TOKEN 3
#define NUM_TOKEN 4
#define CHAR_TOKEN 5
#define PUNC_TOKEN 6
#define PREPRO_TOKEN 7

extern int tokenNum;        // Size of the linked list of tokens

void preProces(FILE *outStream,char *src);      //      Read the source and save it to outStream and if it see another preprocess it call it self
void pushToStr(char *str,char chr);
token *loadfromfile(char *path);    //  returns the pointer of the first node of the token
void pushToken(token t, token **head, token **last,std::vector<char *> *srcDef, std::vector<char *> *destDef);
int getType(char chr);
token *gotoLastNode(token *head);
char *stringTokenizer(char *string,char delim,int tokeN);
int idOrKeyword(char *value);
token *getLastToken(token *start,token *dest);

#endif //CCOMPILER_LOADER_H
