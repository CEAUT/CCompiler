
#include "loader.h"
#include "limits.h"
#include "syntax.h"
#include "identifierTable.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <stack>
#include <malloc.h>
#include <iostream>
#include "irgen.h"

using namespace std;


int main( int argc, char *argv[] )
{
    FILE *pre = fopen("/home/ahmad/ClionProjects/export.c","w");


    token *head;
    // Loading phase

    if(argc <= 1){
        printf("Enter the file path to compile : \n");

        char *path = (char *)malloc(1000 * sizeof(char));
        scanf("%s",path);
        preProces(pre,argv[1]);
    }else{
        preProces(pre,argv[1]);
    }

    fclose(pre);

    printf("Pre process step completed.\n");


    head = loadfromfile("/home/ahmad/ClionProjects/export.c");
    token *ptr = head;
/*
    while (ptr != NULL)
    {
        printf("%d : %s s:%d\n",ptr->lineNumber,ptr->value,ptr->type);
        ptr=ptr->next;
    }
*/
    printf("Preprocess completed.\n");
    checkPunc(head);

    Tcheck(head,'}');

    // Check whether any error occurred in the phase or not
    if(isAnyErr()){
        generateIR(head,"/home/ahmad/ClionProjects/file.ir");
        return 0;
    }
    //Keycheck(head);


    //statement(head);
    //mainAnalyser(head);

    return 0;
}