#include "echo.h"
#include "../headers.h"

void exec_echo(char args[][100])
{
    int i=0;
    while(strlen(args[i])>0)
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}