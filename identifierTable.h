//
// Created by ahmad on 1/16/16.
//
/*
 * This file handles the table of identifiers
 * For example if the programmer define a variable in the code
 * a new field push to this table
 */
#ifndef CCOMPILER_IDENTIFIERTABLE_H
#define CCOMPILER_IDENTIFIERTABLE_H

#include "limits.h"

struct variable{
    int id;
    char name[IDENTIFIER_NAME_LEN_LIM];
    int type;
    void *value;
    bool isInit;
    variable *next;
};

struct number{
    int id;
    char value[NUMBER_LEN_LIM];
    number *next;
};

#define TYPE_NOT_DECLARE 1100
#define TYPE_INT 1101
#define TYPE_BOOL 1102
#define TYPE_CHAR 1103
#define TYPE_FLOAT 1104

extern variable *headOfVariable;
extern variable *lastOfVariable;
extern int numOfVariable;

int getType(char *name);
char *getId(char *name);          // Returns the id of a variable
void newInt(char *name, int lineNum, char *file);
void newFloat(char *name, int lineNum, char *file);
void newBool(char *name, int lineNum, char *file);
void newChar(char *name, int lineNum, char *file);
variable *findVar(char *name);
bool hasValue(char *name);
void setValue(char *name,int lineNum);




extern number *headOfNumber;
extern number *lastOfNumber;
extern int numOfNumber;

char *newNumber(char *value);
number *findNum(char *value);

extern int numOfTemp;
char *newTempMem();

#endif //CCOMPILER_IDENTIFIERTABLE_H
