/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirection_tokens.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_redirection_tokens(t_shell *shell)
{
	if (shell->tokenze->type == HEREDOC)
		shell->in_file_name = shell->tokenze->heredoc_file_name;
	else if (shell->tokenze->type == REDIR_IN)
		handle_redir_in((shell->tokenze->next)->word, &(shell->in_file_name),
			shell);
	else if (shell->tokenze->type == REDIR_OUT)
		handle_redir_out((shell->tokenze->next)->word, &(shell->file_name),
			shell);
	else if (shell->tokenze->type == REDIR_APPEND)
		handle_append((shell->tokenze->next)->word, &(shell->file_name), shell);
	if (shell->exit_status)
		return (1);
	return (0);
}
