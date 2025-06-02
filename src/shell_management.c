#include "minishell.h"

t_shell *init_shell(char **env)
{
    t_shell *shell;

    shell = ft_malloc(sizeof(t_shell));
    if (!shell)
        return (NULL);
    
    // Initialize environment
    shell->env = copy_env(env);
    if (!shell->env)
    {
        free(shell);
        return (NULL);
    }

    // Initialize file descriptors
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);
    shell->pipe_fd[0] = -1;
    shell->pipe_fd[1] = -1;

    // Initialize pointers to NULL
    shell->line = NULL;
    shell->splitted = NULL;
    shell->tokenized = NULL;
    shell->in_file = NULL;
    shell->out_file = NULL;
    shell->heredoc_file = NULL;
    shell->pids = NULL;
    shell->error_msg = NULL;

    // Initialize state variables
    shell->is_running = 1;
    shell->heredoc_active = 0;
    shell->in_pipe = 0;
    shell->in_redir = 0;
    shell->num_commands = 0;
    shell->exit_status = 0;
    shell->error_code = 0;

    // Initialize garbage collection
    shell->garbage = NULL;

    return (shell);
}

void reset_shell_state(t_shell *shell)
{
    if (!shell)
        return;

    // Reset file descriptors
    if (shell->pipe_fd[0] != -1)
        close(shell->pipe_fd[0]);
    if (shell->pipe_fd[1] != -1)
        close(shell->pipe_fd[1]);
    shell->pipe_fd[0] = -1;
    shell->pipe_fd[1] = -1;

    // Free temporary files
    if (shell->in_file)
    {
        unlink(shell->in_file);
        free(shell->in_file);
        shell->in_file = NULL;
    }
    if (shell->out_file)
    {
        free(shell->out_file);
        shell->out_file = NULL;
    }
    if (shell->heredoc_file)
    {
        unlink(shell->heredoc_file);
        free(shell->heredoc_file);
        shell->heredoc_file = NULL;
    }

    // Reset process control
    if (shell->pids)
    {
        free(shell->pids);
        shell->pids = NULL;
    }
    shell->num_commands = 0;

    // Reset state flags
    shell->heredoc_active = 0;
    shell->in_pipe = 0;
    shell->in_redir = 0;

    // Reset error handling
    shell->error_code = 0;
    if (shell->error_msg)
    {
        free(shell->error_msg);
        shell->error_msg = NULL;
    }

    // Free command line data
    if (shell->line)
    {
        free(shell->line);
        shell->line = NULL;
    }
    if (shell->splitted)
    {
        free_2d_array(shell->splitted);
        shell->splitted = NULL;
    }
    if (shell->tokenized)
    {
        free_tokenized_data(shell->tokenized);
        shell->tokenized = NULL;
    }
}

void cleanup_shell(t_shell *shell)
{
    if (!shell)
        return;

    // Reset shell state
    reset_shell_state(shell);

    // Restore original file descriptors
    if (shell->stdin_fd != -1)
        close(shell->stdin_fd);
    if (shell->stdout_fd != -1)
        close(shell->stdout_fd);

    // Free environment
    if (shell->env)
        free_2d_array(shell->env);

    // Free garbage collection
    if (shell->garbage)
        free_memory(shell->garbage);

    // Free shell structure
    free(shell);
} 