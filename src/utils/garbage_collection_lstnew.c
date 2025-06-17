#include "minishell.h"

t_list	*garbage_collection_lstnew(void *content, int flag)
{
	t_list	*node;

	(void)flag; // Suppress unused parameter warning
	node = malloc(sizeof(t_list));
	if(!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return (node);
}
