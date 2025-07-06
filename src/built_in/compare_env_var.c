/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:51:21 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:50:17 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_env_var(char *var1, char *var2)
{
	int	i;

	i = 0;
	while (var1[i] && var2[i])
	{
		if (var1[i] == '=' && var1[i] != var2[i])
			return (0);
		if (var1[i] == '=' && var1[i] == var2[i])
			return (1);
		if (var1[i] != var2[i])
			return (0);
		i++;
	}
	return (1);
}
