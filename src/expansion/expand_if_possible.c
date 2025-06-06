#include "minishell.h"


int	how_many_dallar_to_expand(char *str, int heredoc_flag)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (heredoc_flag || should_i_expand(str, i)))
		{
			if (str[i + 1] == '?' || ft_isalnum(str[i + 1]))
				counter++;
		}
		i++;
	}
	return (counter);
}

void	string_before_dollar(t_expand *data, int index, char *str, int *offset)
{
	int	flag;

	if (!str)
		return ;
	flag = *offset;
	while (str[*offset])
	{
		if (str[*offset] == '$' && (data->heredoc_flag || should_i_expand(str, *offset))
			&& ft_isalnum(str[(*offset) + 1]))
			break ;
		(*offset)++;
	}
	if (*offset > flag)
		data[index].befor_dollar = ft_substr(str, flag, *offset - flag);
}

void	string_to_expand(t_expand *data, int index, char *str, int *offset)
{
	int	start;

	if (!str)
		return ;
	start = *offset;
	while (str[*offset])
	{
		if (str[*offset] == '$' && start == (*offset))
			(*offset)++;
		if (str[*offset] == '?')
		{
			(*offset)++;
			break;
		}
		if (!ft_isalnum(str[*offset]) || (str[*offset] == '$'
				&& (data->heredoc_flag || should_i_expand(str, *offset))))
			break ;
		(*offset)++;
	}
	data[index].to_expand = ft_substr(str, start, *offset - start);
}

void	string_after_dollar(t_expand *data, int index, char *str, int *offset)
{
	int	start;
	int	end;

	if (!str)
		return ;
	start = *offset;
	end = *offset;
	while (str[end])
		end++;
	if (end > start)
		data[index].after_dollar = ft_substr(str, start, end - start);
}

char	*expand_if_possible(char *str , int heredoc_flag)
{
	int			i;
	int			offset;
	int			num_of_expantion;
	char		*new_str;
	t_expand	*list;

	i = 0;
	offset = 0;
	num_of_expantion = how_many_dallar_to_expand(str, heredoc_flag);
  if(num_of_expantion == 0)
    return (ft_strdup(str,1));
	allocat_and_init(&list, num_of_expantion, heredoc_flag);
	while (i < num_of_expantion)
	{
		string_before_dollar(list, i, str, &offset);
		string_to_expand(list, i, str, &offset);
		string_after_dollar(list, i, str, &offset);
		i++;
	}
	new_str = new_str_after_expand(list, num_of_expantion);
	return (new_str);
}
