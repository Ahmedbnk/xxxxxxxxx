#include "minishell.h"

int check_ambiguous_redirection(char *filename)
{
    int i;
    
    if (!filename)
        return 0;
    
    i = 0;
    while (filename[i])
    {
        if (filename[i] == ' ' || filename[i] == '\t' || filename[i] == '\n')
            return 1; // Ambiguous redirection detected
        i++;
    }
    return 0; // No ambiguous redirection
} 