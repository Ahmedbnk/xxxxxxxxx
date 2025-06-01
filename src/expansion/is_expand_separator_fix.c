
#include "minishell.h"

int	is_expend_seperator(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}
