#include "minishell.h"

// void execute_built_in(char **env, char **cmd_and_args)
int execute_built_in(t_shell_control_block *shell)
{ 
    int status = 0;

    if(are_they_equal(*shell->cmd_and_args, "pwd"))
      status = (printf("%s\n", pwd()) < 0) ? 1 : 0;
    else if(are_they_equal(*shell->cmd_and_args, "env"))
      status = (print_env(shell->env_cpy), 0);
    else if(are_they_equal(*shell->cmd_and_args, "echo"))
      status = (echo(shell->cmd_and_args), 0);
    else if(are_they_equal(*shell->cmd_and_args, "cd"))
      status = (cd(shell->env_cpy, shell->cmd_and_args), 0);
    else if(are_they_equal(*shell->cmd_and_args, "export"))
      status = (export(&shell->env_cpy, shell->cmd_and_args + 1), 0);
    else if(are_they_equal(*shell->cmd_and_args, "unset"))
      status = (unset(&shell->env_cpy, shell->cmd_and_args + 1), 0);
    else
      return 0;

    g_shell->last_exit_status = status;
    return 1;
}

