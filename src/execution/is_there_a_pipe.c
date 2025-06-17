#include "minishell.h"

int is_there_a_pipe(t_shell_control_block *shell)
{
  t_token *ptr;

  printf("DEBUG: is_there_a_pipe - checking tokens\n");
  
  if (!shell || !shell->tokenized)
  {
    printf("DEBUG: is_there_a_pipe - no tokens, returning 0\n");
    return 0;
  }
  
  ptr = shell->tokenized;
  while(ptr->word != NULL)
  {
    printf("DEBUG: is_there_a_pipe - token type: %d, word: %s\n", ptr->type, ptr->word);
    if(ptr->type == PIPE)
    {
      printf("DEBUG: is_there_a_pipe - found pipe, returning 1\n");
      return 1;
    }
    ptr++;
  }
  
  printf("DEBUG: is_there_a_pipe - no pipe found, returning 0\n");
  return 0;
}