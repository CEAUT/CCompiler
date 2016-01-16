//
// Created by ahmad on 1/16/16.
//

#include "syntax.h"
#include <stack>
#include <string.h>

void checkPunc(token *head)
{
    using namespace std;
    stack<int> punc;
    token *ptr = head;

    while (ptr != NULL)
    {
        if(ptr->type == PUNC_TOKEN){
            int type;
            if(strcmp(ptr->value,"{") == 0){
                type = PUNC_BRACE_OP;
            }else if(strcmp(ptr->value,"(") == 0){
                type = PUNC_PARAN_OP;
            } else if(strcmp(ptr->value,"}") == 0){
                type = PUNC_BRACE_CL;
            }else if(strcmp(ptr->value,")") == 0) {
                type = PUNC_PARAN_CL;
            }else{
                ptr = ptr->next;
                continue;
            }
            if(type > 0){
                punc.push(type);
            }else{      // type < 0
                if(punc.size() == 0) {      // No punc has been opened to expect one to be close
                    generateErr(ptr->lineNumber, ERR_PUNCT_NOT_EXPECTED, ptr->value, "");
                }else {
                    if ((punc.top() + type) != 0) {
                        generateErr(ptr->lineNumber, ERR_PUNCT_NOT_EXPECTED, ptr->value, "");
                    }else{
                        punc.pop();
                    }

                }
            }
        }
        ptr = ptr->next;
    }
}