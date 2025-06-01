
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
	a = ft_malloc(len1 + len2 + 1);
	if (s1)
		ft_strcpy(a, s1);
	else
	  a[0] = '\0';
	if (s2)
		ft_strcpy(a + len1, s2);
	return (a);
}

// char	*custom_join(char const *s1, char const *s2)
//{
//	char	*a;
//	int		i;
//	int		k;
//
//	if (!s1 && !s2)
//		return (NULL);
//  else if (!s1)
//    return ((char *)s2);
//  else if(!s2)
//    return ((char *)s1);
//	a = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
//	if (!a)
//		return (NULL);
//	i = 0;
//	while (i < (int)ft_strlen(s1))
//  {
//		a[i] = s1[i];
//    i++;
//  }
//	k = 0;
//	while (k < (int)ft_strlen(s2))
//		a[i++] = s2[k++];
//	a[i] = '\0';
//	return (a);
//}

