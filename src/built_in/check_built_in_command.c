#include "minishell.h"

// void execute_built_in(char **env, char **cmd_and_args)
int  execute_built_in(t_shell_control_block *shell, int state)
{ 
    // If state is 1 (parent process), handle redirections first
    if (state == 1)
    {
        printf("DEBUG: execute_built_in - state=1, exit_status=%d\n", shell->exit_status);
        
        // Save original file descriptors
        int original_stdin = dup(0);
        int original_stdout = dup(1);
        
        // Save original tokenized pointer
        t_token *original_tokenized = shell->tokenized;
        
        // Apply redirections using the original tokens
        shell->in_file_name = NULL;
        shell->file_name = NULL;
        
        // Check if there's an ambiguous redirect error
        if (shell->exit_status == 1)
        {
            printf("DEBUG: execute_built_in - ambiguous redirect detected, processing redirections until error\n");
            // Process redirections until we hit the ambiguous redirect
            t_token *temp_tokenized = shell->tokenized;
            while (temp_tokenized && temp_tokenized->word != NULL && temp_tokenized->type != PIPE)
            {
                printf("DEBUG: execute_built_in - processing token: type=%d, word='%s'\n", temp_tokenized->type, temp_tokenized->word);
                
                if (temp_tokenized->type == HEREDOC)
                    shell->in_file_name = temp_tokenized->heredoc_file_name;
                else if (temp_tokenized->type == REDIR_IN)
                    handle_redir_in((temp_tokenized + 1)->word, &(shell->in_file_name));
                else if (temp_tokenized->type == REDIR_OUT)
                {
                    char *filename = (temp_tokenized + 1)->word;
                    printf("DEBUG: execute_built_in - REDIR_OUT with filename: '%s'\n", filename);
                    if (!filename || !*filename || ft_strlen(filename) == 0 || are_they_equal(filename, "EMPTY_REDIR"))
                    {
                        printf("DEBUG: execute_built_in - found ambiguous redirect, stopping\n");
                        // Found the ambiguous redirect - stop processing
                        break;
                    }
                    printf("DEBUG: execute_built_in - creating file: %s\n", filename);
                    handle_redir_out(filename, &(shell->file_name));
                }
                else if (temp_tokenized->type == REDIR_APPEND)
                {
                    char *filename = (temp_tokenized + 1)->word;
                    printf("DEBUG: execute_built_in - REDIR_APPEND with filename: '%s'\n", filename);
                    if (!filename || !*filename || ft_strlen(filename) == 0 || are_they_equal(filename, "EMPTY_REDIR"))
                    {
                        printf("DEBUG: execute_built_in - found ambiguous redirect, stopping\n");
                        // Found the ambiguous redirect - stop processing
                        break;
                    }
                    printf("DEBUG: execute_built_in - creating file: %s\n", filename);
                    handle_append(filename, &(shell->file_name));
                }
                temp_tokenized++;
            }
            
            printf("DEBUG: execute_built_in - returning early due to ambiguous redirect\n");
            // Don't execute the command due to ambiguous redirect
            // Restore original tokenized pointer
            shell->tokenized = original_tokenized;
            // Restore original file descriptors
            dup2(original_stdin, 0);
            dup2(original_stdout, 1);
            close(original_stdin);
            close(original_stdout);
            return 1; // Return early without executing command
        }
        
        printf("DEBUG: execute_built_in - no ambiguous redirect, processing normally\n");
        
        // Process redirections normally
        while (shell->tokenized && shell->tokenized->word != NULL && shell->tokenized->type != PIPE)
        {
            if (shell->tokenized->type == HEREDOC)
                shell->in_file_name = shell->tokenized->heredoc_file_name;
            else if (shell->tokenized->type == REDIR_IN)
                handle_redir_in((shell->tokenized + 1)->word, &(shell->in_file_name));
            else if (shell->tokenized->type == REDIR_OUT)
                handle_redir_out((shell->tokenized + 1)->word, &(shell->file_name));
            else if (shell->tokenized->type == REDIR_APPEND)
                handle_append((shell->tokenized + 1)->word, &(shell->file_name));
            shell->tokenized++;
        }
        
        // Restore original tokenized pointer
        shell->tokenized = original_tokenized;
        
        // Apply the redirections to file descriptors
        if (shell->file_name)
        {
            shell->fd_out = open(shell->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(shell->fd_out, 1);
            close(shell->fd_out);
        }
        
        if(shell->in_file_name)
        {
            shell->fd_in = open(shell->in_file_name, O_RDONLY);
            dup2(shell->fd_in, 0);
            close(shell->fd_in);
        }
        
        // Execute the built-in command
        int result = execute_built_in_command(shell);
        
        // Restore original file descriptors
        dup2(original_stdin, 0);
        dup2(original_stdout, 1);
        close(original_stdin);
        close(original_stdout);
        
        return result;
    }
    else
    {
        // State is 2 (child process) - redirections already handled
        return execute_built_in_command(shell);
    }
}

// Helper function to execute the actual built-in command
int execute_built_in_command(t_shell_control_block *shell)
{
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

