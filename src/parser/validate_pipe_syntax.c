/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_pipe_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:01 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:01 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_pipe_syntax(char **splitted, int i)
{
	if (i == 0 || !splitted[i + 1])
		return (print(2, "syntax error near unexpected str `|'\n"), 1);
	if (is_red_symbole(splitted[i - 1]) || is_pipe(splitted[i - 1]))
		return (print(2, "syntax error near unexpected str `|'\n"), 1);
	return (0);
}
