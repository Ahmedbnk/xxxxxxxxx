#include "minishell.h"

static int g_signal = 0;

void	sigint_handler_in_child(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
	}
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signal = SIGINT;
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
		g_signal = SIGQUIT;
		if (isatty(STDIN_FILENO))
			write(1, "Quit (core dumped)\n", 19);
	}
}

void	handle_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	g_signal = 0;
	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	handle_signals_in_child(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	g_signal = 0;
	sa_int.sa_handler = sigint_handler_in_child;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int	get_signal(void)
{
	return (g_signal);
}

void	reset_signal(void)
{
	g_signal = 0;
}
