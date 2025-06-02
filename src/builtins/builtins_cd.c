#include "../../include/minishell.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

static int	update_pwd(char *oldpwd)
{
	char	cwd[PATH_MAX];
	char	*newpwd;

	if (!getcwd(cwd, PATH_MAX))
	{
		free(oldpwd);
		return (ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2), 1);
	}
	newpwd = ft_strdup(cwd);
	if (!newpwd)
	{
		free(oldpwd);
		return (1);
	}
	if (setenv("OLDPWD", oldpwd, 1) == -1 || setenv("PWD", newpwd, 1) == -1)
	{
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	free(oldpwd);
	free(newpwd);
	return (0);
}

static int	change_directory(char *path, char *cwd)
{
	char	*oldpwd;
	int		ret;

	if (!path)
		return (1);
	ret = chdir(path);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (1);
	return (update_pwd(oldpwd));
}

int	ft_cd(char **args, char **env)
{
	char	*home;
	char	cwd[PATH_MAX];

	(void)env;
	if (!getcwd(cwd, PATH_MAX))
		return (ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2), 1);
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		home = getenv("HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
		return (change_directory(home, cwd));
	}
	if (!ft_strncmp(args[1], "-", 2))
	{
		home = getenv("OLDPWD");
		if (!home)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
		if (change_directory(home, cwd) == 0)
		{
			ft_putstr_fd(home, 1);
			ft_putstr_fd("\n", 1);
		}
		return (0);
	}
	return (change_directory(args[1], cwd));
} 