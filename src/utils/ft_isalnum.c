#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c == '_' || c == '?')
		return (1);
	else
		return (0);
}
