#include "minishell.h"

char	*expnad_and_join_node(t_shell_control_block *s, int i)
{
	char	*result;
	char	*var_value;

	// Safety check
	if (!s || !s->expand_arr || i < 0)
		return NULL;

	// Handle special case for $? (exit status)
	if (s->expand_arr[i].to_expand && are_they_equal(s->expand_arr[i].to_expand, "$?"))
	{
		var_value = ft_itoa(s->exit_status);
	}
	else
	{
		var_value = get_env_var(s, s->expand_arr[i]);
	}
	
	// Handle the case where var_value might be NULL
	if (s->expand_arr[i].befor_dollar && var_value)
	{
		result = custom_join(s->expand_arr[i].befor_dollar, var_value);
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else if (s->expand_arr[i].befor_dollar)
	{
		result = custom_join(s->expand_arr[i].befor_dollar, "");
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else if (var_value)
	{
		result = custom_join("", var_value);
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else
	{
		result = custom_join("", "");
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	return result;
}

char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion)
{
	char	*new_after_expand;
	char	*expanded;
	char	*joined;
	int		i;

	// Safety checks
	if (!s || num_of_expantion <= 0)
		return NULL;

	new_after_expand = NULL;
	i = 0;
	while (i < num_of_expantion)
	{
		if (num_of_expantion - i == 1)
			s->expand_arr[i].last_one = 1;
		expanded = expnad_and_join_node(s, i);
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
