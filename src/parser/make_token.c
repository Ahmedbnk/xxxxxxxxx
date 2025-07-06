/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:00 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(char **splitted)
{
	int	i;
	int	size;

	if (!splitted || !splitted[0])
		return (0);
	size = len_of_two_d_array(splitted);
	i = 0;
	while (i < size)
	{
		if (is_pipe(splitted[i]))
		{
			if (validate_pipe_syntax(splitted, i))
				return (1);
		}
		else if (is_red_symbole(splitted[i]))
		{
			if (validate_redirection_syntax(splitted, i))
				return (1);
		}
		i++;
	}
	if (is_pipe(splitted[size - 1]) || is_red_symbole(splitted[size - 1]))
		return (print(2, "syntax error near unexpected str `newline'\n"), 1);
	return (0);
}
