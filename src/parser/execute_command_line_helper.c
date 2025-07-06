/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_line_helper.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:01 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_line_helper(t_shell *shell)
{
	int	p_id;

	get_cmd_and_its_args(shell);
	p_id = fork();
	if (p_id == 0)
	{
		signal(SIGINT, shell->old_sigint_handler);
		signal(SIGQUIT, shell->old_sigquit_handler);
		if (shell->previous_read_end != -1)
		{
			ft_dup2(shell->previous_read_end, 0);
			ft_close(shell->previous_read_end);
		}
		if (shell->line_pointer && shell->line_pointer->type == PIPE)
		{
			ft_close(shell->previous_read_end);
			ft_close(shell->arr[0]);
			ft_dup2(shell->arr[1], 1);
			ft_close(shell->arr[1]);
		}
		process_command(shell);
		exit((free_all(), 0));
	}
	else
		shell->last_child_pid = p_id;
}
