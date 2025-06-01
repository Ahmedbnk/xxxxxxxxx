
#include "minishell.h"

int	is_expand_separator(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}
