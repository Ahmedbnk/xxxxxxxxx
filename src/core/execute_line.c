#include "minishell.h"

void execute_line(t_shell_control_block *sh)
{
  if (sh->tokenze)
  {
    create_all_heredocs(sh);
    get_cmd_and_its_args(sh);
    if(!is_there_a_pipe(sh) && execute_built_in(sh, parent))
    {
      // Built-in commands now handle their own exit status
      // No need to set default exit status here ...
    }
    else
    {
      // Always use execute_command_line when there are pipes
      // or when the command is not a built-in
      execute_command_line(sh);
    }
  }
}
