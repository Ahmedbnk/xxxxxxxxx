#include "minishell.h"

int	should_i_expand(char *str, int index)
{
	int	quote;

	quote = 0;
	if (quote == SINGLE_Q || str[index + 1] == '\0' || str[index
		+ 1] == SINGLE_Q || str[index + 1] == DOUBLE_Q)
		return (0);
	return (1);
}
