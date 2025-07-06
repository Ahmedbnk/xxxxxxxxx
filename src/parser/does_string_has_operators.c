/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_string_has_operators.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:59 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	does_string_has_operators(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_operator(str, i))
			return (1);
		i++;
	}
	return (0);
}
