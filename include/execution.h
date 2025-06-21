#ifndef EXECUTION_H
# define EXECUTION_H

// Command execution
void	execute_command_line(t_shell_control_block *shell);
void	execute_command(t_shell_control_block *shell);
char	**get_cmd_and_its_args(t_shell_control_block *shell);

// Redirection handling
void	handle_redir_in(char *str, char **in_file_name);
void	handle_redir_out(char *str, char **file_name);
void	handle_append(char *str, char **file_name);
void	handle_heredoc(t_token *tokenized, char **in_file_name);
void	create_all_heredocs(t_shell_control_block *shell);

// Signal handling
void	handle_signals(int flag);
void	handle_signals_in_child(void);
void	child_signal_handler(void);
void	print_exit_signal_message(int exit_status);

// File operations
char	*read_file(char *file_name);
void	print_file(char *str);

#endif 