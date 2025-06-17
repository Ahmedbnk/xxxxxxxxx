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
    // Check for pipe at beginning or end
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((print_error("syntax error near unexpected token `|'\n"), 2));
    
    // Check for pipe without command before it
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((print_error("syntax error near unexpected token `|'\n"), 2));
    
    // Check for redirection followed by another redirection (check this BEFORE redirection at beginning/end)
    else if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
              data[i].type == REDIR_APPEND || data[i].type == HEREDOC) && i + 1 < len &&
             (data[i + 1].type == REDIR_IN || data[i + 1].type == REDIR_OUT || 
              data[i + 1].type == REDIR_APPEND || data[i + 1].type == HEREDOC))
    {
      if (data[i + 1].type == REDIR_OUT)
        return((print_error("syntax error near unexpected token `>'\n"), 2));
      else if (data[i + 1].type == REDIR_IN)
        return((print_error("syntax error near unexpected token `<'\n"), 2));
      else if (data[i + 1].type == REDIR_APPEND)
        return((print_error("syntax error near unexpected token `>>'\n"), 2));
      else if (data[i + 1].type == HEREDOC)
        return((print_error("syntax error near unexpected token `<<'\n"), 2));
    }
    
    // Check for redirection without command before it (but allow heredoc)
    else if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
              data[i].type == REDIR_APPEND) && i == 0)
      return((print_error("syntax error near unexpected token `newline'\n"), 2));
    
    // Check for redirection at the end (no filename)
    else if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
              data[i].type == REDIR_APPEND || data[i].type == HEREDOC) && len - 1 == i)
      return((print_error("syntax error near unexpected token `newline'\n"), 2));
    
    // Check for ambiguous redirection (redirection followed by empty string)
    else if ((data[i].type == REDIR_IN || data[i].type == REDIR_OUT || 
              data[i].type == REDIR_APPEND || data[i].type == HEREDOC) && i + 1 < len && data[i + 1].type == WORD)
    {
      if (data[i + 1].word == NULL || data[i + 1].word[0] == '\0' || 
          ft_strlen(data[i + 1].word) == 0)
        return((print_error("ambiguous redirect\n"), 1));
    }
    
    // Check for invalid token sequences
    else if (data[i].type != PIPE && data[i].type != WORD && 
             data[i + 1].type != WORD && data[i+1].type != -1)
    {
      return((print_error("syntax error near unexpected token `newline'\n"), 2));
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
  if(syntax_result == 2) // Syntax error - return NULL
  {
    shell->exit_status = syntax_result;
    return NULL;
  }
  else if(syntax_result == 1) // Ambiguous redirect - return NULL to prevent execution
  {
    shell->exit_status = syntax_result;
    return NULL; // Return NULL to prevent command execution
  }
  return list;
}
