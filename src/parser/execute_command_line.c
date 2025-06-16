#include "minishell.h"

int	generate_random_number(void)
{
  int	fd;
  int	random_number;

  fd = open("/dev/random", O_RDONLY);
  read(fd, &random_number, 4);
  close(fd);
  if (random_number < 0)
    return (-random_number);
  return (random_number);
}

char	*generate_random_name(void)
{
  int	num;

  num = generate_random_number();
  if (num < 0)
    return (NULL);
  return (ft_itoa(num));
}



void	skip_command(t_token **tokenized_address)
{
  t_token	*tokenized;

  tokenized = *tokenized_address;
  while (tokenized && tokenized->word != NULL && tokenized->type != PIPE)
    tokenized ++;
  *tokenized_address = tokenized;
}

void handle_all_redir(t_shell_control_block *shell)
{
  while (shell->tokenized && shell->tokenized->word != NULL && shell->tokenized->type != PIPE)
  {
    if (shell->tokenized->type == HEREDOC)
      shell->in_file_name = shell->tokenized->heredoc_file_name;
    else if (shell->tokenized->type == REDIR_IN)
      handle_redir_in((shell->tokenized + 1)->word, &(shell->in_file_name));
    else if (shell->tokenized->type == REDIR_OUT)
      handle_redir_out((shell->tokenized + 1)->word, &(shell->file_name));
    else if (shell->tokenized->type == REDIR_APPEND)
      handle_append((shell->tokenized + 1)->word, &(shell->file_name));
    shell->tokenized ++;
  }

}
void	process_command(t_shell_control_block *shell)
{
  shell->in_file_name = NULL;
  shell->file_name = NULL;
  get_cmd_and_its_args(shell);
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
  if(!execute_built_in(shell))
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
    child_signal_handler();
    if (shell->previous_read_end != -1)
    {
      dup2(shell->previous_read_end, 0);
      close(shell->previous_read_end);
    }
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
    {
      close(shell->previous_read_end);
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
  shell->line_pointer = shell->tokenized;
  shell->previous_read_end = -1;
  while (shell->line_pointer && shell->line_pointer->word)
  {
    shell->tokenized = shell->line_pointer;
    skip_command(&(shell->line_pointer));
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
      pipe(shell->arr);
    execute_command_line_helper(shell);
    if (shell->previous_read_end != -1)
      close(shell->previous_read_end);
    if (shell->line_pointer && shell->line_pointer->type == PIPE)
    {
      close(shell->arr[1]);
      shell->previous_read_end =shell->arr[0];
      shell->line_pointer++;
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
