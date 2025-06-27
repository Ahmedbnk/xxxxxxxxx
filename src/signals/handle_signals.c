#include "minishell.h"

// Global variable for signal handling (as required by subject)
int g_signal_received = 0;

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
		g_signal_received = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		g_signal_received = SIGQUIT;
		// In interactive mode, ctrl-\ does nothing
		// This handler is mainly for child processes
	}
}

void	handle_signals(int flag)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	if(flag == 0)
	{
		// Interactive mode - parent shell
		sa_int.sa_handler = sigint_handler;
		sa_quit.sa_handler = sigquit_handler;
	}
	else if(flag == 1)
	{
		// Parent waiting for child
		sa_int.sa_handler = sigint_child_handler;
		sa_quit.sa_handler = sigquit_handler;
	}
	else if(flag == 2)
	{
		// Heredoc mode
		sa_int.sa_handler = heredoc_signal;
		sa_quit.sa_handler = heredoc_signal;
	}
	
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

