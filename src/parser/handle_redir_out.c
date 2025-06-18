#include "minishell.h"

int handle_redir_out(char *str, char **file_name)
{
  int fd;

  // Check for ambiguous redirect
  if (!str || !*str || ft_strlen(str) == 0)
  {
    // Empty filename - ambiguous redirect
    *file_name = NULL;
    printf("ambiguous redirect\n");
    return 0; // Indicates ambiguous redirect
  }
  
  // Check if filename contains spaces (ambiguous redirect)
  for (int i = 0; str[i]; i++)
  {
    if (str[i] == ' ')
    {
      // Filename contains spaces - ambiguous redirect
      *file_name = NULL;
      printf("ambiguous redirect\n");
      return 0; // Indicates ambiguous redirect
    }
  }

  *file_name = str;
  fd = open(str, O_CREAT| O_RDWR | O_TRUNC, 0644);
  close(fd);
  return 1; // Indicates successful redirect
}
