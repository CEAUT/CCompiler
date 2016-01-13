//
// Created by ahmad on 1/12/16.
//
#include <stdio.h>
#include "errorgen.h"

bool errorOccuerd;
void generateErr(int lineNum, int errorCode, char *parameter)
{
    errorOccuerd = true;
    switch (errorCode)
    {
        case ERR_FILE_NOT_FOUND:
            printf("The file '%s' is not existing.\n",parameter);
            break;
        case ERR_SINGLE_CUOT_NOTCLOSE:
            printf("Expected to have ' for characters in line %d\n",lineNum);
            break;
    }
}

bool isAnyErr()
{
    bool res = errorOccuerd;
    errorOccuerd = false;
    return errorOccuerd;
}