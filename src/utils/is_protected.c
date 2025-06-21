#include "minishell.h"

int is_protected(t_shell_control_block *sh, char *str, int index)
{
    char *ptr;
    ptr = sh->porotect_var;
    int i;
    i = 0;
    index += 1;
    int len = ft_strlen(ptr);
    while (i < len)
    {
        if (str[index] != ptr[i])
            return 0;
        index++;
        i++;
    }
    return 1;
}