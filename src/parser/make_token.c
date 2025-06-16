#include "minishell.h"

t_type	get_type_type(const char *str)
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

void fill_the_list(t_token * list, char **arr)
{
  int i;
  i = 0;
  while(arr[i])
  {
    list[i].type = get_type_type(arr[i]);
    list[i].word = ft_strdup(arr[i], 1);
    i++;
  }
    list[i].word = 0;
    list[i].type = -1;
}


int check_syntax_error(t_token *data, int len)
{
  int i; i = 0;
  while(i < len)
  { 
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((print_error("error near | \n"), 2));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((print_error("error near | \n"), 2));
    else if (data[i].type != PIPE && data[i].type != WORD && 
             data[i + 1].type != WORD && data[i+1].type != -1)
    {
      return((print_error("error near new line \n"), 2));
    }
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == WORD)
    {
      // Check for ambiguous redirection (redirection followed by empty string or NULL)
      if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
           data[i].type == REDIR_APPEND))
      {
        // Check if the word after redirection is empty or NULL
        if (data[i + 1].word == NULL)
          return((print_error("ambiguous redirect\n"), 1));
        if (data[i + 1].word[0] == '\0')
          return((print_error("ambiguous redirect\n"), 1));
        if (ft_strlen(data[i + 1].word) == 0)
          return((print_error("ambiguous redirect\n"), 1));
      }
    }
    else if (data[i].type != PIPE && data[i].type != WORD && len -1 == i)
    {
      // Check for ambiguous redirection at the end
      if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
           data[i].type == REDIR_APPEND))
        return((print_error("ambiguous redirect\n"), 1));
      else
        return((print_error("error near new line \n"), 2));
    }
    i++;
  }
  return 0;
}

t_token *make_token(t_shell_control_block *shell)
{
  int len;
  t_token *list;
  char **arr;
  int syntax_result;

  arr = shell->splitted;
  len = len_of_two_d_array(arr);
  list = ft_malloc((len  + 1)* sizeof(t_token), 1);
  fill_the_list(list, arr);
  syntax_result = check_syntax_error(list, len);
  if(syntax_result)
  {
    shell->exit_status = syntax_result;
    return NULL;
  }
  return list;
}
