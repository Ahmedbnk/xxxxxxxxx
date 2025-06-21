#include "minishell.h"

void minishell_exit(t_shell_control_block *shell, char **args)
{
	(void)shell;
	(void)args;
	exit(0);
} 