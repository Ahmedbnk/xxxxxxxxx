#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

# define single_q 39
# define double_q 34
#define BUFFER_SIZE 40

typedef struct s_expand
{
	char			*befor_dollar;
	char			*to_expand;
	char			*after_dollar;
	int				last_one;
	int				heredoc_flag;
}					t_expand;

typedef enum e_token_type
{
	WORD,         //  0 for regular words
	PIPE,         // | 1
	REDIR_IN,     // < 2
	REDIR_OUT,    // > 3
	REDIR_APPEND, // >> 4
	HEREDOC,      // << 5
}					t_token;

typedef struct s_data
{
	int				type;
	char			*word;
}					t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;


//t_token				*add_node(t_token **list, t_token *node);
//t_token				*creat_node(char *str);

int					check_error(char *str);

void				sigint_handler(int signo);
void				handle_signals(void);
int					is_between_quotes(char *line, int index);
int					is_space(char c);
int					are_they_equal(const char *str1, const char *str2);

char	**customized_split(char const *s);
//char        *expand_if_possible(char *string);
char	*expand_if_possible(char *str, int g);
int					should_i_expand(char *str, int index);
int					is_expand_separator(char c);
char				**split_for_expantion(char const *s);
char				*custom_join(char const *s1, char const *s2);


void	allocat_and_init(t_expand **expand_list, int how_much_to_expand, int heredoc_flag);
char				*new_str_after_expand(t_expand *data, int num_of_expantion);
void remove_quotes_from_args(char **splitted);
char	**split_with_operators(char **splitted);
void print_splitted(char **splitted);
t_data *make_token(char **arr);
int len_of_two_d_array(char **str);
void parse_tokenized(t_data *tokenized, char **env);



int					ft_isalnum(int c);
size_t				ft_strlen(const char *s);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list	**get_garbage_pointer(void);
void	free_memory(t_list *lst);
void	*ft_malloc(size_t size);
t_list	*garbage_collection_lstnew(void *content);
char	*get_next_line(int fd);
void handle_heredoc(char *str, char **in_file_name);
void print_file(char *str);
void handle_redir_in(char *str, char **in_file_name);
char *read_file(char *file_name);
void handle_redir_out(char *str, char **file_name);
void handle_append(char *str, char **file_name);
char **get_cmd_and_its_args(t_data *arr_of_stracts);
void execute_command(char *cmd , char **av, char **env);
void	remove_quotes(char **line);

void	handle_signals_in_child(void);
char	*generate_random_name(void);

// Built-in commands
int ft_echo(char **args);
int ft_cd(char **args, char **env);
int ft_pwd(void);
int ft_export(char **args, char **env);
int ft_unset(char **args);
int ft_env(char **env);
int ft_exit(char **args);
int is_builtin(char *cmd);
int execute_builtin(char **args, char **env);

#endif
