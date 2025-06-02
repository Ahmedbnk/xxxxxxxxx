#include "minishell.h"

static void execute_with_path(t_shell *shell, char *cmd_with_its_path, char *cmd, char **av)
{
    if (access(cmd_with_its_path, X_OK) == 0)
    {
        execve(cmd_with_its_path, av, shell->env);
        exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
    }
    exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
}

static void execute_absolute_path(t_shell *shell, char *cmd, char **av)
{
    if (access(cmd, F_OK) == 0)
    {
        if (access(cmd, X_OK) == 0)
        {
            execve(cmd, av, shell->env);
            exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
        }
        exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
    }
    exit((print_error("%s: %s\n", cmd, strerror(errno)), 1));
}

static void execute_relative_path(t_shell *shell, char *cmd, char **av)
{
    int path_index;
    char *cmd_with_slash;
    char *cmd_with_its_path;

    path_index = find_cmd_in_path(cmd, shell->path);
    if (path_index == -1)
        exit((print_error("%s: command not found\n", cmd), 1));
    
    cmd_with_slash = ft_strjoin("/", cmd);
    if (!cmd_with_slash)
        exit(1);
    
    cmd_with_its_path = ft_strjoin(shell->path[path_index], cmd_with_slash);
    free(cmd_with_slash);
    if (!cmd_with_its_path)
        exit(1);
    
    execute_with_path(shell, cmd_with_its_path, cmd, av);
    free(cmd_with_its_path);
}

static int is_builtin_command(char *cmd)
{
    return (are_they_equal(cmd, "echo") || 
            are_they_equal(cmd, "cd") || 
            are_they_equal(cmd, "pwd") || 
            are_they_equal(cmd, "export") || 
            are_they_equal(cmd, "unset") || 
            are_they_equal(cmd, "env") || 
            are_they_equal(cmd, "exit"));
}

static void execute_builtin(t_shell *shell, char **cmd_and_args)
{
    if (are_they_equal(cmd_and_args[0], "echo"))
        echo(cmd_and_args + 1);
    else if (are_they_equal(cmd_and_args[0], "cd"))
        cd(shell->env, cmd_and_args[1]);
    else if (are_they_equal(cmd_and_args[0], "pwd"))
        pwd();
    else if (are_they_equal(cmd_and_args[0], "export"))
        export(&shell->env, cmd_and_args + 1);
    else if (are_they_equal(cmd_and_args[0], "unset"))
        unset(&shell->env, cmd_and_args + 1);
    else if (are_they_equal(cmd_and_args[0], "env"))
        print_env(shell->env);
    else if (are_they_equal(cmd_and_args[0], "exit"))
        exit_shell(shell, cmd_and_args + 1);
}

void execute_command(t_shell *shell, char *cmd, char **av)
{
    if (!cmd)
        return;
    
    if (is_builtin_command(cmd))
    {
        execute_builtin(shell, av);
        return;
    }
    
    if (cmd[0] == '/')
        execute_absolute_path(shell, cmd, av);
    else
        execute_relative_path(shell, cmd, av);
} 