#include "minishell.h"

int main(int ac, char **av, char **env)
{
  t_shell_control_block sh;

  ft_init_shell_block(&sh, ac, av);
  sh.env_of_export = copy_env(env);
  sh.env_cpy = copy_env(env);
 while (1)
  {
    handle_signals(0);
    if (!ft_readline(&sh) || parse_line(&sh))
      continue;
    execute_line(&sh);
    free_memory(get_garbage_pointer(1));
    free(sh.line);
  }
  return (0);
}
