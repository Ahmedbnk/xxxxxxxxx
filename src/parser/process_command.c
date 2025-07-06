/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:28 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(t_shell *shell)
{
	shell->in_file_name = NULL;
	shell->file_name = NULL;
	handle_all_redir(shell);
	if (shell->exit_status)
		exit((free_all(), 1));
	if (shell->file_name)
	{
		shell->fd_out = ft_open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
		ft_dup2(shell->fd_out, 1);
	}
	if (shell->in_file_name)
	{
		shell->fd_in = ft_open(shell->in_file_name, O_RDONLY, 0);
		ft_dup2(shell->fd_in, 0);
	}
	if (is_builtin(*shell->cmd_and_args))
		execute_builtin_child(shell);
	else
		execute_command(shell);
	if (shell->in_file_name)
		unlink(shell->in_file_name);
}
