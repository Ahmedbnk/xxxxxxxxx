/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_split_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_and_split_helper(t_shell *sh, int index)
{
	char	*ptr;

	ptr = expand_if_possible(sh, sh->splitted[index], 0);
	if (*ptr == 0)
	{
		add_token_to_lst(&sh->tokenze, new_token(ptr, -1));
		return ;
	}
	if (are_eq(sh->splitted[index], ptr))
	{
		rm_quotes_from_one_str(sh, &ptr);
		add_token_to_lst(&sh->tokenze, new_token(ptr, get_token_type(ptr)));
	}
	else
		split_after_expantion(sh, ptr, sh->splitted[index]);
}
