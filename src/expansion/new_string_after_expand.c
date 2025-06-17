#include "minishell.h"

char	*expnad_and_join_node(t_shell_control_block *s, int i)
{
	char	*var_value;
	char	*result;

	if (ft_strcmp(s->expand_arr[i].to_expand, "$?") == 0)
		var_value = ft_itoa(s->exit_status);
	else
		var_value = get_env_var(s, s->expand_arr[i]);

	if (var_value)
	{
		if (s->expand_arr[i].befor_dollar && s->expand_arr[i].after_dollar)
			result = custom_join(custom_join(s->expand_arr[i].befor_dollar, var_value), s->expand_arr[i].after_dollar);
		else if (s->expand_arr[i].befor_dollar)
			result = custom_join(s->expand_arr[i].befor_dollar, var_value);
		else if (s->expand_arr[i].after_dollar)
			result = custom_join(var_value, s->expand_arr[i].after_dollar);
		else
			result = ft_strdup(var_value, 1);
	}
	else
	{
		if (s->expand_arr[i].befor_dollar && s->expand_arr[i].after_dollar)
			result = custom_join(s->expand_arr[i].befor_dollar, s->expand_arr[i].after_dollar);
		else if (s->expand_arr[i].befor_dollar)
			result = ft_strdup(s->expand_arr[i].befor_dollar, 1);
		else if (s->expand_arr[i].after_dollar)
			result = ft_strdup(s->expand_arr[i].after_dollar, 1);
		else
			result = ft_strdup("", 1);
	}
	return (result);
}

char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (i < num_of_expantion)
	{
		if (i == 0)
			result = expnad_and_join_node(s, i);
		else
		{
			if (result)
				result = custom_join(result, expnad_and_join_node(s, i));
			else
				result = expnad_and_join_node(s, i);
		}
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
