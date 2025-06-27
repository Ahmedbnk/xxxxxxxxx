#include "minishell.h"

void expand_and_split(t_shell_control_block *sh)
{
  int i;
  i = 0;

  sh->tokenze = NULL;
  while (sh->splitted[i])
  {
    if(are_they_equal(sh->splitted[i], "<<"))
    {
        add_token_to_lst(&sh->tokenze, new_token(sh->splitted[i], get_token_type(sh->splitted[i])));
		i++;
        add_token_to_lst(&sh->tokenze, new_token(sh->splitted[i], get_token_type(sh->splitted[i])));
	}
    else
		expand_and_split_helper(sh, i);
	i++;
  }
}
