#include "minishell.h"

char *remake_delimeter(char *str)
{
  char *returned_str = ft_malloc(ft_strlen(str) + 1, 1);

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
  char *original_str = NULL;

  tokenized->heredoc_file_name = ft_strjoin("/tmp/", generate_random_name());
  tokenized->delimiter = remake_delimeter((tokenized + 1) -> word);
  
  // Debug: print the delimiter
  printf("DEBUG: delimiter = '%s'\n", tokenized->delimiter);
  
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
    
    // Expand for content (but not for delimiter comparison)
    str = expand_if_possible(s, str, 1);
    
    // Debug: print the input and comparison
    printf("DEBUG: original input = '%s', delimiter = '%s', equal = %d\n", original_str, tokenized->delimiter, are_they_equal(original_str, tokenized->delimiter));
    
    if(are_they_equal(original_str, tokenized->delimiter))
    {
      free(original_str);
      break;
    }
    
    // Use expanded string for content
    buffer = ft_strjoin(buffer, str);
    free(original_str);
  }
  fd = open(tokenized->heredoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
  write(fd,buffer,ft_strlen(buffer));
  write(fd,"\n", 1);
  close(fd);
}

void create_all_heredocs(t_shell_control_block *shell)
{
  t_token *ptr;

  ptr = shell->tokenized;
  while(ptr && ptr -> word)
  {
    if(ptr -> type == HEREDOC)
      create_heredoc(shell, ptr);
    ptr ++;
  }
}
