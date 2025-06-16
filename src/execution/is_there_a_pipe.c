#include "minishell.h"

int is_there_a_pipe(t_shell_control_block *shell)
{
  t_token *ptr;

  ptr = shell->tokenized;
  while(ptr->word != NULL)
  {
    if(ptr->type == PIPE)
      return 1;
    ptr++;
  }
  return 0;
}