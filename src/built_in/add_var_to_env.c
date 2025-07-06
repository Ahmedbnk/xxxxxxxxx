/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_to_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:51:06 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:51:06 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_var_to_env(char **env, char *var)
{
	char	**new_env;
	int		i;

	new_env = ft_malloc((len_of_two_d_array(env) + 2) * sizeof(char *), 0);
	i = 0;
	while (*env)
	{
		new_env[i] = ft_strdup(*env, 0);
		i++;
		env++;
	}
	new_env[i++] = ft_strdup(var, 0);
	new_env[i] = NULL;
	return (new_env);
}
