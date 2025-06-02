#include "minishell.h"

static char *get_delimiter(char *str)
{
    char *delimiter;
    int len;

    if (!str)
        return (NULL);
    if (*str == '$' && (*(str + 1) == single_q || *(str + 1) == double_q))
        str++;
    len = 0;
    while (str[len] && !is_space(str[len]))
        len++;
    delimiter = ft_substr(str, 0, len);
    if (!delimiter)
        return (NULL);
    remove_quotes(&delimiter);
    return (delimiter);
}

void handle_heredoc(char *str, char **in_file_name)
{
    int fd;
    char *buffer;
    char *delimiter;
    char *tmp;

    if (!str || !in_file_name)
        return;
    delimiter = get_delimiter(str);
    if (!delimiter)
        return;
    *in_file_name = ft_strjoin("/tmp/", generate_random_name());
    if (!*in_file_name)
    {
        free(delimiter);
        return;
    }
    fd = open(*in_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1)
    {
        free(delimiter);
        free(*in_file_name);
        *in_file_name = NULL;
        return;
    }
    while (1)
    {
        buffer = readline("> ");
        if (!buffer)
        {
            ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            break;
        }
        if (are_they_equal(delimiter, buffer))
        {
            free(buffer);
            break;
        }
        tmp = expand_if_possible(buffer, 1);
        free(buffer);
        if (!tmp)
        {
            ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `", 2);
            ft_putstr_fd(delimiter, 2);
            ft_putstr_fd("')\n", 2);
            break;
        }
        write(fd, tmp, ft_strlen(tmp));
        write(fd, "\n", 1);
        free(tmp);
    }
    free(delimiter);
    close(fd);
}
