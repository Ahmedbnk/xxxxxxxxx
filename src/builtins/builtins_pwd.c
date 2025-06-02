#include "../../include/minishell.h"
#include <limits.h>

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2), 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
} 