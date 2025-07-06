/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_join_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_and_join_node(t_shell *s, t_expand data)
{
	char	*path;
	char	*the_joined_node;
	char	*rest;

	if (data.to_expand != NULL)
	{
		if (are_eq(data.to_expand, "$?"))
			path = ft_itoa(s->exit_status);
		else
			path = ft_strdup(get_env_var(s, data), 1);
		the_joined_node = custom_join(data.befor_dollar, path);
	}
	if (data.last_one)
	{
		rest = custom_join(the_joined_node, data.after_dollar);
		return (rest);
	}
	return (the_joined_node);
}
