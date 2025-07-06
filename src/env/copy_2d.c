/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:11:18 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_2d(char **env, int mode)
{
	int		i;
	char	**my_env;

	my_env = ft_malloc((len_of_two_d_array(env) + 1) * sizeof(char *), mode);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup((const char *)env[i], 0);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}
