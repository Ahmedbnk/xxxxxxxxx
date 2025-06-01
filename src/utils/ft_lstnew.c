#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list));
	node->content = content;
	node->next = NULL;
	return (node);
}


