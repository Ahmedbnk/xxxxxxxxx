#include "minishell.h"

static int count_command_args(t_data *arr_of_stracts)
{
    int count;

    count = 0;
    while (arr_of_stracts->word != NULL)
    {
        if (arr_of_stracts->type == WORD)
            count++;
        arr_of_stracts++;
    }
    return (count);
}

static int is_redirection_token(t_token type)
{
    return (type == REDIR_IN || type == HEREDOC || 
            type == REDIR_OUT || type == REDIR_APPEND);
}

char **get_cmd_and_its_args(t_data *arr_of_stracts)
{
    int i;
    int j;
    char **cmd_and_args;

    cmd_and_args = ft_malloc((count_command_args(arr_of_stracts) + 1) * sizeof(char *));
    if (!cmd_and_args)
        return (NULL);

    i = 0;
    j = 0;
    while (arr_of_stracts[i].word != NULL)
    {
        if (is_redirection_token(arr_of_stracts[i].type))
            i++;
        else if (arr_of_stracts[i].type == WORD)
        {
            cmd_and_args[j] = ft_strdup(arr_of_stracts[i].word);
            if (!cmd_and_args[j])
            {
                free_2d_array(cmd_and_args);
                return (NULL);
            }
            j++;
        }
        else
            break;
        i++;
    }
    cmd_and_args[j] = NULL;
    return (cmd_and_args);
} 