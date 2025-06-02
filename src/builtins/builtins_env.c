#include "../../include/minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

static int	set_env_var(char *arg)
{
	char	*name;
	char	*value;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (!equal)
		return (0);
	name = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	if (!name || !value)
		return (free(name), free(value), 1);
	if (setenv(name, value, 1) == -1)
		return (free(name), free(value), 1);
	free(name);
	free(value);
	return (0);
}

int	ft_export(char **args, char **env)
{
	int	i;

	(void)env;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (set_env_var(args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (unsetenv(args[i]) == -1)
			return (1);
		i++;
	}
	return (0);
} 