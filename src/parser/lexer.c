#include "minishell.h"

static int	ft_w_counter(char const *s)
{
	int	i;
	int	k;
	int	counter;

	i = 0;
	k = 0;
	counter = 0;
	while (s[i])
	{
		if (is_space(s[i]))
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

static void	split_helper(char **splitted, char *s, int i, int k)
{
	int	start;

	start = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		start = i;
		while (s[i] && (!is_space(s[i]) || (is_space(s[i])
					&& is_between_quotes(s, i))))
			i++;
		if (i > start)
			splitted[k++] = ft_substr(s, start, i - start);
	}
	splitted[k] = NULL;
}

char	**customized_split(char const *s)
{
	char	**result;
	int		i;
	int		j;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
			word_count++;
		while (s[i] && !is_space(s[i]))
			i++;
	}
	result = ft_malloc((word_count + 1) * sizeof(char *), 1);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			result[j] = ft_strdup(s + i, 1);
			j++;
		}
		while (s[i] && !is_space(s[i]))
			i++;
	}
	result[j] = NULL;
	return (result);
}

//#include <stdio.h>
//  int	main(void)
//  {
//    char *line = readline(">>> :");
//    char **splitted = customized_split(line);
//    for(int i = 0; splitted[i];i++)
//    {
//      remove_quotes(&splitted[i]);
//      printf("%s\n", splitted[i]);
//    }
//    return (0);
//  }
