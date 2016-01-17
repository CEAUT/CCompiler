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

    char fileName[FILE_PATH_LEN_LIM];   // To store the file name of the punctuation token that may be mistaken further more

    int lastLine;                       // To store the number of the last line of the file

    while (ptr != NULL)
    {
        if(ptr->type == PUNC_TOKEN){
            int type;
            if(strcmp(ptr->value,"{") == 0){
                type = PUNC_BRACE_OP;
                strcpy(fileName,ptr->fileName);
            }else if(strcmp(ptr->value,"(") == 0){
                type = PUNC_PARAN_OP;
                strcpy(fileName,ptr->fileName);
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
                    generateErr(ptr->lineNumber, ERR_PUNCT_NOT_EXPECTED, ptr->value, ptr->fileName);
                }else {
                    if ((punc.top() + type) != 0) {
                        generateErr(ptr->lineNumber, ERR_PUNCT_NOT_EXPECTED, ptr->value, ptr->fileName);
                    }else{
                        punc.pop();
                    }

                }
            }
        }
        lastLine = ptr->lineNumber;     // To store the number of the last line of the file
        ptr = ptr->next;
    }

    for (int i = 0; i < punc.size(); ++i) {
        printf("why?\n");
        switch (punc.top()){
            case PUNC_PARAN_OP:
                generateErr(lastLine,ERR_PUNCT_CLOSE_EXPECTED,"(",fileName);
                break;
            case PUNC_BRACE_OP:
                generateErr(lastLine,ERR_PUNCT_CLOSE_EXPECTED,"{",fileName);
                break;
        }
        punc.pop();
    }
}