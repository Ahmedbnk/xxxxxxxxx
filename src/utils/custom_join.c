
#include "minishell.h"

void ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	if (!dst || !src)
		return;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return;
}

char	*custom_join(char const *s1, char const *s2)
{
	char	*a;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	a = ft_malloc(len1 + len2 + 1, 1);
	if (s1)
		ft_strcpy(a, s1);
	else
	  a[0] = '\0';
	if (s2)
		ft_strcpy(a + len1, s2);
	return (a);
}
