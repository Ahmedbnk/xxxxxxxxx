/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_protected.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:02 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_protected(t_shell *sh, char *str, int index)
{
	char	*ptr;
	int		i;
	int		len;

	ptr = sh->porotect_var;
	i = 0;
	index += 1;
	len = ft_strlen(ptr);
	while (i < len)
	{
		if (str[index] != ptr[i])
			return (0);
		index++;
		i++;
	}
	return (1);
}
