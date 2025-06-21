#include "minishell.h"

int	is_between_quotes(char *line, int index)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (i < index)
	{
		if ((line[i] == SINGLE_Q || line[i] == DOUBLE_Q) && quote == 0)
			quote = line[i];
		else if ((line[i] == SINGLE_Q || line[i] == DOUBLE_Q)
			&& line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

