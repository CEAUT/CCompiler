//
// Created by ahmad on 1/16/16.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "identifierTable.h"
#include "errorgen.h"

variable *headOfVariable;
variable *lastOfVariable;
int numOfVariable;

number *headOfNumber;
number *lastOfNumber;
int numOfNumber;

void newInt(char *name, int lineNum, char *file)
{
    if(findVar(name) == NULL){

        if(headOfVariable == NULL)
        {
            headOfVariable = (variable *)malloc(sizeof(variable));
            lastOfVariable = headOfVariable;
        } else{
            lastOfVariable->next = (variable *)malloc(sizeof(variable));
            lastOfVariable = lastOfVariable->next;
        }

        lastOfVariable->id = numOfVariable;
        lastOfVariable->next = NULL;
        strcpy(lastOfVariable->name,name);
        lastOfVariable->value = malloc(sizeof(int));
        lastOfVariable->isInit = false;

        numOfVariable++;
    } else{
        generateErr(lineNum,ERR_DEF_VAR,name,file);
    }
}
void newFloat(char *name, int lineNum, char *file)
{
    if(findVar(name) == NULL){

        if(headOfVariable == NULL)
        {
            headOfVariable = (variable *)malloc(sizeof(variable));
            lastOfVariable = headOfVariable;
        } else{
            lastOfVariable->next = (variable *)malloc(sizeof(variable));
            lastOfVariable = lastOfVariable->next;
        }

        lastOfVariable->id = numOfVariable;
        lastOfVariable->next = NULL;
        strcpy(lastOfVariable->name,name);
        lastOfVariable->value = malloc(sizeof(float));
        lastOfVariable->isInit = false;

        numOfVariable++;
    } else{
        generateErr(lineNum,ERR_DEF_VAR,name,file);
    }
}
void newBool(char *name, int lineNum, char *file)
{
    if(findVar(name) == NULL){

        if(headOfVariable == NULL)
        {
            headOfVariable = (variable *)malloc(sizeof(variable));
            lastOfVariable = headOfVariable;
        } else{
            lastOfVariable->next = (variable *)malloc(sizeof(variable));
            lastOfVariable = lastOfVariable->next;
        }

        lastOfVariable->id = numOfVariable;
        lastOfVariable->next = NULL;
        strcpy(lastOfVariable->name,name);
        lastOfVariable->value = malloc(sizeof(bool));
        lastOfVariable->isInit = false;

        numOfVariable++;
    } else{
        generateErr(lineNum,ERR_DEF_VAR,name,file);
    }
}
void newChar(char *name, int lineNum, char *file)
{
    if(findVar(name) == NULL){

        if(headOfVariable == NULL)
        {
            headOfVariable = (variable *)malloc(sizeof(variable));
            lastOfVariable = headOfVariable;
        } else{
            lastOfVariable->next = (variable *)malloc(sizeof(variable));
            lastOfVariable = lastOfVariable->next;
        }

        lastOfVariable->id = numOfVariable;
        lastOfVariable->next = NULL;
        strcpy(lastOfVariable->name,name);
        lastOfVariable->value = malloc(sizeof(char));
        lastOfVariable->isInit = false;

        numOfVariable++;
    } else{
        generateErr(lineNum,ERR_DEF_VAR,name,file);
    }
}

variable *findVar(char *name)
{
    variable *ptr = headOfVariable;
    while (ptr != NULL)
    {
        if(0 == strcmp(ptr->name,name))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

char *getNewId()
{
    char *res = (char *)malloc((NUMBER_LEN_LIM + 2) * sizeof(char));
    sprintf(res,"id%d",numOfVariable);
    numOfVariable++;
    return res;
}

char *getId(char *name)
{
    variable *var = findVar(name);
    if(var != NULL) {
        char *res = (char *) malloc((NUMBER_LEN_LIM + 2) * sizeof(char));
        sprintf(res, "id%d", var->id);
        return res;
    }else{
        return NULL;
    }

}

char *newNumber(char *value)
{
    if(headOfNumber == NULL) {
        headOfNumber = (number *)malloc(sizeof(number));
        lastOfNumber = headOfNumber;
    } else{
        lastOfNumber->next = (number *)malloc(sizeof(number));
        lastOfNumber = lastOfNumber->next;
    }
    lastOfNumber->next = NULL;
    lastOfNumber->id = numOfNumber;
    strcpy(lastOfNumber->value,value);
    numOfNumber++;
    char *res = (char *) malloc((NUMBER_LEN_LIM + 2) * sizeof(char));
    sprintf(res, "_t%d", lastOfNumber->id);
    return res;
}