#include "minishell.h"

static void	allocat_expand_list(t_expand **expand_list, int how_much_to_expand)
{
	*expand_list = ft_malloc(how_much_to_expand * sizeof(t_expand));
}

static void	init_expand_list(t_expand *expand_list, int how_much_to_expand, int heredoc_flag)
{
	int	i;

	i = 0;
	while (i < how_much_to_expand)
	{
		expand_list[i].befor_dollar = NULL;
		expand_list[i].to_expand = NULL;
		expand_list[i].after_dollar = NULL;
		expand_list[i].last_one = 0;
		expand_list[i].heredoc_flag = heredoc_flag;

		i++;
	}
}

void	allocat_and_init(t_expand **expand_list, int how_much_to_expand, int heredoc_flag)
{
	allocat_expand_list(expand_list, how_much_to_expand);
	init_expand_list(*expand_list, how_much_to_expand, heredoc_flag);
}
