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

#define TYPE_INT 1100
#define TYPE_BOOL 1101
#define TYPE_CHAR 1102
#define TYPE_FLOAT 1103

extern variable *headOfVariable;
extern variable *lastOfVariable;
extern int numOfVariable;

char *getNewId();
char *getId(char *name);          // Returns the id of a variable
void newInt(char *name, int lineNum, char *file);
void newFloat(char *name, int lineNum, char *file);
void newBool(char *name, int lineNum, char *file);
void newChar(char *name, int lineNum, char *file);
variable *findVar(char *name);




extern number *headOfNumber;
extern number *lastOfNumber;
extern int numOfNumber;

char *newNumber(char *value);

#endif //CCOMPILER_IDENTIFIERTABLE_H
