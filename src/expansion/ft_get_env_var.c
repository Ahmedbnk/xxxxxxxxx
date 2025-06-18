#include "minishell.h"

void get_start_and_end(char *str, int *start, int *end)
{
  int i;
  i = 0;
  while(str[i])
  {
    if(str[i] == '=')
      *start = i+1;
    i++;
  }
  *end = i;
}

int is_quote(char c)
{
  return (c == single_q || c == double_q);
}
int count_number_of_qute(char *str)
{
  int number_of_qute;
  number_of_qute = 0;

  while(*str)
  {
    if(is_quote(*str))
      number_of_qute++;
    str++;
  }
  return number_of_qute;
}

char *protect_str(char *str)
{
  char *new_str;
  new_str = ft_malloc(ft_strlen(str) +count_number_of_qute(str)+1, 1);
  int i;
  i = 0;
  while (*str)
  {
    if(is_quote(*str))
    {
      new_str[i++] = PROTECT;
      new_str[i++] = *str;
      new_str[i++] = PROTECT;
    }
    else
      new_str[i++] = *str;
    str++;
  }
  new_str[i] = '\0';
  return new_str;
}

char *get_env_var(t_shell_control_block *shell , t_expand data)
{
  char **ptr = shell->env_cpy;
  char *value;
  int start;
  int end;

  int i ;
  i = 0;
  while(ptr[i])
  {
    if(compare_env_var(ptr[i], (data.to_expand)+1))
    {
      get_start_and_end(ptr[i], &start, &end);
      value = ft_substr(ptr[i], start, (end-start));
      value = protect_str(value);
      return value;
    }
    i++;
  }
  return NULL;
}
