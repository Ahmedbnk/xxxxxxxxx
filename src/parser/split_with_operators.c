/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_operators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:00 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_with_operators(char **splitted)
{
	int		len;
	int		i;
	int		j;
	char	**container;

	len = calculate_all_symboles_operators(splitted);
	i = 0;
	j = 0;
	while (splitted[i])
		i++;
	container = ft_malloc(sizeof(char *) * ((i + 2 * len) + 1), 1);
	i = 0;
	j = 0;
	while (splitted[i])
	{
		if (does_string_has_operators(splitted[i]))
			split_string_with_operators(container, splitted[i], &j);
		else
			container[j++] = ft_strdup(splitted[i], 1);
		i++;
	}
	container[j] = NULL;
	return (container);
}
