
#include "minishell.h"

t_token	get_token_type(const char *str)
{
	if (are_they_equal(str, "|"))
		return (PIPE);
	else if (are_they_equal(str, "<"))
		return (REDIR_IN);
	else if (are_they_equal(str, ">"))
		return (REDIR_OUT);
	else if (are_they_equal(str, ">>"))
		return (REDIR_APPEND);
	else if (are_they_equal(str, "<<"))
		return (HEREDOC);
	else
		return (WORD);
}

void fill_the_list(t_data * list, char **arr)
{
  int i;
  i = 0;
  while(arr[i])
  {
    list[i].type = get_token_type(arr[i]);
    list[i].word = ft_strdup(arr[i]);
    i++;
  }
    list[i].word = ft_strdup(arr[i]);
}


int check_syntax_error(t_data *data, int len)
{
  int i; i = 0;
  while(i < len)
  { 
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((printf("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((printf("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type != WORD)
      return((printf("error near new line \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && len -1 == i)
      return((printf("error near new line \n"), 1));
    i++;
  }
  return 0;
}

t_data *make_token(char **arr)
{
  int len;
  t_data *list;

  len = len_of_two_d_array(arr);
  list = ft_malloc((len  + 1)* sizeof(t_data));
  fill_the_list(list, arr);
  if(check_syntax_error(list, len))
    exit(1);
  return list;
}

// int main()
// {
//   char *av[] = {"f", ">"  , "f", "eh", "|", NULL};
    
//   for(int i = 0; i < tow_d_lenth(av); i++)
//   {
//     printf("%s : ", ptr[i].word);
//     printf("%d\n", ptr[i].type);
//   }
//
//   return 0;
// }
