/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_its_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd_and_its_args(t_shell *sh)
{
	int		i;
	t_token	*ptr;

	sh->cmd_and_args = ft_malloc((cmd_size(sh->tokenze) + 1) * sizeof(t_token),
			1);
	i = 0;
	ptr = sh->tokenze;
	while (ptr)
	{
		if (ptr->type == -1)
			;
		else if (is_symbole(ptr->type))
			ptr = ptr->next;
		else if (ptr->type == WORD)
			sh->cmd_and_args[i++] = ft_strdup(ptr->word, 1);
		else
			break ;
		ptr = ptr->next;
	}
	sh->cmd_and_args[i] = NULL;
	return (sh->cmd_and_args);
}
