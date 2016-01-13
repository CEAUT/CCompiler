//
// Created by ahmad on 1/12/16.
//

#include <string.h>
#include "loader.h"
#include "errorgen.h"

int currentLine;
int tokenNum;
token *head;
token *last;

void loadfromfile(char *path)
{
    FILE *file;
    file = fopen(path,"r");     // Open the file for reading the source from it
    if(file == NULL)
    {
        generateErr(NO_LINE_SPECIFIED,ERR_FILE_NOT_FOUND,path);
        return;
    }

    currentLine = 1;
    tokenNum = 0;
    head = NULL;
    last = NULL;

    token tok;
    strcpy(tok.value,"");

    char chr;
    int lastType = getType(chr);
    pushToStr(tok.value,chr);

    while(!feof(file)){

        chr = fgetc(file);

        if(chr == '\n') {
            currentLine++;
            tok.lineNumber = currentLine - 1;
            if (strlen(tok.value) != 0) {
                pushToken(tok);
                strcpy(tok.value, "");
            }
            lastType = UNKNOWN_TOKEN;
        }else if(chr == '\t'){
            lastType = UNKNOWN_TOKEN;
        }else if(chr == ' '){
            tok.lineNumber = currentLine;
            if((strlen(tok.value) != 0) && (strcmp(tok.value," ") != 0)) {
                pushToken(tok);
                strcpy(tok.value, "");
            }else{
                continue;
            }
            /*chr = fgetc(file);
            if(chr != ' ') {
                pushToStr(tok.value, chr);
                lastType = getType(chr);
            }*/

        }else if(chr == EOF) {
            tok.lineNumber = currentLine;
            pushToken(tok);
            strcpy(tok.value,"");
            lastType = getType(chr);
            break;
        } else{

            if(getType(chr) != lastType){
                if((lastType == NAME_TOKEN) && (getType(chr) == NUM_TOKEN)){
                    pushToStr(tok.value,chr);
                    tok.type = IDENTIFIER_TOKEN;
                }else{
                    tok.lineNumber = currentLine;
                    tok.type = lastType;
                    pushToken(tok);
                    strcpy(tok.value,"");
                    pushToStr(tok.value,chr);
                    lastType = getType(chr);
                }

            }else{

                if(getType(chr) == PUNC_TOKEN) {
                    if(chr == 39){      // For reading the assignment to character
                        pushToStr(tok.value,chr);
                        chr = fgetc(file);
                        pushToStr(tok.value,chr);
                        chr = fgetc(file);
                        if(chr != 39){      // ' punctuation mark for closing the character scope
                            generateErr(currentLine,ERR_SINGLE_CUOT_NOTCLOSE,NULL);
                        }else{
                            pushToStr(tok.value,chr);
                            tok.type = CHAR_TOKEN;
                            tok.lineNumber = currentLine;
                            strcpy(tok.value, "");
                        }
                    }else {
                        tok.lineNumber = currentLine;
                        pushToken(tok);
                        strcpy(tok.value, "");
                    }
                }
                pushToStr(tok.value,chr);
            }
        }
    }
}

void pushToken(token t)
{

    if(tokenNum == 0)
    {
        head = (token *)malloc(sizeof(token));
        last = head;
        if(head == NULL)
        {
            printf("Cannot allocate memory.\n");
            return;
        }
        head->type = t.type;
        head->lineNumber = t.lineNumber;
        strcpy(head->value, t.value);
        head->next = NULL;
    }else{
        last->next = (token *)malloc(sizeof(token));
        last = last->next;
        strcpy(last->value, t.value);
        last->lineNumber = t.lineNumber;
        last->type = t.type;
        last->next = NULL;
    }
    tokenNum ++;
}

int getType(char chr)
{
    if((chr >= 'A') && (chr <= 'Z'))
        return NAME_TOKEN;

    if(chr == '_')
        return NAME_TOKEN;

    if((chr >= 'a') && (chr <= 'z'))
        return NAME_TOKEN;

    if ((chr >= '0') && (chr <= '9'))
        return NUM_TOKEN;
    if (chr == '.')
        return NUM_TOKEN;

    if ((chr == '+') || (chr == '-') ||
            (chr == '=') || (chr == '*') ||
            (chr == '/') || (chr == '>') ||
            (chr == '<') || (chr == '!') ||
            (chr == '&') || (chr == '|') ||
            (chr == '#'))
        return OPERATOR_TOKEN;

    if ((chr == '+') || (chr == '-') ||
            (chr == ',' ) || (chr == '"') ||
            (chr == '(') || (chr == ')') ||
            (chr == '{') || (chr == '}') ||
            (chr == 39) ||      // stands for th ' character
            (chr == ';'))
        return PUNC_TOKEN;
}

void pushToStr(char *str,char chr)
{
    int len = strlen(str);
    str[len] = chr;
    str[len + 1] = 0;
}