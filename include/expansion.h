#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

// Variable expansion
char	*expand_if_possible(t_shell_control_block *s, char *str, int heredoc_flag);
char	*expand_outside_dollar(t_shell_control_block *scb, char *str);
char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion);
char	*get_env_var(t_shell_control_block *shell, t_expand data);

// Expansion utilities
int		should_i_expand(char *str, int index);
int		is_expand_separator(char c);
int		how_many_dallar_to_expand(char *str, int heredoc_flag);
void	allocat_and_init(t_expand **expand_list, int how_much_to_expand, int heredoc_flag);

// Quote handling in expansion
char	**handle_dollar_with_quotes(char **splitted);

#endif 