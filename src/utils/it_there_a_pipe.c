#include "minishell.h"

int is_there_a_pipe(t_shell_control_block *shell)
{
  t_token *ptr;

  ptr = shell->tokenze;
  while(ptr)
  {
    if(ptr->type == PIPE)
      return 1;
	ptr = ptr->next;
  }
  return 0;
}
