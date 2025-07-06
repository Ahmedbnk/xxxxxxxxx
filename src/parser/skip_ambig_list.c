/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_ambig_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:28 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_ambig_list(t_shell *shell)
{
	t_name_lst	*name_lst;

	name_lst = shell->file_name_lst;
	if (!name_lst)
		return ;
	while (name_lst != NULL && name_lst->status != NEW_START)
		name_lst = name_lst->next;
	if (name_lst != NULL && name_lst->status == NEW_START)
		name_lst = name_lst->next;
	shell->file_name_lst = name_lst;
}
