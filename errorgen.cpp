//
// Created by ahmad on 1/12/16.
//
#include <stdio.h>
#include "errorgen.h"


bool errorOccuerd;
void generateErr(int lineNum, int errorCode, char *parameter, char *file)
{
    errorOccuerd = true;
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
            printf("The punctuation mark %s is not expected to be in line of %d the file %s.\n",parameter,lineNum,file);
            break;
    }
}

bool isAnyErr()
{
    bool res = errorOccuerd;
    errorOccuerd = false;
    return errorOccuerd;
}