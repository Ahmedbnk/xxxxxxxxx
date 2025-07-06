/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*protect_str(t_shell *sh, char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(str) + (ft_strlen(sh->porotect_var)
			* count_number_of_qute(str)) + 1;
	new_str = ft_malloc(size, 1);
	i = 0;
	while (*str)
	{
		j = 0;
		if (is_quote(*str))
		{
			new_str[i++] = *str;
			while (sh->porotect_var[j])
				new_str[i++] = sh->porotect_var[j++];
		}
		else
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
