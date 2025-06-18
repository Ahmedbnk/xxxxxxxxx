#include "minishell.h"

// void execute_built_in(char **env, char **cmd_and_args)
int  execute_built_in(t_shell_control_block *shell, int state)
{ 
    // If state is 1 (parent process), handle redirections first
    if (state == 1)
    {
        // Save original file descriptors
        int original_stdin = dup(0);
        int original_stdout = dup(1);
        
        // Apply redirections
        handle_all_redir(shell);
        
        // Check if there was an ambiguous redirect error
        if (shell->exit_status == 1)
        {
            // Restore file descriptors and return
            dup2(original_stdin, 0);
            dup2(original_stdout, 1);
            close(original_stdin);
            close(original_stdout);
            return 0; // Not a built-in or error occurred
        }
        
        // Apply the redirections
        if (shell->file_name)
        {
            shell->fd_out = open(shell->file_name, O_WRONLY | O_TRUNC);
            if (shell->fd_out == -1)
            {
                shell->fd_out = open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            }
            dup2(shell->fd_out, 1);
            close(shell->fd_out);
        }
        
        if(shell->in_file_name)
        {
            shell->fd_in = open(shell->in_file_name, O_RDONLY);
            dup2(shell->fd_in, 0);
            close(shell->fd_in);
        }
    }
    
    // Execute the built-in command
    if(are_they_equal(*shell->cmd_and_args, "pwd"))
      return ((printf("%s\n",pwd()), 1));
    else if(are_they_equal(*shell->cmd_and_args, "env"))
      return ((print_env(shell->env_cpy), 1));
    else if(are_they_equal(*shell->cmd_and_args, "echo"))
      return ((echo(shell->cmd_and_args), 1));
    else if(are_they_equal(*shell->cmd_and_args, "cd"))
      return ((cd(shell->env_cpy, shell->cmd_and_args), 1));
    else if(are_they_equal(*shell->cmd_and_args, "export"))
      return((export(shell, shell->cmd_and_args +1),1));
    else if(are_they_equal(*shell->cmd_and_args, "unset"))
      return((unset(&shell->env_cpy, shell->cmd_and_args +1),1));
  return 0;
}

