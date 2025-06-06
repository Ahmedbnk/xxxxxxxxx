#include "minishell.h"

char	*expnad_and_join_node(t_expand data)
{
	char	*path;
	char	*the_joined_node;
	char	*rest;
	extern t_shell_control_block *g_shell;  // Add global shell pointer

	if (data.to_expand != NULL)
	{
		if (ft_strcmp(data.to_expand, "$?") == 0)
		{
			path = ft_itoa(g_shell->last_exit_status);
			the_joined_node = custom_join(data.befor_dollar, path);
			free(path);  // Free the itoa result
		}
		else
		{
			path = ft_strdup(getenv((data.to_expand) + 1), 1);
			the_joined_node = custom_join(data.befor_dollar, path);
		}
	}
	if (data.last_one)
	{
		rest = custom_join(the_joined_node, data.after_dollar);
		return (rest);
	}
	return (the_joined_node);
}

char	*new_str_after_expand(t_expand *data, int num_of_expantion)
{
	char	*new_after_expand;
	char	*expanded;
	char	*joined;
	int		i;

	new_after_expand = NULL;
	i = 0;
	while (i < num_of_expantion)
	{
		if (num_of_expantion - i == 1)
			data[i].last_one = 1;
		expanded = expnad_and_join_node(data[i]);
		if (!expanded)
			return (NULL);
		joined = custom_join(new_after_expand, expanded);
		new_after_expand = joined;
		if (!new_after_expand)
			return (NULL);
		i++;
	}
	return (new_after_expand);
}
