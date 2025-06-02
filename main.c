#include "minishell.h"

void expand_input(char **input) {
  int i;
  i = 0;
  while (input[i]) {
    if(are_they_equal(input[i], "<<"))
      i++;
    else
      input[i] = expand_if_possible(input[i], 0);
    i++;
  }
}

void parse_and_expand(t_shell_block *shell_block)
{

  shell_block->splitted = customized_split(shell_block->line);
  shell_block->splitted = split_with_operators(shell_block->splitted);
  expand_input(shell_block->splitted);

  shell_block->tokenized = make_token(shell_block->splitted);
  if (shell_block->tokenized) {
    remove_quotes_from_args(shell_block->splitted);
    create_all_heredocs(shell_block->tokenized);
    execute_command_line(shell_block->tokenized,shell_block->env_cpy);
  }
}

char *ft_readline(void) {

  char *line;
  handle_signals();

  line = readline("\001\033[1;31m\002⚡ Undefined Behavior ⚡ » \001\033[0m\002");
  if (line && *line)
    add_history(line);
  if (line == NULL)
  {
    free(line);
    free_memory(*get_garbage_pointer());
    exit(0);
    return NULL;
  }
  return line;
}

void ft_init_shell_block(t_shell_block *shell_block)
{
  shell_block->env_cpy = NULL;
  shell_block->line = NULL;
  shell_block->splitted = NULL;
}
int main(int ac, char **av, char **env) {

  t_shell_block shell_block;

  ft_init_shell_block(&shell_block);

  shell_block.env_cpy = copy_env(env);

  (void)ac;
  (void)av;
  while (1) {
    shell_block.line  = ft_readline();
    if(!shell_block.line )
      continue;
    if (check_error(shell_block.line ))
      free_memory(*get_garbage_pointer());
    parse_and_expand(&shell_block);
    free(shell_block.line);
  }
  return (0);
}

