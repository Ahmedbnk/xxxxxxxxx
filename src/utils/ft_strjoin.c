#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		i;
	int		k;

	if (!s1)
		return ((char *)s2);
  if(!s2)
    return ((char*)s1);
	a = ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
	i = 0;
	while (i < (int)ft_strlen(s1))
	{
		a[i] = s1[i];
		i++;
	}
	k = 0;
	while (k < (int)ft_strlen(s2))
	{
		a[i] = s2[k];
		i++;
		k++;
	}
	a[i] = '\0';
	return (a);
}
// we cast with int because ft_strlen return size_t type.
