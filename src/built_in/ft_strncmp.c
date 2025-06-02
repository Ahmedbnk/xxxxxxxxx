
#include "minishell.h"

int	ft_strncmp(const char *big, const char *little, size_t n)
{
	size_t	i;

	i = 0;
	if (!big || !little)
		return (0);
	if (n == 0)
		return (0);
	while ((big[i] || little[i]) && i < n)
	{
		if (big[i] != little[i])
		{
			return ((unsigned char)big[i] - (unsigned char)little[i]);
		}
		i++;
	}
	return (0);
}
