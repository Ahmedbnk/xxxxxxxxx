#include "minishell.h"

int execute_built_in_command(t_shell_control_block *shell)
{
  int result;
  
  if(are_they_equal(*shell->cmd_and_args, "pwd"))
  {
    printf("%s\n", pwd());
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "env"))
  {
    print_env(shell->env_cpy);
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "echo"))
  {
    echo(shell->cmd_and_args);
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "cd"))
  {
    result = cd(shell->env_cpy, shell->cmd_and_args);
    shell->exit_status = result;
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "export"))
  {
    result = export(shell, shell->cmd_and_args + 1);
    shell->exit_status = result;
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "unset"))
  {
    result = unset(&shell->env_cpy, shell->cmd_and_args + 1);
    shell->exit_status = result;
    return (1);
  }
  else if(are_they_equal(*shell->cmd_and_args, "exit"))
  {
    exit(0);
    return (1);
  }
  return 0;
}

void save_original_fds(t_shell_control_block *shell)
{
  shell->original_stdin = dup(0);
  shell->original_stdout = dup(1);
}

void restore_original_fds(t_shell_control_block *shell)
{
  dup2(shell->original_stdin, 0);
  dup2(shell->original_stdout, 1);
  close(shell->original_stdin);
  close(shell->original_stdout);
}

void init_redirection_vars(t_shell_control_block *shell)
{
  shell->in_file_name = NULL;
  shell->file_name = NULL;
}

int check_ambiguous_redirection(t_shell_control_block *shell)
{
  if (shell->file_name_lst && shell->file_name_lst->status == AMBIGUOUS)
  {
    print_error("ambig\n");
    shell->exit_status = 1;
    return 1;
  }
  return 0;
}

void advance_file_name_list(t_shell_control_block *shell)
{
  if (shell->file_name_lst)
    shell->file_name_lst = shell->file_name_lst->next;
}

void process_redirection_tokens(t_shell_control_block *shell)
{
  if (shell->tokenze->type == HEREDOC)
    shell->in_file_name = shell->tokenze->heredoc_file_name;
  else if (shell->tokenze->type == REDIR_IN)
    handle_redir_in((shell->tokenze->next)->word, &(shell->in_file_name));
  else if (shell->tokenze->type == REDIR_OUT)
    handle_redir_out((shell->tokenze->next)->word, &(shell->file_name));
  else if (shell->tokenze->type == REDIR_APPEND)
    handle_append((shell->tokenze->next)->word, &(shell->file_name));
}

int parse_redirections(t_shell_control_block *shell)
{
  t_token *original_tokenized;

  original_tokenized = shell->tokenze;
  while (shell->tokenze && shell->tokenze->word != NULL && shell->tokenze->type != PIPE)
  {
    if (is_redirection(shell->tokenze->word))
    {
      if (check_ambiguous_redirection(shell))
      {
        shell->tokenze = original_tokenized;
        return 1;
      }
      advance_file_name_list(shell);
    }
    process_redirection_tokens(shell);
    shell->tokenze = shell->tokenze->next;
  }
  shell->tokenze = original_tokenized;
  return 0;
}

void setup_output_redirection(t_shell_control_block *shell)
{
  if (shell->file_name)
  {
    shell->fd_out = open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(shell->fd_out, 1);
    close(shell->fd_out);
  }
}

void setup_input_redirection(t_shell_control_block *shell)
{
  if (shell->in_file_name)
  {
    shell->fd_in = open(shell->in_file_name, O_RDONLY);
    dup2(shell->fd_in, 0);
    close(shell->fd_in);
  }
}

int execute_built_in_with_redirections(t_shell_control_block *shell)
{
  int result;
  save_original_fds(shell);
  init_redirection_vars(shell);
  if (parse_redirections(shell))
    return 1;
  setup_output_redirection(shell);
  setup_input_redirection(shell);
  result = execute_built_in_command(shell);
  restore_original_fds(shell);
  return result;
}

int execute_built_in(t_shell_control_block *shell, int state)
{
  if (state == 1)
    return execute_built_in_with_redirections(shell);
  else
    return execute_built_in_command(shell);
}
