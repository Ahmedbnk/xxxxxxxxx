#include "minishell.h"

static void	unused_vars(int ac, char **av)
{
	(void)ac;
	(void)av;
}

static char	*ft_readline(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell$ ";
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

static void	expand_input(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (are_they_equal(input[i], "<<"))
			i++;
		else
			input[i] = expand_if_possible(input[i], 0);
		i++;
	}
}

static void	parse_and_expand(char *line, char ***splitted, char **env)
{
	*splitted = customized_split(line);
	*splitted = split_with_operators(*splitted);
	expand_input(*splitted);
	t_data	*tokenized;

	tokenized = make_token(*splitted);
	if (tokenized)
	{
		remove_quotes_from_args(*splitted);
		parse_tokenized(tokenized, env);
	}
}

static int	execute_external_command(char **splitted, char **env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		handle_signals_in_child();
		execute_command(splitted[0], splitted, env);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static int	process_command(char **splitted, char **env)
{
	if (!splitted)
		return (0);
	if (is_builtin(splitted[0]))
		return (execute_builtin(splitted, env));
	return (execute_external_command(splitted, env));
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**splitted;
	int		exit_status;

	unused_vars(ac, av);
	handle_signals();
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		if (*line)
		{
			splitted = NULL;
			parse_and_expand(line, &splitted, env);
			exit_status = process_command(splitted, env);
			if (splitted)
			{
				int i = 0;
				while (splitted[i])
					free(splitted[i++]);
				free(splitted);
			}
		}
		free(line);
	}
	return (exit_status);
}
