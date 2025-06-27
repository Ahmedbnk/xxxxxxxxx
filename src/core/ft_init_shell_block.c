#include "minishell.h"

void ft_init_shell_block(t_shell_control_block *sh, int ac, char **av)
{
  (void) ac;
  (void) av;
  sh->env_cpy = NULL;
  sh->line = NULL;
  sh->splitted = NULL;
  sh->file_name_lst = NULL;
  sh->tokenze = NULL;
  sh->cmd_and_args= NULL;
  sh->env_of_export = NULL;
  sh->exit_status= 0;
}
