#include "minishell.h"

void handle_redir_in(char *str, char **in_file_name)
{
  int fd;
  char *buffer;

  buffer = NULL;

  *in_file_name = ft_strjoin("/tmp/tmp_file", generate_random_name());
  buffer = read_file(str);
  if(!buffer)
    return;
  fd = open(*in_file_name, O_CREAT| O_RDWR | O_TRUNC, 0766);
  write(fd,buffer, ft_strlen(buffer));
  close(fd);
}
