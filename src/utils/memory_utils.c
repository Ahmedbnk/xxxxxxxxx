#include "minishell.h"

void free_2d_array(char **array)
{
    int i;

    if (!array)
        return;
    
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void free_tokenized_data(t_data *tokenized)
{
    int i;

    if (!tokenized)
        return;
    
    i = 0;
    while (tokenized[i].word)
    {
        free(tokenized[i].word);
        if (tokenized[i].heredoc_file_name)
            free(tokenized[i].heredoc_file_name);
        if (tokenized[i].delimiter)
            free(tokenized[i].delimiter);
        i++;
    }
    free(tokenized);
} 