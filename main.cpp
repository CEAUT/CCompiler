
#include "loader.h"
#include "limits.h"
#include "syntax.h"
#include "identifierTable.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <stack>
#include <malloc.h>
#include "irgen.h"

using namespace std;


int main( int argc, char *argv[] )
{
    token *head;
    // Loading phase

    if(argc <= 1){
        printf("Enter the file path to compile : \n");
        char *path = (char *)malloc(1000 * sizeof(char));
        scanf("%s",path);
        head = loadfromfile(path);
    }else{
        head = loadfromfile(argv[1]);
    }

    token *ptr = head;

    while (ptr != NULL)
    {
        printf("%d : %s s:%d\n",ptr->lineNumber,ptr->value,ptr->type);
        ptr=ptr->next;
    }

    checkPunc(head);

    // Check whether any error occurred in the phase or not
    if(isAnyErr()){
        return 0;
    }

    expressionCal(head,getLastToken(head,ptr));
    return 0;
}