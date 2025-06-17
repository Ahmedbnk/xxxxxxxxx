#include "minishell.h"

// void execute_built_in(char **env, char **cmd_and_args)
int  execute_built_in(t_shell_control_block *shell)
{ 
    if(are_they_equal(*shell->cmd_and_args, "pwd"))
    {
      char *result = pwd(shell->cmd_and_args);
      if (result)
      {
        printf("%s\n", result);
        return 1;
      }
      else
      {
        shell->exit_status = 1;
        return 1;
      }
    }
    else if(are_they_equal(*shell->cmd_and_args, "env"))
      return ((print_env(shell->env_cpy), 1));
    else if(are_they_equal(*shell->cmd_and_args, "echo"))
      return ((echo(shell->cmd_and_args), 1));
    else if(are_they_equal(*shell->cmd_and_args, "cd"))
    {
      cd(shell->env_cpy, shell->cmd_and_args, 0);
      return 1;
    }
    else if(are_they_equal(*shell->cmd_and_args, "export"))
    {
      export(&shell->env_cpy, shell->cmd_and_args +1, shell);
      return 1;
    }
    else if(are_they_equal(*shell->cmd_and_args, "unset"))
    {
      unset(&shell->env_cpy, shell->cmd_and_args +1, shell);
      return 1;
    }
  return 0;
}

