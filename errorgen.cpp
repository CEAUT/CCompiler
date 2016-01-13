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
        case 0:
            printf("The file '%s' is not existing.\n",parameter);
            break;
        case 1:
            break;
    }
}

bool isAnyErr()
{
    bool res = errorOccuerd;
    errorOccuerd = false;
    return errorOccuerd;
}