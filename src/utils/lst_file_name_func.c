/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file_name_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:03 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:03 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_name_lst	*new_file_name(void *name_of_file, int status)
{
	t_name_lst	*node;

	node = ft_malloc(sizeof(t_name_lst), 1);
	if (!node)
		return (NULL);
	node->file_name = name_of_file;
	node->status = status;
	node->next = NULL;
	return (node);
}

void	add_back_file_name(t_name_lst **lst, t_name_lst *new)
{
	t_name_lst	*c_node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	c_node = *lst;
	while (c_node->next)
		c_node = c_node->next;
	c_node->next = new;
}
