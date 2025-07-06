/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:02 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:02 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*a;
	unsigned int	n;

	if (s == NULL)
		return (NULL);
	i = 0;
	n = ft_strlen(s);
	if (start >= n)
		return (ft_strdup("", 1));
	if (len > n - start)
		len = n - start;
	a = ft_malloc(len + 1, 1);
	if (!a)
		return (NULL);
	while (i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
// int main()
// {
// 	char a[] = "hello world";
// 	char *s = ft_substr(a, 6, 5);
// 	printf("%s\n", s);
// 	return (0);
// }
