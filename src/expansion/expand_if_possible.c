#include "minishell.h"

static int should_expand_dollar(char *str, int offset, int heredoc_flag)
{
	return (str[offset] == '$' && 
			(heredoc_flag || should_i_expand(str, offset)) && 
			ft_isalnum(str[offset + 1]));
}

static int find_next_dollar(char *str, int offset, int heredoc_flag)
{
	while (str[offset])
	{
		if (should_expand_dollar(str, offset, heredoc_flag))
			break;
		offset++;
	}
	return (offset);
}

void string_before_dollar(t_expand *data, int index, char *str, int *offset)
{
	int start_pos;
	int end_pos;

	if (!str)
		return;
	start_pos = *offset;
	end_pos = find_next_dollar(str, start_pos, data->heredoc_flag);
	if (end_pos > start_pos)
		data[index].befor_dollar = ft_substr(str, start_pos, end_pos - start_pos);
	*offset = end_pos;
}

static int find_expand_end(char *str, int offset, int heredoc_flag)
{
	int start;

	start = offset;
	if (str[offset] == '$')
		offset++;
	while (str[offset])
	{
		if (!ft_isalnum(str[offset]) || 
			(str[offset] == '$' && should_expand_dollar(str, offset, heredoc_flag)))
			break;
		offset++;
	}
	return (offset);
}

void string_to_expand(t_expand *data, int index, char *str, int *offset)
{
	int start;
	int end;

	if (!str)
		return;
	start = *offset;
	end = find_expand_end(str, start, data->heredoc_flag);
	data[index].to_expand = ft_substr(str, start, end - start);
	*offset = end;
}

void string_after_dollar(t_expand *data, int index, char *str, int *offset)
{
	int start;
	int end;

	if (!str)
		return;
	start = *offset;
	end = start;
	while (str[end])
		end++;
	if (end > start)
		data[index].after_dollar = ft_substr(str, start, end - start);
}

int	how_many_dallar_to_expand(char *str, int heredoc_flag)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (heredoc_flag || should_i_expand(str, i)) && ft_isalnum(str[i + 1]))
			counter++;
		i++;
	}
	return (counter);
}

static t_expand *init_expansion_list(char *str, int heredoc_flag, int *num_expansions)
{
	t_expand *list;

	*num_expansions = how_many_dallar_to_expand(str, heredoc_flag);
	if (*num_expansions == 0)
		return (NULL);
	
	allocat_and_init(&list, *num_expansions, heredoc_flag);
	return (list);
}

static void process_single_expansion(t_expand *list, int index, char *str, int *offset)
{
	string_before_dollar(list, index, str, offset);
	string_to_expand(list, index, str, offset);
	string_after_dollar(list, index, str, offset);
}

static void process_all_expansions(t_expand *list, char *str, int num_expansions)
{
	int i;
	int offset;

	i = 0;
	offset = 0;
	while (i < num_expansions)
	{
		process_single_expansion(list, i, str, &offset);
		i++;
	}
}

char *expand_if_possible(char *str, int heredoc_flag)
{
	int num_expansions;
	t_expand *list;
	char *new_str;

	if (!str)
		return (NULL);

	list = init_expansion_list(str, heredoc_flag, &num_expansions);
	if (!list)
		return (ft_strdup(str));

	process_all_expansions(list, str, num_expansions);
	new_str = new_str_after_expand(list, num_expansions);
	
	return (new_str);
}
