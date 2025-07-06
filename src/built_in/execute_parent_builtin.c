/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parent_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:51 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_parent_builtin(t_shell *shell)
{
	save_original_fds(shell);
	init_redirection_vars(shell);
	if (parse_redirections(shell))
		return ;
	setup_output_redirection(shell);
	setup_input_redirection(shell);
	execute_builtin(shell);
	restore_original_fds(shell);
}
