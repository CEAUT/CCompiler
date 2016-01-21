//
// Created by ahmad on 1/16/16.
//

#include "syntax.h"
#include <stack>
#include <string.h>

#include <stdio.h>
#include <string.h>



void Pcheck_m(token * node,char To)
{
    while((node->value[0]!=To)&&(node!=NULL))
    {
        if(node->value[0]=='(')
        {
            if (node->next->value[0]=='(')
                node=node->next;
            else if(node->next->type==2)
                node=node->next;
            else if(node->next->type==4)
                node=node->next;
            else
            {
                generateErr(node->next->lineNumber,ERR_AFTER_PARENTHESIS_OPEN,"",node->fileName);
                return;
            }
        }
        else if(node->value[0]==')')
        {

            if (node->next->value[0]==')')
                node=node->next;
            else if(node->next->type==3)
                node=node->next;
            else if (node->next->value[0]==To)
                node=node->next;
            else
            {
                generateErr(node->next->lineNumber,ERR_AFTER_PARENTHESIS_CLOSE,"",node->fileName);
                return;
            }
        }
        else if ((node->type==4)||(node->type==2))
        {
            if (node->next->type==3)
                node=node->next;
            else if(node->next->value[0]==To)
                node=node->next;
            else if(node->next->value[0]==')')
                node=node->next;
            else
            {
                printf("bad az adad ya moteghayer bayad operator bashe %d \n",node->next->lineNumber);
                return;
            }
        }
        else if (node->type==3)
        {
            if (node->next->value[0]=='(')
                node=node->next;
            else if ((node->next->type==4)||(node->next->type==2))
                node=node->next;
            else
            {
                generateErr(node->next->lineNumber,ERR_AFTER_OPR,"",node->next->fileName);
                return;
            }
        }
        else if(node->value[0]==To)
            return;

    }
}

void Pcheck(token *node,char To){
    //a='a';
    if ((node->type==4)||(node->type==2))
    {
        if (node->next!=NULL)
        {
            if (node->next->value[0]=='=')
            {
                if (node->next->next!=NULL)
                if(node->next->next->type==5)
                {
                    if(node->next->next->next->value[0]==To)
                        ;
                    else{
                        char str[2] = " ";
                        str[0] = To;
                        generateErr(node->next->lineNumber,ERR_REPLACE,str,node->next->fileName);
                    }

                }
            }
        }
    }


    //a=true ;
    if ((node->type==4)||(node->type==2))
    {
        if (node->next!=NULL)
        {
            if (node->next->value[0]=='=')
            {
                if (node->next->next!=NULL)
                if((strcmp(node->next->next->value,"true"))||(strcmp(node->next->next->value,"false")))
                {
                    if(node->next->next->next->value[0]==To)
                        ;
                    else {
                        char str[2] = " ";
                        str[0] = To;
                        generateErr(node->next->lineNumber, ERR_REPLACE, str, node->next->fileName);
                    }
                }
            }
        }
    }

    ////ta inja check shod




    if ((node->type==4)||(node->type==2))
    {
        if ((node->type==4)&&(node->next->value[0]=='='))
            generateErr(node->next->lineNumber,ERR_ASSIGN_TO_NUMBER,"",node->next->fileName);
        if (node->next!=NULL)
        {
            if(node->next->next!=NULL)
            {
                if((node->next->value[0]=='=')&&(strcmp(node->next->next->value,"NULL")==0))
                {
                    if(node->next->next->next!=NULL)
                    {
                        if(node->next->next->next->value[0]==To)
                            ;
                        else {
                            char str[2] = " ";
                            str[0] = To;
                            generateErr(node->next->next->next->lineNumber,ERR_AFTER_NULL,str,node->next->next->next->fileName);
                        }
                    }
                }
                else if((node->next->type==3)&&(node->next->value[0]!='=')&&(strcmp(node->next->next->value,"NULL")==0))
                    generateErr(node->next->next->lineNumber,ERR_NULL_NOT_OPERATABLE,"",node->next->next->fileName);
            }
        }
        /////////////////////

        if(node->next->value[0]=='(')
            Pcheck_m(node->next,To);

        else if (node->next->type==3)
        {
            Pcheck_m(node->next,To);
        }


        else if (node->next->value[0]==To)
            ;

        else {
            char str[2] = " ";
            str[0] = To;
            generateErr(node->next->lineNumber,ERR_OPERATOR_OR_,str,node->next->fileName);
        }
        return;

    }
    else if(node->value[0]=='(')
        Pcheck_m(node,To);

    else
        generateErr(node->lineNumber,ERR_ID_OR_NUM,"",node->fileName);

}


