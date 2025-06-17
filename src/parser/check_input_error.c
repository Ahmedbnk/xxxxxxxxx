#include "minishell.h"

int	check_unclosed_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == single_q && double_quote == 0)
			single_quote = !single_quote;
		else if (str[i] == double_q && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	check_invalid_redirections(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		// Check for more than 2 consecutive > or <
		if (str[i] == '>' && !is_between_quotes(str, i))
		{
			int count = 0;
			while (str[i] == '>' && !is_between_quotes(str, i))
			{
				count++;
				i++;
			}
			if (count > 2)
				return (1);
		}
		else if (str[i] == '<' && !is_between_quotes(str, i))
		{
			int count = 0;
			while (str[i] == '<' && !is_between_quotes(str, i))
			{
				count++;
				i++;
			}
			if (count > 2)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	check_consecutive_operators(char **splitted)
{
	int	i;
	int	j;
	int	consecutive_ops;
	char	last_op;

	i = 0;
	while (splitted[i])
	{
		j = 0;
		consecutive_ops = 0;
		last_op = 0;
		while (splitted[i][j])
		{
			if (!is_between_quotes(splitted[i], j) && 
				(splitted[i][j] == '>' || splitted[i][j] == '<' || splitted[i][j] == '|'))
			{
				if (last_op == 0)
				{
					last_op = splitted[i][j];
					consecutive_ops = 1;
				}
				else if (splitted[i][j] == last_op)
				{
					consecutive_ops++;
					if (consecutive_ops > 2)
						return (1);
				}
				else
				{
					// Different operators - check if valid combination
					if ((last_op == '>' && splitted[i][j] == '<') ||
						(last_op == '<' && splitted[i][j] == '>'))
						return (1);
					last_op = splitted[i][j];
					consecutive_ops = 1;
				}
			}
			else
			{
				last_op = 0;
				consecutive_ops = 0;
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_error(t_shell_control_block *shell)
{
	char *str;

	str = shell->line;
	if(!str || !*str)
		return 1;
	if (check_unclosed_quotes(str))
	{
		print_error("unclosed quote\n");
		shell->exit_status = 2;
		return 1;
	}
	if (check_invalid_redirections(str))
	{
		print_error("syntax error near unexpected token `>>'\n");
		shell->exit_status = 2;
		return 1;
	}
	return (0);
}

int	check_token_syntax(t_shell_control_block *shell)
{
	int	i;
	int	consecutive_redirs;

	i = 0;
	consecutive_redirs = 0;
	while (shell->tokenized[i].word != NULL)
	{
		if (shell->tokenized[i].type == REDIR_IN || 
			shell->tokenized[i].type == REDIR_OUT || 
			shell->tokenized[i].type == REDIR_APPEND || 
			shell->tokenized[i].type == HEREDOC)
		{
			consecutive_redirs++;
			if (consecutive_redirs > 1)
			{
				print_error("syntax error near unexpected token `%s'\n", shell->tokenized[i].word);
				shell->exit_status = 2;
				return (1);
			}
		}
		else if (shell->tokenized[i].type == WORD)
		{
			consecutive_redirs = 0;
		}
		else if (shell->tokenized[i].type == PIPE)
		{
			consecutive_redirs = 0;
		}
		i++;
	}
	return (0);
}

int	check_syntax_after_split(t_shell_control_block *shell)
{
	if (check_consecutive_operators(shell->splitted))
	{
		print_error("syntax error near unexpected token `>>'\n");
		shell->exit_status = 2;
		return 1;
	}
	return (0);
}
