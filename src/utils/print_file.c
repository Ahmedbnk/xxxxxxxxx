#include "minishell.h"

void print_file(char *str)
{
  char *buffer;

  buffer = read_file(str);
  if(buffer == NULL)
    return;
  printf("%s", buffer);
}
