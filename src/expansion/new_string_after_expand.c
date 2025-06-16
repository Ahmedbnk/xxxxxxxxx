#include "minishell.h"

char	*expnad_and_join_node(t_shell_control_block *s, t_expand data)
{
	char	*path;
	char	*the_joined_node;
	char	*rest;
	if (data.to_expand != NULL)
	{
		if (are_they_equal(data.to_expand, "$?"))
			path = ft_itoa(s->exit_status);
		else
			path = ft_strdup(get_env_var(s, data), 1);
		
		// Check for ambiguous redirection if this is part of a redirection
		if (path && check_ambiguous_redirection(path))
		{
			print_error("ambiguous redirect\n");
			s->exit_status = 1;
			return NULL;
		}
		
		the_joined_node = custom_join(data.befor_dollar, path);
	}
	if (data.last_one)
	{
		rest = custom_join(the_joined_node, data.after_dollar);
		return (rest);
	}
	return (the_joined_node);
}

char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion)
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
			s->expand_arr[i].last_one = 1;
		expanded = expnad_and_join_node(s, s->expand_arr[i]);
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
