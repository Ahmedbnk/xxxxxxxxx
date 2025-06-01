#include "minishell.h"

void print_splitted(char **splitted)
{
  int i;

  i = 0;
  while(splitted[i])
  {
    printf("%s\n", splitted[i]);
    i++;
  }
}
