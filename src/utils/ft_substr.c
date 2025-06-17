#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", 1));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)ft_malloc(sizeof(char) * (len + 1), 1);
	if (!substr)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len && s[i])
	{
		substr[j] = s[i];
		i++;
		j++;
	}
	substr[j] = '\0';
	return (substr);
}
