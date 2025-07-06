/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection_lstnew.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:02 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:02 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*garbage_collection_lstnew(void *content, int flag)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		free_memory((t_list **)get_garbage_pointer(flag));
	node->content = content;
	node->next = NULL;
	return (node);
}
