#include "minishell.h"

void expand_input(char **input) {
  int i;
  i = 0;
  while (input[i])
  {
    if(are_they_equal(input[i], "<<"))
      i++;
    else
      input[i] = expand_if_possible(input[i], 0);
    i++;
  }
}

void parse_line(t_shell_control_block *shell)
{
  shell->splitted = customized_split(shell->line);
  shell->splitted = split_with_operators(shell->splitted);
  expand_input(shell->splitted);
  shell->splitted = handle_dollar_with_quotes(shell->splitted);
  shell->tokenized = make_token(shell->splitted);
}

int is_there_a_pipe(t_shell_control_block *shell)
{
  t_data *ptr;

  ptr = shell->tokenized;
  while(ptr->word != NULL)
  {
    if(ptr->type == PIPE)
      return 1;
    ptr++;
  }
  return 0;
}

void execute_line(t_shell_control_block *shell)
{
  if (shell->tokenized)
  {
    create_all_heredocs(shell->tokenized);
    get_cmd_and_its_args(shell);
    if(!is_there_a_pipe(shell) && execute_built_in(shell));
    else
      execute_command_line(shell);
  }
}

char *ft_readline(t_shell_control_block *shell) {


  shell->line = readline("\001\033[1;31m\002⚡ Undefined Behavior ⚡ » \001\033[0m\002");
  if (shell->line && *shell->line)

    add_history(shell->line);
  if (shell->line == NULL)
  {
    free(shell->line);
    free_memory(get_garbage_pointer(1));
    free_memory(get_garbage_pointer(0));
    exit(0);
    return NULL;
  }
  if (check_error(shell->line ))
    return NULL;
  return shell->line;
}

void ft_init_shell_block(t_shell_control_block *shell, int ac, char **av)
{
  (void) ac;
  (void) av;
  shell->env_cpy = NULL;
  shell->line = NULL;
  shell->splitted = NULL;
  shell->cmd_and_args= NULL;
}

int main(int ac, char **av, char **env)
{ 
  t_shell_control_block shell;

  ft_init_shell_block(&shell, ac, av);
  shell.env_cpy = copy_env(env);
 while (1) {

    handle_signals();
    if(!ft_readline(&shell))
      continue;
    parse_line(&shell);
    execute_line(&shell);
    free_memory(get_garbage_pointer(1));
    free(shell.line);
  }
  return (0);
}
