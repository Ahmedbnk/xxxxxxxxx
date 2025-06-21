// #include "minishell.h"

// int	is_in_double_quotes(char *line, int index)
// {
// 	int	i;
// 	int	quote;

// 	i = 0;
// 	quote = 0;
// 	while (line[i])
// 	{
// 		if ((line[i] == single_q || line[i] == double_q) && quote == 0)
// 			quote = line[i];
// 		else if ((line[i] == single_q || line[i] == double_q)
// 			&& line[i] == quote)
// 			quote = 0;
// 		if (i == index)
// 			return (quote == double_q);
// 		i++;
// 	}
// 	return (0);
// }

// int is_inside_expand_dollar(char *str, int index)
// {
// 	if (str[index] != '$')
// 		return (0);
// 	if (!str[index + 1])
// 		return (0);
// 	if (is_in_double_quotes(str, index) && ft_isalnum(str[index + 1]))
// 		return (1);
// 	if (is_in_double_quotes(str, index) && str[index + 1] == '?')
// 		return (1);
// 	return (0);
// }

// static int	num_dollar_toexpand_inside(char *str, int heredoc_flag)
// {
// 	int	i;
// 	int	counter;

// 	counter = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$' && str[i + 1] && (heredoc_flag || 
// 			(is_in_double_quotes(str, i) && 
// 			(ft_isalnum(str[i + 1]) || str[i + 1] == '?'))))
// 			counter++;
// 		i++;
// 	}
// 	return (counter);
// }

// static void	string_before_dollar_inside(t_expand *data, char *str, int *offset)
// {
// 	int	flag;

// 	if (!str)
// 		return ;
// 	flag = *offset;
// 	while (str[*offset])
// 	{
// 		if (str[*offset] == '$' && (data->heredoc_flag || 
// 				is_inside_expand_dollar(str, *offset)))
// 			break ;
// 		(*offset)++;
// 	}
// 	if (*offset > flag)
// 		data->befor_dollar = ft_substr(str, flag, *offset - flag);
// }

// static void	string_to_expand_inside(t_expand *data, char *str, int *offset)
// {
// 	int	start;

// 	if (!str)
// 		return ;
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

// static void	string_after_dollar_inside(t_expand *data, char *str, int *offset)
// {
// 	int	start;
// 	int	end;

// 	if (!str)
// 		return ;
// 	start = *offset;
// 	end = *offset;
// 	while (str[end])
// 		end++;
// 	if (end > start)
// 		data->after_dollar = ft_substr(str, start, end - start);
// }

// char	*expand_inside_quote_dollar(t_shell_control_block *s, char *str, 
// 									int heredoc_flag)
// {
// 	int		i;
// 	int		offset;
// 	int		num_of_expantion;
// 	char	*new_str;

// 	s->expand_arr = NULL;
// 	i = 0;
// 	offset = 0;
// 	num_of_expantion = num_dollar_toexpand_inside(str, heredoc_flag);
// 	if (num_of_expantion == 0)
// 		return (ft_strdup(str, 1));
// 	allocat_and_init(&(s->expand_arr), num_of_expantion, heredoc_flag);
// 	while (i < num_of_expantion)
// 	{
// 		string_before_dollar_inside(&(s->expand_arr[i]), str, &offset);
// 		string_to_expand_inside(&(s->expand_arr[i]), str, &offset);
// 		string_after_dollar_inside(&(s->expand_arr[i]), str, &offset);
// 		i++;
// 	}
// 	new_str = new_str_after_expand(s, num_of_expantion);
// 	return (new_str);
// }