void Keycheck(token * node)
{
    ////////////////////////////////////////////////
    if (strcmp(node->value,"if")==0)
    {
        if(node->next->value[0]=='(')
        {
            Pcheck(node->next->next, ')');
            while(node->value[0]!='{')
                node=node->next;
            //node->value======='{'
            Tcheck(node, '}');

        }
        else
            generateErr(node->lineNumber,ERR_AFTER_IF_OR_WHILE_PARENTHESIS_OPEN,"IF",node->fileName);
    }

        //////////////////////////////////////////////////


    else if (strcmp(node->value,"while")==0)
    {
        if(node->next->value[0]=='(')
        {
            Pcheck(node->next->next, ')');
            while(node->value[0]!='{')
                node=node->next;
            //node->value======='{'
            Tcheck(node, '}');

        }

        else
            generateErr(node->lineNumber,ERR_AFTER_IF_OR_WHILE_PARENTHESIS_OPEN,"WHILE",node->fileName);
    }




        ////////////////////////////////////////////////
    else if (strcmp(node->value,"else")==0)
    {
        if(node->next->value[0]=='{')
            Tcheck(node->next, '}');
        else
            generateErr(node->lineNumber,ERR_AFTER_ELSE_BRACE_OPEN,"",node->fileName);
    }
        ////////////////////////////////////////////////
    else if (strcmp(node->value,"int")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                Pcheck(node->next->next->next,';');
            }
            else if (node->next->next->value[0]==';')
                ;
            else
                generateErr(node->next->lineNumber,ERR_ASSIGN_OR_SEMICOLON,"",node->next->fileName);
        }
        else
            generateErr(node->next->lineNumber,ERR_SHOULD_DECLARE_ID,"",node->next->fileName);
        return;
    }
        /////////////////////////////////////////////////
    else if (strcmp(node->value,"bool")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                if ((strcmp(node->next->next->next->value,"true")==0)||(strcmp(node->next->next->next->value,"false")==0)||(node->next->next->next->type==2))
                {
                    if (node->next->next->next->next->value[0]==';')
                        ;
                    else
                        generateErr(node->next->next->next->lineNumber,ERR_SEMICOLON_NEEDED,"",node->next->next->next->fileName);
                }
                else
                    generateErr(node->next->next->next->lineNumber,ERR_BOOL_TYPE_MISMATCH,"",node->next->next->next->fileName);
            }
            else
                generateErr(node->next->lineNumber,ERR_ASSIGNMENT_EXPECTED,"",node->next->fileName);
        }
        else
            generateErr(node->next->lineNumber,ERR_SHOULD_DECLARE_ID,"",node->next->fileName);
        return;
    }
        /////////////////////////////////////////////////


    else if (strcmp(node->value,"char")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                if ((node->next->next->next->type==5)||(node->next->next->next->type==2))
                {
                    if (node->next->next->next->next->value[0]==';')
                        ;
                    else
                        generateErr(node->next->next->next->lineNumber,ERR_SEMICOLON_NEEDED,"",node->next->next->next->fileName);
                }
                else
                    generateErr(node->next->next->next->lineNumber,ERR_CHAR_TYPE_MISMATCH,"",node->next->next->next->fileName);
            }
            else
                generateErr(node->next->lineNumber,ERR_ASSIGNMENT_EXPECTED,"",node->next->fileName);
        }
        else
            generateErr(node->next->lineNumber,ERR_SHOULD_DECLARE_ID,"",node->next->fileName);
        return;
    }
        ////////////////////////////////////////////////
    else if (strcmp(node->value,"main")==0)
    {
        if (node->next->value[0]=='(')
        {
            if (node->next->next->value[0]==')')
            {  if(node->next->next->next->value[0]=='{')
                {
                    Tcheck(node->next->next->next, '}');

                }
                else
                    printf("bad az main { yadet rafte %d \n",node->next->next->lineNumber);
            }

            else if (strcmp(node->next->next->value,"void")==0)
            {
                if(node->next->next->next->value[0]==')') {
                    if(node->next->next->next->next->value[0]=='{')
                    {
                        Tcheck(node->next->next->next->next, '}');
                    }
                    else
                        printf("bad az main { yadet rafte %d \n",node->next->next->next->lineNumber);
                }

            }

            else
                printf("bad az ( , ya bayad void bashe ya ) %d \n",node->next->lineNumber);

        }
        else
            printf("bad az main ( yadet rafte %d \n",node->lineNumber);

        return;
    }
        /////////////////////////////////////////////////
    else if (strcmp(node->value,"void")==0)
    {
        if (strcmp(node->next->value,"main")==0)
        {
            if (node->next->next->value[0]=='(')
            {
                if (node->next->next->next->value[0]==')')
                {  if(node->next->next->next->next->value[0]=='{')
                    {
                        Tcheck(node->next->next->next->next, '}');
                    }
                    else
                        generateErr(node->next->next->next->lineNumber,ERR_MAIN_SCOPE_START,"",node->next->next->next->fileName);
                }

                else if (strcmp(node->next->next->next->value,"void")==0)
                {
                    if(node->next->next->next->next->value[0]==')')
                    {
                        if(node->next->next->next->next->next->value[0]=='{')
                        {
                            Tcheck(node->next->next->next->next->next, '}');
                        }
                        else
                            generateErr(node->next->next->next->lineNumber,ERR_MAIN_SCOPE_START,"",node->next->next->next->fileName);
                    }
                }

                else
                    generateErr(node->next->next->lineNumber,ERR_MAIN_PARENTHESIS,"",node->next->next->fileName);

            }
            else
                generateErr(node->next->next->lineNumber,ERR_MAIN_PARENTHESIS,"",node->next->next->fileName);
        }
        else
            generateErr(node->lineNumber,ERR_MAIN_AFTER_VOID,"",node->fileName);
        return;
    }

        //////////////////////////////////////////////////

    else if (strcmp(node->value,"return")==0)
    {
        if (node->next->value[0]==';')
            ;
        else
            generateErr(node->lineNumber,ERR_SEMICOLON_AFTER_RETURN,"",node->fileName);
    }

        /////////////////////////////////////////////////

    else
        generateErr(node->lineNumber,ERR_KEYWORD_EXPECTED,"",node->fileName);
    return;

}

