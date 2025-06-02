#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	execute_builtin(char **args, char **env)
{
	if (!ft_strncmp(args[0], "echo", 5))
		return (ft_echo(args));
	if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(args, env));
	if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(args, env));
	if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(args));
	if (!ft_strncmp(args[0], "env", 4))
		return (ft_env(env));
	if (!ft_strncmp(args[0], "exit", 5))
		return (ft_exit(args));
	return (0);
} 