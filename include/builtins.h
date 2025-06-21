#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// Built-in command functions
int		execute_built_in(t_shell_control_block *shell, int state);
void	echo(char **args);
void	cd(char **env, char **path);
char	*pwd(void);
void	print_env(char **env);
void	export(t_shell_control_block *s, char **to_export);
void	unset(char ***env, char **vars);

// Built-in utility functions
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *big, const char *little, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		is_it_key_value(char *str);
int		is_valid_var(char *str);
int		compare_env_var(char *var1, char *var2);

#endif 