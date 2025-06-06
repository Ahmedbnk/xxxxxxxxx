#include "minishell.h"

char ** copy_env(char **env);
//
// int main(int argc, char *argv[], char **env)
// {
//   int i = 0;
//   (void)  argv;
//   (void) argc; 
//   char **my_env;
//   my_env = NULL;
//
//   my_env = copy_env(env);
//   while(my_env[i])
//   {
//     printf("%s\n", env[i]);
//     i++;
//   }
// }
//

char ** copy_env(char **env)
{
  int i;
  char **my_env;
  my_env = ft_malloc((len_of_two_d_array(env) + 1) * sizeof(char *), 0);
  i = 0;
  while(env[i])
  {
    my_env[i] = ft_strdup((const char *)env[i], 0);
    i++;
  }
  my_env[i] = NULL;
  return my_env;
}
