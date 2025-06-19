#include "minishell.h"

void expand(t_shell_control_block *shell) 
{
  int i;
  i = 0;
  while (shell->splitted[i])
  {
    if(are_they_equal(shell->splitted[i], "<<"))
      i++;
    else
    {
      char *expanded = expand_if_possible(shell, shell->splitted[i], 0);
      
      // Check if this is a redirection filename that expanded to empty
      if (expanded && ft_strlen(expanded) == 0)
      {
        // Check if the previous token is a redirection operator
        if (i > 0 && (are_they_equal(shell->splitted[i-1], ">") || 
                      are_they_equal(shell->splitted[i-1], ">>")))
        {
          // This is a redirection filename that expanded to empty
          // Replace with a special marker that won't be removed by customized_split
          shell->splitted[i] = ft_strdup("EMPTY_REDIR", 1);
        }
        else
        {
          shell->splitted[i] = expanded;
        }
      }
      else
      {
        shell->splitted[i] = expanded;
      }
    }
    i++;
  }
}

int count_lsit_size(t_list *list)
{
  int size;
  int i;
  char **array;
  size = 0;
  while(list)
  {
    array = (char **)(list->content);
    i = 0;
    while(array[i])
    {
      size ++;
      i++;
    }
    list = list->next;
  }
  return size;
}

char **creat_new_splitted(t_list *list)
{
  char **new_splitted;
  char **array;

  int i;
  int j;
  j = 0;
  new_splitted = ft_malloc((count_lsit_size(list)+1) * sizeof(char *), 1);
  while(list)
  {
    array = (char **)list->content;
    i = 0;
    while(array[i])
    {
      new_splitted[j] = array[i];
      j++;
      i++;
    }
    list = list->next;
  }
  new_splitted[j] = NULL;
  return new_splitted;
}
char **split_after_expantion(char **str)
{
  int i;
  char **ptr;
  t_list *node;
  t_list *list;
  list =NULL;
  i = 0;
  while(str[i])
  {
    ptr = customized_split(str[i]);
    node = ft_lstnew(ptr);
    ft_lstadd_back(&list, node);
    i++;
  }
  return (creat_new_splitted(list));
}
void parse_line(t_shell_control_block *shell)
{
  shell->splitted = customized_split(shell->line);
  shell->splitted = split_with_operators(shell->splitted);
  expand(shell);
  
  shell->splitted = split_after_expantion(shell->splitted);
  shell->splitted = handle_dollar_with_quotes(shell->splitted);
  shell->tokenized = make_token(shell);
}

int is_there_a_pipe(t_shell_control_block *shell)
{
  t_token *ptr;

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
  // Reset exit_status for new command
  if (shell->exit_status == 1)
  {
    // Ambiguous redirect error - reset for new command
    shell->exit_status = 0;
  }
  
  if (shell->tokenized)
  {
    create_all_heredocs(shell);
    get_cmd_and_its_args(shell);
    if(!is_there_a_pipe(shell) && execute_built_in(shell, 1));
    else
      execute_command_line(shell);
  }
}

char *ft_readline(t_shell_control_block *shell)
{
  shell->line = readline("\001\033[1;31m\002 Undefined Behavior :\001\033[0m\002");
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
  if (check_error(shell))
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
  shell->env_of_export = NULL;
  shell->exit_status= 0;
}

int main(int ac, char **av, char **env)
{ 
  t_shell_control_block shell;

  ft_init_shell_block(&shell, ac, av);
  shell.env_of_export = copy_env(env);
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
