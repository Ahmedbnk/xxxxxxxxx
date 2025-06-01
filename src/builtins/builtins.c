#include "../../include/minishell.h"
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

int ft_echo(char **args)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (args[1] && !ft_strncmp(args[1], "-n", 3))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    return (0);
}

int ft_cd(char **args, char **env)
{
    char *home;
    char *oldpwd;
    char *newpwd;
    char cwd[PATH_MAX];

    (void)env;  // Silence unused parameter warning
    (void)cwd;  // Silence unused variable warning if not used in all paths

    if (!args[1] || !ft_strncmp(args[1], "~", 2))
    {
        home = getenv("HOME");
        if (!home)
            return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
        if (chdir(home) == -1)
            return (ft_putstr_fd("minishell: cd: ", 2), 
                    ft_putstr_fd(home, 2),
                    ft_putstr_fd(": No such file or directory\n", 2), 1);
    }
    else
    {
        if (chdir(args[1]) == -1)
            return (ft_putstr_fd("minishell: cd: ", 2),
                    ft_putstr_fd(args[1], 2),
                    ft_putstr_fd(": No such file or directory\n", 2), 1);
    }
    oldpwd = getenv("PWD");
    if (!getcwd(cwd, PATH_MAX))
        return (1);
    newpwd = ft_strdup(cwd);
    if (!newpwd)
        return (1);
    if (oldpwd)
        setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", newpwd, 1);
    free(newpwd);
    return (0);
}

int ft_pwd(void)
{
    char cwd[PATH_MAX];

    if (!getcwd(cwd, PATH_MAX))
        return (ft_putstr_fd("minishell: pwd: error retrieving current directory\n", 2), 1);
    ft_putstr_fd(cwd, 1);
    ft_putstr_fd("\n", 1);
    return (0);
}

int ft_export(char **args, char **env)
{
    int i;
    char *name;
    char *value;
    char *equal;

    (void)env;  // Silence unused parameter warning

    if (!args[1])
    {
        // Print all environment variables in alphabetical order
        // TODO: Implement this
        return (0);
    }
    i = 1;
    while (args[i])
    {
        equal = ft_strchr(args[i], '=');
        if (!equal)
        {
            i++;
            continue;
        }
        name = ft_substr(args[i], 0, equal - args[i]);
        value = ft_strdup(equal + 1);
        if (!name || !value)
            return (free(name), free(value), 1);
        if (setenv(name, value, 1) == -1)
            return (free(name), free(value), 1);
        free(name);
        free(value);
        i++;
    }
    return (0);
}

int ft_unset(char **args)
{
    int i;

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

int ft_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_putstr_fd(env[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return (0);
}

int ft_exit(char **args)
{
    int exit_code;

    ft_putstr_fd("exit\n", 1);
    if (!args[1])
        exit(0);
    exit_code = ft_atoi(args[1]);
    if (args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    exit(exit_code);
    return (0);
}

int is_builtin(char *cmd)
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

int execute_builtin(char **args, char **env)
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