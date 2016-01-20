//
// Created by ahmad on 1/17/16.
//

#include "irgen.h"
#include "identifierTable.h"
#include <string.h>
#include <stack>
#include "syntax.h"

#define DEBUG_MODE

bool seenMain;
int lableCounter;
FILE *irfile;

char *getNewLable()
{
    char *res = (char *)malloc((NUMBER_LEN_LIM + 1) * sizeof(char));
    sprintf(res,"L%d",++lableCounter);
    return res;
}

token *whiilestatement(token *head)
{
    using namespace std;

    char *lable1 = getNewLable();
    printf("%s:\n",lable1);

    head = head->next;     // It shoud be (
    stack<int > exp;
    exp.push(PUNC_PARAN_OP);

    head = head->next;     // It shoud be something after (
    token *headOfExp = head;
    do{
        if(strcmp(head->next->value,"(") == 0) {
            exp.push(PUNC_PARAN_OP);
        }else if (strcmp(head->next->value,")") == 0){
            exp.pop();
        }
        head = head->next;
    }while (exp.size() != 0);
    char *condition = expressionCal(headOfExp,head);
    char *lable2 = getNewLable();
    char *lable3 = getNewLable();
    printf("IF %s GOTO %s ELSE %s\n",condition,lable2,lable3);
    printf("%s:\n",lable2);
    head = head->next;      // head points to (
    //head = head->next;      // head points to something after (
    head = statement(head);
    printf("GOTO %s\n",lable1);
    printf("%s:\n",lable3);
    token *last = getLastToken(headOfExp,head);


    return last;
}

token *ifStatement(char *condition,token *head)
{
    printf("%d condition size\n",strlen(condition));
    char *lable1 = getNewLable();
    char *lable2 = getNewLable();
    printf("IF %s GOTO %s ELSE %s\n",condition,lable1,lable2);
    printf("%s:\n",lable1);

    head = head->next;
    token *last = statement(head);
    if(strcmp(last->value,"else") == 0){
        char *lable3 = getNewLable();
        printf("GOTO %s:\n",lable3);
        printf("%s:\n",lable2);
        last = last->next;      // last points to something other than else
        last = statement(last);
        printf("%s:\n",lable3);
    } else {
        printf("%s:\n", lable2);
    }
    last = getLastToken(head,last);
    return last;
}

