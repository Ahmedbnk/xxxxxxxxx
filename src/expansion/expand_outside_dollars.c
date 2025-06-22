// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand_outside_dollar.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kaisen1337 <kaisen1337@student.42.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/21 07:39:27 by kaisen1337         #+#    #+#             */
// /*   Updated: 2025/06/21 07:39:27 by kaisen1337        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	is_outside_expand_dollar(char *str, int index)
// {
// 	if (!str || str[index] != '$')
// 		return (0);
// 	if (!str[index + 1])
// 		return (0);
// 	if (!is_between_quotes(str, index) && ft_isalnum(str[index + 1]))
// 		return (1);
// 	if (!is_between_quotes(str, index) && str[index + 1] == '?')
// 		return (1);
// 	return (0);
// }

// static int	num_dollar_toexpand(char *str, int heredoc_flag)
// {
// 	int	i;
// 	int	counter;

// 	if (!str)
// 		return (0);
// 	counter = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && (heredoc_flag || 
// 			(!is_between_quotes(str, i) && 
// 			(ft_isalnum(str[i + 1]) || str[i + 1] == '?'))))
// 			counter++;
// 		i++;
// 	}
// 	return (counter);
// }

// static void	string_before_dollar(t_expand *data, char *str, int *offset)
// {
// 	int	flag;

// 	if (!str)
// 		return ;
// 	flag = *offset;
// 	while (str[*offset])
// 	{
// 		if (str[*offset] == '$' && (data->heredoc_flag || 
// 			is_outside_expand_dollar(str, *offset)))
// 			break ;
// 		(*offset)++;
// 	}
// 	if (*offset > flag)
// 		data->befor_dollar = ft_substr(str, flag, *offset - flag);
// 	else
// 		data->befor_dollar = ft_strdup("", 1);
// }

// static void	string_to_expand(t_expand *data, char *str, int *offset)
// {
// 	int	start;

// 	if (!str || !str[*offset])
// 	{
// 		data->to_expand = NULL;
// 		return ;
// 	}
// 	start = *offset;
// 	(*offset)++;
// 	if (str[*offset] == '?')
// 	{
// 		(*offset)++;
// 		data->to_expand = ft_substr(str, start, *offset - start);
// 		return ;
// 	}
// 	while (str[*offset] && ft_isalnum(str[*offset]))
// 		(*offset)++;
// 	data->to_expand = ft_substr(str, start, *offset - start);
// }

// static void	string_after_dollar(t_expand *data, char *str, int *offset)
// {
// 	int	start;
// 	int	next_dollar;

// 	if (!str)
// 	{
// 		data->after_dollar = NULL;
// 		return ;
// 	}
// 	start = *offset;
// 	next_dollar = *offset;
// 	while (str[next_dollar])
// 	{
// 		if (str[next_dollar] == '$' && (data->heredoc_flag || 
// 			is_outside_expand_dollar(str, next_dollar)))
// 			break;
// 		next_dollar++;
// 	}
// 	if (next_dollar > start)
// 		data->after_dollar = ft_substr(str, start, next_dollar - start);
// 	else
// 		data->after_dollar = ft_strdup("", 1);
// 	*offset = next_dollar;
// }

// char	*expnad_and_join_node(t_shell_control_block *s, t_expand data)
// {
// 	char	*path;
// 	char	*the_joined_node;
// 	char	*rest;

// 	path = NULL;
// 	the_joined_node = NULL;
// 	if (data.to_expand != NULL)
// 	{
// 		if (are_they_equal(data.to_expand, "$?"))
// 			path = ft_itoa(s->exit_status);
// 		else
// 			path = ft_strdup(get_env_var(s, data), 1);
// 		if (!path)
// 			path = ft_strdup("", 1);
// 		the_joined_node = custom_join(data.befor_dollar, path);
// 	}
// 	else
// 		the_joined_node = ft_strdup(data.befor_dollar ? data.befor_dollar : "", 1);
// 	if (data.last_one)
// 	{
// 		rest = custom_join(the_joined_node, data.after_dollar);
// 		return (rest);
// 	}
// 	return (the_joined_node);
// }

// char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion)
// {
// 	char	*new_after_expand;
// 	char	*expanded;
// 	char	*joined;
// 	int		i;

