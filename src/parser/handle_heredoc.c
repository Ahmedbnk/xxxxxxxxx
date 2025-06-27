#include "minishell.h"

int does_it_has_qoutes(char *str)
{
  if(!str)
    return 0;
  while(*str)
  {
    if(is_quote(*str))
      return 1;
    str++;
  }
  return 0;
}

void create_heredoc(t_shell_control_block *s ,t_token *tokenze)
{
  int fd;
  char *str = NULL;
  char *buffer = NULL;
  int has_qoutes;

  tokenze->heredoc_file_name = ft_strjoin("/tmp/", generate_random_name());
  tokenze->delimiter = tokenze->next->word;
  has_qoutes = does_it_has_qoutes(tokenze->delimiter);
  rm_quotes_from_one_str(s, &(tokenze->delimiter));
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  int rc = fork();
  if(rc == 0)
  {
    // Child process - restore default signal handling for heredoc
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    handle_signals(2);
    while(1)
    {
      str = readline("> ");
      if(str == NULL)
      {
        print_error("warning: here-document delimited by end-of-file (wanted `%s')\n", tokenze->delimiter);
        break;
      }
      if(are_they_equal(str, tokenze->delimiter))
        break;
      if(!has_qoutes)
        str = expand_if_possible(s, str, 1);
      buffer = ft_strjoin(buffer, ft_strjoin(str, "\n"));
    }
    fd = open(tokenze->heredoc_file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    write(fd,buffer,ft_strlen(buffer));
    close(fd);
    exit(1);
  }
  else
    wait(NULL);
}

void create_all_heredocs(t_shell_control_block *shell)
{
  t_token *ptr;

  ptr = shell->tokenze;
    while(ptr)
    {
      if(ptr -> type == HEREDOC)
        create_heredoc(shell, ptr);
      ptr = ptr->next;
    }
}
