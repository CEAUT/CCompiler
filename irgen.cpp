//
// Created by ahmad on 1/17/16.
//

#include "irgen.h"
#include "identifierTable.h"
#include <string.h>
#include <stack>
#include "syntax.h"

bool seenMain;
int lableCounter;

char *getNewLable()
{
    char *res = (char *)malloc((NUMBER_LEN_LIM + 1) * sizeof(char));
    sprintf(res,"L%d",++lableCounter);
    return res;
}
void assignment(char *varaibleName,token *head)
{
    ;
}

void mainAnalyser(token *head){
    seenMain = true;
    printf("PROCEDURE MAIN\n");
    printf("BEGIN\n");
    statement(head);
    printf("RETURN\n");
}
void statement(token *head)
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
                    mainAnalyser(ptr);
                } else {
                    generateErr(ptr->lineNumber, ERR_TWO_MAIN, "", ptr->fileName);
                }

            } else {
                generateErr(ptr->lineNumber, ERR_NO_VOID_TYPE_ID,"",ptr->fileName);
            }


        } else if (strcmp(ptr->value, "int") == 0) {
            ptr = ptr->next;
            newInt(ptr->value, ptr->lineNumber, ptr->fileName);
            char *id = getId(ptr->value);
            ptr = ptr->next;
            if (strcmp(ptr->value, "=") == 0) {
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
            ptr = ptr->next;
            if (strcmp(ptr->value, "=") == 0) {
                token *headOfExp = ptr->next;

                while (strcmp(ptr->next->value, ";") != 0) {
                    ptr = ptr->next;
                }
                expressionCal(headOfExp, ptr);
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }

        } else if (strcmp(ptr->value, "bool") == 0) {

            ptr = ptr->next;
            newBool(ptr->value, ptr->lineNumber, ptr->fileName);
            ptr = ptr->next;
            if (strcmp(ptr->next->value, "=") == 0) {
                token *headOfExp = ptr->next->next;
                while (strcmp(ptr->next->next->value, ";") != 0) {
                    ptr = ptr->next;
                }
                expressionCal(headOfExp, ptr);
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }

        } else if (strcmp(ptr->value, "char") == 0) {
            ptr = ptr->next;
            newInt(ptr->value, ptr->lineNumber, ptr->fileName);
            ptr = ptr->next;
            if (strcmp(ptr->value, "=") == 0) {
                if (ptr->next->type == CHAR_TOKEN) {

                }
            } else if (strcmp(ptr->value, ";") != 0) {
                // an error could be generated
            }
        }
        ptr = ptr->next;
    }while(scope.size() != 0);
}
void generateIR(token *head)
{
    seenMain = false;
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
            _operand.push_back(ptr->value);
        } else if (ptr->type == OPERATOR_TOKEN) {
            _operator.push_back(ptr->value);
        } else if (ptr->type == CHAR_TOKEN) {
            ;
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

    return tempMem;
}