#include "minishell.h"

void handle_heredoc(char *str, char **in_file_name)
{
  int fd;
  char *buffer;

  while(1)
  {
    *in_file_name = ft_strjoin("/tmp/", generate_random_name());
    fd = open(*in_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    close(fd);
  }
  if(*str == '$' && (*(str + 1) == single_q || *(str + 1) == double_q))
    str ++;
  remove_quotes(&str);
  buffer = NULL;
  
  fd = open(*in_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
  while(1)
  {
    buffer = readline("> ");
    if(buffer == NULL)
    {
      printf("warning: here-document delimited by end-of-file (wanted `%s')\n", str);
      break;
    }
    else if(are_they_equal(str, buffer))
      break;
    else
      buffer = expand_if_possible(buffer, 1);

    if(buffer == NULL)
    {
      printf("bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s') ",str);
      return;
    }
    write(fd,buffer,ft_strlen(buffer));
    write(fd,"\n", 1);
  }
  close(fd);
}
