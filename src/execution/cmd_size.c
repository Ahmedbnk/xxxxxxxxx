/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:53 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_size(t_token *tokenz)
{
	int	size;

	size = 0;
	while (tokenz)
	{
		if (is_redirection(tokenz->word) || tokenz->type == HEREDOC)
		{
			tokenz = tokenz->next;
		}
		else if (tokenz->type == WORD)
			size++;
		tokenz = tokenz->next;
	}
	return (size);
}
