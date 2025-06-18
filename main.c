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
  printf("DEBUG: execute_line - exit_status at start: %d\n", shell->exit_status);
  
  // Reset exit_status for new command (unless it's a syntax error that should persist)
  // Only reset for non-pipeline commands to preserve errors across pipeline
  if (shell->exit_status == 1 && !is_there_a_pipe(shell)) // Ambiguous redirect error
  {
    printf("DEBUG: Resetting exit_status for non-pipeline command\n");
    shell->exit_status = 0; // Reset for new command
  }
  else if (shell->exit_status == 1)
  {
    printf("DEBUG: Preserving exit_status for pipeline command\n");
  }
    
  if (shell->tokenized)
  {
    printf("DEBUG: Processing tokenized command\n");
    // Check if there's an ambiguous redirect error and return early
    if (shell->exit_status == 1)
    {
      printf("DEBUG: Returning early due to exit_status == 1\n");
      return;
    }
      
    create_all_heredocs(shell);
    get_cmd_and_its_args(shell);
    if(!is_there_a_pipe(shell) && are_they_equal(*shell->cmd_and_args, "cd"))
      cd(shell->env_cpy, shell->cmd_and_args, 1);
    else
      execute_command_line(shell);
  }
  else if (shell->exit_status == 1)
  {
    printf("DEBUG: Returning early due to exit_status == 1 (no tokens)\n");
    return;
  }
  else
  {
    // Empty command (only spaces/tabs) - exit with 0
    shell->exit_status = 0;
  }
  
  printf("DEBUG: execute_line - exit_status at end: %d\n", shell->exit_status);
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
    if (shell.line)
      free(shell.line);
  }
  return (0);
}
