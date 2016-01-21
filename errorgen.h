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
#define ERR_UNKNOWN_PREPROCESS 2
#define ERR_SYNTAX_IN_PREPROCESS 3
#define ERR_PUNCT_NOT_EXPECTED 5
#define ERR_PUNCT_CLOSE_EXPECTED 6
#define ERR_OPERATOR_NOT_OVERLODED 7

#define ERR_SEMICOLON_AFTER_RETURN 20

#define ERR_DEF_VAR 100
#define ERR_NOT_DEF_VAR 101
#define ERR_NOT_INIT_VAR 102

#define ERR_AFTER_PARENTHESIS_OPEN 201
#define ERR_AFTER_PARENTHESIS_CLOSE 202
#define ERR_AFTER_OPR 203
#define ERR_REPLACE 204
#define ERR_ASSIGN_TO_NUMBER 205
#define ERR_AFTER_NULL 206
#define ERR_NULL_NOT_OPERATABLE 207
#define ERR_OPERATOR_OR_ 208
#define ERR_ID_OR_NUM 209
#define ERR_AFTER_IF_OR_WHILE_PARENTHESIS_OPEN 210
#define ERR_AFTER_ELSE_BRACE_OPEN 211
#define ERR_ASSIGN_OR_SEMICOLON 212
#define ERR_SHOULD_DECLARE_ID 213
#define ERR_SEMICOLON_NEEDED 214
#define ERR_BOOL_TYPE_MISMATCH 215
#define ERR_ASSIGNMENT_EXPECTED 216
#define ERR_CHAR_TYPE_MISMATCH 217
#define ERR_MAIN_SCOPE_START 218
#define ERR_MAIN_PARENTHESIS 219
#define ERR_MAIN_AFTER_VOID 220
#define ERR_KEYWORD_EXPECTED 221


#define ERR_TWO_MAIN 300
#define ERR_STATE_AFTER_MAIN 301

#define ERR_NO_VOID_TYPE_ID 501

#define ERR_TYPE_MISSMATCH_INT_TO_CHAR 600

// Warning lists:
#define WAR_AFTER_RETURN_STATEMENT 5001

/*
 * This function generate error from every part of the code
 * - the first argument is the line number that error was occurred in
 * - the second argument is the error code number that can accept values from the above choices
 * - the third argument gets the parameter needed for generating the error like the name of identifier
 */
void generateErr(int lineNum, int errorCode, char *parameter, char *file);
void generateWar(int lineNum, int warningCode, char *parameter, char *file);
bool isAnyErr();

#endif //CCOMPILER_ERRORGEN_H
