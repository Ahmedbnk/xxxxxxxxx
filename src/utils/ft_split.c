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
		{
			k = 0;
		}
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

char	**ft_split(char const *s, char c)
{
	char	**splitted;

	int (i), (k), (start);
	if (!s)
		return (NULL);
	splitted = ft_malloc((w_counter(s, c) + 1) * sizeof(char *),1);
	i = 0;
	k = 0;
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
	return (splitted);
}
// #include <stdio.h>
// int	main(void)
// {
// 	char s[] = "hello world";
// 	// char *str = NULL;
// 	char **splitted = ft_split(NULL, ' ');
// 	if (splitted == NULL)
// 		printf("nadi");
// 	else
// 		printf("%s\n", splitted[0]);
// 	return (0);
// }
