/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 16:47:20 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line(t_shell *sh)
{
	sh->porotect_var = generate_random_name();
	sh->splitted = customized_split(sh->line);
	sh->splitted = split_with_operators(sh->splitted);
	if (check_syntax_error(sh->splitted))
	{
		sh->exit_status = 2;
		free(sh->line);
		return (1);
	}
	get_files_name(sh);
	expand_and_split(sh);
	return (0);
}
