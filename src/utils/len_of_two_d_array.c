
#include "minishell.h"

int len_of_two_d_array(char **str)
{
  int counter;
  counter = 0;
  while(str[counter])
  {
    counter++;
  }
  return counter;
}
