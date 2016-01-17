//
// Created by ahmad on 1/12/16.
//
#include <stdio.h>
#include "errorgen.h"


bool errorOccuerd;
void generateErr(int lineNum, int errorCode, char *parameter, char *file)
{
    errorOccuerd = true;
    printf("error #%o : ",errorCode);
    switch (errorCode)
    {
        case ERR_FILE_NOT_FOUND:
            printf("The file '%s' is not existing.\n",parameter);
            break;

        case ERR_SINGLE_CUOT_NOTCLOSE:
            printf("Expected to have ' for characters in line %d of the file '%s'.\n",lineNum,file);
            break;
        case ERR_UNKNOWN_PREPROCESS:
            printf("'%s' is an unknow preprecess command in line %d of the file '%s'.\n",parameter,lineNum,file);
            break;
        case ERR_PUNCT_NOT_EXPECTED:
            printf("The punctuation mark %s is not expected to be in line %d of the file %s.\n",parameter,lineNum,file);
            break;
        case ERR_PUNCT_CLOSE_EXPECTED:
            printf("The punctuation mark %s expected to be closed in line %d of the file %s.\n",parameter,lineNum,file);
            break;


        case ERR_DEF_VAR:
            printf("The identifier '%s' that is declaring in line %d of file %s, was declared before.\n",parameter,lineNum,file);
            break;
        case ERR_NOT_DEF_VAR:
            printf("The identifier '%s' is using in line %d of file %s without being declared.\n",parameter,lineNum,file);
            break;
        case ERR_NOT_INIT_VAR:
            printf("The identifier '%s' is using in line %d of file %s without being initialized and has no proper value.\n",parameter,lineNum,file);
            break;
    }
}

bool isAnyErr()
{
    bool res = errorOccuerd;
    errorOccuerd = false;
    return errorOccuerd;
}