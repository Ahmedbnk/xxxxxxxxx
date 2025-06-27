#include "minishell.h"

void heredoc_signal(int signo)
{
  if(signo)
  {
	  write(1, "\n", 1);
    exit(1);
  }
}

void	sigint_child_handler(int signo)
{
	(void ) signo;
	  while (wait(NULL) > 0);
	write(1, "\n", 1);
	signal(SIGINT, SIG_IGN);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	handle_signals(int flag)
{
	struct sigaction sa;

	if(flag == 0)
		sa.sa_handler = sigint_handler;
	else if(flag == 1)
		sa.sa_handler = sigint_child_handler;
  else if(flag == 2)
		sa.sa_handler = heredoc_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

