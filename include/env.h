#ifndef ENV_H
# define ENV_H

# include "minishell.h"

// Environment operations
char	**copy_env(char **env);
void	print_env(char **env);
void	remove_var_from_env(char ***env, char *var);

// Environment utilities
char	*ft_get_env_var(t_shell_control_block *shell, char *var_name);

#endif 