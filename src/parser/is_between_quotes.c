#include "minishell.h"

int	is_between_quotes(char *line, int index)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]) && quote == 0)
			quote = line[i];
		else if (is_quote(line[i]) && line[i] == quote)
			quote = 0;
		if (i == index)
			return (quote);
		i++;
	}
	return (0);
}

