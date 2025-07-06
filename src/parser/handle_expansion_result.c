/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion_result.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_expansion_result(t_shell *sh, t_name_lst *ptr,
		char *str)
{
	(void)sh;
	if (are_eq(ptr->file_name, str))
		return ;
	if (is_there_a_space_outside_q(str))
		ptr->status = AMBIGUOUS;
	ptr->file_name = str;
}
