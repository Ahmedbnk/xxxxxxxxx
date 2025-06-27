#include "minishell.h"

void  check_after_geting_path( char *cmd, char **av, char **path, char **env)
{
	int i;
	char *cmd_with_slash;
	char *cmd_with_its_path;

	if(!path)
		return;
	i = 0;
	cmd_with_slash = ft_strjoin("/", cmd);
	while(path[i])
	{
		cmd_with_its_path = ft_strjoin(path[i] ,cmd_with_slash);
		if(access(cmd_with_its_path, F_OK) == 0)
		{
			if(access(cmd_with_its_path, X_OK) == 0)
			{
				execve(cmd_with_its_path , av, env);
				exit((print_error("%s: %s\n", cmd, strerror(errno)), errno));
			}
			else
				exit((print_error("%s: Permition denied\n", cmd), 126));
		}
		i++;
	}
	exit((print_error("%s: command not found\n", cmd), 127));
}


void  check_the_access(char *cmd, char **av, char **env)
{
  if(opendir(cmd) != NULL)
				exit((print_error("%s: Is a directory\n",cmd), 2));
	if (access(cmd, F_OK) == 0)
	{
		if(access(cmd, X_OK) == 0)
		{
			execve(cmd , av, env);
				exit((print_error("%s: %s\n", cmd, strerror(errno)), errno));
		}
		else
				exit((print_error("%s: Permition denied\n", cmd), 126));
	}
  else if(*cmd == '/'  || *cmd == '.')
	  exit((print_error("%s: No such file or directory \n", cmd), 127));
}


char **get_path()
{
	char	*path;
	char	**splited;

	path = getenv("PATH");
	splited = ft_split(path , ':');
	return splited;
}

void execute_command(t_shell_control_block *shell)
{
	if(!*shell->cmd_and_args)
		return;
	if(!**shell->cmd_and_args)
		exit((print_error("'%s' command not found\n", *shell->cmd_and_args), 127));
    if(opendir(*shell->cmd_and_args) != NULL)
				exit((print_error("%s: Is a directory\n",*shell->cmd_and_args), 2));
	char **path = get_path();
	if (**shell->cmd_and_args == '/' || **shell->cmd_and_args == '.')
		check_the_access(*shell->cmd_and_args, shell->cmd_and_args, shell->env_cpy);
	else
		check_after_geting_path(*shell->cmd_and_args ,shell->cmd_and_args , path , shell->env_cpy);
}

int cmd_size(t_token *tokenz)
{
	int size;

	size = 0;
	while(tokenz)
	{
		if(is_redirection(tokenz->word) || tokenz->type == HEREDOC)
			tokenz = tokenz-> next;
		else if(tokenz->type == WORD)
			size++;
		tokenz = tokenz-> next;
	}
	return size;
}
int is_symbole(int  type)
{
	return (type == REDIR_IN || type == HEREDOC || type == REDIR_OUT ||
			type == REDIR_APPEND);
}
char **get_cmd_and_its_args(t_shell_control_block *sh)
{
    int i;
    sh->cmd_and_args = ft_malloc( (cmd_size(sh->tokenze)+1)* sizeof(t_token ),1);
    i = 0;
	t_token *ptr;
	ptr = sh->tokenze;
	while (ptr) {
			if (is_symbole(ptr->type))
				ptr = ptr->next;
			else if (ptr->type == WORD)
				sh->cmd_and_args[i++] = ft_strdup(ptr->word, 1);
			else
				break;
			ptr = ptr->next;
	}
	sh->cmd_and_args[i] = NULL;
  return sh->cmd_and_args;
}
