#include "minishell.h"

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
