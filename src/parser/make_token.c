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


int check_syntax_error(t_token *data, int len, t_shell_control_block *shell)
{
  int i; i = 0;
  while(i < len)
  { 
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((print_error("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((print_error("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type != WORD)
    {
      // Check if this is an ambiguous redirect (empty filename after redirection)
      if ((data[i].type == REDIR_OUT || data[i].type == REDIR_APPEND) && 
          (data[i + 1].word == NULL || data[i + 1].word[0] == '\0'))
      {
        // This is an ambiguous redirect - print error and return
        printf("ambiguous redirect\n");
        shell->exit_status = 1; // Set exit status for ambiguous redirect
        return 1;
      }
      printf("this is what cause the error : %d\n", data[i+1].type);
      return((print_error("error near new line \n"), 1));
    }
    else if (data[i].type != PIPE && data[i].type != WORD && len -1 == i)
      return((print_error("error near new line \n"), 1));
    i++;
  }
  return 0;
}

t_token *make_token(t_shell_control_block *shell)
{
  int len;
  t_token *list;
  char **arr;

  arr = shell->splitted;
  len = len_of_two_d_array(arr);
  list = ft_malloc((len  + 1)* sizeof(t_token), 1);
  fill_the_list(list, arr);
  if(check_syntax_error(list, len, shell))
  {
    // Check if it was an ambiguous redirect error
    if (shell->exit_status == 0) // If exit_status wasn't set by ambiguous redirect
      shell->exit_status = 2; // Set to 2 for other syntax errors
    return NULL;
  }
  return list;
}
