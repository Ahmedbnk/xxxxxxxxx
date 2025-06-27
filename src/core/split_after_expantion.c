#include "minishell.h"

void split_after_expantion(t_shell_control_block *sh, char *str, char *old_str)
{
  int i;
  char **ptr;
  i = 0;
  if(!*str || is_there_invalid_expantion(sh, str, old_str))
	  return;
  ptr = customized_split(str);
  while (ptr[i])
  {
    rm_quotes_from_one_str(sh, &ptr[i]);
    add_token_to_lst(&sh->tokenze, new_token(ptr[i], WORD));
    i++;
  }
}