// 	new_after_expand = ft_strdup("", 1);
// 	if (!new_after_expand)
// 		return (NULL);
// 	i = 0;
// 	while (i < num_of_expantion)
// 	{
// 		if (num_of_expantion - i == 1)
// 			s->expand_arr[i].last_one = 1;
// 		expanded = expnad_and_join_node(s, s->expand_arr[i]);
// 		if (!expanded)
// 			return (NULL);
// 		joined = custom_join(new_after_expand, expanded);
// 		new_after_expand = joined;
// 		if (!new_after_expand)
// 			return (NULL);
// 		i++;
// 	}
// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   dollar_expansion.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kaisen1337 <kaisen1337@student.42.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/21 07:36:07 by kaisen1337         #+#    #+#             */
// /*   Updated: 2025/06/21 07:36:07 by kaisen1337        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// /* Check if character is between quotes - returns quote type or 0 if not */
// int	is_between_quotes(char *line, int index)
// {
// 	int	i;
// 	int	quote;

// 	i = 0;
// 	quote = 0;
// 	while (line[i] && i <= index)
// 	{
// 		if ((line[i] == single_q || line[i] == double_q) && quote == 0)
// 			quote = line[i];
// 		else if ((line[i] == single_q || line[i] == double_q)
// 			&& line[i] == quote)
// 			quote = 0;
// 		if (i == index)
// 			return (quote);
// 		i++;
// 	}
// 	return (0);
// }

// /* Check if dollar sign at position needs expansion */
// int	is_outside_expand_dollar(char *str, int index)
// {
// 	if (!str || str[index] != '$' || !str[index + 1])
// 		return (0);
// 	if (is_between_quotes(str, index) == double_q)
// 		return (0);
// 	if (ft_isalnum(str[index + 1]) || str[index + 1] == '?'
// 		|| str[index + 1] == '_')
// 		return (1);
// 	return (0);
// }

// /* Count number of dollar signs that need expansion */
// static int	count_dollars_to_expand(char *str)
// {
// 	int	i;
// 	int	counter;

// 	if (!str)
// 		return (0);
// 	counter = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (is_outside_expand_dollar(str, i))
// 			counter++;
// 		i++;
// 	}
// 	return (counter);
// }

// /* Extract text before dollar sign */
// static void	extract_before_dollar(t_expand *data, char *str, int *offset)
// {
// 	int	start;

// 	if (!str)
// 		return ;
// 	start = *offset;
// 	while (str[*offset])
// 	{
// 		if (is_outside_expand_dollar(str, *offset))
// 			break ;
// 		(*offset)++;
// 	}
// 	if (*offset > start)
// 		data->before_dollar = ft_substr(str, start, *offset - start);
// 	else
// 		data->before_dollar = ft_strdup("", 1);
// }

// /* Extract variable name to expand */
// static void	extract_var_to_expand(t_expand *data, char *str, int *offset)
// {
// 	int	start;

// 	if (!str || !str[*offset])
// 	{
// 		data->to_expand = NULL;
// 		return ;
// 	}
// 	start = *offset;
// 	(*offset)++;
// 	if (str[*offset] == '?')
// 	{
// 		(*offset)++;
// 		data->to_expand = ft_substr(str, start, *offset - start);
// 		return ;
// 	}
// 	while (str[*offset] && (ft_isalnum(str[*offset]) || str[*offset] == '_'))
// 		(*offset)++;
// 	data->to_expand = ft_substr(str, start, *offset - start);
// }

// /* Extract text after dollar sign until next dollar or end */
// static void	extract_after_dollar(t_expand *data, char *str, int *offset)
// {
// 	int	start;
// 	int	next_dollar;

// 	if (!str)
// 	{
// 		data->after_dollar = NULL;
// 		return ;
// 	}
// 	start = *offset;
// 	next_dollar = *offset;
// 	while (str[next_dollar])
// 	{
// 		if (is_outside_expand_dollar(str, next_dollar))
// 			break ;
// 		next_dollar++;
// 	}
// 	if (next_dollar > start)
// 		data->after_dollar = ft_substr(str, start, next_dollar - start);
// 	else
// 		data->after_dollar = ft_strdup("", 1);
// 	*offset = next_dollar;
// }

// /* Allocate and initialize expansion array */
// static int	init_expansion_array(t_expand **expand_arr, int count)
// {
// 	int	i;

