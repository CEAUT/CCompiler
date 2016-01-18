//
// Created by ahmad on 1/17/16.
//

#include "irgen.h"
#include "identifierTable.h"
#include <string.h>
#include <stack>
#include "syntax.h"

char *expressionCal(token *start, token *end) {
    using namespace std;

    vector<char *> _operand;
    vector<char *> _operator;
    token *ptr = start;

    while (ptr != end->next) {
        if (ptr->type == PUNC_TOKEN) {
            if(strcmp(ptr->value,"("))          // A parentheses expression detected
            {
                stack<int> punc;
                punc.push(PUNC_PARAN_OP);

                token *_start = ptr->next;
                while (punc.size() != 0)
                {
                    ptr = ptr->next;
                    if(ptr->type == PUNC_TOKEN)
                    {
                        if(strcmp(ptr->value,"(") == 0){
                            ;
                        }else if(strcmp(ptr->value,")") == 0){
                            ;
                        }
                    }
                }
            }

        } else if (ptr->type == NUM_TOKEN) {
            _operand.push_back(newNumber(ptr->value));
        } else if (ptr->type == IDENTIFIER_TOKEN) {
            _operand.push_back(ptr->value);
            /*if (findVar(ptr->value) != NULL) {
                if (hasValue(ptr->value)) {
                    _operand.push_back(getId(ptr->value));
                } else {
                    generateErr(ptr->lineNumber, ERR_NOT_INIT_VAR, ptr->value, ptr->fileName);
                    return NULL;
                }
            } else {
                generateErr(ptr->lineNumber, ERR_NOT_DEF_VAR, ptr->value, ptr->fileName);
                return NULL;
            }*/
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
    char *tempMem;

    //  1st priority is * and /
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"*") == 0) ||
           (strcmp(_operator[i],"/") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
        }
    }

    // 2nd priority is + and -
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"+") == 0) ||
           (strcmp(_operator[i],"-") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
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
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
        }
    }

    // 4th priority is == and !=
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"==") == 0) ||
           (strcmp(_operator[i],"!=") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
        }
    }

    // 5th priority is &&
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"&&") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
        }
    }

    // 6th priority is ||
    for (int i = 0; i < _operator.size(); ++i) {
        if((strcmp(_operator[i],"||") == 0)){
            tempMem = newTempMem();
            printf("%s := %s %s %s\n",tempMem,_operand[i],_operator[i],_operand[i+1]);
            strcpy(_operand[i],tempMem);
            for (int j = i+1; j < _operand.size() - 1; ++j) {
                swap(_operand[j],_operand[j+1]);
                swap(_operator[j-1],_operator[j]);
            }
            _operand.pop_back();
            _operator.pop_back();
        }
    }

    printf("res: %s\n",tempMem);
}