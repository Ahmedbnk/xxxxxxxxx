/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_i_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:54 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 19:03:37 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_i_expand(char *str, int index)
{
	char	quote;

	quote = 0;
	quote = is_between_quotes(str, index);
	if (quote == SINGLE_Q || str[index + 1] == '\0' || str[index
		+ 1] == SINGLE_Q || str[index + 1] == DOUBLE_Q)
		return (0);
	else
		return (1);
}
