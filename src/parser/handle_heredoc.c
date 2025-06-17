#include "minishell.h"

char *remake_delimeter(char *str)
{
  if (!str)
    return NULL;
    
  // Allocate enough space for the worst case (no characters removed)
  char *returned_str = ft_malloc(ft_strlen(str) + 1, 1);
  if (!returned_str)
    return NULL;

  int i;
  int j;

  i = 0;
  j = 0;
  while(str[i])
  {
    if(str[i] == '$' && str[i + 1] == '$')
    {
      returned_str[j++] = str[i++];
      returned_str[j++] = str[i++];
    }
    // Handle $ followed by single or double quote (but only if not preceded by $)
    else if(str[i] == '$' && (str[i + 1] == single_q || str[i + 1] == double_q) && 
            (i == 0 || str[i - 1] != '$') && !is_between_quotes(str, i))
      i++;
    // Handle $ followed by quotes (even if preceded by $) - remove the $
    else if(str[i] == '$' && (str[i + 1] == single_q || str[i + 1] == double_q))
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
  char *original_str = NULL;
  char *temp_buffer = NULL;

  if (!tokenized || !(tokenized + 1) || !(tokenized + 1)->word)
    return;

  tokenized->heredoc_file_name = ft_strjoin("/tmp/", generate_random_name());
  if (!tokenized->heredoc_file_name)
    return;
    
  tokenized->delimiter = remake_delimeter((tokenized + 1)->word);
  if (!tokenized->delimiter)
  {
    // Clean up if delimiter creation fails
    free(tokenized->heredoc_file_name);
    tokenized->heredoc_file_name = NULL;
    return;
  }
  
  while(1)
  {
    str = readline(">");
    if(str == NULL)
    {
      print_error("warning: here-document delimited by end-of-file (wanted `%s')\n", tokenized->delimiter);
      break;
    }
    
    // Save original input for delimiter comparison
    original_str = ft_strdup(str, 1);
    if (!original_str)
    {
      free(str); // readline memory
      break;
    }
    
    // Expand for content (but not for delimiter comparison)
    char *expanded_str = expand_if_possible(s, str, 1);
    
    if(are_they_equal(original_str, tokenized->delimiter))
    {
      free(original_str); // ft_malloc memory
      free(str); // readline memory
      break;
    }
    
    // Use expanded string for content
    temp_buffer = ft_strjoin(buffer, expanded_str ? expanded_str : str);
    if (temp_buffer)
    {
      // Don't free buffer here - it's managed by garbage collector
      buffer = temp_buffer;
    }
    
    free(original_str); // ft_malloc memory
    free(str); // readline memory
  }
  
  if (buffer)
  {
    fd = open(tokenized->heredoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd != -1)
    {
      write(fd, buffer, ft_strlen(buffer));
      write(fd, "\n", 1);
      close(fd);
    }
    // Don't free buffer - it's managed by garbage collector
  }
}

void create_all_heredocs(t_shell_control_block *shell)
{
  t_token *ptr;

  if (!shell || !shell->tokenized)
    return;
    
  ptr = shell->tokenized;
  while(ptr && ptr->word)
  {
    if(ptr->type == HEREDOC)
      create_heredoc(shell, ptr);
    ptr++;
  }
}
