
#include "loader.h"
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <stack>
using namespace std;

int main( int argc, char *argv[] )
{
    // Loading phase
    if(argc <= 1){
        printf("Enter the file path to compile : \n");
        char *path = (char *)malloc(1000 * sizeof(char));
        scanf("%s",path);
        loadfromfile(path);
    }else{
        loadfromfile(argv[1]);
    }
    token *ptr = head;

    while (ptr != NULL)
    {
        printf("%d : %s s:%d\n",ptr->lineNumber,ptr->value,ptr->type);
        ptr=ptr->next;
    }

    printf("%d\n",tokenNum);

    // Check whether any error occurred in the phase or not
    if(isAnyErr()){
        return 0;
    }
    return 0;
}