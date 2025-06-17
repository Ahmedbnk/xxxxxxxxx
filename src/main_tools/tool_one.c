#include "minishell.h"

void ft_init_shell_block(t_shell_control_block *shell, int ac, char **av)
{
  (void) ac;
  (void) av;
  shell->env_cpy = NULL;
  shell->line = NULL;
  shell->splitted = NULL;
  shell->tokenized = NULL;
  shell->cmd_and_args = NULL;
  shell->expand_arr = NULL;
  shell->exit_status = 0;
}

char *ft_readline(t_shell_control_block *shell)
{
  shell->line = readline("\001\033[1;31m\002Flash-->\001\033[0m\002");
  if (shell->line && *shell->line)
    add_history(shell->line);
  if (shell->line == NULL)
  {
    free_memory(get_garbage_pointer(1));
    free_memory(get_garbage_pointer(0));
    exit(0);
    return NULL;
  }
  if (check_error(shell))
    return NULL;
  return shell->line;
}

