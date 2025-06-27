#include "minishell.h"

char *read_file(char *file_name)
{
  char *small_buffer;
  char *big_buffer;
  int fd;


  fd = open(file_name, O_RDWR , 0777);

  small_buffer = get_next_line(fd);
  while(buffer)
  {
    big_buffer = ft_strjoin(big_buffer, small_buffer);
    small_buffer = get_next_line(fd);
  }
  close(fd);
  return big_buffer;
}
