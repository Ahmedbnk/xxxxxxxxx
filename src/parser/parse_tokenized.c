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

void	skip_command(t_data **tokenized_address)
{
  t_data	*tokenized;

  tokenized = *tokenized_address;
  while (tokenized && tokenized->word != NULL && tokenized->type != PIPE)
    tokenized ++;
  *tokenized_address = tokenized;
}

void	print_command(t_data *tokenized)
{
  while (tokenized && tokenized->word != NULL && tokenized->type != PIPE)
  {
    printf("%s ", tokenized->word);
    tokenized ++;
  }
  printf("\n");
}

static void handle_heredoc_redirection(t_data *tokenized, char **in_file_name)
{
    if (tokenized->type == HEREDOC)
        *in_file_name = tokenized->heredoc_file_name;
}

static void handle_input_redirection(t_data *tokenized, char **in_file_name)
{
    if (tokenized->type == REDIR_IN)
        handle_redir_in((tokenized + 1)->word, in_file_name);
}

static void handle_output_redirection(t_data *tokenized, char **file_name)
{
    if (tokenized->type == REDIR_OUT)
        handle_redir_out((tokenized + 1)->word, file_name);
    else if (tokenized->type == REDIR_APPEND)
        handle_append((tokenized + 1)->word, file_name);
}

static void handle_file_redirections(t_data *tokenized, char **in_file_name, char **file_name)
{
    while (tokenized && tokenized->word != NULL && tokenized->type != PIPE)
    {
        handle_heredoc_redirection(tokenized, in_file_name);
        handle_input_redirection(tokenized, in_file_name);
        handle_output_redirection(tokenized, file_name);
        tokenized++;
    }
}

static void	setup_file_descriptors(char *in_file_name, char *file_name)
{
  int fd_out;
  int fd_in;

  if (file_name)
  {
    fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd_out, 1);
    close(fd_out);
  }
  if(in_file_name)
  {
    fd_in = open(in_file_name, O_CREAT | O_RDONLY, 0644);
    dup2(fd_in, 0);
    close(fd_in);
  }
}

static void cleanup_redirection_files(char *in_file_name)
{
    if (in_file_name)
        unlink(in_file_name);
}

static void prepare_command_execution(t_shell *shell, t_data *tokenized, 
                                    char **in_file_name, char **file_name, 
                                    char ***command_and_args)
{
    *in_file_name = NULL;
    *file_name = NULL;
    *command_and_args = get_cmd_and_its_args(tokenized);
    if (!*command_and_args)
        shell->error_code = 1;
}

void process_command(t_shell *shell, t_data *tokenized)
{
    char *in_file_name;
    char *file_name;
    char **command_and_args;

    prepare_command_execution(shell, tokenized, &in_file_name, &file_name, &command_and_args);
    if (shell->error_code)
        return;

    handle_file_redirections(tokenized, &in_file_name, &file_name);
    setup_file_descriptors(in_file_name, file_name);
    execute_command(shell, command_and_args[0], command_and_args);
    cleanup_redirection_files(in_file_name);
    free_2d_array(command_and_args);
}

static void setup_pipe_redirections(int previous_read_end)
{
    if (previous_read_end != -1)
    {
        dup2(previous_read_end, 0);
        close(previous_read_end);
    }
}

static void setup_pipe_write_end(int *arr, int previous_read_end)
{
    close(previous_read_end);
    close(arr[0]);
    dup2(arr[1], 1);
    close(arr[1]);
}

static void handle_child_process(t_shell *shell, t_data *start, t_data *tokenized, 
                               int *arr, int previous_read_end)
{
    if (previous_read_end != -1)
        setup_pipe_redirections(previous_read_end);
    if (tokenized && tokenized->type == PIPE)
        setup_pipe_write_end(arr, previous_read_end);
    process_command(shell, start);
    exit(0);
}

static void handle_parent_process(int *arr, int *previous_read_end)
{
    if (*previous_read_end != -1)
        close(*previous_read_end);
    if (arr[1] != -1)
    {
        close(arr[1]);
        *previous_read_end = arr[0];
    }
}

void execute_command_line(t_shell *shell, t_data *tokenized)
{
    int arr[2];
    int previous_read_end;
    t_data *start;

    previous_read_end = -1;
    while (tokenized && tokenized->word)
    {
        start = tokenized;
        skip_command(&tokenized);
        
        if (tokenized && tokenized->type == PIPE)
            pipe(arr);
        
        if (fork() == 0)
            handle_child_process(shell, start, tokenized, arr, previous_read_end);
        
        handle_parent_process(arr, &previous_read_end);
        
        if (tokenized && tokenized->type == PIPE)
            tokenized++;
    }
    
    if (previous_read_end != -1)
        close(previous_read_end);
    while (wait(NULL) > 0);
}
