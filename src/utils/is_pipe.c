#include "minishell.h"

int	is_pipe(char *str)
{
	if (!str)
		return (0);
	return (ft_strcmp(str, "|") == 0);
}
