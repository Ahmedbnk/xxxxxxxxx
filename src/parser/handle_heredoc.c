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
    else if(str[i] == '$' && (str[i + 1] == single_q || str[i + 1] == double_q) && !is_between_quotes(str, i))
      i ++;
    else
      returned_str[j++] = str[i++];
  }
  returned_str[j] = '\0';
  remove_quotes(&returned_str);
  return returned_str;
}

void create_heredoc(t_data *tokenized)
{
  int fd;
  char *str = NULL; 
  char *buffer = NULL; 

  tokenized->heredoc_file_name = ft_strjoin("/tmp/", generate_random_name());
  tokenized->delimiter = remake_delimeter((tokenized + 1) -> word);
  while(1)
  {
    str = readline(">");
    if(str == NULL)
    {
      print_error("warning: here-document delimited by end-of-file (wanted `%s')\n", tokenized->delimiter);
      break;
    }
    str = expand_if_possible(str, 1);
    if(are_they_equal(str, tokenized->delimiter))
       break;
    buffer = ft_strjoin(buffer, str);
  }
  fd = open(tokenized->heredoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
  write(fd,buffer,ft_strlen(buffer));
  write(fd,"\n", 1);
  close(fd);
}

void create_all_heredocs(t_data *tokenized)
{
  while(tokenized && tokenized -> word)
  {
    if(tokenized -> type == HEREDOC)
      create_heredoc(tokenized);
    tokenized ++;
  }
}
