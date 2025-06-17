#include "minishell.h"

void parse_line(t_shell_control_block *shell)
{
  shell->splitted = customized_split(shell->line);
  shell->splitted = split_with_operators(shell->splitted);
  expand(shell);
  shell->splitted = split_after_expantion(shell->splitted);
  shell->splitted = handle_dollar_with_quotes(shell->splitted);
  shell->tokenized = make_token(shell);
}

void execute_line(t_shell_control_block *shell)
{
  // Reset exit_status for new command (unless it's a syntax error that should persist)
  if (shell->exit_status == 1) // Ambiguous redirect error
    shell->exit_status = 0; // Reset for new command
    
  if (shell->tokenized)
  {
    create_all_heredocs(shell);
    get_cmd_and_its_args(shell);
    if(!is_there_a_pipe(shell) && are_they_equal(*shell->cmd_and_args, "cd"))
      cd(shell->env_cpy, shell->cmd_and_args, 1);
    else
      execute_command_line(shell);
  }
  else if (shell->exit_status == 1)
  {
    return;
  }
  else
  {
    // Empty command (only spaces/tabs) - exit with 0
    shell->exit_status = 0;
  }
}

int main(int ac, char **av, char **env)
{ 
  t_shell_control_block shell;

  ft_init_shell_block(&shell, ac, av);
  shell.env_cpy = copy_env(env);
 while (1) {
    handle_signals(0);
    if(!ft_readline(&shell))
      continue;
    parse_line(&shell);
    execute_line(&shell);
    free_memory(get_garbage_pointer(0));
    free(shell.line);
  }
  return (0);
}
