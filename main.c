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
  if (shell->tokenized)
  {
    create_all_heredocs(shell);
    get_cmd_and_its_args(shell);
    if(!is_there_a_pipe(shell) && are_they_equal(*shell->cmd_and_args, "cd"))
      cd(shell->env_cpy, shell->cmd_and_args, 1);
    else
      execute_command_line(shell);
  }
  // If expansion failed due to ambiguous redirect, don't execute
  else if (shell->exit_status == 1)
  {
    // Expansion already set the exit status and printed the error
    return;
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
    free_memory(get_garbage_pointer(1));
    free(shell.line);
  }
  return (0);
}
