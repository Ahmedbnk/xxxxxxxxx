#include "minishell.h"

void handle_append(char *str, char **file_name)
{
  int fd;

  *file_name = str;
  fd = open(str, O_CREAT| O_RDWR | O_APPEND, 0644);
  close(fd);
}
