#include "minishell.h"

void	parse_line(t_shell_control_block *shell)
{
	shell->porotect_var = generate_random_name();
	shell->splitted = customized_split(shell->line);
	shell->splitted = split_with_operators(shell->splitted);
	get_files_name(shell);
	expand_and_split(shell);
	shell->splitted = update_splitted(shell);
	shell->tokenized = make_token(shell);
}

int	main(int ac, char **av, char **env)
{
	t_shell_control_block	shell;

	ft_init_shell_block(&shell, ac, av);
	shell.env_of_export = copy_env(env);
	shell.env_cpy = copy_env(env);
	while (1)
	{
		handle_signals(0);
		if (!ft_readline(&shell))
			continue ;
		parse_line(&shell);
		execute_line(&shell);
		free_memory(get_garbage_pointer(1));
		free(shell.line);
	}
	return (0);
} 