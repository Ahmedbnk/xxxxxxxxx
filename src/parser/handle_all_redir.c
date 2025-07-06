/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_all_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 16:49:21 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_all_redir(t_shell *shell)
{

	while (shell->tokenze && shell->tokenze->word != NULL
		&& shell->tokenze->type != PIPE)
	{
		if (is_redirection(shell->tokenze->word))
		{
			if (shell->tokenze->type == HEREDOC)
				shell->in_file_name = shell->tokenze->heredoc_file_name;
			else if (shell->tokenze->type == REDIR_IN)
				handle_redir_in((shell->tokenze->next)->word,
					&(shell->in_file_name), shell);
			else if (shell->tokenze->type == REDIR_OUT)
				handle_redir_out((shell->tokenze->next)->word,
					&(shell->file_name), shell);
			else if (shell->tokenze->type == REDIR_APPEND)
				handle_append((shell->tokenze->next)->word, &(shell->file_name),
					shell);
			if (shell->exit_status)
				return ;
		}
		shell->tokenze = shell->tokenze->next;
	}

}
