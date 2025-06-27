#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = ft_malloc(sizeof(t_list),1);
	node->content = content;
	node->next = NULL;
	return (node);
}



t_token	*new_token(void *content, int type)
{
	t_token	*node;

	node = ft_malloc(sizeof(t_token),1);
	node->word = content;
	node->type = type;
	node->next = NULL;
	return (node);
}
