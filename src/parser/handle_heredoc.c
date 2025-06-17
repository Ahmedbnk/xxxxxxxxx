#include "minishell.h"

char *remake_delimeter(char *str)
{
  char *returned_str;

  if (!str)
    return NULL;

  // Use the expansion system to expand variables in the delimiter
  char *expanded = expand_if_possible(NULL, str, 1);
  if (expanded && *expanded)
    str = expanded;
  else if (expanded && !*expanded)
  {
    // If expansion results in empty string, use original string
    free(expanded);
  }

  returned_str = ft_malloc(ft_strlen(str) + 1, 1);

  int i;
  int j;

  i = 0;
  j = 0;
  while(str[i])
  {
    // Handle $$ sequences - keep them literal even if followed by quotes
    if(str[i] == '$' && str[i + 1] == '$')
    {
      returned_str[j++] = str[i++];
      returned_str[j++] = str[i++];
    }
    // Handle $ followed by single or double quote (but only if not preceded by $)
    else if(str[i] == '$' && (str[i + 1] == single_q || str[i + 1] == double_q) && 
            (i == 0 || str[i - 1] != '$') && !is_between_quotes(str, i))
      i++;
    else
      returned_str[j++] = str[i++];
  }
  returned_str[j] = '\0';
  remove_quotes(&returned_str);
  return returned_str;
}

void create_heredoc(t_shell_control_block *s ,t_token *tokenized)
{
  int fd;
  char *str = NULL; 
  char *buffer = NULL; 
  char *temp;

  if (!s || !tokenized)
    return;

  tokenized->heredoc_file_name = ft_strjoin("/tmp/", generate_random_name());
  
  // Check if there's a delimiter
  if (!(tokenized + 1) || !(tokenized + 1)->word)
  {
    print_error("syntax error near unexpected token `newline'\n");
    return;
  }
  
  tokenized->delimiter = remake_delimeter((tokenized + 1) -> word);
  
  while(1)
  {
    str = readline(">");
    if(str == NULL)
    {
      print_error("warning: here-document delimited by end-of-file (wanted `%s')\n", tokenized->delimiter);
      break;
    }
    str = expand_if_possible(s, str, 1);
    if(are_they_equal(str, tokenized->delimiter))
       break;
    
    // Handle buffer properly
    if (!buffer)
      buffer = ft_strdup(str, 1);
    else
    {
      temp = ft_strjoin(buffer, str);
      free(buffer);
      buffer = temp;
    }
  }
  
  if (buffer)
  {
    fd = open(tokenized->heredoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    write(fd,buffer,ft_strlen(buffer));
    write(fd,"\n", 1);
    close(fd);
    free(buffer);
  }
}

void create_all_heredocs(t_shell_control_block *shell)
{
  t_token *ptr;

  if (!shell || !shell->tokenized)
    return;

  ptr = shell->tokenized;
  while(ptr && ptr -> word)
  {
    if(ptr -> type == HEREDOC)
      create_heredoc(shell, ptr);
    ptr ++;
  }
}
