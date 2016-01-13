//
// Created by ahmad on 1/12/16.
//

#ifndef CCOMPILER_ERRORGEN_H
#define CCOMPILER_ERRORGEN_H

extern bool errorOccuerd;
#define NO_LINE_SPECIFIED -13

// Error lists:
#define ERR_FILE_NOT_FOUND 0
#define ERR_SINGLE_CUOT_NOTCLOSE 1

/*
 * This function generate error from every part of the code
 * - the first argument is the line number that error was occurred in
 * - the second argument is the error code number that can accept values from the above choices
 * - the third argument gets the parameter needed for generating the error like the name of identifier
 */
void generateErr(int lineNum, int errorCode, char *parameter);
bool isAnyErr();

#endif //CCOMPILER_ERRORGEN_H
