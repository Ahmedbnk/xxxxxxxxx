/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:51 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirections(t_shell *shell)
{
	t_token	*original_tokenized;

	original_tokenized = shell->tokenze;
	while (shell->tokenze && shell->tokenze->word != NULL
		&& shell->tokenze->type != PIPE)
	{
		if (is_symbole(shell->tokenze->type))
		{
			if (check_ambiguous_redirection(shell)
				|| process_redirection_tokens(shell))
				return (1);
			shell->tokenze = shell->tokenze->next;
		}
		shell->tokenze = shell->tokenze->next;
	}
	shell->tokenze = original_tokenized;
	return (0);
}
