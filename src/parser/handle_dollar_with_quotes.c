/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_with_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**handle_dollar_with_quotes(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		if (are_eq(splitted[i], "<<"))
			i++;
		else
			splitted[i] = remove_dollar_if_quotes_after_it(splitted[i]);
		i++;
	}
	return (splitted);
}
