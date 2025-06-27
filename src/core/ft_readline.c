#include "minishell.h"

char *ft_readline(t_shell_control_block *sh)
{
  sh->line = readline("\001\033[1;31m\002Flash:\001\033[0m\002");
  if (sh->line && *sh->line)

    add_history(sh->line);
  if (sh->line == NULL)
  {
    free(sh->line);
    free_memory(get_garbage_pointer(1));
    free_memory(get_garbage_pointer(0));
    exit(0);
  }
  if (check_error(sh))
    return((free(sh->line), NULL));
  return sh->line;
}
