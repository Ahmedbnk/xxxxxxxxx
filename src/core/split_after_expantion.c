/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_after_expantion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:18:09 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_export_range(char **matrix, char *str, int *start, int *end)
{
	int	i;

	i = 0;
	*start = 0;
	*end = 0;
	while (matrix[i])
	{
		if (are_eq(matrix[i], "|"))
			*start = i + 1;
		else if (are_eq(matrix[i], str))
		{
			*end = i;
			return ;
		}
		i++;
	}
}

int	is_export_before(t_shell *sh, char *str)
{
	int		i;
	int		end;
	char	**ptr;

	get_export_range(sh->splitted, str, &i, &end);
	ptr = copy_2d(sh->splitted, 1);
	while (ptr[i])
	{
		rm_quotes_from_one_str(sh, &ptr[i]);
		if (is_redirection(ptr[i]))
			i++;
		else if (are_eq(ptr[i], "export"))
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}

void	split_after_expantion(t_shell *sh, char *str, char *old_str)
{
	int		i;
	char	**ptr;

	i = 0;
	if (!*str || is_there_invalid_expantion(sh, str, old_str))
		return ;
	if (is_export_before(sh, str))
	{
		add_token_to_lst(&sh->tokenze, new_token(str, WORD));
		return ;
	}
	ptr = customized_split(str);
	while (ptr[i])
	{
		rm_quotes_from_one_str(sh, &ptr[i]);
		add_token_to_lst(&sh->tokenze, new_token(ptr[i], WORD));
		i++;
	}
}
