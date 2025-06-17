#include "minishell.h"

void handle_redir_out(char *str, char **file_name)
{
  if (str && *str)
    *file_name = str;
  else
    *file_name = NULL;
}
