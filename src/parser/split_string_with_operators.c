/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string_with_operators.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:00 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_string_with_operators(char **container, char *str, int *j_ptr)
{
	int	i;
	int	start;
	int	j;
	int	op_len;

	i = 0;
	start = 0;
	j = *j_ptr;
	while (str[i])
	{
		op_len = is_operator(str, i);
		if (op_len > 0)
		{
			if (i > start)
				container[j++] = ft_substr(str, start, i - start);
			container[j++] = ft_substr(str, i, op_len);
			i += op_len;
			start = i;
		}
		else
			i++;
	}
	if (start != i)
		container[j++] = ft_substr(str, start, i - start);
	*j_ptr = j;
}
