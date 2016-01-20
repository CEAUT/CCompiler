//
// Created by ahmad on 1/16/16.
//

#include "syntax.h"
#include <stack>
#include <string.h>

#include <stdio.h>
#include <string.h>


int Emain;
void Pcheck(token *node,char To){
//    if (Emain==0)
//    {
//        printf("ghabl az main nemishe %d \n",node->lineNumber);
//        return;
//    }
    if ((node->type==4)||(node->type==2))
    {
        if ((node->type==4)&&(node->next->value[0]=='='))
            printf("akhe adad ke nemitoone mosavie chizi bashe ke %d \n",node->next->lineNumber);

        else if (node->next->type==3)
        {
            if ((node->next->next->type==2)||(node->next->next->type==4))
            {
                if(node->next->next->next->value[0]==To)
                    ;
                else
                    printf("Naresid be tahesh %d \n",node->next->next->lineNumber);
            }
            else if((strcmp(node->next->next->value,"NULL")==0)&&(node->next->value[0]=='='))
            {
                if(node->next->next->next->value[0]==To)
                    ;
                else
                    printf("After NULL should be %c %d \n",To,node->next->next->next->lineNumber);

            }
            else if((strcmp(node->next->next->value,"NULL")==0)&&(node->next->value[0]!='=')&&(node->next->type==3))
                printf("NULL ba chizi jam nemishe%d \n",node->next->next->lineNumber);

            else
                printf("after an operator you should use an id or a num %d \n",node->next->lineNumber);
        }







        else if ((node->next->value[0]==To)||(node->next->value[1]==To))
            ;


        else
            printf("Ya bayad operator bezari ya %c %d\n",To,node->next->lineNumber);

        return;

    }
    else
        printf("inja bayas ya moteghayer bashe ya adad %d\n",node->lineNumber);

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
            printf("Bad az if ( yadet rafte %d \n",node->lineNumber);
    }
        ////////////////////////////////////////////////
    else if (strcmp(node->value,"else")==0)
    {
        if(node->next->value[0]=='{')
            Tcheck(node->next, '}');
        else
            printf("bad az else yadet rafte { bezari %d \n",node->lineNumber);
    }
        ////////////////////////////////////////////////
    else if (strcmp(node->value,"int")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                int a=Emain;
                Emain=1;
                Pcheck(node->next->next->next,';');
                Emain=a;

            }
            else if (node->next->next->value[0]==';')
                ;
            else
                printf("inja bayas = ya ; bashe %d \n",node->next->lineNumber);
        }
        else
            printf("bayad motaghayer tarif koni %d \n",node->next->lineNumber);
        return;
    }
        /////////////////////////////////////////////////
    else if (strcmp(node->value,"bool")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                if ((strcmp(node->next->next->next->value,"true")==0)||(strcmp(node->next->next->next->value,"false")==0))
                {
                    if (node->next->next->next->next->value[0]==';')
                        ;
                    else
                        printf("inja bayas ; bezari %d \n",node->next->next->next->lineNumber);
                }
                else
                    printf("bool nemitoone joz true o false bashe %d \n",node->next->next->next->lineNumber);
            }
            else
                printf("inja bayas = bashe %d \n",node->next->lineNumber);
        }
        else
            printf("bayad motaghayer tarif koni %d \n",node->next->lineNumber);
        return;
    }
        /////////////////////////////////////////////////


    else if (strcmp(node->value,"char")==0)
    {
        if (node->next->type==2)
        {
            if (node->next->next->value[0]=='=')
            {
                if (node->next->next->next->type==5)
                {
                    if (node->next->next->next->next->value[0]==';')
                        ;
                    else
                        printf("inja bayas ; bezari %d \n",node->next->next->next->lineNumber);
                }
                else
                    printf("char nemitoone joz 'character' bashe %d \n",node->next->next->next->lineNumber);
            }
            else
                printf("inja bayas = bashe %d \n",node->next->lineNumber);
        }
        else
            printf("bayad motaghayer tarif koni %d \n",node->next->lineNumber);
        return;
    }
        ////////////////////////////////////////////////
    else if (strcmp(node->value,"main")==0)
    {
        if (Emain)
        {
            printf("ye main dashti ke %d \n",node->lineNumber);
            return;
        }
        if (node->next->value[0]=='(')
        {
            if (node->next->next->value[0]==')')
            {  if(node->next->next->next->value[0]=='{')
                {
                    Tcheck(node->next->next->next, '}');
                    Emain=1;
                }
                else
                    printf("bad az main { yadet rafte %d \n",node->next->next->lineNumber);
            }

            else if (strcmp(node->next->next->value,"void")==0)
            {
                if(node->next->next->next->value[0]==')')
                {  if(node->next->next->next->next->value[0]=='{')
                    {
                        Emain=1;
                        Tcheck(node->next->next->next->next, '}');
                    }
                    else
                        printf("bad az main { yadet rafte %d \n",node->next->next->next->lineNumber);}
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
        if (Emain)
        {
            printf("ye main dashti ke %d \n",node->lineNumber);
            return;
        }
        if (strcmp(node->next->value,"main")==0)
        {
            if (node->next->next->value[0]=='(')
            {
                if (node->next->next->next->value[0]==')')
                {  if(node->next->next->next->next->value[0]=='{')
                    {
                        Emain=1;
                        Tcheck(node->next->next->next->next, '}');
                    }
                    else
                        printf("bad az main { yadet rafte %d \n",node->next->next->next->lineNumber);
                }

                else if (strcmp(node->next->next->next->value,"void")==0)
                {
                    if(node->next->next->next->next->value[0]==')')
                    {
                        if(node->next->next->next->next->next->value[0]=='{')
                        {
                            Emain=1;
                            Tcheck(node->next->next->next->next->next, '}');
                        }
                        else
                            printf("bad az main { yadet rafte %d \n",node->next->next->next->next->lineNumber);
                    }
                }

                else
                    printf("bad az ( , ya bayad void bashe ya ) %d \n",node->next->next->lineNumber);

            }
            else
                printf("bad az main ( yadet rafte %d \n",node->next->lineNumber);
        }
        else
            printf("bad az void bayad main bashe %d \n",node->lineNumber);
        return;
    }
        //////////////////////////////////////////////////
    else
        printf("inja bayad ye keyword bashe %d \n",node->lineNumber);
    return;

}

void Tcheck(token * node,char To)
{
    int s=0;
    int v=1;
    while (v)
    {
        if (node==NULL)
            break;
        if((node->value[0]==To)&&(s==0))
        {v=0;
            break;
        }
        if (node->value[0]=='{')
            s++;
        if(node->value[0]=='}')
            s--;
        if((node->value[0]==To)&&(s==0))
        {v=0;
            break;
        }



        else if (node->type==2){
            Pcheck(node, ';');
            while (node->value[0]!=';')
                node=node->next;
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
                    if(node->value[0]=='{')
                        t++;
                    else if(node->value[0]=='}')
                        t--;
                }
            }



            if (strcmp(node->value,"void")==0)
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


            if ((strcmp(node->value,"int")==0)||(strcmp(node->value,"bool")==0)||(strcmp(node->value,"char")==0))
            {
                while(node->value[0]!=';')
                    node=node->next;
            }

        }




        node=node->next;
    }
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