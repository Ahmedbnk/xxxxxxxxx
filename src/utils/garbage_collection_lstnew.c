#include "minishell.h"

t_list	*garbage_collection_lstnew(void *content, int flag)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list), flag);
	if(!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return (node);
}
