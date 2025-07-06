/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_shell_block(t_shell *sh, int ac, char **av)
{
	(void)ac;
	(void)av;
	sh->env_cpy = NULL;
	sh->line = NULL;
	sh->splitted = NULL;
	sh->file_name_lst = NULL;
	sh->tokenze = NULL;
	sh->cmd_and_args = NULL;
	sh->env_of_export = NULL;
	sh->exit_status = 0;
	sh->exit_status_flag = 0;
}
