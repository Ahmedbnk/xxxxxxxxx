/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:51 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 16:35:50 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_shell *s, char **to_export)
{
	int	state;

	state = 0;
	if (!to_export || !*to_export)
		return ((sort_env(s->env_of_export), 0));
	while (*to_export)
	{
		if (!is_valid_var(*to_export))
			state = 1;
		else
		{
			if (find_and_update_var(s->env_of_export, *to_export))
				;
			else
				s->env_of_export = add_var_to_env(s->env_of_export, *to_export);
			if (!is_it_key_value(*to_export))
				;
			else if (find_and_update_var(s->env_cpy, *to_export))
				;
			else
				s->env_cpy = add_var_to_env(s->env_cpy, *to_export);
		}
		to_export++;
	}
	return (state);
}
