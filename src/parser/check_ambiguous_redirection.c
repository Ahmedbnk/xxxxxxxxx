#include "minishell.h"

int check_ambiguous_redirection(char *filename)
{
    if (!filename)
        return 1;
    
    if (filename[0] == '\0')
        return 1;
    
    if (ft_strlen(filename) == 0)
        return 1;
    
    return 0;
} 