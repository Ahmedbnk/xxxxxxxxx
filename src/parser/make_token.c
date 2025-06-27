
#include "minishell.h"

t_type	get_token_type(const char *str)
{
	if (are_they_equal(str, "|"))
		return (PIPE);
	else if (are_they_equal(str, "<"))
		return (REDIR_IN);
	else if (are_they_equal(str, ">"))
		return (REDIR_OUT);
	else if (are_they_equal(str, ">>"))
		return (REDIR_APPEND);
	else if (are_they_equal(str, "<<"))
		return (HEREDOC);
	else
		return (WORD);
}

static int	is_symbole(char *str)
{
	if (!str)
		return (0);
	if (are_they_equal(str, "<")  || are_they_equal(str, ">") )
		return (1);
	if (are_they_equal(str, ">>")  || are_they_equal(str, "<<") )
		return (1);
	return (0);
}


static int	validate_pipe_syntax(char **splitted, int i)
{
	if (i == 0 || !splitted[i + 1])
		return (print_error("syntax error near unexpected str `|'\n"), 1);
	if (is_symbole(splitted[i - 1]) || is_pipe(splitted[i - 1]))
		return (print_error("syntax error near unexpected str `|'\n"), 1);
	return (0);
}

static int	validate_redirection_syntax(char **splitted, int i)
{
	if (!splitted[i + 1])
		return (print_error("syntax error near unexpected str `newline'\n"), 1);
	if (is_pipe(splitted[i + 1]) || is_symbole(splitted[i + 1]))
		return (print_error("syntax error near unexpected str `newline'\n"), 1);
	return (0);
}

int	check_syntax_error(char **splitted)
{
	int	i;
	int	size;

	if (!splitted || !splitted[0])
		return (0);
	size = len_of_two_d_array(splitted);
	i = 0;
	while (i < size)
	{
		if (is_pipe(splitted[i]))
		{
			if (validate_pipe_syntax(splitted, i))
				return (1);
		}
		else if (is_symbole(splitted[i]))
		{
			if (validate_redirection_syntax(splitted, i))
				return (1);
		}
		i++;
	}
	if (is_pipe(splitted[size - 1]) || is_symbole(splitted[size - 1]))
		return (print_error("syntax error near unexpected str `newline'\n"), 1);
	return (0);
}
