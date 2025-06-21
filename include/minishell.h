#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

// Constants
# define PARENT 1
# define CHILD 2
# define SINGLE_Q 39
# define DOUBLE_Q 34
# define BUFFER_SIZE 40
# define PROTECT 14
# define VALID_NAME 0
# define AMBIGUOUS 1
# define NOT_NEW_START 0
# define NEW_START 1

// Token types
typedef enum e_type
{
	WORD,         //  0 for regular words
	PIPE,         // | 1
	REDIR_IN,     // < 2
	REDIR_OUT,    // > 3
	REDIR_APPEND, // >> 4
	HEREDOC,      // << 5
}					t_type;

// Token structure
typedef struct s_token
{
	int				type;
	char			*word;
	char			*heredoc_file_name;
	char			*delimiter;
}					t_token;

// Linked list structure
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// Expansion structure
typedef struct s_expand
{
	char			*befor_dollar;
	char			*to_expand;
	char			*after_dollar;
	int				last_one;
	int				heredoc_flag;
}					t_expand;

// File name list structure
typedef struct s_name_lst 
{
	char			*file_name;
	int				valid;
	int				new_start;
	struct s_name_lst	*next;
}					t_name_lst;

// Main shell control block
typedef struct s_shell_control_block
{
	char			**env_cpy;
	char			**env_of_export;
	char			*line;
	char			**splitted;
	char			*porotect_var;
	t_list			*lst;
	t_name_lst		*file_name_lst;
	t_token			*tokenized;
	char			**cmd_and_args;
	t_expand		*expand_arr;
	int				arr[2];
	int				previous_read_end;
	t_token			*line_pointer;
	char			*in_file_name;
	char			*file_name;
	int				fd_out;
	int				fd_in;
	int				last_child_pid;
	int				status;
	int				exit_status;
}					t_shell_control_block;

// Include modular headers (after type definitions)
# include "builtins.h"
# include "execution.h"
# include "expansion.h"
# include "parser.h"
# include "utils.h"
# include "env.h"

// Core shell functions
void	ft_init_shell_block(t_shell_control_block *shell, int ac, char **av);
char	*ft_readline(t_shell_control_block *shell);
void	expand_and_split(t_shell_control_block *shell);
char	**update_splitted(t_shell_control_block *shell);
void	execute_line(t_shell_control_block *shell);

int					check_error(t_shell_control_block *shell);
void				handle_signals(int flag);
void child_signal_handler();
int					is_between_quotes(char *line, int index);
int					is_space(char c);
int					are_they_equal(const char *str1, const char *str2);

char	**customized_split(char const *s);
char	*expand_if_possible(t_shell_control_block *s, char *str, int heredoc_flag);
int					should_i_expand(char *str, int index);
int					is_expand_separator(char c);
char				**split_for_expantion(char const *s);
char				*custom_join(char const *s1, char const *s2);

void	allocat_and_init(t_expand **expand_list, int how_much_to_expand, int heredoc_flag);
char	*new_str_after_expand(t_shell_control_block *s, int num_of_expantion);
void remove_quotes_from_args(char **splitted);
void	remove_quotes(char **line, char *quote);
char	**split_with_operators(char **splitted);
void print_splitted(char **splitted);
t_token *make_token(t_shell_control_block *shell);
int len_of_two_d_array(char **str);
void execute_command_line(t_shell_control_block *shell);

int					ft_isalnum(int c);
size_t				ft_strlen(const char *s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s, int flag);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_malloc(size_t size, int flag);
t_list	**get_garbage_pointer(int flag);
void	free_memory(t_list **lst);
t_list	*garbage_collection_lstnew(void *content, int flag);
char	*get_next_line(int fd);
void handle_heredoc(t_token *tokenized, char **in_file_name);
void print_file(char *str);
void handle_redir_in(char *str, char **in_file_name);
char *read_file(char *file_name);
void handle_redir_out(char *str, char **file_name);
void handle_append(char *str, char **file_name);
char **get_cmd_and_its_args(t_shell_control_block *shell);
void execute_command(t_shell_control_block *shell);

void	handle_signals_in_child(void);
char	*generate_random_name(void);

char ** copy_env(char **env);
void print_env(char **env);
void echo(char **args);
int	ft_strncmp(const char *big, const char *little, size_t n);
char *pwd();
int  execute_built_in(t_shell_control_block *shell, int state);
int is_it_key_value(char *str);
int is_valid_var(char *str);
int compare_env_var(char *var1, char *var2);
int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_strcmp(char *s1, char *s2);

char **handle_dollar_with_quotes(char **splitted);

void cd(char **env, char **path);
int	print_error(const char *str, ...);
void create_all_heredocs(t_shell_control_block *shell);
void unset(char ***env, char **vars);

void print_exit_signal_message(int exit_status);
char *get_env_var(t_shell_control_block *shell , t_expand data);
void remove_var_from_env(char ***env , char *var);
void export(t_shell_control_block *s, char **to_export);
void get_files_name(t_shell_control_block *s);
int	how_many_dallar_to_expand(char *str, int heredoc_flag);

void	 rm_quotes_from_multi_str(char **line, char *quote);
char *expand_outside_dollar(t_shell_control_block *scb, char *str);
int is_quote(char c);
int is_protected(t_shell_control_block *sh, char *str, int index);
void rm_quotes_from_one_str(t_shell_control_block *sh, char **line);
int is_all_spaces(const char *str);
int ft_lstsize(t_list *list);
int is_there_a_pipe(t_shell_control_block *shell);

// Additional functions that need to be declared here
void	split_after_expantion(t_shell_control_block *sh, char *str, char *old_str);
void	rm_quotes_from_one_str(t_shell_control_block *sh, char **line);
void	rm_quotes_from_multi_str(char **line, char *quote);
char	**split_for_expantion(char const *s);
void	*ft_malloc(size_t size, int flag);
void	child_signal_handler(void);

#endif
