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
	int i;
	int offset;
	int num_of_expantion;
	char *new_str;

	s->expand_arr = NULL;

	i = 0;
	offset = 0;
	num_of_expantion = how_many_dallar_to_expand(str, heredoc_flag);
	if (num_of_expantion == 0)
		return (ft_strdup(str, 1));
	allocat_and_init(&(s->expand_arr), num_of_expantion, heredoc_flag);
	while (i < num_of_expantion)
	{
		string_before_dollar(&(s->expand_arr[i]), str, &offset);
		string_to_expand(&(s->expand_arr[i]), str, &offset);
		string_after_dollar(&(s->expand_arr[i]), str, &offset);
		i++;
	}
	// printf("s%s\n", str);
//	r_q(s, num_of_expantion);
	new_str = new_str_after_expand(s, num_of_expantion);
	return (new_str);
}
