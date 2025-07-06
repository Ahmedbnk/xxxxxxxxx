/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:02 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:02 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**get_garbage_pointer(int flag)
{
	static t_list	*garbage_list = NULL;
	static t_list	*env_colloctor = NULL;

	if (flag)
		return (&garbage_list);
	return (&env_colloctor);
}

void	free_memory(t_list **list_pointer)
{
	t_list	*lst;
	t_list	*next_node;

	lst = *list_pointer;
	if (!lst)
		return ;
	while (lst != NULL)
	{
		next_node = ((t_list *)lst)->next;
		free(((t_list *)lst)->content);
		free(lst);
		lst = next_node;
	}
	*list_pointer = NULL;
}

void	*ft_malloc(size_t size, int falg)
{
	t_list	**garbage_list;
	void	*pointer;
	t_list	*new_node;

	garbage_list = get_garbage_pointer(falg);
	pointer = malloc(size);
	if (!pointer)
		free_memory(garbage_list);
	new_node = garbage_collection_lstnew(pointer, falg);
	if (!new_node)
	{
		free(pointer);
		free_memory(garbage_list);
	}
	ft_lstadd_back(garbage_list, new_node);
	return (pointer);
}
