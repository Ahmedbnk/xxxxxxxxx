/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_after_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:54 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:54 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_after_dollar(t_expand *data, char *str, int *offset)
{
	int	start;
	int	end;

	if (!str)
		return ;
	start = *offset;
	end = *offset;
	while (str[end])
		end++;
	if (end > start)
		data->after_dollar = ft_substr(str, start, end - start);
}
