/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_original_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_original_fds(t_shell *shell)
{
	shell->original_stdin = ft_dup(0);
	shell->original_stdout = ft_dup(1);
}
