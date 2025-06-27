#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*c_node;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	c_node = *lst;
	while (c_node->next != NULL)
	{
		c_node = c_node->next;
	}
	c_node->next = new;
}

void	add_token_to_lst(t_token **lst, t_token *new)
{
	t_token	*c_node;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	c_node = *lst;
	while (c_node->next != NULL)
	{
		c_node = c_node->next;
	}
	c_node->next = new;
}
