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
            printf("'%s' is an unknow preprecess command in the file '%s'.\n",parameter,file);
            break;
        case ERR_SYNTAX_IN_PREPROCESS:
            printf("Syntax error occured in the preprocess of file '%s'. A cuotation should be used to determine the path of the desired include file.\n",file);
            break;
        case ERR_PUNCT_NOT_EXPECTED:
            printf("The punctuation mark %s is not expected to be in line %d of the file %s.\n",parameter,lineNum,file);
            break;
        case ERR_PUNCT_CLOSE_EXPECTED:
            printf("The punctuation mark %s expected to be closed in line %d of the file %s.\n",parameter,lineNum,file);
            break;

        case ERR_OPERATOR_NOT_OVERLODED:
            printf("The operator %s used in line %d is not overloaded yet.\n",parameter,lineNum);
            break;

        case ERR_DEF_VAR:
            printf("The identifier '%s' that is declaring in line %d, was declared before.\n",parameter,lineNum);
            break;
        case ERR_NOT_DEF_VAR:
            printf("The identifier '%s' is using in line %d without being declared.\n",parameter,lineNum);
            break;
        case ERR_NOT_INIT_VAR:
            printf("The identifier '%s' is using in line %d without being initialized and has no proper value.\n",parameter,lineNum);
            break;


        case ERR_AFTER_PARENTHESIS_OPEN:
            printf("After ( just an identifier, an operator, a number or another ( should be seen in line %d.\n",lineNum);
            break;
        case ERR_AFTER_PARENTHESIS_CLOSE:
            printf("After ) just an identifier, an operator, a number or another ) should be seen in line %d.\n",lineNum);
            break;

        case ERR_AFTER_OPR:
            printf("After an operator an identifier, (, or a number should be seen in line %d.\n ",lineNum);
            break;
        case ERR_REPLACE:
            printf("In line %d should be %s.",lineNum,parameter);
            break;
        case ERR_ASSIGN_TO_NUMBER:
            printf("Nothing could be assigned to a number in line %d.\n",lineNum);
            break;
        case ERR_AFTER_NULL:
            printf("After NULL should be %s in line %d.\n", parameter, lineNum);
            break;
        case ERR_NULL_NOT_OPERATABLE:
            printf("Null in the line %d is not operatble and could not add to anything\n",lineNum);
            break;
        case ERR_OPERATOR_OR_:
            printf("Operator or %s should be put in line %d\n",parameter,lineNum);
            break;
        case ERR_ID_OR_NUM:
            printf("An identifier or a number should be in line %d.\n",lineNum);
            break;
        case ERR_AFTER_IF_OR_WHILE_PARENTHESIS_OPEN:
            printf("After the keyword %s bucn of () should be open and close in line %d.\n",parameter,lineNum);
            break;
        case ERR_AFTER_ELSE_BRACE_OPEN:
            printf("After the ELSE statement in line %d, a { should be seen.\n",lineNum);
            break;
        case ERR_ASSIGN_OR_SEMICOLON:
            printf("In line %d should be = or ;.\n",lineNum);
            break;
        case ERR_SHOULD_DECLARE_ID:
            printf("In line %d an identifier should be declared.\n",lineNum);
            break;
        case ERR_SEMICOLON_NEEDED:
            printf("In line %d an semicolon is needed.\n",lineNum);
            break;
        case ERR_BOOL_TYPE_MISMATCH:
            printf("An identifier of type bool can't accept any values excepts TRUE or FALSE in line %d.\n",lineNum);
            break;
        case ERR_ASSIGNMENT_EXPECTED:
            printf("Here = should be seen in line %d.\n",lineNum);
            break;
        case ERR_CHAR_TYPE_MISMATCH:
            printf("An identifier of type char can't accept any values excepts char types in line %d.\n",lineNum);
            break;
        case ERR_MAIN_SCOPE_START:
            printf("Main scope should be started with in line %d.\n",lineNum);
            break;
        case ERR_MAIN_PARENTHESIS:
            printf("After ( in line %d should not anything be seen except ).\n",lineNum);
            break;
        case ERR_MAIN_AFTER_VOID:
            printf("After a void data type in line %d, the main funcion should be come.\n",lineNum);
            break;
        case ERR_KEYWORD_EXPECTED:
            printf("A keyword expected to be in line %d.\n",lineNum);
            break;

        case ERR_TWO_MAIN:
            printf("Main function can be implemented one time per an application. It is redifed in line %d.\n",lineNum);
            break;

        case ERR_STATE_AFTER_MAIN:
            printf("The statements that came in line %d is out of main scope and could not be executed.\n",lineNum);
            break;
        case ERR_NO_VOID_TYPE_ID:
            printf("Void type used in line %d cannot to be used for defining any other identifier exept main function.\n",lineNum);
            break;

        case ERR_TYPE_MISSMATCH_INT_TO_CHAR:
            printf("Type missmatch occured in line %d. Just a vlue of char can be assigned to a char varaible.\n",lineNum);
            break;

        case ERR_SEMICOLON_AFTER_RETURN:
            printf("After the return statement in line %d should be a semicolon.\n",lineNum);
            break;
    }
}
void generateWar(int lineNum, int warningCode, char *parameter, char *file)
{
    printf("warning #%o : ",warningCode);
    switch (warningCode) {

        case WAR_AFTER_RETURN_STATEMENT:
            printf("The statement(s) after the return statement in line %d won't be executed.\n", lineNum);
            break;
    }
}
bool isAnyErr()
{
    return errorOccuerd;
}