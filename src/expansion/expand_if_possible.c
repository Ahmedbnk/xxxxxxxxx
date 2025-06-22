#include "minishell.h"

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

void	string_before_dollar(t_expand *data, char *str, int *offset)
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
		data->befor_dollar = ft_substr(str, flag, *offset - flag);
}

void	string_to_expand(t_expand *data, char *str, int *offset)
{
	int	start;

	if (!str)
		return ;
	start = *offset;
	while (str[*offset])
	{
		if (str[*offset] == '$' && start == (*offset))
			(*offset)++;
    if(str[*offset] == '?' && str[(*offset) - 1] == '$')
    {
      (*offset) ++;
      break;
    }
    else if (!ft_isalnum(str[*offset]) || (str[*offset] == '$'
				&& (data->heredoc_flag || should_i_expand(str, *offset))))
			break ;
		(*offset)++;
	}
	data->to_expand = ft_substr(str, start, *offset - start);
}

void	string_after_dollar(t_expand *data, char *str, int *offset)
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
		data->after_dollar = ft_substr(str, start, end - start);
}

//char	*expand_if_possible(char *str , int heredoc_flag)

// void r_q(t_shell_control_block *sh, int size)
// {
//   int i = 0;
//   t_expand *ptr;
//   ptr = sh->expand_arr;
//   char quote = 0;
//   while(i < size)
//   {
//     if(ptr->befor_dollar)
//       rm_quotes_from_multi_str(&ptr->befor_dollar, &quote);
//     if(ptr->to_expand)
//       rm_quotes_from_multi_str(&ptr->to_expand, &quote);
//     if(i+1 == size && ptr->after_dollar)
//       rm_quotes_from_multi_str(&ptr->after_dollar, &quote);
//     i++;
//   }
// }

char	*expand_if_possible(t_shell_control_block *s, char *str, int heredoc_flag)
{
	char	*result;
	int		expand_count;

	if (!str || !*str)
		return (str);
	
	expand_count = how_many_dallar_to_expand(str, heredoc_flag);
	if (expand_count == 0)
		return (str);
	
	result = expand_outside_dollar(s, str);
	return (result);
}
