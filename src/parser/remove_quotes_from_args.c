/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_from_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:28 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_quotes_from_one_str(t_shell *sh, char **line)
{
	char	*line_without_quotes;

	line_without_quotes = ft_malloc(ft_strlen(*line) + 1, 1);
	rm_quotes_from_one_str_helper(sh, *line, &line_without_quotes);
	*line = line_without_quotes;
}
