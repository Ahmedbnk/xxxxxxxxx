#include "minishell.h"

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

char	*expand_if_possible(t_shell_control_block *s, char *str, int heredoc_flag)
{
	int i;
	int offset;
	int num_of_expantion;
	char *new_str;

	if (!s || !str)
		return NULL;

	i = 0;
	offset = 0;
	num_of_expantion = how_many_dallar_to_expand(str, heredoc_flag);
	
	if (num_of_expantion == 0)
		return (ft_strdup(str, 1));
	
	if (!s->expand_arr)
	{
		allocat_and_init(&(s->expand_arr), num_of_expantion, heredoc_flag);
		
		if (!s->expand_arr)
		{
			return (ft_strdup(str, 1));
		}
	}
	else
	{
		for (i = 0; i < num_of_expantion; i++)
		{
			s->expand_arr[i].befor_dollar = NULL;
			s->expand_arr[i].to_expand = NULL;
			s->expand_arr[i].after_dollar = NULL;
			s->expand_arr[i].last_one = 0;
			s->expand_arr[i].heredoc_flag = heredoc_flag;
		}
	}
	
	i = 0;
	while (i < num_of_expantion)
	{
		string_before_dollar(&(s->expand_arr[i]), str, &offset);
		string_to_expand(&(s->expand_arr[i]), str, &offset);
		string_after_dollar(&(s->expand_arr[i]), str, &offset);
		i++;
	}
	
	new_str = new_str_after_expand(s, num_of_expantion);
	return (new_str);
}

void expand(t_shell_control_block *shell) 
{
  int i;
  i = 0;
  printf("DEBUG: expand function called\n");
  while (shell->splitted[i])
  {
    printf("DEBUG: Processing splitted[%d]: '%s'\n", i, shell->splitted[i]);
    if(are_they_equal(shell->splitted[i], "<<"))
      i++;
    else
    {
      char *original = shell->splitted[i];
      shell->splitted[i] = expand_if_possible(shell, shell->splitted[i], 0);
      printf("DEBUG: After expansion: '%s' -> '%s'\n", original, shell->splitted[i]);
      if (shell->exit_status == 1)
        return;
    }
    i++;
  }
}
