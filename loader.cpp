//
// Created by ahmad on 1/12/16.
//
#include <string.h>
#include "loader.h"
#include "errorgen.h"
#include <vector>

int tokenNum;

using namespace std;

void preProces(FILE *outStream,char *src)
{
    printf("%s\n",src);
    FILE *srcFile = fopen(src,"r");
    char c = fgetc(srcFile);
    while (c != EOF){
        if(c == '#') {
            char preprocessLine[LINE_LEN_LIM];
            fgets(preprocessLine,LINE_LEN_LIM,srcFile);
            //printf("Line is %s\n",preprocessLine);
            char *ppType = stringTokenizer(preprocessLine,' ',0);
            //printf("Type is %s\n",ppType);
            if(strcmp(ppType,"include") == 0){
                char *path;
                path = stringTokenizer(preprocessLine,34,1);
                preProces(outStream,path);
            } else{
                generateErr(0,ERR_UNKNOWN_PREPROCESS,ppType,src);
            }
        }else {
            fputc(c, outStream);
        }
        c = fgetc(srcFile);
    }
}
token *loadfromfile(char *path)
{
    FILE *file;
    file = fopen(path,"r");     // Open the file for reading the source from it
    if(file == NULL)
    {
        generateErr(NO_LINE_SPECIFIED,ERR_FILE_NOT_FOUND,path,"");
        return NULL;
    }

    int currentLine = 1;
    tokenNum = 0;
    token *head = NULL;

    token *last = NULL;

    vector<char *> srcDef;
    vector<char *> destDef;

    token tok;

    strcpy(tok.value,"");
    strcpy(tok.fileName,path);

    char chr = fgetc(file);

    while((getType(chr) == SPACE_TOKEN) && (!feof(file))) {
        if (chr == '\n') {
            currentLine++;
        }
        chr = fgetc(file);
    }

    tok.lineNumber = currentLine;
    pushToStr(tok.value, chr);

    int lastType = getType(chr);

    while(!feof(file)){
        chr = fgetc(file);

        if(chr == '\n') {
            if(strlen(tok.value) != 0){
                tok.type = lastType;
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value,"");
            }
            currentLine++;
            tok.lineNumber = currentLine;
            lastType = UNKNOWN_TOKEN;

        }else if(chr == '\t') {
            if (strlen(tok.value) != 0) {
                tok.type = lastType;
                pushToken(tok, &head, &last,&srcDef,&destDef);
                strcpy(tok.value, "");
            }

        }else if(getType(chr) == PUNC_TOKEN){
            if(strlen(tok.value) != 0){
                tok.type = lastType;
                tok.lineNumber = currentLine;
                pushToken(tok,&head,&last,&srcDef,&destDef);
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
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value,"");
            } else{
                lastType = PUNC_TOKEN;
                tok.type = lastType;
                pushToStr(tok.value,chr);
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value,"");
                lastType = UNKNOWN_TOKEN;
            }
        }else if(chr == ' ') {
            if (strlen(tok.value) != 0) {
                tok.type = lastType;
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value, "");
            }
            lastType = UNKNOWN_TOKEN;
        }else if((getType(chr) == OPERATOR_TOKEN) && (lastType == NAME_TOKEN)){
            tok.type = lastType;
            pushToken(tok,&head,&last,&srcDef,&destDef);
            strcpy(tok.value,"");
            lastType = OPERATOR_TOKEN;
            pushToStr(tok.value,chr);
        }else if((getType(chr) == NUM_TOKEN) && (lastType == OPERATOR_TOKEN)) {
            tok.type = lastType;
            pushToken(tok, &head, &last, &srcDef, &destDef);
            strcpy(tok.value, "");
            lastType = NUM_TOKEN;
            pushToStr(tok.value, chr);
        }else if((getType(chr) == NUM_TOKEN) && (lastType == UNKNOWN_TOKEN)) {
            pushToStr(tok.value,chr);
            lastType = NUM_TOKEN;
        }else if((getType(chr) == NAME_TOKEN) && (lastType == PUNC_TOKEN)){
            if (strlen(tok.value) != 0){
                tok.type = lastType;
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value,"");
                lastType = NAME_TOKEN;
                pushToStr(tok.value,chr);
            }
        }else if((getType(chr) == NUM_TOKEN) && (lastType != NAME_TOKEN)) {
            pushToStr(tok.value, chr);
            lastType = getType(chr);

        }else if((lastType == OPERATOR_TOKEN) && (getType(chr) == NAME_TOKEN)){
            if(strlen(tok.value) != 0){
                lastType = OPERATOR_TOKEN;
                tok.lineNumber = currentLine;
                pushToken(tok,&head,&last,&srcDef,&destDef);
                strcpy(tok.value,"");
            }
            lastType = NAME_TOKEN;
            pushToStr(tok.value,chr);
        }else if(getType(chr) == OPERATOR_TOKEN){
            if(lastType != OPERATOR_TOKEN)
            {
                if(strlen(tok.value) != 0)
                {
                    tok.type = lastType;
                    pushToken(tok,&head,&last,&srcDef,&destDef);
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
                    lastType = NAME_TOKEN;
                    pushToStr(tok.value,chr);
                } else{
                    if(strlen(tok.value) != 0){
                        tok.type = lastType;
                        pushToken(tok,&head,&last,&srcDef,&destDef);
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
    return head;
}

void pushToken(token t, token **head, token **last,vector<char *> *srcDef, vector<char *> *destDef)
{
    if(t.type == NAME_TOKEN)
    {
        if(strcmp(t.value,"true") == 0){
            strcpy(t.value,"1");
            t.type = NUM_TOKEN;
        }else if(strcmp(t.value,"false") == 0){
            strcpy(t.value,"0");
            t.type = NUM_TOKEN;
        }else{
            t.type = idOrKeyword(t.value);
        }

    }
    // Check for the defined value and replace the defined value
    for (int i = 0; i < srcDef->size(); ++i) {
        if(strcmp(t.value,(*srcDef)[i]) == 0)
        {
            strcpy(t.value,(*destDef)[i]);
            break;
        }
    }

    if(strlen(t.value) == 0)
        return;

    if(tokenNum == 0)
    {
        (*head) = (token *)malloc(sizeof(token));
        (*last) = (*head);
        (*head)->type = t.type;
        (*head)->lineNumber = t.lineNumber;
        strcpy((*head)->value, t.value);
        (*head)->next = NULL;
    }else{
        (*last)->next = (token *)malloc(sizeof(token));
        (*last) = (*last)->next;
        strcpy((*last)->value, t.value);
        (*last)->lineNumber = t.lineNumber;
        (*last)->type = t.type;
        (*last)->next = NULL;
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
            (chr == '%')
            )
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

    if(chr == '#')
        return PREPRO_TOKEN;
}

void pushToStr(char *str,char chr)
{
    int len = strlen(str);
    str[len] = chr;
    str[len + 1] = 0;
}

token *gotoLastNode(token *head)
{
    token *ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    return ptr;
}

char *stringTokenizer(char *string,char delim,int tokeN)
{
    char *res = (char *)malloc(STR_LEN_LIM * sizeof(char));
    strcpy(res,"");
    int j = 0;
    int k;
    for (int i = 0; i < tokeN; ++i) {
        while (string[j] != delim){
            j++;
            if(j == strlen(string))
                return NULL;
        }
        j++;
    }
    k = j;
    while (string[k] != delim){
        k++;
        if(k == strlen(string))
            break;
    }
    k--;
    for (int l = 0; l < (k - j + 1); ++l) {
        res[l] = string[j + l];
    }
    res[k - j + 1] = 0;

    return res;
}

int idOrKeyword(char *value)
{
    if(strcmp(value,"int") == 0) {
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"float") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"char") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"bool") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"void") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"while") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"if") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"else") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"main") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"NULL") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"min") == 0){
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"max") == 0) {
        return KEYWORD_TOKEN;
    }else if(strcmp(value,"return") == 0) {
        return KEYWORD_TOKEN;
    }else{
        return IDENTIFIER_TOKEN;
    }
}

token *getLastToken(token *start,token *dest)
{
    token *ptr = start;
    while (ptr->next != dest)
        ptr = ptr->next;

    return ptr;
}