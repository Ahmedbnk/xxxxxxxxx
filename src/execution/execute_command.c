#include "minishell.h"

// Move these functions to src/execution/path_utils.c
static char **get_path(void)
{
	char	*path;
	char	**splited;

	path = getenv("PATH");
	splited = ft_split(path, ':');
	return splited;
}

static int	how_many_strcut_in_the_array(t_data *arr_of_stracts)
{
	int number_of_structs;

	number_of_structs = 0;
	while(arr_of_stracts->word != NULL)
	{
		number_of_structs++;
		arr_of_stracts++;
	}
	return number_of_structs;
}

// Helper functions for command execution
static void	execute_with_path(char *cmd_with_its_path, char *cmd, char **av, char **env)
{
	if(access(cmd_with_its_path, X_OK) == 0)
	{
		execve(cmd_with_its_path, av, env);
		exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
	}
	else
		exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
}

static void	check_after_geting_bath(char *cmd, char **av, char **path, char **env)
{
	int i;
	char *cmd_with_slash;
	char *cmd_with_its_path;

	i = 0;
	cmd_with_slash = ft_strjoin("/", cmd);
	while(path[i])
	{
		cmd_with_its_path = ft_strjoin(path[i], cmd_with_slash);
		if(access(cmd_with_its_path, F_OK) == 0)
		{
			execute_with_path(cmd_with_its_path, cmd, av, env);
			return;
		}
		i++;
	}
	exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
}

static void	check_the_access(char *cmd, char **av, char **env)
{
	if (access(cmd, F_OK) == 0)
	{
		if(access(cmd, X_OK) == 0)
		{
			execve(cmd, av, env);
			exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
		}
		else
			exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
	}
	else
		exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
}

void execute_command(char *cmd, char **av, char **env)
{
	if(!cmd)
		return;
	char **path = get_path();
	if(*cmd == '/')
		check_the_access(cmd, av, env);
	else
		check_after_geting_bath(cmd, av, path, env);
}

char **get_cmd_and_its_args(t_data *arr_of_stracts)
{
	int i;
	int j;
	char **cmd_and_args;

	cmd_and_args = ft_malloc( how_many_strcut_in_the_array(arr_of_stracts)* sizeof(t_data ) + 1);

	i = 0;
	j = 0;
	while(arr_of_stracts[i].word != NULL)
	{
		if(arr_of_stracts[i].type == REDIR_IN || arr_of_stracts[i].type == HEREDOC || 
		arr_of_stracts[i].type == REDIR_OUT || arr_of_stracts[i].type == REDIR_APPEND)
			i++;
		else if(arr_of_stracts[i].type == WORD)
		{

			cmd_and_args[j] = ft_strdup(arr_of_stracts[i].word);
		j++;
	}
		else
			break;
		i++;
	}
	cmd_and_args[j] = NULL;
	return cmd_and_args;
}
