#include "minishell.h"

char *remove_dollar_if_quotes_after_it(char *str)
{
  char *returned_string = ft_malloc(ft_strlen(str)+1, 1);
  int i = 0;
  int j = 0;
  while(str[i])
  {
    if(str[i] == '$' && !is_between_quotes(str, i) && (str[i + 1] == single_q || str[i + 1] == double_q) )
      i++;
    else
      returned_string[j++] = str[i++];
  }
  returned_string[j] = '\0';
  // remove_quotes(&returned_string);
  return returned_string;
}

char **handle_dollar_with_quotes(char **splitted)
{
  int i = 0;
  while(splitted[i])
  {
    if(are_they_equal(splitted[i], "<<"))
      i++;
    else
      splitted[i] = remove_dollar_if_quotes_after_it(splitted[i]);
    i++;
  }
  return splitted;
}
