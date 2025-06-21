#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// Main parsing functions
void	parse_line(t_shell_control_block *shell);
t_token	*make_token(t_shell_control_block *shell);
char	**split_with_operators(char **splitted);
char	**customized_split(char const *s);

// Token and operator handling
void	get_files_name(t_shell_control_block *s);
int		is_between_quotes(char *line, int index);
int		is_there_a_pipe(t_shell_control_block *shell);

// Quote handling
void	remove_quotes_from_args(char **splitted);
void	remove_quotes(char **line, char *quote);
void	rm_quotes_from_one_str(t_shell_control_block *sh, char **line);
void	rm_quotes_from_multi_str(char **line, char *quote);

// Input validation
int		check_input_error(t_shell_control_block *shell);
int		check_error(t_shell_control_block *shell);

// Utility functions for parsing
void	print_splitted(char **splitted);
int		len_of_two_d_array(char **str);

#endif 