token * Tcheck(token * node,char To)
{
    int s=0;
    int v=1;
    while (v!=0)
    {
        if (node==NULL)
            break;
        if((node->value[0]==To)&&(s==0))
        {
            v=0;
            return node;
        }
        if (node->value[0]=='{')
            s++;
        if(node->value[0]=='}')
            s--;
        if((node->value[0]==To)&&(s==0))
        {
            v=0;
            return node;

        }

        else if ((node->type==2)&&(v!=0)){
            if (node->next->value[0]=='=')
                Pcheck(node->next->next, ';');
            else
                Pcheck(node, ';');

            int x=0;
            while(node->value[0]!=';')
            {
                if(node->next!=NULL) {
                    node=node->next;
                }
                if(node->next==NULL) {
                    x=1;
                    break;
                }

            }
            if (x==1)
                return node;



        }
        else if(node->type==1)
        {
            int t=1;
            Keycheck(node);
            if (strcmp(node->value,"if")==0)
            {
                while(node->value[0]!='{')
                    node=node->next;
                while(t!=0)
                {
                    node=node->next;
                    if(node->value[0]=='{')
                        t++;
                    else if(node->value[0]=='}')
                        t--;
                }
            }

            if (strcmp(node->value,"while")==0)
            {
                while(node->value[0]!='{')
                    node=node->next;
                while(t!=0)
                {
                    node=node->next;
                    if(node->value[0]=='{')
                        t++;
                    else if(node->value[0]=='}')
                        t--;
                }
            }


            if (strcmp(node->value,"else")==0)
            {
                node=node->next;
                while(t!=0)
                {
                    node=node->next;
                    if(node->value[0]=='{')
                        t++;
                    else if(node->value[0]=='}')
                        t--;
                }
            }

            if (strcmp(node->value,"main")==0)
            {
                while(node->value[0]!='{')
                    node=node->next;
                while(t!=0)
                {
                    node=node->next;
                    if (node!=NULL)
                    {if(node->value[0]=='{')
                            t++;
                        else if(node->value[0]=='}')
                            t--;}
                    else return NULL;
                }
            }



            if (strcmp(node->value,"void")==0)
            {
                while(node->value[0]!='{')
                    node=node->next;
                while(t!=0)
                {
                    node=node->next;
                    if (node!=NULL)
                    {if(node->value[0]=='{')
                            t++;
                        else if(node->value[0]=='}')
                            t--;}
                    else return NULL;
                }
            }


            if ((strcmp(node->value,"int")==0)||(strcmp(node->value,"bool")==0)||(strcmp(node->value,"char")==0))
            {
                int x=0;
                while(node->value[0]!=';')
                {
                    if(node->next!=NULL)
                    {   node=node->next;
                    }
                    if(node->next==NULL)
                    {   x=1;
                        break;}

                }
                if (x==1)
                    return node;
            }
            if (strcmp(node->value,"return")==0)
            {
                int x=0;
                while(node->value[0]!=';')
                {
                    if(node->next!=NULL)
                    {   node=node->next;
                    }
                    if(node->next==NULL)
                    {   x=1;
                        break;}
                }
            }

        }

        if(v!=0)
            node=node->next;
    }
    return  node;

}


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