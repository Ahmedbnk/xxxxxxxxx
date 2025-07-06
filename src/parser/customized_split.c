/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customized_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:44:41 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	counter(char const *s)
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

char	**customized_split(char const *s)
{
	char	**splitted;
	int		i;
	int		k;

	if (*s == '\0' || is_all_spaces(s))
	{
		splitted = ft_malloc(2 * sizeof(char *), 1);
		splitted[0] = ft_strdup("", 1);
		splitted[1] = NULL;
		return (splitted);
	}
	if (!s)
		return (NULL);
	splitted = ft_malloc((counter(s) + 1) * sizeof(char *), 1);
	i = 0;
	k = 0;
	split_helper(splitted, (char *)s, i, k);
	return (splitted);
}
