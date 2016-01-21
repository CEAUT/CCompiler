//
// Created by ahmad on 1/16/16.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "irgen.h"
#include "identifierTable.h"
#include "errorgen.h"

variable *headOfVariable;
variable *lastOfVariable;
int numOfVariable;

number *headOfNumber;
number *lastOfNumber;
int numOfNumber;

int numOfTemp;

void setValue(char *name,int lineNum)
{
    variable *var = findVar(name);
    if(var != NULL){
        var->isInit = true;
    } else{
        generateErr(lineNum,ERR_NOT_DEF_VAR,name,NULL);
    }
}
char *newTempMem()
{
    char *res = (char *)malloc((NUMBER_LEN_LIM + 2) * sizeof(char));
    sprintf(res,"_t%d",numOfTemp);
    numOfTemp++;
    return res;
}

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
        lastOfVariable->type = TYPE_INT;
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
        lastOfVariable->type = TYPE_FLOAT;
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
        lastOfVariable->type = TYPE_BOOL;
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
        lastOfVariable->type = TYPE_CHAR;
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

bool hasValue(char *name)
{
    variable *var = findVar(name);
    return var->isInit;
}

int getType(char *name)
{
    variable *var = findVar(name);
    if(var != NULL)
        return var->type;
    else
        return TYPE_NOT_DECLARE;
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
    char *res = (char *) malloc((NUMBER_LEN_LIM + 2) * sizeof(char));
    number *num = findNum(value);
    if(num == NULL) {

        // Add new number to the linked list
        if (headOfNumber == NULL) {
            headOfNumber = (number *) malloc(sizeof(number));
            lastOfNumber = headOfNumber;
        } else {
            lastOfNumber->next = (number *) malloc(sizeof(number));
            lastOfNumber = lastOfNumber->next;
        }
        lastOfNumber->next = NULL;
        lastOfNumber->id = numOfNumber;
        strcpy(lastOfNumber->value, value);
        numOfNumber++;
        sprintf(res, "_n%d", lastOfNumber->id);
#ifdef DEBUG_MODE
        printf("%s := %s\n",res,value);
#else
        fprintf(irfile,"%s := %s\n",res,value);
#endif
    } else {

        // This number is existed in the linked list and it can be reusable
        sprintf(res, "_n%d", num->id);
    }

    return res;
}

number *findNum(char *value)
{
    number *ptr = headOfNumber;
    while (ptr != NULL)
    {
        if(0 == strcmp(ptr->value,value))
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}