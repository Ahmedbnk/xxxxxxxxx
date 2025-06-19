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
  int i; 
  i = 0;
  
  // Debug: print all tokens
  printf("DEBUG: Checking %d tokens\n", len);
  for (int k = 0; k < len; k++)
  {
    printf("DEBUG: Token[%d]: type=%d, word='%s'\n", k, data[k].type, data[k].word ? data[k].word : "NULL");
  }
  
  // First pass: check for ambiguous redirects
  while(i < len)
  { 
    if (data[i].type == REDIR_OUT || data[i].type == REDIR_APPEND)
    {
      printf("DEBUG: Found redirection at index %d\n", i);
      // Check if the next token is empty or the special EMPTY_REDIR marker
      if (i + 1 < len && data[i + 1].word && 
          (ft_strlen(data[i + 1].word) == 0 || are_they_equal(data[i + 1].word, "EMPTY_REDIR")))
      {
        printf("DEBUG: Empty filename detected at index %d\n", i + 1);
        printf("ambiguous redirect\n");
        return 2; // Special return code for ambiguous redirect
      }
      
      // Check if the next token contains spaces (ambiguous redirect)
      if (i + 1 < len && data[i + 1].word)
      {
        for (int j = 0; data[i + 1].word[j]; j++)
        {
          if (data[i + 1].word[j] == ' ')
          {
            printf("DEBUG: Filename with spaces detected at index %d\n", i + 1);
            printf("ambiguous redirect\n");
            return 2; // Special return code for ambiguous redirect
          }
        }
      }
    }
    i++;
  }
  
  // Second pass: check for syntax errors
  i = 0;
  while(i < len)
  { 
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((print_error("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((print_error("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type != WORD)
    {
      printf("DEBUG: Syntax error at index %d: type=%d, next_type=%d\n", i, data[i].type, data[i + 1].type);
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
  list = ft_malloc((len + 1) * sizeof(t_token), 1);
  fill_the_list(list, arr);
  
  int syntax_result = check_syntax_error(list, len);
  if(syntax_result == 1)
  {
    shell->exit_status = 2;
    return NULL;
  }
  else if(syntax_result == 2)
  {
    // Ambiguous redirect detected
    shell->exit_status = 1;
    return list; // Return the tokens so we can process them and create files before the error
  }
  return list;
}
