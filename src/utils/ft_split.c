#include "minishell.h"

static int	w_counter(char const *s, char c)
{
	int	i;
	int	k;
	int	counter;

	i = 0;
	k = 0;
	counter = 0;
	while (s[i])
	{
		if (s[i] == c)
			k = 0;
		else
		{
			if (k == 0)
				counter++;
			k = 1;
		}
		i++;
	}
	return (counter);
}

static void	split_helper(char **splitted, char *s, char c, int i, int k)
{
	int	start;

	start = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
			splitted[k++] = ft_substr(s, start, i - start);
	}
	splitted[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	splitted = ft_malloc((w_counter(s, c) + 1) * sizeof(char *), 1);
	i = 0;
	k = 0;
	split_helper(splitted, (char *)s, c, i, k);
	return (splitted);
}
