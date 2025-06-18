#include "minishell.h"

t_list	*garbage_collection_lstnew(void *content, int flag)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
  if(!node)
    free_memory((t_list **)get_garbage_pointer(flag));
	node->content = content;
	node->next = NULL;
	return (node);
}
