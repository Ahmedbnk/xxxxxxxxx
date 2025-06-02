#include "minishell.h"

static void init_shell_state(t_shell *shell)
{
    shell->line = NULL;
    shell->splitted = NULL;
    shell->tokenized = NULL;
    shell->in_file = NULL;
    shell->out_file = NULL;
    shell->heredoc_file = NULL;
    shell->error_code = 0;
    shell->error_msg = NULL;
    shell->exit_status = 0;
    shell->is_running = 1;
}

static void process_input(t_shell *shell)
{
    shell->splitted = customized_split(shell->line);
    if (!shell->splitted)
        return;

    shell->tokenized = make_token(shell->splitted);
    if (!shell->tokenized)
    {
        free_2d_array(shell->splitted);
        return;
    }

    execute_command_line(shell, shell->tokenized);
}

static void cleanup_command_state(t_shell *shell)
{
    if (shell->line)
        free(shell->line);
    if (shell->splitted)
        free_2d_array(shell->splitted);
    if (shell->tokenized)
        free_tokenized_data(shell->tokenized);
    shell->line = NULL;
    shell->splitted = NULL;
    shell->tokenized = NULL;
}

int main(int ac, char **av, char **env)
{
    t_shell *shell;

    (void)ac;
    (void)av;
    
    shell = init_shell(env);
    if (!shell)
        return (1);

    handle_signals();
    while (shell->is_running)
    {
        init_shell_state(shell);
        shell->line = readline("minishell$ ");
        if (!shell->line)
            break;
        
        if (shell->line[0] != '\0')
        {
            add_history(shell->line);
            process_input(shell);
        }
        cleanup_command_state(shell);
    }
    
    cleanup_shell(shell);
    return (0);
} 