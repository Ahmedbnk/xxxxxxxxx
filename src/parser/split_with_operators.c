#include "minishell.h"

static int	is_operator(char *str, int i)
{
	if (is_between_quotes(str, i))
		return (0);
	if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
			+ 1] == '<'))
		return (2);
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

static int	does_string_has_operators(char *str)
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

static int	calculate_all_symboles_operators(char **splitted)
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
			if (!is_between_quotes(splitted[i], j) && strchr("<>|",
					splitted[i][j]))
				number++;
			j++;
		}
		i++;
	}
	return (number);
}

static void	split_string_with_operators(char **container, char *str, int *j_ptr)
{
	int	i;
	int	start;
	int	j;
	int	op_len;

	i = 0;
	start = 0;
	j = *j_ptr;
	while (str[i])
	{
		op_len = is_operator(str, i);
		if (op_len > 0)
		{
			if (i > start)
				container[j++] = ft_substr(str, start, i - start);
			container[j++] = ft_substr(str, i, op_len);
			i += op_len;
			start = i;
		}
		else
			i++;
	}
  if(start != i)
    container[j++] = ft_substr(str, start, i - start);
	*j_ptr = j;
}

char	**split_with_operators(char **splitted)
{
	int		len;
	int		i;
	int		j;
	char	**container;

	len = calculate_all_symboles_operators(splitted);
	i = 0;
	j = 0;
	while (splitted[i])
		i++;
	container = ft_malloc(sizeof(char *) * ((i + 2 * len) + 1), 1);
	i = 0;
	j = 0;
	while (splitted[i])
	{
		if (does_string_has_operators(splitted[i]))
			split_string_with_operators(container, splitted[i], &j);
		else
			container[j++] = ft_strdup(splitted[i], 1);
		i++;
	}
	container[j] = NULL;
	return (container);
}
