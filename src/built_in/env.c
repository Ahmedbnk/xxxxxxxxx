#include "minishell.h"

void print_env(char **env)
{
    if(!env || !*env)
        return;
    while(*env)
        printf("%s\n", *env++);
}


