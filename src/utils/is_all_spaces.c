#include "minishell.h"

int is_all_spaces(const char *str)
{
  int i;

  i = 0;
  while(str[i])
  {
    if(!is_space(str[i]))
      return 0;
    i++;
  }
  return 1;
}
