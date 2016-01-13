//
// Created by ahmad on 1/12/16.
//

#include "loader.h"
#include "errorgen.h"

void loadfromfile(char *path)
{
    FILE *file;
    file = fopen(path,"r");     // Open the file for reading the source from it
    if(file == NULL)
    {
        generateErr(NO_LINE_SPECIFIED,FILE_NOT_FOUND,path);
        return;
    }
}