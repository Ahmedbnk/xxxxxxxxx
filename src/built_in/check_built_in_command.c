#include "minishell.h"

// void execute_built_in(char **env, char **cmd_and_args)
int  execute_built_in(t_shell_control_block *shell)
{ 
    if(are_they_equal(*shell->cmd_and_args, "pwd"))
      return ((printf("%s\n",pwd()), 1));
    else if(are_they_equal(*shell->cmd_and_args, "env"))
      return ((print_env(shell->env_cpy), 1));
    else if(are_they_equal(*shell->cmd_and_args, "echo"))
      return ((echo(shell->cmd_and_args), 1));
    else if(are_they_equal(*shell->cmd_and_args, "cd"))
      return ((cd(shell->env_cpy, shell->cmd_and_args, 0), 1));
    else if(are_they_equal(*shell->cmd_and_args, "export"))
    {
      export(&shell->env_cpy, shell->cmd_and_args +1);
      return 1;
    }
    else if(are_they_equal(*shell->cmd_and_args, "unset"))
      return((unset(&shell->env_cpy, shell->cmd_and_args +1),1));
  return 0;
}

