#include "minishell.h"

void handle_redir_out(char *str, char **file_name)
{
  int fd;

  // Don't create a file if the filename is the EMPTY_REDIR marker
  if (are_they_equal(str, "EMPTY_REDIR"))
  {
    *file_name = NULL;
    return;
  }

  *file_name = str;
  fd = open(str, O_CREAT| O_RDWR | O_TRUNC, 0644);
  close(fd);
}
