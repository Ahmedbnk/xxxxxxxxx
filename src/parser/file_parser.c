#include "minishell.h"

t_name_lst	*new_file_name(void *name_of_file, int is_valid, int is_it_new_start)
{
	t_name_lst	*node;

	node = ft_malloc(sizeof(t_name_lst), 1);
	if (!node)
		return (NULL);
	node->file_name = name_of_file;
	node->valid = is_valid;
	node->new_start = is_it_new_start;
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

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	return (are_they_equal(str, ">") || are_they_equal(str, "<") || 
		are_they_equal(str, ">>"));
}

int	is_there_a_space_in_file_name(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (is_space(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	handle_expansion_result(t_shell_control_block *sh, 
	t_name_lst *ptr, char *str)
{
	int	i;

	if (are_they_equal(ptr->file_name, str))
	{
		// remove_quotes(&ptr->file_name);
		return ;
	}
	i = 0;
	while (i < how_many_dallar_to_expand(ptr->file_name, 0))
	{
		if (is_there_a_space_in_file_name(get_env_var(sh, sh->expand_arr[i])) 
			|| !*str)
		{
			ptr->valid = AMBIGUOUS;
			break ;
		}
		ptr->file_name = str;
		// remove_quotes(&ptr->file_name);
		i++;
	}
}

void	prepare_lst(t_shell_control_block *sh)
{
	t_name_lst	*ptr;
	char		*str;

	if (!sh || !sh->file_name_lst)
		return ;
	ptr = sh->file_name_lst;
	while (ptr)
	{
		if (!ptr->file_name)
		{
			ptr = ptr->next;
			continue ;
		}
		str = expand_if_possible(sh, ptr->file_name, 0);
		if (!str)
		{
			ptr->valid = AMBIGUOUS;
			ptr = ptr->next;
			continue ;
		}
		handle_expansion_result(sh, ptr, str);
		ptr = ptr->next;
	}
}

void	get_files_name(t_shell_control_block *s)
{
	int		i;
	t_name_lst	*new_node;

	i = 0;
	s->file_name_lst = NULL;
	while (s->splitted[i])
	{
		if (are_they_equal(s->splitted[i], "<") || 
			are_they_equal(s->splitted[i], ">") ||
			are_they_equal(s->splitted[i], ">>") ||
			are_they_equal(s->splitted[i], "<<"))
		{
			if (s->splitted[i + 1])
			{
				new_node = ft_malloc(sizeof(t_name_lst), 1);
				new_node->file_name = s->splitted[i + 1];
				new_node->valid = 1;
				new_node->new_start = 1;
				new_node->next = s->file_name_lst;
				s->file_name_lst = new_node;
			}
		}
		i++;
	}
}
