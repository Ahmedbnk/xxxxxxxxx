#include "minishell.h"

t_list	**get_garbage_pointer(void)
{
	static t_list	*garbage_list = NULL;

	return (&garbage_list);
}

void	free_memory(t_list *lst)
{
	t_list	*next_node;

	if (!lst)
    return;
	while (lst != NULL)
	{
		next_node = ((t_list *)lst)->next;
		free(((t_list *)lst)->content);
		free(lst);
		lst = next_node;
	}
}

void	*ft_malloc(size_t size)
{
	t_list	**garbage_list;
	void	*pointer;
	t_list	*new_node;

	garbage_list = get_garbage_pointer();
	pointer = malloc(size);
	if (!pointer)
		free_memory(*garbage_list);
	new_node = garbage_collection_lstnew(pointer);
	if (!new_node)
	{
		free(pointer);
		free_memory(*garbage_list);
	}
	ft_lstadd_back(garbage_list, new_node);
	return (pointer);
}
