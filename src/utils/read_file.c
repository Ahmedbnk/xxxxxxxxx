#include "minishell.h"

char *read_file(char *file_name)
{
  char *small_buffer;
  char *big_buffer;

  big_buffer = NULL;
  int fd;


  fd = open(file_name, O_RDWR , 0777);
  if(fd < 0)
  {
    printf("No such file or directory \n");
    exit(1);
  }
  small_buffer = get_next_line(fd);
  while(small_buffer)
  {
    big_buffer = ft_strjoin(big_buffer, small_buffer);
    small_buffer = get_next_line(fd);
  }
  close(fd);
  return big_buffer;
}
