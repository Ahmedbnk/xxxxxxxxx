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
  printf("DEBUG: Entering handle_all_redir\n");
  
  while (shell->tokenized && shell->tokenized->word != NULL && shell->tokenized->type != PIPE)
  {
    printf("DEBUG: Processing redirection type: %d, word: %s\n", shell->tokenized->type, shell->tokenized->word);
    
    if (shell->tokenized->type == HEREDOC)
      shell->in_file_name = shell->tokenized->heredoc_file_name;
    else if (shell->tokenized->type == REDIR_IN)
      handle_redir_in((shell->tokenized + 1)->word, &(shell->in_file_name));
    else if (shell->tokenized->type == REDIR_OUT)
    {
      char *filename = (shell->tokenized + 1)->word;
      printf("DEBUG: REDIR_OUT filename: '%s'\n", filename);
      
      // Check for ambiguous redirect first
      if (!filename || !*filename || ft_strlen(filename) == 0)
      {
        printf("DEBUG: Ambiguous redirect detected in REDIR_OUT\n");
        // Don't print error here (already printed in syntax checker)
        shell->exit_status = 1;
        break; // Stop processing redirections
      }
      
      // Create the file if filename is valid
      int fd = open(filename, O_WRONLY | O_TRUNC);
      if (fd == -1)
        fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      if (fd != -1)
        close(fd);
      
      handle_redir_out(filename, &(shell->file_name));
    }
    else if (shell->tokenized->type == REDIR_APPEND)
    {
      char *filename = (shell->tokenized + 1)->word;
      printf("DEBUG: REDIR_APPEND filename: '%s'\n", filename);
      
      // Check for ambiguous redirect first
      if (!filename || !*filename || ft_strlen(filename) == 0)
      {
        printf("DEBUG: Ambiguous redirect detected in REDIR_APPEND\n");
        // Don't print error here (already printed in syntax checker)
        shell->exit_status = 1;
        break; // Stop processing redirections
      }
      
      // Create the file if filename is valid
      int fd = open(filename, O_WRONLY | O_APPEND);
      if (fd == -1)
        fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
      if (fd != -1)
        close(fd);
      
      handle_append(filename, &(shell->file_name));
    }
    
    printf("DEBUG: Moving to next token\n");
    shell->tokenized ++;
  }
  
  printf("DEBUG: Exiting handle_all_redir\n");
}

void	apply_redirections(t_shell_control_block *shell)
{
  printf("DEBUG: Entering apply_redirections\n");
  
  shell->in_file_name = NULL;
  shell->file_name = NULL;
  
  printf("DEBUG: About to call handle_all_redir\n");
  handle_all_redir(shell);
  printf("DEBUG: handle_all_redir completed\n");
  
  printf("DEBUG: Checking shell->file_name: '%s'\n", shell->file_name ? shell->file_name : "NULL");
  
  if (shell->file_name)
  {
    printf("DEBUG: About to open file: %s\n", shell->file_name);
    shell->fd_out = open(shell->file_name, O_WRONLY | O_TRUNC);
    printf("DEBUG: First open result: %d\n", shell->fd_out);
    if (shell->fd_out == -1)
    {
      printf("DEBUG: About to create file: %s\n", shell->file_name);
      shell->fd_out = open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
      printf("DEBUG: Second open result: %d\n", shell->fd_out);
    }
    printf("DEBUG: About to dup2\n");
    dup2(shell->fd_out, 1);
    printf("DEBUG: About to close fd_out\n");
    close(shell->fd_out);
    printf("DEBUG: Closed fd_out\n");
  }
  
  printf("DEBUG: Checking shell->in_file_name: '%s'\n", shell->in_file_name ? shell->in_file_name : "NULL");
  
  if(shell->in_file_name)
  {
    printf("DEBUG: About to open input file: %s\n", shell->in_file_name);
    shell->fd_in = open(shell->in_file_name, O_RDONLY);
    printf("DEBUG: Input file open result: %d\n", shell->fd_in);
    dup2(shell->fd_in, 0);
    close(shell->fd_in);
  }
  
  printf("DEBUG: Exiting apply_redirections\n");
}

void	process_command(t_shell_control_block *shell)
{
  apply_redirections(shell);
  execute_command(shell);
  if(shell->in_file_name)
    unlink(shell->in_file_name);
}

void execute_command_line_helper(t_shell_control_block *shell)
{
  printf("DEBUG: Entering execute_command_line_helper\n");
  
  // Save original tokenized pointer
  t_token *original_tokenized = shell->tokenized;
  
  // Check if it's a built-in command first
  printf("DEBUG: About to call get_cmd_and_its_args\n");
  get_cmd_and_its_args(shell);
  printf("DEBUG: Finished get_cmd_and_its_args\n");
  
  // Save original file descriptors
  int original_stdin = dup(0);
  int original_stdout = dup(1);
  
  // Restore original tokenized pointer for redirection handling
  shell->tokenized = original_tokenized;
  
  // Apply redirections before executing any command (built-in or not)
  printf("DEBUG: About to call apply_redirections\n");
  apply_redirections(shell);
  printf("DEBUG: Finished apply_redirections\n");
  
  // Check if there's an ambiguous redirect error and return early
  printf("DEBUG: Checking exit_status: %d\n", shell->exit_status);
  if (shell->exit_status == 1)
  {
    printf("DEBUG: Ambiguous redirect detected, returning early\n");
    shell->last_child_pid = -1; // Set to -1 to prevent waitpid from hanging
    return;
  }
  
  printf("DEBUG: No ambiguous redirect, continuing with execution\n");
  
  if (execute_built_in(shell))
  {
    // Restore original file descriptors for built-in commands
    dup2(original_stdin, 0);
    dup2(original_stdout, 1);
    close(original_stdin);
    close(original_stdout);
    // Built-in command executed successfully in parent process
    return;
  }
  
  // Restore original file descriptors before forking
  dup2(original_stdin, 0);
  dup2(original_stdout, 1);
  close(original_stdin);
  close(original_stdout);
  
  // Not a built-in command, fork and execute
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
    // Apply redirections in child process
    shell->tokenized = original_tokenized;
    apply_redirections(shell);
    execute_command(shell);
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
  printf("DEBUG: Starting execute_command_line\n");
  
  while (shell->line_pointer && shell->line_pointer->word)
  {
    printf("DEBUG: Processing command in loop\n");
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
  
  printf("DEBUG: Finished command loop\n");
  
  if (shell->previous_read_end != -1)
    close(shell->previous_read_end);
  
  // Only wait for child process if one was actually created
  if (shell->last_child_pid != -1)
  {
    printf("DEBUG: Waiting for child process %d\n", shell->last_child_pid);
    waitpid(shell->last_child_pid, &status, 0);
    if (WIFEXITED(status))
      shell->exit_status = WEXITSTATUS(status);
    else if(WIFSIGNALED(status))
      shell->exit_status =  128 + WTERMSIG(status);
    else if(WIFSTOPPED(status))
      shell->exit_status = WSTOPSIG(status);
    while (wait(NULL) > 0)
      ;
  }
  else
  {
    printf("DEBUG: No child process to wait for\n");
  }
  
  printf("DEBUG: About to exit execute_command_line\n");
  
  if(shell->exit_status > 128)
    print_exit_signal_message(shell->exit_status);
}
