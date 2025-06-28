#include "minishell.h"

void execute_line(t_shell_control_block *sh)
{
  if (sh->tokenze)
  {
    create_all_heredocs(sh);
    get_cmd_and_its_args(sh);
    if(!is_there_a_pipe(sh) && execute_built_in(sh, parent))
      ; // Exit status is already set in execute_built_in_command
    else
      execute_command_line(sh);
  }
}