// 	*expand_arr = (t_expand *)malloc(sizeof(t_expand) * count);
// 	if (!(*expand_arr))
// 		return (1);
// 	i = 0;
// 	while (i < count)
// 	{
// 		(*expand_arr)[i].before_dollar = NULL;
// 		(*expand_arr)[i].to_expand = NULL;
// 		(*expand_arr)[i].after_dollar = NULL;
// 		(*expand_arr)[i].last_one = 0;
// 		i++;
// 	}
// 	return (0);
// }

// /* Expand and join a single node */
// static char	*expand_and_join_node(t_shell_control_block *scb, t_expand data)
// {
// 	char	*value;
// 	char	*joined1;
// 	char	*joined2;

// 	value = NULL;
// 	if (data.to_expand)
// 	{
// 		if (ft_strcmp(data.to_expand, "$?") == 0)
// 			value = ft_itoa(scb->exit_status);
// 		else
// 		{
// 			value = get_env_value(scb, data.to_expand + 1);
// 			if (!value)
// 				value = ft_strdup("", 1);
// 		}
// 	}
// 	else
// 		value = ft_strdup("", 1);
// 	joined1 = ft_strjoin(data.before_dollar ? data.before_dollar : "", 
// 			value ? value : "");
// 	if (data.last_one)
// 	{
// 		joined2 = ft_strjoin(joined1, data.after_dollar ? data.after_dollar : "");
// 		free(joined1);
// 		return (joined2);
// 	}
// 	return (joined1);
// }

// /* Create new string after expanding all variables */
// static char	*create_expanded_string(t_shell_control_block *scb, 
// 									t_expand *expand_arr, int count)
// {
// 	char	*result;
// 	char	*expanded;
// 	char	*temp;
// 	int		i;

// 	result = ft_strdup("", 1);
// 	if (!result)
// 		return (NULL);
// 	i = 0;
// 	while (i < count)
// 	{
// 		if (i == count - 1)
// 			expand_arr[i].last_one = 1;
// 		expanded = expand_and_join_node(scb, expand_arr[i]);
// 		if (!expanded)
// 		{
// 			free(result);
// 			return (NULL);
// 		}
// 		temp = ft_strjoin(result, expanded);
// 		free(result);
// 		free(expanded);
// 		result = temp;
// 		i++;
// 	}
// 	return (result);
// }

// /* Clean up expansion array */
// static void	cleanup_expansion_array(t_expand *expand_arr, int count)
// {
// 	int	i;

// 	if (!expand_arr)
// 		return ;
// 	i = 0;
// 	while (i < count)
// 	{
// 		free(expand_arr[i].before_dollar);
// 		free(expand_arr[i].to_expand);
// 		free(expand_arr[i].after_dollar);
// 		i++;
// 	}
// 	free(expand_arr);
// }

// /* Main function to expand all dollar variables outside double quotes */
// char	*expand_outside_dollar(t_shell_control_block *scb, char *str)
// {
// 	t_expand	*expand_arr;
// 	int			dollar_count;
// 	int			i;
// 	int			offset;
// 	char		*result;

// 	if (!str)
// 		return (NULL);
// 	dollar_count = count_dollars_to_expand(str);
// 	if (dollar_count == 0)
// 		return (ft_strdup(str, 1));
// 	if (init_expansion_array(&expand_arr, dollar_count))
// 		return (ft_strdup(str, 1));
// 	i = 0;
// 	offset = 0;
// 	while (i < dollar_count)
// 	{
// 		extract_before_dollar(&expand_arr[i], str, &offset);
// 		extract_var_to_expand(&expand_arr[i], str, &offset);
// 		extract_after_dollar(&expand_arr[i], str, &offset);
// 		i++;
// 	}
// 	result = create_expanded_string(scb, expand_arr, dollar_count);
// 	cleanup_expansion_array(expand_arr, dollar_count);
// 	return (result ? result : ft_strdup(str, 1));
// }

#include "minishell.h"

char	*expand_outside_dollar(t_shell_control_block *scb, char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str || !*str)
		return (str);
	
	result = ft_malloc(ft_strlen(str) * 2 + 1, 1);
	i = 0;
	j = 0;
	
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1]))
		{
			// Simple variable expansion
			result[j++] = str[i++];
			while (str[i] && !is_space(str[i]) && str[i] != '$')
				result[j++] = str[i++];
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}