token *mainAnalyser(token *head){
    seenMain = true;
    printf("PROCEDURE MAIN\n");
    printf("BEGIN\n");
    token *tok = statement(head);

    if(tok != NULL)
        generateErr(tok->lineNumber,ERR_STATE_AFTER_MAIN,"","");
    printf("RETURN\n");
    return tok;
}
token *statement(token *head)
{
    using namespace std;

    stack<int> scope;


    token *ptr = head;
    do {
        if(strcmp(ptr->value,"{") == 0) {
            scope.push(PUNC_BRACE_OP);
        } else if (strcmp(ptr->value,"}") == 0){
            scope.pop();

            //  Checking for main function
        } else if ((ptr->type == KEYWORD_TOKEN) && (strcmp(ptr->value,"void") == 0)) {
            if (strcmp(ptr->next->value, "main") == 0) {
                if (!seenMain) {
                    ptr = ptr->next;     // Now ptr points to the main keyword
                    // ignoring ( and )
                    ptr = ptr->next;    // Now ptr points to the (
                    ptr = ptr->next;    // Now ptr points to the )
                    ptr = ptr->next;    // Now ptr points to the {
                    ptr = mainAnalyser(ptr);
                } else {
                    generateErr(ptr->lineNumber, ERR_TWO_MAIN, "", ptr->fileName);
                }

            } else {
                generateErr(ptr->lineNumber, ERR_NO_VOID_TYPE_ID, "", ptr->fileName);
            }

        } else if(strcmp(ptr->value,"return") == 0){
            if(strcmp(ptr->next->value,";") == 0){
                printf("RETURN\n");
                ptr = ptr->next;        // ptr points to the ;
                if((strcmp(ptr->next->value,"}") != 0) && (scope.size() != 0)){
                    generateWar(ptr->lineNumber,WAR_AFTER_RETURN_STATEMENT,"",ptr->fileName);
                }
            } else{
                generateErr(ptr->lineNumber,ERR_SEMICOLON_AFTER_RETURN,"",ptr->fileName);
                while(strcmp(ptr->value,";") != 0)
                    ptr = ptr->next;
            }
        } else if (strcmp(ptr->value, "int") == 0) {

            ptr = ptr->next;
            newInt(ptr->value, ptr->lineNumber, ptr->fileName);
            char *id = getId(ptr->value);
            if (strcmp(ptr->next->value, "=") == 0) {
                setValue(ptr->value,ptr->lineNumber);
                ptr = ptr->next;
                token *headOfExp = ptr->next;
                while (strcmp(ptr->next->value, ";") != 0) {
                    ptr = ptr->next;
                }
                printf("%s := %s\n", id ,expressionCal(headOfExp, ptr));
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }

        } else if (strcmp(ptr->value, "float") == 0) {

            ptr = ptr->next;
            newFloat(ptr->value, ptr->lineNumber, ptr->fileName);
            char *id = getId(ptr->value);
            if (strcmp(ptr->next->value, "=") == 0) {
                setValue(ptr->value,ptr->lineNumber);
                ptr = ptr->next;
                token *headOfExp = ptr->next;
                while (strcmp(ptr->next->value, ";") != 0) {
                    ptr = ptr->next;
                }
                printf("%s := %s\n", id ,expressionCal(headOfExp, ptr));
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }

        } else if (strcmp(ptr->value, "bool") == 0) {

            ptr = ptr->next;
            newBool(ptr->value, ptr->lineNumber, ptr->fileName);
            char *id = getId(ptr->value);
            if (strcmp(ptr->next->value, "=") == 0) {
                setValue(ptr->value,ptr->lineNumber);
                ptr = ptr->next;
                token *headOfExp = ptr->next;
                while (strcmp(ptr->next->value, ";") != 0) {
                    ptr = ptr->next;
                }
                printf("%s := %s\n", id ,expressionCal(headOfExp, ptr));
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }

        } else if (strcmp(ptr->value, "char") == 0) {
            ptr = ptr->next;
            newChar(ptr->value, ptr->lineNumber, ptr->fileName);
            char *idname = (char *)malloc(IDENTIFIER_NAME_LEN_LIM * sizeof(char));
            strcpy(idname, ptr->value);
            ptr = ptr->next;
            if (strcmp(ptr->value, "=") == 0) {
                if (ptr->next->type == CHAR_TOKEN) {
                    printf("%s := %s\n",getId(idname),newNumber(ptr->next->value));
                    setValue(idname,ptr->lineNumber);
                }else if(ptr->next->type == NUM_TOKEN){
                    generateErr(ptr->lineNumber,ERR_TYPE_MISSMATCH_INT_TO_CHAR,"",ptr->fileName);
                }else if(ptr->next->type == IDENTIFIER_TOKEN){

                    if(getType(ptr->next->value) == TYPE_CHAR){
                        if(hasValue(ptr->next->value)) {
                            printf("%s := %s\n", getId(idname), getId(ptr->next->value));
                            setValue(idname, ptr->lineNumber);
                        } else{
                            generateErr(ptr->lineNumber,ERR_NOT_INIT_VAR,ptr->next->value,ptr->next->fileName);
                        }
                    } else{
                        generateErr(ptr->lineNumber,ERR_TYPE_MISSMATCH_INT_TO_CHAR,"",ptr->fileName);
                    }
                }
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }
        }else if(ptr->type == IDENTIFIER_TOKEN){



            if (strcmp(ptr->next->value, "=") == 0) {

                char *id = (char *)malloc(IDENTIFIER_NAME_LEN_LIM * sizeof(char));

                if((getType(ptr->value) == TYPE_INT) || (getType(ptr->value) == TYPE_FLOAT) ||
                   (getType(ptr->value) == TYPE_BOOL)) {
                    strcpy(id, getId(ptr->value));
                    setValue(ptr->value, ptr->lineNumber);
                    ptr = ptr->next;        // ptr points to the =
                    ptr = ptr->next;        // ptr points to the after =
                    token *head = ptr;
                    while (strcmp(ptr->next->value, ";") != 0) {
                        ptr = ptr->next;
                    }
                    printf("%s := %s\n", id, expressionCal(head, ptr));
                } else if(getType(ptr->value) == TYPE_NOT_DECLARE){
                    strcpy(id, ptr->value);
                    generateErr(ptr->lineNumber,ERR_NOT_DEF_VAR,ptr->value,ptr->fileName);
                    ptr = ptr->next;        // ptr points to the =
                    ptr = ptr->next;        // ptr points to the after =
                    token *head = ptr;
                    while (strcmp(ptr->next->value, ";") != 0) {
                        ptr = ptr->next;
                    }
                    printf("%s := %s\n", id, expressionCal(head, ptr));

                } else if (getType(ptr->value) == TYPE_CHAR){

                    char *idname = (char *)malloc(IDENTIFIER_NAME_LEN_LIM * sizeof(char));
                    strcpy(idname, ptr->value);
                    ptr = ptr->next;
                    if (strcmp(ptr->value, "=") == 0) {
                        if (ptr->next->type == CHAR_TOKEN) {
                            printf("%s := %s\n",getId(idname),newNumber(ptr->next->value));
                            setValue(idname,ptr->lineNumber);
                        }else if(ptr->next->type == NUM_TOKEN){
                            generateErr(ptr->lineNumber,ERR_TYPE_MISSMATCH_INT_TO_CHAR,"",ptr->fileName);
                        }else if(ptr->next->type == IDENTIFIER_TOKEN){

                            if(getType(ptr->next->value) == TYPE_CHAR){
                                if(hasValue(ptr->next->value)) {
                                    printf("%s := %s\n", getId(idname), getId(ptr->next->value));
                                    setValue(idname, ptr->lineNumber);
                                } else{
                                    generateErr(ptr->lineNumber,ERR_NOT_INIT_VAR,ptr->next->value,ptr->next->fileName);
                                }
                            } else{
                                generateErr(ptr->lineNumber,ERR_TYPE_MISSMATCH_INT_TO_CHAR,"",ptr->fileName);
                            }
                        }
                    } else if (strcmp(ptr->value, ";") != 0) {
                        // an error could be generated
                    }

                }
            }else{
                //  Todo some additional error checking
            }

        } else if (strcmp(ptr->value, "if") == 0){
            ptr = ptr->next;     // It shoud be (
            stack<int > exp;
            exp.push(PUNC_PARAN_OP);

            token *headOfExp = ptr;
            do{
                ptr = ptr->next;     // It shoud be something after (
                if(strcmp(ptr->next->value,"(") == 0) {
                    exp.push(PUNC_PARAN_OP);
                }else if (strcmp(ptr->next->value,")") == 0){
                    exp.pop();
                }
                ptr = ptr->next;
            }while (exp.size() != 0);
            printf("log : %s\n",headOfExp->value);
            headOfExp = headOfExp->next;
            ptr = getLastToken(headOfExp,ptr);
            ptr = ifStatement(expressionCal(headOfExp,ptr),ptr);

        } else if(strcmp(ptr->value, "while") == 0){
            ptr = whiilestatement(ptr);
        }
        if (ptr == NULL)
            return NULL;
        ptr = ptr->next;
    }while((scope.size() != 0) && (ptr != NULL) );

    return ptr;
}
void generateIR(token *head)
{
    seenMain = false;
    token *ptr = head;

    while (ptr != NULL)
    {
        ptr = statement(ptr);
    }

}
char *expressionCal(token *start, token *end) {
    using namespace std;

    vector<char *> _operand;
    vector<char *> _operator;
    token *ptr = start;

    if(start == end)
    {
        if (ptr->type == NUM_TOKEN) {
            return newNumber(ptr->value);
        } else if (ptr->type == IDENTIFIER_TOKEN) {
            return getId(ptr->value);
        }
    }

    while (ptr != end->next) {
        if (ptr->type == PUNC_TOKEN) {
            if(strcmp(ptr->value,"(") == 0)          // A parentheses expression detected
            {
                stack<int> punc;


                token *_start = ptr->next;
                do
                {
                    if(ptr->type == PUNC_TOKEN)
                    {
                        if(strcmp(ptr->value,"(") == 0){
                            punc.push(PUNC_PARAN_OP);
                        }else if(strcmp(ptr->value,")") == 0){
                            punc.pop();
                        }
                    }
                    ptr = ptr->next;
                }while (punc.size() != 0);

                ptr = getLastToken(start,ptr);
                ptr = getLastToken(start,ptr);
                char *res = expressionCal(_start,ptr);
                _operand.push_back(res);
            }

        } else if (ptr->type == NUM_TOKEN) {
            _operand.push_back(newNumber(ptr->value));
        } else if (ptr->type == IDENTIFIER_TOKEN) {
            int type = getType(ptr->value);

            if((type == TYPE_INT) || (type == TYPE_FLOAT) || (type == TYPE_BOOL) || (type == TYPE_BOOL)){
                if(hasValue(ptr->value)){
                    _operand.push_back(getId(ptr->value));
                } else{
                    generateErr(ptr->lineNumber,ERR_NOT_INIT_VAR,ptr->value,ptr->fileName);
                    _operand.push_back(getId(ptr->value));
                }
            } else if(type == TYPE_NOT_DECLARE){    // This variable is not declared yet
                generateErr(ptr->lineNumber,ERR_NOT_DEF_VAR,ptr->value,ptr->fileName);
                _operand.push_back(ptr->value);
            }
        } else if (ptr->type == OPERATOR_TOKEN) {
            _operator.push_back(ptr->value);
        } else if (ptr->type == CHAR_TOKEN) {
            _operand.push_back(newNumber(ptr->value));
        } else if (ptr->type == KEYWORD_TOKEN){
            if(strcmp(ptr->value,"min") == 0){
                //  To do the min calculation expressions
            }else if(strcmp(ptr->value,"max") == 0){
                //  To do the max calculation expressions
            }
        }
        ptr = ptr->next;
    }


    // Calculating the expression
    char *tempMem = (char *)malloc(10 * sizeof(char));


    //  1st priority is * and /
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"*") == 0) ||
           (strcmp(_operator[i],"/") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    // 2nd priority is + and -

    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"+") == 0) ||
           (strcmp(_operator[i],"-") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }


    //  3rd priority is <= >= < >
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],">=") == 0) ||
           (strcmp(_operator[i],"<=") == 0) ||
           (strcmp(_operator[i],"<") == 0) ||
           (strcmp(_operator[i],">") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    // 4th priority is == and !=
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"==") == 0) ||
           (strcmp(_operator[i],"!=") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    // 5th priority is &&
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"&&") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    // 6th priority is ||
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"||") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    // 7th priority is =
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"=") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            _operand.erase(_operand.begin() + (i + 1));
            _operator.erase(_operator.begin() + i);
            i--;
        }
    }

    return tempMem;
}