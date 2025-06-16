#include "minishell.h"

int	is_between_quotes(char *line, int index)
{
	int	i;
	int	quote;

	// Safety checks
	if (!line || index < 0)
		return 0;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == single_q || line[i] == double_q) && quote == 0)
			quote = line[i];
		else if ((line[i] == single_q || line[i] == double_q)
			&& line[i] == quote)
			quote = 0;
		if (i == index)
			return (quote);
		i++;
	}
	return (0);
}
