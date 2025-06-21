#include "minishell.h"

int ft_lstsize(t_list *list)
{
  t_list *ptr;
  int size;
  if(!list)
    return 0;
  size = 0;
  ptr = list;
  while (ptr)
  {
      size ++;
    ptr = ptr->next;
  }
  return size;
}
