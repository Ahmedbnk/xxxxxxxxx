/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string_after_expand.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:54 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:50:32 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_str_after_expand(t_shell *s, int num_of_expantion)
{
	char	*new_after_expand;
	char	*expanded;
	char	*joined;
	int		i;

	new_after_expand = NULL;
	i = 0;
	while (i < num_of_expantion)
	{
		if (num_of_expantion - i == 1)
			s->expand_arr[i].last_one = 1;
		expanded = expand_and_join_node(s, s->expand_arr[i]);
		if (!expanded)
			return (NULL);
		joined = custom_join(new_after_expand, expanded);
		new_after_expand = joined;
		if (!new_after_expand)
			return (NULL);
		i++;
	}
	return (new_after_expand);
}
