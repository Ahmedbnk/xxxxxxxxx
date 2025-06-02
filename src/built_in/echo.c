#include "minishell.h"

void echo(char **args)
{
    int flag;
    int i;

    i = 0;
    flag = 0;
    args++;
    if(are_they_equal(*args, "-n"))
    {
        args++;
        flag = 1;
    }
    while(*args)
    {
        printf("%s", *args);
        if(*(args + 1) != NULL)
            printf(" ");
        args++;
    }
    if(!flag)
         printf("\n");
}

