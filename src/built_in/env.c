#include "minishell.h"

int print_env(char **env)
{
    if(!env || !*env)
        return 0;
    while(*env)
        printf("%s\n", *env++);
    return 0;
}


