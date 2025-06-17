#include "minishell.h"



// typedef struct s_new_exp
// {
//     void *ptr;
//     int exp_flag;
// }t_new_epx;

// void	string_before_dollar(t_expand *data, char *str, int *offset)
// {
// 	int	flag;

// 	if (!str)
// 		return ;
// 	flag = *offset;
// 	while (str[*offset])
// 	{
// 		if (str[*offset] == '$' && (data->heredoc_flag || should_i_expand(str, *offset))
// 			&& ft_isalnum(str[(*offset) + 1]))
// 			break ;
// 		(*offset)++;
// 	}
// 	if (*offset > flag)
// 		data->befor_dollar = ft_substr(str, flag, *offset - flag);
// }
// void ft_init_list(t_new_epx *list)
// {
//     list->ptr= NULL;
//     list->exp_flag= 0;
// }
// void expand(char *str)
// {
//     t_new_epx *list;
//     list = NULL;
//     ft_init_list(list);

// }