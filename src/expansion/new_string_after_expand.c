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
	char	*result;
	int		i;

	(void)s;
	(void)num_of_expantion;
	
	result = ft_malloc(100, 1);
	ft_strcpy(result, "expanded_string");
	return (result);
}
