#include "minishell.h"

void handle_redir_out(char *str, char **file_name)
{
  int fd;

  if (check_ambiguous_redirection(str))
  {
    print_error("ambiguous redirect\n");
    *file_name = NULL;
    return;
  }
  
  *file_name = str;
  fd = open(str, O_CREAT| O_RDWR | O_TRUNC, 0644);
  close(fd);
}
