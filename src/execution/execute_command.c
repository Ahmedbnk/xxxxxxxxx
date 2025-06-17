#include "minishell.h"

void  check_path(char *cmd, char **av, char **path, char **env)
{
	int i;
	char *slash_cmd;
	char *full_path;
	DIR *dir;

	if(!path)
		return;
	i = 0;
	slash_cmd = ft_strjoin("/", cmd);
	while(path[i])
	{
		full_path = ft_strjoin(path[i] ,slash_cmd);
		if(access(full_path, F_OK) == 0)
		{
			dir = opendir(full_path);
			if (dir != NULL)
			{
				closedir(dir);
				exit((print_error("%s: Is a directory\n", cmd), 126));
			}
			else if(access(full_path, X_OK) == 0)
			{
				execve(full_path , av, env);
				exit((print_error("%s: %s\n", cmd, strerror(errno)), errno));
			}
			else
				exit((print_error("%s: Permission denied\n", cmd), 126));
		}
		i++;
	}
	exit((print_error("%s: command not found\n", cmd), 127));
}

void  check_file(char *cmd, char **av, char **env)
{
	DIR *dir;
	
	if (access(cmd, F_OK) == 0)
	{
		dir = opendir(cmd);
		if (dir != NULL)
		{
			closedir(dir);
			exit((print_error("%s: Is a directory\n", cmd), 126));
		}
		else if(access(cmd, X_OK) == 0)
		{
			execve(cmd , av, env);
			exit((print_error("%s: %s\n", cmd, strerror(errno)), errno));
		}
		else
			exit((print_error("%s: Permission denied\n", cmd), 126));
	}
	else
		exit((print_error("%s: No such file or directory\n", cmd), 127));
}

char **get_path()
{
	char	*path;
	char	**split;

	path = getenv("PATH");
	split = ft_split(path , ':');
	return split;
}

void execute_command(t_shell_control_block *shell)
{
	if(!*shell->cmd_and_args)
		return;
	char **path = get_path();
	if(**shell->cmd_and_args == '/')
		check_file(*shell->cmd_and_args, shell->cmd_and_args, shell->env_cpy);
	else
		check_path(*shell->cmd_and_args ,shell->cmd_and_args , path , shell->env_cpy);
}

int count_tokens(t_token *tokens)
{
	int count;

	count = 0;
	while(tokens->word != NULL )
	{
		count++;
		tokens++;
	}
	return count;
}

char **get_cmd_and_its_args(t_shell_control_block *shell)
{
    int i;
    int j;

    shell->cmd_and_args = ft_malloc( (count_tokens(shell->tokenized)+1)* sizeof(char *),1);

    i = 0;
    j = 0;
    while(shell->tokenized[i].word != NULL)
    {
      if(shell->tokenized[i].word[0] == '\0')
        i++;
      else
      {
        if(shell->tokenized[i].type == REDIR_IN || shell->tokenized[i].type == HEREDOC || 
          shell->tokenized[i].type == REDIR_OUT || shell->tokenized[i].type == REDIR_APPEND)
          i++;
        else if(shell->tokenized[i].type == WORD)
          shell->cmd_and_args[j++] = ft_strdup(shell->tokenized[i].word, 1);
        else
          break;
        i++;
      }
    }
	shell->cmd_and_args[j] = NULL;
  return shell->cmd_and_args;
}
