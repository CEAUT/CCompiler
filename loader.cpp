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

token *loadfromfile(char *path)
{
    FILE *file;
    file = fopen(path,"r");     // Open the file for reading the source from it
    if(file == NULL)
    {
        generateErr(NO_LINE_SPECIFIED,ERR_FILE_NOT_FOUND,path);
        return NULL;
    }

    currentLine = 1;
    tokenNum = 0;
    head = NULL;
    last = NULL;

    token tok;

    strcpy(tok.value,"");

    char chr = fgetc(file);

    while((getType(chr) == SPACE_TOKEN) && (!feof(file))) {
        if (chr == '\n') {
            currentLine++;
        }
        chr = fgetc(file);
    }
    tok.lineNumber = currentLine;
    pushToStr(tok.value,chr);
    int lastType = getType(chr);

    while(!feof(file)){
        chr = fgetc(file);
        if(chr == '\n') {
            if(strlen(tok.value) != 0){
                tok.type = lastType;
                pushToken(tok);
                strcpy(tok.value,"");
            }
            currentLine++;
            tok.lineNumber = currentLine;
            lastType = UNKNOWN_TOKEN;

        }else if(chr == '\t'){
            if(strlen(tok.value) != 0){
                tok.type = lastType;
                pushToken(tok);
                strcpy(tok.value,"");
            }

        }else if(getType(chr) == PUNC_TOKEN){
            if(strlen(tok.value) != 0){
                tok.type = lastType;
                tok.lineNumber = currentLine;
                pushToken(tok);
                strcpy(tok.value,"");
            }

            if(chr == 39){
                pushToStr(tok.value,chr);
                chr = fgetc(file);
                while((chr != 39) && (!feof(file) && (chr != '\n')) ){
                    pushToStr(tok.value,chr);
                    chr = fgetc(file);
                }
                pushToStr(tok.value,chr);
                lastType = CHAR_TOKEN;
                tok.type = lastType;
                pushToken(tok);
                strcpy(tok.value,"");
            } else{
                lastType = PUNC_TOKEN;
                tok.type = lastType;
                pushToStr(tok.value,chr);
                pushToken(tok);
                strcpy(tok.value,"");
                lastType = UNKNOWN_TOKEN;
            }
        }else if(chr == ' ') {
            if (strlen(tok.value) != 0) {
                tok.type = lastType;
                pushToken(tok);
                strcpy(tok.value, "");
            }
        }else if((getType(chr) == NUM_TOKEN) && (lastType != NAME_TOKEN)){
            pushToStr(tok.value,chr);
            lastType = getType(chr);
        }else if(getType(chr) == OPERATOR_TOKEN){
            if(lastType != OPERATOR_TOKEN)
            {
                if(strlen(tok.value) != 0)
                {
                    tok.type = lastType;
                    pushToken(tok);
                    strcpy(tok.value,"");
                }
            }
            lastType = OPERATOR_TOKEN;
            pushToStr(tok.value,chr);
        }else{

            if(lastType == UNKNOWN_TOKEN)
                lastType = getType(chr);

            if(lastType != getType(chr)){
                if((lastType == NAME_TOKEN) && (getType(chr) == NUM_TOKEN)){
                    pushToStr(tok.value,chr);
                } else{
                    if(strlen(tok.value) != 0){
                        tok.type = lastType;
                        pushToken(tok);
                        strcpy(tok.value,"");
                        lastType = UNKNOWN_TOKEN;
                    }
                }
            }else{
                pushToStr(tok.value,chr);
                lastType = getType(chr);
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
            (chr == 39) ||      // stands for the ' character
            (chr == ';'))
        return PUNC_TOKEN;

    if((chr == ' ') || (chr == '\n') || (chr == '\t'))
        return SPACE_TOKEN;
}

void pushToStr(char *str,char chr)
{
    int len = strlen(str);
    str[len] = chr;
    str[len + 1] = 0;
}