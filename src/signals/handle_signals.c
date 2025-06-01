#include "minishell.h"


void	sigint_handler_in_child(int signo)
{
	if (signo == SIGINT)
	{
		wait(NULL);
		exit(0);
	}
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		wait(NULL);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	handle_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals_in_child(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler_in_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
