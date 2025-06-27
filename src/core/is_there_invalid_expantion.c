#include "minishell.h"

int is_there_invalid_expantion(t_shell_control_block *sh, char *str, char *old_str)
{
  if(!is_it_valid_dollar(old_str))
  {
    rm_quotes_from_one_str(sh, &str);
    add_token_to_lst(&sh->tokenze, new_token(str, WORD));
    return 1;
  }
  return 0;
}
