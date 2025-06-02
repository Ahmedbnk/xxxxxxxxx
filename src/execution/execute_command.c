#include "minishell.h"
#include <sys/wait.h>

static char	**get_path(void)
{
	char	*path;
	char	**splited;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	splited = ft_split(path, ':');
	return (splited);
}

static void	check_after_getting_path(char *cmd, char **av, char **path, char **env)
{
	int		i;
	char	*cmd_with_slash;
	char	*cmd_with_its_path;

	if (!path)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		exit(1);
	}
	i = 0;
	cmd_with_slash = ft_strjoin("/", cmd);
	if (!cmd_with_slash)
		exit(1);
	while (path[i])
	{
		cmd_with_its_path = ft_strjoin(path[i], cmd_with_slash);
		if (!cmd_with_its_path)
		{
			free(cmd_with_slash);
			exit(1);
		}
		if (access(cmd_with_its_path, F_OK) == 0)
		{
			if (access(cmd_with_its_path, X_OK) == 0)
			{
				free(cmd_with_slash);
				execve(cmd_with_its_path, av, env);
				free(cmd_with_its_path);
				ft_putstr_fd("minishell: Permission denied\n", 2);
				exit(126);
			}
			free(cmd_with_its_path);
			free(cmd_with_slash);
			ft_putstr_fd("minishell: Permission denied\n", 2);
			exit(126);
		}
		free(cmd_with_its_path);
		i++;
	}
	free(cmd_with_slash);
	ft_putstr_fd("minishell: command not found\n", 2);
	exit(127);
}

static void	check_the_access(char *cmd, char **av, char **env)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, av, env);
			ft_putstr_fd("minishell: Permission denied\n", 2);
			exit(126);
		}
		ft_putstr_fd("minishell: Permission denied\n", 2);
		exit(126);
	}
	ft_putstr_fd("minishell: No such file or directory\n", 2);
	exit(127);
}

void	execute_command(char *cmd, char **av, char **env)
{
	char	**path;

	if (!cmd)
		return ;
	if (*cmd == '/')
		check_the_access(cmd, av, env);
	else
	{
		path = get_path();
		check_after_getting_path(cmd, av, path, env);
	}
}

int	how_many_struct_in_the_array(t_data *arr_of_structs)
{
	int	number_of_structs;

	number_of_structs = 0;
	while (arr_of_structs[number_of_structs].word != NULL)
		number_of_structs++;
	return (number_of_structs);
}

char	**get_cmd_and_its_args(t_data *arr_of_structs)
{
	int		i;
	int		j;
	char	**cmd_and_args;

	cmd_and_args = ft_malloc((how_many_struct_in_the_array(arr_of_structs) + 1) * sizeof(char *));
	if (!cmd_and_args)
		return (NULL);
	i = 0;
	j = 0;
	while (arr_of_structs[i].word != NULL)
	{
		if (arr_of_structs[i].type == REDIR_IN || arr_of_structs[i].type == HEREDOC
			|| arr_of_structs[i].type == REDIR_OUT || arr_of_structs[i].type == REDIR_APPEND)
			i++;
		else if (arr_of_structs[i].type == WORD)
		{
			cmd_and_args[j] = ft_strdup(arr_of_structs[i].word);
			if (!cmd_and_args[j])
			{
				while (j > 0)
					free(cmd_and_args[--j]);
				free(cmd_and_args);
				return (NULL);
			}
			j++;
		}
		else
			break ;
		i++;
	}
	cmd_and_args[j] = NULL;
	return (cmd_and_args);
}
