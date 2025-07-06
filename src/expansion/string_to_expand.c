/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:58 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:58 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_to_expand(t_expand *data, char *str, int *offset)
{
	int	start;

	if (!str)
		return ;
	start = *offset;
	while (str[*offset])
	{
		if (str[*offset] == '$' && start == (*offset))
			(*offset)++;
		if (str[*offset] == '?' && str[(*offset) - 1] == '$')
		{
			(*offset)++;
			break ;
		}
		else if (!ft_isalnum(str[*offset]) || (str[*offset] == '$'
				&& (data->heredoc_flag || should_i_expand(str, *offset))))
			break ;
		(*offset)++;
	}
	data->to_expand = ft_substr(str, start, *offset - start);
}
