#include "../../include/minishell.h"

int	ft_exit(char **args)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(0);
	exit_code = ft_atoi(args[1]);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit(exit_code);
	return (0);
} 