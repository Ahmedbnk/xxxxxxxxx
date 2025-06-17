#include "minishell.h"

char	*expnad_and_join_node(t_shell_control_block *s, int i)
{
	char	*result;
	char	*var_value;

	// Safety check
	if (!s || !s->expand_arr || i < 0)
	{
		printf("DEBUG: expnad_and_join_node safety check failed\n");
		return NULL;
	}

	printf("DEBUG: expnad_and_join_node called with i = %d\n", i);
	printf("DEBUG: to_expand = '%s'\n", s->expand_arr[i].to_expand ? s->expand_arr[i].to_expand : "NULL");

	// Handle special case for $? (exit status)
	if (s->expand_arr[i].to_expand && are_they_equal(s->expand_arr[i].to_expand, "$?"))
	{
		printf("DEBUG: Handling $? case\n");
		var_value = ft_itoa(s->exit_status);
	}
	else
	{
		printf("DEBUG: Calling get_env_var\n");
		var_value = get_env_var(s, s->expand_arr[i]);
	}
	
	printf("DEBUG: var_value = '%s'\n", var_value ? var_value : "NULL");
	
	// Handle the case where var_value might be NULL
	if (s->expand_arr[i].befor_dollar && var_value)
	{
		printf("DEBUG: Case 1: befor_dollar and var_value both exist\n");
		result = custom_join(s->expand_arr[i].befor_dollar, var_value);
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else if (s->expand_arr[i].befor_dollar)
	{
		printf("DEBUG: Case 2: only befor_dollar exists\n");
		result = custom_join(s->expand_arr[i].befor_dollar, "");
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else if (var_value)
	{
		printf("DEBUG: Case 3: only var_value exists\n");
		result = custom_join("", var_value);
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	else
	{
		printf("DEBUG: Case 4: neither befor_dollar nor var_value exist\n");
		result = custom_join("", "");
		if (s->expand_arr[i].after_dollar)
			result = custom_join(result, s->expand_arr[i].after_dollar);
	}
	
	printf("DEBUG: expnad_and_join_node returning: '%s'\n", result ? result : "NULL");
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
	{
		printf("DEBUG: new_str_after_expand safety check failed\n");
		return NULL;
	}

	printf("DEBUG: new_str_after_expand called with num_of_expantion = %d\n", num_of_expantion);

	new_after_expand = NULL;
	i = 0;
	while (i < num_of_expantion)
	{
		printf("DEBUG: Processing expansion %d/%d in new_str_after_expand\n", i+1, num_of_expantion);
		
		if (num_of_expantion - i == 1)
			s->expand_arr[i].last_one = 1;
		
		printf("DEBUG: About to call expnad_and_join_node with i = %d\n", i);
		expanded = expnad_and_join_node(s, i);
		
		if (!expanded)
		{
			printf("DEBUG: expnad_and_join_node returned NULL\n");
			return (NULL);
		}
		
		printf("DEBUG: expnad_and_join_node returned: '%s'\n", expanded);
		joined = custom_join(new_after_expand, expanded);
		new_after_expand = joined;
		
		if (!new_after_expand)
		{
			printf("DEBUG: custom_join returned NULL\n");
			return (NULL);
		}
		
		printf("DEBUG: custom_join returned: '%s'\n", new_after_expand);
		i++;
	}
	
	printf("DEBUG: new_str_after_expand returning: '%s'\n", new_after_expand);
	return (new_after_expand);
}
