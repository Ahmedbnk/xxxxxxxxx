/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_invalid_expantion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_invalid_expantion(t_shell *sh, char *str,
		char *old_str)
{
	if (!is_it_valid_dollar(old_str))
	{
		rm_quotes_from_one_str(sh, &str);
		add_token_to_lst(&sh->tokenze, new_token(str, WORD));
		return (1);
	}
	return (0);
}
