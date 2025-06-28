#include "minishell.h"


void skip_ambig_list(t_shell_control_block *shell)
{
  t_name_lst *name_lst;

  name_lst = shell->file_name_lst;
  if(!name_lst)
    return;
  while(name_lst != NULL && name_lst->status != NEW_START)
    name_lst = name_lst ->next;
  if(name_lst != NULL && name_lst ->status == NEW_START)
    name_lst = name_lst ->next;
  shell->file_name_lst = name_lst;
}
void	skip_command(t_token **tokenized_address)
{
  t_token	*tokenze;

  tokenze = *tokenized_address;
  while (tokenze && tokenze->word != NULL && tokenze->type != PIPE)
    tokenze = tokenze->next;
  *tokenized_address = tokenze;
}

void handle_all_redir(t_shell_control_block *shell)
{
  while (shell->tokenze && shell->tokenze->word != NULL && shell->tokenze->type != PIPE)
  {
    if(is_redirection(shell->tokenze->word))
    {
      if(shell->file_name_lst && shell->file_name_lst->status == AMBIGUOUS)
      {
        print_error("AMBIGUOUS\n");
        exit(1);
      }
      if(shell->file_name_lst)
        shell->file_name_lst = shell->file_name_lst ->next;
    }
      if (shell->tokenze->type == HEREDOC)
        shell->in_file_name = shell->tokenze->heredoc_file_name;
      else if (shell->tokenze->type == REDIR_IN)
        handle_redir_in((shell->tokenze->next)->word, &(shell->in_file_name));
      else if (shell->tokenze->type == REDIR_OUT)
        handle_redir_out((shell->tokenze->next)->word, &(shell->file_name));
      else if (shell->tokenze->type == REDIR_APPEND)
        handle_append((shell->tokenze->next)->word, &(shell->file_name));
      shell->tokenze =shell->tokenze->next;
  }

}

void	process_command(t_shell_control_block *shell)
{
  shell->in_file_name = NULL;
  shell->file_name = NULL;
  handle_all_redir(shell);
    if (shell->file_name)
  {
    shell->fd_out = open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(shell->fd_out, 1);
    close(shell->fd_out);
  }
  if(shell->in_file_name)
  {
    shell->fd_in = open(shell->in_file_name, O_CREAT | O_RDONLY, 0644);
    dup2(shell->fd_in, 0);
    close(shell->fd_in);
  }
  if(!execute_built_in(shell, child))
    execute_command(shell);
	if(shell->in_file_name)
  		unlink(shell->in_file_name);
}

void execute_command_line_helper(t_shell_control_block *shell)
{
  handle_signals(1);
  int p_id = fork();
  if (p_id == 0)
  {
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (shell->previous_read_end != -1)
    {
      dup2(shell->previous_read_end, 0);
      close(shell->previous_read_end);
    }
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
    {
      close(shell->arr[0]);
      dup2(shell->arr[1], 1);
      close(shell->arr[1]);
    }
    process_command(shell);
    exit(0);
  }
  else
    shell->last_child_pid = p_id;
}

void execute_command_line(t_shell_control_block *shell)
{
  int status;

  status = 0;
  shell->line_pointer = shell->tokenze;
  shell->previous_read_end = -1;
  while (shell->line_pointer && shell->line_pointer->word)
  {
    shell->tokenze = shell->line_pointer;
    skip_command(&(shell->line_pointer));
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
      pipe(shell->arr);
    execute_command_line_helper(shell);
    skip_ambig_list(shell);
    if (shell->previous_read_end != -1)
      close(shell->previous_read_end);
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
    {
      close(shell->arr[1]);
      shell->previous_read_end =shell->arr[0];
      shell->line_pointer = shell->line_pointer->next ;
    }
  }
  if (shell->previous_read_end != -1)
    close(shell->previous_read_end);
  waitpid(shell->last_child_pid, &status, 0);
  if (WIFEXITED(status))
    shell->exit_status = WEXITSTATUS(status);
  else if(WIFSIGNALED(status))
    shell->exit_status =  128 + WTERMSIG(status);
  else if(WIFSTOPPED(status))
    shell->exit_status = WSTOPSIG(status);
  while (wait(NULL) > 0)
    ;
  if(shell->exit_status > 128)
    print_exit_signal_message(shell->exit_status);

}
