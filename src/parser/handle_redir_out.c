#include "minishell.h"

void handle_redir_out(char *str, char **file_name)
{
  *file_name = str;
}
