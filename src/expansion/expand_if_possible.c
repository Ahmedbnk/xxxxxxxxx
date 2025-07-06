/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_if_possible.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:29 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_if_possible(t_shell *s, char *str, int heredoc_flag)
{
	int		i;
	int		offset;
	int		num_of_expantion;
	char	*new_str;

	s->expand_arr = NULL;
	i = 0;
	offset = 0;
	num_of_expantion = how_many_dallar_to_expand(str, heredoc_flag);
	if (num_of_expantion == 0)
		return (ft_strdup(str, 1));
	allocat_and_init(&(s->expand_arr), num_of_expantion, heredoc_flag);
	while (i < num_of_expantion)
	{
		string_before_dollar(&(s->expand_arr[i]), str, &offset);
		string_to_expand(&(s->expand_arr[i]), str, &offset);
		string_after_dollar(&(s->expand_arr[i]), str, &offset);
		i++;
	}
	new_str = new_str_after_expand(s, num_of_expantion);
	return (new_str);
}
