#include "minishell.h"

char	*ft_strdup(const char *s, int flag)
{
	char	*a;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	a = ft_malloc((ft_strlen(s) + 1) * sizeof(char), flag);
	while (s[i])
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
