#include "minishell.h"

int	is_operator(char *str, int i)
{
	if (is_between_quotes(str, i))
		return (0);
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<'))
		return (2);
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

int	does_string_has_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_operator(str, i))
			return (1);
		i++;
	}
	return (0);
}

int	calculate_all_symboles_operators(char **splitted)
{
	int	i;
	int	j;
	int	number;

	i = 0;
	j = 0;
	number = 0;
	while (splitted[i])
	{
		j = 0;
		while (splitted[i][j])
		{
			if (!is_between_quotes(splitted[i], j) && strchr("<>|", splitted[i][j]))
				number++;
			j++;
		}
		i++;
	}
	return (number);
} 