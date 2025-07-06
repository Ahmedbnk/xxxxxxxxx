/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_output_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_output_redirection(t_shell *shell)
{
	if (shell->file_name)
	{
		shell->original_stdout = ft_dup(1);
		if (shell->tokenze->type == REDIR_OUT)
			ft_close(ft_open(shell->file_name, O_TRUNC | O_CREAT | O_WRONLY,
					0644));
		else if (shell->tokenze->type == REDIR_APPEND)
			ft_close(ft_open(shell->file_name, O_APPEND | O_CREAT | O_WRONLY,
					0644));
		ft_dup2(ft_open(shell->file_name, O_WRONLY, 0), 1);
	}
}
