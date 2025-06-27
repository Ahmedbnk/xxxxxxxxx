#include "minishell.h"

int parse_line(t_shell_control_block *sh)
{
  sh->porotect_var = generate_random_name();
  sh->splitted = customized_split(sh->line);
  sh->splitted = split_with_operators(sh->splitted);
  if(check_syntax_error(sh->splitted))
  {
	  free(sh->line);
	  return 1;
  }
  get_files_name(sh);
  expand_and_split(sh);
  return 0;
}
